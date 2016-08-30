 

#pragma once
#include "FlyByText.h"

class CWinTextPopUp {

public:
	CWinTextPopUp();
	BOOL  OpenWinPopUpTool(CWnd *parent);
	void  SetWinPopUpToolText(  CPoint pt,  CString Cs);
 	void  SetWinPopUpToolMousePos( int tick , CPoint mPos );
	BOOL  GetWinPopUpToolStatus();
private:

	CFlyByText  mMyWnd;
	BOOL  mMyWndOpen;
	int   mTimeOut;
	BOOL  mMove;
	CPoint mLastPoint;
	CPoint mLastTextPoint;
	CPoint mPos ;
};