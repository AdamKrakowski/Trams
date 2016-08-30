

#include "stdafx.h"

#include "Windowsx.h"
#include "Math.h"
#include <stdio.h>

#include "Debug.h"
#include "StdTrainDef.h"  
 
extern CDebug mDebug;


CDebugGraphics mCDebugGraphics;

 

CDebugGraphics::CDebugGraphics() 
{
	mGraphicModeEnable=0;
	mNbrOfPoint=0;
	nNbrOfSegments=0;
	nNmrOfRectangles=0;	 
}

CDebugGraphics::~CDebugGraphics() 
{

}

void CDebugGraphics::ResetStorage()
{
	mNbrOfPoint=0;
	nNbrOfSegments=0;
	nNmrOfRectangles=0;	 
}
	 
void CDebugGraphics::AddPoint(CPoint pt)
{
	if ( mNbrOfPoint < MAX_PTS )
	{
		mtPts[mNbrOfPoint] = pt ;
		mtPtsColor[mNbrOfPoint] = RGB(0,0,0) ; // default black
		mNbrOfPoint +=1;
	}
}
void CDebugGraphics::AddPoint(CFPoint ptf)
{
	CPoint pt ( (int)ptf.x, (int)ptf.y );
	if ( mNbrOfPoint < MAX_PTS )
	{
		mtPts[mNbrOfPoint] = pt  ;
		mtPtsColor[mNbrOfPoint] = RGB(0,0,0) ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddPoint(COLORREF crColor,CPoint pt)
{
	if ( mNbrOfPoint < MAX_PTS )
	{
		mtPts[mNbrOfPoint] = pt ;
		mtPtsColor[mNbrOfPoint] = crColor ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddPoint(COLORREF crColor,CFPoint ptf)
{
	CPoint pt ( (int)ptf.x, (int)ptf.y );
	if ( mNbrOfPoint < MAX_PTS )
	{
		mtPts[mNbrOfPoint] = pt  ;
		mtPtsColor[mNbrOfPoint] = crColor ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddSegment( CRect rc)
{
//	CPoint pt ( (int)ptf.x, (int)ptf.y );
	
	if ( nNbrOfSegments < MAX_SEG )
	{
		rc.NormalizeRect();		
		mtSeg[nNbrOfSegments] = rc ;
		mtSegColor[nNbrOfSegments] = RGB(0,0,0) ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddSegment( CPoint pt1 ,CPoint pt2)
{
	CRect rc ( pt1.x , pt1.y , pt2.x , pt2.y ); 
	if ( nNbrOfSegments < MAX_SEG )
	{
		rc.NormalizeRect();		
		mtSeg[nNbrOfSegments] = rc ;
		mtSegColor[nNbrOfSegments] = RGB(0,0,0) ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddSegment( CFPoint ptf1 ,CFPoint ptf2)
{
	CRect rc ( (int)ptf1.x , (int)ptf1.y , (int)ptf2.x , (int)ptf2.y ); 
	if ( nNbrOfSegments < MAX_SEG )
	{
		rc.NormalizeRect();		
		mtSeg[nNbrOfSegments] = rc ;
		mtSegColor[nNbrOfSegments] = RGB(0,0,0) ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddSegment(COLORREF crColor, CRect rc)
{
	if ( nNbrOfSegments < MAX_SEG )
	{
		rc.NormalizeRect();		
		mtSeg[nNbrOfSegments] = rc ;
		mtSegColor[nNbrOfSegments] = crColor ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddSegment(COLORREF crColor, CPoint pt1 ,CPoint pt2)
{
	CRect rc ( pt1.x , pt1.y , pt2.x , pt2.y );
	if ( nNbrOfSegments < MAX_SEG )
	{
		rc.NormalizeRect();		
		mtSeg[nNbrOfSegments] = rc ;
		mtSegColor[nNbrOfSegments] = crColor ; // default black
		mNbrOfPoint +=1;
	}
}

void CDebugGraphics::AddSegment(COLORREF crColor, CFPoint ptf1 ,CFPoint ptf2)
{
	CRect rc ( (int)ptf1.x , (int)ptf1.y , (int)ptf2.x , (int)ptf2.y ); 
	if ( nNbrOfSegments < MAX_SEG )
	{
		rc.NormalizeRect();		
		mtSeg[nNbrOfSegments] = rc ;
		mtSegColor[nNbrOfSegments] = crColor ; // default black
		mNbrOfPoint +=1;
	}
}


void CDebugGraphics::AddRect( CRect rc)
{
	if ( nNmrOfRectangles < MAX_REC )
	{
		rc.NormalizeRect();		
		mtRec[nNmrOfRectangles] = rc ;
		mtRecColor[nNmrOfRectangles] = RGB(0,0,0) ; // default black
		nNmrOfRectangles +=1;
	}
}

void CDebugGraphics::AddRect( CPoint pt1 ,CPoint pt2 )
{
	CRect rc ( pt1.x , pt1.y , pt2.x , pt2.y ); 
	if ( nNmrOfRectangles < MAX_REC )
	{
		rc.NormalizeRect();	
		mtRec[nNmrOfRectangles] = rc ;
		mtRecColor[nNmrOfRectangles] = RGB(0,0,0) ; // default black
		nNmrOfRectangles +=1;
	}
}

void CDebugGraphics::AddRect( CFPoint ptf1 ,CFPoint ptf2 )
{
	CRect rc ( (int)ptf1.x , (int)ptf1.y , (int)ptf2.x , (int)ptf2.y ); 
	if ( nNmrOfRectangles < MAX_REC )
	{
		rc.NormalizeRect();
		mtRec[nNmrOfRectangles] = rc ;
		mtRecColor[nNmrOfRectangles] = RGB(0,0,0) ; // default black
		nNmrOfRectangles +=1;
	}
}

void CDebugGraphics::AddRect(COLORREF crColor, CRect rc)
{
	if ( nNmrOfRectangles < MAX_REC )
	{
		rc.NormalizeRect();		
		mtRec[nNmrOfRectangles] = rc ;
		mtRecColor[nNmrOfRectangles] = crColor ; // default black
		nNmrOfRectangles +=1;
	}
}

void CDebugGraphics::AddRect(COLORREF crColor, CPoint pt1 ,CPoint pt2 )
{
	CRect rc ( pt1.x , pt1.y , pt2.x , pt2.y ); 
	if ( nNmrOfRectangles < MAX_REC )
	{
		rc.NormalizeRect();		
		mtRec[nNmrOfRectangles] = rc ;
		mtRecColor[nNmrOfRectangles] = crColor ; // default black
		nNmrOfRectangles +=1;
	}
}

void CDebugGraphics::AddRect(COLORREF crColor, CFPoint ptf1 ,CFPoint ptf2 )
{
	CRect rc ( (int)ptf1.x , (int)ptf1.y , (int)ptf2.x , (int)ptf2.y ); 
	if ( nNmrOfRectangles < MAX_REC )
	{
		rc.NormalizeRect();		
		mtRec[nNmrOfRectangles] = rc ;
		mtRecColor[nNmrOfRectangles] = crColor ; // default black
		nNmrOfRectangles +=1;
	}
}

void CDebugGraphics::Invalidate( int offset , CRect rc )
{

}

// draw collection of graphical items
void CDebugGraphics::Draw( HDC   hdc , CPoint offset , CRect rc	 )
{
	int i;

	//mDebug.CDebugPut((char *)"Draw  %d   ", mNbrOfPoint );


	for ( i=0 ; i < mNbrOfPoint ; i++ )
	{
		CPoint P1 =  OffsetFPoint ( mtPts[i] , offset );
 		if (   ( rc.PtInRect( P1 ) )    )
			DrawPointCross( P1 , hdc , mtPtsColor[i] , 2 );
	}

	for ( i=0 ; i < nNmrOfRectangles ; i++ )
	{
		CPoint P1 =  OffsetFPoint ( mtRec[i].TopLeft() , offset );
 		CPoint P2 =  OffsetFPoint ( mtRec[i].BottomRight() , offset );
 		if (   ( rc.PtInRect( P1 ) || ( rc.PtInRect( P2 ) ) )    )
			 OnDrawRect( &mtRec[i] ,  hdc );   

		/*
		{
			CMyRect mrc( mtRec[i] , mtRecColor[i] );
			mrc.Draw( hdc );
		}
		*/

	}

	for ( i=0 ; i < nNbrOfSegments ; i++ )
	{
		CPoint P1 =  OffsetFPoint ( mtSeg[i].TopLeft() , offset );
 		CPoint P2 =  OffsetFPoint ( mtSeg[i].BottomRight() , offset );
 		if (   ( rc.PtInRect( P1 ) || ( rc.PtInRect( P2 ) ) )    )
		{
			CSegment  cs( P1 , P2 );
			cs.DrawSegment( hdc, 2 , mtSegColor[i] ); 
		}	  
	}
}


BOOL CDebugGraphics::IsGraphicsEnabled()
{

	//mDebug.CDebugPut((char *)"Enbaled ?  %d   ", mGraphicModeEnable );


   if ( mGraphicModeEnable == 1 ) return TRUE;
   return FALSE;
}

void CDebugGraphics::EnableGraphics( BOOL enable ) 
{

	if ( enable == TRUE ) mGraphicModeEnable = 1;
	else mGraphicModeEnable = 0;
}

 