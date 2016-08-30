

#include "stdafx.h"

#include "Math.h"
#include <stdio.h>
 
#include "StdTrainDef.h"

#include "DrawTmpObject.h"


#include "Debug.h"
extern CDebug mDebug;
 
extern CDebugGraphics mCDebugGraphics;
 

COLORREF GetBlackColor() 
{
	return RGB( 0 ,0,0);
}
 
COLORREF GetGrayColor()
{
	return	RGB( 127 ,127,127);
}

COLORREF GetRedColor()
{
	return	RGB( 255 ,0,0);
}

COLORREF GetBlueColor()
{
	return	RGB( 0,0,255);
} 

COLORREF GetBlueDarkColor() 
{
	return	RGB( 0,0,127);
} 

COLORREF GetRedDarkColor() 
{
	return	RGB( 127 ,0,0);
}

COLORREF GetWhiteColor()
{
	return	RGB( 255 ,255,255);
}

COLORREF GetBraunColor()
{
	return	RGB( 100 ,100,0);
}

COLORREF GetGreenColor()
{
	return	RGB( 0 ,255 ,0);
}

 COLORREF GetGreyColor()
{
	return	RGB( 127 ,127 ,127);
}
 

COLORREF GetDarkGreenColor()
{
	return	RGB( 0 ,127 ,0);
}

COLORREF GetYellowColor()
{
	return	RGB( 255 , 255 , 0);
}

COLORREF  GetDarkYellowColor()
{
	return	RGB( 127 ,127 ,0);
}

 

void OnDrawRect( CRect  *srect , HDC hdc )
{
	MoveToEx(hdc ,  srect->left     ,srect->top ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  srect->right  ,  srect->top );
	LineTo(  hdc ,  srect->right ,  srect->bottom );
	LineTo(  hdc ,  srect->left  ,  srect->bottom );
	LineTo(  hdc ,  srect->left  ,  srect->top );
}

void DrawRectTilted( CPoint p1, CPoint p2, CPoint p3, CPoint p4  , HDC hdc )
{
	MoveToEx(hdc ,  p1.x    ,p1.y ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  p2.x    ,p2.y   );
	LineTo(  hdc ,  p3.x    ,p3.y   );
	LineTo(  hdc ,  p4.x    ,p4.y   );
	LineTo(  hdc ,  p1.x    ,p1.y   );
}
// Four overridden functions  to draw point

void DrawPointPlus( CFPoint cp , HDC hdc , COLORREF clr , int weight) 
{
	CMyPoint  ptf = CMyPoint( cp  ); 
    DrawPointPlus( ptf ,   hdc ,   clr ,   weight) ;
}

void DrawPointCross( CFPoint cp , HDC hdc , COLORREF clr , int weight) 
{
	CMyPoint  ptf = CMyPoint( cp  ); 
    DrawPointCross( ptf ,   hdc ,   clr ,   weight) ;
}

void DrawPointPlus( CPoint cp , HDC hdc , COLORREF clr , int weight) 
{
	HPEN pen;
	pen = CreatePen( PS_SOLID , weight , clr );
		if ( pen == NULL ) 
	{
		//SystemErrorMessage( 1 );
		return;
	}
	HPEN oldpen = (HPEN)SelectObject( hdc , pen );
	
	MoveToEx(hdc ,  cp.x-5     , cp.y ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  cp.x+5   ,  cp.y );
	MoveToEx(hdc ,  cp.x      , cp.y-5 ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  cp.x    ,  cp.y+5 );

	SelectObject( hdc , oldpen );
	DeleteObject( pen );
}

void DrawPointCross( CPoint cp , HDC hdc , COLORREF clr , int weight) 
{
	HPEN pen;
	pen = CreatePen( PS_SOLID , weight , clr );
		if ( pen == NULL ) 
	{
		//SystemErrorMessage( 1 );
		return;
	}
	HPEN oldpen = (HPEN)SelectObject( hdc , pen );
	
	MoveToEx(hdc ,  cp.x-4     , cp.y-4 ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  cp.x+4   ,  cp.y+4 );
	MoveToEx(hdc ,  cp.x-4      , cp.y+4 ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  cp.x+4    ,  cp.y-4 );

	SelectObject( hdc , oldpen );
	DeleteObject( pen );
}


