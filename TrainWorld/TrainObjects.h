///////////////////////////////////////////////////////////////////////////
//
//
//
//	All object definition
//
//
///////////////////////////////////////////////////////////////////////////



#pragma once

#include "stdafx.h"

#define MAX_RAILS  10000
#define MAX_OBJS 2000
#define MAX_TRAMS 200
#define MAXINDEX  14	
#define MAX_CNTGRP  100
// distance to check collision
#define MIN_EP_DISTANCE 30

//  time for reg green yellow
//#define TMPDEF 40
#define DEF_TIMEOUT 40 

class CControlGroupElement
{
	public:
	CControlGroupElement();
	~CControlGroupElement();	

	void CreateElTable(int size);
	void KickOnElement();
	void KickMonoElement();
	void AddItem( int el );
	//void SetMono();

	int  *mptr;
	int  miPtr;
	int  mSize;
	int  mTimeOut;
	int  mCurStopPtr;     // circular pointer  to the stops in group  -if next reset CurState to yellow
	int  mCurState;		 // state green,yellow,red,yellow   - when chnage reset time out
	WORD  mType;
	WORD  mMono;

	int  m_yellow_TimeOut; 

};


class CMyObject : public CObject
{
public:
	CMyObject();
	virtual ~CMyObject();
	virtual void DspInformation();
	virtual void DrawMyObject( CPoint offset, HDC hdc , CRect rc );   // must be hdc, window
	virtual void Serialize(CArchive& ar);

	void SetObjectType(int itype);
	int  GetObjectType();
protected:
	int mObjType;
};


class CObjControls  : public CMyObject
{
public:
	CObjControls();
	CObjControls(int tId,  CPoint endep );
	virtual ~CObjControls();

	void DrawMyObject( CPoint offset, HDC hdc , CRect rc );   // must be hdc, window
	void Serialize(CArchive& ar);
	void SetCenterPoint( CPoint pt);
	void SetRailObjectPtr( CObjRail *pObjRail );
	void SetRailControlPoint( CPoint  pt  );
 	void SetRailObjectEndpoint( int ep  );

	WORD	GetRailPtrId();  //	WORD m_ObjRailID;
	void    SetRailPtrId(int id );
	CPoint	GetCenterPoint();
	CPoint	GetRailControlPoint();

	int GetStatus();
	void SetStatus(int is);
	void SetGroupId( WORD id );
	int GetGroupId();
	//WORD GetNextGroupId();

	void ToggleStatus();
	void ToggleStatusEx() ;
	CObjRail *GetRailObjectPointer();
	int  GetControlEndpoint();

//	void InitControlObjects ();
	int  GetControlID();  ///m_ID

	int GetTimeOut(); //	int  m_timeout;
	void SetTimeOut(int tmout);

	BOOL Signaling();              
	void SetSignal( BOOL bset );   

	void SetTextId( int id );  // m_text_id
	int  GetTextId();

	BOOL IsMonostab();
    void SetMonoStab( BOOL bset);

private:
	CPoint m_CenterPoint;
	int m_ID;
	CObjRail *mpObjRail;
	WORD m_ObjRailID;
	WORD m_group;
	CPoint  mPt;
	int  mep; // endpoint
	int  status;
	int  m_timeout;       
	int  m_signal;
	int  m_text_id;
	BYTE m_isMonoStab; 
	// store the name of the control
	// WORD  m_text_idtype;  //  what is it is line or endline must be with text
    

	friend class CControlGroupElement;

};


#define MAX_CNT_RECORDS  2000 
#define MXINDEXENTRIES   80

typedef struct {
	WORD mLineId;      
	WORD mControlId;
	WORD mParam;   //  next rail , starttime  ( hour:min ) -->converted to absolute  60*hour+min
	WORD mType;   // daily(switch) , night(switch) , starttime (stops)  - add selection
}   LINERECORD ;  


class CObjTramLine  
{
public:
	CObjTramLine();
	virtual ~CObjTramLine();
	void Serialize(CArchive& ar);
	int GetControlParam( int route , int CntId );  
	int GetControlParam( int route_id ,int id ,  int CntId ) ; 

	LINERECORD  mLineDataBase[MAX_CNT_RECORDS+4];
	int  mRecords;

	int   mLineIndex[MXINDEXENTRIES];
	int   mMaxIndexEntry;

	int GetControlParamByIndex( int route , int CntId ); 
	int GetControlParamByIndex(  int route_id , int CntId ,  int Tram_id );

	void  DoLineIndex();
private:
 
	int   FindFirstLineItem( int route_id );

	friend class CTramTrainVagons;
};


 
#define MAX_NAME_RECORDS  250 
#define MAX_NAME_LENGHT 32 

