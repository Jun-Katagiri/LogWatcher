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
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};




CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ダイアログ



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);

}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
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

	CMenu* pSysMenu = GetSystemMenu(FALSE);
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
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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
	OnBnClickedBtnStop();
	CDialogEx::OnOK();
}

void CMFCApplication1Dlg::OnBnClickedBtnStart()
{
	// TODO: CFileDialog を使用して、ファイルを開くダイアログを表示するコードを追加します。
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK) {
		m_filePath = dlg.GetPathName();
		MessageBox(m_filePath);

		int pos = m_filePath.ReverseFind('\\');
		if (pos != -1) {
			m_folderPath = m_filePath.Left(pos);
			m_fileName = m_filePath.Mid(pos + 1);
		}
		else {
			m_folderPath = "";
			m_fileName = m_filePath;
		}

		// IDC_STATIC_PATH コントロールにファイルパスを表示するコードを追加します。
		SetDlgItemText(IDC_STATIC_PATH, m_folderPath + "\\" + m_fileName);

		// スレッド開始
		m_stopRequested = false;
		m_watchThread = AfxBeginThread(&CMFCApplication1Dlg::WatchThreadProc, this);
		if (m_watchThread != nullptr) {
			m_watchThread->m_bAutoDelete = FALSE;
		}

	}
}

void CMFCApplication1Dlg::OnBnClickedBtnStop()
{
	m_stopRequested = true;

	const HANDLE hDir = m_hDir.load();
	if (hDir != INVALID_HANDLE_VALUE) {
		// 停止要求のみを行い、ハンドルは監視スレッド側で閉じる
		CancelIoEx(hDir, nullptr);
	}

	if (m_watchThread != nullptr) {
		const DWORD waitResult = WaitForSingleObject(m_watchThread->m_hThread, INFINITE);
		if (waitResult != WAIT_OBJECT_0) {
			TRACE(L"[Watch] Stop wait failed. result=%lu\n", waitResult);
		}
		delete m_watchThread;
		m_watchThread = nullptr;
	}
}

void CMFCApplication1Dlg::OnDestroy()
{
	OnBnClickedBtnStop();
	CDialogEx::OnDestroy();
}


UINT CMFCApplication1Dlg::WatchThreadProc(LPVOID pParam)
{
	auto* self = reinterpret_cast<CMFCApplication1Dlg*>(pParam);

	// ディレクトリのハンドルを取得
	HANDLE hDir = CreateFileW(
		self->m_folderPath,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		nullptr
	);

	if (hDir == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		TRACE(L"[Watch] CreateFileW failed. err=%lu folder=%s\n", error, (LPCWSTR)self->m_folderPath);
		return 0;
	}

	self->m_hDir.store(hDir);

	TRACE(L"[Watch] Start watching folder: %s\n", (LPCWSTR)self->m_folderPath);

	while (!self->m_stopRequested.load()) {
		std::vector<BYTE> bufffer(64 * 1024); // 64KBのバッファ
		DWORD bytesReturned = 0;

		BOOL ok = ReadDirectoryChangesW(
			hDir,
			bufffer.data(),
			static_cast<DWORD>(bufffer.size()),
			FALSE, // サブディレクトリは監視しない
			FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE,
			&bytesReturned,
			nullptr,
			nullptr
		);

		if (!ok) {
			DWORD error = GetLastError();
			TRACE(L"[Watch] ReadDirectoryChangesW failed. err=%lu\n", error);
			break;
		}

		if (bytesReturned == 0) {
			// タイムアウト
			continue;
		}

		// 通知バッファを解析（1件とは限らない）
		BYTE* p = bufffer.data();
		while (true) {
			auto* fni = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(p);
			// 変更されたファイル名を取得
			std::wstring changedName(fni->FileName, fni->FileNameLength / sizeof(WCHAR));

			TRACE(L"[Watch] Change detected: %s (Action=%lu)\n", changedName.c_str(), fni->Action);

			if (changedName == (LPCWSTR)self->m_fileName) {
								// 監視対象のファイルが変更された
				self->PostMessage(WM_LOG_CHANGED, 0, 0);

			}

			if (fni->NextEntryOffset == 0) {
				break;
			}

			p += fni->NextEntryOffset;
		}



	}

	CloseHandle(hDir);
	self->m_hDir.store(INVALID_HANDLE_VALUE);

	TRACE(L"[Watch] Stopped.\n");

	return 0;


}

static std::wstring Utf8ToWString(const std::string& s) {
	if (s.empty()) return L"";
	int len = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
	std::wstring ws(len, L'\0');
	MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &ws[0], len);

	return ws;
}

// ログ変更ハンドラ
LRESULT CMFCApplication1Dlg::OnLogChanged(WPARAM, LPARAM)
{
	std::ifstream ifs((LPCWSTR)m_filePath, std::ios::binary);
	if (!ifs) {
		TRACE(L"[LogChanged] Failed to open file: %s\n", (LPCWSTR)m_filePath);
		return 0;
	}

	std::string bytes((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());

	// BOM付きUTF-8ならBOMをスキップ
	if (bytes.size() >= 3 &&
		(unsigned char)bytes[0] == 0xEF &&
		(unsigned char)bytes[1] == 0xBB &&
		(unsigned char)bytes[2] == 0xBF)
	{
		bytes.erase(0, 3);
	}

	std::wstring w = Utf8ToWString(bytes);

	m_editLog.SetWindowTextW(w.c_str());
	m_editLog.SetSel(-1, -1);
	m_editLog.ReplaceSel(L"");
	return 0;
}
