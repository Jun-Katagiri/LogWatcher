
// MFCApplication1Dlg.h : ヘッダー ファイル
//

#pragma once
#include <atomic>

constexpr UINT WM_LOG_CHANGED = WM_APP + 10;
constexpr UINT_PTR LOG_DEBOUNCE_TIMER_ID = 1;
constexpr UINT LOG_DEBOUNCE_INTERVAL_MS = 200;


// CMFCApplication1Dlg ダイアログ
class CMFCApplication1Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:

		CEdit m_editLog;

		// ファイルパスを記憶
		CString m_filePath;
		CString m_folderPath;
		CString m_fileName;
		ULONGLONG m_lastReadPos = 0;
		bool m_isMonitoring = false;

		std::atomic<bool> m_stopRequested{ false };
		CWinThread* m_watchThread = nullptr;
		std::atomic<HANDLE> m_hDir{ INVALID_HANDLE_VALUE };
		bool m_logUpdatePending = false;


	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート

	static UINT WatchThreadProc(LPVOID pParam);
	void ApplyLogChanges();

	afx_msg LRESULT OnLogChanged(WPARAM wParam, LPARAM lParam);

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditLog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
