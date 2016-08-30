

#include "stdafx.h"
//#include "MouseTest.h"

//#include "Windowsx.h"
#include "Math.h"
#include <stdio.h>


#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "DrawTmpObject.h"

#include "Debug.h"
extern CDebug mDebug;

// -------------------------------------------------------------------------------
//   Temporary object class definition
// -------------------------------------------------------------------------------
//
//   Steps:
//	1.Setup object to draw/add  by pressing the object type to draw button 
//				CTempVectorSetTmpObject( TMPOBJECT_DRAWDATASTRUCT *tmpObjS )
//	2.Set Start End at the MouseButtonDown
//				CTempVectorUpdateStart( CPoint start )
//				CTempVectorUpdateEnd( CPoint start )
//	3.Update End  at the MouseMov
//				CTempVectorUpdateEnd( CPoint start )
//	4.Update  End at the MouseButtonUp  , create object add Object to the right collection. 
//				CTempVectorUpdateEnd( CPoint start )
//

CTempVector::CTempVector()
{
//	mObjectType = ObjNothing;

	mData.StartPoint = CPoint(0,0);
	mData.EndPoint = CPoint(0,0); 
	mData.Radius = 100;
	mData.Width = 10;
	mData.mStartAngle = 0.0;
	mData.mSweepAngle = 0.0;
  	mData.Turn =0;
}

void CTempVector::CTempVectorSetTmpObject( TMPOBJECT_DRAWDATASTRUCT *tmpObjS )
{
	mData.Radius = tmpObjS->Radius ;
	mData.Width =  tmpObjS->Width;
	mObjectType =  tmpObjS->mtype;
	mData.mStartAngle = tmpObjS->mStartAngle;
	mData.mSweepAngle = tmpObjS->mSweepAngle;
  	mData.Turn = tmpObjS->Turn;
	mDrawVagonData.mInitialLenght = (float)tmpObjS->Lenght;
}

void CTempVector::CTempVectorSetTmpObject( int type )
{
	mObjectType =  type;
}


void	CTempVector::CTempVectorSetPointReference( int option , CFPoint pt ) 
{
     CPoint  ptp;
	 ptp.x = (int)pt.x;
	 ptp.y = (int)pt.y;
	 CTempVectorSetPointReference(   option , ptp ) ;
}


void	CTempVector::CTempVectorSetPointReference( int option , CPoint pt ) 
{
	if ( option == CLEAR_REF )
		{
			iPtRef = FALSE;
		}
	else if ( option == SET_REF ) 
		{
			iPtRef = TRUE;
			ptPtRef = pt;
		}
}
 

void    CTempVector::CTempVectorSetSegmentReference( int option , CObjRail *px  )  
{
	if ( option == CLEAR_REF )
		{
			iSegmRef = FALSE;
		}
	else if ( option == SET_REF ) 
		{
			iSegmRef = TRUE;
			mData.pRail = px;
		}

}

CRect CTempVector::CTempVectorGetRectToInvalidate()
{
 	CRect  rc =   CTempVectorGetRect() ;

		//ComputeBandingRectBend( &mData  );


 	rc.InflateRect(2,2);
	rc.NormalizeRect();
    return rc;
}

void CTempVector::CTempVectorUpdateStart( CPoint start )
{
	mData.StartPoint.x =(float)start.x; 
	mData.StartPoint.y =(float)start.y; 
}

void CTempVector::CTempVectorUpdateEnd( CPoint end )
{
	mData.EndPoint.x = (float)end.x; 
	mData.EndPoint.y = (float)end.y; 
}
 
void    CTempVector::CTempVectorPaintTmpObject(  CPoint offset, HDC hdc )
{
	if ( mObjectType == ObjStraightRail )	CTempVectorPaintStright(  hdc );
	if ( mObjectType == ObjBendRightRail )	{ mData.Turn = 1; CTempVectorPaintBend(  hdc );}
	if ( mObjectType == ObjBendLeftRail )	{ mData.Turn = 0; CTempVectorPaintBend(  hdc );}
 	if ( mObjectType == ObjStraightDblRail )	{ mData.Turn = 0; CTempVectorPaintDblStright(  hdc );}
	if ( mObjectType == ObjTracker ) CTempVectorPaintTracker(   hdc );
	if ( mObjectType == ObjRailEnd )	CTempVectorPaintStright(  hdc );
	if ( mObjectType == ObjStop )	CTempVectorPaintStop(  offset ,hdc );  // semaphore
	if ( mObjectType == ObjSwitch )	CTempVectorPaintSwitch(  offset, hdc );
	if ( mObjectType == ObjSem )	CTempVectorPaintSemaphore(  offset, hdc );
 
}
 
