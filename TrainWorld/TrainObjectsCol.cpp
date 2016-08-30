
#include "stdafx.h"
#include "Math.h"

#include "StdTrainDef.h"

#include "TrainObjects.h"

#include "MainFrm.h"

#include "Debug.h"
extern CDebug mDebug;

 
extern CSystem  mSystem;



///////////////////////////////////////////////////////////////////////
///-
/// [00] CObjRailsColl::CObjRailsColl()
///
/// ------[Object adding group]
/// [10] BOOL CObjRailsColl::AddObjectStright(CPoint offset,DRAWDATASTRUCT *pds) 
/// [11] BOOL CObjRailsColl::AddObjectStrightEnd(CPoint offset,DRAWDATASTRUCT *pds) 
/// [12] BOOL CObjRailsColl::AddObjectDblStright(CPoint offset,DRAWDATASTRUCT *pds)  
/// [13] BOOL CObjRailsColl::AddObjectBend(CPoint offset,DRAWDATASTRUCT *pds)  
/// [14] BOOL CObjRailsColl::AddObjectControl(CPoint offset,DRAWDATASTRUCT *pds) 
///
/// ------[Object delete group]
/// [16] BOOL CObjRailsColl::RemoveLastControl()  
/// [17] BOOL CObjRailsColl::RemoveLastRail()  
/// [18] BOOL CObjRailsColl::RemoveLastTram()    
/// [19] BOOL CObjRailsColl::RemoveLastContrGroup() 
/// [20] BOOL CObjRailsColl::DeleteSelected()
/// [21] void CObjRailsColl::DeleteAllObjects()  
/// [22] int CObjRailsColl::GetNumberOfTrams()  
/// [23] int CObjRailsColl::GetNumberOfControlGroup() 
/// [24] int CObjRailsColl::GetNumberOfControls()  
//  [25] BOOL CObjRailsColl::DeleteControlById(int id)
/// [26] BOOL CObjRailsColl::DeleteTramById(int id) 
///------[control object handling group]
/// [27] CTramTrainVagons * CObjRailsColl::FindTrainObjectById(int id) 
 
///  
//  [28] BOOL CObjRailsColl::DeleteControlById(int id) 
/// [30] CObjControls *CObjRailsColl::FindControlObject(   CPoint offset, CPoint pt )  
/// [31] CObjControls *CObjRailsColl::FindControlObject(  int railID , int type , int inum) 
/// [32] CObjRailsColl::InitControlObjects() 
/// [33] CObjRailsColl::ManageControlObject (  CPoint offset, CPoint pt  ) 
/// [34] CObjRailsColl::AddObjectControlGroup( CPoint offset, CRect rc , int type)
/// [35] CObjRailsColl::CreateControlGroupTbl() 
/// [36] CObjRailsColl::ManageSemInControlGroup()
/// [37] CObjRailsColl::FindControlSwitchObject(  int railID , int ep ) 
/// [38] CObjRailsColl::FindControlObject(  int objID  ) 
/// 
/// ------[find rail objects handling group]
/// [40] CObjRailsColl::FindObjects(   CPoint offset, CRect rc ) -- find rails	!!! rename to FindRailObjects
/// [41] BOOL CObjRailsColl::FindRailObject(   CPoint offset, CRect rc ) 
/// [42] CObjRailsColl::FindObjectById(    int Id  )   -- find rails	!!! rename to FindRailObjectById
/// [43] CObjRailsColl::GetClosestRail ( CPoint offset , CPoint ptp , int MaxDistance)	
/// [44] CObjRailsColl::GetClosestRailEp ( CPoint offset , CPoint ptp , int MaxDistance , int *ep)
/// [45] CObjRail *CObjRailsColl::GetByEndPoint( CObjRail *pOld , int endpoint ) 
/// [46] CObjRailsColl::GetByEndPointAbs( CObjRail *pOld , int endpoint ) 
/// [47] CObjRailsColl::GetAt( int idx) 
/// [48] CObjRailsColl::GetRailPtrById( int id )
/// [49] CObjRailsColl::DoIndex()
/// [50] CObjRailsColl::GetIndex(int railId )
/// [51] CObjRailsColl::GetRailSelected()
/// [52] CObjRailsColl::GetNumberOfSelectedObjects()
/// [53] CObjRailsColl::ClearSelected()
/// [54] CObjRailsColl::DrawHandleOnSelected()
/// [55] CObjRailsColl::GetSelectedObjectRect(CPoint offset, int mode)
///
/// ------[bend rail objects handling group]
/// [60] CObjRailsColl::HitBendHandle( CPoint offset, CPoint point ) 
/// [61] CObjRailsColl::ModifyBendObject( CPoint offset, CPoint point )  
/// [62] CObjRailsColl::IsSingleBendRailSelected()
/// 
/// [70] CObjRailsColl::SnapSelectedObjects()  
/// [71] CObjRailsColl::Detach( WORD mcID ) 
/// [72] CObjRailsColl::GlueAdjust( CObjRail *p  , CObjRail *px , int conn1 , int conn2 )
/// [73] CObjRailsColl::Glue( CObjRail *p  , CObjRail *px , int conn1 , int conn2 )
/// [74] CObjRailsColl::AutoSnap(CObjRail *p)
/// [75] CObjRailsColl::Serialize(CArchive& ar)
///
/// ------[display or draw]
/// [80] CObjRailsColl::DisplaySelected()  
/// [81] CObjRailsColl::DrawMyObject( CPoint offset, HDC hdc , CRect rc)     // draw my rail object
/// [82] CObjRailsColl::DrawMyObjects(  CPoint offset, HDC hdc , CRect rc)   // draw my control objects
/// [83] CObjRailsColl::DebugRailList()
/// [84] CObjRailsColl::Resources()
///
/// -----  rail object verification and fix
/// [90] CObjRailsColl::CheckSwitchesDetails(int mode)
/// [91] CObjRailsColl::CheckThisEP(int ep, CObjRail *p , int mode) 
/// [92] CObjRailsColl::CheckStops(int mode)
/// [93] int CObjRailsColl::CheckSemaphores(int mode)
/// [94] int CObjRailsColl::CheckIndexTable()
/// [95] int CObjRailsColl::CheckIndexTableId()	
///
/// -----  [tram object releted]
/// [100] BOOL CObjRailsColl::AddObjectTram( CTramModelDef *ptm , int nodes) 
/// [101] BOOL CObjRailsColl::FindTrainObject(  CPoint offset, CPoint pt ) 
/// [102] CObjRailsColl::GetTramId( int i )
/// [103] CObjRailsColl::MoveTrams(float steps)
/// [104] CObjRailsColl::StartTrams() 
/// [105] CObjRailsColl::StopTrams() 
/// [106] CObjRailsColl::ReversTramsDir() 
/// [106] CObjRailsColl::ReversTramsDir() 
/// [107] CObjRailsColl::CheckIfTheEpIsMerging(CObjRail *p  , int endpoint , int *tbls2 )
/// [108] BOOL CObjRailsColl::CheckIfGivenTramInCloseDistance(CTramTrainVagons *p , int *tbls2 )
/// [109] BOOL CObjRailsColl::CheckColissionOfThisTrain(CTramTrainVagons *p ) 
///
///----------------------------------------------------------------------------------


CObjRailsColl  mCObjRailsColl;


////////////////////////////////
/// [00] CObjRailsColl::CObjRailsColl()

CObjRailsColl::CObjRailsColl()
{
	m_NbrOfRails=0;
	m_LastRailId=0;
	mDrawHandle = FALSE;
	Indexes=0;
	m_NbrOfObj = 0;
	m_LastObjId =0;
	m_NbrOfTrams = 0;
	m_LastTramId =0;
	m_LastGrpId = 0;
	mCntGrpPtr = 0;
}

CObjRailsColl::~CObjRailsColl() 
{

}
/// [10] BOOL CObjRailsColl::AddObjectStright(CPoint offset,DRAWDATASTRUCT *pds) 
BOOL CObjRailsColl::AddObjectStright( CPoint offset, DRAWDATASTRUCT *pds  ) 
{
	if ( GetDistance( pds->StartPoint , pds->EndPoint ) <  4 )  return FALSE;
	if ( m_NbrOfRails >= MAX_RAILS ) return FALSE;
	m_LastRailId+=1;
	CObjRail *p = new CObjRail(m_LastRailId, pds->StartPoint+offset , pds->EndPoint+offset );
	p->SetObjectType( ObjStraightRail );
	mRailTable[m_NbrOfRails] = p;

TblIndex[p->GetRailId()] = m_NbrOfRails;

	m_NbrOfRails+=1;
	AutoSnap(p);
	//m_NbrOfRails+=1;
	return TRUE;
}
/// [11] CObjRailsColl::AddObjectStrightEnd(CPoint offset,DRAWDATASTRUCT *pds) 
BOOL CObjRailsColl::AddObjectStrightEnd( CPoint offset, DRAWDATASTRUCT *pds) 
{
	if ( GetDistance( pds->StartPoint , pds->EndPoint ) <  4 )  return FALSE;
	if ( m_NbrOfRails >= MAX_RAILS ) return FALSE;
	m_LastRailId+=1;
	CObjRail *p = new CObjRail(m_LastRailId, pds->StartPoint+offset , pds->EndPoint+offset );
	p->SetObjectType( ObjRailEnd );
	p->m_Connections[2]=p->m_Connections[3]= -1;
	mRailTable[m_NbrOfRails] = p;

TblIndex[p->GetRailId()] = m_NbrOfRails;
	m_NbrOfRails+=1;
	AutoSnap(p);
	//m_NbrOfRails+=1;
	return TRUE;
}

