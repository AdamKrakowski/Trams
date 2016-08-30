// FlyByText.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"
#include "FlyByText.h"


// CFlyByText

IMPLEMENT_DYNAMIC(CFlyByText, CWnd)

CFlyByText::CFlyByText()
{
	mTextToDisplay  =0;
}

CFlyByText::~CFlyByText()
{
}


BEGIN_MESSAGE_MAP(CFlyByText, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CFlyByText message handlers




int CFlyByText::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// this->ShowWindow(FALSE);

	//SetTimer( 100 , 5000 ,NULL);

	return 0;
}


void CFlyByText::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
    GetClientRect( rect) ;
    dc.FillSolidRect( &rect, RGB(255,255,0) );

	CDC* pDC  =  &dc;

	if ( mTextToDisplay  == 1  )
	{
		LOGFONT logFont;
	    memset(&logFont, 0, sizeof(LOGFONT));
		logFont.lfHeight = 16 ;   
	    strcpy_s(logFont.lfFaceName,8, "Courier");    //    with face name "Arial".
	 
	    CFont font;
	    CFont* pOldFont = NULL;
	    if (font.CreateFontIndirect(&logFont))
		       pOldFont = pDC->SelectObject(&font);
 
		pDC->TextOut( 2 , 2  , mCString, mCString.GetLength());

		if (pOldFont != NULL)
		 	 pDC->SelectObject(pOldFont);

	}
}


void CFlyByText::SetTipText( CPoint  cp , CString Cs )
{
	SetTimer( 100 , 5000 ,NULL);
	mCString = Cs;
	mTextToDisplay  = 1;
	this->SetWindowPos( &CWnd::wndTop   , cp.x , cp.y - 32 , 0,0, SWP_NOSIZE) ;
	this->ShowWindow(TRUE);
	Invalidate();
}

void CFlyByText::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer( 100 );
	CWnd::OnTimer(nIDEvent);
	mTextToDisplay  = 0;
	this->ShowWindow(FALSE);
	Invalidate();

}
