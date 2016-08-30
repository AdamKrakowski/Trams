/////////////////////////////////////
//
//
//   standard definitionfor train application
//
//
////////////////////////////////////
// #include "StdTrainDef.h"

#pragma once


// painting options

#define  SINGLELINE  0x0001
#define  DOUBLELINE  0x0002
#define  DRAWLINES   0x0004
#define  SWITCHOFF   0x0008 
#define  TESTMODE    0x0010     // draw all the endpoint  - normally only not connected
#define  TMPDRAWLINES   0x0020
#define  SELECTEDLINE   0x0040
#define   MODIBEND   0x0080 
#define   UNDERGND   0x0100 

#define  TUNDERGND   0x0080 
#define  FRONT_SHD   0x0100
#define  BACK_SHD    0x0200
#define  FRONT_DRW   0x0400
#define  BACK_DRW    0x0800
#define  BODY_GREEN  0x1000
#define  BODY_RED    0x2000
#define  BODY_YELLOW 0x4000
#define  BODY_LBLUE  0x8000

#define  TMP_COLOR_RED 0x1000
#define  TMP_COLOR_BLUE 0x2000

// double lines distance
#define RailWidth1024  3
#define RailWidth2048  6

#define RAILWIDTH RailWidth2048


#define  STATUS_NOOPER  0
#define  STATUS_SET     1

#define  STATUS_SET_STOP   2
#define  STATUS_SET_GO   3
#define  STATUS_SET_YELLOW   4


#define  CLEAR_REF   0
#define  SET_REF   1

// Messages
#define  CLOSE_DIALOG_SWITCH  1
#define  ENABLE_TESTMODE 2
#define  TOGGLE_CONTROL 3
#define  SWAP_SWITCHRAILS 4
#define  INVALIDATE_MAIN 5

#define  CLOSE_DIALOG_SEM  11
#define  CLOSE_DIALOG_STOP  12
#define  CLOSE_DIALOG_RAIL  13
#define  CLOSE_DIALOG_TRAMS  14
#define  CLOSE_DIALOG_STOPS  15

// constants
#define PI  3.14159265358979323846
#define PI180  0.0174532925199433
#define C180PI 57.2957795 

//   system definitions
//  object types

#define		ObjNothing				0
#define	 	ObjStraightRail			1
#define	 	ObjBendRightRail		2
#define	 	ObjBendLeftRail			3
#define	 	ObjStraightDblRail		4 
#define	 	ObjRailEnd				5
#define	 	ObjRailControl			6 
#define	 	ObjTrain				7
#define	 	ObjSwitch			  	8
#define	 	ObjCntDis    			9
#define	 	ObjTracker    			10
#define	 	ObjStop	    			11
#define	 	ObjSem	    			12
 
// dymamincs route state
#define		DirUndef				0
#define		DirInit					1
#define		DirForService			2
#define		DirFrmService			3
#define		DirInService			4

// dynamics for train
#define		StateUndef				0
#define		StateRUN				1
#define		StateSTOP				0
// stop reasom
#define		StopUndef 				0
#define		StopDet					1
#define		SwitchDet				2
#define		SemaphoreDet			3
#define		ObjDet					4
#define		WaitSet					5

/////////////////////////////////////////////////////
///
///		Base classses functions
///
////////////////////////////////////////////////////


  
 class CSystemState
{
public:
	CSystemState();
	virtual void SystemErrorMessage( int i_err );
	virtual int GetSystemError();
	int system_error;
};

 //  system class