/// [12] CObjRailsColl::AddObjectDblStright(CPoint offset,DRAWDATASTRUCT *pds) 
BOOL CObjRailsColl::AddObjectDblStright( CPoint offset, int type, DRAWDATASTRUCT *pds  ) 
{
	if ( GetDistance( pds->StartPoint , pds->EndPoint ) <  4 )  return FALSE;
	DRAWDATASTRUCT pds1;
	memcpy( &pds1, pds ,sizeof (DRAWDATASTRUCT));
	pds1.StartPoint = ComputeTwoParLines( pds->StartPoint , pds->EndPoint , RAILWIDTH , 0 ) ;
	pds1.EndPoint = ComputeTwoParLines( pds->StartPoint , pds->EndPoint , RAILWIDTH , 2) ;
	AddObjectStright(  offset , &pds1  ); 
	pds1.StartPoint = ComputeTwoParLines( pds->StartPoint , pds->EndPoint , RAILWIDTH , 1 ) ;
	pds1.EndPoint = ComputeTwoParLines( pds->StartPoint , pds->EndPoint , RAILWIDTH , 3) ;
	AddObjectStright(  offset , &pds1  ); 
	return TRUE;
}

/// [13] CObjRailsColl::AddObjectBend(CPoint offset,DRAWDATASTRUCT *pds)  
BOOL CObjRailsColl::AddObjectBend(  CPoint offset, int type, DRAWDATASTRUCT *pds ) 
{
	if ( GetDistance( pds->StartPoint , pds->EndPoint) <  4 )  return FALSE;
	if ( m_NbrOfRails >= MAX_RAILS ) return FALSE;
	m_LastRailId+=1;
	CObjBendRail *p = new CObjBendRail(  m_LastRailId , pds->StartPoint+offset , pds->EndPoint +offset);
	p->SetObjectType( type );	
	p->SetCenterPoint( pds->CenterPoint +offset);
	mRailTable[m_NbrOfRails] = p;

TblIndex[p->GetRailId()] = m_NbrOfRails;
	m_NbrOfRails+=1;
	AutoSnap(p);
	//m_NbrOfRails+=1;
	return TRUE;
}

//mDebug.CDebugPut("*AddObjectControl0*: %6.2f  : %6.2f ",  (float)pp.x ,  (float)pp.y );
/// [14] CObjRailsColl::AddObjectControl(CPoint offset,DRAWDATASTRUCT *pds)  
BOOL CObjRailsColl::AddObjectControl(  CPoint offset, int type, DRAWDATASTRUCT *pds ) 
{
	if ( m_NbrOfObj >= MAX_OBJS ) return FALSE;
	m_LastObjId+=1;
 
	CMyPoint pp(   pds->EndPoint.x +offset.x, pds->EndPoint.y +offset.y );
	CObjControls *p = new CObjControls(  m_LastObjId ,  pp );  //  pp show control main position in absolute coordination
	if ( (type == ObjStop) || ( type == ObjSem )   ) 
	{
		p->SetObjectType( type  );	
	 	CMyPoint ptt ( pds->EndPoint  );  // this is the icon placement point in relative coordination
		CObjRail   *px =  GetClosestRail ( offset , ptt  , 60  );

		if ( px != NULL )
		{
			CPoint rp =  GetPointOnRail ( px , pp );
			p->SetRailObjectPtr( px);
			p->SetRailControlPoint ( rp);
			mObjTable[m_NbrOfObj] = p;
			m_NbrOfObj+=1;
			return TRUE;
		}
		else delete p;
	}

	if ( type == ObjSwitch ) 
	{	
		p->SetObjectType( ObjSwitch );
		CMyPoint ptt ( pds->EndPoint  );

		int ep;
		CObjRail   *px =  GetClosestRailEp ( offset , ptt  , 60 ,&ep );
		if ( px != NULL )
		{ 
			p->SetRailObjectPtr( px);
			p->SetRailObjectEndpoint(  ep);
			CMyPoint  cp1 = px->GetPoint( ep );
			p->SetRailControlPoint ( cp1 );
			mObjTable[m_NbrOfObj] = p;
			m_NbrOfObj+=1;
			return TRUE;
		}
		else delete p;
	}

	return FALSE;
}

/// [16] BOOL CObjRailsColl::RemoveLastControl()  
BOOL CObjRailsColl::RemoveLastControl()
{
	if ( m_NbrOfObj > 0 )
	{
		m_NbrOfObj -= 1;
		CObjControls *p  =  (CObjControls *)mObjTable[m_NbrOfObj];
		delete p;
		m_LastObjId -=1;
		return TRUE;
	}
	return FALSE;
}
/// [17] BOOL CObjRailsColl::RemoveLastRail()  
BOOL CObjRailsColl::RemoveLastRail()
{
	if ( m_NbrOfRails > 0 )
	{
		m_NbrOfRails -= 1;
		CObjBendRail *p  =  (CObjBendRail *)mRailTable[m_NbrOfRails]; 
		TblIndex[p->GetRailId()] = 0;
		delete p;
		m_LastRailId-=1;

		return TRUE;
	}
	return FALSE;
}

/// [18] BOOL CObjRailsColl::RemoveLastTram()     
 
BOOL CObjRailsColl::RemoveLastTram()
{
	if ( m_NbrOfTrams > 0 )
	{
		m_NbrOfTrams -= 1;
		CTramTrainVagons *p  =  (CTramTrainVagons *)mTramTable[m_NbrOfTrams]; 
		delete p;
		m_LastTramId -=1;
		return TRUE;
	}
	return FALSE;
}
 
/// [19] BOOL CObjRailsColl::RemoveLastContrGroup()     
 
BOOL CObjRailsColl::RemoveLastContrGroup()
{
	if ( mCntGrpPtr > 0 )
	{
		mCntGrpPtr -= 1;
		CControlGroupElement *p  =  (CControlGroupElement *)mCntGrpTbl[mCntGrpPtr]; 
		delete p;
		return TRUE;
	}
	return FALSE;
}


/// [20] BOOL CObjRailsColl::DeleteSelected()
BOOL CObjRailsColl::DeleteSelectedRails() 
{
	int i ;
	BOOL bwas = FALSE;
	for ( i =0; i < Indexes ; i++)
	{
			CObjRail *p = mRailTable[Index[i]];
			if ( p->Selected == 1)
			{
				int  j=-1;
				Detach( p->GetRailId() ) ;
				j =  Index[i] ;

	            TblIndex[p->GetRailId()] = 0;
				delete p;
				//break;
 
				if ( j >=0 )
				{
					int ii;
					m_NbrOfRails -=1 ;
					for ( ii = j;  ii < m_NbrOfRails; ii++)
							mRailTable[ii] = mRailTable[ii+1];
				}

				bwas = TRUE;
			}
	}

	if ( bwas == TRUE )	
	{
		DoIndex();
		CheckSwitchesDetails(1);
	}
	return bwas;
}

/// [21] void CObjRailsColl::DeleteAllObjects()  
void CObjRailsColl::DeleteAllObjects()
{

	   for (int  i =0; i < m_NbrOfRails ; i++)
		{
			CObjRail *p = mRailTable[i];
			delete p;
		}
	   m_NbrOfRails =0;
	   m_LastRailId =0;

 
	   for ( int i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p = (CObjControls*)mObjTable[i];
			delete p;
		}
       m_NbrOfObj =0;
	   m_LastObjId =0;

 
	   for (int i =0; i < m_NbrOfTrams ; i++)
		{
			CTramTrainVagons *p = (CTramTrainVagons*)mTramTable[i];
			delete p;
	   }
	   m_NbrOfTrams=0;
	   m_LastTramId=0;

	   // control gropups
	   for (int i =0; i < mCntGrpPtr ; i++)
		{
		CControlGroupElement *p = ( CControlGroupElement *  )  mCntGrpTbl[i];
		delete p;
	   }
	   mCntGrpPtr = 0;

}


/// [22] int CObjRailsColl::GetNumberOfTrams()    
 
int CObjRailsColl::GetNumberOfTrams()
{
	return  m_NbrOfTrams;
}

/// [23] int CObjRailsColl::GetNumberOfControlGroup()    

int CObjRailsColl::GetNumberOfControlGroup()
{
	return  mCntGrpPtr;
}

/// [24] int CObjRailsColl::GetNumberOfControls()    

int CObjRailsColl::GetNumberOfControls()
{
	return  m_NbrOfObj;
}

/// [25] BOOL CObjRailsColl::DeleteControlById(int id) 

BOOL  CObjRailsColl::DeleteControlById(  int theId   )  
{
	int  deleted =0;
	
	for ( int i=0;i<m_NbrOfObj;i++)
	{
		CObjControls *p;
		p = (CObjControls*)mObjTable[i];

	 	if ( p->GetControlID() == theId ) 
		{
		   // delete and shift 
			delete p;
			m_NbrOfObj -=1;
			while ( i < m_NbrOfObj )
			{
				mObjTable[i] = mObjTable[i+1];
				i++;
			}
			return TRUE;
		}
	}
	return FALSE;
}
 
/// [26] BOOL CObjRailsColl::DeleteTramById(int id) 

BOOL  CObjRailsColl::DeleteTramById(  int theId   )  
{
	int  deleted =0;
	
	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		CTramTrainVagons *pv;
		pv = mTramTable[i];
	 	if ( pv->GetTramId() == theId ) 
		{
		   // delete and shift 
			delete pv;
			//mTramTable[i] = NULL;  //unsafe  better compact
			// lets compact
			m_NbrOfTrams -=1;
			while ( i < m_NbrOfTrams )
			{
				mTramTable[i] = mTramTable[i+1];
				i++;
			}
			return TRUE;
		}
	}
	return FALSE;
}

