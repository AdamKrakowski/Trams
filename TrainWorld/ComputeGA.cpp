
#include "stdafx.h"
//#include "MouseTest.h"

#include "Windowsx.h"
#include "Math.h"
#include <stdio.h>

#include "StdTrainDef.h"

#include "DrawTmpObject.h"

#include "TrainObjects.h"

// independent module
#include "Debug.h"
extern CDebug mDebug;


 


double roundToNearest(double num) {
    return (num > 0.0) ? floor(num + 0.5) : ceil(num - 0.5);
}


int GetTheOtherPointIndex( int index  )
{
	if ( index == 0 ) return 1;
	else return 0;
}

// int GetTheOtherPointIndex( 0 ,  iret)

int GetTheOtherPointIndex( int index , int iret)
{
	if ( index == 0 ) return iret;
	else return 0;
}


int GetLowestValue( int *table, int size )
{
  int highest= 100000;
  int i;

  for ( i=0;i < size;i++)
	  if ( table[i] < highest ) highest =  table[i] ;

  return highest;
}

int GetHighestValue( int *table, int size )
{
  int lowest = -100000;
  int i;

  for ( i=0;i < size;i++)
	  if ( table[i] > lowest )   lowest = table[i] ;


  return lowest;
}

 
CFPoint  OffsetFPoint ( CFPoint data , CPoint cp )
{
	CFPoint fp;
	fp.x = (float)data.x - cp.x;
	fp.y = (float)data.y - cp.y;
	return fp;
}

CPoint  OffsetFPoint ( CPoint data , CPoint cp )
{
	CPoint fp;
	fp.x =  data.x - cp.x;
	fp.y =  data.y - cp.y;
	return fp;
}


int IsPoinInsideSegment(CFPoint StartPoint , CFPoint EndPoint ,CFPoint ThePoint)
{
	float d = GetDistance(StartPoint,EndPoint);
	if ( (GetDistance(StartPoint,ThePoint)  < d ) && (GetDistance(EndPoint,ThePoint)  < d )) return 1;
	return 0;
}

 
int IsPointOnTheArch( CFPoint StartPoint , CFPoint EndPoint,  CFPoint CnterPoint ,  CFPoint ThePoint) 
{
   float d = GetDistance( CnterPoint, ThePoint ); 
   //  get avarage of the two pints distance
   float fradius = ( GetDistance(CnterPoint ,StartPoint  ) + GetDistance( CnterPoint ,  EndPoint  ))/2 ;

   if ( abs(d - fradius) < 1.6 )  // check radius first 
   { 
	   float a1 = GetAbsAngleOfTwoVectors ( CnterPoint , StartPoint , CnterPoint ,ThePoint );  //  
	   float a2 = GetAbsAngleOfTwoVectors ( CnterPoint , EndPoint , CnterPoint ,ThePoint );	    //
	   float a3 = GetAbsAngleOfTwoVectors ( CnterPoint , EndPoint , CnterPoint ,StartPoint );	//  the angle less than 180  always returned
	   if (  abs((a1+a2) - a3) < 2.8) return 1;
	   else return -1;
   }
   return -2;
}

////////////////////////////////////////////////////////////////////////////
//
//  sp - the  & ep the must be close to 180 to be valid 
//  need addtional if is inside the arch
///////////////////////////////////////////////////////////////////////////

int IsPointOnTheSegment( CFPoint StartPoint , CFPoint EndPoint ,CFPoint ThePoint)
{

	if ( GetAbsAngleOfTwoVectors( StartPoint , ThePoint , ThePoint ,EndPoint ) > 10.0 ) 
		return -1;  // risk avaidance  SP X---->X----->X EP
 
	if ( GetDistanceLineToPoint( StartPoint , EndPoint , ThePoint ) > 3.0 ) 	return -2;
	
	return 1;
}

 
//  get the crossing point of line and arch
//


CFPoint  CrossArchWithLine( CLineObject line , PASSDATASTRUCT *pdata ) 
{
	// create the circe radius of  ::GetDistance( mCenterPoint,mFirstPoint  ) 
	CCircle mCicle( pdata->CenterPoint , ::GetDistance( pdata->CenterPoint , pdata->StartPoint  )   );
	// check intersetion of the circle with the line from center to the point selected
	CTwoPoints tp =  ComputeIntersectionOfCircleAndLine( mCicle , line );
	// get distance of the two point segment  (Start & stop points )
	float d =  ::GetDistance( pdata->StartPoint , pdata->EndPoint  );	
	CLineObject mLine1( pdata->StartPoint , pdata->EndPoint  );
	// create the two point segment line
	CLineObject mLine2( tp.mPoint2 , tp.mPoint1 );
	//  take the projection of the center  onto main segment laying in betwean of Start & stop points
	CFPoint  pf1 =  CrossOfTwoLines ( mLine1 , mLine2) ;
    // get distance to those point
	//     /-----d1-----//-----d2-----/
	//     /-----------d--------------/
	float d1 = ::GetDistance( pdata->StartPoint , pf1  );	
 	float d2 = ::GetDistance( pdata->EndPoint , pf1  );	
	//  verify if betwean the point - precise tune here
	if ( abs( d1+d2 - d ) < (float)1.2 )  
	{  // valid point - cos must return but which one ?
		float a =  GetAngleOfTwoVectors ( pdata->CenterPoint  ,  pf1  ,tp.mPoint1  );
		if ( abs(a) < 45 )  return tp.mPoint1 ;
		a =  GetAngleOfTwoVectors ( pdata->CenterPoint  ,  pf1  ,tp.mPoint2  );
		if ( abs(a) < 45 )  return tp.mPoint2 ;
		return CFPoint( 0,0);  // should not get here
	}
	return CFPoint( 0,0);  // outside of the segment
}


CFPoint  CrossArchWithLinePerpendicular( CFPoint point , PASSDATASTRUCT *pdata ) 
{
	CLineObject mLine( point , pdata->CenterPoint );
	return  CrossArchWithLine( mLine , pdata  ); 
}

