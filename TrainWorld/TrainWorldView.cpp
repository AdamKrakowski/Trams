
// TrainWorldView.cpp : implementation of the CTrainWorldView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TrainWorld.h"
#endif

#include "SystemValues.h"	

#include "StdTrainDef.h" 
#include "TrainObjects.h"

#include "TrainWorldDoc.h"
#include "TrainWorldView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Debug.h"
extern CDebug mDebug;
 
#include "DrawTmpObject.h"
CTempVector mCTempVector ;


#include "SelTram.h"

 
extern CObjRailsColl  mCObjRailsColl;
extern DWORD  dwVisible ; 

#include "WinTextPop.h"
extern CWinTextPopUp mWinTextPopUp;

extern CSystem  mSystem;


// graphics debug 
//	CRect testRect;
//	int   testRectEnable;

 
extern CDebugGraphics mCDebugGraphics;

CToolTipCtrl mCToolTipCtrl; 

// CTrainWorldView

IMPLEMENT_DYNCREATE(CTrainWorldView, CView)

BEGIN_MESSAGE_MAP(CTrainWorldView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTrainWorldView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDITTERAIN_ADDSTRIGHT, &CTrainWorldView::OnEditterainAddstright)
	ON_UPDATE_COMMAND_UI(ID_EDITTERAIN_ADDSTRIGHT, &CTrainWorldView::OnUpdateEditterainAddstright)
	ON_COMMAND(ID_EDITTERAIN_ADDBENDRIGH, &CTrainWorldView::OnEditterainAddbend)
	ON_UPDATE_COMMAND_UI(ID_EDITTERAIN_ADDBENDRIGH, &CTrainWorldView::OnUpdateEditterainAddbend)
	ON_COMMAND(ID_SEL_POINT, &CTrainWorldView::OnSelPoint)
	ON_UPDATE_COMMAND_UI(ID_SEL_POINT, &CTrainWorldView::OnUpdateSelPoint)
	ON_COMMAND(ID_SEL_RECT, &CTrainWorldView::OnSelRect)
	ON_UPDATE_COMMAND_UI(ID_SEL_RECT, &CTrainWorldView::OnUpdateSelRect)
	ON_COMMAND(ID_TRACK_MOVE, &CTrainWorldView::OnTrackMove)
	ON_UPDATE_COMMAND_UI(ID_TRACK_MOVE, &CTrainWorldView::OnUpdateTrackMove)
	ON_COMMAND(ID_TRACK_DEL, &CTrainWorldView::OnTrackDel)
	ON_UPDATE_COMMAND_UI(ID_TRACK_DEL, &CTrainWorldView::OnUpdateTrackDel)
	ON_COMMAND(ID_TRACKS_SNAP, &CTrainWorldView::OnTracksSnap)
	ON_UPDATE_COMMAND_UI(ID_TRACKS_SNAP, &CTrainWorldView::OnUpdateTracksSnap)
	ON_COMMAND(ID_TRACK_DEL_SEL, &CTrainWorldView::OnTrackDelSel)
	ON_UPDATE_COMMAND_UI(ID_TRACK_DEL_SEL, &CTrainWorldView::OnUpdateTrackDelSel)
	ON_COMMAND(ID_TRACK_SHOW, &CTrainWorldView::OnTrackShow)
	ON_UPDATE_COMMAND_UI(ID_TRACK_SHOW, &CTrainWorldView::OnUpdateTrackShow)
	ON_COMMAND(ID_TRACK_SHOW_CONN, &CTrainWorldView::OnTrackShowConn)
	ON_UPDATE_COMMAND_UI(ID_TRACK_SHOW_CONN, &CTrainWorldView::OnUpdateTrackShowConn)
	ON_COMMAND(ID_EDITTERAIN_ADDTERMINATOR, &CTrainWorldView::OnEditterainAddterminator)
	ON_UPDATE_COMMAND_UI(ID_EDITTERAIN_ADDTERMINATOR, &CTrainWorldView::OnUpdateEditterainAddterminator)
	ON_COMMAND(ID_EDITTERAIN_DBL_STRIGHT, &CTrainWorldView::OnEditterainDblStright)
	ON_UPDATE_COMMAND_UI(ID_EDITTERAIN_DBL_STRIGHT, &CTrainWorldView::OnUpdateEditterainDblStright)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_MODE_RUN, &CTrainWorldView::OnModeRun)
	ON_UPDATE_COMMAND_UI(ID_MODE_RUN, &CTrainWorldView::OnUpdateModeRun)
	ON_COMMAND(ID_MODE_EDIT_INF, &CTrainWorldView::OnModeEditInf)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDIT_INF, &CTrainWorldView::OnUpdateModeEditInf)
	ON_COMMAND(ID_TOOLS_CNVBMPTOJPG, &CTrainWorldView::OnToolsCnvbmptojpg)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CNVBMPTOJPG, &CTrainWorldView::OnUpdateToolsCnvbmptojpg)
	ON_COMMAND(ID_MODE_EDIT_TRAINS, &CTrainWorldView::OnModeEditTrains)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDIT_TRAINS, &CTrainWorldView::OnUpdateModeEditTrains)
	ON_COMMAND(ID_EDITTERAIN_ADDBENDLEFT, &CTrainWorldView::OnEditterainAddbendleft)
	ON_UPDATE_COMMAND_UI(ID_EDITTERAIN_ADDBENDLEFT, &CTrainWorldView::OnUpdateEditterainAddbendleft)
	ON_UPDATE_COMMAND_UI(ID_RUN_START, &CTrainWorldView::OnUpdateRunStart)
	ON_COMMAND(ID_RUN_START, &CTrainWorldView::OnRunStart)
	ON_UPDATE_COMMAND_UI(ID_RUN_STOP, &CTrainWorldView::OnUpdateRunStop)
	ON_COMMAND(ID_RUN_STOP, &CTrainWorldView::OnRunStop)
	ON_UPDATE_COMMAND_UI(ID_RUN_STEP, &CTrainWorldView::OnUpdateRunStep)
	ON_COMMAND(ID_RUN_STEP, &CTrainWorldView::OnRunStep)
	ON_UPDATE_COMMAND_UI(ID_RUN_REVERS, &CTrainWorldView::OnUpdateRunRevers)
	ON_COMMAND(ID_RUN_REVERS, &CTrainWorldView::OnRunRevers)
	ON_UPDATE_COMMAND_UI(ID_ADD_TRAM, &CTrainWorldView::OnUpdateAddTram)
	ON_COMMAND(ID_ADD_TRAM, &CTrainWorldView::OnAddTram)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO_RAIL, &CTrainWorldView::OnUpdateEditUndoRail)
	ON_COMMAND(ID_EDIT_UNDO_RAIL, &CTrainWorldView::OnEditUndoRail)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO_CTRL, &CTrainWorldView::OnUpdateEditUndoCtrl)
	ON_COMMAND(ID_EDIT_UNDO_CTRL, &CTrainWorldView::OnEditUndoCtrl)
	ON_COMMAND(ID_ADD_SEM, &CTrainWorldView::OnAddSem)
	ON_UPDATE_COMMAND_UI(ID_ADD_SEM, &CTrainWorldView::OnUpdateAddSem)
	ON_COMMAND(ADD_CONT_GROUP, &CTrainWorldView::OnContGroup)
	ON_UPDATE_COMMAND_UI(ADD_CONT_GROUP, &CTrainWorldView::OnUpdateContGroup)
	ON_UPDATE_COMMAND_UI(ID_TRACK_FIND, &CTrainWorldView::OnUpdateTrackFind)
	ON_COMMAND(ID_TRACK_FIND, &CTrainWorldView::OnTrackFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDOTRAM, &CTrainWorldView::OnUpdateEditUndotram)
	ON_COMMAND(ID_EDIT_UNDOTRAM, &CTrainWorldView::OnEditUndotram)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDOCONTROLGROUP, &CTrainWorldView::OnUpdateEditUndocontrolgroup)
	ON_COMMAND(ID_EDIT_UNDOCONTROLGROUP, &CTrainWorldView::OnEditUndocontrolgroup)
	ON_UPDATE_COMMAND_UI(ID_ADD_STOP_GRP, &CTrainWorldView::OnUpdateAddStopGrp)
	ON_COMMAND(ID_ADD_STOP_GRP, &CTrainWorldView::OnAddStopGrp)
	ON_COMMAND(ID_TRAMS_CONTROL, &CTrainWorldView::OnTramsControlCenter)
	ON_WM_CREATE()
 	ON_COMMAND(ID_FIND_TRACK, &CTrainWorldView::OnFindTrack)
	ON_COMMAND(ID_FIND_STOP, &CTrainWorldView::OnFindStop)
	ON_COMMAND(ID_FIND_ENDSTOPBYNAME, &CTrainWorldView::OnFindEndstopbyname)
	ON_COMMAND(ID_RUN_STOPFIND, &CTrainWorldView::OnRunStopfind)
