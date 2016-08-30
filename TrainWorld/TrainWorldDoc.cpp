
// TrainWorldDoc.cpp : implementation of the CTrainWorldDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TrainWorld.h"
#endif

#include "SystemValues.h"	

#include "StdTrainDef.h" 

#include "TrainWorldDoc.h"
 
#include "MainFrm.h"

//#include "ViewContr.h"

#include "TrainWorldView.h"
#include "ViewContr.h"

#include <propkey.h>


#include "BgrBmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Debug.h"
extern CDebug mDebug;

extern CSystem  mSystem;

// CTrainWorldDoc
#define  _ProjDocument   CTrainWorldDoc 



IMPLEMENT_DYNCREATE(CTrainWorldDoc, CDocument)

BEGIN_MESSAGE_MAP(CTrainWorldDoc, CDocument)
	ON_COMMAND(ID_TOOLS_DEBUG_RAILS, &CTrainWorldDoc::OnToolsDebugRails)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DEBUG_RAILS, &CTrainWorldDoc::OnUpdateToolsDebugRails)
	ON_COMMAND(ID_TOOLS_DEBUG_CLOSE, &CTrainWorldDoc::OnToolsDebugClose)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DEBUG_CLOSE, &CTrainWorldDoc::OnUpdateToolsDebugClose)
	ON_COMMAND(ID_TOOLS_DEBUG_OPEN, &CTrainWorldDoc::OnToolsDebugOpen)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_DEBUG_OPEN, &CTrainWorldDoc::OnUpdateToolsDebugOpen)
	ON_COMMAND(ID_TOOLS_CHECKSWITCHES, &CTrainWorldDoc::OnToolsCheckswitches)
	ON_COMMAND(ID_TOOLS_FIXSWITCHES, &CTrainWorldDoc::OnToolsFixswitches)
	ON_COMMAND(ID_SETUP_TESTMODE, &CTrainWorldDoc::OnSetupTestmode)
	ON_UPDATE_COMMAND_UI(ID_SETUP_TESTMODE, &CTrainWorldDoc::OnUpdateSetupTestmode)
	ON_COMMAND(ID_SETUP_RVISIBLE, &CTrainWorldDoc::OnSetupRvisible)
	ON_UPDATE_COMMAND_UI(ID_SETUP_RVISIBLE, &CTrainWorldDoc::OnUpdateSetupRvisible)
	ON_COMMAND(ID_SETUP_DONOTSAVETRAMS, &CTrainWorldDoc::OnSetupDonotsavetrams)
	ON_COMMAND(ID_SETU_SETLAUNCHRAIL, &CTrainWorldDoc::OnSetuSetlaunchrail)
	ON_UPDATE_COMMAND_UI(ID_SETUP_DONOTSAVETRAMS, &CTrainWorldDoc::OnUpdateSetupDonotsavetrams)
	ON_COMMAND(ID_TOOLS_STAT, &CTrainWorldDoc::OnToolsStat)
	ON_COMMAND(ID_TOOLS_CHECKFLT, &CTrainWorldDoc::OnToolsCheckflt)
	ON_COMMAND(ID_MANAGE_ROUTES, &CTrainWorldDoc::OnManageRoutes)
	ON_COMMAND(ID_DEL_CONTROL, &CTrainWorldDoc::OnDelControl)
	ON_COMMAND(IDM_MANAGE_NAMES, &CTrainWorldDoc::OnManageNames)
	ON_COMMAND(IDM_SYSTEM_SETTINGS, &CTrainWorldDoc::OnSystemSettings)
	ON_COMMAND(IDM_CHECK_STOP, &CTrainWorldDoc::OnCheckStop)
	ON_COMMAND(IDM_CHECK_RAILS, &CTrainWorldDoc::OnCheckRails)
END_MESSAGE_MAP()

//  C:\root\sub\filename.unq  ->  C:\root\sub\

CString StrippedDir(CString Ci)
{
 int v=0,i,l=Ci.GetLength();

 for (i=l;i>0;i--)
     if ( Ci.GetAt(i)=='\\') {v=i;break;}
 if ( v==0) return Ci;
 else return Ci.Left(v+1);
}
// CTrainWorldDoc construction/destruction

