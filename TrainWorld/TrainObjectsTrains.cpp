
#include "stdafx.h"
#include "Math.h"

#include "StdTrainDef.h"

#include "TrainObjects.h"

#include "Debug.h"
extern CDebug mDebug;


 
///////////////////////////////////////////////////////////////////////
///-
/// [00] CTramConNode::CTramConNode()
///
/// ------[Object adding group]
/// [10] float CTramConNode::GetLenghCorrection() 
/// [11]  void CTramConNode::AddCurrentDif( float dif )
///
/// [20] CTramTrainVagons::CTramTrainVagons()
/// [21] void CTramTrainVagons::InitializeObject(CFPoint PtStartPoint , CObjRail *pSegment , int RailEp )
/// [22] void CTramTrainVagons::ReInitializeObject()
/// [23] void CTramTrainVagons::ReversTrain( BOOL revtrain ) 
/// [24] BOOL CTramTrainVagons::IsTrainReversed() 
/// [25] void CTramTrainVagons::SetManualControlMode( bool byesno ) 
/// [26] BOOL CTramTrainVagons::GetManualControlStatus()  	
/// [27] int  CTramTrainVagons::GetLineId()  	
/// [28] void CTramTrainVagons::SetLineId( int lineid)  
/// [29] void CTramTrainVagons::SetTramId( int TramId )
/// [30] int  CTramTrainVagons::GetTramId() 
/// [31] CFPoint  CTramTrainVagons::GetHeadPoint()  // duplicate 1
/// [32] CFPoint  CTramTrainVagons::GetTailPoint() // duplicate 2
/// [33] CFPoint CTramTrainVagons::GetStartPoint() // duplicate 1
/// [34] CFPoint CTramTrainVagons::GetEndPoint()    // duplicate 2
/// [35] void  CTramTrainVagons::SetDynTimeOut(  int tick ) 
/// [36] int  CTramTrainVagons::GetDynTimeOut()
/// [37] BYTE  CTramTrainVagons::GetCurState()
/// [38] BYTE  CTramTrainVagons::GetStopReason()
/// [39] BOOL CTramTrainVagons::CreateVagons(  CTramModelDef *pModel , int nodes )
/// [40] void CTramTrainVagons::Serialize(CArchive& ar)
/// [41] WORD CTramTrainVagons::GetRailPtrId( int k )  // duplicate 3
/// [41] WORD CTramTrainVagons::GetRailPtrId2( int k )  // duplicate 3
/// [42] void CTramTrainVagons::SetRailObjectPtr( int k, CObjRail *p)  
/// [43] int  CTramTrainVagons::GetNumberOfNodes()  
/// [44] CObjRail * CTramTrainVagons::GetHeadRailObjPtr() 
/// [45] CObjRail * CTramTrainVagons::GetTailRailObjPtr() 
/// [46] int  CTramTrainVagons::GetHeadPointEpDir()
/// [47]  CFPoint  CTramTrainVagons::GetNodePoint( int inode )
/// [48]  BOOL  CTramTrainVagons::IsTramsInMotion()
/// [49] int CTramTrainVagons::GetDistanceOfTheHeadToEp()
/// [50] void  CTramTrainVagons::DrawObject( HDC hdc ,  CPoint offset  ) 
/// [51] BOOL CTramTrainVagons::CollisionCheck()
/// [52] BOOL CTramTrainVagons::StopCheck()
/// [53] BOOL CTramTrainVagons::StopGetStatus()
/// [54] BOOL CTramTrainVagons::SemCheck()
/// [55] BOOL CTramTrainVagons::SwitchCheck()
/// [56] int  CTramTrainVagons::GetControlEndpoint() 
/// [57] int CTramTrainVagons::ControlStopTimeOut( int nId ) 
/// [58] int  CTramTrainVagons::SetSwitch(int ep , int nId ) 
/// [59] BOOL  CTramTrainVagons::StateObject( )
/// [60] BOOL  CTramTrainVagons::MoveObject( float step ) 
/// [61] void CTramTrainVagons::ChangeMoveObjectDir()
/// [62] void  CTramTrainVagons::StopTrain(  BOOL stoptrain )  
/// [63] BOOL  CTramTrainVagons::IsTrainStopped()   
/// [64] void CTramTrainVagons::ChangeTrainObjectDir()
///
///////////////////////////////////////////////////////////////////////
///
/// 
///
///----------------------------------------------------------------------------------

