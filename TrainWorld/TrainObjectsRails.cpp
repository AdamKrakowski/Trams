
#include "stdafx.h"
#include "Math.h"

#include "StdTrainDef.h"

#include "TrainObjects.h"

#include "Debug.h"
extern CDebug mDebug;

extern CSystem  mSystem;

///////////////////////////////////////////////////////////////////////
 
///---------------------------------------------------------------------
///
/// [20] CObjRail::CObjRail()
/// [21] CObjRail::CObjRail( int tId, CPoint startep, CPoint endep  ) 
/// [22] CObjRail::CObjRail( int tId, CFPoint startep, CFPoint endep) 
/// [23] CObjRail::SetConnection( int index , int value ) 
/// [24] CObjRail::GetPoint( int ep )
/// [25] CObjRail::GetMode( int mode_no) 
/// [26] CObjRail::SetMode( int mode_no , int newmode )
/// [27] CObjRail::GetRailId()
/// [28] CObjRail::GetRailConnId( int endpoint )
/// [29] CObjRail::SetSwitch( int ep, int mode) 
/// [30] CObjRail::GetSwitchStatus(int ep) 
/// [31] CObjRail::SetStopPoint( CPoint pt , int state )
/// [32] CObjRail::GetStopPointState()
/// [33] CObjRail::GetStopPointPoint()
/// [34] CObjRail::DrawMyObject( CPoint offset, HDC hdc , CRect rc)
/// [35] CObjRail::Serialize(CArchive& ar)
/// [36] void CObjRail::SetUndergroundRail( BOOL ion )
/// [37] BOOL CObjRail::IsUndergroundRail() 
///
///-------------------------------------------------------------------
///
/// [40] CObjBendRail::CObjBendRail() 
/// [41] CObjBendRail::CObjBendRail(int tId,CPoint startep,CPoint endep) 
/// [42] CObjBendRail::CObjBendRail(int tId,CFPoint startep,CFPoint endep) 
/// [43] CObjBendRail::GetCenterPoint()  
/// [44] CObjBendRail::DrawMyObject( CPoint offset, HDC hdc , CRect rc) 
/// [45] CObjBendRail::Serialize(CArchive& ar)
/// [46] CObjBendRail::SetCenterPoint( CFPoint cp ) 
///
///---------------------------------------------------------------------
///



extern CObjRailsColl  mCObjRailsColl;
extern CSystem  mSystem;



////////////////////////////////
/// [20] CObjRail::CObjRail()
CObjRail::CObjRail()
{
	for (int i=0;i<4;i++) { m_Connections[i] =0; m_mode[i] =0; }   
	Selected = 0;
	Handled = 0;
	Switch[0]=Switch[1]=STATUS_NOOPER ;
}
/// [21] CObjRail::CObjRail( int tId, CPoint startep, CPoint endep  ) 
CObjRail::CObjRail( int tId, CPoint startep, CPoint endep  ) 
{
	m_ID = tId;				// this object ID
	m_EndPoints[0] = startep;	 
 	m_EndPoints[1] = endep;	
	for (int i=0;i<4;i++) { m_Connections[i] =0; m_mode[i] =0; }   
	Selected = 0;
	Handled =0;
	Switch[0]=Switch[1]=STATUS_NOOPER ;
}
/// [22] CObjRail::CObjRail( int tId, CFPoint startep, CFPoint endep) 
CObjRail::CObjRail( int tId, CFPoint startep, CFPoint endep  ) 
{
	m_ID = tId;				// this object ID
	m_EndPoints[0] =  startep.Round();
	m_EndPoints[1] =  endep.Round();
	for (int i=0;i<4;i++) { m_Connections[i] =0; m_mode[i] =0; }   
	Switch[0]=Switch[1]=STATUS_NOOPER ;
	Selected = 0;
	Handled =0;
}
 
CObjRail::~CObjRail() 
{

}

/// [23] CObjRail::SetConnection( int index , int value ) 
void CObjRail::SetConnection( int index , int value ) 
{
	m_Connections[index] = value;
}
/// [24] CObjRail::GetPoint( int ep )
CFPoint  CObjRail::GetPoint( int ep ) 
{
  return CFPoint( m_EndPoints[ep].x , m_EndPoints[ep].y  );
}

CPoint  CObjRail::GetPPoint( int ep ) 
{  return m_EndPoints[ep]; }

void  CObjRail::SetPoint( int ep , CPoint pt ) 
{
	m_EndPoints[ep] = pt;
}