CTrainWorldDoc::CTrainWorldDoc()
{
	// TODO: add one-time construction code here
	m_view_hWnd = NULL;
	m_hDIB = NULL;
	m_sizeDoc = CSize(1,1); 
	m_hSmallDIB = NULL;

	char path[160];
	GetModuleFileName( NULL ,path ,158);
    CString Cs = path;
	mCsHomePath = StrippedDir(Cs);

/*
1024x1024 bitmap as fixed  aux
Scale   5   -   32 max blocs     32x32 win size
Scale   6  -    64 max blocks   16x16 win size
Scale   7   - 128 max blocks    8x8   win size
*/


	m_scaledown = SCALE_INTRER;

	SystemDbRead = USE_FORMAT_JPG;
}

CTrainWorldDoc::~CTrainWorldDoc()
{
 
	if (m_hDIB != NULL)
	{::GlobalFree((HGLOBAL) m_hDIB);}
	if (m_hSmallDIB != NULL)
	{::GlobalFree((HGLOBAL) m_hSmallDIB);}

}

#include "TrainObjects.h"
extern  CObjRailsColl  mCObjRailsColl;

#include "RoutesRec.h"
extern CObjTramLine mCObjTramLine;

BOOL CTrainWorldDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	mCObjRailsColl.DeleteAllObjects();
	UpdateAllViews(  NULL , 4 , NULL);

	return TRUE;
}


CTime CTrainWorldDoc::GetSimulationStartTime()
{
  CTime tm( 2014,1,1, 5 ,0,0,0);
  return tm;
}

CTimeSpan CTrainWorldDoc::GetSimulationIncTimeSpan()
{
  CTimeSpan tm_distunit( 0, 0 , 1 , 0 );
  return tm_distunit;
}

// CTrainWorldDoc serialization

extern CObjNames mObjNames;

void CTrainWorldDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		CVersion=_T("TSMv9");
        ar << CVersion;
		
		mSystem.Serialize(  ar) ;
		mCObjRailsColl.Serialize(  ar) ;
	     mCObjTramLine.Serialize(  ar) ;
	 	mObjNames.Serialize(  ar) ;
	}
	else
	{
		mCObjRailsColl.DeleteAllObjects();
		ar >> CVersion;
		
//mDebug.CDebugPut("* Serialize*: "   );

		if ( CVersion ==_T("TSMv9"))
		{
		mSystem.Serialize(  ar) ;
	 	mCObjRailsColl.Serialize(  ar) ;
	  	mCObjTramLine.Serialize(  ar) ;
	  	mObjNames.Serialize(  ar) ;
		}
		else
		{
			CString Cs ; Cs.Format("Tylko wersja :%d bazy danych moze byc uzywana twoja wersja:", (int)9);
			Cs += CVersion;
			AfxMessageBox( Cs );

		}
 
		UpdateAllViews(  NULL , 4 , NULL);

	}
}

void CTrainWorldDoc::OnToolsCheckswitches()
{
	int e =mCObjRailsColl.CheckSwitchesDetails(0);
	CString Cs ; Cs.Format("Checked - Number of errors:%d",e);
	AfxMessageBox( Cs );
}


void CTrainWorldDoc::OnToolsFixswitches()
{
 	int e = mCObjRailsColl.CheckSwitchesDetails(1);
	CString Cs ; Cs.Format("Fixed - Number of errors:%d",e);
	AfxMessageBox( Cs );
}

void CTrainWorldDoc::OnToolsCheckflt()
{
	int e = mCObjRailsColl.CheckSwitchesDetails(3);
	CString Cs ; Cs.Format("Warning - Number of floating rails :%d",e);
	AfxMessageBox( Cs );
}

void CTrainWorldDoc::OnCheckStop()
{
	int e = mCObjRailsColl.CheckStops(1);
	CString Cs ; Cs.Format("Warning - Number of stops error :%d",e);
	AfxMessageBox( Cs );

 	e = mCObjRailsColl.CheckSemaphores(1);
 	Cs.Format("Warning - Number of sem error :%d",e);
 	AfxMessageBox( Cs );
}


void CTrainWorldDoc::OnCheckRails()
{
	int e = mCObjRailsColl.CheckIndexTable();
	CString Cs ; Cs.Format("Warning - Number of index errors :%d",e);
	AfxMessageBox( Cs );
}


#ifdef SHARED_HANDLERS

// Support for thumbnails
void CTrainWorldDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CTrainWorldDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CTrainWorldDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CTrainWorldDoc diagnostics

