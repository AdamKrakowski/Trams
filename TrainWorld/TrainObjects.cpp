
#include "stdafx.h"
#include "Math.h"

#include "StdTrainDef.h"

#include "TrainObjects.h"

#include "Debug.h"
extern CDebug mDebug;

#include "mainfrm.h"
 
 

///////////////////////////////////////////////////////////////////////
/// [00] CMyObject::CMyObject()
///
/// [10] CObjTramLine::CObjTramLine()
/// [11] int CObjTramLine::GetControlParam( int route_id , int CntId )  
/// [12] int CObjTramLine::GetControlParamByIndex(  int route_id , int CntId ,  int Tram_id )
/// [13] int CObjTramLine::GetControlParam( int route_id , int Tram_id , int CntId )
/// [14] int CObjTramLine::GetControlParamByIndex( int route_id , int CntId )  
/// [15] int CObjTramLine::FindFirstLineItem( int route_id   )  
/// [16] void CObjTramLine::DoLineIndex()  
/// [17] void CObjTramLine::Serialize(CArchive& ar)
///
/// [20] CObjNames::CObjNames()
/// [21] int CObjNames::GetName( int id , int type , char *p )   
/// [22] void CObjNames::Serialize(CArchive& ar)
///
///
/// [30] CObjControls::CObjControls()
//  [31] CObjControls::DrawMyObject(CPoint offset, HDC hdc , CRect rc ) 
//  [32] CObjControls::Serialize(CArchive& ar)
//  [33] void CObjControls::SetTextId( int id ) 
//  [34] int  CObjControls::GetTextId() 
//  [35] CObjControls::SetCenterPoint( CPoint pt)
// [36] CObjControls::SetRailObjectPtr( CObjRail *pObjRail ) 
// [37] CObjControls::SetRailObjectPoint( CPoint  pt  ) 
// [38] CObjControls::SetRailObjectEndpoint( int ep  ) 
// [39] CObjControls::GetCenterPoint() 
// [39] CPoint CObjControls::GetRailControlPoint()
// [40] CObjControls::GetStatus() 
// [41] CObjControls::SetStatus(int is) 
// [42] CObjControls::ToggleStatus( ) 
// [43] void CObjControls::ToggleStatusEx() 
// [44] CObjControls::GetRailObjectPointer()
// [45] CObjControls::GetControlEndpoint()
// [46] CObjControls::GetRailPtrId()
// [47] void    CObjControls::SetRailPtrId(int id ) 
// [48] int  CObjControls::GetControlID() 
// [49] void CObjControls::SetGroupId( WORD id )
// [50] int CObjControls::GetGroupId() 
// [51] int CObjControls::GetTimeOut()
// [52] void CObjControls::SetTimeOut( int tmout) 
// [53] BOOL CObjControls::Signaling() 
// [54] void CObjControls::SetSignal( BOOL bset ) 
///  
// [60] CControlGroupElement::CControlGroupElement()
// [61] void CControlGroupElement::CreateElTable(int size)
// [62] void CControlGroupElement::AddItem( int el   )
// [63] void CControlGroupElement::KickOnElement()
//
// [70]  Funtions - none class
//
// int CheckValidConnections ( CObjRail *p , int epc , CObjRail *p1 , CObjRail *p2 )
// BOOL CheckSwitch(  CObjRail *p , CObjRail *p1 , CObjRail *p2 , int ep , int ep1, int ep2 ) 
// BOOL CheckSwitch(  CObjRail *p , CObjRail *p1  , int ep , int ep1  ) 
// int CheckPhysicalConnection(  int nr , int ep, CObjRail *p , CObjRail *prt[] , int *ept    , int mode)
// int  GoRailOperStatus()
// void  GoSwitchRail( CTramConNode *pnode  , float frem  )
// void GoStright( CTramConNode *pnode , float step )
// void GoBend( CTramConNode *pnode , float step )
// void	MoveNode( CTramConNode *pnode , float step )  
// void	MoveNode( CTramConNode *pnode , float step , int node_nbr)  
// CPoint  GetPointOnRail ( CObjRail   *px , CMyPoint ControlPoint )
// int GetDistanceOfPointFromRail( CObjRail   *px , CMyPoint ControlPoint )
// CObjBendRail *IsBendObject( CObjRail   *px   )
// BOOL CheckIfTheEpIsSwitch( CObjRail *p  , int endpoint )  
// int GetOtherEndEp( CObjRail *pnx  , int ThisId )
// int BrowseTime( CString Cs )
//
///----------------------------------------------------------------------------------


extern CObjRailsColl  mCObjRailsColl;
extern CSystem  mSystem;


 
//////////////////////////////// 
/// [00] CMyObject::CMyObject()
CMyObject::CMyObject()
{

}

CMyObject::~CMyObject() 
{

}
//
void CMyObject::DspInformation() 
{

}

void CMyObject::DrawMyObject( CPoint offset,HDC hdc , CRect rc) 
{

}

void CMyObject::SetObjectType(int itype) 
{
	mObjType = itype;
}

int  CMyObject::GetObjectType() 
{
	return mObjType;
}

void CMyObject::Serialize(CArchive& ar)
{
}

///////////////////////////////
/// [10] CObjTramLine::CObjTramLine()
CObjTramLine::CObjTramLine()
{
	mRecords =0;
}

CObjTramLine::~CObjTramLine() 
{

}
/// [11] int CObjTramLine::GetControlParam( int route_id , int CntId )  
int CObjTramLine::GetControlParam( int route_id , int CntId )  
{

    return GetControlParamByIndex(   route_id ,   CntId )  ;
	// works 
/*
	int mtick = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetSimulationTime();
	
	if ( mtick > 23*60 ) // look for night schedule
	for ( int i=0; i <  mRecords; i++)
		if (  mLineDataBase[i].mLineId == route_id )  
			if (  mLineDataBase[i].mControlId == CntId ) 
				if (  mLineDataBase[i].mType == 1024  ) 
				return mLineDataBase[i].mParam;
	
	// look for daily
	
	for ( int i=0; i <  mRecords; i++)
		if (  mLineDataBase[i].mLineId == route_id )  
			if (  mLineDataBase[i].mControlId == CntId ) 
				return mLineDataBase[i].mParam;
   return -1;
   */
}

/// [12] int CObjTramLine::GetControlParamByIndex(  int route_id , int CntId ,  int Tram_id )
int CObjTramLine::GetControlParamByIndex(  int route_id , int CntId ,  int Tram_id )
{
	int ifirst = FindFirstLineItem( route_id );
	if ( ifirst < 0 ) return -1;

	for ( int i= ifirst; i <  mRecords; i++)
		{
			if (  mLineDataBase[i].mControlId == CntId ) 
				if (  mLineDataBase[i].mType == Tram_id ) 
					return mLineDataBase[i].mParam;
			if ( mLineDataBase[i].mLineId  != route_id ) break;
		}
	return -1;
}


/*
Identyfikator elementu kontrolnego | Control ID	| Route ID	| Tram ID/Option|	Parameter|
Control ID   = 5002	Numer linii o zakresie 0 - 255	N/A.	Numer tramwaju z rozk³adem kompletnym dla linii 
Control ID   = 5003	Numer linii o zakresie 0 - 255	Identyfikator tramwaju ( w zakresie 0 – 999 ) 	Offset do pe³nego rozk³adu jazdy.
*/

// mDebug.CDebugPut("*GetCntPar5*[%d] CntId:%d Type:%d route_id:%d ", i ,mLineDataBase[i].mControlId  , mLineDataBase[i].mType , mLineDataBase[i].mLineId);
// mDebug.CDebugPut("*GetCntPar-Abs2*  nearsch:%02d:%02d ", (int)nearsch/60, (int)nearsch%60);