/// [27] CTramTrainVagons * CObjRailsColl::FindTrainObjectById(int id) 

CTramTrainVagons *CObjRailsColl::FindTrainObjectById(  int theId   )  
{
	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		CTramTrainVagons *pv;
		pv = mTramTable[i];
	 	if ( pv->GetTramId() == theId ) return pv;
	}
	return NULL;
}



/// [30] CObjControls *CObjRailsColl::FindControlObject(   CPoint offset, CPoint pt )  
CObjControls *CObjRailsColl::FindControlObject(   CPoint offset, CPoint pt ) 
{
	for ( int i =0; i < m_NbrOfObj ; i++)
	{
		CObjControls *p = (CObjControls *) mObjTable[i];

		CPoint rpoint =   offset + pt;  
		CPoint cp = p->GetCenterPoint();

		CRect rc ( cp.x -10 , cp.y -10 , cp.x +10 , cp.y +10 );

		if ( rc.PtInRect(  rpoint ) == TRUE )
				return p;
	}
	return NULL;
}

/// [31] CObjRailsColl::FindControlObject(  int railID , int type , int inum) 
CObjControls *CObjRailsColl::FindControlObject ( int railID , int type , int inum)
{
	if (   (ObjStop == type ) || (ObjSem == type ))
	{
		int cnt = 0;
		for ( int i =0; i < m_NbrOfObj ; i++)
		{
		CObjControls *p = (CObjControls *) mObjTable[i];
		if ( p->GetObjectType() == type )
			{
			CObjRail *pr =  p->GetRailObjectPointer();
			if ( pr != NULL )
				if (  railID == pr->GetRailId() )
				{
				if ( cnt == inum ) return p;
				cnt+=1;
				}
			}
		}
	}

	if (   ObjSwitch == type )
	{
		for ( int i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p = (CObjControls *) mObjTable[i];
			if ( p->GetObjectType() == type )
			{
				CObjRail *pr =  p->GetRailObjectPointer();
				if ( pr != NULL )
				  if (  railID == pr->GetRailId() )
					if ( inum == p->GetControlEndpoint() )	
						return p;

			}
		}
	}


	return NULL;
}


/// [38] CObjRailsColl::FindControlObject(  int objId  ) 
CObjControls *CObjRailsColl::FindControlObject(  int objId   ) 
{
	for ( int i =0; i < m_NbrOfObj ; i++)
	{
		CObjControls *p = (CObjControls *) mObjTable[i];
		if ( p->GetControlID() == objId ) return p;
	}
	return NULL;
}


/// [381] CObjRailsColl::FindControlObject(  int objId  ) 
CObjControls *CObjRailsColl::FindControlObjectByTextId(  int textid  ) 
{
	for ( int i =0; i < m_NbrOfObj ; i++)
	{
		CObjControls *p = (CObjControls *) mObjTable[i];
		     if ( p->GetTextId() == textid ) return p;
	}
	return NULL;
}


/// [32] CObjRailsColl::InitControlObjects() 
void CObjRailsColl::InitControlObjects ()
{
	
	for ( int i =0; i < m_NbrOfObj ; i++)
		{
		CObjControls *p = (CObjControls *) mObjTable[i];
		if ( p->GetObjectType() ==   ObjSwitch )
			{
				CObjRail *pr =  p->GetRailObjectPointer();
				if ( pr != NULL )
			 		pr->SetSwitch( p->GetControlEndpoint() , p->GetStatus() ) ;	
			}

		//if ( p->GetObjectType() ==   ObjStop )
		//	if ( p->GetGroupId() == 0 )
		//	{
		//		p->SetStatus( STATUS_NOOPER  );
		//			 
		//	}


		}
}

/// [33] CObjRailsColl::ManageControlObject (  CPoint offset, CPoint pt  ) 
CRect CObjRailsColl::ManageControlObject (  CPoint offset, CPoint pt  )
{
	CObjControls *p = FindControlObject(     offset,   pt ) ;
	if ( p == NULL ) return NULL;

	CPoint cp = p->GetCenterPoint();
	cp -= offset;
	CRect rc ( cp.x -50 , cp.y -50 , cp.x +50 , cp.y +50 );

	// mDebug.CDebugPut((char *)" HITT mode[%d]  ", (int)p->GetObjectType() );

	if ( p->GetObjectType() == ObjSwitch )
	{
		p->ToggleStatus() ;
		CObjRail *pr =  p->GetRailObjectPointer();
		pr->SetSwitch( p->GetControlEndpoint() , p->GetStatus() ) ;		
	}
	else if ( p->GetObjectType() == ObjStop )
	{
		p->ToggleStatus() ;
		//CObjRail *pr =  p->GetRailObjectPointer();
		//pr->SetStopPoint( p->GetControlEndpoint() , p->GetStatus()   ); 
	}
	else if ( p->GetObjectType() == ObjSem )
	{
		p->ToggleStatusEx() ;
		//CObjRail *pr =  p->GetRailObjectPointer();
	}
	return rc;
}

 
// iterrate through controls and check if the control belongs to rect
/// [34] CObjRailsColl::AddObjectControlGroup( CPoint offset, CRect rc, int type ) 
BOOL CObjRailsColl::AddObjectControlGroup(  CPoint offset, CRect rc , int type ) 
{

	WORD w = m_LastGrpId +1 ;
	int cnt =0;
 

	for ( int i =0; i < m_NbrOfObj ; i++)
		{
		  CObjControls *p = (CObjControls *) mObjTable[i];

		  if ( type  != p->GetObjectType())  continue;
		  // brings center point to local window
		  CPoint lpt =  OffsetFPoint ( p->GetCenterPoint() , offset );
		   
		  if (   rc.PtInRect( lpt )   )
			{

				//mDebug.CDebugPut((char *)"In ....  "  );
				// create table of pointer to control 
				cnt+=1;
				p->SetGroupId(w);

			}
		}

	if ( cnt > 0 )
	{
		m_LastGrpId = w;

		CreateControlGroupTbl();

	}

	return TRUE;
}

/// [35] CObjRailsColl::CreateControlGroupTbl() 
void CObjRailsColl::CreateControlGroupTbl()
{
	//int i;

	// destroy if already created !
	if ( mCntGrpPtr > 0 )
	{
		for ( int i =0; i < mCntGrpPtr ; i++)
		{
			CControlGroupElement  *pg = mCntGrpTbl[i];
			delete pg; 
		}
	}

	mCntGrpPtr=0;
	// find max group ID
	int imax=0;

 	for ( int i =0; i <  m_NbrOfObj ; i++)
		{
		  CObjControls *p = (CObjControls *) mObjTable[i];
		  if ( p->GetObjectType() == ObjSem )
			  if ( p->GetGroupId() > imax )  imax = p->GetGroupId();

		  if ( p->GetObjectType() == ObjStop )
			  if ( p->GetGroupId() > imax )  imax = p->GetGroupId();


		  if ( imax > MAX_CNTGRP ) break;
		}

//mDebug.CDebugPut("*MaxGrpId*: %d Objs: %d ", imax ,  m_NbrOfObj );


	// find # of group ID  and create gropu structure
	int isiz;  
	for ( int j = 1; j <= imax ; j++)
	{
		isiz =0;
 		for ( int i =0; i <  m_NbrOfObj ; i++)
		{
		  CObjControls *p = (CObjControls *)  mObjTable[i];
		  if ( p->GetObjectType() == ObjSem )
			  if ( p->GetGroupId() ==  j )  isiz +=1;

		   if ( p->GetObjectType() == ObjStop )
			   if ( p->GetGroupId() ==  j )  isiz +=1;
		}

//mDebug.CDebugPut("*MaxGrpIdSize*: %d Objs: %d ", isiz ,  m_NbrOfObj );

		if ( isiz > 0 )
		{
			CControlGroupElement  *pg =  new CControlGroupElement();
			pg->CreateElTable( isiz );

 			for ( int i =0; i < m_NbrOfObj ; i++)
			{
				CObjControls *p = (CObjControls *)  mObjTable[i];
				if ( p->GetObjectType() == ObjSem )
					if ( p->GetGroupId() ==  j )  
					{
						pg->AddItem( i  ) ;
						pg->mType = ObjSem;
					}

				if ( p->GetObjectType() == ObjStop )
					if ( p->GetGroupId() ==  j )  
					{
						pg->AddItem( i  ) ;
						pg->mType = ObjStop;
					}

			}

 //mDebug.CDebugPut("*GRPAdded*: %d Objs: %d ", pg->mType ,  mCntGrpPtr+1 );

			mCntGrpTbl[mCntGrpPtr++] =  pg;
		}

		// add to the table 
		//mCntGrpTbl[mCntGrpPtr++] =  pg;
//mDebug.CDebugPut("*GRPAdded*: %d Objs: %d ", mCntGrpPtr ,  m_NbrOfObj );

	}

//  need to create m_LastGrpId;   or  ????


//  debug !


}

/// [36] CObjRailsColl::ManageSemInControlGroup() 
void CObjRailsColl::ManageSemInControlGroup() 
{
	if ( mCntGrpPtr > 0 )
	{
		for ( int i =0; i < mCntGrpPtr ; i++)
		{
			CControlGroupElement  *pg = mCntGrpTbl[i];
			pg->KickOnElement(); 
		}
	}
 
}


/// [37] CObjRailsColl::FindControlSwitchObject(  int railID , int ep ) 
CObjControls  *CObjRailsColl::FindControlSwitchObject(   int railID , int ep ) 
{
	for ( int i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p = (CObjControls *) mObjTable[i];
			if ( p->GetRailPtrId() == railID )
				if ( p->GetControlEndpoint() == ep )
					return p;
		}
	return NULL;
}
 