END_MESSAGE_MAP()

// CTrainWorldView construction/destruction

CTrainWorldView::CTrainWorldView()
{
	// TODO: add construction code here
	iSelect = 0;
	iAddMode = 0;
	iModeOper = MODE_NONE;

	MouseStatePressed = FALSE;
	//CPoint Last_Point_DC; 

	TotalSpaceEndPoint.x =PIXEL_BLOCK*BLOCKS_IN_ROW;
	TotalSpaceEndPoint.y =PIXEL_BLOCK*BLOCKS_IN_COL;

	BmpSizeWindow.left  = BmpSizeWindow.top = 0;
	BmpSizeWindow.right =  WIN_X  ;
	BmpSizeWindow.bottom = 	WIN_Y  ;

	IsBitmap = FALSE;
	bActiveObjects = FALSE;

 
	//testRectEnable = FALSE;

	m_divider20 = 1000;
}

CTrainWorldView::~CTrainWorldView()
{
	DeleteObject(bitmap);
	DeleteDC(hdcMem);

}

BOOL CTrainWorldView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}



int CTrainWorldView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CTrainWorldView::OnSize(UINT nType, int cx, int cy)
{
	//CView::OnSize(nType, cx, cy);

	current_size_x = cx;
	current_size_y = cy;

 	if ( IsBitmap == TRUE )
	{
		CTrainWorldDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc) return  ;

		BmpSizeWindow.right  = BmpSizeWindow.left + current_size_x;
		BmpSizeWindow.bottom = BmpSizeWindow.top + current_size_y;
		pDoc->Interface_UpdateControlView( this, 2 , &BmpSizeWindow );
	 	ReloadMemoryBitmap( NULL );  // PROBLEM
	}

	// TODO: Add your message handler code here
}

void CTrainWorldView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	mWinTextPopUp.OpenWinPopUpTool(this);

	//CSize sizeTotal;
	// TODO: calculate the total size of this view
	//sizeTotal.cx = sizeTotal.cy = 1024;
	// SetScrollSizes(MM_TEXT, sizeTotal);

	CTrainWorldDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc) return  ;

	BmpSizeWindow.left  = BmpSizeWindow.top = 0;

	BmpSizeWindow.right  = BmpSizeWindow.left + current_size_x;
	BmpSizeWindow.bottom = BmpSizeWindow.top + current_size_y;
	pDoc->Interface_UpdateControlView( this, 2 , &BmpSizeWindow );
	pDoc->Interface_RegisterActiveView( this );

	//	mCDebugGraphics.EnableGraphics( TRUE);
	//mCDebugGraphics.ResetStorage();

}
 
void CTrainWorldView::OnUpdate(CView*  pSender , LPARAM  lHint , CObject*  pHint )
{
	if ( lHint == 3)
	{
		CRect *p = (CRect *)pHint;
		if ( IsBitmap == TRUE )
		{
			BmpSizeWindow.left = p->left  ;
			BmpSizeWindow.top = p->top  ;
			ReloadMemoryBitmap( NULL  );
			InvalidateRect( FALSE);
			return ;
		}
	//  mDebug.CDebugPut((char *)" Update2 (%d,%d)(%d,%d) " , p->left,p->top,p->right,p->bottom  );
	}
	else if ( lHint == 4) InvalidateRect( FALSE);


}

 