typedef struct {
	WORD mId;  // not used      
	WORD mType;
	CString mName;
	//char mName[MAX_NAME_LENGHT];   //  
}   NAMERECORD ;


class CObjNames  
{
public:
	CObjNames();
	virtual ~CObjNames();
	void Serialize(CArchive& ar);
	int GetName( int id , int type , char *p );   
	void DeleteLast();

	NAMERECORD  mNameDataBase[MAX_NAME_RECORDS+2];
	int mRecords;
	int	mLastId;	

	friend class CTramTrainVagons;
};


class CObjRail : public CMyObject
{

public:
	CObjRail();
	CObjRail( int tId, CPoint startep, CPoint endep  );
	CObjRail( int tId, CFPoint startep, CFPoint endep  );
	virtual ~CObjRail();
	void DrawMyObject( CPoint offset, HDC hdc , CRect rc);
	void Serialize(CArchive& ar);
	void SetConnection( int index , int value );
	CFPoint  GetPoint( int ep );
	CPoint  GetPPoint( int ep );
	void  SetPoint( int ep , CPoint pt );
	//CPoint  GetPoint( int ep );
	int   GetMode( int mode_no);
	void  SetMode( int mode_no ,int newmode );
	int GetRailId();
	int GetRailConnId( int endpoint );

	void SetSwitch( int ep, int mode);
	// here to check wthether switch
	int GetSwitchStatus(int ep) ;
	void SetSelected(int sel);  
	void SetUndergroundRail( BOOL ion );
	BOOL IsUndergroundRail();


protected:
	// objects
	WORD m_ID;				// this object ID
	WORD m_Aux;
	CPoint m_EndPoints[2];	// physical coordinates  X1,Y1,X2,Y2
	WORD m_Connections[4];	// connected to  0-1 first Ep  2-3 second ep
	unsigned char Switch[2];	// 0 or 1 of the switch is defined
	unsigned char Handled ;
	unsigned char Selected;
	unsigned char m_mode[4];  // mode(2) to pass back infor , (1) speed index
 


	friend class CObjRailsColl ;
};


class CObjBendRail : public CObjRail
{

public:
	CObjBendRail();
	CObjBendRail( int tId, CPoint startep, CPoint endep  );
	CObjBendRail( int tId, CFPoint startep, CFPoint endep  );
	virtual ~CObjBendRail();
	void DrawMyObject( CPoint offset, HDC hdc , CRect rc);
	void Serialize(CArchive& ar);
	void SetCenterPoint( CFPoint cp );
	CFPoint  GetCenterPoint(); 

//	virtual void Serialize(CArchive& ar);
//	CObjRail( CRect rc , int type );

protected:
	CFPoint mCenterPoint;
 	friend class CObjRailsColl ;
};



class CObjControlStation : public CMyObject
{
public:
	CObjControlStation();
	virtual ~CObjControlStation();
//	virtual void Serialize(CArchive& ar);
protected:
	// colection of controlled switches
	// collection of controlled semaphores
	// collection of trips schedules

	friend class CControlGroupElement;

};

class CTramTrainVagons;

class CObjRailsColl : public CMyObject
{
public:
	CObjRailsColl();
	virtual ~CObjRailsColl();

	void Resources();

	//void FixSwitch();

	//void CheckSwitches();
	int CheckSwitchesDetails(int mode);
	int CheckSemaphores(int mode);
	int CheckStops(int mode);
	int CheckIndexTableId( int id ,int cid  ) ;
	int CheckIndexTable( ) ;


	void InitControlObjects ();

	int CheckThisEP( int ep, CObjRail *p , int mode);

	BOOL AddObjectStright(  CPoint offset, DRAWDATASTRUCT *p );
	BOOL AddObjectStrightEnd(  CPoint offset, DRAWDATASTRUCT *p );
	BOOL AddObjectBend(   CPoint offset, int type , DRAWDATASTRUCT *p  );
	BOOL AddObjectDblStright(   CPoint offset, int type , DRAWDATASTRUCT *p  );
	BOOL AddObjectControl(  CPoint offset, int type, DRAWDATASTRUCT *pds ) ;

	BOOL AddObjectControlGroup(  CPoint offset, CRect rc , int type) ;
	void ManageSemInControlGroup(    ) ;

	void CreateControlGroupTbl();

	BOOL RemoveLastControl();
	BOOL RemoveLastRail();
	BOOL RemoveLastTram();
	BOOL RemoveLastContrGroup();
	BOOL DeleteControlById(  int theId   )  ;

	BOOL AddObjectTram( CTramModelDef *ptm ,  int nodes , int routeId ) ;
	void MoveTrams(float steps);
	void StartTrams();
	void StopTrams();