extern CObjRailsColl  mCObjRailsColl;
extern CObjTramLine mCObjTramLine;

 
CTramConNode::CTramConNode()
{
	   // position on the rail
	pSegment = NULL; // pointer to the  rail 
	len = 0; 
	bCorrSign = true ;
	mDifTable[0]=0;
	mStyle = 0;
	mWidth = 5;
};

 /// [10] float CTramConNode::GetLenghCorrection()  
 float CTramConNode::GetLenghCorrection()
 {
	float fdif = (float)len - fcur_len;
	float fadir = abs(fdif ) ;

	mDifTable[1]= mDifTable[0]; // save reference
    	mDifTable[0] = fadir;

	if ( fadir > 0.2 )
	 {
		 if (  mDifTable[1]  <  fadir )  bCorrSign = !bCorrSign ; //    md = (md+1)&1 ;   
//mDebug.CDebugPut("CTramConNode: Len=%d md=%d::fdif:[%6.2f]  abs[%6.2f]  ", len , bCorrSign, fdif , abs(fdif ));
		 if ( bCorrSign   ) return fadir ;
		 else return -fadir ;
	}
	else
	{
//mDebug.CDebugPut("-----------: Len=%d md=%d::fdif:[%6.2f]  abs[%6.2f]  ", len , bCorrSign, fdif , abs(fdif ));
		bCorrSign=true ; // default direction
		return 0;
	}

 }
  /// [11]  void CTramConNode::AddCurrentDif( float dif )
 void CTramConNode::AddCurrentDif( float dif )
 {
	fcur_len = dif;
 }

  
 ////////////////////////////////////////////////////////////////////////////////
 //
 //
 //
 ///////////////////////////////////////////////////////////////////////////////
 /// [20] CTramTrainVagons::CTramTrainVagons()
CTramTrainVagons::CTramTrainVagons()
{
	for ( int i=0 ; i<MAX_NODES;i++) mNode[i] = NULL;
	ReInitializeObject();
}
 
CTramTrainVagons::~CTramTrainVagons()
{
	for ( int i=0 ; i< MAX_NODES; i++)
		if ( mNode[i] != NULL )  delete mNode[i] ;
}

CTramTrainVagons::CTramTrainVagons( CFPoint mStartPoint , CObjRail *pSegment , int RailEp )
{
	InitializeObject( mStartPoint ,  pSegment ,  RailEp );
}

CTramTrainVagons::CTramTrainVagons( CFPoint mStartPoint , CObjRail *pSegment ) 
{
	InitializeObject(  mStartPoint ,  pSegment , 0 );
}
/// [21] void CTramTrainVagons::InitializeObject(CFPoint PtStartPoint , CObjRail *pSegment , int RailEp )
void CTramTrainVagons::InitializeObject(CFPoint PtStartPoint , CObjRail *pSegment , int RailEp )
{
		// CTramConNode 
	mStartPoint = PtStartPoint;
	mStartSegment = pSegment;
	mStartDir = RailEp;
	for ( int i=0 ; i<MAX_NODES;i++) mNode[i] = NULL;

	//dynState = StateSTOP;  def
	dynState = 	StateRUN;
	dynStopReason = StopUndef;
	dynService = DirInit;
	dynTmOut = 0;
	dunStopObjRailID = 0;
	dunSwitchObjRailID =0;

	mForward = 1;
	mGetControl = 0;
	mStopTrain = 0;
}

/// [22] void CTramTrainVagons::ReInitializeObject()
void CTramTrainVagons::ReInitializeObject()
{
	//mForward = 1;
	//mGetControl = 0;
	//mStopTrain = 0;  // during stop go it is changed
}

/// [23] void CTramTrainVagons::ReversTrain( BOOL revtrain ) 
void CTramTrainVagons::ReversTrain( BOOL revtrain ) 
{
	if ( revtrain == TRUE )
	{
		if ( mForward == 1 ) ChangeMoveObjectDir();
	}
	else
	{ 
		if ( mForward == 0 ) ChangeMoveObjectDir();
	}
}

/// [24] BOOL CTramTrainVagons::IsTrainReversed() 
BOOL CTramTrainVagons::IsTrainReversed() 
{		 
//mDebug.CDebugPut((char *)"IsTrainReversed  %d   ",mForward );
	if ( mForward == 1 ) return FALSE; else return TRUE ;
}