/// [13] int CObjTramLine::GetControlParam( int route_id , int Tram_id , int CntId )  
int CObjTramLine::GetControlParam( int route_id , int Tram_id , int CntId )  
{
	
	if ( mSystem.m_schenable == TRUE ) return -1;
	
	int nearsch = 1440;  // default for departure from this control - 60*24
	int mtick = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetSimulationTime();  // current tick time - sim time
	// find the first item for line
	int  ifirst = FindFirstLineItem( route_id );  
	if ( ifirst < 0 ) return -1;  // the time is not defined in the programming
	// check if schedule is enabled fir this line
	if (  GetControlParamByIndex(  route_id , 5004 ) == 1 ) return -1; // schedule disabled for this line  [TBI]  

	int ifullsch = 0;  // default for the tram with full schedule
	int ifulloff = 0;  //  offset to current tram
	int itramvirt  = Tram_id;  //  tram ID - default is the input Id
 
	ifullsch = GetControlParamByIndex(  route_id , 5002 ); // get the tram with full reference schedule
	if ( ifullsch >  0)  
	{
		if ( ifullsch != Tram_id )  // do not look for as it is defined by full schedule with offset 0 
		{
			ifulloff = GetControlParamByIndex(  route_id , 5003 , Tram_id ); 
			itramvirt = ifullsch;
		}
	}
	else return -1; // no reference tram defined -always if the tram schedule exist must be marked with the control 5002
	
	// iterate through schedule to find the matching time
	for ( int i= ifirst; i <  mRecords; i++)   
	{
		if ( mLineDataBase[i].mLineId  != route_id ) break; // end of records for the line  

		if (  mLineDataBase[i].mControlId == CntId )   // the control Id is found
			{

				if ( mLineDataBase[i].mType == itramvirt ) // is this the schedule record ?
				   {
						int msched =  mLineDataBase[i].mParam; 
						msched += ifulloff;  // adjust by offset
							// get time diffrence ------
						if (( msched  < 12 ) && ( mtick > 12 ) ) msched += 24*60 ; 
							//if ( abs( mtick - msched  )  < nearsch ) 

						if ( msched <= mtick ) 
							if (   (mtick - msched ) < mSystem.m_LookBackDelay ) // up to 10 min delays  need to start now
								return 300;  // 1 minutes more an go fast

						if ( msched > mtick )  // if the departure greater the current time
							if ( nearsch > msched )  // is this the closer then before
									nearsch = msched ;  // take this as current
				   }
			}
	}

   if ( nearsch < 1440 ) //  was it any record found
   {
	   int  tmmindif = nearsch - mtick  +1 ;  // time diffrence to next departure time .
	   if ( tmmindif > mSystem.m_LookBackDelay ) tmmindif = 1; // out of the start window go now !!
		// mDebug.CDebugPut("*GetControlParam nearch:%d  mtcik:%d  tmdif:%d ", (int)nearsch , mtick,  tmmindif );	
	   return tmmindif*mSystem.m_SimDivisor;   // 320 is default minute divider  
   }
   return -1;  // not found
}


/// [14] int CObjTramLine::GetControlParamByIndex( int route_id , int CntId )  
int CObjTramLine::GetControlParamByIndex( int route_id , int CntId )  
{
	int ifirst = FindFirstLineItem( route_id );

	if ( ifirst < 0 ) return 0;

	int mtick = ((CMainFrame*)(AfxGetApp()->m_pMainWnd))->GetSimulationTime();
	

	if ( mtick > mSystem.m_NightModeStarts ) 
		for ( int i= ifirst; i <  mRecords; i++)
		{
			if (  mLineDataBase[i].mControlId == CntId ) 
				if (  mLineDataBase[i].mType == 999 ) 
					return mLineDataBase[i].mParam;
			if ( mLineDataBase[i].mLineId  != route_id ) break;
		}

	for ( int i= ifirst; i <  mRecords; i++)
	{
			if (  mLineDataBase[i].mControlId == CntId ) 
				return mLineDataBase[i].mParam;
			if ( mLineDataBase[i].mLineId  != route_id ) break;
	}

   return -1;
}

/// [15] int CObjTramLine::FindFirstLineItem( int route_id   )  
int CObjTramLine::FindFirstLineItem( int route_id   )  
{
	if ( route_id < MXINDEXENTRIES   )
		return mLineIndex[route_id];
	else
		return  -1;
}


// sort and index
/// [16] void CObjTramLine::DoLineIndex()  
void CObjTramLine::DoLineIndex()  
{
	if ( mRecords == 0 ) return ;

	for ( int i= 0 ; i <  MXINDEXENTRIES ; i++) mLineIndex[i] = 0;
 
	for ( int j= 0 ; j <  mRecords -1 ; j++)
		for ( int i= 0 ; i <  mRecords -1 ; i++)
			if ( mLineDataBase[i].mLineId > mLineDataBase[i+1].mLineId )
			{
				WORD w1 = mLineDataBase[i].mControlId;
				WORD w2 = mLineDataBase[i].mLineId;
				WORD w3 = mLineDataBase[i].mParam;
				WORD w4 = mLineDataBase[i].mType;

				mLineDataBase[i].mControlId = mLineDataBase[i+1].mControlId;
				mLineDataBase[i].mLineId	= mLineDataBase[i+1].mLineId;
				mLineDataBase[i].mParam		= mLineDataBase[i+1].mParam;
				mLineDataBase[i].mType		= mLineDataBase[i+1].mType;

				mLineDataBase[i+1].mControlId = w1;
				mLineDataBase[i+1].mLineId	= w2;
				mLineDataBase[i+1].mParam	= w3;
				mLineDataBase[i+1].mType	= w4;
			}

    // index  0 is normally not used since there is no 0 line available - if so then error
 
	int ln = mLineDataBase[0].mLineId;
	if ( ln <  MXINDEXENTRIES )
		mLineIndex[ ln ] = 0 ;  

	for ( int i = 1 ; i <  mRecords   ; i++)
	{
		if ( mLineDataBase[i].mLineId != ln )
		{
			ln = mLineDataBase[i].mLineId;	
			if ( ln <  MXINDEXENTRIES )
				mLineIndex[ ln ] = i ;
		}
	}

}


/// [17] void CObjTramLine::Serialize(CArchive& ar)
void CObjTramLine::Serialize(CArchive& ar)
{
	int i;
	CString CVersion;

	if (ar.IsStoring())
	{
		CVersion=_T("001");
		ar << CVersion;
		ar <<  mRecords;
		for ( i=0; i<mRecords;i++)
		{
			ar <<  mLineDataBase[i].mControlId;
			ar <<  mLineDataBase[i].mLineId;
			ar <<  mLineDataBase[i].mParam;
			ar <<  mLineDataBase[i].mType;
		}
	}
	else
	{
		ar >> CVersion;
		ar >> mRecords;
		for ( i=0; i<mRecords;i++)
		{
			ar >>  mLineDataBase[i].mControlId;
			ar >>  mLineDataBase[i].mLineId;
			ar >>  mLineDataBase[i].mParam;
			ar >>  mLineDataBase[i].mType;
		}

		DoLineIndex(); 
	}

}




///////////////////////////////
/// [20] CObjNames::CObjNames()
CObjNames::CObjNames()
{
	mRecords = 0;
	mLastId = 0;
}