class CSystem : public CSystemState
{
	public:
	CSystem();
	void SystemErrorMessage( int i_err );
	int GetSystemError();
	void  Serialize(CArchive& ar);

//protected:
	CTime m_NewSimTime;
	CTime m_SimTime;  // we save this 
	CTimeSpan m_TimeSpan;
	int  m_LaunchRail ;
	int  m_SimSpeed;
	int  m_SimDivisor;
	int  m_SimStep;
	BOOL  m_SimTestMode;
	BOOL  m_SimShowRail;
	BOOL  m_SaveTrams;
	int  m_LookBackDelay;
	int  m_NightModeStarts;
	int  m_SpeedIndexLimit1;
	int  m_SpeedIndexLimit2;
	int  m_schenable;
	int  m_Extra4;
	int  m_Extra5;
	int  m_Extra6;
	int  m_Extra7;
	int  m_Extra8;

};

 
//CArchive& AFXAPI operator<<(CArchive& ar, CTimeSpan dateSpanSrc);

 class CFPoint 
{

public:
	CFPoint::CFPoint();
	CFPoint::CFPoint(float ix,float iy);
	CFPoint::CFPoint(int ix,int iy);
    CFPoint::CFPoint(CPoint cp);
	CFPoint Offset(  CPoint cp  );
	void  DrawCross( HDC hdc , int weight );
	void  DrawPlus( HDC hdc , int weight );
	CFPoint operator+(const CFPoint &second );
	CFPoint operator-(const CFPoint &second);
	CFPoint operator+=(const CFPoint &second);
	CFPoint operator-=(const CFPoint &second);
	void Serialize(CArchive& ar);
	CPoint Round();
	float x;
	float y;

	CArchive& operator<<(const CFPoint &fpt );

};


class CMyPoint  : public CPoint
{
public:
	CMyPoint( float x , float y);
	CMyPoint( CFPoint fpt );
	CMyPoint( CPoint  pt );
	// void Draw( HDC hdc );
	// COLORREF mColour;
	// int  mPenFat;
	// CPoint mpt
};


class CMyRect  : public CRect
{
public:
	CMyRect( CRect rc);
	CMyRect( CFPoint p1 , CFPoint p2 );
	CMyRect( CPoint p1 , CPoint p2 );
	CMyRect( CRect rc , COLORREF colour );
	CMyRect( CFPoint p1 , CFPoint p2, COLORREF colour );
	CMyRect( CPoint p1 , CPoint p2 , COLORREF colour );
	CMyRect( CRect rc , COLORREF colour , int fat);
	CMyRect( CFPoint p1 , CFPoint p2, COLORREF colour , int fat );
	CMyRect( CPoint p1 , CPoint p2 , COLORREF colour , int fat);
	void Draw( HDC hdc ); 
protected:
	COLORREF mColour;
	CRect mRc;
	int  mPenFat;
};

 

class CVector 
{
public:
	CVector();
	CVector(CPoint start,CPoint End );
	CVector(CFPoint start,CFPoint End );
	CPoint mStart;
	CPoint mEnd;
};

class CFVector 
{
public:
	CFVector();
	CFVector(CPoint start,CPoint End );
	CFVector(CFPoint start,CFPoint End );
	CFPoint mStart;
	CFPoint mEnd;
};

class CSegment 
{
public:
	CSegment();
	CSegment(CPoint start,CPoint End );
	CSegment(CFPoint start,CFPoint End );
	CSegment(CFPoint start,CPoint End );
	void DrawSegment( HDC hdc,  int pen_w , COLORREF rf ); 
	void DrawSegment( HDC hdc  ); 
	float GetDistance( CFPoint point);
	CFPoint mStart;
	CFPoint mEnd;
};


class CCircle 
{
public:
	CCircle();
	CCircle( CFPoint center , float fradius  );
	void DrawCircle( HDC hdc  );
	void SetColor( COLORREF rf );
	void SetPen( int iwide, COLORREF rf );
public:	
	CFPoint mCenter;
	float  mRadius;
protected:
	COLORREF mColour;
	int  mPenFat;
};

class CLineObject;

class CArch 
{
public:
	CArch();
	CArch( CFPoint CenterPoint ,  CFPoint FirstPoint , CFPoint mSecondPoint    );
	void DrawArch( HDC hdc, int option );
	void SetColor(COLORREF rf);
	void SetWide(int wide);
	void SetPen( int iwide, COLORREF rf );
	void SetPenDotted( int iwide, COLORREF rf );

	float GetDistance( CFPoint point);  // new 
	float GetDistance( CPoint point);   // new
	CFPoint CrossWithLine( CLineObject line);  // new

protected:
	CFPoint mCenterPoint;
	CFPoint mFirstPoint;
	CFPoint mSecondPoint;
	float  mRadius;
	COLORREF mColour;
	int mPenFat;
	BOOL mDotted;
};

class CTwoPoints
{
public:
	CTwoPoints();
	CTwoPoints(  CFPoint point1, CFPoint point2  );
	CFPoint mPoint1;
	CFPoint mPoint2;
	int  result;
};