/// [25] void CTramTrainVagons::SetManualControlMode( bool byesno ) 
void CTramTrainVagons::SetManualControlMode( bool byesno ) 
{
	if ( byesno == TRUE ) mGetControl = 1; else mGetControl = 0;
}
/// [26] BOOL CTramTrainVagons::GetManualControlStatus()  	
BOOL CTramTrainVagons::GetManualControlStatus() 
{		 
	if ( mGetControl == 1 ) return TRUE; else return FALSE;
}
/// [27] int  CTramTrainVagons::GetLineId()  	
int  CTramTrainVagons::GetLineId() 
{
	return (int)mLineId;
}
/// [28] void CTramTrainVagons::SetLineId( int lineid)  
void CTramTrainVagons::SetLineId( int lineid) 
{
	mLineId = (BYTE)lineid;
}
/// [29] void CTramTrainVagons::SetTramId( int TramId ) 
void CTramTrainVagons::SetTramId( int TramId )   //mId
{ mId =TramId ;}

/// [30] int  CTramTrainVagons::GetTramId() 
int  CTramTrainVagons::GetTramId() 
{ return mId;}

/// [31] CFPoint  CTramTrainVagons::GetHeadPoint()
CFPoint  CTramTrainVagons::GetHeadPoint()
{
	return mNode[0]->sp;
}
/// [32] CFPoint  CTramTrainVagons::GetTailPoint() 
CFPoint  CTramTrainVagons::GetTailPoint() 
{
	return mNode[iCurNodes-1]->sp;
}
/// [33] CFPoint CTramTrainVagons::GetStartPoint()
CFPoint CTramTrainVagons::GetStartPoint()
{
	return mNode[0]->sp;
}
/// [34] CFPoint CTramTrainVagons::GetEndPoint()  
CFPoint CTramTrainVagons::GetEndPoint() 
{
	return mNode[iCurNodes-1]->sp;
}

/// [35] void  CTramTrainVagons::SetDynTimeOut(  int tick ) 
void  CTramTrainVagons::SetDynTimeOut(  int tick )  
{  dynTmOut = tick;}
/// [36] int  CTramTrainVagons::GetDynTimeOut()
int  CTramTrainVagons::GetDynTimeOut()
{ return dynTmOut; }
/// [37] BYTE  CTramTrainVagons::GetCurState()
BYTE  CTramTrainVagons::GetCurState()
{ return dynState; }
/// [38] BYTE  CTramTrainVagons::GetStopReason()
BYTE  CTramTrainVagons::GetStopReason()
{ return dynStopReason; } 


/// [39] BOOL CTramTrainVagons::CreateVagons(  CTramModelDef *pModel , int nodes )
BOOL CTramTrainVagons::CreateVagons(  CTramModelDef *pModel , int nodes )
{
	if ( mNode[0] != NULL ) return FALSE;

	iCurNodes = nodes+1;
	int inc_size =0;

	for ( int i=0 ; i < iCurNodes; i++)
	{
		mNode[i] = new CTramConNode(); 

		mNode[i]->len = (pModel+i)->len;
		mNode[i]->mStyle = (pModel+i)->style;
		mNode[i]->mWidth = (pModel+i)->width;
		if( 0 == mStartDir   )  mNode[i]->dir = 1;
		else mNode[i]->dir = 0;
		mNode[i]->fcur_len = (float)mNode[i]->len;
		mNode[i]->pSegment = mStartSegment;
		// size of  the node
		mNode[i]->sp = GetPointFmStart( mStartPoint , mStartSegment->GetPoint(mStartDir) , (float)inc_size );
		inc_size += mNode[i]->len;
	}
	 
	return TRUE;
}

