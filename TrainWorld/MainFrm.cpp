
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "MainFrm.h"
 
#include "TrainWorldDoc.h"
#include "TrainWorldView.h"
#include "ViewContr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame




IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
END_MESSAGE_MAP()
/*
static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};
*/

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_SEPARATOR,  
	ID_SEPARATOR,   
	ID_SEPARATOR,
	ID_SEPARATOR 
	//ID_INDICATOR_1  - predefined in RC as color indicator 
};




// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	 
	   // !!! need to be AFX_IDW_TOOLBAR+1  othervise interfere with 'standard\ bar
	if (!m_wndEditBar.Create(this,  WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS | CBRS_FLYBY  ,AFX_IDW_TOOLBAR+1 ) ||
		!m_wndEditBar.LoadToolBar( IDR_MAINFRAME_EDIT_256  ))
	{
		//TRACE0("Failed to create toolbar\n");  IDS_TOOLBAR_TRAINS
		//mDebug.CDebugPut("Failed to create toolbar 2 \n");
		return -1;      // fail to create
	}
 	 
	//must be specified in resource file    ID_SEL_POINT   "Select point or section\nPoint"

	m_wndEditBar.SetShowTooltips(TRUE);
 
 
	   // !!! need to be AFX_IDW_TOOLBAR+1  othervise interfere with 'standard\ bar
	if (!m_wndCntBar.CreateEx(this,  WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS | CBRS_FLYBY  ,AFX_IDW_TOOLBAR+2 ) ||
		!m_wndCntBar.LoadToolBar( IDR_MAINFRAME_CNTR_256  ))
	{
		//TRACE0("Failed to create toolbar\n");  IDS_TOOLBAR_TRAINS
		//mDebug.CDebugPut("Failed to create toolbar 2 \n");
		return -1;      // fail to create
	}


	   // !!! need to be AFX_IDW_TOOLBAR+1  othervise interfere with 'standard\ bar
	if (!m_wndRunBar.Create(this,  WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS | CBRS_FLYBY  ,AFX_IDW_TOOLBAR+3 ) ||
		!m_wndRunBar.LoadToolBar( IDR_MAINFRAME_RUN_256  ))
	{
		//TRACE0("Failed to create toolbar\n");  IDS_TOOLBAR_TRAINS
		//mDebug.CDebugPut("Failed to create toolbar 2 \n");
		return -1;      // fail to create
	}
 

	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	/*
		if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");	
		return -1;      // fail to create
	}
	*/

	 m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

m_wndStatusBar.SetPaneInfo(  0, ID_SEPARATOR,  SBPS_NORMAL,  320 ); 
     m_wndStatusBar.SetPaneInfo(  1, ID_SEPARATOR , SBPS_NORMAL  ,  320 ); 
     m_wndStatusBar.SetPaneInfo(  2, ID_SEPARATOR, SBPS_NORMAL , 48 ); 		 
     m_wndStatusBar.SetPaneInfo(  3, ID_SEPARATOR,  SBPS_NORMAL  ,  64 ); 	
     m_wndStatusBar.SetPaneInfo(  4, ID_SEPARATOR ,  SBPS_NORMAL  ,  96 ); 


	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndEditBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndCntBar.EnableDocking(CBRS_ALIGN_TOP);
	m_wndRunBar.EnableDocking(CBRS_ALIGN_TOP);

	EnableDocking(CBRS_ALIGN_TOP);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	DockPane(&m_wndEditBar);
	DockPane(&m_wndCntBar);
	DockPane(&m_wndEditBar);
	DockPane(&m_wndRunBar);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == NULL)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{

	 // create a splitter with 1 row, 2 columns
		if (!m_wndSplitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}
	 
	if (!m_wndSplitter.CreateView(0, 0,
		 RUNTIME_CLASS(CViewContr),
		CSize(512, 500), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	} 

	if (!m_wndSplitter.CreateView(0, 1,
		 RUNTIME_CLASS(CTrainWorldView),
		CSize(1024, 1024), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}  

	return TRUE;
	 
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


// CMainFrame message handlers

void CMainFrame::DisplayPanel(  int panel ,CString Cs  )
{
 
	m_wndStatusBar.SetPaneText(  panel , Cs );
}



 
void CMainFrame::DisplayPanelColor(  int panel ,CString Cs , COLORREF cr_text ,COLORREF cr_bgr  )
{
   
	CRect rect;

	CClientDC dc(&m_wndStatusBar);

	m_wndStatusBar.GetItemRect( panel , &rect ); 
	 

    LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfHeight = 14;  //  3/4th inch high in MM_LOENGLISH	
	logFont.lfWeight =4;
	strcpy_s(logFont.lfFaceName,14, "Courier");    //    with face name "Arial".
	CFont font;
	CFont* pOldFont = NULL;
	if (font.CreateFontIndirect(&logFont))   pOldFont = dc.SelectObject(&font);


	rect.DeflateRect(2,2);

	dc.FillSolidRect( &rect , cr_bgr);
	dc.SetTextColor(cr_text);
 
	dc.TextOut( rect.left+4   ,rect.top-2  ,  Cs, Cs.GetLength() );
  
	if (pOldFont != NULL) dc.SelectObject(pOldFont);
 

 	// m_wndStatusBar.SetPaneText(  panel , Cs );
 
}
 


void CMainFrame::DisplayPanelColour(  COLORREF cr )
{
  CRect rect;
  m_wndStatusBar.GetItemRect( 2 , &rect ); 
  CDC *cdc = m_wndStatusBar.GetWindowDC();
  rect.DeflateRect(2,2);
  cdc->FillSolidRect( &rect ,cr  );
}

 void CMainFrame::PaintSimulationTime( CTime tm )
 {
	CRect rect;

	CClientDC dc(&m_wndStatusBar);
	m_wndStatusBar.GetItemRect(4,&rect);

	LOGFONT logFont;
	memset(&logFont, 0, sizeof(LOGFONT));
	logFont.lfHeight = 16;  //  3/4th inch high in MM_LOENGLISH	
	logFont.lfWeight =4;
	strcpy_s(logFont.lfFaceName,16, "Courier");    //    with face name "Arial".
	CFont font;
	CFont* pOldFont = NULL;
	if (font.CreateFontIndirect(&logFont))   pOldFont = dc.SelectObject(&font);

	dc.FillSolidRect( &rect , RGB( 0, 0, 0));
	dc.SetTextColor(RGB( 255,0,0));
	CString Cs;
	Cs.Format("%02d:%02d:%02d", tm.GetDay(),tm.GetHour(),tm.GetMinute());
	dc.TextOut( rect.left+20   ,rect.top  ,  Cs, Cs.GetLength() );
  
	if (pOldFont != NULL) dc.SelectObject(pOldFont);

	mMinTicks = 60*tm.GetHour() + tm.GetMinute();  /// nEW

 }

  int CMainFrame::GetSimulationTime( )
 {
	 return mMinTicks;
 }