///////////////////////////////////////////////////////////////////////////////////////
//  revised 2016.03.20
void CTempVector::CTempVectorPaintBend(   HDC hdc )
{
	PaintBendRail( &mData, SINGLELINE|  TMPDRAWLINES  , hdc );
	ComputeBandingRectBend( &mData  ); // compute active rectangle
	mUnionRect = mData.mUpdRect; // save active rectangle
	OnDrawRect( &mData.mUpdRect ,   hdc ); // draw framing rect
}
////////////////////////////////////////////////////////////////////////////////////////
//  revised 2016.03.20
void CTempVector::CTempVectorPaintStright(   HDC hdc )
{
	 PaintStraightRail( &mData, SINGLELINE | TMPDRAWLINES , hdc );
	 ComputeBandingRectStright( &mData  ); // compute active rectangle
	 mUnionRect = mData.mUpdRect;  // save active rectangle
	 OnDrawRect( &mData.mUpdRect ,   hdc ); // draw framing rect
}

////////////////////////////////////////////////////////////////////////////////////////
//  revised 2016.03.20
void CTempVector::CTempVectorPaintDblStright(   HDC hdc )
{
	PaintStraightRail( &mData, DOUBLELINE | TMPDRAWLINES , hdc );
	ComputeBandingRectStright( &mData  ); // compute active rectangle
	mUnionRect = mData.mUpdRect;  // save active rectangle
	OnDrawRect( &mData.mUpdRect ,   hdc ); // draw framing rect
}

////////////////////////////////////////////////////////////////////////////////////////
//   
void CTempVector::CTempVectorPaintTracker(   HDC hdc )
{
	CPoint pts,pte;
	pts.x = (int)mData.StartPoint.x;
	pts.y = (int)mData.StartPoint.y;
	pte.x = (int)mData.EndPoint.x;
	pte.y = (int)mData.EndPoint.y;
	CRect rfc( pts,pte );
	mUnionRect = rfc;  // save active rectangle
}

////////////////////////////////////////////////////////////////////////////////////////
//  revised 2016.03.20
void CTempVector::CTempVectorPaintStop( CPoint offset,  HDC hdc )
{
 	//PaintStop(  &mData, DOUBLELINE | TMPDRAWLINES , hdc  );
 	//ComputeBandingRectStop( &mData  ); // compute active rectangle	

	PaintControl( &mData, DOUBLELINE | TMPDRAWLINES  | TMP_COLOR_RED , hdc   );
	ComputeBandingRectControl( &mData  );


	mUnionRect = mData.mUpdRect;  // save active rectangle
	mUnionRect.NormalizeRect();

	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	if ( iSegmRef == TRUE  )
	{
		// translate to window coordinates from world coordinates
 	
		CMyPoint  tStartPt = mData.pRail->GetPoint(0) - offset;
		CMyPoint  tEndPt = mData.pRail->GetPoint(1) - offset;
		    
		// draw white box around the draw area
		if (   mPenSet.GetSolidPen(  1 , GetBlackColor() ) == NULL ) return ;	 
		DrawPointCross( tStartPt ,   hdc , GetWhiteColor() , 4);
		DrawPointCross( tEndPt ,   hdc , GetWhiteColor() , 4);

		CObjBendRail *pb = IsBendObject( mData.pRail  );
		CFPoint ptx;

		PASSDATASTRUCT tdata;
		tdata.StartPoint = tStartPt;
		tdata.EndPoint = tEndPt;
		
		if ( pb != NULL )
		{
			tdata.CenterPoint = pb->GetCenterPoint() - offset;
			ptx = CrossArchWithLinePerpendicular( mData.EndPoint  ,  &tdata ); 
		}
		else
			ptx =  CrossSegmentWithLinePerpendicular( mData.EndPoint  ,  &tdata ); 


		// EndPoint has point
		CSegment cs( mData.EndPoint , ptx  );
		cs.DrawSegment( hdc );

		CRect rn( tStartPt.x , tStartPt.y , (int)tEndPt.x  , (int)tEndPt.y );
		rn.NormalizeRect();
		rn.InflateRect(8,8);
		mData.mUpdRect.UnionRect( &rn ,  &mUnionRect ) ; 
		mUnionRect = mData.mUpdRect; 
	}

 	OnDrawRect( &mData.mUpdRect ,   hdc ); // draw framing rect
}

