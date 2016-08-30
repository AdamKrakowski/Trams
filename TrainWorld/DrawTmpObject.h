
#pragma once

#include "stdafx.h"

#include "StdTrainDef.h"
 

class CTempVector {
public: 
	CTempVector();

	void    CTempVectorSetTmpObject(TMPOBJECT_DRAWDATASTRUCT *tmpObjS );
	void	CTempVectorSetTmpObject( int type);
	void	CTempVectorSetPointReference(  int option ,CPoint pt); 
	void	CTempVectorSetPointReference(  int option ,CFPoint pt); 
 

	void    CTempVectorSetSegmentReference( int option , CObjRail *px  )  ;

	CRect   CTempVectorGetRectToInvalidate(); 

	void	CTempVectorUpdateStart( CPoint start );
	void	CTempVectorUpdateEnd( CPoint end );
	void    CTempVectorPaintTmpObject( CPoint offset,  HDC hdc );
	CPoint	CTempVectorGetPoint( int ipoint );
	CRect   CTempVectorGetRect();
	void    CTempVectorSetRect(CRect rc);
	DRAWDATASTRUCT *CTempVectorGetDrawData();
 
private:
	DRAWDATASTRUCT mData;
	DRAWVAGONDATASTRUCT mDrawVagonData;
	int		mObjectType;
 	CRect   mUnionRect;
	int     iPtRef;
	int     iSegmRef;
	CPoint  ptPtRef;

	void	CTempVectorPaintBend(   HDC hdc );
	void	CTempVectorPaintStright(   HDC hdc );
	void	CTempVectorPaintDblStright( HDC hdc );
	void	CTempVectorPaintSwitch (  CPoint offset, HDC hdc );
	void	CTempVectorPaintEnd(   HDC hdc );
	void	CTempVectorPaintTrain( HDC hdc );
	void	CTempVectorPaintSemaphore( CPoint offset, HDC hdc );
	void	CTempVectorPaintTracker( HDC hdc );
	void	CTempVectorPaintStop( CPoint offset ,HDC hdc );
 
};