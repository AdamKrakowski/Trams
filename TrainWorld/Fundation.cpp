
#include "stdafx.h"
//#include "MouseTest.h"

//#include "Windowsx.h"
#include "Math.h"
#include <stdio.h>
 
#include "StdTrainDef.h"


#include "Debug.h"
extern CDebug mDebug;


CSystem  mSystem;


 

CSystem::CSystem()
{
	m_LaunchRail = 1;
	m_SimShowRail = TRUE;
	m_SimTestMode = FALSE;
	m_SaveTrams= TRUE;
	m_schenable = FALSE;

	m_SimDivisor = 320 ;
	m_SimStep = 2;
	m_SimSpeed = 100; // timer interval
	m_LookBackDelay = 15;  // min
	m_SimSpeed = 1; // 100msec
	m_NightModeStarts = 23*60;

	m_SimTime = CTime( 2014,1,1, 4 ,30 ,0,0); 
	m_NewSimTime = CTime( 2014,1,1, 4 ,30 ,0,0); 
	m_TimeSpan = CTimeSpan( 0, 0 , 1 , 0 );

	m_SpeedIndexLimit1 = 250;
	m_SpeedIndexLimit2 = 500;

}

void CSystem::SystemErrorMessage( int i_err ) 
{
	char etext[256];
	etext[0]=0;
	switch (i_err)
	{
		case 0:
			break;
		default :
			sprintf_s(  etext,200, "Error:%d",i_err);
		break;
	}
//	SetWindowText( hwndButtonStatic , etext);
	system_error = i_err;
}

int CSystem::GetSystemError()
{
	return system_error;
}


void CSystem::Serialize(CArchive& ar)
{
 
	CString CVersion;

	if (ar.IsStoring())
	{
		CVersion=_T("SYS");
		ar <<	 CVersion;
		ar << 	m_SimTime;
		ar <<	m_NewSimTime;
		ar <<	m_TimeSpan;
		ar <<	m_LaunchRail ;
		ar <<	m_SimSpeed;
		ar <<	m_SimStep;
		ar <<	m_SimDivisor;
		ar <<   m_SimTestMode;
		ar <<	m_SimShowRail;
		ar <<   m_SaveTrams;
		ar <<	m_LookBackDelay;
		ar <<	m_NightModeStarts;
		ar <<   m_SpeedIndexLimit1;
		ar <<   m_SpeedIndexLimit2;
		ar <<   m_schenable;
		ar <<	m_Extra4;
		ar <<	m_Extra5;
		ar <<   m_Extra6;
		ar <<   m_Extra7;
		ar <<   m_Extra8;
	}
	else
	{
		ar >>	CVersion;
		ar >>	m_SimTime;
		ar >>	m_NewSimTime;
		ar >>	m_TimeSpan;
		ar >>	m_LaunchRail ;
		ar >>	m_SimSpeed;
		ar >>	m_SimStep;
		ar >>	m_SimDivisor;
		ar >>   m_SimTestMode;
		ar >>	m_SimShowRail;
		ar >>   m_SaveTrams;
		ar >>   m_LookBackDelay;
		ar >>	m_NightModeStarts;
		ar >>   m_SpeedIndexLimit1;
		ar >>   m_SpeedIndexLimit2;
		ar >>   m_schenable;
		ar >>	m_Extra4;
		ar >>	m_Extra5;
		ar >>   m_Extra6;
		ar >>   m_Extra7;
		ar >>   m_Extra8;
	}

}

////////////////////////////////////////////
//
//   Class CFPoint  floats as data members  
//
////////////////////////////////////////////

CFPoint::CFPoint() 
{
	x =0;y=0;
}

CFPoint	CFPoint::operator+(const CFPoint &second ) 
{
	CFPoint fp;
	fp.x = this->x + second.x;
	fp.y = this->y + second.y;
	return fp;
}