void DrawTwoParLinesExt( DRAWDATASTRUCT *p , DWORD mode , HDC hdc ) 
{

	float  dx = (float)(p->EndPoint.x-p->StartPoint.x);
	float  dy = (float)(p->EndPoint.y-p->StartPoint.y);

	float fl = sqrt((float)(dx*dx+dy*dy));
	float fdisp =(float) p->Width;

	float dxx =    (fdisp * ((float)dy)/fl);
    float dyy =    (fdisp * ((float)dx)/fl);

	POINT SPoint0; 
	POINT SPoint1;
	POINT EPoint0; 
	POINT EPoint1;

	SPoint0.x = (int)roundToNearest((p->StartPoint.x + dxx));
	SPoint0.y = (int)roundToNearest((p->StartPoint.y - dyy));
	SPoint1.x = (int)roundToNearest((p->StartPoint.x - dxx));
	SPoint1.y = (int)roundToNearest((p->StartPoint.y + dyy));

	EPoint0.x = (int)roundToNearest((p->EndPoint.x + dxx));
	EPoint0.y = (int)roundToNearest((p->EndPoint.y - dyy));
	EPoint1.x = (int)roundToNearest((p->EndPoint.x - dxx));
	EPoint1.y = (int)roundToNearest((p->EndPoint.y + dyy));

	// need to create CFpoints when p become modified

    if (  mode&DRAWLINES )
	{
		MoveToEx(hdc ,  SPoint0.x     , SPoint0.y ,    (LPPOINT) NULL); 
		LineTo(  hdc , EPoint0.x ,  EPoint0.y  );
		MoveToEx(hdc ,  SPoint1.x     , SPoint1.y ,    (LPPOINT) NULL); 
		LineTo(  hdc , EPoint1.x ,  EPoint1.y  );
	}

	// compute update region
 
}

// same as DrawTwoParLinesExt

void DrawBox( DRAWDATASTRUCT *p , DWORD mode , HDC hdc ) 
{
	float  dx = (float)(p->EndPoint.x-p->StartPoint.x);
	float  dy = (float)(p->EndPoint.y-p->StartPoint.y);

	float fl = sqrt((float)(dx*dx+dy*dy));
	float fdisp =(float) p->Width;

	float dxx =    (fdisp * ((float)dy)/fl);
    float dyy =    (fdisp * ((float)dx)/fl);

	POINT SPoint0; 
	POINT SPoint1;
	POINT EPoint0; 
	POINT EPoint1;

	SPoint0.x = (int)roundToNearest((p->StartPoint.x + dxx));
	SPoint0.y = (int)roundToNearest((p->StartPoint.y - dyy));
	SPoint1.x = (int)roundToNearest((p->StartPoint.x - dxx));
	SPoint1.y = (int)roundToNearest((p->StartPoint.y + dyy));

	EPoint0.x = (int)roundToNearest((p->EndPoint.x + dxx));
	EPoint0.y = (int)roundToNearest((p->EndPoint.y - dyy));
	EPoint1.x = (int)roundToNearest((p->EndPoint.x - dxx));
	EPoint1.y = (int)roundToNearest((p->EndPoint.y + dyy));

	// need to create CFpoints when p become modified

  //  if (  mode&DRAWLINES )
	{
		MoveToEx(hdc ,  SPoint0.x     , SPoint0.y ,    (LPPOINT) NULL); 
		LineTo(  hdc , EPoint0.x ,  EPoint0.y  );

		MoveToEx(hdc ,  EPoint0.x     , EPoint0.y ,    (LPPOINT) NULL); 
		LineTo(  hdc , EPoint1.x ,  EPoint1.y  );

		MoveToEx(hdc ,  SPoint0.x     , SPoint0.y ,    (LPPOINT) NULL); 
		LineTo(  hdc , SPoint1.x ,  SPoint1.y  );


		MoveToEx(hdc ,  SPoint1.x     , SPoint1.y ,    (LPPOINT) NULL); 
		LineTo(  hdc , EPoint1.x ,  EPoint1.y  );
	}

}

 
/*

void ShadowStraightRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
	DrawTwoParLinesExt(  p , 0 , hdc ); 
}
*/
 


void PaintEndRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc ) 
{ 
}

 char tb[24*64+8];


void PaintTrainBitmap( CFPoint StartPoint,CFPoint EndPoint,HBITMAP bmpExercising , HDC hdc )
{
	 HDC   MemDCExercising;

	 float angle = 	ComputeVectorAngle( StartPoint,  EndPoint  ) +90 ;

//mDebug.CDebugPut((char *)" = %d   %d", (int)angle , (int)StartPoint.x );
 
	    MemDCExercising = CreateCompatibleDC(hdc);
        SelectObject(MemDCExercising, bmpExercising);
		BITMAP bm;
		GetObject ( bmpExercising, sizeof(bm), &bm );
		 
		HBITMAP bmpMono=NULL;
 
		CRect cr;
	  	POINT  AP[4];

		CFPoint FPoffs = ComputeTwoParLines(StartPoint,  EndPoint , (float)(bm.bmWidth>>1) , 1 );   // why one [1] is OK

		 AP[0].x = (long)roundToNearest(FPoffs.x)  ;
		 AP[0].y = (long)roundToNearest(FPoffs.y);

		cr.left  = AP[0].x  ;
		cr.right = cr.left + bm.bmWidth ;
		cr.top = AP[0].y;
		cr.bottom = AP[0].y+bm.bmHeight; 

		double dcos_angle = cos(  PI180*(angle) );
		double dsin_angle = sin(  PI180*(angle) );

		AP[1].x = (long)((float)cr.left		+	roundToNearest(bm.bmWidth*dcos_angle));
		AP[1].y = (long)((float)cr.top		-	roundToNearest(bm.bmWidth*dsin_angle)); 

		AP[2].x = (long)((float)cr.left		+	roundToNearest(bm.bmHeight*dsin_angle));
		AP[2].y = (long)((float)cr.top	    +	roundToNearest(bm.bmHeight*dcos_angle)); 

		  //  0,0  source copy OK
		PlgBlt( hdc , AP   ,MemDCExercising ,   0,  0, bm.bmWidth ,bm.bmHeight,bmpMono  , 0, 0);

		DeleteObject(bmpMono);
	    DeleteDC(MemDCExercising);
}




// rather paint vagon  TUNDERGND

