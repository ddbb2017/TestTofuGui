
// TestTofuGuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestTofuGui.h"
#include "TestTofuGuiDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CTestTofuGuiDlg dialog



CTestTofuGuiDlg::CTestTofuGuiDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTTOFUGUI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestTofuGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestTofuGuiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CTestTofuGuiDlg message handlers

BOOL CTestTofuGuiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here


	//Change the font here
	CWnd* pWndTxt = this->GetDlgItem(IDC_STATIC_1);
	ASSERT(pWndTxt);
//	pWndTxt->SetFont(CFont::FromHandle((HFONT)::GetStockObject(SYSTEM_FONT)));


	//Do all the tests here
	testGlyphs();



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestTofuGuiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestTofuGuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestTofuGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




int CTestTofuGuiDlg::metafileproc(HDC, HANDLETABLE*, const ENHMETARECORD *record,
    int, LPARAM logfont)
{
    if(record->iType == EMR_EXTCREATEFONTINDIRECTW)
    {
        auto ptr = (const EMREXTCREATEFONTINDIRECTW*)record;
        *(LOGFONT*)logfont = ptr->elfw.elfLogFont;
    }
    return 1;
}

HFONT CTestTofuGuiDlg::GetFallbackFont(const wchar_t *str, HFONT hfont_test)
{
    //use metafile to find the fallback font
    auto metafile_hdc = CreateEnhMetaFile(NULL, NULL, NULL, NULL);
    auto metafile_oldfont = SelectObject(metafile_hdc, hfont_test);

    SCRIPT_STRING_ANALYSIS ssa;
    ScriptStringAnalyse(metafile_hdc, str, (int)wcslen(str), 0, -1,
        SSA_METAFILE | SSA_FALLBACK | SSA_GLYPHS | SSA_LINK,
        0, NULL, NULL, NULL, NULL, NULL, &ssa);
    ScriptStringOut(ssa, 0, 0, 0, NULL, 0, 0, FALSE);
    ScriptStringFree(&ssa);

    SelectObject(metafile_hdc, metafile_oldfont);
    auto hmetafile = CloseEnhMetaFile(metafile_hdc);

    LOGFONT logfont = { 0 };
    EnumEnhMetaFile(0, hmetafile, metafileproc, &logfont, NULL);
    AddStatusMsg(L"Selecting fallback font: %s\n", logfont.lfFaceName);
    HFONT hfont = CreateFontIndirect(&logfont);
    DeleteEnhMetaFile(hmetafile);

    return hfont;
}

bool CTestTofuGuiDlg::IsTofu(HDC hdc, HFONT hfont_test, const wchar_t *str)
{
    if(wcsstr(str, L" "))
    {
        AddStatusMsg(L"*** cannot test strings containing blank space\n");
		ASSERT(NULL);
    }

    auto hfont = GetFallbackFont(str, hfont_test);
    auto oldfont = SelectObject(hdc, hfont);

    //find the characters not supported in this font
    //note, blank space is blank, unsupported fonts can be blank also
    SCRIPT_CACHE sc = NULL;
    SCRIPT_FONTPROPERTIES fp = { sizeof(fp) };
    ScriptGetFontProperties(hdc, &sc, &fp);
    ScriptFreeCache(&sc);
    AddStatusMsg(L"SCRIPT_FONTPROPERTIES:\n");
    AddStatusMsg(L" Blank: %d, Default: %d, Invalid: %d\n",
        fp.wgBlank, fp.wgDefault, fp.wgInvalid);

	int nchSzStr = (int)wcslen(str);

    // Get glyph indices for the string
    GCP_RESULTS gcp_results = { sizeof(GCP_RESULTS) };
    gcp_results.nGlyphs = nchSzStr;
    auto wstr_memory = (wchar_t*)calloc(wcslen(str) + 1, sizeof(wchar_t));
    gcp_results.lpGlyphs = wstr_memory;
    GetCharacterPlacement(hdc, str, nchSzStr, 0, &gcp_results, GCP_GLYPHSHAPE);

    //check the characters against wgBlank...
    bool istofu = false;
    AddStatusMsg(L"Glyphs:");
    for(UINT i = 0; i < gcp_results.nGlyphs; i++)
    {
        wchar_t n = gcp_results.lpGlyphs[i];
        AddStatusMsg(L"%d,", (int)n);
        if(n == fp.wgBlank || n == fp.wgInvalid || n == fp.wgDefault)
		{
            istofu = true;

			//Correction: No need to loop here anymore
			break;
		}
    }
    AddStatusMsg(L"\n");

    free(wstr_memory);
    SelectObject(hdc, oldfont);
    DeleteObject(hfont);

    return istofu;
}

