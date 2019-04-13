
// TestTofuGuiDlg.h : header file
//

#pragma once


// CTestTofuGuiDlg dialog
class CTestTofuGuiDlg : public CDialogEx
{
// Construction
public:
	CTestTofuGuiDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTTOFUGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	static int CALLBACK metafileproc(HDC, HANDLETABLE *, const ENHMETARECORD * record, int, LPARAM logfont);
	HFONT GetFallbackFont(const wchar_t * str, HFONT hfont_test);
	bool IsTofu(HDC hdc, HFONT hfont_test, const wchar_t * str);
	HFONT get_font_link(const wchar_t ch, HDC hdc, HFONT hfont, CComPtr<IMLangFontLink>& ifont, CComPtr<IMLangCodePages>& icodepages);
	int testGlyphs();
	void checkCodePoint(const wchar_t * single_codepoint, CComPtr<IMLangFontLink>& ifont, CComPtr<IMLangCodePages>& icodepages);
	static int isCharWhitespace(WCHAR ch);
	static void AddStatusMsg(LPCTSTR pszFormat, ...);
	DECLARE_MESSAGE_MAP()
};