/// [25] CObjRail::GetMode( int mode_no) 
int   CObjRail::GetMode( int mode_no) 
{
  return m_mode[mode_no];
}
/// [26] CObjRail::SetMode( int mode_no , int newmode )
void  CObjRail::SetMode( int mode_no , int newmode ) 
{
	m_mode[mode_no] = newmode;
}
/// [27] CObjRail::GetRailId()
int CObjRail::GetRailId() 
{ return  (0x7FFF & m_ID) ; }

/// [28] CObjRail::GetRailConnId( int endpoint )
int CObjRail::GetRailConnId( int endpoint )
{ return m_Connections[endpoint];}
/// [29] CObjRail::SetSwitch( int ep, int mode) 
void CObjRail::SetSwitch( int ep, int mode) 
{
	if (ep > 1 ) return;
	Switch[ep] = mode;
//	mDebug.CDebugPut((char *)"Set switch ep:%d mode:%d", ep,mode);
}
/// [30] CObjRail::GetSwitchStatus(int ep) 
int CObjRail::GetSwitchStatus(int ep) 
{ 
	//	mDebug.CDebugPut((char *)"Get switch ep:%d mode:%d", ep,Switch[ep]);
	return Switch[ep]  ;}
/// [31] CObjRail::SetStopPoint( CPoint pt , int state )
 
void CObjRail::SetSelected(int sel) 
{ Selected = sel;}
/// [32] CObjRail::GetStopPointState()
 
/// [34] CObjRail::DrawMyObject( CPoint offset, HDC hdc , CRect rc)
void CObjRail::DrawMyObject( CPoint offset, HDC hdc , CRect rc)
{
	DRAWDATASTRUCT mData;

	mData.StartPoint =  OffsetFPoint (  m_EndPoints[0] , offset );
 	mData.EndPoint =  OffsetFPoint ( m_EndPoints[1] , offset );
	mData.m_Connections[0] = m_Connections[0];
	mData.m_Connections[1] = m_Connections[1];
	mData.m_Connections[2] = m_Connections[2];
	mData.m_Connections[3] = m_Connections[3];

	CPoint  Spt( (int)mData.StartPoint.x , (int) mData.StartPoint.y );
	CPoint  Ept( (int)mData.EndPoint.x , (int) mData.EndPoint.y );
	CPoint  Mpt( GetMidlePoint( Spt , Ept  ) ); 

	if (   ( rc.PtInRect( Spt ) ) ||  ( rc.PtInRect( Ept ) )  || ( rc.PtInRect( Mpt ) ))
	{

		DWORD  dwOptions;
		if ( mSystem.m_SimTestMode == TRUE) dwOptions = TESTMODE;
		else dwOptions = 0;
 
		 if ( IsUndergroundRail() ) dwOptions |= UNDERGND;

 
		if (  (GetObjectType() == ObjStraightRail) || (GetObjectType() == ObjRailEnd)  ) 
		{
			if( Selected == 1)
				PaintStraightRail( &mData, SELECTEDLINE | SINGLELINE | dwOptions , hdc );
			else
				PaintStraightRail( &mData, SINGLELINE | dwOptions , hdc );
		}
	}
}
/// [35] CObjRail::Serialize(CArchive& ar)
void CObjRail::Serialize(CArchive& ar)
{

	//mDebug.CDebugPut((char *)"CObjRail::Serialize(CArchive& ar)");

	if (ar.IsStoring())
	{
		ar << m_ID;
		ar <<  m_EndPoints[0];
		ar <<  m_EndPoints[1];
		ar <<  m_Connections[0];
		ar <<  m_Connections[1];
		ar <<  m_Connections[2];
		ar <<  m_Connections[3];
	}
	else
	{
		ar >> m_ID;
		ar >>  m_EndPoints[0];
		ar >>  m_EndPoints[1];
		ar >>  m_Connections[0];
		ar >>  m_Connections[1];
		ar >>  m_Connections[2];
		ar >>  m_Connections[3];

		if ( GetObjectType() == ObjStraightRail )
		{   // compute speed index on the rail
			if ( GetDistance(  m_EndPoints[0],m_EndPoints[1] ) > mSystem.m_SpeedIndexLimit1 )  m_mode[1] = 1;
			if ( GetDistance(  m_EndPoints[0],m_EndPoints[1] ) > mSystem.m_SpeedIndexLimit2 )  m_mode[1] = 2;
		}


	}
}