HFONT CTestTofuGuiDlg::get_font_link(const wchar_t ch, 
    HDC hdc, 
    HFONT hfont,
    CComPtr<IMLangFontLink> &ifont,
    CComPtr<IMLangCodePages> &icodepages)
{
	//RETURN:
	//		= Font handle -- when done using it call IMLangFontLink::ReleaseFont()
	//		= NULL if error

    //DWORD codepages_dst[100] = { 0 };
    //LONG codepages_count = 100;				//DO NOT hardcode!

    DWORD codepages = 0;
    HFONT hfont_new = NULL;

	//Correction: Removed the following due to possibility of the buffer overflow!
	//
    //if(SUCCEEDED(icodepages->GetStrCodePages(str, wcslen(str), 0, codepages_dst, &codepages_count)))
    //    codepages = codepages_dst[0];

	if(SUCCEEDED(icodepages->GetCharCodePages(ch, &codepages)))
	{
		if(SUCCEEDED(ifont->MapFont(hdc, codepages, hfont, &hfont_new)))
		{

			//This part below is needed only for debugging output
			HGDIOBJ hOldFont = SelectObject(hdc, hfont);
			SelectObject(hdc, hfont_new);
			wchar_t buf[100];
			GetTextFace(hdc, _countof(buf), buf);
			AddStatusMsg(L"Selecting a different font: %s\n", buf);
			SelectObject(hdc, hOldFont);


		}

	}


    return hfont_new;
}

int CTestTofuGuiDlg::testGlyphs()
{
	//SOURCES:
	//		https://stackoverflow.com/questions/54050095/how-to-tell-if-a-surrogate-pair-unicode-character-is-supported-by-the-font
	//		https://devblogs.microsoft.com/oldnewthing/20040716-00/?p=38413
	//

	//IMPORTANT:
	//      Due to this project being just a DEMO, most of the error handling
	//      has been omitted by me and the original author of this code on SO!
	//      DO NOT USE IT AS-IS IN YOUR PRODUCTION CODE!


    bool bComInitted = SUCCEEDED(CoInitialize(NULL));

	if(true)	//Need this so that CoUninitialize() is called after destructors below
    {
        CComPtr<IMultiLanguage> imultilang;
        CComPtr<IMLangFontLink> ifont;
        CComPtr<IMLangCodePages> icodepages;
        if(FAILED(imultilang.CoCreateInstance(CLSID_CMultiLanguage))) return 0;
        if(FAILED(imultilang.QueryInterface(&ifont))) return 0;
        if(FAILED(imultilang.QueryInterface(&icodepages))) return 0;


		//Have to check code-point by code-point (CAN'T DO it all at once!)
		//If you need to check the string, break it up into glyphs
		//using IS_SURROGATE_PAIR() macro and then check them one-by-one.
		//Also make sure to remove whitespaces first. They don't work.
		//My partially working code (for surrogate pairs only) that
		//shows most of that prep-work can be found here:
		//  https://pastebin.com/67DuKmgv
		//
		checkCodePoint(L"A", ifont, icodepages);
		checkCodePoint(L"请", ifont, icodepages);
		checkCodePoint(L"😉", ifont, icodepages);

    }

	if(bComInitted)
		CoUninitialize();


    return 0;
}


