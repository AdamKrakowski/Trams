// SemControl.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "SemControl.h"
#include "afxdialogex.h"

 
// CSwitchControl dialog

#include "TrainWorldDoc.h"
#include "TrainWorldView.h"
 
#include "Debug.h"
extern CDebug mDebug;

extern CDebugGraphics mCDebugGraphics;
extern CObjRailsColl  mCObjRailsColl;


// CSemControl dialog

IMPLEMENT_DYNAMIC(CSemControl, CDialogEx)

CSemControl::CSemControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSemControl::IDD, pParent)
	, m_edit_timeout(0)
{
		m_pParent = pParent;
		
	MonoHasChanged = FALSE;
}

CSemControl::~CSemControl()
{
}

BOOL CSemControl::Create(CObjControls *p)
{
	 mMyObjectPtr =p;  //CObjControls * 

///mDebug.CDebugPut((char *)" Create  ");
	return CDialog::Create(CSemControl::IDD, m_pParent);
}

void CSemControl::Update(CObjControls *p)
{
	mMyObjectPtr =p;
	DisplayData();
}

void CSemControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CNTR_ID, mCntrId);
	DDX_Control(pDX, IDC_EDIT_CNTPOSX, m_edit_cntposX);
	DDX_Control(pDX, IDC_EDIT_CNTPOSY, m_edit_cntposY);
	DDX_Control(pDX, IDC_EDIT_RAIL_ID, m_edit_railId);
	DDX_Control(pDX, IDC_EDIT_RAILPTX_ID2, m_edit_railPtX);
	DDX_Control(pDX, IDC_EDIT_RAILPTY_ID2, m_edit_railPtY);
	//DDX_Control(pDX, IDC_EDIT_EP_ID2, m_edit_railEP);
	DDX_Control(pDX, IDC_EDIT_GROUP_ID, m_edit_group);
	DDX_Control(pDX, IDC_EDIT_TIMEOUT, m_edit_tm);
	DDX_Control(pDX, IDC_CHECK_MONO, m_check_mono);
}


BEGIN_MESSAGE_MAP(CSemControl, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_ID, &CSemControl::OnBnClickedButtonChangeId)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CSemControl::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CSemControl::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CSemControl::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CSemControl::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UPDGROUP, &CSemControl::OnBnClickedButtonUpdgroup)
	ON_BN_CLICKED(IDC_BUTTON_TO1, &CSemControl::OnBnClickedButtonTo1)
	ON_BN_CLICKED(IDC_BUTTON_TO0, &CSemControl::OnBnClickedButtonTo0)
	ON_BN_CLICKED(IDC_CHECK_MONO, &CSemControl::OnBnClickedCheckMono)
END_MESSAGE_MAP()


// CSemControl message handlers


void CSemControl::OnClose()
{
			mCDebugGraphics.EnableGraphics( FALSE );

	  ((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_SEM , 0 , NULL ) ; 

	CDialogEx::OnClose();
}


void CSemControl::DisplayData()
{
	CString Cs0;
	
	Cs0.Format("%d", mMyObjectPtr->GetControlID());
	mCntrId.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailPtrId());
	m_edit_railId.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailControlPoint().x);
	m_edit_railPtX.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailControlPoint().y);
	m_edit_railPtY.SetWindowTextA(Cs0);

	m_check_mono.SetCheck( mMyObjectPtr->IsMonostab() );

	//  This only applies to the switch control
 //	Cs0.Format("NA/%d", mMyObjectPtr->GetGroupId());
 //	m_edit_railEP.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetCenterPoint().x);
	m_edit_cntposX.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetCenterPoint().y);
	m_edit_cntposY.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetGroupId());
	m_edit_group.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetTimeOut() );
	m_edit_tm.SetWindowTextA(Cs0);

	mCDebugGraphics.AddPoint(  GetWhiteColor() , mMyObjectPtr->GetRailControlPoint() );
	Invalidate();

}