/// [40] void CTramTrainVagons::Serialize(CArchive& ar)
void CTramTrainVagons::Serialize(CArchive& ar)
{
	int it;

	if (ar.IsStoring())
	{		
		it = mStopTrain;
		it = it << 8;
		it |= mLineId;
		it = it << 8;
		it |= iCurNodes;
 
		//it = it << 8;
		//it |= mForward;	mScheduleId

		ar << it;

//mDebug.CDebugPut("*CTramTrainVagons::Serialize*:Store  %d %d  ",  mLineId ,iCurNodes );

		
		//BYTE  mGetControl;

		// state machine
		ar << dynState;
		ar << dynStopReason;
		ar << dynService;
		ar << dynExtra;
		ar << dynTmOut;
		ar << dunStopObjRailID;
		ar << dunSwitchObjRailID;

//mDebug.CDebugPut("*CTramTrainVagons::Store Serialize*: %d  %d  %d %d",  (int)dynState ,(int)dynStopReason,(int)dunStopObjRailID,(int)dunSwitchObjRailID );


		for ( int i=0; i < iCurNodes;i++)
		{
			it = mNode[i]->len ;
			it +=  ( mNode[i]->mWidth << 16);
			ar << mNode[i]->dir ;
			ar << it;
			ar << mNode[i]->mStyle ;
			WORD m_ObjRailID = mNode[i]->pSegment->GetRailId() ;	
			ar << m_ObjRailID;
			mNode[i]->sp.Serialize( ar); 
		}
	}
	else
	{
		//ar >> iCurNodes;
		ar >> it;

		iCurNodes = it&0xFF;
		mLineId =  ( it >> 8 ) & 0xFF;
		mStopTrain =  ( it >> 16 ) & 0xFF;
		
		mForward =1;

//mDebug.CDebugPut("*CTramTrainVagons::Restore Serialize*: %d  %d ",  mLineId ,iCurNodes );
  
		ar >> dynState;
		ar >> dynStopReason;
		ar >> dynService;
		ar >> dynExtra;
		ar >> dynTmOut;
		ar >> dunStopObjRailID;
		ar >> dunSwitchObjRailID;
  

//mDebug.CDebugPut("*CTramTrainVagons::Restorte Serialize*: %d  %d  %d %d",  (int)dynState ,(int)dynStopReason,(int)dunStopObjRailID,(int)dunSwitchObjRailID );



		// initilize CurNodes module !!!!
		for ( int i=0; i < iCurNodes;i++)
		{
			int it;
			mNode[i] = new CTramConNode(); 
			ar >> mNode[i]->dir ;
			ar >> it;
			mNode[i]->len = it&0xFFFF;
			mNode[i]->mWidth = it >> 16;
			if ( mNode[i]->mWidth == 0 ) mNode[i]->mWidth =5;
			//ar >> mNode[i]->len ;
			mNode[i]->fcur_len = (float)mNode[i]->len;
			ar >> mNode[i]->mStyle ;
			// current rail
			ar >> mNode[i]->m_ObjRailID;
			// current rail position - start point
			mNode[i]->sp.Serialize( ar); 
		}
	}
}

// used with serialization
/// [41] WORD CTramTrainVagons::GetRailPtrId( int k ) 
WORD CTramTrainVagons::GetRailPtrId( int k ) 			// mNode[MAX_NODES]->m_ObjRailID ;
{
	  return mNode[k]->m_ObjRailID;
}

//  we dont update m_ObjRailID  on the next segment !!!!
//  void  GoSwitchRail( CTramConNode *pnode  , float frem  )  FIXED
/// [41] WORD CTramTrainVagons::GetRailPtrId2( int k ) 

WORD CTramTrainVagons::GetRailPtrId2( int k ) 			// mNode[MAX_NODES]->m_ObjRailID ;
{

	return mNode[k]->m_ObjRailID;
	/*
	 if ( mNode[k]->pSegment != NULL )
	    return mNode[k]->pSegment->GetRailId();
	 else return 0;*/
}


/// [42] void CTramTrainVagons::SetRailObjectPtr( int k, CObjRail *p)  

void CTramTrainVagons::SetRailObjectPtr( int k, CObjRail *p)  // mNode[MAX_NODES]->pSegment ;
{
	mNode[k]->pSegment = p;
}

/// [43] int  CTramTrainVagons::GetNumberOfNodes()  
int  CTramTrainVagons::GetNumberOfNodes()   //iCurNodes
{
	return iCurNodes;
}

/// [44] CObjRail * CTramTrainVagons::GetHeadRailObjPtr() 
CObjRail * CTramTrainVagons::GetHeadRailObjPtr()
{
	return mNode[0]->pSegment;
}

/// [45] CObjRail * CTramTrainVagons::GetTailRailObjPtr() 
CObjRail * CTramTrainVagons::GetTailRailObjPtr() 
{
	return mNode[iCurNodes-1]->pSegment;
}

/// [46] int  CTramTrainVagons::GetHeadPointEpDir()
int  CTramTrainVagons::GetHeadPointEpDir()
{
	return mNode[0]->dir;
}

/// [47]  CFPoint  CTramTrainVagons::GetNodePoint( int inode )
 CFPoint  CTramTrainVagons::GetNodePoint( int inode )
 {
	return mNode[inode]->sp;
}

/// [48]  BOOL  CTramTrainVagons::IsTramsInMotion()
BOOL  CTramTrainVagons::IsTramsInMotion()
{
	if ( dynState == StateSTOP ) 
		if ( dynStopReason == ObjDet ) 
			return FALSE;
	return  TRUE;
}


