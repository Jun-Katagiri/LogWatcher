// MFCApplication1Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <atomic>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_ABOUTBOX
	};
#endif

protected:
	virtual void DoDataExchange(CDataExchange *pDX); // DDX/DDV サポート

	// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCApplication1Dlg ダイアログ

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd *pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange *pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_DESTROY()
ON_WM_TIMER()
ON_EN_CHANGE(IDC_EDIT_LOG, &CMFCApplication1Dlg::OnEnChangeEditLog)
ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_BTN_START, &CMFCApplication1Dlg::OnBnClickedBtnStart)
ON_BN_CLICKED(IDC_BTN_STOP, &CMFCApplication1Dlg::OnBnClickedBtnStop)
ON_MESSAGE(WM_LOG_CHANGED, &CMFCApplication1Dlg::OnLogChanged)
END_MESSAGE_MAP()

// CMFCApplication1Dlg メッセージ ハンドラー

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);	 // 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE); // 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE; // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnEnChangeEditLog()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
}

void CMFCApplication1Dlg::OnBnClickedOk()
{
	// ダイアログを閉じる前に監視停止を完了させる。
	// ここで待機しておくことで、終了直前のスレッドアクセス競合を避ける。
	OnBnClickedBtnStop();
	CDialogEx::OnOK();
}

void CMFCApplication1Dlg::OnBnClickedBtnStart()
{
	// 監視対象ファイルを選択する。
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		m_filePath = dlg.GetPathName();
		MessageBox(m_filePath);

		// 監視APIはフォルダー単位なので、ファイルパスを
		// 「フォルダー」と「ファイル名」に分解して保持する。
		int pos = m_filePath.ReverseFind('\\');
		if (pos != -1)
		{
			m_folderPath = m_filePath.Left(pos);
			m_fileName = m_filePath.Mid(pos + 1);
		}
		else
		{
			m_folderPath = "";
			m_fileName = m_filePath;
		}

		// UI表示と読み取り状態を初期化する。
		SetDlgItemText(IDC_STATIC_PATH, m_folderPath + "\\" + m_fileName);
		m_lastReadPos = 0;
		m_logUpdatePending = false;
		KillTimer(LOG_DEBOUNCE_TIMER_ID);
		m_editLog.SetWindowTextW(L"");

		// 新しい監視スレッドを開始する。
		m_stopRequested = false;
		m_watchThread = AfxBeginThread(&CMFCApplication1Dlg::WatchThreadProc, this);
		if (m_watchThread != nullptr)
		{
			// UI側で delete して生存管理するため、自動解放を無効化。
			m_watchThread->m_bAutoDelete = FALSE;
		}
	}
}

void CMFCApplication1Dlg::OnBnClickedBtnStop()
{
	// 新規通知を止め、保留中のUI更新も破棄する。
	m_stopRequested = true;
	KillTimer(LOG_DEBOUNCE_TIMER_ID);
	m_logUpdatePending = false;

	const HANDLE hDir = m_hDir.load();
	if (hDir != INVALID_HANDLE_VALUE)
	{
		// ブロッキング中の ReadDirectoryChangesW を解除する。
		// ハンドルの Close は監視スレッド側に一本化している。
		CancelIoEx(hDir, nullptr);
	}

	if (m_watchThread != nullptr)
	{
		// 完全停止まで待機。待機完了後に CWinThread を解放する。
		const DWORD waitResult = WaitForSingleObject(m_watchThread->m_hThread, INFINITE);
		if (waitResult != WAIT_OBJECT_0)
		{
			TRACE(L"[Watch] Stop wait failed. result=%lu\n", waitResult);
		}
		delete m_watchThread;
		m_watchThread = nullptr;
	}
}

void CMFCApplication1Dlg::OnDestroy()
{
	// 破棄経路でもタイマーと監視スレッドを必ず停止する。
	KillTimer(LOG_DEBOUNCE_TIMER_ID);
	OnBnClickedBtnStop();
	CDialogEx::OnDestroy();
}