void CTrainWorldView::ReloadMemoryBitmap( CRect *rc )
{
	CTrainWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return ;

	CRect ext ; //  = BmpSizeWindow;
	
	ext.left = BmpSizeWindow.left;
	ext.top	 = BmpSizeWindow.top;

	// tune the rectangle for smaller scroll window
	if (  current_size_x  < WIN_X )	ext.right  = ext.left + current_size_x ;
	else ext.right = ext.left + WIN_X;
	if (  current_size_y  < WIN_Y )	ext.bottom  = ext.top + current_size_y ;
	else ext.bottom = ext.top + WIN_Y;

	// update the base window indicated by left upper corner
	pDoc->Interface_UpdateShadowImage(   hdcMem , 0,0 ,  ext   ) ;
 
	// for bigger sizes the 1024x1024 ( WIN_X x WIN_Y )
	if ( current_size_x  > WIN_X )
		{

		 	CRect rext;
			rext.left	= BmpSizeWindow.left + WIN_X ;
			rext.right  = rext.left + current_size_x - WIN_X ;
			rext.top	= BmpSizeWindow.top;
			rext.bottom = rext.top  + WIN_Y;
			// update right quadrant
			pDoc->Interface_UpdateShadowImage( hdcMem  , WIN_X ,0 , rext );

			if ( current_size_y  > WIN_Y )
			{
				rext.top += WIN_Y ;
				rext.bottom = rext.top + current_size_y - WIN_Y;
				// update right bottom quadrant
				pDoc->Interface_UpdateShadowImage( hdcMem  ,WIN_X ,WIN_Y , rext   );
			}
			 
		}

 
	if ( current_size_y  > WIN_Y )
			{
			 	CRect rext ;  
				rext.left = BmpSizeWindow.left;
				rext.right = rext.left + WIN_X;
				rext.top  = BmpSizeWindow.top + WIN_Y;
				rext.bottom = rext.top + current_size_y ;
				// update left bottom quadrant
				pDoc->Interface_UpdateShadowImage( hdcMem  ,0, WIN_Y, rext   );
			}
 
}





// CTrainWorldView drawing
 


void CTrainWorldView::OnDraw(CDC* pDC)
{


	if (pDC->IsPrinting())  return;

    if ( IsBitmap == FALSE )
	{
		int i;
		for (i=0;i<NBR_OF_BUFFERS;i++)
		{
 			hdcTmpMem[i] = CreateCompatibleDC(pDC->m_hDC);     
			bitTmpmap[i] = CreateCompatibleBitmap(pDC->m_hDC, WIN_X_BITMAP, WIN_Y_BITMAP );     // memory bitmap
			SelectObject(hdcTmpMem[i], bitTmpmap[i]);		
		}

 		hdcMemTmp = CreateCompatibleDC(pDC->m_hDC);     
		bitmapTmp = CreateCompatibleBitmap(pDC->m_hDC, WIN_X_BITMAP, WIN_Y_BITMAP );     // memory bitmap
		SelectObject(hdcMemTmp, bitmapTmp);	


 		CTrainWorldDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc) return  ;

		pDoc->Interface_SetupDataBase( hdcTmpMem );

				// double buffer
		//hdcMemDbl = CreateCompatibleDC(pDC->m_hDC); 
		//bitmapDbl = CreateCompatibleBitmap(pDC->m_hDC, WIN_X_BITMAP, WIN_Y_BITMAP ); // should cover HD  2048x1200  - need to check the client area !!!
		//SelectObject( hdcMemDbl, bitmapDbl);

		hdcMem = CreateCompatibleDC(pDC->m_hDC); 
		bitmap = CreateCompatibleBitmap(pDC->m_hDC, WIN_X_BITMAP, WIN_Y_BITMAP ); // should cover HD  2048x1200  - need to check the client area !!!
		SelectObject(hdcMem, bitmap);
		IsBitmap = TRUE;
		// now load mem bitamp with DIBS

		//ReloadMemoryBitmap( );

	}
	// always reload it
	ReloadMemoryBitmap( NULL );

//	BitBlt( hdcMemDbl , 0,  0, current_size_x, current_size_y , hdcMem,  0,  0 , SRCCOPY);	
 
	CRect ViewRect(0,0,current_size_x,current_size_y);

	if (  mSystem.m_SimShowRail == TRUE )
		mCObjRailsColl.DrawMyObject( BmpSizeWindow.TopLeft(), hdcMem , ViewRect ) ;

	mCObjRailsColl.DrawMyObjects( BmpSizeWindow.TopLeft(), hdcMem , ViewRect ) ;
	mCObjRailsColl.DrawTrams(  BmpSizeWindow.TopLeft(), hdcMem , ViewRect);
 

	if ( MouseStatePressed == TRUE )
	{
		if ( iModeOper == MODE_ADD_OBJECT  )
			mCTempVector.CTempVectorPaintTmpObject( BmpSizeWindow.TopLeft()  , hdcMem );

		if ( iModeOper == MODE_EDIT_OBJECT )
			if ( iSelect == SELECT_RECT)
				mCTempVector.CTempVectorPaintTmpObject( BmpSizeWindow.TopLeft() ,hdcMem );

	}
 
	if ( mCDebugGraphics.IsGraphicsEnabled() == TRUE) 
				mCDebugGraphics.Draw(  hdcMem ,  BmpSizeWindow.TopLeft() ,ViewRect);


	 BitBlt(pDC->m_hDC, 0,  0, current_size_x, current_size_y , hdcMem ,  0,  0 , SRCCOPY);
	 
	 if ( iSelect == SELECT_RECT)
				OnDrawTracker( pDC->m_hDC);



        // pDC->GetClipBox(&r);
		//	mDebug.CDebugPut((char *)"Draw  %d %d %d %d ",r.left,r.top,r.right, r.bottom );

	// TODO: add draw code for native data here
}

void CTrainWorldView::OnToolsCnvbmptojpg()
{
	CTrainWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return  ;

	//pDoc->BMPtoJPGConverstion( hdcMem ,  bitmap );
	pDoc->Tool_BMPtoJPGConverstion( hdcMemTmp ,  bitmapTmp ); // MUST 1024x1024  fit into 
}


void CTrainWorldView::OnUpdateToolsCnvbmptojpg(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  TRUE   );
}


void CTrainWorldView::OnDrawTracker( HDC hdc)
{
	int xw = 0;
	if (  iModeOper == MODE_EDIT_OBJECT ) xw = 1;
	if (  (iModeOper == MODE_ADD_OBJECT)  && (   (iAddMode == ADDMODE_CONT_GRP) || ( iAddMode == ADDMODE_STOP_GRP) ) ) xw = 1;

	if (  xw == 1 )
	{
		if ( MouseStatePressed == TRUE )  
			{
			CRect rc1 =  CRect ( mCTempVector.CTempVectorGetPoint(0) , mCTempVector.CTempVectorGetPoint(1));
			rc1.NormalizeRect(); 
			DrawFocusRect(hdc, &rc1 );   // WIN32 function
			}
	}
}



void CTrainWorldView::OnDrawBgn(   HDC hdc )
{
//  create solid window background - Green
    CRect  clientRect;
	HRGN bgRgn;
    HBRUSH hBrush;
 

	clientRect.left =0;
	clientRect.top =0;
	clientRect.right = 32;
	clientRect.bottom = 32;

    bgRgn = CreateRectRgnIndirect(&clientRect);

	if ( bgRgn == NULL ) 
	{
		//SystemErrorMessage( 2 );
		return;
	}

    hBrush = CreateSolidBrush(RGB( 0 , 200, 0));

	if ( hBrush == NULL ) 
	{
		//SystemErrorMessage( 2 );
		return;
	}

    FillRgn(hdc, bgRgn, hBrush);

	DeleteObject( bgRgn );
	DeleteObject( hBrush );
	GetStockObject(WHITE_BRUSH);
}