CFPoint	CFPoint::operator+=(const CFPoint &second) 
{
	x += second.x;
	y += second.y;
	return CFPoint(x,y);
}

CFPoint	CFPoint::operator-(const CFPoint &second) 
{
	CFPoint fp;
	fp.x = this->x - second.x;
	fp.y = this->y - second.y;
	return fp;
}

CFPoint	CFPoint::operator-=(const CFPoint &second) 
{
	x -= second.x;
	y -= second.y;
	return CFPoint(x,y);
}

CFPoint	CFPoint::Offset(  CPoint cp   ) 
{
	CFPoint fp;
	fp.x = (float)this->x - cp.x;
	fp.y = (float)this->y - cp.y;
	return fp;
}

CFPoint::CFPoint(float ix,float iy )
{
	x = ix ;y=iy;
}
CFPoint::CFPoint(int ix,int iy )
{
	x = (float)ix ;y=(float)iy;
}

CFPoint::CFPoint( CPoint cp )
{
  x = (float)cp.x; y = (float)cp.y;

}

CPoint CFPoint::Round()
{
	CPoint pt;
	pt.x = (int)roundToNearest(x);
	pt.y = (int)roundToNearest(y);
	return pt;
}

void  CFPoint::DrawCross( HDC hdc , int weight )
{
	CPoint tmp( (int) x , (int) y ); 
	DrawPointCross( tmp ,   hdc , GetWhiteColor() ,weight);
}

void  CFPoint::DrawPlus( HDC hdc , int weight )
{
	CPoint tmp( (int) x , (int) y ); 
	DrawPointPlus( tmp ,   hdc , GetWhiteColor() ,weight);
}

 void CFPoint::Serialize(CArchive& ar) 
 {
	if (ar.IsStoring())
	{
        ar <<   x;
        ar <<   y;
	}
	else
	{
        ar >>   x;
        ar >>   y;
	}
 }

 
/*
CArchive& CFPoint::operator<<(const CFPoint &second) 
{
	CArchive ar;
        ar <<   x;
        ar <<   y;
	return ar;
}
*/



////////////////////////////////////////////
//
//   convert from float to initer based point  
//
////////////////////////////////////////////
 
CMyPoint::CMyPoint( float fx , float fy) 
{
	CPoint::x = (int )roundToNearest(fx);
	CPoint::y = (int )roundToNearest(fy);
 
}

CMyPoint::CMyPoint( CFPoint fpt )
{
	CPoint::x = (int )roundToNearest(fpt.x);
	CPoint::y = (int )roundToNearest(fpt.y);
}

CMyPoint::CMyPoint( CPoint  pt )
{
	CPoint::x =  pt.x ;
	CPoint::y =  pt.y ;
}

////////////////////////////////////////////
//
//   convert from float to initer based point  
//
////////////////////////////////////////////


CMyRect::CMyRect( CRect rc) 
{
	mColour = RGB(0,0,0);
	mRc = rc;
	mRc.NormalizeRect();
	mPenFat = 3;
}

CMyRect::CMyRect( CFPoint p1 , CFPoint p2 )
{
	mColour = RGB(0,0,0);
	mRc = CRect( (int)p1.x, (int)p1.y , (int)p2.x , (int)p2.y );
	mRc.NormalizeRect();
	mPenFat = 3;
}

CMyRect::CMyRect( CPoint p1 , CPoint p2 )
{
	mColour = RGB(0,0,0);;
	mRc = CRect( p1,p2);
	mRc.NormalizeRect();
	mPenFat = 3;
}

CMyRect::CMyRect( CRect rc , COLORREF colour ) 
{
	mColour = colour;
	mRc = rc;
	mRc.NormalizeRect();
	mPenFat = 3;
}

CMyRect::CMyRect( CFPoint p1 , CFPoint p2, COLORREF colour )
{
	mColour = colour;
	mRc = CRect( (int)p1.x, (int)p1.y , (int)p2.x , (int)p2.y );
	mRc.NormalizeRect();
	mPenFat = 3;
}