void	PaintTrain( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc  )
{
	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);
 
	if ( p->pVagonData != NULL ) // we don't use bitmaps to draw currently but for future extention it stays
	 	PaintTrainBitmap(p->StartPoint,p->EndPoint, p->pVagonData->bmpHandle ,   hdc );
	else
	{
		
       // backup the input parameters	
	 	CFPoint stb1 =  p->StartPoint  ;
		CFPoint stb2 =  p->EndPoint   ;	
		int  withb   =  p->Width;
		float ln = GetDistance ( stb1,stb2 );

		// draw body of the vagon default  or optional colours 
		if (   mPenSet.GetSolidPen(   p->Width+2 , GetGrayColor()  ) == NULL ) return ;

		if ( mode&BODY_GREEN)
			if (   mPenSet.GetSolidPen(   p->Width+2 , GetGreenColor()  ) == NULL ) return ;

		if ( mode&BODY_RED)
			if (   mPenSet.GetSolidPen(   p->Width+2 , GetRedColor()  ) == NULL ) return ;

		if ( mode&BODY_YELLOW)
			if (   mPenSet.GetSolidPen(   p->Width+2 , GetYellowColor()  ) == NULL ) return ;

		if ( mode&BODY_LBLUE)
			if (   mPenSet.GetSolidPen(   p->Width+2 , GetDarkGreenColor() ) == NULL ) return ;

		if ( mode&TUNDERGND)
			if (   mPenSet.GetSolidPen(   p->Width+2 , GetGreyColor() ) == NULL ) return ;

		p->StartPoint = GetPointFmStart( stb1 , stb2 , (float)(2 + (withb >> 1)) );     // insted of  6 must be reletive
		p->EndPoint   = GetPointFmStart( stb1 , stb2 , (float)(ln - 2- (withb >> 1)) );
		p->Width = (p->Width >> 1) - 1;
		DrawBox(  p , DRAWLINES , hdc );

		// draw frame of the vagon   with of withb/p->Width  & shorter by 4 pixels (2x2)
		
		if ( mode&TUNDERGND)
		{
			if (   mPenSet.GetSolidPen(   1 , GetGreyColor()  ) == NULL ) return ; // frame color is blue
		}
		else
		 if (   mPenSet.GetSolidPen(   2 , GetBlueColor()  ) == NULL ) return ; // frame color is blue
		
		p->StartPoint = GetPointFmStart( stb1 , stb2  ,  2 );
		p->EndPoint   = GetPointFmStart( stb1 , stb2  , ln -2 );
		p->Width = withb;
		DrawBox(  p , DRAWLINES , hdc );

		if ( mode&FRONT_DRW)
		{
			// draw the head window
			int ws =  p->Width-3; if ( p->Width < 5 ) ws =2;
			if (   mPenSet.GetSolidPen(  ws , GetWhiteColor()  ) == NULL ) return ; 
			CFPoint st1 = GetPointFmStart( stb1 , stb2  ,  2 );	 
			CLineObject mLine( stb1 , stb2  );
			CLineObject mLinePerp( mLine.GetA() , mLine.GetB() , st1 );
			//  new CLineObject mLinePerp( mLine , st1 );
			CCircle  c1 = CCircle(  p->StartPoint   ,(float)( p->Width/2 +2) );
			CTwoPoints cp2 = ComputeIntersectionOfCircleAndLine(   c1 , mLinePerp );
			// draw white window
			MoveToEx(hdc ,  (int)cp2.mPoint1.x    ,  (int)cp2.mPoint1.y  ,    (LPPOINT) NULL); 
		    LineTo(  hdc , (int)cp2.mPoint2.x      ,  (int)cp2.mPoint2.y   );
	    }

		p->Width = withb - 2;  // schrink the inter vagon connection tube size 

		if ( mode&FRONT_SHD)
		{
		   	if ( mode&TUNDERGND)
			{
			    if (   mPenSet.GetSolidPen(   p->Width+2 , GetBlackColor() ) == NULL ) return ;
			}
			else
			    if (   mPenSet.GetSolidPen(   4 , GetBlueColor()  ) == NULL ) return ; 
		   	p->StartPoint = GetPointFmStart( stb1 , stb2  ,  -2 );  // use backup
			p->EndPoint   = GetPointFmStart( stb1 , stb2  , 2 );
			DrawBox(  p , DRAWLINES , hdc ); 
	    }
		if ( mode&BACK_SHD)
		{
		   	if ( mode&TUNDERGND)
			{
			    if (   mPenSet.GetSolidPen(   p->Width+2 , GetBlackColor() ) == NULL ) return ;
			}
			else
			    if (   mPenSet.GetSolidPen(   4 , GetBlueColor()  ) == NULL ) return ; 
			p->StartPoint = GetPointFmStart( stb1 , stb2  , ln - 2  );
			p->EndPoint   = GetPointFmStart( stb1 , stb2  , ln + 2 );
			DrawBox(  p , DRAWLINES , hdc ); 
		}
		// restore
		// p->Width = withb;
	 } 
}