class CArrow
{
public:
	CArrow();
	CArrow(  CFPoint point1, CFPoint point2 , int width );
	void   Draw( HDC hdc );
	void   Draw( HDC hdc , COLORREF rf );
	void   Swap();
	CFPoint mPoint1;
	CFPoint mPoint2;
	int  mWidth;
	//int  result;
};

 
class CLineObject
{
public:
	CLineObject();
	CLineObject( CPoint FirstPoint,CPoint SecondPoint );
	CLineObject( CFPoint FirstPoint,CFPoint SecondPoint );
	CLineObject( double ACoeff,double BCoeff ,CFPoint ThroughPoint);
	CLineObject( CLineObject mLine  ,CFPoint ThroughPoint);
	CLineObject( double dACoeff,double dBCoeff ,double dCCoeff) ;
	CLineObject( double MCoeff ,double DCoeff  );
	void LineFromPoints(CPoint FirstPoint,CPoint SecondPoint);
	void LineFromPoints(CFPoint FirstPoint,CFPoint SecondPoint);
	void LinePenpendicularFromLineAndPoint( double ACoeff,double BCoeff ,CFPoint ThroughPoint);
	void   DrawLine( HDC hdc ,COLORREF rf );
	double GetA();
	double GetB();
	double GetC();
	float GetDistance( CFPoint point);
	float GetDistance( CPoint point);
	CFPoint GetCrossWithLine( CLineObject point);
private:
	double ACoeff;
	double BCoeff;
	double CCoeff;
};

 class CPenStorage
{
public:
	CPenStorage();
	~CPenStorage();
	HPEN GetPen(int fnPenStyle, int nWidth, COLORREF crColor);
	HPEN GetDottedPen(COLORREF crColor);
	HPEN GetSolidPen( int nWidth, COLORREF crColor);
	HPEN GetSlippersPen(); 
	HBRUSH GetNewBrush( int fnBrushStyle,   COLORREF crColor ) ;
	void SetDC( HDC   hdc );
	HPEN m_pen;
	HPEN m_oldpen;
	HBRUSH m_brush;
	HBRUSH m_oldbrush;
	HDC  m_hdc;
	int  m_Pen_Error;
private:
	HPEN GetNewPen( int fnPenStyle, int nWidth, COLORREF crColor );
}; 

#define MAX_PTS  6
#define MAX_REC  4
#define MAX_SEG  6
 
 // implemented in DebugGraphics.cpp

 class CDebugGraphics
{
public:
	CDebugGraphics();
	~CDebugGraphics();

	void ResetStorage();
	 
	void AddPoint(CPoint pt);
	void AddPoint(CFPoint ptf);
	void AddSegment( CRect rc);
	void AddSegment( CPoint pt1 ,CPoint pt2);
	void AddSegment( CFPoint ptf1 ,CFPoint ptf2);
	void AddRect( CRect rc);
	void AddRect( CPoint pt1 ,CPoint pt2 );
	void AddRect( CFPoint ptf1 ,CFPoint ptf2 );

	void AddPoint(COLORREF crColor,CPoint pt);
	void AddPoint(COLORREF crColor,CFPoint ptf);
	void AddSegment(COLORREF crColor, CRect rc);
	void AddSegment(COLORREF crColor, CPoint pt1 ,CPoint pt2);
	void AddSegment(COLORREF crColor, CFPoint ptf1 ,CFPoint ptf2);
	void AddRect(COLORREF crColor, CRect rc);
	void AddRect(COLORREF crColor, CPoint pt1 ,CPoint pt2 );
	void AddRect(COLORREF crColor, CFPoint ptf1 ,CFPoint ptf2 );

	void Invalidate( int offset , CRect rc );
	void Draw( HDC   hdc	, CPoint offset , CRect rc  );
	BOOL IsGraphicsEnabled();
	void EnableGraphics( BOOL enable );

private:
 
	int mGraphicModeEnable;
	int mNbrOfPoint;
	int nNbrOfSegments;
	int nNmrOfRectangles;
	CPoint mtPts[MAX_PTS];
	COLORREF mtPtsColor[MAX_PTS];
	CRect  mtSeg[MAX_SEG];
	COLORREF mtSegColor[MAX_SEG];
	CRect  mtRec[MAX_REC];
	COLORREF mtRecColor[MAX_REC];
}; 