CMyRect::CMyRect( CPoint p1 , CPoint p2 , COLORREF colour )
{
	mColour = colour;
	mRc = CRect( p1,p2);
	mRc.NormalizeRect();
	mPenFat = 3;
}

CMyRect::CMyRect( CRect rc , COLORREF colour , int fat)
{
	mColour = colour;
	mRc = rc;
	mRc.NormalizeRect();
	mPenFat = fat;
}

CMyRect::CMyRect( CFPoint p1 , CFPoint p2, COLORREF colour , int fat )
{
	mColour = colour;
	mRc = CRect( (int)p1.x, (int)p1.y , (int)p2.x , (int)p2.y );
	mRc.NormalizeRect();
	mPenFat = fat;
}

CMyRect::CMyRect( CPoint p1 , CPoint p2 , COLORREF colour , int fat)
{
	mColour = colour;
	mRc = CRect( p1,p2);
	mRc.NormalizeRect();
	mPenFat = fat;
}

void CMyRect::Draw( HDC hdc )
{
	HPEN pen;
	pen = CreatePen( PS_SOLID , mPenFat , mColour );
	HPEN oldpen = (HPEN)SelectObject( hdc , pen );	

	OnDrawRect( &mRc ,  hdc );

	SelectObject( hdc , oldpen );
	DeleteObject( pen );
}

 
////////////////////////////////////////////
//
//   Class CVector ( structure - int) 
//
////////////////////////////////////////////
 
CVector::CVector() 
{
}

CVector::CVector(CPoint start,CPoint end ) 
{
	mStart = start; mEnd = end;
}

CVector::CVector(CFPoint start,CFPoint end )
{
mStart.x =(int)start.x;
mStart.y =(int)start.y;
mEnd.x = (int)end.x;
mEnd.y = (int)end.y;
}

////////////////////////////////////////////
//
//   Class CFVector ( structure  - float ) 
//
////////////////////////////////////////////

CFVector::CFVector() 
{
}

CFVector::CFVector(CFPoint start,CFPoint end ) 
{
	mStart = start; mEnd = end;
}

CFVector::CFVector(CPoint start,CPoint end )
{
mStart.x = (float)start.x;
mStart.y = (float)start.y;
mEnd.x =  (float)end.x;
mEnd.y =  (float)end.y;
}

////////////////////////////////////////////
//
//   Class CSegment  
//
////////////////////////////////////////////

CSegment::CSegment() 
{
	 mStart = CFPoint(0,0);
	 mEnd = CFPoint(0,0);
}

CSegment::CSegment(CPoint start,CPoint end ) 
{
	 mStart = CFPoint(start.x,start.y) ;  mEnd = CFPoint(end.x,end.y);  
}

CSegment::CSegment(CFPoint start,CPoint end ) 
{
	mStart = start;
	mEnd = CFPoint(end.x,end.y);  
}

CSegment::CSegment(CFPoint start,CFPoint end )
{
mStart.x = start.x;
mStart.y = start.y;
mEnd.x =  end.x;
mEnd.y =  end.y;
}

void CSegment::DrawSegment( HDC hdc, int pen_w , COLORREF rf ) 
{
	HPEN pen;
	pen = CreatePen( PS_SOLID , pen_w , rf );
	HPEN oldpen = (HPEN)SelectObject( hdc , pen );
	
	MoveToEx(hdc ,   (int)roundToNearest(mStart.x )     , (int)roundToNearest(mStart.y )  ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  (int)roundToNearest(mEnd.x )    ,(int)roundToNearest( mEnd.y) );
 
	SelectObject( hdc , oldpen );
	DeleteObject( pen ); 
}

void CSegment::DrawSegment( HDC hdc  )
{
	MoveToEx(hdc ,   (int)roundToNearest(mStart.x )     , (int)roundToNearest(mStart.y )  ,    (LPPOINT) NULL); 
	LineTo(  hdc ,  (int)roundToNearest(mEnd.x )    ,(int)roundToNearest( mEnd.y) );
}