void ComputeBandingRectTrain( DRAWDATASTRUCT *p  )
{

	float  dx = (float)(p->EndPoint.x-p->StartPoint.x);
	float  dy = (float)(p->EndPoint.y-p->StartPoint.y);

	float fl = sqrt((float)(dx*dx+dy*dy));
	float fdisp =(float) p->Width;

	float dxx =    (fdisp * ((float)dy)/fl);
    float dyy =    (fdisp * ((float)dx)/fl);

	POINT SPoint0; 
	POINT SPoint1;
	POINT EPoint0; 
	POINT EPoint1;

	SPoint0.x = (int)roundToNearest((p->StartPoint.x + dxx));
	SPoint0.y = (int)roundToNearest((p->StartPoint.y - dyy));
	SPoint1.x = (int)roundToNearest((p->StartPoint.x - dxx));
	SPoint1.y = (int)roundToNearest((p->StartPoint.y + dyy));

	EPoint0.x = (int)roundToNearest((p->EndPoint.x + dxx));
	EPoint0.y = (int)roundToNearest((p->EndPoint.y - dyy));
	EPoint1.x = (int)roundToNearest((p->EndPoint.x - dxx));
	EPoint1.y = (int)roundToNearest((p->EndPoint.y + dyy));

 
	CFPoint P1 =  GetPointFmStart(  p->StartPoint, p->EndPoint , -10 );
	CFPoint P2 =  GetPointFmStart(  p->StartPoint, p->EndPoint , 10 +GetDistance(p->StartPoint, p->EndPoint));

int table[6];

	table[0] = (int)SPoint0.x;
	table[1] = (int)SPoint1.x;
	table[2] = (int)EPoint0.x;
	table[3] = (int)EPoint1.x;
	table[4] = (int)P1.x;
	table[5] = (int)P2.x;
	// find the trailing ([   ]) extension

	p->mUpdRect.left =  GetLowestValue(  table, 6 );
	p->mUpdRect.right =  GetHighestValue(  table, 6 );

	table[0] = (int)SPoint0.y;
	table[1] = (int)SPoint1.y;
	table[2] = (int)EPoint0.y;
	table[3] = (int)EPoint1.y;
	table[4] = (int)P1.y;
	table[5] = (int)P2.y;


	p->mUpdRect.top =  GetLowestValue(  table, 6 );
	p->mUpdRect.bottom =  GetHighestValue(  table, 6 );

	p->mUpdRect.NormalizeRect();
	p->mUpdRect.InflateRect( 2 ,2);

}

//////////////////////////////////////////////////////////////////
///  2016.04.20  Revised
///
/// UNDERGND

void PaintBendRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
	// temporary segment 
	if ( mode&TMPDRAWLINES)
	{
		// nedd to find center point for temp drawing
		CSegment mSegm( p->StartPoint , p->EndPoint );
		mSegm.DrawSegment (hdc , 1 , GetGrayColor());
 
		CFPoint middle  = GetCenterPoint(  p->StartPoint ,  p->EndPoint );
		CLineObject  mLine( p->StartPoint ,  p->EndPoint  );
		CLineObject  mLinePerp( mLine.GetA()  , mLine.GetB()  , middle);

		CCircle  mcircle(  middle , 50.0 );
		CTwoPoints tpo = ComputeIntersectionOfCircleAndLine(mcircle , mLinePerp );

		CFPoint temp_rad_pnt = tpo.mPoint1;
		float a = GetAngleOfTwoVectors ( p->StartPoint , p->EndPoint , temp_rad_pnt );
		if ( p->Turn == 0 )	if ( a < 0 ) temp_rad_pnt = tpo.mPoint2;
		if ( p->Turn == 1 )	if ( a > 0 ) temp_rad_pnt = tpo.mPoint2;

 		float fhi =  GetDistance(  p->StartPoint ,  p->EndPoint) * (float)(sqrt ((double)3.0)/((double)2.0)) ;
		p->CenterPoint =  GetPointFmStart(  middle , temp_rad_pnt , fhi  );
 
		CLineObject  mLine1( p->CenterPoint  ,  p->EndPoint  );
		CLineObject  mLinePerp1( mLine1.GetA()  , mLine1.GetB()  , p->EndPoint );
		mLinePerp1.DrawLine( hdc, GetGreenColor()  );

		CLineObject  mLine2( p->CenterPoint  ,  p->StartPoint  );
		CLineObject  mLinePerp2( mLine2.GetA()  , mLine2.GetB()  , p->StartPoint);
		mLinePerp2.DrawLine( hdc, GetGreenColor()  );

	}
	 
	CArch  mArch(  p->CenterPoint ,  p->StartPoint  , p->EndPoint   );

	if  ( mode&SELECTEDLINE )
	{
		mArch.SetPen( 3 , GetRedColor());
	    CFPoint middle  = GetCenterPoint(  p->StartPoint ,  p->EndPoint );
		if  ( mode&MODIBEND )
		{
			CSegment mSegm( p->CenterPoint , middle );
			mSegm.DrawSegment (hdc , 1 , GetRedColor());

			PatBlt(hdc, (int)p->CenterPoint.x - 3, (int)p->CenterPoint.y - 3, 7, 7, DSTINVERT);

			//CLineObject  mLine( p->StartPoint ,  p->EndPoint  );
			//CLineObject  mLinePerp( mLine.GetA()  , mLine.GetB()  , middle);
			//mLinePerp.DrawLine( hdc ,GetBlueColor());

 //mDebug.CDebugPut((char *)">>>(%d,%d) (%d,%d)  ", (int)p->StartPoint.x,(int)p->StartPoint.y,(int)p->EndPoint.x, (int)p->EndPoint.y );

		}
	}
	else
		mArch.SetPen( 3 , GetBlackColor());

	if (  (mode&UNDERGND) == 0 )
		mArch.DrawArch( hdc , 0 );

	mArch.SetPenDotted( 1 , GetGrayColor());
	
	mArch.DrawArch( hdc , 0 );

	p->Radius = GetDistance( p->CenterPoint , p->StartPoint) ;
	p->Width = 3;

	//  mark if connected to nothing from this endpoints
 	if (  (p->m_Connections[0] == 0 ) && (p->m_Connections[1] == 0 ))
		DrawPointCross( p->StartPoint,hdc,GetRedColor(),2);

	if (  TESTMODE&mode ) DrawPointCross( p->StartPoint,hdc,GetRedColor(),2);

 	if (  (p->m_Connections[2] == 0 ) && (p->m_Connections[3] == 0 ))
		DrawPointCross( p->EndPoint,hdc,GetRedColor(),2); 

	if (  TESTMODE&mode ) DrawPointCross( p->EndPoint,hdc,GetRedColor(),2);

}