CFPoint  CrossSegmentWithLinePerpendicular( CFPoint point , PASSDATASTRUCT *pdata ) 
{
	CLineObject mLine( pdata->StartPoint , pdata->EndPoint  );  // line containing the segment - line segment
	CLineObject pLine ( mLine ,point);  // line perpendicular to  - crossing the validated point
	CFPoint pf = mLine.GetCrossWithLine( pLine );  // projection of the validate point onto line segment
	float d1 = ::GetDistance( pdata->StartPoint , pf   );	
 	float d2 = ::GetDistance( pdata->EndPoint, pf   );	
	float d =  ::GetDistance( pdata->StartPoint , pdata->EndPoint  );	
	// if the distance matches then the point is in betwean
	if ( abs( d1 + d2 - d ) < (float)1.5 )  return  pf;
	return CFPoint(0,0);
}

CTwoPoints  ComputeIntersectionOfTwoCircles(CCircle  c1 , CCircle c2  )
{
	CTwoPoints  tpc( CFPoint(-1,-1),CFPoint(-1,-1) );
	tpc.result = 0;

	float D = sqrt( (c1.mCenter.x-c2.mCenter.x )*(c1.mCenter.x-c2.mCenter.x ) + (c1.mCenter.y-c2.mCenter.y  )*(c1.mCenter.y-c2.mCenter.y) );

	if (  ( c1.mRadius+c2.mRadius)  < D  ) 
		{
			tpc.result = -1;
			return tpc;
		}

	if (  abs( c1.mRadius-c2.mRadius)  > D  )
		{
			tpc.result = -2;	
			return tpc;
		}

	if (  ( abs(c1.mRadius+c2.mRadius)-D) < 0.000000001  ) 
		{
			tpc.mPoint1.x = (c2.mCenter.x - c1.mCenter.x)/2;
			tpc.mPoint1.y = (c2.mCenter.y - c1.mCenter.y)/2;
			tpc.result = 1;
			return tpc;
		}

	double d1 = (double)(D+c1.mRadius+c2.mRadius);
	double d2 = (double)(D+c1.mRadius-c2.mRadius);
	double d3 = (double)(D-c1.mRadius+c2.mRadius);
	double d4 = (double)(-D+c1.mRadius+c2.mRadius);
	float delta =  (float)0.25*(float)sqrt(d1*d2*d3*d4);

	tpc.mPoint1.x =(float)0.5*(c1.mCenter.x+c2.mCenter.x )
			 + ((c2.mCenter.x-c1.mCenter.x )*(c1.mRadius*c1.mRadius-c2.mRadius*c2.mRadius ))/((float)2.0*D*D)
			 + (float)2.0*delta*( c1.mCenter.y-c2.mCenter.y )/( D*D );

	tpc.mPoint2.x  = (float)0.5*(c1.mCenter.x+c2.mCenter.x )
			 + ((c2.mCenter.x-c1.mCenter.x )*(c1.mRadius*c1.mRadius-c2.mRadius*c2.mRadius ))/((float)2.0*D*D)
			 - (float)2.0*delta*( c1.mCenter.y-c2.mCenter.y )/( D*D );

	tpc.mPoint1.y  = (float)0.5*(c1.mCenter.y+c2.mCenter.y )
			 + ((c2.mCenter.y-c1.mCenter.y )*(c1.mRadius*c1.mRadius-c2.mRadius*c2.mRadius ))/((float)2.0*D*D)
			 - (float)2.0*delta*( c1.mCenter.x-c2.mCenter.x )/( D*D );
 
	tpc.mPoint2.y  = (float)0.5*(c1.mCenter.y+c2.mCenter.y )
			 + ((c2.mCenter.y-c1.mCenter.y )*(c1.mRadius*c1.mRadius-c2.mRadius*c2.mRadius ))/((float)2.0*D*D)
			 + (float)2.0*delta*( c1.mCenter.x-c2.mCenter.x )/( D*D );

	tpc.result = 2;
	return tpc;
}


// mDebug.CDebugPut("*CArrow::Draw* - %d-", tp.result );

CTwoPoints  ComputeIntersectionOfCircleAndLine(CCircle  c1 , CLineObject l1 )
{


	//  mDebug.CDebugPut("*Cicle:: * Radius  = %6.2f  CenterX: %6.2f )  ", c1.mRadius , c1.mCenter.x );	
	// mDebug.CDebugPut("*Cicle:: * CenterY = %6.2f  Acoeff: %6.2f )  ",  c1.mCenter.y , l1.GetA() );	
	//  mDebug.CDebugPut("*Cicle:: * Bcoeff = %6.2f  Ccoeff: %6.2f )  ",  l1.GetB() , l1.GetC() );	

	CTwoPoints  tpc( CFPoint(-1,-1),CFPoint(-1,-1) );
	tpc.result = -1;
	
	if (  l1.GetB() !=  0.0 )
		{
		float m =  (float)(-l1.GetA()/l1.GetB());
		float d =  (float)(-l1.GetC()/l1.GetB());

		float D = c1.mRadius*c1.mRadius*(1 + m*m) -  (c1.mCenter.y- m*c1.mCenter.x - d)* (c1.mCenter.y- m*c1.mCenter.x - d);

		// if D == 0  the one point
		tpc.mPoint2.x  =  ( c1.mCenter.x + c1.mCenter.y*m - d*m + sqrt(D))/(1+m*m );
		tpc.mPoint1.x  =  ( c1.mCenter.x + c1.mCenter.y*m - d*m - sqrt(D))/(1+m*m );

		tpc.mPoint1.y  =  ( d + c1.mCenter.x*m + c1.mCenter.y*m*m - m*sqrt(D))/(1+m*m );
		tpc.mPoint2.y  =  ( d + c1.mCenter.x*m + c1.mCenter.y*m*m  + m*sqrt(D))/(1+m*m );
 
		tpc.result = 2;
		if ( D == 0.0) tpc.result = 1;
	} 
	else if (  l1.GetA() !=  0.0 )
	{
		float fA = 1 ;
		float fB = -2*c1.mCenter.y;

		float fC =	(float)(l1.GetC()*l1.GetC()/( l1.GetA()*l1.GetA()  ) 
				+ 2.0*c1.mCenter.x*l1.GetC()/l1.GetA() 
				+ c1.mCenter.x*c1.mCenter.x 
				+ c1.mCenter.y*c1.mCenter.y 
				- c1.mRadius*c1.mRadius);

		float delta =  fB*fB - 4*fA*fC;




	    if ( delta < 0 ) 
			{

	//mDebug.CDebugPut("*Cicle:: * delta = %6.2f  delta: %6.2f )  ",  delta , delta );	

				tpc.result = 0;
				return tpc ;
			}
		else
		{
			float sdelta = sqrt(delta);
			tpc.mPoint1.y =  ( -fB - sdelta)/(2*1);
			tpc.mPoint2.y =  ( -fB  + sdelta)/(2*1);
			tpc.mPoint1.x  =  (float)(-l1.GetC()/l1.GetA()) ;
			tpc.mPoint2.x  =  (float)(-l1.GetC()/l1.GetA()) ;
			tpc.result = 2;
			if ( delta == 0.0) tpc.result = 1;

		}
	}

	return tpc;
}