	void ReversTramsDir();
	void DrawTrams(  CPoint offset, HDC hdc , CRect rc); 
	BOOL CheckColissionOfThisTrain( CTramTrainVagons *pv );

	//BOOL FindObjects(   CPoint offset, CRect rc );
	BOOL FindRailObjects(   CPoint offset, CRect rc ) ;
	//BOOL FindObjects(   CPoint offset, CPoint rc );
	BOOL FindRailObject( CPoint offset, CPoint pt ); 

	CTramTrainVagons *FindTrainObject(   CPoint offset, CPoint pt ) ;

	CObjRail   * FindObjectById(    int Id ) ;   // non idexed version
	CObjControls  *CObjRailsColl::FindControlSwitchObject(   int railID , int ep ); 

	CRect ManageControlObject (  CPoint offset, CPoint pt  );
	CObjControls *FindControlObject(   CPoint offset, CPoint rc );
	CObjControls *FindControlObject ( int railID , int type , int inum);
	CObjControls *FindControlObject(  int objId   ) ;
	CObjControls *FindControlObjectByTextId(  int textid  ); 

	CTramTrainVagons *FindTrainObjectById(  int objId   ) ;

	int  GetNumberOfSelectedObjects();
	BOOL SnapSelectedObjects(); 

	BOOL HitBendHandle( CPoint offset, CPoint rc );
	BOOL ModifyBendObject( CPoint offset, CPoint rc );

	BOOL ClearSelected();
	BOOL DeleteSelectedRails();
	void DisplaySelected();
	BOOL IsSingleBendRailSelected();
	void DrawHandleOnSelected();
	CObjRail *GetRailSelected();

	CRect GetSelectedObjectRect(CPoint offset,int mode);

	void DrawMyObject(  CPoint offset, HDC hdc , CRect rc); 
	void DrawMyObjects(  CPoint offset, HDC hdc , CRect rc); 

	CObjRail *GetByEndPoint( CObjRail *pOld , int dir ); 
	//CObjRail *GetByEndPointAbs( CObjRail *pOld , int endpoint ) ; 

	CObjRail   *GetAt( int idx);

	CObjRail   *GetClosestRail ( CPoint offset , CPoint ref , int MaxDistance);
	CObjRail   *GetClosestRailEp ( CPoint offset , CPoint ref , int MaxDistance , int *ep);

 

	void DeleteAllObjects();
	void Serialize(CArchive& ar);
	void DebugRailList();

	void DoIndex();  // all the time whne start control
	CObjRail  *GetIndex( int railId ); 
	CObjRail  *GetRailObjPtrByIdIndex( int railId ) ;
	CObjRail  *GetRailPtrById( int ConId  );  // indexed version

	/// [26] CObjRailsColl::GetNumberOfTrams()    / 
 
	int GetNumberOfTrams();
	int GetNumberOfControlGroup();
	int GetNumberOfControls();
 
	int GetTramId( int i );
	BOOL  DeleteTramById( int id );  

	BOOL CObjRailsColl::CheckIfTheEpIsMerging( CObjRail *p  , int endpoint , int *tbls2 );
	BOOL CObjRailsColl::CheckIfGivenTramInCloseDistance ( CTramTrainVagons *pv , int *tbls2 )  ;


protected:
	void AutoSnap(CObjRail *p);
	//void Glue( CObjRail *p1 , CObjRail *p2 , int conn1 , int conn2 );
	//void GlueAdjust( CObjRail *p  , CObjRail *px , int conn1 , int conn2 );
	void Detach( WORD mcID ); 

	int m_NbrOfRails;
	int m_LastRailId;
	BOOL mDrawHandle;

	int Index[MAXINDEX+2];

	// what size ?
 	int EpointIndx[MAXINDEX+2];
	int Indexes;

	//CObList  mRailList;  // list of the rails or simple  table  - indexed 
	//  optional
	CObjRail  *mRailTable[MAX_RAILS+4];
 	int  TblIndex[MAX_RAILS+4];

	CMyObject  *mObjTable[MAX_OBJS+4];
	int m_NbrOfObj;
	int m_LastObjId;
	WORD m_LastGrpId;


	CTramTrainVagons  *mTramTable[MAX_TRAMS+4];
	int m_NbrOfTrams;
	int m_LastTramId;

 

	int mCntGrpPtr;
	CControlGroupElement*  mCntGrpTbl[MAX_CNTGRP];

	friend class CControlGroupElement ;

};

 // 5 vagons
#define MAX_NODES  12

class CTramConNode
{
	public:
	CTramConNode();
	float GetLenghCorrection();
	void  AddCurrentDif( float dif );
	CFPoint sp;  // position on the rail
	CObjRail *pSegment; // pointer to the  rail 