float CSegment::GetDistance( CFPoint point )
{
	PASSDATASTRUCT data;
	data.StartPoint = mStart  ;
	data.EndPoint = mEnd;
	
	CFPoint pf =CrossSegmentWithLinePerpendicular(   point , &data );
	if ( pf.x == 0 ) return 0;
	return ::GetDistance( pf,  point );
}


////////////////////////////////////////////
//
//   Class CTwoPoints  ( data structure to keep two points)  
//
////////////////////////////////////////////


CTwoPoints::CTwoPoints() 
{
	 mPoint1 =  CFPoint(0,0); mPoint2 = mPoint1;
}

CTwoPoints::CTwoPoints( CFPoint point1, CFPoint point2   ) 
{
	mPoint1 = point1; mPoint2 = point2;
}

////////////////////////////////////////////
//
//   Class CCircle  ( data structure + draw ))  
//
////////////////////////////////////////////


CCircle::CCircle() 
{
	mColour = GetGrayColor();
	mPenFat =1;
}

CCircle::CCircle( CFPoint center , float fradius ) 
{
	mCenter = center; mRadius = fradius;
}

void CCircle::SetColor( COLORREF rf ) 
{
   mColour = rf;
}

void CCircle::SetPen( int iwide, COLORREF rf )
{
   mColour = rf;
   mPenFat = iwide;
}

void CCircle::DrawCircle( HDC hdc  )
{
    CLineObject	mLineObject( 1.0 ,1.0 , mCenter );
	CTwoPoints tpo = ComputeIntersectionOfCircleAndLine( *this , mLineObject );

	float fStartAngle =	ComputeVectorAngle(  mCenter , tpo.mPoint1 ) ;

	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	if (   mPenSet.GetSolidPen(   mPenFat , mColour ) == NULL ) return ;

	MoveToEx(hdc,(int)tpo.mPoint1.x  ,(int)(int)tpo.mPoint1.y   ,(LPPOINT) NULL);
	AngleArc(hdc,(int)roundToNearest(mCenter.x), (int)roundToNearest(mCenter.y) , (int)roundToNearest( mRadius), fStartAngle ,   360 );
}


////////////////////////////////////////////
//
//   Class CArch  ( data structure + draw ))  
//
////////////////////////////////////////////

CArch::CArch() 
{
	mColour = GetGrayColor();
	mPenFat = 1;
	mDotted = FALSE;
}

// create arch with center & two diffrent points
CArch::CArch( CFPoint CenterPoint ,  CFPoint FirstPoint , CFPoint SecondPoint     ) 
{
	mCenterPoint = CenterPoint;  
	mFirstPoint  = FirstPoint ;
	mSecondPoint = SecondPoint ;
	mRadius = ::GetDistance( mCenterPoint  ,  mFirstPoint );
}
// option 0 /default // shorter arch always
void CArch::DrawArch(HDC hdc, int option ) 
{
	float fStartAngle =	ComputeVectorAngle(  mCenterPoint , mFirstPoint ) ;
	float fEndAngle =	ComputeVectorAngle(  mCenterPoint , mSecondPoint ) ;
	float fsweap =   fEndAngle -fStartAngle;
	mRadius = ::GetDistance( mCenterPoint  ,  mFirstPoint );
	 
	if ( fsweap < -180.0 ) fsweap += 360.0;
	else if ( fsweap > 180.0 ) fsweap -= 360.0;

	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	if ( mDotted == FALSE )
		if (   mPenSet.GetSolidPen(  mPenFat , mColour ) == NULL ) return ;
 	if ( mDotted == TRUE )
		if (   mPenSet.GetDottedPen( mColour ) == NULL ) return ;

	MoveToEx(hdc,(int)mFirstPoint.x  ,(int)(int)mFirstPoint.y  ,(LPPOINT) NULL);
	AngleArc(hdc,(int)roundToNearest(mCenterPoint.x), (int)roundToNearest(mCenterPoint.y) , (int)roundToNearest( mRadius),  fStartAngle ,   fsweap );
}