UINT CMFCApplication1Dlg::WatchThreadProc(LPVOID pParam)
{
	auto *self = reinterpret_cast<CMFCApplication1Dlg *>(pParam);

	// ReadDirectoryChangesW を使うため、フォルダーハンドルを開く。
	HANDLE hDir = CreateFileW(
		self->m_folderPath,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		nullptr);

	if (hDir == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();
		TRACE(L"[Watch] CreateFileW failed. err=%lu folder=%s\n", error, (LPCWSTR)self->m_folderPath);
		return 0;
	}

	// 停止側（UIスレッド）から CancelIoEx で参照できるよう公開する。
	self->m_hDir.store(hDir);

	TRACE(L"[Watch] Start watching folder: %s\n", (LPCWSTR)self->m_folderPath);

	while (!self->m_stopRequested.load())
	{
		// 通知は可変長エントリで複数件返るため、十分なバッファを毎回用意する。
		std::vector<BYTE> bufffer(64 * 1024); // 64KBのバッファ
		DWORD bytesReturned = 0;

		// 同期I/Oで変更通知を待つ。停止時は CancelIoEx でこの呼び出しを解除する。
		BOOL ok = ReadDirectoryChangesW(
			hDir,
			bufffer.data(),
			static_cast<DWORD>(bufffer.size()),
			FALSE, // サブディレクトリは監視しない
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE,
			&bytesReturned,
			nullptr,
			nullptr);

		if (!ok)
		{
			DWORD error = GetLastError();
			// 停止要求による中断（ERROR_OPERATION_ABORTED）もここに入る。
			TRACE(L"[Watch] ReadDirectoryChangesW failed. err=%lu\n", error);
			break;
		}

		if (bytesReturned == 0)
		{
			// 今回は有効通知なし。
			continue;
		}

		// 通知バッファを解析（1件とは限らない）
		BYTE *p = bufffer.data();
		while (true)
		{
			auto *fni = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(p);
			// 変更されたファイル名を取得
			std::wstring changedName(fni->FileName, fni->FileNameLength / sizeof(WCHAR));

			TRACE(L"[Watch] Change detected: %s (Action=%lu)\n", changedName.c_str(), fni->Action);

			if (changedName == (LPCWSTR)self->m_fileName)
			{
				// 実ファイル読み込みはUI側に任せる（スレッド境界を明確化）。
				self->PostMessage(WM_LOG_CHANGED, 0, 0);
			}

			if (fni->NextEntryOffset == 0)
			{
				break;
			}

			p += fni->NextEntryOffset;
		}
	}

	// ハンドルクローズは監視スレッドのみで実行する。
	CloseHandle(hDir);
	self->m_hDir.store(INVALID_HANDLE_VALUE);

	TRACE(L"[Watch] Stopped.\n");

	return 0;
}

static std::wstring Utf8ToWString(const std::string &s)
{
	if (s.empty())
		return L"";
	// 入力を UTF-8 前提で UTF-16(wstring) に変換する。
	int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
	std::wstring ws(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &ws[0], len);

	return ws;
}

// ログ変更ハンドラ
LRESULT CMFCApplication1Dlg::OnLogChanged(WPARAM, LPARAM)
{
	// 通知連打をそのまま処理するとUI更新が過密になるため、
	// 実読み込みはタイマー満了時に1回へ集約する。
	m_logUpdatePending = true;
	SetTimer(LOG_DEBOUNCE_TIMER_ID, LOG_DEBOUNCE_INTERVAL_MS, nullptr);
	return 0;
}

void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == LOG_DEBOUNCE_TIMER_ID)
	{
		// ワンショット運用なので都度止める。
		KillTimer(LOG_DEBOUNCE_TIMER_ID);
		if (m_logUpdatePending)
		{
			m_logUpdatePending = false;
			// まとめて1回だけ差分反映する。
			ApplyLogChanges();
		}
		return;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCApplication1Dlg::ApplyLogChanges()
{
	// 監視対象のログファイルをバイナリで開く。
	// 文字コード変換は読み取り後にUTF-8として実施する。
	std::ifstream ifs((LPCWSTR)m_filePath, std::ios::binary);
	if (!ifs)
	{
		TRACE(L"[LogChanged] Failed to open file: %s\n", (LPCWSTR)m_filePath);
		return;
	}

	ifs.seekg(0, std::ios::end);
	const std::streamoff endPos = ifs.tellg();
	if (endPos < 0)
	{
		TRACE(L"[LogChanged] Failed to get file size: %s\n", (LPCWSTR)m_filePath);
		return;
	}
	const ULONGLONG fileSize = static_cast<ULONGLONG>(endPos);

	// ログローテーション/truncate を検知したら表示をリセットして先頭から読む
	if (fileSize < m_lastReadPos)
	{
		m_lastReadPos = 0;
		m_editLog.SetWindowTextW(L"");
	}

	// サイズが進んでいなければ追加分はない。
	if (fileSize == m_lastReadPos)
	{
		return;
	}

	// 前回読み取り位置から末尾までのみ取得する。
	ifs.seekg(static_cast<std::streamoff>(m_lastReadPos), std::ios::beg);
	if (!ifs)
	{
		TRACE(L"[LogChanged] Failed to seek file: %s pos=%llu\n", (LPCWSTR)m_filePath, m_lastReadPos);
		return;
	}

	const ULONGLONG delta = fileSize - m_lastReadPos;
	std::string bytes(static_cast<size_t>(delta), '\0');
	ifs.read(&bytes[0], static_cast<std::streamsize>(bytes.size()));
	const std::streamsize readBytes = ifs.gcount();
	if (readBytes <= 0)
	{
		return;
	}
	bytes.resize(static_cast<size_t>(readBytes));
	// 次回の差分計算用に読み取り位置を進める。
	m_lastReadPos += static_cast<ULONGLONG>(readBytes);

	// 先頭読み込み時のみ BOM付きUTF-8 を考慮して BOM を除去する。
	if (m_lastReadPos == static_cast<ULONGLONG>(readBytes) &&
		bytes.size() >= 3 &&
		(unsigned char)bytes[0] == 0xEF &&
		(unsigned char)bytes[1] == 0xBB &&
		(unsigned char)bytes[2] == 0xBF)
	{
		bytes.erase(0, 3);
	}

	std::wstring w = Utf8ToWString(bytes);

	// 常に末尾へ追記する。
	m_editLog.SetSel(-1, -1);
	m_editLog.ReplaceSel(w.c_str());
}