//
//  find point which is in given segment  -1,-1  if not
//  circle center  creates range
//  Start & End refers to reference segment
//  need to consider direction to EndPoint


CTwoPoints  ComputeIntersectionOfCircleAndSegment( CFPoint CenterPoint , float Radius , CFPoint StartPoint,CFPoint EndPoint  )
{
	CTwoPoints  tpc( CFPoint(-1,-1),CFPoint(-1,-1) );

	CLineObject l1 = CLineObject( StartPoint ,  EndPoint );
	CCircle  c1 = CCircle( CenterPoint,Radius);

	tpc = ComputeIntersectionOfCircleAndLine(   c1 ,  l1 );

	return tpc;

}



//   d = | Ax0 + By0 + C |/sqrt( A*A +B*B )

 float	GetDistanceLineToPoint( CFPoint  mstartpoint , CFPoint EndPoint  ,  CFPoint  mPoint   ) 
 {
	double d=0;

	CLineObject l1 =  CLineObject(  mstartpoint , EndPoint );

	d = abs( l1.GetA()*mPoint.x + l1.GetB()*mPoint.y + l1.GetC() )/sqrt( l1.GetA()*l1.GetA() + l1.GetB()*l1.GetB() );

	return (float)d;
 }

float   GetDistanceBtwTwoLines( CFPoint StartPoint1 , CFPoint EndPoint1 , CFPoint StartPoint2 , CFPoint EndPoint2 ) 
{   
 	CLineObject  mLineL1;
	CLineObject  mLineLP;
	CLineObject  mLineL2;

	mLineL1 = CLineObject(  StartPoint1 ,   EndPoint1  );
	mLineL2 = CLineObject(  StartPoint2 ,   EndPoint2 );

	mLineLP = CLineObject( mLineL1.GetA() , mLineL1.GetB(), StartPoint1 );
    CFPoint CrossPoint  =  CrossOfTwoLines (  mLineLP , mLineL2 ) ;
    return GetDistance( StartPoint1 , CrossPoint  ) ;
}

 
float   GetDistance( CFPoint StartPoint , CFPoint EndPoint  ) 
{
	float  dx = EndPoint.x-StartPoint.x;
	float  dy = EndPoint.y-StartPoint.y;
	float  d2 = dx*dx+dy*dy;
	float fl = sqrt((float)d2);
    return fl;
}
 


CFPoint   GetCenterPoint( CFPoint StartPoint , CFPoint EndPoint  )
{
	CFPoint  pt;
	pt.x = (( StartPoint.x )+( EndPoint.x ))/(float)2.0;
	pt.y = (( StartPoint.y )+( EndPoint.y ))/(float)2.0;
	return pt;
}

CPoint   GetMidlePoint( CPoint StartPoint , CPoint EndPoint  )
{
	CPoint  pt;
	pt.x = (int)((( StartPoint.x )+( EndPoint.x ))/(float)2.0);
	pt.y = (int)((( StartPoint.y )+( EndPoint.y ))/(float)2.0);
	return pt;
}



CFPoint GetPointAtTheLine (  CFPoint StartPoint ,CFPoint EndPoint , CFPoint ExtPoint )
{
	CFPoint  pt;

	CLineObject  mLineL;
	mLineL.LineFromPoints(   StartPoint ,    EndPoint );

	CLineObject mLineP =  CLineObject( mLineL.GetA() , mLineL.GetB(), ExtPoint );

	pt =  CrossOfTwoLines ( mLineL , mLineP ) ;

	return pt;
}
 


CFPoint   CrossOfTwoLines ( CLineObject  mLineMath1 , CLineObject  mLineMath2 ) 
{
	CFPoint ptf = CFPoint(0,0);
	double fw = mLineMath1.GetA()*mLineMath2.GetB()-mLineMath2.GetA()*mLineMath1.GetB();
	if ( (int)fw != 0  )  // lines are ! paraller
	{
		double fwx,fwy;
		fwx = -mLineMath1.GetC()*mLineMath2.GetB() - (-mLineMath2.GetC()  )*mLineMath1.GetB();
		fwy = -mLineMath2.GetC()*mLineMath1.GetA() - (-mLineMath1.GetC()  )*mLineMath2.GetA();
		ptf.x = (float) (fwx/fw ) ;
 		ptf.y = (float) (fwy/fw ) ;
	}
	return ptf;
}

CFPoint fCrossOfTwoVectors ( CVector vFirst ,CVector vSecond )
{
	CFPoint ptf = CFPoint(0,0);

	CLineObject  mLineMath1;
	CLineObject  mLineMath2;

	mLineMath1.LineFromPoints(   vFirst.mStart ,    vFirst.mEnd);
	mLineMath2.LineFromPoints(   vSecond.mStart ,   vSecond.mEnd);

	double fw = mLineMath1.GetA()*mLineMath2.GetB()-mLineMath2.GetA()*mLineMath1.GetB();
	if ( (int)fw != 0  )  //  if zero  -- vectors are paraller
	{
		double fwx,fwy;
		fwx = -mLineMath1.GetC()*mLineMath2.GetB() - (-mLineMath2.GetC()  )*mLineMath1.GetB();
		fwy = -mLineMath2.GetC()*mLineMath1.GetA() - (-mLineMath1.GetC()  )*mLineMath2.GetA();
		ptf.x = (float) (fwx/fw ) ;
 		ptf.y = (float) (fwy/fw ) ;
	}
	return ptf;
}