void CArch::SetColor( COLORREF rf ) 
{
   mColour = rf;
}

void CArch::SetWide( int iwide ) 
{
   mPenFat = iwide;
}

void CArch::SetPen( int iwide, COLORREF rf )
{
	mColour = rf;
	mPenFat = iwide;
	mDotted = FALSE;
}
 
void  CArch::SetPenDotted( int iwide, COLORREF rf ) 
{
   mColour = rf;
   mPenFat = iwide;
   mDotted = TRUE;
}


float CArch::GetDistance( CFPoint point)
{
	CLineObject mLine( point , mCenterPoint );
	CFPoint pf = this->CrossWithLine( mLine);  // check if the line crossing the arch
	if ( pf.x == 0.0)  return 0;  // not this time fro thi spoint
	return ::GetDistance( pf,  point );
}

float CArch::GetDistance( CPoint point)
{
	CLineObject mLine( point , mCenterPoint );
	CFPoint pf = this->CrossWithLine( mLine);
	if ( pf.x == 0.0)  return 0;
	return ::GetDistance( pf,  point );
}


CFPoint CArch::CrossWithLine( CLineObject line) 
{
	PASSDATASTRUCT data;
	data.CenterPoint = mCenterPoint;
	data.StartPoint = mFirstPoint ;
	data.EndPoint = mSecondPoint;
	return  CrossArchWithLine( line , &data ); 
}

////////////////////////////////////////////////////////////
//
//
////////////////////////////////////////////////////////////
 
CArrow::CArrow()
{
}

CArrow::CArrow(  CFPoint point1, CFPoint point2 , int width )
{ mPoint1 = point1; mPoint2 = point2;mWidth = width;}	

void  CArrow::Swap()
{
	CFPoint tp = mPoint1;
	mPoint1 = mPoint2;
	mPoint2 = tp;
}

void   CArrow::Draw( HDC hdc ) 
{
	CFPoint middle = GetCenterPoint( mPoint1 , mPoint2);

	CLineObject  mLine( mPoint1 , mPoint2  );
	CLineObject  mLinePerp( mLine.GetA() , mLine.GetB() , middle );
	CCircle  mCCircle( middle , (float)mWidth  ); 	
	CTwoPoints tp = ComputeIntersectionOfCircleAndLine( mCCircle , mLinePerp );

	if ( tp.result != 2 )
		return;


	MoveToEx(hdc ,   (int)roundToNearest( mPoint1.x  )     , (int)roundToNearest( mPoint1.y  )  ,    (LPPOINT) NULL); 

	LineTo(  hdc ,  (int)roundToNearest( tp.mPoint2.x  )    ,(int)roundToNearest( tp.mPoint2.y ) );
	LineTo(  hdc ,  (int)roundToNearest( tp.mPoint1.x  )    ,(int)roundToNearest( tp.mPoint1.y ) );
	LineTo(  hdc ,  (int)roundToNearest( mPoint1.x  )    ,(int)roundToNearest( mPoint1.y ) );
	LineTo(  hdc ,  (int)roundToNearest( mPoint2.x  )    ,(int)roundToNearest( mPoint2.y ) );
}

void   CArrow::Draw( HDC hdc , COLORREF rf ) 
{


}
 



////////////////////////////////////////////
//
//   Class CLineObject   
//
////////////////////////////////////////////

CLineObject::CLineObject()
{
	ACoeff=0;
	BCoeff=0;
	CCoeff=0;
}

CLineObject::CLineObject (CPoint FirstPoint,CPoint SecondPoint)
{
	LineFromPoints( FirstPoint, SecondPoint);
}

CLineObject::CLineObject( CFPoint FirstPoint,CFPoint SecondPoint )
{
    LineFromPoints( FirstPoint, SecondPoint);
}