/// [49] int CTramTrainVagons::GetDistanceOfTheHeadToEp()
int CTramTrainVagons::GetDistanceOfTheHeadToEp()
{
	return (int)GetDistance( mNode[0]->pSegment->GetPoint( mNode[0]->dir ) , mNode[0]->sp);
}

/// [50] void  CTramTrainVagons::DrawObject( HDC hdc ,  CPoint offset  ) 
void  CTramTrainVagons::DrawObject( HDC hdc ,  CPoint offset  ) 
{
	DRAWDATASTRUCT mData;
	mData.pVagonData = NULL;
 

	for ( int i=0; i < iCurNodes-1 ; i++)
	{
		DWORD  mode = DRAWLINES  ;
		CObjRail *p =  mNode[i]->pSegment;
		if ( p->IsUndergroundRail() ) mode |= TUNDERGND  ;
		mode |=  mNode[i]->mStyle;

		mData.StartPoint = OffsetFPoint ( mNode[i]->sp , offset );
		mData.EndPoint   = OffsetFPoint ( mNode[i+1]->sp, offset );
		// mData.Width = 10;
		mData.Width  = mNode[i]->mWidth;
		PaintTrain( &mData,  mode ,  hdc  );
	}
	 
}


//   the head mNode[0]  is checked egainst mNode[N]  of  other trams
/// [51] BOOL CTramTrainVagons::CollisionCheck()
BOOL CTramTrainVagons::CollisionCheck()
{ 
	return  mCObjRailsColl.CheckColissionOfThisTrain( this );
}

/// [52] BOOL CTramTrainVagons::StopCheck()
BOOL CTramTrainVagons::StopCheck()
{
	CObjRail *pSegment = mNode[0]->pSegment; // head on this rail
	CObjControls *p; // ptr to control object
	int ipoint = 0;  // segment iteration if more controls
	//mDebug.CDebugPut("*New Dir  %d  ",   (int)mNode[0]->dir   );
	/*
if ( mId  == 25 )
{
 mDebug.CDebugPut((char *)"StopCheck  [%d] %d ", (int)dynState , (int)dynStopReason  );
 mDebug.CDebugPut("StateObject  Tram_id:%d route_id:%d ",     (int)mId ,  (int)mLineId    );
}
*/

	while ( ipoint < 10 )
	{
		if ( ( p = mCObjRailsColl.FindControlObject ( pSegment->GetRailId() , ObjStop , ipoint )) == NULL ) return FALSE;

//if ( mId  == 25 )
//	mDebug.CDebugPut("*Cntr:%d  %d Distance*:%d ",p->GetControlID() ,(int)pSegment->GetRailId()  , (int)GetDistance ( p->GetRailControlPoint() , mNode[0]->sp ) );
		
		ipoint += 1;  //  point for  the next point at the segment
		if ( GetDistance ( p->GetRailControlPoint() , mNode[0]->sp )  < 8 )  // we are in
			{
				int cntID = p->GetControlID(); 
				if ( dunStopObjRailID == cntID)  return FALSE;  // already  stoped at this control
//if ( mId  == 25 )
//			mDebug.CDebugPut("*New IDs*:%d  %d  ",   (int)dunStopObjRailID , cntID  );	
				dunStopObjRailID = cntID ;
				return TRUE;
			}
	}
	return FALSE;
}

/// [53] BOOL CTramTrainVagons::StopGetStatus()

BOOL CTramTrainVagons::StopGetStatus()
{
	CObjControls *p = mCObjRailsColl.FindControlObject( dunStopObjRailID   ) ;
	if ( p == NULL ) return TRUE; // go
	if ( p->GetStatus() == STATUS_SET_GO ) return TRUE  ;  // go 
	if ( p->GetStatus() == STATUS_NOOPER ) return TRUE  ;  // go 
	return FALSE; // stop
}

/// [54] BOOL CTramTrainVagons::SemCheck()

BOOL CTramTrainVagons::SemCheck()
{
	CObjRail *pSegment = mNode[0]->pSegment; // head on this rail
	CObjControls *p; // ptr to control object
	int ipoint = 0;  // segment iteration if more controls
	//mDebug.CDebugPut("*New Dir  %d  ",   (int)mNode[0]->dir   );
	while ( ipoint < 10 )
	{
		if ( ( p = mCObjRailsColl.FindControlObject ( pSegment->GetRailId() , ObjSem , ipoint )) == NULL ) return FALSE;
		// mDebug.CDebugPut("* %d Distance*:%d ", (int)pSegment->GetRailId()  , (int)GetDistance ( p->GetRailControlPoint() , mNode[0]->sp ) );
		
		 ipoint += 1;  //  point for  the next point at the segment
		if ( GetDistance ( p->GetRailControlPoint() , mNode[0]->sp )  < 8 )  // we are in
			{
				if ( p->GetStatus() == STATUS_SET_GO ) return FALSE; 
				p->SetSignal( TRUE );
				return TRUE;
			}
	}
	return FALSE;
}