/////////////////////////////////////////////////////
///
///	Global structures definition
///
///
////////////////////////////////////////////////////


class CObjRail;
 
typedef struct {
	CFPoint StartPoint;     // mouse hit location
	CFPoint EndPoint;       // mouse move to/release location
	int mResourceId;
	HBITMAP bmpHandle;
	int mType;
//	SIZE sz;
 //	CObjRail	*mHeadPointer;     //  pointer to the element where head  cars are on [0]
 //	CObjRail	*mTailPointer;     //  pointer to the element where trail cars are on [1]
//	int     OnTheBend[2];
//	int    mRailHeadDir;         // direction of the head axis  (-1)  - fm 1to0  (1)  from 0 --> 1
//	int    mRailTailDir;         // direction of the trail axis  !!!!!! OBSOLITE  mDrawData.Turn !!!!!!!
	int    mVagonDir;            // is  vagon moving forward or bacward   <-  H====T  ->  mDrawData show s the same
//	WORD   mHeadHandle;			// if <> 0   the connected to other vagon
//	WORD   mTailHandle;			// if <> 0   the connected to other vagon
 	float   mInitialLenght;
//	float   mCorrection;
}   DRAWVAGONDATASTRUCT;
 

typedef struct {
	CFPoint StartPoint;     // mouse hit location
	CFPoint EndPoint;       // mouse move to/release location
	CFPoint CenterPoint;
	float   Radius;
	int    Width;
    int    Turn;
	float  mStartAngle;
	float  mSweepAngle;
	CRect  mUpdRect;
	WORD   ThisID;
	WORD   ConnID[3];
	int   m_Connections[4];
	CObjRail *pRail;

	DRAWVAGONDATASTRUCT *pVagonData;
}   DRAWDATASTRUCT;

typedef struct {
	CFPoint StartPoint;     // mouse hit location
	CFPoint EndPoint;       // mouse move to/release location
	CFPoint CenterPoint;
}   PASSDATASTRUCT;

 
typedef struct {
	int     mtype;
	float   Radius;
	int     Width;
	int     Lenght;
	int     iResBitmap;
	WORD    Turn;
	WORD    tType;
	float  mStartAngle;
	float  mSweepAngle;
	HANDLE  bmHandle;
}   TMPOBJECT_DRAWDATASTRUCT;


class CTrainVagon;
 

class CTramModelDef
{
	public:	
	int len;
	int width;
	DWORD style;
};


/////////////////////////////////////////////////////
///
///		WinAPi Functions
///
///
////////////////////////////////////////////////////

 
 void SystemErrorMessage( int i_err );
 int  GetSystemError();

  //  int PointInsideTheRect( CPoint cp , CRect rc ) ;
 //  int PointInsideTheRect( CFPoint cp , CRect rc ) ;

/////////////////////////////////////////////////////
///
///		Graphics functions
///
///
////////////////////////////////////////////////////


void OnDrawBgn( HWND hWnd , HDC hdc );

//  Public colours definition

COLORREF GetBlackColor();
COLORREF GetGrayColor();
COLORREF GetRedColor();
COLORREF GetBlueColor();

COLORREF GetBlueDarkColor();
COLORREF GetRedDarkColor();
COLORREF GetWhiteColor();
COLORREF GetBraunColor();
COLORREF GetDarkYellowColor();
COLORREF GetYellowColor();


// Public to draw cross marks (+, x) for CPOint or extended CFPoint (float)

void DrawPointPlus( CPoint cp , HDC hdc , COLORREF clr , int weight);
void DrawPointCross( CPoint cp , HDC hdc , COLORREF clr , int weight);

void DrawPointPlus( CFPoint cp , HDC hdc , COLORREF clr , int weight) ;
void DrawPointCross( CFPoint cp , HDC hdc , COLORREF clr , int weight); 
 
// Draw rectangle

void OnDrawRect( CRect  *srect , HDC hdc );
void DrawRectTilted( CPoint p1, CPoint p2, CPoint p3, CPoint p4  , HDC hdc );