void CTestTofuGuiDlg::checkCodePoint(const wchar_t *single_codepoint, CComPtr<IMLangFontLink>& ifont, CComPtr<IMLangCodePages>& icodepages)
{
	//INFO: This method contains my corrections for the original code sample posted on SO.

	//Is it a surrogate pair vs just a WCHAR
	ASSERT(single_codepoint);					//OK, where's the string?
	size_t szchLn = wcslen(single_codepoint);
	BOOL bSurrogatePair = szchLn >= 1 && IS_SURROGATE_PAIR(single_codepoint[0], single_codepoint[1]);


#ifdef _DEBUG
	//Check if the caller got the message?
	ASSERT(szchLn != 0);						//Provide something to test!
	if(bSurrogatePair)
	{
		//It must be a single glyph only!
		ASSERT(szchLn == 2);
	}
	else
	{
		//It must be a single WCHAR only!
		ASSERT(szchLn == 1);

		//Additionally it must not be an empty WCHAR!
		ASSERT(isCharWhitespace(single_codepoint[0]) == 0);
	}
#endif

	//We're doing it for our demo STATIC control (but it can be any window with a single font)
	CWnd* pWnd = this->GetDlgItem(IDC_STATIC_1);
	ASSERT(pWnd);

	HWND hWnd = pWnd->GetSafeHwnd();
    HDC hdc = ::GetDC(hWnd);
    //HDC memdc = CreateCompatibleDC(hdc);						//Correction: Unnecessary complexity
    //HBITMAP hbitmap = CreateCompatibleBitmap(hdc, 1, 1);
    //auto oldbmp = SelectObject(memdc, hbitmap);

	CFont* pFont = pWnd->GetFont();
	ASSERT(pFont);

	//Get the font from our control
    HFONT hfont = (HFONT)pFont->GetSafeHandle();	//    CreateFont(10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");

	//Correction: Do not delete 'hfont'. 
	//            Also 'hMappedFont' needs special delete handling below.
    HFONT hMappedFont = NULL;
	if(!bSurrogatePair)
	{
		hMappedFont = get_font_link(single_codepoint[0], hdc /*memdc*/, hfont, ifont, icodepages);
	}

	AddStatusMsg(L"hMappedFont=0x%p%s\n", hMappedFont, hMappedFont ? L"" : L" (Will use original font)");

	//Correction: Use font only if it was mapped. Otherwise use original font handle!
    AddStatusMsg(L">>> IsTofu for %s <<< = %d\n", single_codepoint, IsTofu(hdc, hMappedFont ? hMappedFont : hfont, single_codepoint));

	CString s;
	pWnd->GetWindowTextW(s);
	s += single_codepoint;
	pWnd->SetWindowTextW(s);

    //::SelectObject(memdc, oldbmp);
    //::DeleteObject(hbitmap);
    //::DeleteDC(memdc);
    ::ReleaseDC(hWnd, hdc);
//    ::DeleteObject(hfont);		//Correction: DO NOT do this!

	//Correction: Need to delete our mapped font in a special way, check MSDN
	if(hMappedFont)
	{
		VERIFY(SUCCEEDED(ifont->ReleaseFont(hMappedFont)));
	}

}

int CTestTofuGuiDlg::isCharWhitespace(WCHAR ch)
{
	//RETURN:
	//		1	= if 'ch' is a whitespace
	//		0		= if 'ch' is not a whitespace
	//		-1	= if error determining (check GetLastError() for info)
	WORD chType = 0;
	if(::GetStringTypeEx(LOCALE_USER_DEFAULT, CT_CTYPE1, &ch, 1, &chType))
	{
		return (chType & C1_SPACE) ? 1 : 0;
	}

	return -1;
}


void CTestTofuGuiDlg::AddStatusMsg(LPCTSTR pszFormat, ...)
{
	CTestTofuGuiDlg* pThis = (CTestTofuGuiDlg*)AfxGetMainWnd();
	if(pThis)
	{
		CString s;
		va_list argList;

		va_start( argList, pszFormat );
		s.FormatV(pszFormat, argList);
		va_end( argList );

		s.Replace(L"\n", L"\r\n");

		CString strTxt;
		pThis->GetDlgItemTextW(IDC_EDIT1, strTxt);
		strTxt += s;
		pThis->SetDlgItemTextW(IDC_EDIT1, strTxt);
	}
	else
		ASSERT(NULL);
}