/// [40] BOOL CObjRailsColl::FindObjects(   CPoint offset, CRect rc ) 						 
BOOL CObjRailsColl::FindRailObjects(   CPoint offset, CRect rc ) 
{
	BOOL bFound=FALSE;

	Indexes = 0;

	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];
		CRect  AbsRect =  rc;
		AbsRect.OffsetRect( offset); // move the rect coordinates from screen to absolute world coordinates
		BOOL p1 =	AbsRect.PtInRect(  p->m_EndPoints[0] );
		BOOL p2 =	AbsRect.PtInRect(  p->m_EndPoints[1] );
		if (  p1 || p2   )
		 {
				p->Selected = 1;
				bFound=TRUE;
				if ( Indexes < MAXINDEX)  
				{
					if ( p1 )
						EpointIndx[Indexes] = 0;
					else
						EpointIndx[Indexes] = 1;

					Index[Indexes++] =i ;

				}
				else  return bFound;
		 }
	}
	return bFound;
}

/// [41] BOOL CObjRailsColl::FindRailObject(   CPoint offset, CRect rc ) 	

BOOL CObjRailsColl::FindRailObject( CPoint offset, CPoint pt ) 
{
	BOOL bFound=FALSE;
	Indexes = 0;

	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];
		//CPoint AbsPoint = pt + offset ; // move the point coordinates from screen to absolute world coordinates
		CFPoint AbsPoint = CFPoint ( pt + offset ) ;

		CObjBendRail *pb = IsBendObject(  p   );
		if ( pb != NULL )
		{
			if ( IsPointOnTheArch( pb->GetPoint(0) , pb->GetPoint(1) , pb->GetCenterPoint() , AbsPoint ) == 1 )
			{
				p->Selected = 1;
				Index[Indexes++] = i ;
				return TRUE;  // only one object at the time
			}
		}
       if (  IsPointOnTheSegment( p->GetPoint(0) , p->GetPoint(1) , AbsPoint  ) == 1)
		{
			p->Selected = 1;
			Index[Indexes++] = i;
			return TRUE; // only one object at the time
		}
	}
	return bFound;
}

/// [42] CObjRailsColl::FindObjectById(    int Id  ) 						 
CObjRail   *CObjRailsColl::FindObjectById(    int Id ) 
{
    CPoint sp,ep;
	BOOL bFound=FALSE;

	Indexes = 0;
	int i;

	for ( i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];

		if ( p->GetRailId() == Id )
		{
				p->Selected = 1;
				Index[Indexes++] = i ;
				return p;
		}
	}

	return NULL;
}

/// [43] CObjRailsColl::GetClosestRail ( CPoint offset , CPoint ptp , int MaxDistance)	
CObjRail   *CObjRailsColl::GetClosestRail ( CPoint offset , CPoint ptp , int MaxDistance)
{
	CObjRail *pr = NULL;
	CObjBendRail  *pb;
	float ftdist;
 
	CPoint ptRef = ptp + offset ;  // absolute point reference

	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *px  =  mRailTable[ i ] ;
		pb = IsBendObject( px );

		if ( pb == NULL )
		{
			CSegment  mlineseg( px->GetPoint(0) , px->GetPoint(1));  // new
			ftdist = mlineseg.GetDistance( ptRef );
		}
		else
		{
			CArch mArch(  pb->GetCenterPoint() ,  px->GetPoint(0), px->GetPoint(1 )  );
			ftdist = mArch.GetDistance( ptRef );
		}
		if ( ftdist > 0 )  
	    	if( ftdist < MaxDistance )
				pr = px;
	}
	return pr;
}

 
/// [44] CObjRailsColl::GetClosestRailEp ( CPoint offset , CPoint ptp , int MaxDistance , int *ep)
CObjRail   *CObjRailsColl::GetClosestRailEp ( CPoint offset , CPoint ptp , int MaxDistance , int *ep)
{
	CObjRail *pr = NULL;
	float fdist = (float)(MaxDistance + MaxDistance);
	
	CPoint ptRef = ptp + offset ;

	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p  =  mRailTable[ i ] ;

		// if switch ???
		if  ( p->m_Connections[1] != 0 )
		{
			float ftdist = GetDistance( p->GetPoint(0) , ptRef );
			if( ftdist < MaxDistance )
			{
				if ( ftdist < fdist )   //check if this ep has already allocated switch	
					if ( FindControlSwitchObject( p->GetRailId() , 0 ) == NULL )
						{ pr = p;  *ep = 0 ; }
			}
		}

		if  ( p->m_Connections[3] != 0 )
		{
			float ftdist = GetDistance( p->GetPoint(1) , ptRef );
			if( ftdist < MaxDistance )
			{
				if ( ftdist < fdist )	
					if ( FindControlSwitchObject( p->GetRailId() , 1 ) == NULL )
						{ pr = p;  *ep = 1 ; }
			}
		}
	}
	return pr;
}
/// [45] CObjRail *CObjRailsColl::GetByEndPoint( CObjRail *pOld , int endpoint ) 
CObjRail *CObjRailsColl::GetByEndPoint( CObjRail *pOld , int endpoint )  
{
	//int tmpep = endpoint;

	if ( endpoint == 1) endpoint = 2; // tbdopt

	if (( endpoint == 0 ) && ( pOld->GetRailConnId( 1 ) != 0) ) 
		if ( pOld->GetSwitchStatus( 0 ) == STATUS_SET ) endpoint +=1 ;

	if (( endpoint == 2 ) && ( pOld->GetRailConnId( 3 ) != 0)  )
		if ( pOld->GetSwitchStatus( 1 ) == STATUS_SET ) endpoint +=1 ;

	WORD ThisId = pOld->GetRailId();
	WORD cId = pOld->GetRailConnId( endpoint );

 //mDebug.CDebugPut("*GetByEndPoint*:ep:%d [%d] [%d]  ", endpoint , cId ,ThisId );

	CObjRail *p  = GetIndex( cId) ;	
	if (  p != NULL )
		p->SetMode(2, GetOtherEndEp( p ,   ThisId ) )  ;
	return p;
}

/// [47] CObjRailsColl::GetAt( int idx) 
CObjRail  *CObjRailsColl::GetAt( int idx)
{
	return mRailTable[ idx ] ;
}

/// [48] CObjRailsColl::GetRailPtrById( int id )
// dublicate !!!!
CObjRail  *CObjRailsColl::GetRailPtrById( int id )
{
	return GetRailObjPtrByIdIndex( id );
}
 

/// [49] CObjRailsColl::DoIndex()
void CObjRailsColl::DoIndex()
{
	// init index table

((CMainFrame*)(AfxGetApp()->m_pMainWnd))->DisplayPanel(  1 , "Indexing rails table ... "  );

	for ( int i =0; i < MAX_RAILS ; i++)
		TblIndex[i] = 0;

	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];
		TblIndex[p->GetRailId()] = i;
	}

((CMainFrame*)(AfxGetApp()->m_pMainWnd))->DisplayPanel(  1 , "Verifieing rails index ... "  );

	int ierr =0;

	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p1 = mRailTable[i];
		int id  = p1->GetRailId();
		CObjRail *p2 =  mRailTable[TblIndex[id  ]];
		if ( p2->GetRailId() != id  )  ierr +=1;
	}

	if ( ierr == 0 )
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->DisplayPanel(  1 , "Index ok ... "  );
	else{
		CString Cs; Cs.Format(" Index table errors %d ", ierr);
		((CMainFrame*)(AfxGetApp()->m_pMainWnd))->DisplayPanel(  1 , Cs );
	}
}
 
/// [50] CObjRailsColl::GetIndex(int railId )
CObjRail  *CObjRailsColl::GetIndex( int railId ) 
{
	return GetRailObjPtrByIdIndex( railId );
}

/// [50] CObjRailsColl::GetIndex(int railId )
CObjRail  *CObjRailsColl::GetRailObjPtrByIdIndex( int railId ) 
{
	
	if ( railId == 0xFFFF ) return NULL;

	if ( railId >  m_LastRailId )
	{
		mDebug.CDebugPut((char *)"GetRailByIdIndex - FATAL ERRO0  for :%d  ", (int)railId  );
		AfxMessageBox("GetRailByIdIndex FATAL ERROR2 index - stopping application");
	}


	int iptr = TblIndex[railId];
	/*
	if (  iptr == 0 ) // can be zero for rail 1
	{
		mDebug.CDebugPut((char *)"GetRailByIdIndex - FATAL ERROR1  for :%d  ", (int)railId  );
		AfxMessageBox("GetRailByIdIndex - FATAL ERROR1 index - stopping application");
		while( 1);
		return NULL;
	}
	*/
	CObjRail *p = mRailTable[iptr];
	if ( p == NULL )
	{
		mDebug.CDebugPut((char *)"GetRailByIdIndex - FATAL ERROR2  for :%d  ", (int)railId  );
		AfxMessageBox("GetRailByIdIndex FATAL ERROR2 index - stopping application");
		//while( 1);
		return NULL;
	}
	if ( p->GetRailId() != railId )  // give AFx  and stop all simulation
	{
		mDebug.CDebugPut((char *)"GetIndex !OK CurId:%d Param:%d  ", (int)p->GetRailId() , (int)railId  );
		AfxMessageBox("GetRailByIdIndex FATAL ERROR3 index");
	}
	return   p;
}





/// [51] CObjRailsColl::GetRailSelected()
CObjRail *CObjRailsColl::GetRailSelected()
{
	if ( Indexes > 0 )
		{
		CObjRail *p = mRailTable[Index[0]];
		return p;
		}
	return NULL;
}

/// [52] CObjRailsColl::GetNumberOfSelectedObjects()
int  CObjRailsColl::GetNumberOfSelectedObjects()
{
	return Indexes;
}