CLineObject::CLineObject( double dACoeff,double dBCoeff ,double dCCoeff) 
{
	ACoeff=dACoeff;
	BCoeff=dBCoeff;
	CCoeff=dCCoeff;
}

CLineObject::CLineObject( double MCoeff ,double DCoeff  )
{
	ACoeff=-MCoeff;
	BCoeff=1;
	CCoeff=-DCoeff;
}

CLineObject::CLineObject( double ACoeff,double BCoeff ,CFPoint ThroughPoint)
{
	LinePenpendicularFromLineAndPoint( ACoeff,  BCoeff ,  ThroughPoint );
}

CLineObject::CLineObject( CLineObject mLine , CFPoint ThroughPoint )
{
	LinePenpendicularFromLineAndPoint( mLine.GetA(),  mLine.GetB(),  ThroughPoint );
}

double CLineObject::GetA()
{
	return ACoeff;
}
double CLineObject::GetB()
{
	return BCoeff;
}
double CLineObject::GetC()
{
	return CCoeff;
}

void CLineObject::LineFromPoints(CPoint FirstPoint,CPoint SecondPoint)
{	
    ACoeff = (double)(FirstPoint.y-SecondPoint.y);
    BCoeff = (double)(SecondPoint.x-FirstPoint.x);
	CCoeff = (double)(FirstPoint.y*( FirstPoint.x-SecondPoint.x)  + FirstPoint.x*( SecondPoint.y - FirstPoint.y)) ;
}

void CLineObject::LineFromPoints(CFPoint FirstPoint,CFPoint SecondPoint)
{	
    ACoeff = (double)(FirstPoint.y-SecondPoint.y);
    BCoeff = (double)(SecondPoint.x-FirstPoint.x);
	CCoeff = (double)(FirstPoint.y*( FirstPoint.x-SecondPoint.x)  + FirstPoint.x*( SecondPoint.y - FirstPoint.y)) ;
}


void CLineObject::LinePenpendicularFromLineAndPoint( double iACoeff,double iBCoeff ,CFPoint ThroughPoint)
{	
	BCoeff =   iACoeff;
	ACoeff = - iBCoeff;
	CCoeff =   -ACoeff*ThroughPoint.x - BCoeff*ThroughPoint.y;
}

void CLineObject::DrawLine( HDC hdc ,COLORREF rf  )
{	
	CFPoint fp1 = CFPoint(10,10) ;
	CFPoint fp2 = CFPoint( 2000 , 1200 ) ;
 
	if ( (int)this->GetB() == 0 )
	{
		if ( (int)this->GetA() != 0 )  
		{
			fp1.x = fp2.x = - (float)this->GetC()  /(float)this->GetA();
			fp1.y = 0;
			fp2.y = (float)1200 ;
		}
		else return ;
	}
	else
	{
		fp1.y = (float)((-this->GetA() * fp1.x - this->GetC()  ) /this->GetB());
		fp2.y = (float)((-this->GetA() * fp2.x - this->GetC()  ) /this->GetB());
	}

	CMyPoint pt1 = CMyPoint( fp1 ) ;
	CMyPoint pt2 = CMyPoint( fp2 ) ;

	HPEN pen;
	pen = CreatePen( PS_SOLID , 1 , rf);
	HPEN oldpen = (HPEN)SelectObject( hdc , pen );
	
	MoveToEx(hdc ,  pt1.x     , pt1.y,    (LPPOINT) NULL); 
	LineTo(  hdc ,  pt2.x     , pt2.y );
 
	SelectObject( hdc , oldpen );
	DeleteObject( pen ); 
}

