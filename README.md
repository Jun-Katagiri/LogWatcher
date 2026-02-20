# MFCApplication1（ログファイル監視ビューア）

Windows MFC のダイアログアプリです。  
指定したログファイルの更新を監視し、`IDC_EDIT_LOG` に内容を表示します。

## 主な機能

- ファイル選択ダイアログから監視対象ファイルを選択
- `ReadDirectoryChangesW` によるフォルダー監視
- 変更通知は `WM_LOG_CHANGED` で UI スレッドへ転送
- UI 更新は 200ms デバウンス（通知連打を集約）
- ログ表示は全読みではなく追記分のみ反映（`m_lastReadPos` 利用）
- ログローテーション / truncate 検知時は表示をリセットして先頭から再読込
- 停止時は監視スレッド終了待機まで実施

## 画面

- `IDC_EDIT_LOG`: ログ表示用 `EDIT`（複数行）
- `IDC_STATIC_PATH`: 選択中のファイルパス表示
- `IDC_BTN_START`: 監視開始
- `IDC_BTN_STOP`: 監視停止

## 動作概要

1. `Start` でファイルを選択
2. ファイルの親フォルダーを監視開始
3. 変更通知を受けたら `WM_LOG_CHANGED` をポスト
4. `OnLogChanged` はタイマー（200ms）をセットして更新要求を保留
5. `OnTimer` で `ApplyLogChanges` を 1 回実行し、追記分だけ `IDC_EDIT_LOG` に追加

## スレッドと停止処理

- 監視スレッド: `CMFCApplication1Dlg::WatchThreadProc`
- 停止要求: `m_stopRequested = true` + `CancelIoEx(hDir, nullptr)`
- ハンドルクローズ: 監視スレッド側のみで `CloseHandle(hDir)` を実行
- UI 側: スレッドハンドルを `WaitForSingleObject(..., INFINITE)` で終了待機
- ダイアログ終了時（`OnDestroy` / `OnOK`）も停止処理を通す

## 文字コード

- 対応: UTF-8（BOM あり/なし）
- 変換: `MultiByteToWideChar(CP_UTF8, ...)`
- 非対応: Shift-JIS / EUC-JP / UTF-16 など（現状）

## 既知の仕様

- `m_lastReadPos` はメモリ上のみで保持（永続化なし）
- アプリ再起動時は読み取り位置がリセットされる

## 主要コード位置

- 監視スレッド: `MFCApplication1/MFCApplication1Dlg.cpp` の `WatchThreadProc`
- 通知受信: `MFCApplication1/MFCApplication1Dlg.cpp` の `OnLogChanged`
- デバウンス: `MFCApplication1/MFCApplication1Dlg.cpp` の `OnTimer`
- 差分読込: `MFCApplication1/MFCApplication1Dlg.cpp` の `ApplyLogChanges`