/// [55] BOOL CTramTrainVagons::SwitchCheck()
BOOL CTramTrainVagons::SwitchCheck()
{
	CObjRail *pSegment = mNode[0]->pSegment; // head on this rail
	CObjControls *p; // ptr to control object
	// which ep we are heading to ? -> mNode[0]->dir
 
	if ( ( p = mCObjRailsColl.FindControlObject ( pSegment->GetRailId() , ObjSwitch , mNode[0]->dir )) == NULL ) return FALSE;
	
   // mDebug.CDebugPut("*New EP: %d  %d  ",   (int)p->GetControlPoint().x  ,(int)p->GetControlPoint().y);
//	if ( mId == 2 ) 
//	mDebug.CDebugPut("* %d Distance*:%d ", (int)pSegment->GetRailId()  , (int)GetDistance ( p->GetRailControlPoint() , mNode[0]->sp ) );

	if ( GetDistance ( p->GetRailControlPoint() , mNode[0]->sp )  < 16 )  // we are in
		{
				int cntID = p->GetControlID(); 
				if ( dunSwitchObjRailID == cntID)  return FALSE;  // already  stoped at this control
				// mDebug.CDebugPut("*New IDs*:%d  %d  ",   (int)dunSwitchObjRailID , cntID  );	
				dunSwitchObjRailID = cntID ;
				return TRUE;
			}

	return FALSE;
}

/// [56] int  CTramTrainVagons::GetControlEndpoint() 
int  CTramTrainVagons::GetControlEndpoint() 
{
	CObjControls *p;
	p = mCObjRailsColl.FindControlObject(  dunSwitchObjRailID );
	if ( p == NULL ) return -1;
	return p->GetControlEndpoint();
}

/// [57] int CTramTrainVagons::ControlStopTimeOut( int nId ) 
int CTramTrainVagons::ControlStopTimeOut( int nId ) 
{
	CObjControls *p;
	p = mCObjRailsColl.FindControlObject(  nId );
	if ( p == NULL ) return -1;
	return p->GetTimeOut();
}

/// [58] int  CTramTrainVagons::SetSwitch(int ep , int nId ) 
int  CTramTrainVagons::SetSwitch(int ep , int nId ) 
{
	CObjControls *p;
	p = mCObjRailsColl.FindControlObject(  dunSwitchObjRailID );
	if ( p == NULL ) return -1;
	
	CObjRail *pr =  mNode[0]->pSegment;   
	if ( pr == NULL ) return -1;
	
	int epc  = ep << 1;
	int isw = -1;

	if ( pr->GetRailConnId( epc) == nId ) isw = 0;
	if ( pr->GetRailConnId( epc+1) == nId ) isw = 1;

	if ( isw < 0 ) return -1;

	if ( p->GetObjectType() == ObjSwitch )
	{
		p->SetStatus ( isw );
	 	pr->SetSwitch( ep , p->GetStatus() ) ;	
		return 0;
	}
	return -1;
}

 /// [59] BOOL  CTramTrainVagons::StateObject( )