CFPoint fCrossOfTwoVectors ( CFVector vFirst ,CFVector vSecond )
{
	CFPoint ptf = CFPoint(0,0);

	CLineObject  mLineMath1;
	CLineObject  mLineMath2;

	mLineMath1.LineFromPoints(   vFirst.mStart ,    vFirst.mEnd);
	mLineMath2.LineFromPoints(   vSecond.mStart ,   vSecond.mEnd);

	double fw = mLineMath1.GetA()*mLineMath2.GetB()-mLineMath2.GetA()*mLineMath1.GetB();
	if ( (int)fw != 0  )  //  if zero  -- vectors are paraller
	{
		double fwx,fwy;
		fwx = -mLineMath1.GetC()*mLineMath2.GetB() - (-mLineMath2.GetC()  )*mLineMath1.GetB();
		fwy = -mLineMath2.GetC()*mLineMath1.GetA() - (-mLineMath1.GetC()  )*mLineMath2.GetA();
		ptf.x = (float) (fwx/fw ) ;
 		ptf.y = (float) (fwy/fw ) ;
	}
	return ptf;
}

 
// fixed  distance 
///  compute both  crossing point equally placed on both side of the center point on the line
//

CFPoint   ComputePointFromLinePointOriginExt ( CLineObject mLine  , CFPoint  CenterPoint , float  fRadius , int idir )
{
	CFPoint cf= CFPoint(0,0);
	float fA,fB,fC,delta;
	float lA=(float)mLine.GetA(),lB=(float)mLine.GetB(),lC=(float)mLine.GetC();
	float lA2 = lA*lA,lB2 = lB*lB,lC2 = lC*lC;;

	if ( (int)lA == 0  )
	{
	   if ( (int)lB != 0  )	
	   {
		fC = -fRadius*fRadius + CenterPoint.y*CenterPoint.y + CenterPoint.x*CenterPoint.x + (float)2.0*CenterPoint.y*lC/lB + lC2/lB2;
		fB = (float)2.0* ( lC*lA/lB2 + lA*CenterPoint.y/lB - CenterPoint.x ); 
		fA = lA2/lB2 +1; 
		delta = fB*fB - (float)4.0*fA*fC; if ( delta <= 0 ) return CFPoint(0,0);
		if ( idir == 0) { cf.x = (-fB - sqrt ( delta))/(2*fA) ; cf.y = -(lC + lA*cf.x)/lB; }
		else { cf.x = (-fB +sqrt ( delta))/(2*fA) ; cf.y = -( lC + lA*cf.x)/lB; }
	   }
	   else   return cf;
	}
	else
	{
		fC =  -fRadius*fRadius +CenterPoint.y*CenterPoint.y + CenterPoint.x*CenterPoint.x + (float)2.0*CenterPoint.x*lC/lA+lC2/lA2;
		fB =  (float)2.0* ( lC*lB/lA2 + lB*CenterPoint.x/lA - CenterPoint.y) ; 
		fA = lB2/lA2 +1; 
		delta = fB*fB - (float)4.0*fA*fC;  if ( delta <= 0 ) return cf;
		if ( idir == 0)	{ cf.y = (-fB - sqrt ( delta))/(2*fA)  ;cf.x = -( lC + lB*cf.y)/lA; }
		else	{ cf.y = (-fB +sqrt ( delta))/(2*fA) ;	cf.x = -( lC + lB*cf.y)/lA; }
	}
	return cf;
}


float  GetAbsAngleOfTwoVectors ( float a1, float a2 )
{
	float angle =  0.0;
	float angle1=0,angle2=0;

	if ( a1 > a2 )
	{
		angle1 = a1;
		angle2 = a2;
	}
	else
		if ( a2 > a1 )
		{
		angle2 = a1;
		angle1 = a2;
		}

    angle = angle1 - angle2;
	if ( angle > 180 ) angle = 360 - angle;
    return angle;
}


float  GetAbsAngleOfTwoVectors ( CVector vFirst ,CVector vSecond ) 
{
	float a1 =	ComputeVectorAngle( vFirst.mStart  ,  vFirst.mEnd ) ;
	float a2 =	ComputeVectorAngle( vSecond.mStart , vSecond.mEnd ) ;
	return  GetAbsAngleOfTwoVectors (   a1,   a2 );
}

float  GetAbsAngleOfTwoVectors ( CFPoint StartPoint1 ,CFPoint EndPoint1  ,CFPoint StartPoint2 ,CFPoint EndPoint2 )
{
	float a1 =	ComputeVectorAngle( StartPoint1 , EndPoint1 ) ;
	float a2 =	ComputeVectorAngle( StartPoint2 , EndPoint2 ) ;
	return  GetAbsAngleOfTwoVectors (   a1,   a2 );
}

float  GetAngleOfTwoVectors ( CFPoint StartPoint  , CFPoint EndPoint1 ,CFPoint EndPoint2 )
{
	float a1 =	ComputeVectorAngle( StartPoint , EndPoint1 ) ;
	float a2 =	ComputeVectorAngle( StartPoint , EndPoint2 ) ;

	return a1-a2;
}

float  GetRelAngleOfTwoVectors ( CFPoint StartPoint  , CFPoint EndPoint1 ,CFPoint EndPoint2 )
{
	float a1 =	ComputeVectorAngle( StartPoint , EndPoint1 ) ;
	float a2 =	ComputeVectorAngle( StartPoint , EndPoint2 ) ;
	float a = a1-a2;
	if  ( a  < -179 ) a +=360;
	if  ( a  > 179 ) a -=360;
	return a;
}

float	GetDistanceBend( CObjBendRail *p    ) 
{
	//DRAWDATASTRUCT *pdd = 	p->GetDrawDataStructPtr();

	float fRadius = GetDistance( p->GetCenterPoint() , p->GetPoint( 0 )  );
	float a =  GetAbsAngleOfTwoVectors ( p->GetCenterPoint()  , p->GetPoint(0 )   , p->GetCenterPoint()   , p->GetPoint( 1 ) );
	float perimeter = ((float)PI180)*fRadius*a;  // Pi/180
	return perimeter;
}

