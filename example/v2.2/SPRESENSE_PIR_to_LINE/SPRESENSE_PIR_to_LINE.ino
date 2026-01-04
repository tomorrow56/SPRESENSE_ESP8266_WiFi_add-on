/************************************************************
* ESP8266 WiFi add-on for SPRESENSE
* LINE Messaging API Send Message Library and DeepSleep Example
* Copyright(c) @tomorrow56 All rights reserved.
* ESP8266 baudrate: 115200 baud
************************************************************/

#include "Arduino.h"
#include "LineMessenger.h"
#include <LowPower.h>

#define debug true       // デバッグモード

#define rst_pin PIN_D21   // ESP8266のリセットピン, Hでリセット
#define wake_pin PIN_D14  // SPRESENSEのWakeUpトリガピン, LでWakeUp

// WiFiとLINEの設定
const char* ssid = "<your SSID>";
const char* password = "<your Password>";
// 以下からLINEチャネルアクセストークンを取得する
// https://developers.line.biz/ja/docs/messaging-api/getting-started/
const char* accessToken =  "<your LINE Access Token>";

// Line Messaging API インスタンス作成
LineMessenger line;

bool wakeUpFlag = false;    // WakeUp割り込みフラグ, trueでWakeUp
bool sendCompleteFlag = false;  // LINE Message 送信フラグ, trueで送信完了

bootcause_e bc; // 起動要因を格納する変数

// 起動要因の列挙型
const char* boot_cause_strings[] = {
  "Power On Reset with Power Supplied",
  "System WDT expired or Self Reboot",
  "Chip WDT expired",
  "WKUPL signal detected in deep sleep",
  "WKUPS signal detected in deep sleep",
  "RTC Alarm expired in deep sleep",
  "USB Connected in deep sleep",
  "Others in deep sleep",
  "SCU Interrupt detected in cold sleep",
  "RTC Alarm0 expired in cold sleep",
  "RTC Alarm1 expired in cold sleep",
  "RTC Alarm2 expired in cold sleep",
  "RTC Alarm Error occurred in cold sleep",
  "Unknown(13)",
  "Unknown(14)",
  "Unknown(15)",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "GPIO detected in cold sleep",
  "SEN_INT signal detected in cold sleep",
  "PMIC signal detected in cold sleep",
  "USB Disconnected in cold sleep",
  "USB Connected in cold sleep",
  "Power On Reset",
};

// ESP8266からの受信バッファをクリアする関数
void clearSerial2Buffer() {
  while (Serial2.available() > 0) {
    Serial2.read(); // バッファから1バイトずつ読み出して捨てる
  }
}

// ESP8266をリセットする関数
void resetESP8266() {
  Serial.println("ESP8266 has been reset...");
  digitalWrite(rst_pin, HIGH);  // リセットピンをHにする
  delay(200);
  digitalWrite(rst_pin, LOW);  // リセットピンをLにする

  //ESP8266起動時のゴミデータを捨てる
  delay(250);
  clearSerial2Buffer();

  digitalWrite(LED1, HIGH);  // LED1を点灯
}

// ESP8266をDeep Sleepに移行する関数
void gotoSleepESP8266() {
  // ESP8266をDeep Sleepに移行（最大時間: 約71分、単位はマイクロ秒）
  // AT+GSLP=0は無限スリープ（外部リセットが必要）

  line.sendCommand("AT+GSLP=0", 1000);
  Serial.println("ESP8266 goes to deep sleep mode...");
  
  digitalWrite(LED3, HIGH);  // LED3を点灯

  delay(1000); // Deep Sleepに完全に入るまでの待ち時間
}

// SPRESENSEの起動要因を表示する関数 
void printBootCause(bootcause_e bc) {
  Serial.println("--------------------------------------------------");
  Serial.print("Boot Cause: ");
  Serial.print(boot_cause_strings[bc]);
  if ((COLD_GPIO_IRQ36 <= bc) && (bc <= COLD_GPIO_IRQ47)) {
    // Wakeup by GPIO
    int pin = LowPower.getWakeupPin(bc);
    Serial.print(" <- pin ");
    Serial.print(pin);
  }
  Serial.println();
  Serial.println("--------------------------------------------------");
}