//////////////////////////////////////////////////////////////////
///  2016.04.20  Revised
///
///

void PaintStraightRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);
	if (   mPenSet.GetSolidPen(  4 , GetBraunColor() ) == NULL ) return ;
	// tracks
	if  ( mode&SINGLELINE )
		p->Width = 1;
	else 
		p->Width = RAILWIDTH;


	if  ( mode&SELECTEDLINE )
	{
		if (   mPenSet.GetSolidPen(   mode&0x03 , GetRedColor()) == NULL ) return ;
	}
	else
		if (   mPenSet.GetSolidPen(   mode&0x03 , GetBlackColor()) == NULL ) return ;
 	
	if (  (mode&UNDERGND) == 0 )
	  DrawTwoParLinesExt(  p , DRAWLINES , hdc );
	 


	// center line 
 	if ( (SWITCHOFF&mode) == 0)
	{
		if (   mPenSet.GetDottedPen(GetGrayColor()) == NULL ) return ;
		MoveToEx(hdc , (int)roundToNearest(p->StartPoint.x ) ,(int)roundToNearest(p->StartPoint.y) ,    (LPPOINT) NULL);
		LineTo(  hdc , (int)roundToNearest(p->EndPoint.x ) ,  (int)roundToNearest(p->EndPoint.y ));
	}
 

	//TESTMODE

//  mark if connected to nothing from this endpoints
 	if (  (p->m_Connections[0] == 0 ) && (p->m_Connections[1] == 0 ))
		DrawPointCross( p->StartPoint,hdc,GetRedColor(),2);

	// aways draw in test mode
 	if (  TESTMODE&mode )  DrawPointCross( p->StartPoint,hdc,GetRedColor(),2);
 
	if (  (p->m_Connections[2] == 65535 ) && (p->m_Connections[3] == 65535 ))
	{
		//CRect rc( (int)p->EndPoint.x-3,(int)p->EndPoint.y-3,(int)p->EndPoint.x+3,(int)p->EndPoint.y+3);
		//OnDrawRect( &rc ,   hdc );

		//FillRect(hdc , &rc , (HBRUSH) GetBlackColor());

		mPenSet.GetSolidPen(   8 , GetBlackColor());
 		MoveToEx(hdc ,  (int)p->EndPoint.x    ,(int)p->EndPoint.y ,  (LPPOINT) NULL); 
		LineTo(  hdc ,  (int)p->EndPoint.x+3   ,(int)p->EndPoint.y +3   );

		//DrawPointCross( p->EndPoint, hdc,GetBlackColor(),2); 
	}

 	if (  (p->m_Connections[2] == 0 ) && (p->m_Connections[3] == 0 ))
		DrawPointCross( p->EndPoint,hdc,GetRedColor(),2); 

	// aways draw in test mode
	if (  TESTMODE&mode ) DrawPointCross( p->EndPoint,hdc,GetRedColor(),2); 



}