CFPoint GetPointFmStartStright(  CObjRail *p , int ep1  ,float distance   ) 
{
	return GetPointFmStart(  p->GetPoint(ep1) , p->GetPoint( (ep1+1)%2 ),  distance );
}

float	GetDistance(  CObjBendRail *p   , int sep ,  CFPoint mEndPoint  ) 
{
	//DRAWDATASTRUCT *pdd = 	p->GetDrawDataStructPtr();
	float fRadius = (float)GetDistance( p->GetCenterPoint() , p->GetPoint( sep )  );
	float a =  (float)GetAbsAngleOfTwoVectors ( p->GetCenterPoint() ,  p->GetPoint( sep )  , p->GetCenterPoint()  , mEndPoint );
	float perimeter = (((float)PI180)*fRadius)*a;  // Pi/180

 //mDebug.CDebugPut("**GetDistance a: %6.2f perimeter:%6.2f ",   (float)a , (float)perimeter  ); 

	return (float)perimeter;
}

 

//   distance from the endpoint

CFPoint GetPointFmStartBend(  CObjBendRail *p , int epfm  ,float distance  )
{
	//DRAWDATASTRUCT *pdd = 	p->GetDrawDataStructPtr();

	CFPoint fCenterPoint = p->GetCenterPoint() ;

	float fRadius = GetDistance( fCenterPoint , p->GetPoint( epfm )  );
	//float dti =  distance*((float)C180PI)/fRadius;  // convert distance to angle

 	//mDebug.CDebugPut("**#######:Radius:%8.2f Dist:%6.2f ", fRadius   ,  distance );

	 float dti =   (( distance)*((float)C180PI))/  fRadius     ;  // convert distance to angl

 //	mDebug.CDebugPut("**#######:reldist:%6.2f dti:%6.2f ", distance   ,   dti ); 

	float fStartAngle =	ComputeVectorAngle( fCenterPoint  , p->GetPoint( 0 ) ) ;
	float fSweepAngle = GetRelAngleOfTwoVectors ( fCenterPoint , p->GetPoint( 1 ) , p->GetPoint( 0 )) ;
	float fEndAngle	=	fStartAngle + fSweepAngle ;
	BOOL iturn = ( fSweepAngle < 0 ) ;
	float angle = fStartAngle;
	if ( epfm == 0 )  { if ( iturn == TRUE ) dti = -dti; }
	else			{ angle = fEndAngle; if ( iturn == FALSE ) dti = -dti;}
	angle += dti ;
	
//mDebug.CDebugPut("**$$$$$$:New points :(%6.2f dti:%6.2f) ", fCenterPoint.x+(float)fRadius*(float)cos(PI180*angle)  ,fCenterPoint.y-  (float)fRadius*(float)sin(PI180*angle) ); 


	CFPoint cpt (fCenterPoint.x+(float)fRadius*(float)cos(PI180*angle),fCenterPoint.y-(float)fRadius*(float)sin(PI180*angle)) ;
	
//mDebug.CDebugPut("**$$$$$$:distance :%6.2f dti:%6.2f ", distance  ,   dti ); 

//	mDebug.CDebugPut("**$$$$$$:New points :(%6.2f dti:%6.2f) ", cpt.x  ,cpt.y ); 

		return cpt;
	//return CFPoint( fCenterPoint.x+(float)fRadius*(float)cos(PI180*angle),fCenterPoint.y-(float)fRadius*(float)sin(PI180*angle) );
}


 CFPoint ComputeBendExtendedPoint ( CFPoint  CenterPoint , CFPoint  MidleEndPoint , CFPoint OtherEndPoint)
 {
	CLineObject mLineL =  CLineObject ( CenterPoint , MidleEndPoint  );
	CLineObject mLineP =  CLineObject( mLineL.GetA() , mLineL.GetB(), MidleEndPoint );
	//CFPoint cf = ComputePointFromLinePointOrigin ( mLineP , MidleEndPoint , 100 );
	
	CFPoint cf = ComputePointFromLinePointOriginExt( mLineP , MidleEndPoint , 100 ,0 );


	float a1 = ComputeVectorAngle( MidleEndPoint , OtherEndPoint ) ;
	float a2 = ComputeVectorAngle( MidleEndPoint , cf  ) ;
	float aa =  GetAbsAngleOfTwoVectors (   a1,   a2 );

	if (  aa  > 90 )  
			CFPoint cf = ComputePointFromLinePointOriginExt( mLineP , MidleEndPoint , 100 ,1);

		//cf = ComputePointFromLinePointOrigin ( mLineP , MidleEndPoint , -100 );
	return cf;
 }

 //  start point is where :
//  perpendicular line is created
//  two solutions for center point are evaluated and the one with closer angle to ExtPoint is selected as center
//  Turn has only symbolic meaning for matching it with ExtPoint
//  consider passing the parameters as structure !

CFPoint ComputeCenterPoint( CFPoint   StartPoint ,CFPoint   EndPoint , CFPoint   ExtPoint , float iRadius   )  
{
	int lTurn = 0;
	CLineObject mLineL =  CLineObject ( StartPoint , EndPoint );
	CLineObject mLineP =  CLineObject( mLineL.GetA() , mLineL.GetB(), StartPoint );
	CFPoint pt  = ComputePointFromLinePointOriginExt ( mLineP  , StartPoint , iRadius , lTurn );
	if ( lTurn  == 0 ) lTurn =1; else lTurn =0; // swap it if no match in the first place
	if (  GetAbsAngleOfTwoVectors ( ComputeVectorAngle( StartPoint , ExtPoint ),ComputeVectorAngle(StartPoint,pt)) > 90 )
						pt  = ComputePointFromLinePointOriginExt ( mLineP , StartPoint , iRadius , lTurn );
	return pt;
}


CFPoint ComputeExtendedLinePoint( CFPoint CenterPoint ,CFPoint StartPoint , CFPoint EndPoint )
{
  int lTurn = 0;
 
  CLineObject mLineL =  CLineObject ( CenterPoint , EndPoint );   // create line from center point to exp point
  CLineObject mLineP =  CLineObject( mLineL.GetA() , mLineL.GetB(), EndPoint );  // perpendicular line

  CFPoint pt  = ComputePointFromLinePointOriginExt ( mLineP  ,EndPoint , 100 , lTurn );

  if ( lTurn  == 0 ) lTurn =1; else lTurn =0; // swap it if no match in the first place
  
  if (  GetAbsAngleOfTwoVectors ( ComputeVectorAngle( StartPoint , EndPoint ),ComputeVectorAngle( EndPoint ,pt)) > 90 )
						pt  = ComputePointFromLinePointOriginExt ( mLineP , EndPoint , 100 , lTurn );
 
  //p->SetDebugPoint(0, EndPoint);  
  //p->SetDebugPoint(1, pt ); 
  //p->SetDebugPoint(2, CenterPoint ); 
  return pt;
}
 