//  to draw basic  primitives
void PaintBendRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc );
void PaintStraightRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc );
void PaintRailSwitch( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc );
void PaintEndRail( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc  );

void PaintTrain( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc  );
void PaintTrainBitmap( CFPoint StartPoint,CFPoint EndPoint,HBITMAP bmpExercising , HDC hdc );

void PaintSem( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc );
void PaintStop( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc ); 
void PaintSwitch( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc );
void PaintControl( DRAWDATASTRUCT *p, DWORD mode ,  HDC hdc );

void ComputeBandingRectBend( DRAWDATASTRUCT *p  );
void ComputeBandingRectTrain( DRAWDATASTRUCT *p  ); 
void ComputeBandingRectStright( DRAWDATASTRUCT *p  ); 
void ComputeBandingRectStop( DRAWDATASTRUCT *p  );
void ComputeBandingRectSwitch( DRAWDATASTRUCT *p  );
void ComputeBandingRectControl( DRAWDATASTRUCT *p  );


CFPoint  AdjustBendCenterPoint(  CPoint StartPoint , CPoint EndPoint , CFPoint m_currentCenter );
 
 
/////////////////////////////////////////////////////
///
///		Math functions
///
///
////////////////////////////////////////////////////


double roundToNearest(double num); 

int GetLowestValue( int *table, int size );
int GetHighestValue( int *table, int size );
int GetTheOtherPointIndex( int index , int iret);
int GetTheOtherPointIndex( int index  );
// frist two defines segment  the third is the point to check - assuming ThePoint is on the segment 
int IsPoinInsideSegment(CFPoint StartPoint , CFPoint EndPoint ,CFPoint ThePoint); 
//int IsPointOnTheCycle(CFPoint CnterPoint , float radius , CFPoint ThePoint); 
//int IsPointOnTheCycle( CFPoint StartPoint , CFPoint EndPoint,  CFPoint CnterPoint , float radius , CFPoint ThePoint) ;
int IsPointOnTheSegment( CFPoint StartPoint , CFPoint EndPoint ,CFPoint ThePoint);
int IsPointOnTheArch( CFPoint StartPoint , CFPoint EndPoint,  CFPoint CnterPoint ,  CFPoint ThePoint) ;

float LtoAngle(float shiftlinear, DRAWDATASTRUCT *pdd  );

CFPoint GetCenterPoint( CFPoint StartPoint , CFPoint EndPoint  );
CPoint   GetMidlePoint( CPoint StartPoint , CPoint EndPoint  );
//    >------------x-----------+
//   start        end         result ( distance from start to result point - could be negative )
CFPoint GetPointFmStart(  CFPoint StartPoint,CFPoint EndPoint, float distance );
//    >------------x-----------+
//   start        end         result ( distance from start to result point - could be negative )
CFPoint GetPointFmStartBend(  CFPoint StartPoint,CFPoint EndPoint, DRAWDATASTRUCT *pdd ,float distance );
CFPoint GetPointFmStart(  CFPoint StartPoint,CFPoint EndPoint,float distance ,DRAWDATASTRUCT *pdd );
float	GetDistance( CFPoint StartPoint , CFPoint EndPoint  );
float	GetDistance( CFPoint  mstartpoint , CFPoint EndPoint  , DRAWDATASTRUCT *pdd  ) ;

float	GetDistanceLineToPoint( CFPoint  mstartpoint , CFPoint EndPoint  ,  CFPoint  mPoint   ) ;