////////////////////////////////////////////////////////////////////////////////////////
//  revised 2016.03.20
void CTempVector::CTempVectorPaintSemaphore( CPoint offset,  HDC hdc )
{
		 PaintControl( &mData, DOUBLELINE | TMPDRAWLINES  | TMP_COLOR_RED , hdc   );
	 ComputeBandingRectControl( &mData  );


	mUnionRect = mData.mUpdRect;  // save active rectangle
	mUnionRect.NormalizeRect();

	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);

	if ( iSegmRef == TRUE  )
	{
		// translate to window coordinates from world coordinates
 	
		CMyPoint  tStartPt = mData.pRail->GetPoint(0) - offset;
		CMyPoint  tEndPt = mData.pRail->GetPoint(1) - offset;
		    
		// draw white box around the draw area
		if (   mPenSet.GetSolidPen(  2 , GetWhiteColor() ) == NULL ) return ;	 
		DrawPointCross( tStartPt ,   hdc , GetWhiteColor() , 4);
		DrawPointCross( tEndPt ,   hdc , GetWhiteColor() , 4);

		CObjBendRail *pb = IsBendObject( mData.pRail  );
		CFPoint ptx;

		PASSDATASTRUCT tdata;
		tdata.StartPoint = tStartPt;
		tdata.EndPoint = tEndPt;

		if ( pb != NULL )
		{
			tdata.CenterPoint = pb->GetCenterPoint() - offset;
			ptx = CrossArchWithLinePerpendicular( mData.EndPoint  ,  &tdata ); 
		}
		else
			ptx =  CrossSegmentWithLinePerpendicular( mData.EndPoint  ,  &tdata ); 


		// EndPoint has point
		CSegment cs( mData.EndPoint , ptx  );
		cs.DrawSegment( hdc );

		CRect rn( tStartPt.x , tStartPt.y , (int)tEndPt.x  , (int)tEndPt.y );
		rn.NormalizeRect();
		rn.InflateRect(8,8);
		mData.mUpdRect.UnionRect( &rn ,  &mUnionRect ) ; 
		mUnionRect = mData.mUpdRect; 
		
	}

 	OnDrawRect( &mData.mUpdRect ,   hdc ); // draw framing rect 
}

////////////////////////////////////////////////////////////////////////////////////////
//  revised 2016.03.20

void CTempVector::CTempVectorPaintSwitch ( CPoint offset,  HDC hdc )
{
	mData.mUpdRect.left = (int)mData.EndPoint.x-20;
	mData.mUpdRect.top = (int)mData.EndPoint.y-10;

	mData.mUpdRect.right = (int)mData.EndPoint.x;
	mData.mUpdRect.bottom = (int)mData.EndPoint.y;

 // mDebug.CDebugPut("*mData*: [%d,%d]    ",  (int)mData.EndPoint.x , (int)mData.EndPoint.y  );

	PaintControl( &mData, DOUBLELINE | TMPDRAWLINES  | TMP_COLOR_BLUE , hdc   );
	ComputeBandingRectControl( &mData  );


	//ComputeBandingRectSwitch( &mData);
	mUnionRect = mData.mUpdRect;  // save active rectangl
	mUnionRect.NormalizeRect();


	CPenStorage   mPenSet ;  // destruktor called outomatically
	mPenSet.SetDC( hdc);
	if (   mPenSet.GetSolidPen(  4 , GetBlueColor() ) == NULL ) return ;


	if ( iPtRef == TRUE  )
	{
		
		CPoint  tPoint = ptPtRef - offset;

		if (   mPenSet.GetSolidPen(  2 , GetWhiteColor() ) == NULL ) return ;	 

		CSegment cs( mData.EndPoint , tPoint   );
		cs.DrawSegment( hdc );

		mData.EndPoint.DrawCross( hdc , 4);
	    DrawPointCross( tPoint ,   hdc , GetWhiteColor() , 4);
		CRect rn( tPoint.x , tPoint.y , (int)mData.EndPoint.x  , (int)mData.EndPoint.y );
		rn.NormalizeRect();
		rn.InflateRect(8,8);

		mData.mUpdRect.UnionRect( &rn ,  &mUnionRect ) ; 
		mUnionRect = mData.mUpdRect; 

		//mDebug.CDebugPut("*mUnionRect*: [%d,%d] [%d,%d]   ", mUnionRect.left, mUnionRect.top,
		//	mUnionRect.right , mUnionRect.bottom );
	}


	OnDrawRect( &mData.mUpdRect ,   hdc ); // draw framing rect	
 
}


////////////////////////////////////////////////////////////////////////////////////////
//
//
//

void CTempVector::CTempVectorPaintEnd(   HDC hdc )
{
}


void	CTempVector::CTempVectorPaintTrain( HDC hdc ) 
{
// no temporary object
}


 
 
CPoint	CTempVector::CTempVectorGetPoint( int ipoint ) 
{
	if ( ipoint == 0 ) return CMyPoint( mData.StartPoint ); 
 	else return CMyPoint(mData.EndPoint);
}

CRect   CTempVector::CTempVectorGetRect() 
{

	CRect rc = mUnionRect;

	rc.NormalizeRect();

	if ( (rc.left == 0 ) && (rc.top == 0 ) )
	{
		rc = CRect ( (int) mData.StartPoint.x,(int)mData.StartPoint.y,(int)mData.EndPoint.x,(int)mData.EndPoint.y);
		rc.InflateRect(32,32);
	}
	else
 		rc.InflateRect(4,4);

	rc.NormalizeRect();
	return rc;
}

 
void    CTempVector::CTempVectorSetRect(CRect rc)
{
   mUnionRect = rc ;
}
 

DRAWDATASTRUCT *CTempVector::CTempVectorGetDrawData() 
{
	return &mData;
}