// ViewContr.cpp : implementation file
//

#include "stdafx.h"

//#include "Foundation.h"

#include "TrainWorld.h"

#include "TrainWorldDoc.h"

#include "ViewContr.h"

#include "Debug.h"
extern CDebug mDebug;

#include "SystemValues.h"	

#include "DrawTmpObject.h"
//#include "Graphics.h"

// define 
//#define SEL_SIZE 16*16


// CViewContr

IMPLEMENT_DYNCREATE(CViewContr, CScrollView)

CViewContr::CViewContr()
{
	m_mouse_move =0;
	IsBitmap = FALSE;
	mSelRect.left = 0;
	mSelRect.top = 0;
	mSelRect.right = STD_AUX_WIN;    
	mSelRect.bottom = STD_AUX_WIN;    
}

CViewContr::~CViewContr()
{
}

BEGIN_MESSAGE_MAP(CViewContr, CScrollView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CViewContr drawing


BOOL CViewContr::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	/*
	if ( WM_USER == message){}
	*/
	return CScrollView::OnWndMsg(message, wParam, lParam, pResult);
}

void CViewContr::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
 
    CSize sizeDoc;
	sizeDoc.cx= STD_AUX_WIN*BLOCKS_IN_ROW;
	sizeDoc.cy = STD_AUX_WIN*BLOCKS_IN_COL;
	SetScrollSizes(MM_TEXT, sizeDoc);
 
 // mDebug.CDebugPut((char *)" CViewContr::Initial Update  "   ); 
}

int v;

void CViewContr::OnUpdate(CView*  pSender , LPARAM  lHint , CObject*  pHint )
{
	if ( lHint == 2)
	{
		CRect *p = (CRect *)pHint;
		if ( *(CRect*)p != mSelRect )
		{
			InvalidateRect( mSelRect, FALSE);
			mSelRect = *(CRect*)p; //tSelRect;

			CRect local = mSelRect;
			DocToClient( local );

			InvalidateRect( local ,FALSE);
		}
	//  mDebug.CDebugPut((char *)" Update2 (%d,%d)(%d,%d) " , p->left,p->top,p->right,p->bottom  );
	}
}


void CViewContr::DocToClient(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(rect);
	rect.NormalizeRect();
} 

void CViewContr::ClientToDoc(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(&point);
}

 
void CViewContr::ClientToDoc(CRect& rect)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.DPtoLP(rect);
	ASSERT(rect.left <= rect.right);
	ASSERT(rect.bottom <= rect.top);
}

void CViewContr::DocToClient(CPoint& point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc, NULL);
	dc.LPtoDP(&point);
}


//  1024x1014 max bitmap to load
// nothing to change here  - instead crete bigger jpg file in doc

void CViewContr::OnDraw(CDC* pDC)
{
	CTrainWorldDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	if ( IsBitmap == FALSE)
	{
		hdcMem = CreateCompatibleDC(pDC->m_hDC); 
		bitmap = CreateCompatibleBitmap(pDC->m_hDC, WIN_X_AUX, WIN_Y_AUX ); //  
		SelectObject(hdcMem, bitmap);
		CRect rc(0,0,WIN_X_AUX,WIN_Y_AUX);
		pDoc->Interface_LoadAuxImage( hdcMem  ,  rc   );
		IsBitmap = TRUE;
	}

	BitBlt( pDC->m_hDC, 0,  0, WIN_X_AUX, WIN_Y_AUX , hdcMem,  0,  0 , SRCCOPY);

	OnDrawNet(  pDC->m_hDC  );
	OnDrawRemoteNetSelection(  pDC  );

	if ( m_mouse_move ) OnDrawNetSelectionTemp(  pDC  );

}


 

 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

void CViewContr::OnDrawRemoteNetSelection(   CDC* pDC ) 
{
 
 
	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( pDC->m_hDC);
	if (   mPenSet.GetSolidPen(   2 , GetRedColor()  ) == NULL ) return ;
	CRect tRec = mSelRect;
	tRec.DeflateRect(2,2,2,2);
	OnDrawRect( &tRec , pDC->m_hDC );
}

void CViewContr::OnDrawNet(   HDC hdc )
{
	int i ;

	for ( i =0;  i< BLOCKS_IN_COL ; i++)
	{
	 MoveToEx( hdc ,  0    , i << SCALE_COEEF  ,    (LPPOINT) NULL); 
	 LineTo(  hdc,  BLOCKS_IN_ROW*STD_AUX_WIN   ,  i << SCALE_COEEF  );
	}

	for ( i =0;  i< BLOCKS_IN_ROW ; i++)
	{
	  MoveToEx( hdc ,  i << SCALE_COEEF     , 0  ,    (LPPOINT) NULL); 
	  LineTo(  hdc ,  i << SCALE_COEEF   ,  BLOCKS_IN_COL*STD_AUX_WIN );
	}
	  
}