	WORD  m_ObjRailID;

	int  len;
	int  dir; // 0 to 0  1 to 1
	float fcur_len;
	bool bCorrSign;
	float mDifTable[2];
 
	DWORD mStyle;
	int mWidth;
	friend class CTramTrain;
	friend class CTramTrainVagons ;
};



class CTramTrainVagons   
{
	public:
		CTramTrainVagons();
		~CTramTrainVagons();
	 	CTramTrainVagons( CFPoint mStartPoint , CObjRail *pSegment , int RailEp  );
	 	CTramTrainVagons( CFPoint mStartPoint , CObjRail *pSegment ); // assume 0 --> 1
    	BOOL CreateVagons(  CTramModelDef *pModel , int nodes  );
		void SetTramId( int TramId );  //mId
		int  GetTramId();

		void Serialize(CArchive& ar);
		void DrawObject(HDC hdc , CPoint offset );
		BOOL MoveObject( float step);
		BOOL StateObject();
		void ChangeMoveObjectDir();

		void ChangeTrainObjectDir();
		CFPoint GetStartPoint();
		CFPoint GetEndPoint();	

		WORD GetRailPtrId( int knode );			// mNode[MAX_NODES]->m_ObjRailID ;

		WORD GetRailPtrId2( int knode );			// mNode[MAX_NODES]->m_ObjRailID ;
		void SetRailObjectPtr( int knode , CObjRail *); // mNode[MAX_NODES]->pSegment ;
		int  GetNumberOfNodes();  //iCurNodes

		CFPoint  GetHeadPoint();
		CFPoint  GetTailPoint();

		CObjRail *GetHeadRailObjPtr();  
		CObjRail *GetTailRailObjPtr(); 

 
		void ReInitializeObject();

		void  StopTrain(  BOOL stoptrain );    
		BOOL  IsTrainStopped();	

		int  GetLineId();
		void SetLineId( int lineid);

		int  GetControlEndpoint(); 
		int  SetSwitch(int ep , int nId ); 
		int  ControlStopTimeOut( int nId ) ;

		int GetDistanceOfTheHeadToEp();
		int   GetHeadPointEpDir();
		CFPoint   GetNodePoint( int inode );
		BOOL IsTramsInMotion();

		void SetManualControlMode( bool byesno );
		BOOL GetManualControlStatus();

		void  ReversTrain(  BOOL revtrain );    
		BOOL  IsTrainReversed();

		void  SetDynTimeOut(  int tick );    
		int		GetDynTimeOut();
		BYTE  GetCurState();
		BYTE  GetStopReason();



	private:
		WORD  mId;
		void InitializeObject(CFPoint mStartPoint , CObjRail *pSegment , int RailEp );
		CTramConNode *mNode[MAX_NODES];
		int iCurNodes;
		CFPoint mStartPoint;
		CObjRail *mStartSegment;
		int mStartDir;

		BYTE  mForward;     //  1 is forward
		BYTE  mStopTrain;	//  1 is stopped
		BYTE  mLineId;      // need serialize
		BYTE  mGetControl;  // we are getting control

		// state machine
		BYTE dynState;
		BYTE dynStopReason;
		BYTE dynService;
		BYTE dynExtra;
		int  dynTmOut;
		WORD dunStopObjRailID;
		WORD dunSwitchObjRailID;

		BOOL CollisionCheck();
		BOOL StopCheck();
		BOOL SwitchCheck();
		BOOL SemCheck();
		BOOL StopGetStatus();

};

int  GoRailOperStatus();
void	MoveNode( CTramConNode *pnode , float step )  ;
void	MoveNode( CTramConNode *pnode , float step , int node_nbr)  ;
BOOL CheckSwitch(  CObjRail *p , CObjRail *p1  , int ep , int ep1  );
BOOL CheckSwitch(  CObjRail *p , CObjRail *p1 , CObjRail *p2 , int ep , int ep1, int ep2 ) ;
int CheckValidConnections ( CObjRail *p , int epc , CObjRail *p1 , CObjRail *p2 );
int CheckPhysicalConnection(  int nr , int ep, CObjRail *p , CObjRail *prt[] , int *ept , int mode);
CPoint  GetPointOnRail ( CObjRail   *px , CMyPoint ControlPoint );
int GetDistanceOfPointFromRail( CObjRail   *px , CMyPoint ControlPoint );
CObjBendRail *IsBendObject( CObjRail   *px   );
int GetOtherEndEp( CObjRail *pnx  , int ThisId );
BOOL CheckIfTheEpIsSwitch( CObjRail *p  , int endpoint )  ;
int BrowseTime( CString Cs );