float  ComputeVectorAngleIn( CFPoint startPoint , CFPoint endPoint ) 
{
 if (( endPoint.x >  startPoint.x ) && ( endPoint.y  <= startPoint.y ))
  return (float)( C180PI*atan((double)((double)( startPoint.y-endPoint.y))/((double)(endPoint.x-startPoint.x)))  );
 
 if (( endPoint.x <=  startPoint.x ) && ( endPoint.y  <  startPoint.y ))
  return (float)(90.0+C180PI*atan((double)((double)(startPoint.x-endPoint.x))/((double)(startPoint.y-endPoint.y))) );

 if (( endPoint.x <  startPoint.x ) && ( endPoint.y  >= startPoint.y ))
  return (float)(180.0+C180PI*atan((double)((double)(endPoint.y-startPoint.y))/((double)(startPoint.x-endPoint.x))) );

 if (( endPoint.x >=  startPoint.x ) && ( endPoint.y  >  startPoint.y ))
  return (float)(270.0+C180PI*atan((double)((double)(endPoint.x-startPoint.x))/((double)(endPoint.y-startPoint.y))) );

 return 0.0;
}


float  ComputeVectorAngle( CFPoint startPoint , CFPoint endPoint ) 
{
  float angle = ComputeVectorAngleIn(  startPoint ,   endPoint ) ;
  if ( angle >= 360 ) angle -=360;
  return angle;
}


float ComputeVectorAngle( CPoint startPoint , CPoint endPoint ) 
{
 if (( endPoint.x >  startPoint.x ) && ( endPoint.y  <= startPoint.y ))
  return (float)( C180PI*atan((double)((double)( startPoint.y-endPoint.y))/((double)(endPoint.x-startPoint.x)))  );
 
 if (( endPoint.x <=  startPoint.x ) && ( endPoint.y  <  startPoint.y ))
  return (float)(90.0+C180PI*atan((double)((double)(startPoint.x-endPoint.x))/((double)(startPoint.y-endPoint.y))) );

 if (( endPoint.x <  startPoint.x ) && ( endPoint.y  >= startPoint.y ))
  return (float)(180.0+C180PI*atan((double)((double)(endPoint.y-startPoint.y))/((double)(startPoint.x-endPoint.x))) );

 if (( endPoint.x >=  startPoint.x ) && ( endPoint.y  >  startPoint.y ))
  return (float)(270.0+C180PI*atan((double)((double)(endPoint.x-startPoint.x))/((double)(endPoint.y-startPoint.y))) );

 return 0.0;
}


int  GetDistance( POINT StartPoint , POINT EndPoint  ) 
{
 
	int  dx = EndPoint.x-StartPoint.x;
	int  dy = EndPoint.y-StartPoint.y;
	int  d2 = dx*dx+dy*dy;
	float fl = sqrt((float)d2);
	d2 =(int)( roundToNearest (fl));
    return d2;
}

int  GetDistance( CPoint StartPoint , CPoint EndPoint  ) 
{
 
	int  dx = EndPoint.x-StartPoint.x;
	int  dy = EndPoint.y-StartPoint.y;
	int  d2 = dx*dx+dy*dy;
	float fl = sqrt((float)d2);
	d2 =(int)( roundToNearest (fl));
    return d2;
}

CPoint  GetCenterPoint( CPoint StartPoint , CPoint EndPoint  )
{
	CPoint  pt;

	pt.x = (( StartPoint.x )+( EndPoint.x )) >> 1;
	pt.y = (( StartPoint.y )+( EndPoint.y )) >> 1;

	return pt;
}

 

CPoint GetPointFmStart(  CPoint StartPoint, CPoint EndPoint, int distance )
{
	CPoint  ExtPoint;

	float	fdx = (float)(EndPoint.x-StartPoint.x);
	float	fdy = (float)(EndPoint.y-StartPoint.y);
	float	fl = sqrt((float)(fdx*fdx+fdy*fdy ) );  

	float	fx = ((float)(distance))*fdx/fl;
	float	fy = ((float)(distance))*fdy/fl;

	fx = (float)roundToNearest (fx) ;
	fy = (float)roundToNearest (fy) ;

	ExtPoint.x =  StartPoint.x +(int)fx;
	ExtPoint.y =  StartPoint.y +(int)fy;

	return ExtPoint;
}


CFPoint  GetPointFmStart(  CFPoint StartPoint,CFPoint EndPoint, float distance )
{
	CFPoint ExtPoint;
	float	fdx = EndPoint.x-StartPoint.x;
	float	fdy = EndPoint.y-StartPoint.y;
	float	fl = sqrt(fdx*fdx+fdy*fdy ) ;  
	float	fx = distance*fdx/fl;
	float	fy = distance*fdy/fl;
	ExtPoint.x =  StartPoint.x + fx;
	ExtPoint.y =  StartPoint.y + fy;
	return ExtPoint;
}



CFPoint  AdjustBendCenterPoint(  CPoint StartPoint , CPoint EndPoint , CFPoint m_currentCenter )
{ 
		CFPoint middle  = GetCenterPoint(  StartPoint ,   EndPoint );
		CLineObject  mLine(  StartPoint ,   EndPoint  );
		CLineObject  mLinePerp( mLine.GetA()  , mLine.GetB()  , middle );

		CCircle  mcircle(  middle , 50.0 );
		CTwoPoints tpo = ComputeIntersectionOfCircleAndLine(mcircle , mLinePerp );

		CFPoint newCenter1;
		CFPoint newCenter2;

 		float fhi =  GetDistance(  StartPoint ,   EndPoint) * (float)(sqrt ((double)3.0)/((double)2.0)) ;

		newCenter1 =  GetPointFmStart(  middle , tpo.mPoint1 , fhi  );
		newCenter2 =  GetPointFmStart(  middle , tpo.mPoint2 , fhi  );

		if ( GetDistance( m_currentCenter , newCenter1 )  <  GetDistance( m_currentCenter , newCenter2 )     )  return newCenter1;
		else return newCenter2;
 
}