float	GetDistanceAngle( CFPoint  mstartpoint , DRAWDATASTRUCT *pdd , CFPoint  mpoint ) ;
float   GetDistanceBtwTwoLines( CFPoint StartPoint1 , CFPoint EndPoint1 , CFPoint StartPoint2 , CFPoint EndPoint2 ) ;
CFPoint ComputeTwoParLines( CFPoint SPoint ,CFPoint EPoint , float disp , int point_index ); 
void DrawTwoParLines( CPoint SPoint ,CPoint EPoint , int disp, HDC hdc ) ;
// verified up to 20140718
float	ComputeVectorAngle( CFPoint startPoint , CFPoint endPoint ) ;
// verified up to 20140718
CFPoint fCrossOfTwoVectors ( CVector vFirst ,CVector vSecond );
// Basic math
CFPoint   CrossOfTwoLines ( CLineObject  mLineMath1 , CLineObject  mLineMath2 ) ;
//   (0,0 ) if the line do not cross the arch defined by two points & center
CFPoint  CrossArchWithLine( CLineObject line , PASSDATASTRUCT *pdata ) ;
// (0,0 ) if the line do not cross the arch defined by two points & center
CFPoint  CrossArchWithLinePerpendicular( CFPoint point , PASSDATASTRUCT *pdata ) ;
//   (0,0 ) if the line do not cross the arch defined by two points & center
CFPoint  CrossSegmentWithLinePerpendicular( CFPoint point , PASSDATASTRUCT *pdata ) ;
// verified 20140718 
CFPoint ComputePointFromLinePointOriginExt ( CLineObject mLine  , CFPoint  CenterPoint , float  fRadius , int idir );
// verified up to 20140718
class CObjBendRail;
class CObjRail;

float  GetAbsAngleOfTwoVectors ( float a1, float a2 );
float  GetAbsAngleOfTwoVectors ( CVector vFirst ,CVector vSecond );
float  GetAbsAngleOfTwoVectors ( CFPoint StartPoint1 ,CFPoint EndPoint1  ,CFPoint StartPoint2 ,CFPoint EndPoint2 );
float	GetDistanceBend( CObjBendRail *p    ) ;
float	GetDistance(  CObjBendRail *p   , int sep ,  CFPoint mEndPoint  ) ;
CFPoint GetPointFmStartStright(  CObjRail *p , int ep1  ,float distance   ) ;
CFPoint GetPointFmStartBend(  CObjBendRail *p , int epfm  ,float distance  );
 




// angle betwean one common point & ywo others
float  GetAngleOfTwoVectors ( CFPoint StartPoint  , CFPoint EndPoint1 ,CFPoint EndPoint2 );
// obsolite as we cen get it directly from GetPoint - index 5
CFPoint ComputeBendExtendedPoint ( CFPoint  CenterPoint , CFPoint  MidleEndPoint , CFPoint OtherEndPoint);
// verified 20140718
CFPoint ComputeCenterPoint( CFPoint StartPoint ,CFPoint EndPoint , CFPoint ExtPoint, float iRadius  )  ;
// verified 20140718
CFPoint ComputeExtendedLinePoint( CFPoint CenterPoint ,CFPoint StartPoint , CFPoint EndPoint );
//  new 20140724					*
//									|
//    >------------x----------------+
//									|
//									*
//   StartPoint        EndPoint         result ( distance from start to result point - could be negative but zero )
CSegment ComputeSectionPependicularAtPoint( CFPoint StartPoint ,CFPoint EndPoint ,float distance,float lenght);
//  Same as above but also  allows 0 - offset
CSegment ComputeSectionPependicularAtPointExt( CFPoint StartPoint ,CFPoint EndPoint ,float offset ,float lenght); 
//  Get  point on the line closest to the ExtPoint
//						x ExtPoint
//	StartPoint			|
//     x----------------X-----------x EndPoint
//						| X = point returned
//						|
CFPoint GetPointAtTheLine (  CFPoint StartPoint ,CFPoint EndPoint , CFPoint ExtPoint );

CTwoPoints  ComputeIntersectionOfTwoCircles(CCircle  c1 , CCircle c2  );
CTwoPoints  ComputeIntersectionOfCircleAndLine(CCircle  c1 , CLineObject l1 );
CTwoPoints  ComputeIntersectionOfCircleAndSegment(CCircle  c1 , CFPoint StartPoint,CFPoint EndPoint  );
CTwoPoints  ComputeIntersectionOfCircleAndSegment( CFPoint CenterPoint , float Radius , CFPoint StartPoint,CFPoint EndPoint  );
CTwoPoints  ComputeIntersectionOfCircleAndCircleSegment( CCircle  c1 , CCircle  c2 , CFPoint StartPoint,CFPoint EndPoint  );
 
CTwoPoints  ComputeParSectionOfTheLenght( CFPoint p0, CFPoint p1, float d , float d1);

CFPoint  OffsetFPoint ( CFPoint data , CPoint cp );
CPoint  OffsetFPoint ( CPoint data , CPoint cp );
 

 