/// [53] CObjRailsColl::ClearSelected()
BOOL CObjRailsColl::ClearSelected() 
{
	int i;
	BOOL bwas = FALSE;

//mDebug.CDebugPut((char *)"Clear Indexes:%d ", (int)Indexes  );

	for ( i =0; i < Indexes ; i++)
	{
		CObjRail *p = mRailTable[Index[i]];
	//mDebug.CDebugPut((char *)" Clear:%d Was %d ", (int)Index[i] , (int)p->Selected   );

			p->Selected = 0;
			p->Handled = 0; 
			bwas = TRUE;
	}

	Indexes = 0;
	return bwas;
}

/// [54] CObjRailsColl::DrawHandleOnSelected()
void CObjRailsColl::DrawHandleOnSelected()
{
		mDrawHandle = TRUE;  // po co?

		int i;
		for ( i =0; i < Indexes ; i++)
			{
			 CObjRail *p = mRailTable[Index[i]];
			 if ( p->Selected == 1)  p->Handled = 1; 
			}
}
/// [55] CObjRailsColl::GetSelectedObjectRect(CPoint offset, int mode)
CRect CObjRailsColl::GetSelectedObjectRect(CPoint offset, int mode)
{
	CRect rc (0,0,0,0);
	CRect rcu (0,0,0,0);
	DRAWDATASTRUCT mData;
	mData.Width = 2;
	int ifirst=0;
	

	int i;
	for ( i =0; i < Indexes ; i++)
		{
			CObjRail *p = mRailTable[Index[i]];
	 
			if (( p->mObjType ==  ObjBendRightRail) || ( p->mObjType ==  ObjBendLeftRail)) 
			{
				CObjBendRail* pp = (CObjBendRail*)p;

				mData.StartPoint =  OffsetFPoint (  pp->m_EndPoints[0] , offset );
 				mData.EndPoint	=  OffsetFPoint (	pp->m_EndPoints[1] , offset );
 				mData.CenterPoint =  OffsetFPoint ( pp->mCenterPoint , offset );
				mData.Radius = GetDistance (mData.StartPoint,mData.CenterPoint);
				ComputeBandingRectBend( &mData );
				
				if ( ifirst == 0 )
				{
					rc = mData.mUpdRect;
					ifirst =1 ;
					rcu = rc;
				}
				else
				{
					rc.UnionRect( mData.mUpdRect , rcu );
					rcu = rc;
				}

			}
			else
			{
				mData.StartPoint =  OffsetFPoint ( p->m_EndPoints[0] , offset );
 				mData.EndPoint =  OffsetFPoint ( p->m_EndPoints[1] , offset );
				ComputeBandingRectStright( &mData );

				if ( ifirst == 0 )
				{
					rc = mData.mUpdRect;
					ifirst =1 ;
					rcu = rc;
				}
				else
				{
					rc.UnionRect( mData.mUpdRect , rcu );
					rcu = rc;
				}
			}

		}

	return rc;
}

 
/// [60] CObjRailsColl::HitBendHandle( CPoint offset, CPoint point ) 
BOOL CObjRailsColl::HitBendHandle( CPoint offset, CPoint point ) 
{
	CObjBendRail *p = (CObjBendRail * )mRailTable[Index[0]];
	CFPoint cp( p->mCenterPoint.x - offset.x , p->mCenterPoint.y -  offset.y) ;
	if ( GetDistance ( point , cp ) < 4)  return TRUE;
	return FALSE;
}
/// [61] CObjRailsColl::ModifyBendObject( CPoint offset, CPoint point ) 
BOOL CObjRailsColl::ModifyBendObject( CPoint offset, CPoint point ) 
{
	CPoint sp,ep ;

	CObjBendRail *p = (CObjBendRail * )mRailTable[Index[0]];

	sp =  OffsetFPoint ( p->m_EndPoints[0] , offset );
 	ep =  OffsetFPoint ( p->m_EndPoints[1] , offset );

	CFPoint cp( p->mCenterPoint.x - offset.x , p->mCenterPoint.y -  offset.y) ;

    CFPoint middle  = GetCenterPoint( sp  ,  ep );
	CLineObject  mLine( sp  ,  ep  );
	CLineObject  mLinePerp( mLine.GetA() , mLine.GetB() , middle );
	CLineObject  mLinePerp2( mLinePerp.GetA() , mLinePerp.GetB() , point );
	
	CFPoint  cp1 = mLinePerp2.GetCrossWithLine( mLinePerp );

	p->mCenterPoint.x  = cp1.x + offset.x ;
	p->mCenterPoint.y =  cp1.y + offset.y ;

	return TRUE;
}

/// [62] CObjRailsColl::IsSingleBendRailSelected()
BOOL CObjRailsColl::IsSingleBendRailSelected()
{
	if ( Indexes == 1 )
		{
			 CObjRail *p = mRailTable[Index[0]];
			 if ( p->Selected == 1)
			 {
				 if (( p->mObjType ==  ObjBendRightRail) || ( p->mObjType ==  ObjBendLeftRail))  return TRUE;
				 else return FALSE;
			 }
		}
	return FALSE;
}

 
/// [70] CObjRailsColl::SnapSelectedObjects()  
BOOL CObjRailsColl::SnapSelectedObjects()  
{
	if ( Indexes != 2 ) return FALSE;

	CObjRail *p1 = mRailTable[Index[0]];
	CObjRail *p2 = mRailTable[Index[1]];

	int ob1=0,ob2=0;

	if (( p1->mObjType ==  ObjBendRightRail) || ( p1->mObjType ==  ObjBendLeftRail)) ob1 = 1;
	if (( p2->mObjType ==  ObjBendRightRail) || ( p2->mObjType ==  ObjBendLeftRail)) ob2 = 1;

	if ( (ob1+ob2) == 2 ) return FALSE;
 	 
	int ip1 = EpointIndx[0];
	int ip2 = EpointIndx[1];


 //mDebug.CDebugPut((char *)">SnapSelectedObjects> ip: %d %d    ", ip1 , ip2 );

	int ic1 = ip1 << 1;
	int ic2 = ip2 << 1;
 


 	if ( (ob1+ob2) == 0 )
	{
		p2->m_EndPoints[ip2] = p1->m_EndPoints[ip1];

		p2->m_Connections[ic2]  = p1->GetRailId();
		p1->m_Connections[ic1 ] = p2->GetRailId();

		return TRUE;
	}

	if ( ob1 == 0 )
	{
		p1->m_EndPoints[ip1] = p2->m_EndPoints[ip2];
		p2->m_Connections[ic2]  = p1->GetRailId();
		p1->m_Connections[ic1 ] = p2->GetRailId();
	}
	else
	{
		p2->m_EndPoints[ip2] = p1->m_EndPoints[ip1];
		p2->m_Connections[ic2]  = p1->GetRailId();
		p1->m_Connections[ic1 ] = p2->GetRailId();
	}
	return TRUE;
}
/// [71] CObjRailsColl::Detach( WORD mcID ) 
void CObjRailsColl::Detach( WORD mcID ) 
{
	int i;
	for ( i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];
		if ( p->m_Connections[0] == mcID ) p->m_Connections[0] = 0;
		if ( p->m_Connections[1] == mcID ) p->m_Connections[1] = 0;	
		if ( p->m_Connections[2] == mcID ) p->m_Connections[2] = 0;
		if ( p->m_Connections[3] == mcID ) p->m_Connections[3] = 0;
	} 
}
 
  
/// [74] CObjRailsColl::AutoSnap(CObjRail *p)
///   check wheter any of the existing rails has close one of their endpoint
///
///  new algo  - only adjust  point  to exiting let the rest be done by checkswitches

void CObjRailsColl::AutoSnap(CObjRail *p)
{
	int i; CObjRail *px;
	int ep = -1;

	for ( i =0;i < m_NbrOfRails-1  ; i++)  // N-1 since last p is beiing added
	{
		px = mRailTable[i];

		if ( GetDistance( px->m_EndPoints[0] , p->m_EndPoints[0] ) < 4 )
		{  // check new 0 ep with any of existing 0
			p->SetPoint( 0 , px->GetPPoint(0) );
			ep = 0;  
		}

		if ( GetDistance( px->m_EndPoints[1] , p->m_EndPoints[0] ) < 4 )
		{  // check new 0 ep with any of existing 1
			p->SetPoint( 0 , px->GetPPoint(1) );
			ep = 0;  
		}

		if ( GetDistance( px->m_EndPoints[0] , p->m_EndPoints[1] ) < 4 )
		{  // check new 1 ep with any of existing 0
			p->SetPoint( 1 , px->GetPPoint(0) );
			ep = 1;  
		}

		if ( GetDistance( px->m_EndPoints[1] , p->m_EndPoints[1] ) < 4 )
		{   // check new 1 ep with any of existing 1
			p->SetPoint( 1 , px->GetPPoint(1) );
			ep = 1;  
		}
	}

	
	if ( ep >= 0 )
	{    

		//CheckThisEP( ep , p  , 1 ) ;  
		 CheckSwitchesDetails(1);

		CObjBendRail *pb = IsBendObject( p  );
		if ( pb != NULL )  // if this is the bend adjust center point
		{
			CFPoint newCp =  AdjustBendCenterPoint(  p->GetPPoint(0) , p->GetPPoint(1) ,pb->GetCenterPoint() );
			if ( GetDistance (newCp , pb->GetCenterPoint() ) < 3 ) pb->SetCenterPoint(newCp );
			else
			{
			mDebug.CDebugPut((char *)"Adjust bend Er: old=(%6.2f,%6.2f)",pb->GetCenterPoint().x , pb->GetCenterPoint().y );
			mDebug.CDebugPut((char *)"Adjust bend Er: new=(%6.2f,%6.2f)",newCp.x , newCp.y);
			}

		}

	}
}