//////////////////////////////////////////////////////////////////
///  2016.04.20  Added for consistency
///
///

void ComputeBandingRectStright( DRAWDATASTRUCT *p  )
{

	int table[4];
 
	table[0] = (int)p->StartPoint.x;
	table[1] = (int)p->EndPoint.x;

	p->mUpdRect.left =  GetLowestValue(  table, 2 );
	p->mUpdRect.right =  GetHighestValue(  table, 2 );

	table[0] = (int)p->StartPoint.y;
	table[1] = (int)p->EndPoint.y;

	p->mUpdRect.top =  GetLowestValue(  table, 2);
	p->mUpdRect.bottom =  GetHighestValue(  table, 2 );

	p->mUpdRect.NormalizeRect();
	p->mUpdRect.InflateRect( p->Width+4  , p->Width+4  );

}

//////////////////////////////////////////////////////////////////
///  2016.04.20  Revised
///
///
 
void ComputeBandingRectBend( DRAWDATASTRUCT *p  )
{
	// middle point
	CFPoint middle  = GetCenterPoint(  p->StartPoint ,  p->EndPoint );
	// extend from circe center via middle
	CFPoint rpoint =  GetPointFmStart( p->CenterPoint ,  middle ,  p->Radius+p->Width   );

	CFPoint middle1  = GetCenterPoint(  p->StartPoint ,  middle );
	// extend from circe center via middle
	CFPoint rpoint1 =  GetPointFmStart( p->CenterPoint ,  middle1 ,  p->Radius+p->Width   );

	CFPoint middle2  = GetCenterPoint(  p->EndPoint ,  middle );
	// extend from circe center via middle
	CFPoint rpoint2 =  GetPointFmStart( p->CenterPoint ,  middle2 ,  p->Radius+p->Width   );

	int table[6];

	table[0] = (int)p->StartPoint.x;
	table[1] = (int)p->EndPoint.x;
	table[2] = (int)rpoint.x;
	table[3] = (int)rpoint1.x;
	table[4] = (int)rpoint2.x;
	table[5] = (int)p->CenterPoint.x;

	p->mUpdRect.left =  GetLowestValue(  table, 6 );
	p->mUpdRect.right =  GetHighestValue(  table, 6 );

	table[0] = (int)p->StartPoint.y;
	table[1] = (int)p->EndPoint.y;
	table[2] = (int)rpoint.y;
	table[3] = (int)rpoint1.y;
	table[4] = (int)rpoint2.y;
	table[5] = (int)p->CenterPoint.y;

	p->mUpdRect.top =  GetLowestValue(  table, 6 );
	p->mUpdRect.bottom =  GetHighestValue(  table, 6 );

	p->mUpdRect.NormalizeRect();
	p->mUpdRect.InflateRect( p->Width+4  , p->Width+4  );

}
 

//////////////////////////////////////////////////////////////////
///  2016.04.20  Revised
///
///

void PaintControl( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
 	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	if ( mode&TMP_COLOR_RED)
		{ if (   mPenSet.GetSolidPen(  4 , GetRedColor() ) == NULL ) return ;}
	else if ( mode&TMP_COLOR_BLUE)
		{ if (   mPenSet.GetSolidPen(  4 , GetBlueColor() ) == NULL ) return ;}

	Ellipse( hdc, (int)p->EndPoint.x-10 ,(int)p->EndPoint.y-10 , (int)p->EndPoint.x +10 ,(int)p->EndPoint.y +10);
}