void CSemControl::VerifyPointOnLine()
{
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	if ( px != NULL )
	{
		CMyPoint  mp( (float)mMyObjectPtr->GetRailControlPoint().x , (float)mMyObjectPtr->GetRailControlPoint().y);	
				// change this to detect such cases
		int igetd = GetDistanceOfPointFromRail(  px , mp );
		//float dis =  (float)igetd;
		if ( igetd < 0 )
		{
			CString Cs;
			Cs.Format("Invalid control point [err=%d] - check limits" ,-igetd );
			AfxMessageBox(Cs);
		}

		if ( igetd == 2 )  // out of lenght can be corrected
		{
				AfxMessageBox("Invalid control point - fixing ");
				//CMyPoint  mpc( mMyObjectPtr->GetCenterPoint().x , mMyObjectPtr->GetCenterPoint().y);
				//CPoint pt =  GetPointOnRail (  px , mpc ); 

				mDebug.CDebugPut((char *)"Invalid control {idcnt:%d} point:ildId:%d NewId:%d ", mMyObjectPtr->GetControlID() ,mMyObjectPtr->GetRailPtrId() , px->GetRailId()  );
				
				if ( mMyObjectPtr->GetRailPtrId() != px->GetRailId() )
				{
					mDebug.CDebugPut((char *)"Invalid control point:Index error "   );
				}
				else
				{
					CPoint pt =  GetPointOnRail (  px , mMyObjectPtr->GetCenterPoint() ); 
					mMyObjectPtr->SetRailControlPoint( pt);
					mMyObjectPtr->SetRailObjectPtr( px);
				}
		}
	}
}

BOOL CSemControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCDebugGraphics.EnableGraphics( TRUE);
	mCDebugGraphics.ResetStorage();

	VerifyPointOnLine();

	DisplayData();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSemControl::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
			mCDebugGraphics.EnableGraphics( FALSE );

	CString Cs; 
	m_edit_tm.GetWindowTextA(Cs);
	mMyObjectPtr->SetTimeOut( atoi(Cs)) ;

	mMyObjectPtr->SetMonoStab( m_check_mono.GetCheck() );

	if ( MonoHasChanged  == TRUE )
			mCObjRailsColl.CreateControlGroupTbl();


	 ((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_SEM , 0 , NULL ) ; 

	CDialogEx::OnOK();
}


void CSemControl::OnBnClickedButtonChangeId()
{
	CString Cs;
	m_edit_railId.GetWindowTextA(Cs);
	mMyObjectPtr->SetRailPtrId(atoi(Cs));

			//  add this
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());

	if ( px != NULL )
	{
		mMyObjectPtr->SetRailObjectPtr( px);
		CPoint pt =  GetPointOnRail (  px , mMyObjectPtr->GetCenterPoint() ); 
		mMyObjectPtr->SetRailControlPoint( pt);
		mMyObjectPtr->SetRailObjectPtr( px);
		VerifyPointOnLine();
	}
}


void CSemControl::OnBnClickedButtonLeft()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x -4 ,  mMyObjectPtr->GetCenterPoint().y   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CSemControl::OnBnClickedButtonRight()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x + 4 ,  mMyObjectPtr->GetCenterPoint().y   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CSemControl::OnBnClickedButtonUp()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x  ,  mMyObjectPtr->GetCenterPoint().y -4   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CSemControl::OnBnClickedButtonDown()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x  ,  mMyObjectPtr->GetCenterPoint().y + 4   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}

void CSemControl::Invalidate()
{
((CTrainWorldView*)m_pParent)->SwitchDialogMessage( INVALIDATE_MAIN , 0 , NULL ) ; 
}


void CSemControl::OnBnClickedButtonUpdgroup()
{
	CString Cs; 
	m_edit_group.GetWindowTextA(Cs);
	mMyObjectPtr->SetGroupId( (WORD) atoi(Cs) ); 
	DisplayData();
}


void CSemControl::OnBnClickedButtonTo1()
{
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	if ( px != NULL )
	{
		if ( GetDistance( px->GetPoint(1),mMyObjectPtr->GetRailControlPoint() ) > 5)	
			if ( px->GetObjectType() == ObjStraightRail  )
			{
				CMyPoint  pt = GetPointFmStart( mMyObjectPtr->GetRailControlPoint() , px->GetPoint(1) ,    (float)4.0 );
				mMyObjectPtr->SetRailControlPoint( pt);
				DisplayData();
				Invalidate();
			}
	}
}


void CSemControl::OnBnClickedButtonTo0()
{
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	if ( px != NULL )
	{
		if ( GetDistance( px->GetPoint(0),mMyObjectPtr->GetRailControlPoint() ) > 5)
			if ( px->GetObjectType() == ObjStraightRail  )
			{
				CMyPoint  pt = GetPointFmStart( mMyObjectPtr->GetRailControlPoint() , px->GetPoint(0) ,    (float)4.0 );
				mMyObjectPtr->SetRailControlPoint( pt);
				DisplayData();
				Invalidate();
			}
	}
}


void CSemControl::OnBnClickedCheckMono()
{
	// TODO: Add your control notification handler code here
	MonoHasChanged  = TRUE ;	 
}