/// [75] CObjRailsColl::Serialize(CArchive& ar)
void CObjRailsColl::Serialize(CArchive& ar)
{
	int i;
	CString CVersion;


	if (ar.IsStoring())
	{
       ar <<  (int) m_NbrOfRails;
	   ar <<  (int) m_LastRailId;
	   for ( i =0; i < m_NbrOfRails ; i++)
		{
			CObjRail *p = mRailTable[i];
			ar << p->mObjType;
			p->Serialize( ar);
		}

	   CVersion=_T("OBJ");
       ar << CVersion;

       ar <<  (int) m_NbrOfObj;
	   ar <<  (int) m_LastObjId;
	   for ( i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p = (CObjControls*)mObjTable[i];
			//ar << p->mObjType;
			p->Serialize( ar);
		}


	   CVersion=_T("TRN");
       ar << CVersion;

	   if ( mSystem.m_SaveTrams == FALSE )
	   {
			ar <<  (int) 0;
			ar <<  (int) 0;
	   }
	   else
	   {

//mDebug.CDebugPut("* Serialize*:Store  %d %d  ",  m_NbrOfTrams ,m_LastTramId );

			ar <<  (int) m_NbrOfTrams;
			ar <<  (int) m_LastTramId;
			for ( i =0; i < m_NbrOfTrams ; i++)
			{
			CTramTrainVagons *p = (CTramTrainVagons*)mTramTable[i];
			//ar << p->mObjType;
			p->Serialize( ar);
			// added to prevent stopping failure
			//p->ReInitializeObject();
			}
	   }

	   ar << m_LastGrpId;

	   CVersion=_T("END");
       ar << CVersion;

	}
	else
	{
		ar >>  (int) m_NbrOfRails;
		ar >>  (int) m_LastRailId;
	    for ( i =0; i < m_NbrOfRails ; i++)
		{
			int ot;
			ar >> ot;
			if (( ot ==  ObjStraightRail ) || ( ot ==  ObjRailEnd ))
			{
				CObjRail *p;
				p = new  CObjRail();
				mRailTable[i] = p;
				p->SetObjectType( ot );
				p->Serialize( ar);
			}
			if (( ot ==  ObjBendRightRail) || ( ot ==  ObjBendLeftRail))
			{
				CObjBendRail *p;
				p = new  CObjBendRail();
				mRailTable[i] = p;
				p->SetObjectType( ot );
				p->Serialize( ar);
			}
		}


		DoIndex();

		ar >> CVersion;

		ar >>  (int) m_NbrOfObj;
		ar >>  (int) m_LastObjId;
	    for ( i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p = new CObjControls();
			mObjTable[i] = p;
			p->Serialize( ar);
			// get actual pointer to rail object
			int err=1;
			for ( int j =0; j < m_NbrOfRails ; j++)
			{
				CObjRail *pr = mRailTable[j];
				if ( pr->GetRailId() == p->GetRailPtrId() )
				{
					p->SetRailObjectPtr( pr);
					err =0;
					break;
				}
			}

			if ( err == 1)
			{
				 p->SetRailObjectPtr( NULL );
				mDebug.CDebugPut((char *)"Error 1 finding rail pointer: %d ", p->GetRailPtrId());	
				//break;
			}
			// error here
		}

 
	 //	return;
 
       ar >> CVersion;
       ar >>  (int) m_NbrOfTrams;
	   ar >>  (int) m_LastTramId;

 //mDebug.CDebugPut("* Serialize*:Restore  %d %d  ",  m_NbrOfTrams ,m_LastTramId );


	   int tmpId =1;

	   for ( i =0; i < m_NbrOfTrams ; i++)
		{
			CTramTrainVagons *p = new CTramTrainVagons();
			mTramTable[i] = p;

			p->SetTramId(tmpId );
			tmpId +=1;

			p->Serialize( ar);

			for ( int node =0; node < p->GetNumberOfNodes() ; node++)
			{

				int err=1;
				for ( int j =0; j < m_NbrOfRails ; j++)
				{
					CObjRail *pr = mRailTable[j];
					if ( pr->GetRailId() == p->GetRailPtrId( node ) )
					{
						p->SetRailObjectPtr( node , pr);
						err =0;
						break;
					}
				}

				if ( err == 1)
				{
				mDebug.CDebugPut((char *)"Error 2 finding rail pointer 2");	
				return ;
				}
			}
		}

	    ar >> m_LastGrpId;
	    ar >> CVersion;

		 
		CreateControlGroupTbl();
	  

	  	 //FixSwitch();


	}
}


/// [80] CObjRailsColl::DisplaySelected()  
void CObjRailsColl::DisplaySelected() 
{
	int i;
	mDebug.CDebugPut((char *)"-------------SELECTED-----------");
	for ( i =0; i < Indexes ; i++)
	{
		CObjRail *p = mRailTable[Index[i]];
		if ( p->Selected == 1)
			{
			mDebug.CDebugPut((char *)">>>>> Id:%d  ", (int)p->GetRailId()  );
			mDebug.CDebugPut((char *)"Conn:[%d][%d] [%d][%d]  ", (int)p->m_Connections[0],(int)p->m_Connections[1],(int)p->m_Connections[2], (int)p->m_Connections[3]  );
			mDebug.CDebugPut((char *)"Epoints:(%d,%d) (%d,%d)  ", (int)p->m_EndPoints[0].x,(int)p->m_EndPoints[0].y,(int)p->m_EndPoints[1].x, (int)p->m_EndPoints[1].y );
			mDebug.CDebugPut((char *)"-----------------------------------------");
			}
	}
	mDebug.CDebugPut((char *)"----------End of list-----------");
}
/// [81] CObjRailsColl::DrawMyObject( CPoint offset, HDC hdc , CRect rc)  
void CObjRailsColl::DrawMyObject( CPoint offset, HDC hdc , CRect rc) 
{
	int i =0;

	for ( i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];
		p->DrawMyObject(   offset , hdc , rc );
	}
}
/// [82] CObjRailsColl::DrawMyObjects(  CPoint offset, HDC hdc , CRect rc) 
void CObjRailsColl::DrawMyObjects(  CPoint offset, HDC hdc , CRect rc)  
{
	int i =0;

	for ( i =0; i < m_NbrOfObj ; i++)
	{
		CMyObject *p = mObjTable[i];
		p->DrawMyObject(   offset , hdc , rc );
	}
}
 
/// [83] CObjRailsColl::DebugRailList()

void CObjRailsColl::DebugRailList()
{
   int i;
 	mDebug.CDebugPut((char *)"---------Rail objects list --------");
   for ( i=0;i<m_NbrOfRails;i++)
	   {
		CObjRail *p = mRailTable[i];
	    mDebug.CDebugPut((char *)">>>>>  Object :Id:%d Type:%d ", (int)p->GetRailId() ,(int)p->mObjType );
		mDebug.CDebugPut((char *)"Cn:[%d][%d] [%d][%d]  ", (int)p->m_Connections[0],(int)p->m_Connections[1],(int)p->m_Connections[2], (int)p->m_Connections[3]  );
		mDebug.CDebugPut((char *)"Ep:(%d,%d) (%d,%d)  ", (int)p->m_EndPoints[0].x,(int)p->m_EndPoints[0].y,(int)p->m_EndPoints[1].x, (int)p->m_EndPoints[1].y );
		if (( p->mObjType == ObjBendRightRail ) ||  ( p->mObjType ==ObjBendLeftRail))
		{
			CObjBendRail  *pb = (CObjBendRail *)p;
			mDebug.CDebugPut((char *)"Center:(%d,%d)", (int)pb->mCenterPoint.x, (int)pb->mCenterPoint.y  );
		}

	   }
	mDebug.CDebugPut((char *)"-----------------------------------------");

	mDebug.CDebugPut((char *)"---------Control objects list --------");
	for ( i=0;i<m_NbrOfObj;i++)
	   {
			CObjControls *p = (CObjControls*)mObjTable[i];
			mDebug.CDebugPut((char *)"+++++  Control :Id:%d Type:%d Rail Id:%04d Status:%d ", (int)p->GetControlID() ,(int)p->GetObjectType(),(int)p->GetRailPtrId(),(int)p->GetStatus() );
			mDebug.CDebugPut((char *)"Point: (%d,%d)  ", p->GetRailControlPoint().x , p->GetRailControlPoint().y );
		}

	mDebug.CDebugPut((char *)"-----------------------------------------");

	mDebug.CDebugPut((char *)"---------Trams objects list --------");
	for ( i=0;i<m_NbrOfTrams;i++)
	   {
			CTramTrainVagons *p = (CTramTrainVagons*)mTramTable[i];
			mDebug.CDebugPut((char *)"+++++  Control :Id:%d   ", (int)p->GetTramId()  );
			//mDebug.CDebugPut((char *)"Point: (%d,%d)  ", p->GetControlPoint().x , p->GetControlPoint().y );
		}

	mDebug.CDebugPut((char *)"-----------------------------------------");

 

}