CObjNames::~CObjNames() 
{

}
/// [21] int CObjNames::GetName( int id , int type , char *p )   
int CObjNames::GetName( int id , int type , char *p )   
{

	for ( int i=0; i <  mRecords; i++)
		if (  mNameDataBase[i].mId ==  id )  
			if (  mNameDataBase[i].mType == type ) 
			{
				strcpy_s(  p , 30 ,  mNameDataBase[i].mName );
				return 1;
			}
   return 0;
}
/// [22] void CObjNames::Serialize(CArchive& ar)
void CObjNames::Serialize(CArchive& ar)
{
	int i;
	CString CVersion;

	if (ar.IsStoring())
	{
		CVersion=_T("001");
		ar << CVersion;
		ar <<  mRecords;
		ar <<  mLastId;
		for ( i=0; i<mRecords;i++)
		{
			ar <<  mNameDataBase[i].mId;
			ar <<  mNameDataBase[i].mType;
			ar <<  mNameDataBase[i].mName;
		}
	}
	else
	{
		ar >> CVersion;
		ar >> mRecords;
		ar >> mLastId;
		 
		for ( i=0; i<mRecords;i++)
		{
			ar >>  mNameDataBase[i].mId;
			ar >>  mNameDataBase[i].mType;
			ar >>  mNameDataBase[i].mName;
		}
		 
	}
}



 
////////////////////////////////
//  [30] CObjControls::CObjControls()
CObjControls::CObjControls()
{

}
CObjControls::CObjControls(int tId,  CPoint endep ) 
{
	m_ID = tId;				// this object ID
	m_CenterPoint = endep;	 
	status = STATUS_NOOPER;
	m_group = 0;
	m_timeout = DEF_TIMEOUT;
	m_text_id = 0;
	m_isMonoStab =0;
}
CObjControls::~CObjControls() 
{

}

//  [31] CObjControls::DrawMyObject(CPoint offset, HDC hdc , CRect rc ) 
void CObjControls::DrawMyObject( CPoint offset, HDC hdc , CRect rc )
{
	DRAWDATASTRUCT mData;

	if ( mpObjRail == NULL ) return;

	mData.CenterPoint = OffsetFPoint (  m_CenterPoint , offset );

	mData.StartPoint = OffsetFPoint (  mpObjRail->GetPoint(0) , offset );
	mData.EndPoint =  OffsetFPoint (  mpObjRail->GetPoint(1)  , offset );
	mData.Turn = mep;
	mData.ThisID = status;

	mData.pRail = mpObjRail;  

	CMyPoint Ept(mData.CenterPoint);

	if (   rc.PtInRect( Ept )   )
		{
		if ( mObjType ==  ObjStop ) PaintStop( &mData, 0 ,   hdc );
		if ( mObjType ==  ObjSwitch )  PaintSwitch( &mData, 0 ,   hdc );
		if ( mObjType ==  ObjSem )  PaintSem( &mData, 0 ,   hdc );
		}
}
//  [32] CObjControls::Serialize(CArchive& ar)
void CObjControls::Serialize(CArchive& ar)
{
	int it;
	if (ar.IsStoring())
	{
		ar << mObjType; // not used but store  - from the base class  int - only 16 bytes used
		ar << m_ID;   // int  too big size only 16 bits used at most
		ar << m_CenterPoint;
		//WORD m_ObjRailID;

		if ( mpObjRail != NULL )
		m_ObjRailID = mpObjRail->GetRailId();
		else
		m_ObjRailID =0;

		ar << m_ObjRailID;
		ar <<  mPt;

//m_text_id =0;

		it = m_text_id << 16 ;
		it += m_isMonoStab << 8 ;
		it += mep;



		ar << it;

		//ar <<  mep; // endpoint  only one byte used
		it = status + ( m_timeout << 16 ); 
		ar <<  it;
		ar <<   m_group;
	}
	else
	{
		ar >> mObjType;
		ar >> m_ID;
		ar >> m_CenterPoint;
		ar >> m_ObjRailID;
		ar >>  mPt;

		ar >>  it;
//if (  mObjType ==  ObjSem)
//mDebug.CDebugPut((char *)" It: %X ", it   );

		mep = it&0x00FF;
		m_isMonoStab = ( it&0xFF00)  >> 8 ;
		m_text_id = it >> 16;

		if ( m_isMonoStab > 1 )
				m_isMonoStab = 0;

//if (  mObjType ==  ObjSem)
//mDebug.CDebugPut((char *)" - %d %d", (int)mep , (int)m_isMonoStab  );

		//ar >>  mep; // endpoint

//m_text_id =0;


		ar >> it ;
		status = it&0xFFFF;
		m_timeout = it >> 16;
		if ( m_timeout == 0 ) m_timeout = DEF_TIMEOUT;
		ar >>  m_group;
	}
}

//  [33] void CObjControls::SetTextId( int id ) 
void CObjControls::SetTextId( int id ) 
{	m_text_id  = id;}

//  [34] int  CObjControls::GetTextId() 
int  CObjControls::GetTextId() 
{ return m_text_id; }
//  [35] CObjControls::SetCenterPoint( CPoint pt)
void CObjControls::SetCenterPoint( CPoint pt)
{m_CenterPoint = pt;}

// [36] CObjControls::SetRailObjectPtr( CObjRail *pObjRail ) 
void CObjControls::SetRailObjectPtr( CObjRail *pObjRail ) 
{
	mpObjRail = pObjRail;
	if ( pObjRail != NULL )
	   m_ObjRailID = pObjRail->GetRailId();
}
// [37] CObjControls::SetRailObjectPoint( CPoint  pt  ) 
void CObjControls::SetRailControlPoint( CPoint  pt  ) 
{mPt = pt;}
// [38] CObjControls::SetRailObjectEndpoint( int ep  ) 
void CObjControls::SetRailObjectEndpoint( int ep  ) 
{mep = ep;}
// [39] CObjControls::GetCenterPoint() 
CPoint CObjControls::GetCenterPoint() 
{  return m_CenterPoint;}
CPoint CObjControls::GetRailControlPoint()
{  return mPt;}
// [40] CObjControls::GetStatus() 
int CObjControls::GetStatus() 
{ return status;}
// [41] CObjControls::SetStatus(int is) 
void CObjControls::SetStatus(int is) 
{ status = is;}
// [42] CObjControls::ToggleStatus( ) 
void CObjControls::ToggleStatus() 
{
	if ( status == STATUS_NOOPER  ) status = STATUS_SET;
 	else status = STATUS_NOOPER;
}

// [43] void CObjControls::ToggleStatusEx() 
void CObjControls::ToggleStatusEx() 
{	status = (status+1)%3;}
// [44] CObjControls::GetRailObjectPointer()
CObjRail *CObjControls::GetRailObjectPointer()
{ return mpObjRail ;}
// [45] CObjControls::GetControlEndpoint()
int  CObjControls::GetControlEndpoint()
{ return mep;}
// [46] CObjControls::GetRailPtrId()
WORD CObjControls::GetRailPtrId()  //	WORD m_ObjRailID;
{ return m_ObjRailID ;}

// [47] void    CObjControls::SetRailPtrId(int id ) 
void    CObjControls::SetRailPtrId(int id ) 
{  m_ObjRailID = id ;}

// [48] int  CObjControls::GetControlID() 
int  CObjControls::GetControlID()   ///m_ID
{ return m_ID ;}

// [49] void CObjControls::SetGroupId( WORD id ) 
void CObjControls::SetGroupId( WORD id ) 
{
	m_group = id;
}
// [50] int CObjControls::GetGroupId() 
int CObjControls::GetGroupId() 
{ return m_group ;}