//  need to convert to angle  first then  set properly on the bend
//		----------------
//	   |				|
//   [0]				[1]
//
//
//
//

 /*

CFPoint GetPointFmStartBend(  CFPoint StartPoint,CFPoint EndPoint,DRAWDATASTRUCT *pdd ,float distance )
{
	CFPoint ExtPoint;

	float dti =  distance*((float)C180PI)/pdd->Radius;  // from distance to angle
    // what is our start point ? Are we going from real start or opposite ?
	int startpoint ;

	if (  (  ((int)StartPoint.x) ==  ((int)pdd->StartPoint.x) ) && (  ((int)StartPoint.y) ==  ((int)pdd->StartPoint.y) ))
		startpoint = 1; // yes
	else 
		startpoint = 0; // must be other point
 
	float angle;

	// mDebug.CDebugPut("GBFS startpoint:%d  Turn: %d  ", startpoint,  pdd->Turn  );

	if ( startpoint == 1 )
	{	
		if ( pdd->Turn == 1 ) dti*=-1;
		angle = pdd->mStartAngle + dti ;
	}
	else
	{
		if ( pdd->Turn == 0 ) dti*=-1;
		angle = pdd->mStartAngle + pdd->mSweepAngle + dti ;
	}


 //mDebug.CDebugPut("GBFS start angle:%6.2f  sweep:%6.2f   ", pdd->mStartAngle , pdd->mSweepAngle );
 //mDebug.CDebugPut("GBFS angle:%6.2f  dti:%6.2f   ", angle , dti );


	ExtPoint.x = pdd->CenterPoint.x +  (float)pdd->Radius*(float)cos(  PI180*(angle) );
	ExtPoint.y = pdd->CenterPoint.y -  (float)pdd->Radius*(float)sin(  PI180*(angle) );

	return ExtPoint;
}
 */
/*
CFPoint GetPointFmStart(  CFPoint StartPoint,CFPoint EndPoint,float distance ,DRAWDATASTRUCT *pdd )
{
	CFPoint ExtPoint(0,0);

	float dti =  distance*((float)C180PI)/pdd->Radius;  // from distance to angle
    // what is our start point ? Are we going from real start or opposite ?
	int startpoint ;

	if (  (  ((int)StartPoint.x) ==  ((int)pdd->StartPoint.x) ) && (  ((int)StartPoint.y) ==  ((int)pdd->StartPoint.y) ))
		startpoint = 1; // yes
	else 
		startpoint = 0; // must be other point
 
	float angle;

	// mDebug.CDebugPut("GBFS startpoint:%d  Turn: %d  ", startpoint,  pdd->Turn  );

	if ( startpoint == 1 )
	{	
		if ( pdd->Turn == 1 ) dti*=-1;
		angle = pdd->mStartAngle + dti ;
	}
	else
	{
		if ( pdd->Turn == 0 ) dti*=-1;
		angle = pdd->mStartAngle + pdd->mSweepAngle + dti ;
	}


 //mDebug.CDebugPut("GBFS start angle:%6.2f  sweep:%6.2f   ", pdd->mStartAngle , pdd->mSweepAngle );
 //mDebug.CDebugPut("GBFS angle:%6.2f  dti:%6.2f   ", angle , dti );


	ExtPoint.x = pdd->CenterPoint.x +  (float)pdd->Radius*(float)cos(  PI180*(angle) );
	ExtPoint.y = pdd->CenterPoint.y -  (float)pdd->Radius*(float)sin(  PI180*(angle) );

   return ExtPoint;
}

*/

/*
float  GetDistanceAngle( CFPoint  mstartpoint , DRAWDATASTRUCT *pdd , CFPoint  mpoint ) 
{

	float a1 =	ComputeVectorAngle( pdd->CenterPoint , mstartpoint ) ;
	float a2 =	ComputeVectorAngle( pdd->CenterPoint , mpoint ) ;
	return abs( a1-a2);

}
*/

float	GetDistance( CFPoint  mStartpoint , CFPoint mEndPoint  , DRAWDATASTRUCT *pdd  ) 
{
	// convert to abgle 
	
	float a =  GetAbsAngleOfTwoVectors ( pdd->CenterPoint  ,mStartpoint   ,pdd->CenterPoint  ,mEndPoint );
	 
//	float a1 =	ComputeVectorAngle( pdd->CenterPoint , mStartpoint ) ;
//	float a2 =	ComputeVectorAngle( pdd->CenterPoint , mEndPoint ) ;
/*
	mDebug.CDebugPut("GetDistance:-------------------- "  );
	mDebug.CDebugPut("GetDistance: stp %6.2f , %6.2f   ", mStartpoint.x, mStartpoint.y  );
	mDebug.CDebugPut("GetDistance: enp %6.2f , %6.2f   ", mEndPoint.x, mEndPoint.y  );	
	mDebug.CDebugPut("GetDistance: a1:%6.2f a2:%6.2f   ", a1 , a2  );
	mDebug.CDebugPut("GetDistance: abs:%6.2f  :%6.2f   ", a , (float)0  );
	mDebug.CDebugPut("GetDistance:-------------------- "  );
	 */
	float perimeter = ((float)PI180)*pdd->Radius*a;  // Pi/180
	return perimeter;
}


float LtoAngle(float distance , DRAWDATASTRUCT *pdd  ) 
{
	return  distance*((float)C180PI)/pdd->Radius;   
}
// create perpendicular section at pPoint lengh of lenght
//           *        * S,E  
//           |
//        X--+--X    + PPoint disp
//           | 
//           |
//           |
//           *