void CViewContr::OnDrawNetSelection(   CDC* pDC)
{
	/*
	pDC->FillSolidRect( clientRect, RGB(  0 ,  200 , 0)  );
 */
}


void CViewContr::OnDrawNetSelectionTemp(   CDC* pDC)
{
	 
	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( pDC->m_hDC);
	if (   mPenSet.GetSolidPen(   2 , GetBlueColor()  ) == NULL ) return ;
	CRect tRec = mMoveRect ;
	tRec.DeflateRect(2,2,2,2);
	OnDrawRect( &tRec , pDC->m_hDC );

}

 
void CViewContr::OnDrawBgn(   CDC* pDC)
{
//  create solid window background - Green
	/*
    CRect  clientRect;
 	clientRect.left = 0;
 	clientRect.right = 16*16; 	
	clientRect.top = 0;
 	clientRect.bottom = 16*16 ;
	pDC->FillSolidRect( clientRect  , RGB( 200 ,  200, 200)  );
	**/
}



// CViewContr diagnostics

#ifdef _DEBUG
void CViewContr::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CViewContr::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CViewContr message handlers


void CViewContr::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if ( m_mouse_move == 1 )
	{
	CPoint local = point;
	ClientToDoc( local );

	
	if ((local.x > 0) && (local.y > 0) && (local.x < WIN_X_AUX) && (local.y < WIN_Y_AUX))
		{

			CRect rlocal = mMoveRect;
			DocToClient( rlocal );
			InvalidateRect( rlocal ,FALSE);

		//	CTrainWorldDoc* pDoc = GetDocument();
		//	ASSERT_VALID(pDoc);if (!pDoc)return;

			int wide =  mSelRect.right - mSelRect.left;
			int high =	mSelRect.bottom - mSelRect.top;

			mMoveRect.left = local.x;
			mMoveRect.top  = local.y;
			mMoveRect.right =  mMoveRect.left +wide;
			mMoveRect.bottom = mMoveRect.top + high;

			rlocal = mMoveRect;
			DocToClient( rlocal );
			InvalidateRect( rlocal ,FALSE);

		//	pDoc->Interface_UpdateTrainView( this, 3 , &mMoveRect );

		}
	}
}

void CViewContr::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint local = point;
	ClientToDoc( local );

	if ((local.x > 0) && (local.y > 0) && (local.x < WIN_X_AUX) && (local.y < WIN_Y_AUX))
	{
		 
		m_mouse_move = 1;
		SetCapture();

		CTrainWorldDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);if (!pDoc)return;

		int wide =  mSelRect.right - mSelRect.left;
		int high =	mSelRect.bottom - mSelRect.top;

		mMoveRect.left = local.x;
		mMoveRect.top  = local.y;
		mMoveRect.right =  mMoveRect.left +wide;
		mMoveRect.bottom = mMoveRect.top + high;

		pDoc->Interface_UpdateTrainView( this, 3 , &mMoveRect );

		CRect rlocal = mMoveRect;
		DocToClient( rlocal );
		InvalidateRect( rlocal ,FALSE);

		SetTimer( 100,500,NULL);
 
	}
}


void CViewContr::OnLButtonUp(UINT nFlags, CPoint point)
{
	KillTimer( 100 );
	ReleaseCapture();
	if ( m_mouse_move == 1)
	{
			CPoint local = point;
			ClientToDoc( local );
			m_mouse_move = 0;

		if ((local.x > 0) && (local.y > 0) && (local.x < WIN_X_AUX) && (local.y < WIN_Y_AUX))
			{
 		
				CRect rlocal = mSelRect;
				DocToClient( rlocal );
				InvalidateRect( rlocal ,FALSE);
	  
				CTrainWorldDoc* pDoc = GetDocument();
				ASSERT_VALID(pDoc);if (!pDoc)return;

				int wide =  mSelRect.right - mSelRect.left;
				int high =	mSelRect.bottom - mSelRect.top;

				mSelRect.left = local.x;
				mSelRect.top = local.y;

				mSelRect.right =  mSelRect.left +wide;
				mSelRect.bottom = mSelRect.top + high;

				pDoc->Interface_UpdateTrainView( this, 3 , &mSelRect );
				
				rlocal = mSelRect;
				DocToClient( rlocal );
				InvalidateRect( rlocal ,FALSE);

				InvalidateRect( FALSE);
			}
	}
}



void CViewContr::OnTimer(UINT_PTR nIDEvent)
{
	  KillTimer( 100 );

	   if ( m_mouse_move == 1)
	   {
		   if ( mOldRect != mMoveRect )
		   {
			CTrainWorldDoc* pDoc = GetDocument();
			ASSERT_VALID(pDoc);if (!pDoc)return;
			pDoc->Interface_UpdateTrainView( this, 3 , &mMoveRect );
			mOldRect = mMoveRect;
		   }
		 SetTimer( 100,500,NULL);
	   }


	//CScrollView::OnTimer(nIDEvent);
}