// [51] int CObjControls::GetTimeOut()
int CObjControls::GetTimeOut()  //	int  m_timeout;
{
	return m_timeout;
}

// [52] void CObjControls::SetTimeOut( int tmout) 
void CObjControls::SetTimeOut( int tmout) 
{
	m_timeout = tmout;
}

// [53] BOOL CObjControls::Signaling() 
BOOL CObjControls::Signaling() 
{
	if ( m_signal == 1 ) return TRUE ;
	else return FALSE;
}

// [54] void CObjControls::SetSignal( BOOL bset ) 
void CObjControls::SetSignal( BOOL bset )   /// NEW
{
	if ( bset == TRUE ) m_signal = 1;
	else m_signal = 0;
}

BOOL CObjControls::IsMonostab()
{
	if ( m_isMonoStab == 0 )
	return FALSE;
	else
	return TRUE;
}

void CObjControls::SetMonoStab( BOOL bset)
{
    if ( bset == TRUE) m_isMonoStab = 1;
	else m_isMonoStab = 0;
}


 // [60] CControlGroupElement::CControlGroupElement()

CControlGroupElement::CControlGroupElement(){mptr = NULL;miPtr =0;mMono=0;};
CControlGroupElement::~CControlGroupElement(){ if (mptr != NULL )  delete mptr; };

 // [61] void CControlGroupElement::CreateElTable(int size)

void CControlGroupElement::CreateElTable(int size)
{
	mSize = size;
	mptr = new int[size+2];

//mDebug.CDebugPut("*CreateElTable*: %d Size: %d ",  mSize ,  mSize );

	mTimeOut = DEF_TIMEOUT;     // need to define idependentrly !!
	mCurStopPtr=0;     // circular pointer  to the stops in group  -if next reset CurState to yellow
	mCurState = 0;
}

 // [62] void CControlGroupElement::AddItem( int el   )
void CControlGroupElement::AddItem( int el   )
{
	if ( miPtr  < mSize ) 
		{ 
			mptr[miPtr++] =el;
			CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[el];
			p->SetStatus(STATUS_SET_YELLOW); 

			if ( p->IsMonostab() ) mMono =1;

//mDebug.CDebugPut("*AddItem*: %d Size: %d ", miPtr-1 , mSize );

		}
}

//
//  changing the light in group 
//
 // [63] void CControlGroupElement::KickOnElement()
void CControlGroupElement::KickOnElement()
{
	
	if ( mMono == 1 ) {  KickMonoElement(); return;}
	
	if ( mTimeOut > 0 ) {  mTimeOut -=1; return;}
	
//mDebug.CDebugPut("*KickOnElement*:mCurState %d mCurStopPtr: %d ", mCurState ,  mCurStopPtr );

	if ( mCurState == 0 )  // next green/red
		{  
			for ( int i =0; i < mSize ; i++)  
			{	// set all red
				CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
				p->SetStatus(STATUS_SET_STOP); 
			}
			// set green for the choosen one
			CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[mCurStopPtr]];
			p->SetStatus(STATUS_SET_GO);
			// remember timeout for yellow
			m_yellow_TimeOut = p->GetTimeOut() ;
			if ( m_yellow_TimeOut < DEF_TIMEOUT ) m_yellow_TimeOut = DEF_TIMEOUT;
 
			mCurState = 1; 
			mTimeOut = DEF_TIMEOUT;  // time out for green
			return ;
		}

	if ( mCurState == 1 )  // need to set all  yellow
		{  
			// clear signaling from prevoius control if any
			CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[mCurStopPtr]];
			p->SetSignal(FALSE);

			// set yellow time out
			mTimeOut = m_yellow_TimeOut;
			if ( mTimeOut < DEF_TIMEOUT ) mTimeOut = DEF_TIMEOUT;

			for ( int i =0; i < mSize ; i++)
			{
				CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
				p->SetStatus(STATUS_SET_YELLOW); 
			}

			mCurState = 0;
			mCurStopPtr+=1;  // next element in group will be green
			if ( mCurStopPtr >= mSize ) mCurStopPtr=0;

			// priority can be changed if there is waiting train signalling
			for ( int i =0; i < mSize ; i++)  
			{	// set all red
				CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
				if ( p->Signaling() )
				{
					mCurStopPtr = i;
				}
			}


		}
	 
}

// [63] void CControlGroupElement::KickMonoElement() 
void CControlGroupElement::KickMonoElement()
{
	if ( mTimeOut > 0 ) {  mTimeOut -=1; return;}
	if ( mCurState == 0 )  // need to light red & green
		{  // get the pointer to current control
			CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[mCurStopPtr]];

			if ( p->IsMonostab() == TRUE )  // can check if any other party signaling
			{
				for ( int i =0; i < mSize ; i++)  
				{	// set all red
					CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
					if ( p->IsMonostab() == FALSE )  p->SetStatus(STATUS_SET_STOP); 
				}
				// check if any unstable is signaling
				for ( int i =0; i < mSize ; i++)  
				{	// is any signaling ?
					CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
					if ( p->IsMonostab() == FALSE )
						if ( p->Signaling() )
							{  // yes use this and go to yellow
							mCurStopPtr = i;
							m_yellow_TimeOut = p->GetTimeOut() ; // get time for yellow
							if ( m_yellow_TimeOut < DEF_TIMEOUT ) m_yellow_TimeOut = DEF_TIMEOUT;
							mTimeOut = 4 ;  // current time out  wait for yellow can be shorter 
							mCurState = 1;
							return;
							}
				}
				// as we got here nobody from not monostab signal so set green to all mono stab
				for ( int i =0; i < mSize ; i++)  
				{	// is any signaling ?
					CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
					if ( p->IsMonostab() == TRUE )  p->SetStatus(STATUS_SET_GO);	
				}
				mTimeOut = DEF_TIMEOUT;  // time out for green
				return ;
			}
			else
			{    // the current selection is one of unstabile check if sselected unstabile is signalling		
				if ( p->Signaling() )
				{   // let him go on green but first stop all others
						for ( int i =0; i < mSize ; i++)  
							{	// set all red
							CObjControls *px = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
							if (px  != p )  px->SetStatus(STATUS_SET_STOP); 
							}
						// then let this go
						p->SetStatus(STATUS_SET_GO); 
						mTimeOut = DEF_TIMEOUT << 2 ; // def for green
						p->SetSignal(FALSE);  // after the time out we get back below
						return ;
				}
				//  we opened green for signalling and now need to get back to stable situation				
				for ( int i =0; i < mSize ; i++)  
					{	// set all red
						CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
						if ( p->IsMonostab() == TRUE ) { mCurStopPtr = i; p->SetStatus(STATUS_SET_GO); }
						else p->SetStatus( STATUS_SET_STOP );
					}
				mTimeOut = DEF_TIMEOUT; 
				return;
			} // unstable 

			mTimeOut = DEF_TIMEOUT;  // should not get here
			return ;
		}

	if ( mCurState == 1 )  // need to set all  yellow for the while
		{  
			mTimeOut = m_yellow_TimeOut; // use the yellow timeout out of signaling control
			for ( int i =0; i < mSize ; i++)
			{
				CObjControls *p = (CObjControls *) mCObjRailsColl.mObjTable[mptr[i]];
				p->SetStatus(STATUS_SET_YELLOW); 
			}
			mCurState = 0;
		} 
}