CSegment ComputeSectionPependicularAtPoint( CFPoint StartPoint ,CFPoint EndPoint ,float distance,float lenght)
{
	CSegment mSection= CSegment();
	// get the extednded point
	CFPoint ExtPoint;
	if ( distance != 0 ) // the distance cannot be zero
	{
	 ExtPoint = GetPointFmStart(    StartPoint,  EndPoint,   distance );
	// use old obsolite function
	CFPoint Pt1 = ComputeTwoParLines( ExtPoint ,StartPoint , lenght , 0);
	CFPoint Pt2 = ComputeTwoParLines( ExtPoint ,StartPoint , lenght , 1);
	mSection= CSegment(Pt1,Pt2);
	}
	return mSection;
}
 
CSegment ComputeSectionPependicularAtPointExt( CFPoint StartPoint ,CFPoint EndPoint ,float offset,float lenght)
{
	CSegment mSection= CSegment();

	CLineObject   mLine = CLineObject (  StartPoint ,  EndPoint); // generate the line 
 
	CFPoint ExtPoint;
	if ( offset != 0 )
		ExtPoint = GetPointFmStart(  StartPoint,  EndPoint,   offset );
	 else 
		ExtPoint = StartPoint;

	CLineObject   mLineP =   CLineObject( mLine.GetA() ,mLine.GetB()  ,ExtPoint)  ;        // perpendicular at the point

	CFPoint Pt1 =  ComputePointFromLinePointOriginExt (  mLineP  , ExtPoint, lenght   , 0 );
	CFPoint Pt2 =  ComputePointFromLinePointOriginExt (  mLineP  , ExtPoint, lenght   , 1 );
 
	mSection= CSegment(Pt1,Pt2);

	return mSection;
}




CFPoint  ComputeTwoParLines( CFPoint SPoint ,CFPoint EPoint , int disp , int point_index ) 
{
	float  dx = EPoint.x-SPoint.x;
	float  dy = EPoint.y-SPoint.y;

	float fl = sqrt((float)(dx*dx+dy*dy));
	float fdisp =(float) disp;

	float dxx =    (fdisp * ((float)dy)/fl);
    float dyy =    (fdisp * ((float)dx)/fl);
	
	CFPoint SPoint0; 
	CFPoint SPoint1;
	CFPoint EPoint0; 
	CFPoint EPoint1;

	if ( point_index == 0 )
	{
	SPoint0.x = SPoint.x + dxx;
	SPoint0.y = SPoint.y - dyy;
	return SPoint0;
	}
	else if ( point_index == 1 )
	{
	SPoint1.x = SPoint.x - dxx;
	SPoint1.y = SPoint.y + dyy;
	return SPoint1;
	}
	else if ( point_index == 2 )
	{
	EPoint0.x = EPoint.x + dxx;
	EPoint0.y = EPoint.y - dyy;
	return EPoint0;
	}
 	else if ( point_index == 3 )
	{
	EPoint1.x = EPoint.x - dxx;
	EPoint1.y = EPoint.y + dyy;
	return EPoint1;
	}

	EPoint1.x = 0;
	EPoint1.y = 0;
    return EPoint1;
}

CFPoint  ComputeTwoParLines( CFPoint SPoint ,CFPoint EPoint , float disp , int point_index ) 
{
	float  dx = EPoint.x-SPoint.x;
	float  dy = EPoint.y-SPoint.y;

	float fl = sqrt((float)(dx*dx+dy*dy));
	float fdisp =(float) disp;

	float dxx =    (fdisp * ((float)dy)/fl);
    float dyy =    (fdisp * ((float)dx)/fl);
	
	CFPoint SPoint0; 
	CFPoint SPoint1;
	CFPoint EPoint0; 
	CFPoint EPoint1;

	if ( point_index == 0 )
	{
	SPoint0.x = SPoint.x + dxx;
	SPoint0.y = SPoint.y - dyy;
	return SPoint0;
	}
	else if ( point_index == 1 )
	{
	SPoint1.x = SPoint.x - dxx;
	SPoint1.y = SPoint.y + dyy;
	return SPoint1;
	}
	else if ( point_index == 2 )
	{
	EPoint0.x = EPoint.x + dxx;
	EPoint0.y = EPoint.y - dyy;
	return EPoint0;
	}
 	else if ( point_index == 3 )
	{
	EPoint1.x = EPoint.x - dxx;
	EPoint1.y = EPoint.y + dyy;
	return EPoint1;
	}

	EPoint1.x = 0;
	EPoint1.y = 0;
    return EPoint1;
}


CPoint ComputeTwoParLines( CPoint SPoint ,CPoint EPoint , int disp , int point_index ) 
{

	int  dx = EPoint.x-SPoint.x;
	int  dy = EPoint.y-SPoint.y;

	float fl = sqrt((float)(dx*dx+dy*dy));
	float fdisp =(float) disp;

 
	int dxx = (int )roundToNearest(   (fdisp * ((float)dy)/fl));
    int dyy = (int )roundToNearest(   (fdisp * ((float)dx)/fl));
	
	CPoint SPoint0; 
	CPoint SPoint1;
	CPoint EPoint0; 
	CPoint EPoint1;

	if ( point_index == 0 )
	{
	SPoint0.x = SPoint.x + dxx;
	SPoint0.y = SPoint.y - dyy;
	return SPoint0;
	}
	else if ( point_index == 1 )
	{
	SPoint1.x = SPoint.x - dxx;
	SPoint1.y = SPoint.y + dyy;
	return SPoint1;
	}
	else if ( point_index == 2 )
	{
	EPoint0.x = EPoint.x + dxx;
	EPoint0.y = EPoint.y - dyy;
	return EPoint0;
	}
 	else if ( point_index == 3 )
	{
	EPoint1.x = EPoint.x - dxx;
	EPoint1.y = EPoint.y + dyy;
	return EPoint1;
	}

	EPoint1.x = 0;
	EPoint1.y = 0;
    return EPoint1;
}
 
CTwoPoints  ComputeParSectionOfTheLenght( CFPoint p0, CFPoint p1, float d , float d1)
{
       CTwoPoints cp2;
       CFPoint pex =  GetPointFmStart(  p0 , p1 , d );
       CLineObject mLine = CLineObject ( p0 , pex);
       CLineObject   mLineP =   CLineObject( mLine.GetA() ,mLine.GetB() ,pex )  ; 
       CCircle  c1 = CCircle( pex , d1 );
       cp2 = ComputeIntersectionOfCircleAndLine(   c1 , mLineP );
       return cp2;
}