// CTrainWorldView printing


void CTrainWorldView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTrainWorldView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTrainWorldView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTrainWorldView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTrainWorldView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTrainWorldView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTrainWorldView diagnostics

#ifdef _DEBUG
void CTrainWorldView::AssertValid() const
{
	CView::AssertValid();
}

void CTrainWorldView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrainWorldDoc* CTrainWorldView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrainWorldDoc)));
	return (CTrainWorldDoc*)m_pDocument;
}
#endif //_DEBUG


BOOL CTrainWorldView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if ( WM_USER == message)  // this message is to send block number from control window
	{
  
		return TRUE;
	}

	return CView::OnWndMsg(message, wParam, lParam, pResult);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Operatio mode: MODE_RUN,MODE_ADD_OBJECT,MODE_EDIT_OBJECT
//
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void CTrainWorldView::OnModeRun()
{
	iModeOper = MODE_RUN; 
	if ( mCObjRailsColl.ClearSelected() == TRUE ) Invalidate(FALSE);
		bActiveObjects = FALSE;
}

void CTrainWorldView::OnUpdateModeRun(CCmdUI *pCmdUI)
{
	 pCmdUI->SetCheck( iModeOper == MODE_RUN ); 
}

void CTrainWorldView::OnModeEditInf()
{
	iModeOper = MODE_ADD_OBJECT;
	if ( mCObjRailsColl.ClearSelected() == TRUE ) Invalidate(FALSE);
	bActiveObjects = FALSE;
}

void CTrainWorldView::OnUpdateModeEditInf(CCmdUI *pCmdUI)
{
	 pCmdUI->SetCheck( iModeOper == MODE_ADD_OBJECT ); 
}

void CTrainWorldView::OnModeEditTrains()
{
	 iModeOper =  MODE_EDIT_OBJECT  ; 
}

void CTrainWorldView::OnUpdateModeEditTrains(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( iModeOper == MODE_EDIT_OBJECT ); 
}


void CTrainWorldView::OnTramsControlCenter()
{
	OnTramsControl( 0 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// ADD handlers
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTrainWorldView::OnEditterainAddstright()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_STRIGHT;
	mCTempVector.CTempVectorSetTmpObject( ObjStraightRail );
}

void CTrainWorldView::OnUpdateEditterainAddstright(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
	pCmdUI->SetCheck(  iModeOper == ADDMODE_STRIGHT );
}

void CTrainWorldView::OnEditterainAddbend()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_BEND_RIGHT;
	mCTempVector.CTempVectorSetTmpObject( ObjBendRightRail );
}

void CTrainWorldView::OnUpdateEditterainAddbend(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
	pCmdUI->SetCheck( iAddMode == ADDMODE_BEND_RIGHT  );
}

void CTrainWorldView::OnEditterainAddbendleft()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_BEND_LEFT;
	mCTempVector.CTempVectorSetTmpObject( ObjBendLeftRail );
}

void CTrainWorldView::OnUpdateEditterainAddbendleft(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
	pCmdUI->SetCheck( iAddMode == ADDMODE_BEND_LEFT  );
}

void CTrainWorldView::OnEditterainAddterminator()
{
		iSelect = SELECT_NONE;
		iAddMode = ADDMODE_TERMINATOR;
		mCTempVector.CTempVectorSetTmpObject( ObjRailEnd );
 
}

void CTrainWorldView::OnUpdateEditterainAddterminator(CCmdUI *pCmdUI)
{
			//pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
	 	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );	
	 pCmdUI->SetCheck( iAddMode == ADDMODE_TERMINATOR  );
}

void CTrainWorldView::OnEditterainDblStright()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_DB_STRIGHT;
	mCTempVector.CTempVectorSetTmpObject( ObjStraightDblRail );
}

void CTrainWorldView::OnUpdateEditterainDblStright(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
	pCmdUI->SetCheck( iAddMode == ADDMODE_DB_STRIGHT  );
}

void CTrainWorldView::OnUpdateAddTram(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
}

void CTrainWorldView::OnAddTram()
{
//	if ( pv != NULL) return ;

	CSelTram  dlg;
	if ( dlg.DoModal() == IDOK )
	{
		int sel;
		if ( (sel = dlg.GetSelectedTramId()) != 0 )
		{

		    CTramModelDef mModel[6];
			int modules = dlg.GetShape( mModel );

			//mDebug.CDebugPut((char *)" Shapes (%d  " , modules );

			mCObjRailsColl.AddObjectTram(  mModel  , modules , dlg.mLineId);

			OnTramsControl(0);

			Invalidate(FALSE);
		}
	}

}


void CTrainWorldView::OnUpdateEditUndoRail(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
}


void CTrainWorldView::OnEditUndoRail()
{
 
	mCObjRailsColl.RemoveLastRail();
	Invalidate(FALSE);
}


void CTrainWorldView::OnUpdateEditUndoCtrl(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
}


void CTrainWorldView::OnEditUndoCtrl()
{
	mCObjRailsColl.RemoveLastControl();
	Invalidate(FALSE);
}

void CTrainWorldView::OnUpdateEditUndotram(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  mCObjRailsColl.GetNumberOfTrams() > 0 );
}


void CTrainWorldView::OnEditUndotram()
{
	mCObjRailsColl.RemoveLastTram();
	Invalidate(FALSE);
}



void CTrainWorldView::OnUpdateEditUndocontrolgroup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  mCObjRailsColl.GetNumberOfControlGroup() > 0 );
}


void CTrainWorldView::OnEditUndocontrolgroup()
{
	mCObjRailsColl.RemoveLastContrGroup();
}