/////////////////////////////////////////////////////////////////////////////////////
//
//      (p) 
//          pt_start = p->GetPoint( ( ep +1)&1   )
//          or 
//					pt_start = p->GetPoint( ( ep +1)&1   )
//					LineA( p->GetPoint( ( ep +1)&1   ) , p->GetCenterPoint() )
//					LineB( pt_end, p->GetCenterPoint() )
//					LineC  = Perpendicular(LineB)
//					pt_start = Cross(Line C , Line A )
//			-------------------------------
//          pt_end = p->GetPoint( ep );
//
//		(p1)(p2)
//
//          pt_start = p->GetPoint(  ep  )
//			---------------------------------
//			pt_end = p->GetPoint( ep1 +1)&1 );
//          or 
//					pt_end = p->GetPoint( ( ep +1)&1   )
//					LineA( pt_end , p->GetCenterPoint() )
//					LineB( pt_start, p->GetCenterPoint() )
//					LineC  = Perpendicular(LineB)
//					pt_end = Cross(Line C , Line A )
//           
//
//

//   one or two logical connection  matches one or two physical connection 
//
//
//


int CheckValidConnections ( CObjRail *p , int epc , CObjRail *p1 , CObjRail *p2 )
{
	int tmpId1 = p->GetRailConnId( epc );  // logical connection
	int tmpId2 = p->GetRailConnId(epc +1 ); // logical connection
	int s1 = 0;
	int s2 = 0;

	//  p1 or p2 , physically connected , are the ones in the p connection edpoint is connected to epc
	if (  (p1->GetRailId () == tmpId1 ) || ( p2->GetRailId () == tmpId1 )  ) s1 = 1;

	//  p1 or p2 is connected to epc + 1
	if (  (p1->GetRailId () == tmpId2 ) || ( p2->GetRailId () == tmpId2 )  ) s2 = 1;
	 
	return s1+s2 ;
}



BOOL CheckSwitch(  CObjRail *p , CObjRail *p1 , CObjRail *p2 , int ep , int ep1, int ep2 ) 
{
	if  (	(CheckSwitch(  p ,  p1  ,   ep , ep1  ) == TRUE ) &&
			(CheckSwitch(  p ,  p2  ,   ep , ep2  ) == TRUE )  )
				return TRUE;
	 return FALSE;	
}


int CheckSwitchOtherEndValidConnection ( int tId , int epc ,  CObjRail *p1  , int mode  )
{
	if ( p1->GetRailConnId( epc << 1 )  == tId)  return 0;
	mDebug.CDebugPut("*Error A* || Id:%d Ido:%d epo:%d ,oep:%d ) ", tId , p1->GetRailId()  , epc,  p1->GetRailConnId( epc << 1 )   );
	if ( mode == 1 )
	{
		p1->SetConnection( epc << 1 , tId ); 
		mDebug.CDebugPut("*Fixing A* || Id:%d Ido:%d epo:%d ,oep:%d ) ", tId , p1->GetRailId()  , epc,  p1->GetRailConnId( epc << 1 )   );
		//p1->SetConnectionId( 1 + (epc << 1) , 0 ); 
		return 0 ;
	}
	return 1;
}