float CLineObject::GetDistance( CFPoint mPoint) 
{
 
	
	double d=0;

	d = abs( ACoeff*mPoint.x + BCoeff*mPoint.y + CCoeff  )/sqrt( ACoeff*ACoeff + BCoeff*BCoeff );

	return (float)d;
}
float CLineObject::GetDistance( CPoint mPoint) 
{
	double d=0;

	d = abs( ACoeff*mPoint.x + BCoeff*mPoint.y + CCoeff  )/sqrt( ACoeff*ACoeff + BCoeff*BCoeff );

	return (float)d;

}

CFPoint CLineObject::GetCrossWithLine( CLineObject mLinePerp) 
{
	return   CrossOfTwoLines ( *this , mLinePerp ) ;
}

////////////////////////////////////////////
//
//   Class CPenStorage   
//
////////////////////////////////////////////

CPenStorage::CPenStorage()
{
	m_pen=NULL;
	m_oldpen=NULL;
	m_hdc = NULL;
	m_Pen_Error =0;
 
	m_brush =NULL;
	m_oldbrush = NULL;
}

CPenStorage::~CPenStorage()
{
	if ( m_hdc != NULL )
	{
		if ( m_oldpen != NULL)
			SelectObject( m_hdc , m_oldpen );

		if ( m_oldbrush != NULL)
			SelectObject( m_hdc , m_oldbrush );
	}

	if (m_pen !=NULL )
		DeleteObject( m_pen );

	if (m_brush !=NULL )
		DeleteObject( m_brush );

}

HBRUSH CPenStorage::GetNewBrush( int fnBrushStyle,   COLORREF crColor ) 
{
	if (m_brush != NULL )
	{
		if ( m_oldbrush != 0 )
			 SelectObject( m_hdc , m_oldbrush );
		DeleteObject( m_brush );
	}

	m_brush = CreateSolidBrush(crColor );  
	if ( m_brush == NULL ) 
	{
		m_Pen_Error = 1;
		//SystemErrorMessage( 1 );
	}
	else
	{
		HBRUSH tmpbr= (HBRUSH)SelectObject( m_hdc , m_brush );
		
		if ( m_oldbrush == 0 )  m_oldbrush = tmpbr ;
	}

	return m_brush;
}

HPEN CPenStorage::GetNewPen( int fnPenStyle, int nWidth, COLORREF crColor ) 
{
	
	if (m_pen != NULL )
	{
		if ( m_oldpen != 0 )
			 SelectObject( m_hdc , m_oldpen );
		DeleteObject( m_pen );
	}

	m_pen = CreatePen( fnPenStyle , nWidth, crColor );
	if ( m_pen == NULL ) 
	{
		m_Pen_Error = 1;
		//SystemErrorMessage( 1 );
	}
	else
	{
		HPEN tmppen = (HPEN)SelectObject( m_hdc , m_pen );
		
		if ( m_oldpen == 0 )  m_oldpen = tmppen ;
	}

	return m_pen;
}


HPEN  CPenStorage::GetPen(int fnPenStyle, int nWidth, COLORREF crColor)
{
	return GetNewPen(  fnPenStyle,   nWidth,   crColor ) ;
}

HPEN CPenStorage::GetDottedPen(COLORREF crColor)
{
	return GetNewPen( PS_DOT , 1 ,   crColor ) ;
}


HPEN CPenStorage::GetSolidPen( int nWidth, COLORREF crColor)
{
	return GetNewPen( PS_SOLID , nWidth ,   crColor ) ;
}
/*
HPEN CPenStorage::GetSlippersPen() 
{
	//return GetNewPen( PS_DOT , 1 ,  GetBraunColor() ) ;
}
*/
void CPenStorage::SetDC( HDC   hdc ) 
{
	m_hdc = hdc;
	//m_Pen_Handle = GetStockObject( BLACK_PEN );
}


////////////////////////////////////////////
//
//   Class CSystemState   
//
////////////////////////////////////////////
 
CSystemState::CSystemState()
{
	system_error =0;
}

void CSystemState::SystemErrorMessage( int i_err )
{
	system_error = i_err;
}

int CSystemState::GetSystemError() 
{
	return system_error;
}

 
 