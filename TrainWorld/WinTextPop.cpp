

#include "stdafx.h"
#include "TrainWorld.h"

#include "WinTextPop.h"
#include "FlyByText.h"




CWinTextPopUp mWinTextPopUp;

 CWinTextPopUp::CWinTextPopUp()
 {
	 mMyWndOpen = FALSE;
	 mMove = FALSE;
	 mLastTextPoint = CPoint(0,0);
	 mPos  = CPoint(0,0);
 }


BOOL  CWinTextPopUp::OpenWinPopUpTool(CWnd *parent) 
{
	if (  mMyWndOpen == FALSE )
	 {

		if ( !mMyWnd.Create( NULL, NULL, WS_CHILD, CRect(10 , 10 , 160,  28 ), parent, 0, NULL))
		    return FALSE;
		mMyWnd.ShowWindow(  SW_HIDE);
		mMyWnd.UpdateWindow();
		mMyWndOpen = TRUE;
		return TRUE;
	 }
	return FALSE;
}

void  CWinTextPopUp::SetWinPopUpToolText(CPoint pt, CString Cs) 
{
	mMyWnd.SetTipText(  pt ,  Cs );
	mLastTextPoint = pt ;
	if ( mPos != mLastPoint )
	{
		mMove = FALSE;
	}
}

void  CWinTextPopUp::SetWinPopUpToolMousePos( int tick , CPoint mPos ) 
{
	if ( mPos != mLastPoint )
		if ( mPos != mLastTextPoint )
		{
			mMove = TRUE;
			mTimeOut = 0;
			mLastPoint = mPos;
		}
		else
		{
			if ( mLastTextPoint != mPos ) 
					mTimeOut += tick;
		}
}

BOOL  CWinTextPopUp::GetWinPopUpToolStatus() 
{
	if ( mMove == TRUE )
		if ( mTimeOut > 500 ) 
			return TRUE;
	return FALSE;
}