BOOL CheckSwitch(  CObjRail *p , CObjRail *p1  , int ep , int ep1  ) 
{
		
//	mDebug.CDebugPut("*ConfSwitch*:   " );  
 
	CFPoint pt_start = p->GetPoint( ( ep +1)&1   );
	CFPoint pt_end = p->GetPoint(   ep );
	
	if ( p->GetObjectType() != ObjStraightRail )
	{  // asume bend
		CObjBendRail *pb = ( CObjBendRail *)p; 
		CLineObject mALine( pt_end , pb->GetCenterPoint() );
		CLineObject mBLine( mALine.GetA() , mALine.GetB() , pt_end );
		CLineObject mCLine( mBLine.GetA() , mBLine.GetB() , pt_start );
		pt_start =  CrossOfTwoLines ( mBLine , mCLine ) ;
	}
		

//mDebug.CDebugPut("**CheckSwitch(p):Start(%d,%d) Arrow(%d,%d) ", (int)pt_start.x , (int)pt_start.y , (int)pt_end.x ,(int)pt_end.y  ); 


	CFPoint pt1_start = p1->GetPoint(  ep1   );
	CFPoint pt1_end = p1->GetPoint(   ( ep1 +1)&1  );

	if ( p1->GetObjectType() != ObjStraightRail )
	{  // asume bend
		CObjBendRail *pb = ( CObjBendRail *)p1; 
		CLineObject mALine( pt1_start , pb->GetCenterPoint() );
		CLineObject mBLine( mALine.GetA() , mALine.GetB() , pt1_start );
		CLineObject mCLine( mBLine.GetA() , mBLine.GetB() , pt1_end );
		pt1_end =  CrossOfTwoLines (  mBLine , mCLine  ) ;
	}


//mDebug.CDebugPut("**CheckSwitch(p1):Start(%d,%d) Arrow(%d,%d) ", (int)pt1_start.x , (int)pt1_start.y , (int)pt1_end.x ,(int)pt1_end.y  ); 
//mDebug.CDebugPut("**CheckSwitch(p2):Start(%d,%d) Arrow(%d,%d) ", (int)pt2_start.x , (int)pt2_start.y , (int)pt2_end.x ,(int)pt2_end.y  ); 

	float a1 =  GetAbsAngleOfTwoVectors (pt_start , pt_end  , pt1_start , pt1_end );



//mDebug.CDebugPut("**:ID1:%d  ID2[%d] ID3[%d] ", p->GetRailId(), p1->GetRailId(),p2->GetRailId() ); 
//mDebug.CDebugPut("**:Angles :%6.2f %6.2f  ",a1,a2 ); 

	if (  a1 < 90    ) return TRUE;

/*
mDebug.CDebugPut("**CheckSwitch(p):Start(%d,%d) Arrow(%d,%d) ", (int)pt_start.x , (int)pt_start.y , (int)pt_end.x ,(int)pt_end.y  ); 
mDebug.CDebugPut("**CheckSwitch(p1):Start(%d,%d) Arrow(%d,%d) ", (int)pt1_start.x , (int)pt1_start.y , (int)pt1_end.x ,(int)pt1_end.y  ); 
mDebug.CDebugPut("**CheckSwitch(p2):Start(%d,%d) Arrow(%d,%d) ", (int)pt2_start.x , (int)pt2_start.y , (int)pt2_end.x ,(int)pt2_end.y  ); 
mDebug.CDebugPut("**FALSE:ID1:%d  ID2[%d] ID3[%d] ", p->GetRailId(), p1->GetRailId(),p2->GetRailId() ); 
mDebug.CDebugPut("**FALSE:Angles :%6.2f %6.2f  ",a1,a2 );
*/

	return FALSE;
	
}

 
int CheckPhysicalConnection(  int nr , int ep, CObjRail *p , CObjRail *prt[] , int *ept    , int mode)
{
	int tId = p->GetRailId();  // this rail Id
	CFPoint tPt = p->GetPoint( ep ) ;
	int  nbrErrors = 0;

	if ( nr == 0 ) 
	{	// error always but for the endpoint
		if ( mode == 3 )  
		{
			mDebug.CDebugPut("*Warning:Floating rail endpoint * || Id:%d ||", tId );
			return 1;
		}
		return 0;  
	}

	if ( nr > 3 ) 
	{	// error always
		mDebug.CDebugPut("*Overloaded rail* || Id:%d ||", tId );
		return 1;  
	}

	//  (p) rail data 
	int epc = ep << 1;	
	int ic1 = p->GetRailConnId( epc );
	int ic2 = p->GetRailConnId( epc+1 );
	// at least one phycsicall connection to (p) rail 
	CObjRail *p1 = prt[0];
	int iId1 = p1->GetRailId();
	int epc1 = ept[0] << 1;

 

	if ( nr == 1 )   // only one addtional rail is physically connected  to the 'p' - rail to rail single physical connection
		{
			if ( ic2  != 0  )  
			{   // the logical connection should have logical connection on the first  conn of the endpoint  
				mDebug.CDebugPut("*Error 00* || Id:%d Phy Id:(%d) LogIds:(%d,%d)  ", tId , iId1 , ic1 ,  ic2 );
				nbrErrors +=1;
				if ( mode == 1 )  
					{
						p->SetConnection( epc +1 , 0 );
						ic2 = p->GetRailConnId( epc+1 );
						mDebug.CDebugPut("*Fixing 00 || Id:%d Phy Id:(%d) LogIds:(%d,%d)  ", tId , iId1 , ic1 , ic2  );
						nbrErrors -=1;
					}
			}
			if ( ic1 !=  iId1 )  
			{   // the logical and physicall connection are diffrent
				mDebug.CDebugPut("*Error 01* || Id:%d Phy Id:(%d) LogIds:(%d,%d)  ", tId , iId1 , ic1 ,  ic2 );
				nbrErrors +=1;
				if ( mode == 1 )  
					{
						p->SetConnection( epc, iId1 );
						ic1 = p->GetRailConnId( epc);
						mDebug.CDebugPut("*Fixing 00 || Id:%d Phy Id:(%d) LogIds:(%d,%d)  ", tId , iId1 , ic1 , ic2  );
						nbrErrors -=1;
					}			
			}
			// this should be corrected  at p1 evaluation
			if ( p1->GetRailConnId( epc1+1 ) != 0 )  
				mDebug.CDebugPut("*Warning 10* || Id:%d Phy Id:(%d) LogId:(%d)=%d ", iId1 , tId , epc1+1, p1->GetRailConnId( epc1+1 ) );				
			if ( p1->GetRailConnId( epc1 ) !=  tId)  
				mDebug.CDebugPut("*Warning 11* || Id:%d Phy Id:(%d) LogId:(%d)=%d ", iId1 , tId , epc1, p1->GetRailConnId( epc1 ) );				

			return nbrErrors;
		}

	// must have more then one physically connected rails
	CObjRail *p2 = prt[1];
	int iId2 = p2->GetRailId();
	int epc2 = ept[1] << 1;

	if ( nr == 3 )  // special cases of double switch
	 {		//mDebug.CDebugPut("*******Special handling******* || #:%d   ", nr );	
			CObjRail *p3 = prt[2];
			int epc3 = ept[2] << 1;
			int cnt = 0;
			int phcnt = 0;
			int Id[4];
			int IdPtr =0;
			int iId3 = p3->GetRailId();

			if ( CheckSwitch(   p ,  p1  ,  ep , ept[0] )  == TRUE )	// physical conn OK
			{
				phcnt++; Id[IdPtr++] = iId1;
				if ( (ic1 == iId1) ||  (ic2 == iId1)    ) cnt++;		// logical connection OK
			}

			if ( CheckSwitch(   p ,  p2  ,  ep , ept[1] )  == TRUE )	// physical conn OK
			{
				phcnt++; Id[IdPtr++] = iId2;
				if ( (ic1 == iId2 ) ||  (ic2 == iId2 )    ) cnt++;		// logical connection OK
			}

			if ( CheckSwitch(   p ,  p3  ,  ep , ept[2] )  == TRUE )	// physical conn OK
			{
				phcnt++; Id[IdPtr++] = iId3;
				if ( (ic1 == iId3 ) ||  (ic2 == iId3 )    ) cnt++;		// logical connection OK
			}

			if ( cnt != 2 ) // must have two OK connection 
			{					
				if ( phcnt != 2 )
				{
					nbrErrors +=1;
					mDebug.CDebugPut("*Error 2* || Physical: Id:%d Id1:%d Id2:%d Id3:%d ", tId , iId1 , iId2 , iId3 );
					mDebug.CDebugPut("*NON!!!!* || Physical EPs:( %d , %d , %d ,%d ) ",   ep , ept[0] ,  ept[1] ,  ept[2]);
					mDebug.CDebugPut("*Fixable* || Logical Conn(%d)=%d  Conn(%d)=%d ) ",   epc , ic1   , epc + 1,  ic2  );
				}
				else
				{   
					nbrErrors +=1;
					mDebug.CDebugPut("*Error 3* || Physical: Id:%d Id1:%d Id2:%d Id3:%d ", tId , iId1 , iId2 , iId3 );
					mDebug.CDebugPut("*       * || Physical EPs:( %d , %d , %d ,%d ) ",   ep , ept[0] ,  ept[1] ,  ept[2]);
					mDebug.CDebugPut("*Fixable* || Logical Conn(%d)=%d  Conn(%d)=%d ) ",   epc , ic1   , epc + 1,  ic2  );
					if ( mode == 1 )  
					{
						p->SetConnection( epc, Id[0] );
						p->SetConnection( epc+1, Id[1] );
						nbrErrors -=1;
					}
				}

				return nbrErrors;
			}

			// two ok connections from (p) rail
			return nbrErrors;
	 }


	//  check if switch candidate

	if ( CheckSwitch(   p ,  p1 ,  p2 ,   ep ,   ept[0] ,  ept[1]) == FALSE) 
	{   // physically two physical connections but not a switch
		// need to check if this physical connection has proper one  logical connector
		if (( ic1 == 0 ) || ( ic2 == 0 ))  // need to be one zero at leat
			if ( CheckValidConnections ( p , epc , p1 , p2 ) == 1 )  	// one or two logical connection  matches one or two physical connection 
				{   // one physical to logical matches
                     return nbrErrors;
				}

		{  // one of the  logical connections  is wrong ( or both )
			nbrErrors +=1;
			mDebug.CDebugPut("*Error 4* || Physical: Id:%d Id1:%d Id2:%d  ", tId ,  iId1 ,  iId2 );
			mDebug.CDebugPut("*       * || Physical EPs:( %d , %d , %d ) ",   ep , ept[0] ,  ept[1] );
			mDebug.CDebugPut("*       * || Logical  Conn[%d]:%d , %d , %d ) ",   epc , ic1   , epc + 1,  ic2  );
		}

		if ( CheckValidConnections ( p , epc , p1 , p2 ) == 2 )  
				mDebug.CDebugPut("*Info 420* || Physical & logical match Id:%d Id1:%d Id1:%d ", tId ,iId1 ,  iId2   );

		if ( CheckValidConnections ( p , epc , p1 , p2 ) == 1 )  
		{
			int tmpId = p->GetRailConnId( epc );
			int ii = 0;
			if ( tmpId == 0 ) { tmpId = p->GetRailConnId( epc +1); ii =1;}
			// must be one of the other rail id
			mDebug.CDebugPut("*Info 421* || Physical & logical match Id:%d conn(%d) Id:%d ", tId , epc+ii,    tmpId  );
		}

		if ( CheckValidConnections ( p , epc , p1 , p2 ) == 0 )  
			mDebug.CDebugPut("*Info 422* || Physical & logical both diffrent Phys(%d,%d) Logical(%d,%d)" ,iId1 ,  iId2 ,ic1,ic2);

		//  check p <--> p1 physical configuration
		if ( CheckSwitch(   p ,  p1  ,  ep , ept[0] )  == TRUE )
		{  // this is the one
			mDebug.CDebugPut("*Info 423* || Id:%d Id1:%d  OK  ", tId ,  iId1  );
			if ( mode == 1 )
				{  // update logical configuration
					mDebug.CDebugPut("*Info 424* || FIXING Id:%d epc:%d Id1:%d", tId , epc, iId1  );					
					p->SetConnection( epc  ,  iId1 );
					p->SetConnection( epc+1  , 0 );
					nbrErrors -=1;
					return nbrErrors;
				}
		}
		//  check p <--> p2 physical configuration
		if ( CheckSwitch(   p ,  p2  ,  ep , ept[1] )  == TRUE )
		{  // this is the one
			mDebug.CDebugPut("*Info 425* || Id:%d Id2:%d  OK  ", tId ,  iId2  );
			if ( mode == 1 )
				{  // update logical configuration
					mDebug.CDebugPut("*Info 426* || FIXING Id:%d epc:%d Id1:%d", tId , epc,  iId2   );	
					p->SetConnection( epc  ,  iId2 );
					p->SetConnection( epc+1  , 0 );
					nbrErrors -=1;
					return nbrErrors;
				}
		}				
		return nbrErrors;
	}
	else
	{ //   switch candidate

		if (( ic1 == 0 ) || ( ic2 == 0 ))  // one or both !- 0
		{	// physical switch but no logical switch - one of two logical connections zero ( or both )
			mDebug.CDebugPut("*Error 8* || Id:%d EP:( %d , %d , %d ) ", tId ,  ep , ept[0] ,  ept[1] );
			mDebug.CDebugPut("*       * || IdR:%d  Idrr:(  %d , %d ) ", ic1 , iId1 ,  iId2 );
			mDebug.CDebugPut("*       * || IdR:%d  Idrr:(  %d , %d ) ", ic2 , iId1 ,  iId2 );
			nbrErrors +=1;
			if ( mode == 1 )
				{	// set based on physical connection 
					mDebug.CDebugPut("*Info 801 Fixing * || Id:%d Id1:%d Id2:%d   ", tId ,iId1 ,  iId2 );
					p->SetConnection( epc  , iId1 );
					p->SetConnection( epc+1  , iId2);
					nbrErrors -=1;
					return nbrErrors;
				}
		}

		if (( ic1 != 0 ) && ( ic2 != 0 ))
		{   // improper logical connection
					
			//if ( tId == 1651 )
			//	mDebug.CDebugPut("*GENERAL 2 * || Id:%d Id1:%d Id2:%d   ", tId ,iId1 ,  iId2 );		
			
			if ( CheckValidConnections ( p , epc , p1 , p2 ) < 2 ) 	
					{   // wrong logical connection - one or both are wrong
						nbrErrors +=1;
						mDebug.CDebugPut("*Error 9* || Id:%d EP:( %d , %d , %d ) ", tId ,  ep , ept[0] ,  ept[1] );
						mDebug.CDebugPut("*       * || IdR:%d  Idrr:(  %d , %d ) ", ic1  , iId1 ,  iId2);
						mDebug.CDebugPut("*       * || IdR:%d  Idrr:(  %d , %d ) ", ic2 ,iId1 ,  iId2 );
						if ( mode == 1 )
						{	// set based on physical connection 
							mDebug.CDebugPut("*Info 901 Fixing * || Id:%d Id1:%d Id2:%d   ", tId ,iId1 ,  iId2 );
							p->SetConnection( epc  , iId1 );
							p->SetConnection( epc+1  , iId2);
							//nbrErrors -=1;
							//return nbrErrors;
						}

						if  ( CheckSwitchOtherEndValidConnection ( tId,  ept[0] ,  p1 ,  mode ) == 0 ) // NO err
							if  ( CheckSwitchOtherEndValidConnection (  tId , ept[1] ,  p2 ,  mode ) == 0 )
								nbrErrors -=1;


						return nbrErrors;


					}
			else
					{
			
						//	if ( tId == 1651 )
						//	    mDebug.CDebugPut("*GENERAL 3 * || Id:%d Id1:%d Id2:%d   ", tId ,iId1 ,  iId2 );	

						nbrErrors +=1;

						if  ( CheckSwitchOtherEndValidConnection ( tId,  ept[0] ,  p1 ,  mode ) == 0 ) // NO err
							if  ( CheckSwitchOtherEndValidConnection (  tId , ept[1] ,  p2 ,  mode ) == 0 )
								nbrErrors -=1;

						return nbrErrors; // SWITCH is properly set !!!!!  Both logical & physical connection matches
					}
		}
		mDebug.CDebugPut("*Info 00 NO path here* "); 
	}
	return nbrErrors;
}

