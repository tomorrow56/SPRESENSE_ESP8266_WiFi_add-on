# SPRESENSE v1.1 Examples

[English](README_EN.md)

## 概要

このディレクトリには、SPRESENSE Wi-Fi add-on v1.1 を使用したサンプルプログラムが含まれています。v1.1 は基本的なWi-Fi通信機能を提供し、様々なIoTアプリケーションの基礎として利用できます。

## サンプル一覧

### 1. SPRESENSE_ESP8266

Wi-Fi add-onの基本的な動作を確認するためのシンプルなサンプルです。

#### 機能

- Wi-Fiアクセスポイントへの接続
- HTTPクライアントによるWebサーバーとの通信
- シリアルモニターによる通信状態の表示

#### 特徴

- 初めてSPRESENSE Wi-Fi add-onを使用する方向けの基本サンプル
- ATコマンドの基本的な使用方法を学習できます
- ESP8266との通信テストに最適

### 2. SPRESENSE_ESP8266_ambient

Ambient（IoTデータ可視化サービス）にセンサーデータを送信するサンプルです。

#### 機能

- センサーデータの定期的な取得
- Ambientサーバーへのデータ送信
- グラフによるデータ可視化

#### 必要なもの

- AmbientアカウントとチャネルID
- センサー（温度、湿度など）

### 3. SPRESENSE_SERIAL_TEST

SPRESENSEとESP8266間のシリアル通信をテストするサンプルです。

#### 機能

- シリアル通信の双方向テスト
- ATコマンドの送受信確認
- 通信速度と安定性の検証

### 4. SPRESENSE_Sparkfun_ESP8266_Phant

SparkFun Phantサービスにデータを送信するサンプルです。

#### 機能

- Phantサーバーへのデータ投稿
- IoTデータロギング
- クラウドデータストア連携

### 5. SPRESENSE_Sparkfun_ESP8266_Ping

ネットワーク接続を確認するためのPingテストサンプルです。

#### 機能

- 指定ホストへのPing送信
- ネットワーク遅延測定
- 接続状態の監視

### 6. SPRESENSE_Sparkfun_ESP8266_Shield_Demo

SparkFun ESP8266 Shieldの基本的な使用方法を示すデモンストレーションです。

#### 機能

- Wi-Fiシールドの初期化
- 各種ネットワークサービスの利用例
- 実用的なアプリケーションの雛形

## ライブラリ

### SparkFun ESP8266 AT Arduino Library

v1.1サンプルで使用されているArduinoライブラリです。

#### 機能

- ESP8266 ATコマンドの簡単なインターフェース
- Wi-Fi接続管理
- HTTP/TCP/UDP通信
- DNS解決

#### 使用方法

1. Arduino IDEにライブラリをインストール
2. サンプルスケッチを開く
3. Wi-Fi設定を変更
4. スケッチをSPRESENSEに書き込む

## ハードウェア要件

- SPRESENSEメインボード
- SPRESENSE Wi-Fi add-on v1.1
- USBケーブル（プログラミング用）
- Wi-Fiアクセスポイント

## 設定

すべてのサンプルで、以下の設定が必要です：

```cpp
// Wi-Fi設定
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
```

各サンプル固有の設定については、スケッチ内のコメントを参照してください。

## 注意事項

- 本サンプルはSPRESENSE Wi-Fi add-on v1.1専用です
- v2.2のDeep Sleep機能には対応していません
- Wi-Fi接続には2.4GHz帯のアクセスポイントが必要です
- 一部のサンプルでは外部サービスのアカウントが必要です

## ライセンス

各サンプルコードおよびライブラリは、プロジェクト全体と同じくGNU General Public License v3.0の下で提供されます。