void CTrainWorldView::OnUpdateTrackFind(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

#include "EnterID.h"
void CTrainWorldView::OnTrackFind()
{
	// TODO: Add your command handler code here

	CEnterID  dlg;
	dlg.m_ID_Selected = 0;
	if ( dlg.DoModal() == IDOK )
	{
		// m_ID_Selected
		CObjRail   *p =  mCObjRailsColl.FindObjectById( dlg.m_ID_Selected ) ;
		if ( p != NULL )
			MoveWindowToTheObject(  (int)p->GetPoint(0).x  , (int)p->GetPoint(0).y   );
	}
}

void CTrainWorldView::OnFindTrack()
{
	OnTrackFind();
}


void CTrainWorldView::OnFindStop()
{
	CEnterID  dlg;
	dlg.m_ID_Selected = 0;
	if ( dlg.DoModal() == IDOK )
	{
		// m_ID_Selected
		CObjControls   *p =  mCObjRailsColl.FindControlObject( dlg.m_ID_Selected ) ;
		if ( p != NULL )
		{
			CPoint pt =	p->GetCenterPoint();
			MoveWindowToTheObject(  (int)pt.x  , (int)pt.y   );
		}
	}
}


void CTrainWorldView::OnFindEndstopbyname()
{
	OnRunStopfind();
}

void CTrainWorldView::MoveWindowToTheObject(  int ix , int iy  )
{
	BmpSizeWindow.left =  ix - 512 ;
	BmpSizeWindow.top =  iy - 512 ;
	BmpSizeWindow.right  = BmpSizeWindow.left + current_size_x;
	BmpSizeWindow.bottom = BmpSizeWindow.top + current_size_y;

	CTrainWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( pDoc)  
			pDoc->Interface_UpdateControlView( this, 2 , &BmpSizeWindow );
	Invalidate(FALSE);
}

void CTrainWorldView::OnContGroup()
{
	iSelect = SELECT_RECT;
	iAddMode = ADDMODE_CONT_GRP;
	mCTempVector.CTempVectorSetTmpObject( ObjTracker );
}

void CTrainWorldView::OnUpdateContGroup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
}

void CTrainWorldView::OnUpdateAddStopGrp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );
}

void CTrainWorldView::OnAddStopGrp()
{
	iSelect = SELECT_RECT;
	iAddMode = ADDMODE_STOP_GRP;
	mCTempVector.CTempVectorSetTmpObject( ObjTracker );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// selection methods handlers
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTrainWorldView::OnSelPoint()
{
	iSelect = SELECT_POINT;
	iAddMode = ADDMODE_NONE;
}

void CTrainWorldView::OnUpdateSelPoint(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(  iSelect == SELECT_POINT   );
}

void CTrainWorldView::OnSelRect()
{
	iSelect = SELECT_RECT;
	iAddMode = ADDMODE_NONE;
	mCTempVector.CTempVectorSetTmpObject( ObjTracker );
}

void CTrainWorldView::OnUpdateSelRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(  iSelect == SELECT_RECT   );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// edit methods handlers
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTrainWorldView::OnTrackMove()
{
	if ( mCObjRailsColl.IsSingleBendRailSelected() )
	{
		mCObjRailsColl.DrawHandleOnSelected();
		Invalidate(FALSE);
		iSelect = HANDLE_BEND;
	}
}

void CTrainWorldView::OnUpdateTrackMove(CCmdUI *pCmdUI)
{
	BOOL bsel =  mCObjRailsColl.IsSingleBendRailSelected();
	pCmdUI->Enable( bsel);	 
}

void CTrainWorldView::OnTrackDel()
{
	mCObjRailsColl.DeleteSelectedRails();
	bActiveObjects = FALSE;
	Invalidate(FALSE);
}

void CTrainWorldView::OnUpdateTrackDel(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(  iSelect == SELECT_POINT   );
		pCmdUI->Enable(  bActiveObjects  );
}

void CTrainWorldView::OnTrackShow()
{
	CObjRail * pr = mCObjRailsColl.GetRailSelected() ;
	if ( pr != NULL )
		OnRailEdit( pr );
}

void CTrainWorldView::OnUpdateTrackShow(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(  iSelect == SELECT_POINT   );
		pCmdUI->Enable(  bActiveObjects  );

}

void CTrainWorldView::OnTracksSnap()
{
	mCObjRailsColl.SnapSelectedObjects();
	CRect  rc = mCObjRailsColl.GetSelectedObjectRect(BmpSizeWindow.TopLeft(),   0 );
	//  testRect = rc; testRectEnable = TRUE; Invalidate(FALSE);
	InvalidateRect( rc , FALSE);
}

void CTrainWorldView::OnUpdateTracksSnap(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(  iSelect == SELECT_RECT   );
	pCmdUI->Enable(  mCObjRailsColl.GetNumberOfSelectedObjects() == 2 );
}
////////////////////////////////////////////////////////////////////
//   select central
//  ID_TRACK_DEL_SEL        "Add stop \nAdd stop"

void CTrainWorldView::OnTrackDelSel()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_STOP;
	mCTempVector.CTempVectorSetTmpObject( ObjStop );
}

/////////// slect  route

void CTrainWorldView::OnUpdateTrackDelSel(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(  iSelect == SELECT_RECT   );
		 	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );	
}

//ID_TRACK_SHOW_CONN      "Add swithc \nAdd swithc"

void CTrainWorldView::OnTrackShowConn()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_SWITCH;
	mCTempVector.CTempVectorSetTmpObject( ObjSwitch );
}

void CTrainWorldView::OnUpdateTrackShowConn(CCmdUI *pCmdUI)
{
	//pCmdUI->Enable(  iSelect == SELECT_RECT   );
		 	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );	
}


 


void CTrainWorldView::OnAddSem()
{
	iSelect = SELECT_NONE;
	iAddMode = ADDMODE_SEM;
	mCTempVector.CTempVectorSetTmpObject( ObjSem );
}