#define  nNODETRACE

#ifdef NODETRACE
int tnode_trace =0 ;
#endif

int op= 0;

int  GoRailOperStatus()
{
	int ops = op;
	op = 0;
	return ops;
}

void  GoSwitchRail( CTramConNode *pnode  , float frem  )
{

	CObjRail *pr;
	float fLinRest = frem;	if (fLinRest == 0) fLinRest+=(float)0.01;

	// !!!   rework this this needs to decide whtere we go right or left  

	//mDebug.CDebugPut("*1GoSwitchRail*:%d dir:%d ", pnode->pSegment->GetRailId(), pnode->dir );


	// MUST stop
 	if (  (pr = mCObjRailsColl.GetByEndPoint( pnode->pSegment , pnode->dir )) == NULL ) 
	{
		op = 1;
		return  ;
	}

	op = 0;

	//mDebug.CDebugPut("*2GoSwitchRail*:%d mode:%d ", pr->GetRailId() , pr->GetMode(2));

#ifdef NODETRACE
if ( tnode_trace == 0 )
{
	mDebug.CDebugPut("**GoSwitchRail trace:New rail ID:%d Mode: %d ",   pr->GetRailId(), pr->GetMode(2) ); 
	mDebug.CDebugPut("**GoSwitchRail reminders frem:%6.2f ,fLinRest:%6.2f    ",  (float)frem  , (float)fLinRest   ); 
}
#endif

	 
	if ( pr->GetObjectType() == ObjStraightRail || pr->GetObjectType() == ObjRailEnd ) // next is the straight
	{
		pnode->sp = GetPointFmStartStright( pr, pr->GetMode(2) ,  fLinRest );
 #ifdef NODETRACE
if ( tnode_trace == 0 )
	mDebug.CDebugPut("**GoSwitchRail New point of stright :( %6.2f ,%6.2f )  ",  (float)pnode->sp.x  , (float)pnode->sp.y   ); 
#endif


	}
		//	if (   pr->mtype == ObjRailEnd ) oes->endrail_reached = 1;

	if (( pr->GetObjectType()  == ObjBendRightRail )  || ( pr->GetObjectType()  == ObjBendLeftRail  ))
	{
		CObjBendRail *pb = (CObjBendRail *)pr;
		pnode->sp   = GetPointFmStartBend( pb, pb->GetMode(2) , fLinRest  );

#ifdef NODETRACE
if ( tnode_trace == 0 )
	mDebug.CDebugPut("**GoSwitchRail New point of bend :( %6.2f ,%6.2f )  ",  (float)pnode->sp.x  , (float)pnode->sp.y   ); 
#endif


	}

	pnode->dir = ( pr->GetMode(2) +1)&1; 
	pnode->pSegment = pr;
	pnode->m_ObjRailID = pr->GetRailId();  // added 2016.06.25
}