/// [36] void CObjRail::SetUndergroundRail( BOOL ion )
void CObjRail::SetUndergroundRail( BOOL ion )
{
  if ( ion == TRUE ) m_ID = m_ID | 0x8000 ;
  else m_ID = m_ID & 0x7FFF;
}
/// [37] BOOL CObjRail::IsUndergroundRail() 
BOOL CObjRail::IsUndergroundRail() 
{
   if ( m_ID & 0X8000 ) return TRUE;
   else return FALSE;
}

////////////////////////////////////////////////////////
/// [40] CObjBendRail::CObjBendRail() 

CObjBendRail::CObjBendRail() 
{
	for (int i=0;i<4;i++) m_Connections[i] =0;
}
/// [41] CObjBendRail::CObjBendRail(int tId,CPoint startep,CPoint endep) 
CObjBendRail::CObjBendRail( int tId, CPoint startep, CPoint endep  ) 
{
 	m_ID = tId;				// this object ID
	m_EndPoints[0] = startep;	 
 	m_EndPoints[1] = endep;	
	for (int i=0;i<4;i++) m_Connections[i] =0;
}
/// [42] CObjBendRail::CObjBendRail(int tId,CFPoint startep, CFPoint endep ) 
CObjBendRail::CObjBendRail( int tId, CFPoint startep, CFPoint endep  ) 
{
 	m_ID = tId;				// this object ID
	m_EndPoints[0] =  startep.Round();
	m_EndPoints[1] =  endep.Round();
	for (int i=0;i<4;i++) m_Connections[i] =0;
}

CObjBendRail::~CObjBendRail() 
{

}
/// [43] CObjBendRail::GetCenterPoint()  
CFPoint   CObjBendRail::GetCenterPoint()  
{
	return mCenterPoint;
}
/// [44] CObjBendRail::DrawMyObject( CPoint offset, HDC hdc , CRect rc) 
void CObjBendRail::DrawMyObject( CPoint offset, HDC hdc , CRect rc)
{
	DRAWDATASTRUCT mData;

	mData.StartPoint =  OffsetFPoint (  m_EndPoints[0] , offset );
 	mData.EndPoint =  OffsetFPoint ( m_EndPoints[1] , offset );
 	mData.CenterPoint =  OffsetFPoint ( mCenterPoint , offset );

	mData.m_Connections[0] = m_Connections[0];
	mData.m_Connections[1] = m_Connections[1];
	mData.m_Connections[2] = m_Connections[2];
	mData.m_Connections[3] = m_Connections[3];

	CPoint cp( (int)mData.CenterPoint.x ,(int)mData.CenterPoint.y );

	CPoint  Spt( (int)mData.StartPoint.x , (int) mData.StartPoint.y );
	CPoint  Ept( (int)mData.EndPoint.x , (int) mData.EndPoint.y );

	if (   ( rc.PtInRect( Spt ) ) ||  ( rc.PtInRect( Ept ) )  )
	{

		DWORD  dwOptions;
		if ( mSystem.m_SimTestMode == TRUE) dwOptions = TESTMODE;
		else dwOptions = 0;

		if ( IsUndergroundRail() ) dwOptions |= UNDERGND;

		if( Selected == 1)
		{
			if ( Handled == 1) 	
				PaintBendRail( &mData, SELECTEDLINE | MODIBEND | dwOptions , hdc );
			else
				PaintBendRail( &mData, SELECTEDLINE | dwOptions , hdc );
		}
		else
			PaintBendRail( &mData, SINGLELINE | dwOptions , hdc );
	}
}
/// [45] CObjBendRail::Serialize(CArchive& ar)
void CObjBendRail::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
        ar << m_ID;
		ar <<  m_EndPoints[0];
		ar <<  m_EndPoints[1];
		mCenterPoint.Serialize( ar);
		ar <<  m_Connections[0];
		ar <<  m_Connections[1];
		ar <<  m_Connections[2];
		ar <<  m_Connections[3];
	}
	else
	{
		ar >> m_ID;
		ar >>  m_EndPoints[0];
		ar >>  m_EndPoints[1];
		mCenterPoint.Serialize( ar);
		ar >>  m_Connections[0];
		ar >>  m_Connections[1];
		ar >>  m_Connections[2];
		ar >>  m_Connections[3];
	}
}
/// [46] CObjBendRail::SetCenterPoint( CFPoint cp ) 
void CObjBendRail::SetCenterPoint( CFPoint cp )
{
	mCenterPoint = cp;
}