#ifdef _DEBUG
void CTrainWorldDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTrainWorldDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CTrainWorldDoc::DebugHDC(int id , HDC hdcMem   )
{
	mDebug.CDebugPut((char *)"DebugHDC:%d", id  );
	mDebug.CDebugPut((char *)"HORZSIZE :%d",  GetDeviceCaps(hdcMem , HORZSIZE ) );
	mDebug.CDebugPut((char *)"VERTSIZE :%d",  GetDeviceCaps(hdcMem , VERTSIZE ) );
	mDebug.CDebugPut((char *)"BITSPIXEL :%d",  GetDeviceCaps(hdcMem , BITSPIXEL ) );
	//mDebug.CDebugPut((char *)"VERTSIZE :%d",  GetDeviceCaps(hdcMem , VERTSIZE ) );


}

void CTrainWorldDoc::DebugHDC(int id , CDC *pdc  )
{
	mDebug.CDebugPut((char *)"DebugHDC:%d", id  );
	mDebug.CDebugPut((char *)"HORZSIZE :%d", pdc->GetDeviceCaps( HORZSIZE ) );
	mDebug.CDebugPut((char *)"VERTSIZE :%d", pdc->GetDeviceCaps( VERTSIZE ) );	
 	mDebug.CDebugPut((char *)"BITSPIXEL :%d", pdc->GetDeviceCaps( BITSPIXEL ) );	
	//mDebug.CDebugPut((char *)"VERTSIZE :%d", pdc->GetDeviceCaps( VERTSIZE ) );	
}

void CTrainWorldDoc::DebugCImage(int id , CImage *pim  )
{
	mDebug.CDebugPut((char *)"DebugCImage:%d", id  );
	mDebug.CDebugPut((char *)"GetBPP :%d", pim->GetBPP() );
	mDebug.CDebugPut((char *)"GetHeight :%d", pim->GetHeight() );	
 	mDebug.CDebugPut((char *)"GetWidth :%d", pim->GetWidth() );	


/*
img.GetBPP();
	img.GetDC();
	img.GetHeight();
	img.GetWidth();
	img.
*/

}

// called by view to grab handle
HDIB CTrainWorldDoc::GetHDIB()  
{ return m_hDIB; }

HDIB CTrainWorldDoc::GetAuxHDIB()  
{ return m_hSmallDIB; }

// CTrainWorldDoc commands

void CTrainWorldDoc::Interface_RegisterViewWindow( HWND hWnd )
{ m_view_hWnd = hWnd; }

void CTrainWorldDoc::Interface_RegisterCtrlWindow( HWND hWnd )
{ m_ctrl_hWnd = hWnd; }


void CTrainWorldDoc::Interface_SendMessageToView( int iuser,int ix ,int lp)
{
	if ( m_view_hWnd != NULL )
		::PostMessageA(m_view_hWnd  , WM_USER+iuser , ix  , lp);
}

void CTrainWorldDoc::Interface_SendMessageToCntr(int iuser,int ix,int lp)
{
	if ( m_ctrl_hWnd != NULL )
		::PostMessageA(m_ctrl_hWnd  , WM_USER+iuser , ix  , lp);
}

 
void CTrainWorldDoc::Interface_RegisterActiveView( CView *pv )
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->SetActiveView( pv , TRUE );
}

void CTrainWorldDoc::Interface_UpdateTrainView(  CView *pv, int func , CRect *pr )
{
	CRect rc;

	rc.left = pr->left << m_scaledown;
	rc.top = pr->top << m_scaledown;
 	rc.right = pr->right << m_scaledown;
	rc.bottom = pr->bottom << m_scaledown;

	UpdateAllViews(  pv , func , ( CObject*)&rc );
}

void CTrainWorldDoc::Interface_UpdateControlView(  CView *pv, int func , CRect *pr )
{
	CRect rc;

	rc.left = pr->left >> m_scaledown;
	rc.top = pr->top >> m_scaledown;
 	rc.right = pr->right >> m_scaledown;
	rc.bottom = pr->bottom >> m_scaledown;

	UpdateAllViews(  pv , func , ( CObject*)&rc );
}


CBgrBmp mCBgrBmp;