void GoStright( CTramConNode *pnode , float step )
{
	CObjRail *pr = pnode->pSegment;

	float fSegLenght = GetDistance( pr->GetPoint(0) , pr->GetPoint(1) );  
	float fSegPlus = GetDistance( pr->GetPoint( ( pnode->dir+1)&1 ) , pnode->sp ) +step  ;

#ifdef NODETRACE
if ( tnode_trace == 0 )
	mDebug.CDebugPut("**GoStright trace:fSegLenght:%6.2f fSegPlus:%6.2f ",   fSegLenght , fSegPlus  ); 
#endif


	if (  fSegPlus <=  fSegLenght ) //  old track
		pnode->sp  = GetPointFmStartStright( pr, ( pnode->dir+1)&1 , fSegPlus );
	else
		GoSwitchRail( pnode , abs( fSegLenght - fSegPlus ));// whats left to take  -linear	
}

void GoBend( CTramConNode *pnode , float step )
{
	CObjBendRail *pr = (CObjBendRail *)pnode->pSegment;

	float fSegLenght =	GetDistanceBend( pr ); 


#ifdef NODETRACE
if ( tnode_trace == 0 )
		mDebug.CDebugPut("**GoBend trace:Step:%6.2f fSegLenght:%6.2f ",   step , fSegLenght  ); 
#endif

	float fSegPlus =  GetDistance( pr , ( pnode->dir+1)&1 , pnode->sp ) +step  ;

#ifdef NODETRACE
if ( tnode_trace == 0 )
		mDebug.CDebugPut("**GoBend trace:Dist before:%6.2f Distance after :%6.2f ",    GetDistance( pr , ( pnode->dir+1)&1 , pnode->sp ) ,fSegPlus ); 
#endif

   CFPoint p1 = pnode->sp ;

	if (  fSegPlus   <=  fSegLenght ) 
		pnode->sp = GetPointFmStartBend( pr, ( pnode->dir+1)&1 , fSegPlus );
	else
		GoSwitchRail( pnode , abs( fSegLenght - fSegPlus) ); 


	// compare distance bewtean new and old point
	float d1 = (float)GetDistance(  p1 , pnode->sp ); 
	float d2 = GetDistance( pr , ( pnode->dir+1)&1 , pnode->sp )  ; 
 

#ifdef NODETRACE
if ( tnode_trace == 0 )
		mDebug.CDebugPut("**GoBend Point distance PD :%6.2f LD  :%6.2f ",   (float)GetDistance(  p1 , pnode->sp )  , GetDistance( pr , ( pnode->dir+1)&1 , pnode->sp )  ); 
#endif


}

void	MoveNode( CTramConNode *pnode , float step )  
{
	if ( ( pnode->pSegment->GetObjectType() == ObjStraightRail )  ||  ( pnode->pSegment->GetObjectType() == ObjRailEnd ) ) 
		GoStright(  pnode, step );
	else
		GoBend(  pnode,step );
}
 

void	MoveNode( CTramConNode *pnode , float step , int node_nbr)  
{

#ifdef NODETRACE
 tnode_trace = node_nbr;
		
if ( node_nbr == 0 )
	mDebug.CDebugPut("**Node trace:Rail type:%d Point:(%d,%d) RailId:%d ",   
	pnode->pSegment->GetObjectType(),(int)pnode->sp.x, (int)pnode->sp.y,(int)pnode->pSegment->GetRailId()   ); 
#endif	

	if ( ( pnode->pSegment->GetObjectType() == ObjStraightRail )  ||  ( pnode->pSegment->GetObjectType() == ObjRailEnd ) ) 
		GoStright(  pnode, step );
	else
		GoBend(  pnode,step );
}

// px is validated 
CPoint  GetPointOnRail ( CObjRail   *px , CMyPoint ControlPoint )
{
 
			// rail could be bend  - no implementation for bend
	CLineObject  mLine( px->GetPoint(0),px->GetPoint(1));
	CLineObject  mLinePerp( mLine.GetA() , mLine.GetB() , ControlPoint );
			// for stright
	CMyPoint  cp1 = mLinePerp.GetCrossWithLine( mLine );
			// for bend
			// cross bend in direction of vector  ptt , cross with line (cp1)

	if ( (px->GetObjectType() == ObjBendRightRail ) || ( px->GetObjectType() == ObjBendLeftRail )  )
			{
				CObjBendRail  *pb = (CObjBendRail*)px; 
				CFPoint pc = pb->GetCenterPoint();
				CFPoint p0 = pb->GetPoint( 0); 

				float fradius = GetDistance(  pc,p0 ) ;

				CTwoPoints tp =  ComputeIntersectionOfCircleAndSegment( pc , fradius , ControlPoint , cp1 );

				CMyPoint  cm1(0,0) ;
				if( GetDistance( tp.mPoint1 , cp1 ) <  GetDistance( tp.mPoint2 , cp1 ) )
					 cm1 =  tp.mPoint1;
				else
					 cm1 =  tp.mPoint2;
				return cm1 ;
			}
	else
	{
		return cp1;
	}
	return CPoint(0,0);
}		 

 
// return 0 if no errors
// -1 bend  outside of the arch
// 2 bend  wrong distance 
// 3 bend other error
// 4 segment - out of segment
// 5 n/a
//
//  IsPointOnTheArch   - return -1 if out of the range -2 out of the lenght ( correctable )
//	IsPointOnTheSegment - return -1 if out of the range -2 out of the lenght ( correctable )
//
//
//

int GetDistanceOfPointFromRail( CObjRail   *px , CMyPoint ControlPoint )
{
	CObjBendRail *pb = IsBendObject(  px  );
	if ( pb != NULL )
	{
		int ierr = IsPointOnTheArch( pb->GetPoint( 0) , pb->GetPoint( 1) , pb->GetCenterPoint() ,  ControlPoint  ) ;
		if ( ierr == 1 ) return 0;  // OK
		if ( ierr < 0  ) return -ierr;
		return 3;
	}
	else
	{
		int ierr = IsPointOnTheSegment(px->GetPoint(0) , px->GetPoint(1) ,ControlPoint ) ;
		if ( ierr == 1 ) return 0;  // OK
		if ( ierr < 0  ) return -ierr;
		return 3;
	}
}
 


CObjBendRail *IsBendObject( CObjRail   *px   )
{
	CObjBendRail *pb = NULL;; 

	if ( (px->GetObjectType() == ObjBendRightRail ) || ( px->GetObjectType() == ObjBendLeftRail )  )
				pb = ( CObjBendRail*) px; 
    return pb;		 
}


////////////////////////////////////////////////////////////////
//	Return the endpoint connected to this en on This rail
//
//
///////////////////////////////////////////////////////////////

BOOL CheckIfTheEpIsSwitch( CObjRail *p  , int endpoint )  
{
	endpoint = endpoint << 1;
	if (  (p->GetRailConnId( endpoint )  != 0 ) && (p->GetRailConnId( endpoint+1 )  != 0)  )
		return TRUE;
	else 
		return FALSE;
}


////////////////////////////////////////////////////////////////
//	Return the endpoint connected to this en on This rail
//
//
///////////////////////////////////////////////////////////////

int GetOtherEndEp( CObjRail *pnx  , int ThisId )
{
	int oep=-1; // other ep
	if ( pnx->GetRailConnId(0) == ThisId )	oep = 0;
	if ( pnx->GetRailConnId(1) == ThisId )	oep = 0;
	if ( pnx->GetRailConnId(2) == ThisId )	oep = 1;
	if ( pnx->GetRailConnId(3) == ThisId )	oep = 1;
	return oep;
}
 

int BrowseTime( CString Cs )
{
	int p1 = (WORD) atoi(Cs)*60;
	int p2 = 0;
	int ip = Cs.Find(':' );

	if ( ip > 0 )
			{
				CString Cs22 = Cs.Mid( ip+1);
				p2 = atoi(Cs22);
			}
	return p1  +p2;
}