// SPRESENSEのWakeUp割り込み関数
void wakeUpISR() {
 // Print the boot cause
 printBootCause(bc);
 Serial.println("wakeup from cold sleep");
 wakeUpFlag = true;  // set flag
}

// SPRESENSEをCold Sleepに移行する関数
void gotoSleep() {
 Serial.println("SPRESENSE goes to cold sleep...");
 Serial.println("Wait until wake_pin is low.");

 digitalWrite(LED0, LOW);  // LED0を消灯
 digitalWrite(LED1, LOW);  // LED1を消灯
 digitalWrite(LED2, LOW);  // LED2を消灯
 digitalWrite(LED3, LOW);  // LED3を消灯

 delay(100);
 LowPower.coldSleep();
}

void setup() {

  // シリアル通信の初期化
  Serial.begin(115200);    // SPRESENSEデバッグ用シリアル
  Serial2.begin(115200);   // ESP8266用シリアル
  // シリアル通信が確立するまで待機
  while (!Serial);
  while (!Serial2);

  // LEDの設定
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // ESP8266のリセットピンの設定
  pinMode(rst_pin, OUTPUT);
  // ESP8266のリセットを解除する(リセットピンをLにする)
  digitalWrite(rst_pin, LOW);

  //ESP8266起動時のゴミデータを捨てる
  delay(250);
  clearSerial2Buffer();

  // SPRESENSE LowPowerライブラリの初期化
  LowPower.begin();
  // 起動要因を取得
  bc = LowPower.bootCause();
      
  //  WakeUp割り込みではない場合は開始メッセージを表示
  if ((bc == POR_SUPPLY) || (bc == POR_NORMAL)) {
    Serial.println("--------------------------------------------------");
    Serial.println("DeepSleep->Line Send Message Example");
    Serial.println("--------------------------------------------------");
  }

  digitalWrite(LED0, HIGH);  // LED0を点灯

  // WakeUpピンの設定
  pinMode(wake_pin, INPUT_PULLUP);
  // WakeUp割り込みの設定
  //attachInterrupt(pin, void (*isr)(void), mode, filter);
  attachInterrupt(wake_pin, wakeUpISR, FALLING, true);
  // WakeUpピンによる起動を有効にする
  LowPower.enableBootCause(wake_pin);

  gotoSleepESP8266();  // ESP8266をDeep Sleepに移行

  // WakeUp割り込み以外で起動した場合はSPRESENSEをCold Sleepに移行
  if (wakeUpFlag == false) {
    gotoSleep();  // Cold sleep
    }
}

void loop() {
  if (wakeUpFlag) {
    if(sendCompleteFlag == false) {   // LINE Messageを送信完了していない場合
      // ESP8266をリセットしてDeep Sleepから起動
       resetESP8266();

      Serial.println("ESP8266 was woken up from deep sleep by the RST pin.");
      // アクセストークン設定
      line.setAccessToken(accessToken);
      // WiFi接続
      if (line.connectWiFi(ssid, password, debug)) {
        Serial.println("WiFi connected");

        digitalWrite(LED2, HIGH);  // LED2を点灯

        // LINEメッセージ送信
        line.sendMessage("人感センサーが反応しました。部屋に誰かがいる可能性があります。", debug);
      } else {
        Serial.println("WiFi connection failed");
      }
      sendCompleteFlag = true;  // LINE Message 送信完了
      gotoSleepESP8266();  // ESP8266をDeep Sleepに移行
    }
    // WakeUpピンが開放された場合(HIGH)はCold Sleepに移行
    if(digitalRead(wake_pin)) {
      wakeUpFlag = false;
      gotoSleep();  // Cold sleep
    }
  }
  delay(100);
}