void ComputeBandingRectControl( DRAWDATASTRUCT *p  )
{
	p->mUpdRect.left = (int)p->EndPoint.x-10;
	p->mUpdRect.top = (int)p->EndPoint.y-10;
	p->mUpdRect.right = (int)p->EndPoint.x+10;
	p->mUpdRect.bottom = (int)p->EndPoint.y+10;
	p->mUpdRect.NormalizeRect();
	p->mUpdRect.InflateRect(  4  ,  4  );
}


void PaintStop( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
 	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	COLORREF  crb = GetRedColor();

	if (   p->ThisID == STATUS_SET_GO ) crb  = GetGreenColor();
	if (   p->ThisID == STATUS_NOOPER ) crb  = GetGreenColor();
	if (   mPenSet.GetSolidPen(  2 , crb ) == NULL ) return ;

	Ellipse( hdc, (int)p->CenterPoint.x-8 ,(int)p->CenterPoint.y-8 , (int)p->CenterPoint.x +8 ,(int)p->CenterPoint.y +8);
}
 

void PaintSem( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
 	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	COLORREF  cr = GetBlackColor();
	if (   mPenSet.GetSolidPen(  2 , cr ) == NULL ) return ;

	COLORREF  crb = GetYellowColor();

	if (   p->ThisID == STATUS_SET_STOP ) crb  = GetRedColor();
	if (   p->ThisID == STATUS_SET_GO ) crb  = GetGreenColor();
 
	mPenSet.GetNewBrush( 1 ,   crb ) ;

	Ellipse( hdc, (int)p->CenterPoint.x-6 ,(int)p->CenterPoint.y-6 , (int)p->CenterPoint.x +6 ,(int)p->CenterPoint.y +6);
}
 
#include "TrainObjects.h"

void PaintSwitch( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc )
{
 	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);
	if (   mPenSet.GetSolidPen(  4 , GetBlueColor() ) == NULL ) return ;

	CObjBendRail *pb ;
	CObjRail *px = p->pRail ;

	if ( px == NULL ) pb = NULL;
	else pb = IsBendObject( px );
 
	if ( pb != NULL )
	{
		//mDebug.CDebugPut((char *)">>>>>SWITCH  ep:%d  " ,p->Turn );
		CLineObject  mLine( pb->GetPoint( p->Turn ) , pb->GetCenterPoint() );
		CLineObject  mLinePerp1( mLine.GetA() , mLine.GetB() , pb->GetPoint( p->Turn ) );
		CLineObject  mLinePerp( mLinePerp1.GetA() , mLinePerp1.GetB() , p->CenterPoint );
		CFPoint  cp1 = mLinePerp.GetCrossWithLine( mLinePerp1 );
		p->StartPoint = GetPointFmStart( p->CenterPoint , cp1   ,  -8);
		p->EndPoint   = GetPointFmStart( p->CenterPoint , cp1   ,  8 );
	}
	else
	{
		CLineObject  mLine( p->StartPoint ,  p->EndPoint  );
		CLineObject  mLinePerp( mLine.GetA() , mLine.GetB() , p->CenterPoint );
		CFPoint  cp1 = mLinePerp.GetCrossWithLine( mLine );
		p->StartPoint = GetPointFmStart( p->CenterPoint , cp1   ,  -8);
		p->EndPoint   = GetPointFmStart( p->CenterPoint , cp1   ,  8 );
	}


	if (   mPenSet.GetSolidPen(  4 , GetBlackColor() ) == NULL ) return ;  

	p->Width = 6;
	DrawBox(  p , DRAWLINES , hdc );

	//COLORREF cr = GetGreenColor();
	//if ( p->ThisID == STATUS_NOOPER ) cr = GetRedColor();

	if (   mPenSet.GetSolidPen(  2 , GetGreenColor() ) == NULL ) return ;

	CArrow mCArrow(  p->StartPoint ,  p->EndPoint , p->Width-2 );

	if ( p->ThisID != STATUS_NOOPER ) 
	     mCArrow.Swap();
 
	mCArrow.Draw( hdc );
}
 
 