BOOL  CTramTrainVagons::StateObject( )
{

/*
if ( mId  == 25 )
{
 
	mDebug.CDebugPut((char *)"StateObject  [%d] %d ", (int)dynState , (int)dynStopReason  );
 mDebug.CDebugPut("StateObject  Tram_id:%d route_id:%d ",     (int)mId ,  (int)mLineId    );
}
*/
	if ( dynState == StateRUN  )
	{

 
		if ( CollisionCheck() == TRUE ) 
			{ 
				dynState = StateSTOP  ; 
				dynStopReason = ObjDet; 
				return FALSE;
			}
		

		if ( StopCheck() == TRUE )
			{ 
				dynState = StateSTOP  ;
 				dynTmOut = 40;
				// check control default wait time
				int dctm = ControlStopTimeOut( dunStopObjRailID );
				if ( dctm > 0 )	dynTmOut = dctm;
				// can be overwrite by line specific
				int npId = mCObjTramLine.GetControlParam(  (int)mLineId , dunStopObjRailID );
				if ( npId > 0 )	dynTmOut = npId;		
				//  specific wait time for given hour

  //mDebug.CDebugPut("*---------- CntId:%d Tram_id:%d route_id:%d ", dunStopObjRailID ,   (int)mId ,  (int)mLineId    );


				int npId1 = mCObjTramLine.GetControlParam(  (int)mLineId , (int)mId ,   dunStopObjRailID );
				if ( npId1 > 0 )	dynTmOut = npId1;
				dynStopReason = StopDet;   

//if ( mId  == 25 )
//			  mDebug.CDebugPut("*Stop tm:%d %d  ",  dynTmOut, (int)mId );		
				

				return FALSE;
		}

		if ( SemCheck() == TRUE )
			{ 			
				dynState = StateSTOP  ;
				dynStopReason = SemaphoreDet;   
				return FALSE;
			}

		if ( SwitchCheck() == TRUE )	
			{ 			
				dynState = StateSTOP  ;
				dynStopReason = SwitchDet; 
				return FALSE;
			}

		return TRUE;
	}
	else
	{

 
		if ( dynStopReason == ObjDet ) 
			{  
				if ( CollisionCheck() == FALSE )   // collision gone
					{ 
						dynStopReason = WaitSet  ; 
						dynTmOut = DEF_TIMEOUT; 
					}   
				return FALSE ; 
			}

		if ( dynStopReason == SemaphoreDet ) 
			{   
				if ( SemCheck() == FALSE )
				{
					// mDebug.CDebugPut("* Wait restrt from SEM on rail  %d ",    mNode[0]->pSegment->GetRailId()   );		
					
					dynState = StateRUN;
				}
				return FALSE;
			}

		if ( dynStopReason == StopDet ) 
			{   
				if ( dynTmOut > 0 )	dynTmOut-=1;
				else	
				{
					if ( StopGetStatus() == TRUE ) dynState = StateRUN; 
					else dynTmOut=1;
				}
				return FALSE;
			}

		if ( dynStopReason == SwitchDet ) 
			{   
				dynTmOut = 0;
				dynState = StateRUN; 	

				int ep = GetControlEndpoint();
				if ( ep >= 0 )
				{
					int npId = mCObjTramLine.GetControlParam(  (int)mLineId , dunSwitchObjRailID );
					if ( npId > 0 )  // must be npId - so set switch accordingly 
					{						
	/*			       
if ( mId == 2 )
{
	mDebug.CDebugPut("*SwitchSetStatus* GetManualControlStatus:%d (Line:%d) %d ", dunSwitchObjRailID , (int)mLineId , GetManualControlStatus()   );				
}*/

						if ( GetManualControlStatus() == FALSE )
							if ( SetSwitch( ep , npId ) < 0 )
						    mDebug.CDebugPut("*SwitchSetErorr1* : ControlId:%d Line:%d NextId:%d RailId:%d ",  dunSwitchObjRailID , (int)mLineId , npId , mNode[0]->pSegment->GetRailId() );	
					}
					else
						 mDebug.CDebugPut("*SwitchSetErorr2* ControlId:%d Line:%d RailId:%d Ep:%d ",  dunSwitchObjRailID   ,  (int)mLineId ,  mNode[0]->pSegment->GetRailId() , ep  );	
				}
				else
					mDebug.CDebugPut("*SwitchSetErorr3* ControlId: %d ", dunSwitchObjRailID   );


				return FALSE;
			}	
		
		if ( dynStopReason == WaitSet ) 
			{
				if ( dynTmOut > 0 )	dynTmOut-=1;
				else dynState = StateRUN;
				return FALSE;
			}
		// error when we got here
		return FALSE;
	}
	return TRUE;
}

 /// [60] BOOL  CTramTrainVagons::MoveObject( float step ) 