void CTrainWorldView::OnUpdateAddSem(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(  iModeOper == MODE_ADD_OBJECT  );	
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//  handling mouse move in run mode
//
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTrainWorldView::ScrollMapsInRunMode(CPoint point)
{

	CRect rect1;
	GetClientRect( &rect1 );

	if ( (point.x < 16 ) || (point.y < 16 ) || (point.x > ( rect1.right-16) ) ||(point.y > ( rect1.bottom -16) ))
		 		{  MouseStatePressed = FALSE;	ReleaseCapture();return;}

	int  diff_x = point.x - Last_Point_DC.x;
	int  diff_y = point.y - Last_Point_DC.y;
 
	 if ( (diff_x != 0) || (diff_y != 0) )
		{
				CRect  rc_cur = BmpSizeWindow;
				
			 	if ( diff_x < 0 ) // move left
			 		if (  (BmpSizeWindow.left-diff_x+current_size_x  ) >  (TotalSpaceEndPoint.x  ) ) 
						diff_x = TotalSpaceEndPoint.x - BmpSizeWindow.left - current_size_x ;

				if ( diff_x > 0 )  // move right
			 		if (  (BmpSizeWindow.left-diff_x) < 0 )	diff_x =  BmpSizeWindow.left  ;
			 
				BmpSizeWindow.left -= diff_x;

				if ( diff_y < 0 ) // move up
					if (  (  (BmpSizeWindow.top + WIN_Y ) - diff_y ) > TotalSpaceEndPoint.y )  
						diff_y =  TotalSpaceEndPoint.y  - ( BmpSizeWindow.top + WIN_Y)    ;

				if ( diff_y > 0 )  // move down
					if (  (BmpSizeWindow.top-diff_y) < 0 )	diff_y =  BmpSizeWindow.top  ;

 				BmpSizeWindow.top -= diff_y;

				BmpSizeWindow.right  = BmpSizeWindow.left + current_size_x;
				BmpSizeWindow.bottom = BmpSizeWindow.top + current_size_y;

				Last_Point_DC = point;

				CTrainWorldDoc* pDoc = GetDocument();
				ASSERT_VALID(pDoc);
				if ( pDoc)  
					{
					 	pDoc->Interface_UpdateControlView( this, 2 , &BmpSizeWindow );
						//ReloadMemoryBitmap( NULL );
					}
				Invalidate (FALSE);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//  handling mouse button down
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTrainWorldView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	MouseStatePressed=TRUE;
    Last_Point_DC = point;
    SetCapture();

 
	if (  iModeOper == MODE_ADD_OBJECT )
		{
				mCTempVector.CTempVectorUpdateStart( point );
				mCTempVector.CTempVectorUpdateEnd( point );
				CRect rc;
				rc = mCTempVector.CTempVectorGetRectToInvalidate();
				InvalidateRect( rc , FALSE);
		}

	if (  iModeOper == MODE_EDIT_OBJECT )
		{
			if ( iSelect == SELECT_RECT)
				{
				mCTempVector.CTempVectorUpdateStart( point );
				mCTempVector.CTempVectorUpdateEnd( point );
				CRect rc;
				rc = mCTempVector.CTempVectorGetRectToInvalidate();
				InvalidateRect( rc , FALSE);
				}
			if ( iSelect == HANDLE_BEND)
				{
					if ( mCObjRailsColl.HitBendHandle( BmpSizeWindow.TopLeft() , point ) == FALSE)  iSelect =SELECT_POINT;
					// chnage mouse cursor her to grab  handle
				}

		}
	if (  iModeOper == MODE_RUN )
		{
 

		}

}

 ////////////////////////////////////////////////////////////////////////////////////////////////////////
//  handling mouse move  
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTrainWorldView::OnMouseMove(UINT nFlags, CPoint point)
{

	if ( MouseStatePressed == TRUE )
    {
		if ( iModeOper == MODE_RUN )  ScrollMapsInRunMode(  point);
		else 
			{   
			// update the temp vector for drawing - just the endpoint 
			//  invalidate prevoius postion
				if ( iModeOper == MODE_ADD_OBJECT  )
				{

					if (  (iAddMode == ADDMODE_CONT_GRP ) || (iAddMode == ADDMODE_STOP_GRP) )
					{
						mCTempVector.CTempVectorUpdateEnd( point ); 
						CRect rc1 = mCTempVector.CTempVectorGetRectToInvalidate();
					 	InvalidateRect( rc1 , FALSE);
						 //   testRect = rc1; testRectEnable = TRUE;Invalidate(FALSE);
					}


					if (   iAddMode == ADDMODE_SWITCH )
					{
						int ep;
						CObjRail   *px = mCObjRailsColl.GetClosestRailEp ( BmpSizeWindow.TopLeft() ,point , 60 , &ep);
						if ( px != NULL )
							mCTempVector.CTempVectorSetPointReference( SET_REF , px->GetPoint(ep) );
						else
							mCTempVector.CTempVectorSetPointReference( CLEAR_REF , point );

					}

					if (  (iAddMode == ADDMODE_STOP)  ||  (iAddMode == ADDMODE_SEM ) )
					{
	
						CObjRail   *px = mCObjRailsColl.GetClosestRail ( BmpSizeWindow.TopLeft() ,point , 60  );
						if ( px != NULL )
							mCTempVector.CTempVectorSetSegmentReference( SET_REF , px   );
						else
							mCTempVector.CTempVectorSetSegmentReference( CLEAR_REF , px   );
					}


					CRect rc1 = mCTempVector.CTempVectorGetRectToInvalidate();
					mCTempVector.CTempVectorUpdateEnd( point );
					CRect rc2 = mCTempVector.CTempVectorGetRectToInvalidate();
					CRect rc3; rc3.UnionRect( &rc1,&rc2);
			 		InvalidateRect( rc3 , FALSE);
				}		
				if (  iModeOper == MODE_EDIT_OBJECT )
				{
					
					if ( iSelect == SELECT_RECT)
					{
						mCTempVector.CTempVectorUpdateEnd( point ); 
						CRect rc1 = mCTempVector.CTempVectorGetRectToInvalidate();
					 	InvalidateRect( rc1 , FALSE);
						 //   testRect = rc1; testRectEnable = TRUE;Invalidate(FALSE);
					}
 
					if ( iSelect == HANDLE_BEND)
					{  // the handle is hit during mouse down
						 mCObjRailsColl.ModifyBendObject( BmpSizeWindow.TopLeft() , point )  ;
						 CRect rc = mCObjRailsColl.GetSelectedObjectRect(BmpSizeWindow.TopLeft(), 1);
						 InvalidateRect( rc  , FALSE);
						//	testRect = rc ; testRectEnable = TRUE;// Invalidate(FALSE);
					}

				}

 


		}

    }
 
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  handling mouse button up
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTrainWorldView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	MouseStatePressed=FALSE;
    Last_Point_DC = point;
	ReleaseCapture();

 
	//CRect CObjRailsColl::ManageControlObject (  CPoint offset, CPoint pt  )

	if ( iModeOper == MODE_ADD_OBJECT )
	{
			CRect rc1 = mCTempVector.CTempVectorGetRectToInvalidate();
			mCTempVector.CTempVectorUpdateEnd( point );
			CRect rc2 = mCTempVector.CTempVectorGetRectToInvalidate();
			CRect rc3; rc3.UnionRect( &rc1,&rc2);
			InvalidateRect( rc3 , FALSE);

			if (  iAddMode == ADDMODE_STRIGHT )
			{
				mCObjRailsColl.AddObjectStright( BmpSizeWindow.TopLeft(), mCTempVector.CTempVectorGetDrawData()) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_BEND_RIGHT )
			{
				mCObjRailsColl.AddObjectBend( BmpSizeWindow.TopLeft(), ObjBendRightRail,  mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_BEND_LEFT )
			{
				mCObjRailsColl.AddObjectBend( BmpSizeWindow.TopLeft(), ObjBendLeftRail , mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_DB_STRIGHT )
			{
				mCObjRailsColl.AddObjectDblStright( BmpSizeWindow.TopLeft(), ObjStraightDblRail , mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_TERMINATOR )
			{
				mCObjRailsColl.AddObjectStrightEnd( BmpSizeWindow.TopLeft(),   mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_STOP )
			{
				mCObjRailsColl.AddObjectControl( BmpSizeWindow.TopLeft(),  ObjStop,  mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_SWITCH )
			{
				mCObjRailsColl.AddObjectControl( BmpSizeWindow.TopLeft(),  ObjSwitch ,  mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}
			if (  iAddMode == ADDMODE_SEM )
			{
				mCObjRailsColl.AddObjectControl( BmpSizeWindow.TopLeft(),  ObjSem ,  mCTempVector.CTempVectorGetDrawData() ) ;
				InvalidateRect( rc3 , FALSE);
			}

			if (  iAddMode == ADDMODE_CONT_GRP )
			{
 						 
					mCTempVector.CTempVectorUpdateEnd( point ); 
					CRect rc1 =  CRect ( mCTempVector.CTempVectorGetPoint(0) , mCTempVector.CTempVectorGetPoint(1));

					//AfxMessageBox( "Add group now");

					mCObjRailsColl.AddObjectControlGroup( BmpSizeWindow.TopLeft() , rc1 , ObjSem ); 

			}

 			if (  iAddMode == ADDMODE_STOP_GRP )
			{
 						 
					mCTempVector.CTempVectorUpdateEnd( point ); 
					CRect rc1 =  CRect ( mCTempVector.CTempVectorGetPoint(0) , mCTempVector.CTempVectorGetPoint(1));

					//AfxMessageBox( "Add group now");

					mCObjRailsColl.AddObjectControlGroup( BmpSizeWindow.TopLeft() , rc1 , ObjStop ); 

			}


			 
	}
	if (  iModeOper == MODE_EDIT_OBJECT )
	{
					if ( iSelect == SELECT_RECT)
					{
						if ( mCObjRailsColl.ClearSelected() == TRUE ) Invalidate(FALSE);
						mCTempVector.CTempVectorUpdateEnd( point ); 
						CRect rc1 =  CRect ( mCTempVector.CTempVectorGetPoint(0) , mCTempVector.CTempVectorGetPoint(1));
						rc1.NormalizeRect(); 
						rc1.InflateRect( 2,2);
						InvalidateRect( rc1 , FALSE);
						bActiveObjects = mCObjRailsColl.FindRailObjects( BmpSizeWindow.TopLeft(), rc1 ) ;
						CRect  rrc = mCObjRailsColl.GetSelectedObjectRect(BmpSizeWindow.TopLeft(),   0 );
						 //  testRect = rrc; testRectEnable = TRUE;Invalidate(FALSE);
						InvalidateRect( rrc , FALSE);

					}
					if ( iSelect == SELECT_POINT )
					{
						
						if ( mCObjRailsColl.ClearSelected() == TRUE ) Invalidate(FALSE);
						mCTempVector.CTempVectorUpdateEnd( point ); 
						CRect rc1 =  CRect ( mCTempVector.CTempVectorGetPoint(0) , mCTempVector.CTempVectorGetPoint(1));
						rc1.NormalizeRect(); 
						rc1.InflateRect( 2,2);
						InvalidateRect( rc1 , FALSE);
						bActiveObjects = mCObjRailsColl.FindRailObject( BmpSizeWindow.TopLeft(), point ) ;
						CRect  rrc = mCObjRailsColl.GetSelectedObjectRect(BmpSizeWindow.TopLeft(),   0 );
						//  testRect = rrc; testRectEnable = TRUE; Invalidate(FALSE);
					 	InvalidateRect( rrc , FALSE);

						///  must also find other objects  as controls  trams !!!!!!  trams are higher priorities !!!!!
						{
							CObjRail * pr = mCObjRailsColl.GetRailSelected() ;
							if ( pr != NULL )
	                              //mDebug.CDebugPut((char *)" HType  [%d] %d ", (int)pr->GetObjectType() , (int) pr->GetRailId());
								OnRailUpdateEdit(pr);


						}


						{
							CObjControls *p = mCObjRailsColl.FindControlObject( BmpSizeWindow.TopLeft(), point ) ;
							if ( p != NULL )  
								{

 //mDebug.CDebugPut((char *)" HType  [%d]  ", (int)p->GetObjectType() );

//OnStopUpdateEdit(CObjControls *p)
									if ( p->GetObjectType() == ObjSwitch )  OnSwitchControlEdit(p);
									if ( p->GetObjectType() == ObjSem ) OnSemControlEdit( p);
									if ( p->GetObjectType() == ObjStop) OnStopControlEdit( p);
								}
						}


					}
					if ( iSelect == HANDLE_BEND)
					{
						mCObjRailsColl.ModifyBendObject( BmpSizeWindow.TopLeft() , point ) ;
						iSelect = SELECT_POINT;
						Invalidate(FALSE);
					}

	}

	if (  iModeOper == MODE_RUN )
	{
		 CRect rc  = mCObjRailsColl.ManageControlObject (  BmpSizeWindow.TopLeft() , point  );
		 if ( rc != NULL ) InvalidateRect(  rc , FALSE);

 		 CTramTrainVagons *pv = mCObjRailsColl.FindTrainObject( BmpSizeWindow.TopLeft() , point  );
		 if ( pv != NULL )
		 {
			 CString Cs; Cs.Format("Tram(%d) Line:%d", pv->GetTramId() , pv->GetLineId() );
			 ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->DisplayPanel(  1 , Cs  );
			 mWinTextPopUp.SetWinPopUpToolText(point,  Cs  );
			 OnTramsControl(pv->GetTramId()  );
		 }
 
	}


	CView::OnLButtonUp(nFlags, point);
}



 


void CTrainWorldView::OnUpdateRunStart(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable( iModeOper == MODE_RUN ); 
}

 

void CTrainWorldView::OnRunStart()
{ 
	mCObjRailsColl.StartTrams();  	

	CTrainWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
 

    if ( pDoc)
	{
	 
	// tm_simulation_time = pDoc->GetSimulationStartTime();
	 tm_simulation_time = mSystem.m_SimTime;
	 SetTimer( THIS_VIEW_TIMER ,THIS_VIEW_TIMER_INTERVAL,NULL);
	}
}


void CTrainWorldView::OnUpdateRunStop(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable( iModeOper == MODE_RUN ); 
}


void CTrainWorldView::OnRunStop()
{
	KillTimer(THIS_VIEW_TIMER );
}


void CTrainWorldView::OnUpdateRunStep(CCmdUI *pCmdUI)
{
	 pCmdUI->Enable( iModeOper == MODE_RUN ); 
}


void CTrainWorldView::OnRunStep()
{
	mCObjRailsColl.MoveTrams(4);
	Invalidate(FALSE);
}


void CTrainWorldView::OnUpdateRunRevers(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( iModeOper == MODE_RUN ); 
}


void CTrainWorldView::OnRunRevers()
{

	mCObjRailsColl.ReversTramsDir();
	Invalidate(FALSE);
}


 

void CTrainWorldView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	//CView::OnTimer(nIDEvent);
	KillTimer(THIS_VIEW_TIMER);

	mCObjRailsColl.MoveTrams( (float)mSystem.m_SimStep );
	Invalidate(FALSE);

	CTrainWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if ( !pDoc)  return;  
	 
  
	 	// divider 10 per second  60 per minute   =  600 - real time  
	//  trams run average 30km/hour  need 1 hour for loop  20 pixels per secodn   300 pixels - 3 min  100 pixels / min  
	// let's put  300

	m_divider20 +=1;

	if ( m_divider20 > mSystem.m_SimDivisor )
	{
		//CTimeSpan tm_distunit = pDoc->GetSimulationIncTimeSpan(); 

		CTime tm = tm_simulation_time;
		tm += mSystem.m_TimeSpan;

		tm_simulation_time = tm;
		mSystem.m_SimTime = tm;
		
		m_divider20 = 0;
	//CTime tm_simulation_time( 0);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->PaintSimulationTime( tm_simulation_time );
	}
	
	SetTimer( THIS_VIEW_TIMER ,THIS_VIEW_TIMER_INTERVAL,NULL);
}

 #include "SwitchControl.h"

CSwitchControl * mCSwitchControl = NULL;

void CTrainWorldView::OnSwitchControlEdit( CObjControls *p )
{
   if (mCSwitchControl == NULL)
	{
		mCSwitchControl = new CSwitchControl(this);
		if (mCSwitchControl->Create( p ) == TRUE)
		{
			 
		}	
	}
	else
	{
		mCSwitchControl->SetActiveWindow();
		mCSwitchControl->Update(p);
   }
}


 

 #include "SemControl.h"

CSemControl * mCSemControl = NULL; 

void  CTrainWorldView::OnSemControlEdit(CObjControls *p)
{

   if (mCSemControl == NULL)
	{
		mCSemControl = new  CSemControl(this);
		if (mCSemControl->Create( p ) == TRUE)
		{
			 
		}	
	}
	else
	{
		mCSemControl->SetActiveWindow();
		mCSemControl->Update(p);
   }
}


 #include "EditStop.h"

CEditStop * mCEditStop = NULL;

void  CTrainWorldView::OnStopControlEdit(CObjControls *p)
{

   if (mCEditStop == NULL)
	{
		mCEditStop = new  CEditStop(this);
		if (mCEditStop->Create( p ) == TRUE)
		{
			 
		}	
	}
	else
		OnStopUpdateEdit(  p);
		//mCEditStop->SetActiveWindow();
}

void  CTrainWorldView::OnStopUpdateEdit(CObjControls *p)
{
   if (mCEditStop != NULL)  
	{
		mCEditStop->SetActiveWindow();
		mCEditStop->Update(p);
   }
}

 #include "RailEdit.h"

CRailEdit * mCRailEdit = NULL;

void  CTrainWorldView::OnRailEdit(CObjRail *p)
{

   if (mCRailEdit == NULL)
	{
		mCRailEdit = new  CRailEdit(this);
		if (mCRailEdit->Create( p ) == TRUE)
		{
			 
		}	
	}
	else
		mCRailEdit->SetActiveWindow();
}

void  CTrainWorldView::OnRailUpdateEdit(CObjRail *p)
{
   if (mCRailEdit != NULL)  
	{
		mCRailEdit->SetActiveWindow();
		mCRailEdit->Update(p);
   }
}


#include "TramsContr.h"

CTramsContr * mCTramsContr = NULL;

void  CTrainWorldView::OnTramsControl(int selId  )
{
   if (mCTramsContr == NULL)
	{
		mCTramsContr = new  CTramsContr(this);

		if (mCTramsContr->Create( selId   ) == TRUE)
		{
 	 
		}	
		else
			mDebug.CDebugPut(" CTrainWorldView::OnTramsControl( )  failed" );
	}
	else
	{
		mCTramsContr->SetActiveWindow();
		mCTramsContr->Update(selId);
   }
}
 

 #include "FindStop.h"

CFindStop  *mCFindStop = NULL;

void CTrainWorldView::OnRunStopfind()
{
   if (mCFindStop == NULL)
	{
		mCFindStop = new  CFindStop(this);

		if (mCFindStop->Create( 1  ) == TRUE)
		{
 	 
		}	
		else
			mDebug.CDebugPut(" CTrainWorldView::OnRunStopfind( )  failed" );
	}
	else
	{
		mCFindStop->SetActiveWindow();
		//mCFindStop->Update(selId);
   }
}

//  use this to close dialogs for all !!!!!!!!!!

void  CTrainWorldView::SwitchDialogMessage( int msg , int value, CObject *p )  
{
	if ( msg ==  CLOSE_DIALOG_SWITCH) { 
		  Invalidate(FALSE);
		mCSwitchControl = NULL;
	}

	if ( msg ==  CLOSE_DIALOG_SEM) { 
		  Invalidate(FALSE);
		  mCSemControl = NULL;
	}

	if ( msg ==  CLOSE_DIALOG_STOP) { 
		  Invalidate(FALSE);
		  mCEditStop = NULL;
	}

	if ( msg ==  CLOSE_DIALOG_RAIL) { 
		  Invalidate(FALSE);
		  mCRailEdit = NULL;
	}

	if ( msg ==  CLOSE_DIALOG_TRAMS) { 
		  Invalidate(FALSE);
		  mCTramsContr = NULL;
	}

	if ( msg ==  CLOSE_DIALOG_STOPS) { 
		  Invalidate(FALSE);
		  mCFindStop = NULL;
	}

 

	if ( msg ==  ENABLE_TESTMODE) {  Invalidate(FALSE); }

	// need also small invalidatio
	if ( msg == INVALIDATE_MAIN ) Invalidate(FALSE);
	
} 

 
