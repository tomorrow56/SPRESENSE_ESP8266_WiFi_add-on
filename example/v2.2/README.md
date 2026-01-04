# SPRESENSE v2.2 Examples

[English](README_EN.md)

## 概要

このディレクトリには、SPRESENSE Wi-Fi add-on v2.2 を使用したサンプルプログラムが含まれています。v2.2 では ESP8266 の Deep Sleep 機能に対応し、SPRESENSE の Cold Sleep 機能と組み合わせることで、バッテリー駆動時の消費電力を大幅に削減できます。

## サンプル一覧

### 1. SPRESENSE_PIR_to_LINE

PIR（人感）センサーの割込み検出をトリガーとして、SPRESENSEとESP8266経由でLINE Messaging APIにメッセージを送信する省電力IoTアプリケーションです。

#### 特徴

- **超低消費電力設計**: 待機時は ESP8266 を Deep Sleep、SPRESENSE を Cold Sleep にすることで、消費電力を数μAレベルに抑制
- **イベント駆動**: PIRセンサーによる人体検出で自動的に起動し、メッセージ送信後に再びスリープ状態へ移行
- **リアルタイム通知**: LINEアプリに即時通知を送信可能

#### 動作概要

1. **初期化**: SPRESENSEとESP8266を初期化し、Wi-Fi接続を確立
2. **スリープ移行**: ESP8266をDeep Sleep、SPRESENSEをCold Sleepに移行
3. **イベント検出**: PIRセンサーが人体を検出し、SPRESENSEを起動
4. **処理実行**: ESP8266を起動し、LINE Messaging API経由でメッセージを送信
5. **再スリープ**: 処理完了後、再び両チップをスリープ状態へ

#### 必要なハードウェア

- SPRESENSEメインボード
- SPRESENSE Wi-Fi add-on v2.2
- PIRセンサーモジュール（出力：HIGH/LOWデジタル信号）
- 電源（バッテリーまたはUSB電源）

#### 設定

使用前に以下の設定が必要です：

- Wi-Fiアクセスポイント情報（SSID、パスワード）
- LINE Messaging APIのチャネルアクセストークン
- 通知先のLINEグループまたはユーザーID

詳しい設定方法は、各スケッチのコメントを参照してください。

### 2. Library/ESP8266_LINE_Messaging_API

LINE Messaging APIをSPRESENSE + ESP8266で簡単に利用するためのArduinoライブラリです。

#### 機能

- LINE Messaging API v3.0対応
- テキストメッセージ送信機能
- 簡単な初期化と認証処理
- エラーハンドリング機能

#### 使用方法

ライブラリをArduino IDEにインストール後、サンプルスケッチを参考に以下の手順で使用します：

1. ライブラリをインクルード
2. アクセストークンを設定
3. Wi-Fi接続を確立
4. メッセージ送信関数を呼び出し

詳細なAPIリファレンスはライブラリ内のコメントを参照してください。

## 省電力機能について

### Deep Sleep (ESP8266)

- 消費電力: 約10μA
- 起動時間: 約200ms
- リセットピン（D21）制御で起動

### Cold Sleep (SPRENSE)

- 消費電力: 約1μA（RTC除く）
- 起動時間: 約1ms
- GPIO割込みで起動

### 組合せ効果

両スリープ機能を組み合わせることで、バッテリー駆動時の動作寿命を大幅に延長できます。例えば、1日数回のイベント検知用途であれば、コイン電池での数ヶ月〜数年の駆動も可能です。

## 注意事項

- 本サンプルはSPRESENSE Wi-Fi add-on v2.2専用です。v1.1では動作しません。
- Deep Sleep機能を使用するため、リセットピン（D21）の接続が必要です。
- 電源電圧や周囲温度によってスリープ時の消費電力は変動します。
- LINE Messaging APIの利用にはインターネット接続が必要です。

## ライセンス

各サンプルコードおよびライブラリは、プロジェクト全体と同じくGNU General Public License v3.0の下で提供されます。