BOOL  CTramTrainVagons::MoveObject( float step ) 
{
 
    if (  mStopTrain == 1 )  return FALSE; 


//mDebug.CDebugPut((char *)" Move  [%d] %d ", (int)mForward , (int)StateObject()  );

	if ( mForward == 1 )
	{

		if ( StateObject() == FALSE) return FALSE;

		
		CObjRail *p = mNode[0]->pSegment; 
		step += (float)p->GetMode(1);  // increase the speed on long stright rails

		//step += 0.5*(float)p->GetMode(1);  // increase the speed on long stright rails

		for ( int i=0; i < iCurNodes; i++)
		{
		float corr =  0;
		if ( i > 0 )
			corr =  mNode[i-1]->GetLenghCorrection();
		
		corr += step;

		// mDebug.CDebugPut("MoveObject::Loop: %d  %d  corr:[%6.2f] corr [%6.2f]  ", i, i, corr ,step);

		MoveNode(  mNode[i] ,  corr    );  // adjustment

		if ( GoRailOperStatus() == 1 )  { mStopTrain =  1 ;  return FALSE; }

		if ( i > 0 )
			{			
			float d = GetDistance( mNode[i]->sp , mNode[i-1]->sp  );
			mNode[i-1]->AddCurrentDif ( d );

		//mDebug.CDebugPut("DistanceF  :[%6.2f]  [%6.2f]  ", d , corr  );
 
			}
		}
	}
	else
	{
		for ( int i= iCurNodes-1 ; i >= 0 ; i--)
		{
		float corr =  0;
		if ( i < (iCurNodes-1) )
			corr =  mNode[i]->GetLenghCorrection();
		
		corr += step;

		// mDebug.CDebugPut("MoveObject::Loop: %d  %d  corr:[%6.2f] corr [%6.2f]  ", i, i, corr ,step);

		MoveNode(  mNode[i] ,  corr    );  // adjustment

		if ( GoRailOperStatus() == 1 )  { mStopTrain =  1 ;  return FALSE; }

		if ( i < (iCurNodes-1) )
			{			
			float d = GetDistance( mNode[i]->sp , mNode[i+1]->sp  );
			mNode[i]->AddCurrentDif ( d );

		//mDebug.CDebugPut("DistanceF  :[%6.2f]  [%6.2f]  ", d , corr  );
 
			}
		}

	}
	return FALSE;
}
//  if goes to 0 then now goes to 1 and vice vers

/// [61] void CTramTrainVagons::ChangeMoveObjectDir()

void CTramTrainVagons::ChangeMoveObjectDir()
{
	for ( int i=0; i < iCurNodes; i++)
		if ( mNode[i]->dir == 1) mNode[i]->dir = 0;
		else mNode[i]->dir = 1;

	if ( 	mForward == 1 )	mForward = 0;
	else mForward = 1;

	dunSwitchObjRailID = 0;
}

/// [62] void  CTramTrainVagons::StopTrain(  BOOL stoptrain )  
void  CTramTrainVagons::StopTrain(  BOOL stoptrain )  
{
	if ( stoptrain == TRUE ) mStopTrain = 1;
	else mStopTrain = 0;
}

/// [63] BOOL  CTramTrainVagons::IsTrainStopped()   
BOOL  CTramTrainVagons::IsTrainStopped()
{
	if ( mStopTrain == 1) return TRUE;
	return FALSE;
}

/// [64] void CTramTrainVagons::ChangeTrainObjectDir()
void CTramTrainVagons::ChangeTrainObjectDir()
{
	 CTramModelDef mModel[6];
	 if ( mForward == 0 ) ChangeMoveObjectDir();

	int nodes = iCurNodes -1;			//nodes 3
	for ( int i=0 ; i <  nodes ; i++)    //  iCurNodes = 4
	{
		mModel[i].len = mNode[i]->len;
		mModel[i].style = mNode[i]->mStyle; 
		mModel[i].width = mNode[i]->mWidth;
	}

	CFPoint  new_point ;
mDebug.CDebugPut("mNode[0]->dir  :%d  ", mNode[0]->dir );
// works only for forward 0  --> 
	mStartDir = mNode[0]->dir;
	 
	if ( mNode[0]->dir == 0 ) // towards 0 endpoint
	{new_point = mNode[nodes]->sp;	}
	else 
	{	new_point = mNode[nodes]->sp;}
mDebug.CDebugPut("tdir  :%d mStartDir %d  ",   0 , mStartDir );
	CTramModelDef *pModel =  &mModel[0];
	iCurNodes = nodes+1;
	int inc_size =0;

	for ( int i=0 ; i< iCurNodes; i++)
	{
		mNode[i] = new CTramConNode(); 

		mNode[i]->len = (pModel+i)->len;
		mNode[i]->mStyle = (pModel+i)->style;
		mNode[i]->mWidth = (pModel+i)->width;

		if ( mStartDir == 1 ) mNode[i]->dir  =0;
		else mNode[i]->dir = 1;

		mNode[i]->fcur_len = (float)mNode[i]->len;
		mNode[i]->pSegment = mStartSegment;
		// size of  the node
		mNode[i]->sp = GetPointFmStart( new_point , mStartSegment->GetPoint(mStartDir) , (float)inc_size );	
		inc_size += mNode[i]->len;
	}
} 

 
 