void CTrainWorldDoc::Interface_SetupDataBase(  HDC  *hdcTmpMem )  
{
    sBgrBmpInit  mBgrBmpInit;
	mBgrBmpInit.pDoc =this;
	mBgrBmpInit.p = hdcTmpMem;
	mCBgrBmp.CBgrBmpInit( &mBgrBmpInit );
}
 
BOOL CTrainWorldDoc::Interface_UpdateShadowImage( HDC hdcMem , int des_off_x, int des_off_y , CRect rc   ) 
{
	mCBgrBmp.CBgrBmpUpdateAreas( &hdcMem , des_off_x,des_off_y , rc   );
	return FALSE;
}

/*
BOOL CTrainWorldDoc::Interface_UpdateScrolledAreas( HDC hdcMem   , CRect rc ,int dx,int dy)  
{
	CRect std(0,0,1024,1024);
    CRect rc1;

	//ScrollDC ( hdcMem, dx,dy ,NULL , NULL ,NULL , &rc  );
	return FALSE;
}
 */


void CTrainWorldDoc::OnToolsDebugRails()
{
			mCObjRailsColl.DebugRailList();
}

void CTrainWorldDoc::OnUpdateToolsDebugRails(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  mDebug.CDebugIsOpen()  == TRUE  );
}

void CTrainWorldDoc::OnToolsDebugClose()
{
 
	 mDebug.CDebugClose();
}

void CTrainWorldDoc::OnUpdateToolsDebugClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  mDebug.CDebugIsOpen()  == TRUE  );
}

void CTrainWorldDoc::OnToolsDebugOpen()
{
	 mDebug.CDebugOpen();
}

void CTrainWorldDoc::OnUpdateToolsDebugOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  mDebug.CDebugIsOpen()  == FALSE  );
}


void CTrainWorldDoc::OnSetupTestmode()
{
  
	if ( mSystem.m_SimTestMode == TRUE) mSystem.m_SimTestMode = FALSE;
	else mSystem.m_SimTestMode = TRUE;
	
	UpdateAllViews(  NULL , 4 , NULL);
}


void CTrainWorldDoc::OnUpdateSetupTestmode(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( mSystem.m_SimTestMode == TRUE );
}


void CTrainWorldDoc::OnSetupRvisible()
{
	if (  mSystem.m_SimShowRail == FALSE ) mSystem.m_SimShowRail =  TRUE;
	else mSystem.m_SimShowRail =  FALSE;

	UpdateAllViews(  NULL , 4 , NULL);
}


void CTrainWorldDoc::OnUpdateSetupRvisible(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( mSystem.m_SimShowRail == TRUE  );
}


void CTrainWorldDoc::OnSetupDonotsavetrams()
{
	// TODO: Add your command handler code here
	if (  mSystem.m_SaveTrams == FALSE ) mSystem.m_SaveTrams =  TRUE;
	else mSystem.m_SaveTrams =  FALSE;
}

void CTrainWorldDoc::OnUpdateSetupDonotsavetrams(CCmdUI *pCmdUI)
{
		pCmdUI->SetCheck( mSystem.m_SaveTrams ==  FALSE  );
}

#include "EnterID.h"
void CTrainWorldDoc::OnSetuSetlaunchrail()
{
	CEnterID  dlg;
	dlg.m_ID_Selected = mSystem.m_LaunchRail;
	if ( dlg.DoModal() == IDOK )
	{
		mSystem.m_LaunchRail  = dlg.m_ID_Selected ;
	}
}




void CTrainWorldDoc::OnToolsStat()
{
	mCObjRailsColl.Resources() ;
}


 
#include "RoutesRec.h"

void CTrainWorldDoc::OnManageRoutes()
{
	CRoutesRec dlg;
	dlg.DoModal();

}


void CTrainWorldDoc::OnDelControl()
{
	CEnterID  dlg;
	dlg.m_ID_Selected = 1;
	if ( dlg.DoModal() == IDOK )
	{
		int mId  = dlg.m_ID_Selected ;
		mCObjRailsColl.DeleteControlById(mId );
	} 
}

#include "Names.h"

void CTrainWorldDoc::OnManageNames()
{
	CNames dlg;
	dlg.DoModal();
}

#include "SystemSettings.h"

void CTrainWorldDoc::OnSystemSettings()
{
	CSystemSettings dlg;
	dlg.DoModal();
	
	UpdateAllViews(  NULL , 4 , NULL);
}
