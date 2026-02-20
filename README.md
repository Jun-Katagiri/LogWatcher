# MFCApplication1（ログファイル監視ビューア）

Windows（MFC）のダイアログアプリです。選択したログファイルが更新されたことを検知し、内容を画面の `IDC_EDIT_LOG` に表示します。

## 機能

- ファイル選択（開始ボタン）
- 監視対象ファイルのあるフォルダーを `ReadDirectoryChangesW` で監視
- 監視対象ファイルの変更を検知したら、`WM_LOG_CHANGED` を `PostMessage` でUIスレッドへ通知
- `OnLogChanged` でファイルを読み直して `m_editLog` に表示
- 停止ボタンで監視停止（ハンドルを閉じて `ReadDirectoryChangesW` を解除）

## 画面（リソース）

- `IDC_EDIT_LOG`: ログ表示用の `EDIT`（複数行）
- `IDC_STATIC_PATH`: 選択したパス表示
- `IDC_BTN_START`: 開始
- `IDC_BTN_STOP`: 停止

## 動作要件

- Windows 10/11
- Visual Studio（C++/MFC がインストール済み）
- MFC（ダイアログベース）

## ビルド方法

1. Visual Studio でソリューションを開く
2. 構成（`Debug` / `Release`）とプラットフォーム（`x64` など）を選択
3. ビルドして実行

## 使い方

1. アプリ起動
2. **開始**を押して監視したいファイルを選択
3. 選択したファイルが更新されると、内容が `IDC_EDIT_LOG` に反映されます
4. **停止**で監視を止めます

## 文字コードについて

`OnLogChanged` はバイナリで読み込み、UTF-8（BOMあり/なし）を想定して `MultiByteToWideChar(CP_UTF8, ...)` で `std::wstring` に変換します。

- UTF-8 BOM（`EF BB BF`）がある場合はスキップします
- UTF-8 以外（Shift-JIS等）のファイルを読む場合は、変換処理の拡張が必要です

## 実装メモ

- 監視スレッド: `CMFCApplication1Dlg::WatchThreadProc`
- UI通知: `WM_LOG_CHANGED`（`WM_APP + 10`）
- UI更新: `CMFCApplication1Dlg::OnLogChanged`
- `m_editLog` は `DoDataExchange` で `DDX_Control(pDX, IDC_EDIT_LOG, m_editLog)` により紐づけています

## 既知の注意点 / 今後の改善候補

- 「開始」を複数回押した場合の二重起動ガード
- 大きいファイルの全読み込みではなく追記分のみ反映（`m_lastReadPos` の活用）
- 変更通知が多い場合のデバウンス（一定時間まとめて更新）
- エラーハンドリング（ファイルオープン失敗、権限不足など）

## リポジトリ

- `.gitignore` は Visual Studio / C++ の生成物（`.vs/`, `x64/`, `*.pdb` など）を除外する設定を含みます