/// [84] CObjRailsColl::Resources()
void CObjRailsColl::Resources() 
{
	mDebug.CDebugPut((char *)"---------Resources usage --------");
	mDebug.CDebugPut((char *)"Rails objects LastId:%d MaxIds:%d Count:%d", (int)m_LastRailId ,(int)MAX_RAILS,(int)m_NbrOfRails );
	mDebug.CDebugPut((char *)"Control objects LastId:%d MaxIds:%d Count:%d", (int)m_LastObjId ,(int)MAX_OBJS,(int)m_NbrOfObj );
	mDebug.CDebugPut((char *)"Train objects LastId:%d MaxIds:%d Count:%d", (int)m_LastTramId ,(int)MAX_TRAMS,(int)m_NbrOfTrams );
	mDebug.CDebugPut((char *)"Group objects LastId:%d MaxIds:%d Count:%d", (int)mCntGrpPtr ,(int)MAX_CNTGRP,(int)mCntGrpPtr );
	mDebug.CDebugPut((char *)"---------Resources usage end ------");	 
}
 
 
/// [90] CObjRailsColl::CheckSwitchesDetails(int mode)
int CObjRailsColl::CheckSwitchesDetails(int mode)
{
	int ErrCnt=0;
//mDebug.CDebugPut("*CheckSwitchesDetails starts*"  );  

   for (int  i =0; i < m_NbrOfRails ; i++)
		{
			CObjRail *p = mRailTable[i];
		//	if ( p->GetObjectType() == ObjRailEnd ) continue;
			if ( CheckThisEP( 0 , p  ,mode  ) > 0 ) ErrCnt +=1;
			if ( CheckThisEP( 1 , p  ,mode  ) > 0 ) ErrCnt +=1;
		}

//mDebug.CDebugPut("*CheckSwitchesDetails Done...*"  );  
   return ErrCnt;
}	

/// [91] CObjRailsColl::CheckThisEP(int ep, CObjRail *p , int mode) 
/// private function
int CObjRailsColl::CheckThisEP( int ep, CObjRail *p , int mode)
{
	int tId = p->GetRailId();  // this rail Id
	CFPoint tPt = p->GetPoint( ep ) ;
	int nr = 0;
	CObjRail *prt[4];
	int ept[4];

   for (int  i =0; i < m_NbrOfRails ; i++)
		{
			CObjRail *px = mRailTable[i];
			if ( tId == px->GetRailId()) continue ; // this rail
			// check physical connection 
			if (  GetDistance(  tPt ,  px->GetPoint(0)   ) <  1.2 )  
				{
					ept[nr] = 0;
					prt[nr++]  =  px;
					if ( nr > 3 ) break;
					continue;
				}
			// check physical connection 
			if (  GetDistance(  tPt ,  px->GetPoint(1)   ) <  1.2 )  
				{
					ept[nr] = 1;
					prt[nr++]  =  px;
					if ( nr > 3 ) break;
				}
		}

   return CheckPhysicalConnection(    nr ,  ep,  p ,  prt  ,  ept    ,   mode);
}



/// [92] CObjRailsColl::CheckStops(int mode)
int CObjRailsColl::CheckStops(int mode)
{
	int ErrCnt=0;
 
	for (int  i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p  =  (CObjControls *)mObjTable[i];
			if ( p->GetObjectType() ==   ObjStop )
			{
				CObjRail *px =  GetRailObjPtrByIdIndex( p->GetRailPtrId() );
				if ( px != NULL )
					{
						CMyPoint  mp( (float)p->GetRailControlPoint().x , (float)p->GetRailControlPoint().y);	
						int igetd = GetDistanceOfPointFromRail(  px , mp );
 
						if ( igetd != 0 )
							{
								mDebug.CDebugPut((char *)"Invalid point on Stop object control %d error:%d railId=%d", p->GetControlID(),  igetd , px->GetRailId() );
								ErrCnt +=1;
								//continue;
							}
					}
				else
					{
						mDebug.CDebugPut((char *)"Invalid control stop:%d ", p->GetControlID() );
						ErrCnt +=1;
					}
			}
		}
   return ErrCnt;
}	


/// [93] int CObjRailsColl::CheckSemaphores(int mode)
int CObjRailsColl::CheckSemaphores(int mode)
{
	int ErrCnt=0;
 
	for (int  i =0; i < m_NbrOfObj ; i++)
		{
			CObjControls *p  =  (CObjControls *)mObjTable[i];
			if ( p->GetObjectType() ==   ObjSem )
			{
				CObjRail *px =  GetRailObjPtrByIdIndex( p->GetRailPtrId() );
				if ( px != NULL )
					{
						CMyPoint  mp( (float)p->GetRailControlPoint().x , (float)p->GetRailControlPoint().y);	
						int igetd = GetDistanceOfPointFromRail(  px , mp );
						if ( igetd != 0 )
							{
								mDebug.CDebugPut((char *)"Invalid point on sem object control %d error:%d railId=%d", p->GetControlID(), igetd , px->GetRailId() );
								ErrCnt +=1;
								//continue;
							}

					}
				else
					{
						mDebug.CDebugPut((char *)"Invalid control sem:%d ", p->GetControlID() );
						ErrCnt +=1;
					}
			}
		}
   return ErrCnt;
}
	 
/// [94] int CObjRailsColl::CheckIndexTable()					 
int CObjRailsColl::CheckIndexTable( ) 
{
	int  nErrors = 0;
	for ( int i =0; i < m_NbrOfRails ; i++)
	{
		CObjRail *p = mRailTable[i];
		int id = p->GetRailId();

		nErrors = nErrors + CheckIndexTableId(  id , id ); 
		 
		for ( int j =0 ; j < 4; j++)
		{
			int cid = p->GetRailConnId( j);
			if ( cid > 0 )
				nErrors = nErrors + CheckIndexTableId( id , cid ); 
		}
		 
	}
	return nErrors;
}

/// [95] int CObjRailsColl::CheckIndexTableId()	
int CObjRailsColl::CheckIndexTableId( int mid ,int  id ) 
{

	if (   id  >= MAX_RAILS )  // can be endof terminator
	{
		//mDebug.CDebugPut((char *)"GetIndex ID  CurId:%d   ", (int)id   );
		return 1;
	}

    if ( TblIndex[id] != 0 )	
		{
			CObjRail *p1 = mRailTable[TblIndex[id]];
			if ( p1 != NULL )
			{
				if ( id != p1->GetRailId() )
					{
mDebug.CDebugPut((char *)"GetIndex ID do not match Rid:%d CurId:%d FeedbackId:%d  ", mid , (int)id , (int)p1->GetRailId() );
						return 1;
					}
			}
			else
			{
mDebug.CDebugPut((char *)"GetIndex NULL Pointer:Rid:%d CurId:%d   " , mid , (int)id );
				return 1;
			}
		}
		else
		{
			if ( (mid != 1  ) & (id != 0 ))
			{
				mDebug.CDebugPut((char *)"GetIndex NULL index :Rid:%d CurId:%d   ", mid , (int)id );
			    return 1;
			}
		}

	return 0;
}


 
/// [100] BOOL CObjRailsColl::AddObjectTram( CTramModelDef *ptm , int nodes) 
BOOL CObjRailsColl::AddObjectTram( CTramModelDef *ptm , int nodes , int routeId ) 
{
	//  first rail is the launch pad for tram
	if ( m_NbrOfRails == 0 ) return FALSE;

	CObjRail   *p  =  mCObjRailsColl.GetAt( 0);
	
   for ( int i=0;i<m_NbrOfRails;i++)
	   {
		CObjRail *px = mRailTable[i];
		if ( px->GetRailId() == mSystem.m_LaunchRail )	{ p =px; break;}
		}

	//mLaunchId

	//CFPoint pm = GetCenterPoint(  p->GetPoint(0) ,  p->GetPoint(1) );
	//pm = GetCenterPoint(  p->GetPoint(0) ,  pm );

	CFPoint pm =   GetPointFmStart(  p->GetPoint(0) ,  p->GetPoint(1) , GetDistance(p->GetPoint(0) ,  p->GetPoint(1)) -40);

	
	CTramTrainVagons *pv;

	pv = new CTramTrainVagons( pm  , p  ) ;
	pv->CreateVagons(  ptm ,nodes );
	pv->SetLineId( routeId );


	mTramTable[ m_NbrOfTrams] =pv;
	m_NbrOfTrams+=1;
	m_LastTramId =m_NbrOfTrams ;

	pv->SetTramId(m_LastTramId );

	// mDebug.CDebugPut(" Get idd  %d " , pv->GetTramId() );

	return TRUE;
}

/// [101] BOOL CObjRailsColl::FindTrainObject(  CPoint offset, CPoint pt ) 

CTramTrainVagons *CObjRailsColl::FindTrainObject(   CPoint offset, CPoint pt ) 
{
	for ( int i =0; i < m_NbrOfTrams ; i++)
	{
		CTramTrainVagons *pv = mTramTable[i];
		// global coordinates for train
		CPoint rpoint =   offset + pt; 
		// create Train rect  - betwean end and begonning of the first vagon
		CRect rc ( (int)pv->GetNodePoint( 0 ).x , (int)pv->GetNodePoint( 0 ).y , (int)pv->GetNodePoint( 1).x ,(int) pv->GetNodePoint( 1 ).y );
		rc.NormalizeRect();
		rc.InflateRect( 6,6,6,6);

		if ( rc.PtInRect(  rpoint ) == TRUE )
				return pv;
	}
	return NULL;
}


/// [101] CObjRailsColl::MoveTrams(float steps)
void CObjRailsColl::MoveTrams(float steps)
{
	CTramTrainVagons *pv;

	 ManageSemInControlGroup() ;

	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		pv = mTramTable[i];
		pv->MoveObject( steps);
	}
}
/// [102] CObjRailsColl::GetTramId( int i )
int CObjRailsColl::GetTramId( int i )
{
	if ( i > m_NbrOfTrams ) return -1;

	CTramTrainVagons *pv;
	pv = mTramTable[i];
	return pv->GetTramId(); 
}

/// [103] CObjRailsColl::StartTrams() 
void CObjRailsColl::StartTrams() 
{
	CTramTrainVagons *pv;

	 InitControlObjects ();

	DoIndex();

	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		pv = mTramTable[i];
		pv->ReInitializeObject();
	}
}
/// [104] CObjRailsColl::StopTrams() 
void CObjRailsColl::StopTrams() 
{

}

/// [105] CObjRailsColl::ReversTramsDir() 
void CObjRailsColl::ReversTramsDir() 
{
	CTramTrainVagons *pv;

	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		pv = mTramTable[i];
		pv->ChangeMoveObjectDir();
	}
}

/// [106] CObjRailsColl::ReversTramsDir() 
void CObjRailsColl::DrawTrams(  CPoint offset, HDC hdc , CRect rc)
{
	CTramTrainVagons *pv;
	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		pv = mTramTable[i];
		CMyPoint  Spt =  OffsetFPoint ( pv->GetStartPoint() , offset );
		CMyPoint  Ept = OffsetFPoint ( pv->GetEndPoint() , offset );
		if (   ( rc.PtInRect( Spt ) ) ||  ( rc.PtInRect( Ept ) )  )
			pv->DrawObject( hdc ,   offset );
	}
}

////////////////////////////////////////////////////////////////
/// [107] CObjRailsColl::CheckIfTheEpIsMerging(CObjRail *p  , int endpoint , int *tbls2 )
 
BOOL CObjRailsColl::CheckIfTheEpIsMerging( CObjRail *p  , int endpoint , int *tbls2 )
{ 
	int ep = endpoint << 1;  //  0  or 2  EP to check
	int idnx = p->GetRailConnId( ep  );  // maybe we can pas in the table 
	if ( idnx ==  0)
		{
			mDebug.CDebugPut("*CheckIfTheEpIsMerging* ERROR1 {idnx=%d} ", idnx );
			return FALSE; // this might be the error
		}
	// get quicky the idexed pointer
	CObjRail *pnx =  GetIndex( idnx ) ;
	if ( pnx == NULL ) 
		{
			//mDebug.CDebugPut("*CheckIfTheEpIsMerging* ERROR2 {idnx=%d} ", idnx );
			return FALSE;  // dbase error
		}
	if ( pnx->GetRailId() != idnx ) 
		{
			mDebug.CDebugPut("*CheckIfTheEpIsMerging* ERROR3 {idnx=%d} [%d]", idnx , pnx->GetRailId() );
			return FALSE;  // dbase error
		}
	int ThisId = p->GetRailId();
	int oep = GetOtherEndEp(  pnx  ,  ThisId );
	if ( oep < 0 ) 
		{
			mDebug.CDebugPut("*CheckIfTheEpIsMerging* ERROR4 {ThisId=%d} oep=%d  ", ThisId, oep );	
			return FALSE;  // dbase error
		}

	if ( CheckIfTheEpIsSwitch(  pnx  ,oep ) == FALSE ) return FALSE;
	// now we know it is merging point - must return both epsID

	tbls2[0] = idnx;		// directly connected next rail
	tbls2[2] = oep;
	tbls2[1] = 0;			// merging rail
	int epm = oep << 1;		//

	if ( pnx->GetRailConnId( epm)  == ThisId ) 
		{
			tbls2[1] = pnx->GetRailConnId( epm +1) ;
		}
	if ( pnx->GetRailConnId( epm + 1)  == ThisId ) 
		{
			tbls2[1] = pnx->GetRailConnId( epm ) ;  
		}

	if ( tbls2[1] == 0 ) 
		{
			mDebug.CDebugPut("*CheckIfTheEpIsMerging* ERROR5 {oep=%d}  ", oep );			
			return FALSE;
		}

	CObjRail *pop =  GetIndex( tbls2[1] ) ;
	if ( pop == NULL ) return FALSE;

	tbls2[3] = GetOtherEndEp(  pop  ,  idnx );

	if ( tbls2[3] < 0 ) 
		{
			mDebug.CDebugPut("*CheckIfTheEpIsMerging* ERROR6 {oep=%d}  ", tbls2[1] );			
			return FALSE;
		}
//mDebug.CDebugPut("*CheckIfTheEpIsMerging* (0):%d (1):%d (2):%d (3):%d ", tbls2[0], tbls2[1],tbls2[2],tbls2[3] );	
	return TRUE;
}


//mDebug.CDebugPut("* i on the bend* [%d]  {%d} ? {%d} ",pv->GetTramId(), tbls2[0], pv->GetRailPtrId2(i ) );
/// [108] BOOL CObjRailsColl::CheckIfGivenTramInCloseDistance(CTramTrainVagons *p , int *tbls2 )   

BOOL CObjRailsColl::CheckIfGivenTramInCloseDistance ( CTramTrainVagons *pv , int *tbls2 )  
{
	CObjRail *pnx =  GetIndex( tbls2[0] ) ; // next rail
	if ( pnx == NULL ) return FALSE;
	CObjRail *pmr =  GetIndex( tbls2[1] ) ; // merge line
	if ( pmr == NULL ) return FALSE;

	int nodes = pv->GetNumberOfNodes();

	// check next rail
	CObjBendRail *pb = IsBendObject( pnx  );
	if ( pb != NULL )
	{ // on the bend
		for ( int i = 0; i < nodes ; i++ )
		{
			// is node at the segment
			if ( tbls2[0] ==  pv->GetRailPtrId2( i ) ) // the node on the same rail
				if ( GetDistance(  pb   , tbls2[2]  ,  pv->GetNodePoint(i)  )  < MIN_EP_DISTANCE )  
					return TRUE ;  // we have potential collision
		}
	}
	else
	{ // just stright
		for ( int i = 0; i < nodes ; i++ )
		{	// is node at the segment
			if ( tbls2[0] ==  pv->GetRailPtrId2( i ) ) // the node on the same rail
				if ( GetDistance(  pnx->GetPoint( tbls2[2] ) , pv->GetNodePoint(i) ) < MIN_EP_DISTANCE )  
					return TRUE ; // we have potential collision
		}
	}

	// same with merging line

	pb = IsBendObject( pmr  );
	if ( pb != NULL )
	{ // on the bend
		for ( int i = 0; i < nodes ; i++ )
		{// is node at the segment
			if ( tbls2[1] ==  pv->GetRailPtrId2( i ) ) // the node on the same rail
				if ( GetDistance(  pb   , tbls2[3]  ,  pv->GetNodePoint(i)  )  < MIN_EP_DISTANCE ) 
					return TRUE ; // we have potential collision
		}
	}
	else
	{ // just stright
		for (int i = 0; i < nodes ; i++ )
		{// is node at the segment
			if ( tbls2[1] ==  pv->GetRailPtrId2( i ) ) // the node on the same rail
				if ( GetDistance(  pmr->GetPoint( tbls2[3] )  ,  pv->GetNodePoint(i)  )  < MIN_EP_DISTANCE )  
					return TRUE ; // we have potential collision
		}
	}
	return FALSE;
}

/// [109] BOOL CObjRailsColl::CheckColissionOfThisTrain(CTramTrainVagons *p ) 
// need to be on the same or neigbouring track
 
BOOL  CObjRailsColl::CheckColissionOfThisTrain( CTramTrainVagons *p  )
{
	CTramTrainVagons *pv;
	int theId = p->GetTramId();
	CFPoint p1 = p->GetHeadPoint();
	CObjRail *pr =  p->GetHeadRailObjPtr();
	int theRailId = pr->GetRailId();
	
	//int myep;
	int mskip = 0;  // as default
	int tabId[4];  // returns the merged and connected rails if merged

	int	epdis  = p->GetDistanceOfTheHeadToEp();

// mDebug.CDebugPut("*CheckColission* Distance {%d}  ", epdis );

	if ( epdis < MIN_EP_DISTANCE )
		{
			int myep = p->GetHeadPointEpDir() ;   

//mDebug.CDebugPut("*CheckColission* myep {%d}  ", myep );	

			// check switch and skip if the ep is switch
			if ( CheckIfTheEpIsSwitch( pr , myep ) == TRUE ) mskip = 1; 
			// check merging point of the current ep and skip if not

//mDebug.CDebugPut("*CheckColission* NOT SWI myep {%d}  ", myep );	


			if ( CheckIfTheEpIsMerging( pr , myep , tabId ) == FALSE ) mskip = 1; 
	// 	else
 //mDebug.CDebugPut("*YESIsMerging* (0):%d (1):%d (2):%d (3):%d ", tabId[0], tabId[1],tabId[2],tabId[3] );	

			//  go on with check
		}
	else mskip = 1;

	for ( int i=0;i<m_NbrOfTrams;i++)
	{
		pv = mTramTable[i];
	 	if ( pv->GetTramId() == theId ) continue;

		CObjRail *pvr  =  pv->GetTailRailObjPtr();
 
		//  check each tram to be in the merging distance
		if ( mskip == 0 )
		{  // int tabId[2];

  //mDebug.CDebugPut("*CheckColission222* Distance {%d} ThisTram:%d Other:%d", epdis,theId, pv->GetTramId()  );

			if  ( CheckIfGivenTramInCloseDistance ( pv , tabId ) == TRUE )
			{
	// mDebug.CDebugPut("*YES !!!! coliding* (0):%d (1):%d (2):%d (3):%d ", tabId[0], tabId[1],tabId[2],tabId[3] );	
		 
				if ( pv->IsTramsInMotion()  == TRUE )
				   return TRUE; // must stop this tram
			}
		}

		int eRailId = pvr->GetRailId() ;
		if ( theRailId != eRailId ) continue ;  // we are not on the same rail 
		CFPoint p2 = pv->GetTailPoint();
		if ( GetDistance( p1,p2) < 20 ) return TRUE ;
	}
	return FALSE;
}