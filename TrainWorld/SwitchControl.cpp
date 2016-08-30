// SwitchControl.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "SwitchControl.h"
#include "afxdialogex.h"

// CSwitchControl dialog


#include "TrainWorldDoc.h"
#include "TrainWorldView.h"
 
 
#include "Debug.h"
extern CDebug mDebug;

extern CObjRailsColl  mCObjRailsColl;
extern CDebugGraphics mCDebugGraphics;
 


IMPLEMENT_DYNAMIC(CSwitchControl, CDialogEx)

CSwitchControl::CSwitchControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSwitchControl::IDD, pParent)
{
	m_pParent = pParent;
	mMyObjectPtr = NULL;
	p_main = NULL;
	p_m0= NULL;
	p_m1= NULL;
	id_main=0;
	id_m0=0;
	id_m1=0;
 

}

BOOL CSwitchControl::Create(CObjControls *p)
{
	mMyObjectPtr =p;  //CObjControls * 
 
	return CDialog::Create(CSwitchControl::IDD, m_pParent);
}

CSwitchControl::~CSwitchControl()
{
}

void CSwitchControl::Update(CObjControls *p)
{
	mMyObjectPtr =p;
	DisplayData();
}


void CSwitchControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RAIL_ID0, mSwitch0);
	DDX_Control(pDX, IDC_EDIT_RAIL_ID1, mSwitch1);
	DDX_Control(pDX, IDC_EDIT_RAIL_SEL, mSwitchCur);
	DDX_Control(pDX, IDC_CHECK_TEST, mTestMode);
	DDX_Control(pDX, IDC_EDIT_SWITCHCNT_ID, m_edit_cntId);
	DDX_Control(pDX, IDC_EDIT_CNTPOSX, m_edit_cntposX);
	DDX_Control(pDX, IDC_EDIT_CNTPOSY, m_edit_cntposY);
	DDX_Control(pDX, IDC_EDIT_RAIL_ID, m_edit_railId);
	DDX_Control(pDX, IDC_EDIT_EP_ID, m_edit_railEP);
}


BEGIN_MESSAGE_MAP(CSwitchControl, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CSwitchControl::OnBnClickedOk)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK_TEST, &CSwitchControl::OnBnClickedCheckTest)
	ON_BN_CLICKED(IDC_BUTTON_TESTSWITCH, &CSwitchControl::OnBnClickedButtonTestswitch)
	ON_BN_CLICKED(IDC_BUTTON_SWAP, &CSwitchControl::OnBnClickedButtonSwap)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CSwitchControl::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CSwitchControl::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CSwitchControl::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CSwitchControl::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_ID, &CSwitchControl::OnBnClickedButtonChangeId)
END_MESSAGE_MAP()


// CSwitchControl message handlers


int CSwitchControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CSwitchControl::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	
	mCDebugGraphics.EnableGraphics( FALSE );
		if ( p_main != NULL )
	{
	p_main->SetSelected ( 0);
	p_m0->SetSelected ( 0);
	p_m1->SetSelected ( 0);
		}
	CDialog::OnClose();
 
    ((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_SWITCH , 0 , NULL ) ;

   // DestroyWindow();

	CDialogEx::OnClose();
}


void CSwitchControl::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	mCDebugGraphics.EnableGraphics( FALSE );

	if ( p_main != NULL )
	{
		p_main->SetSelected ( 0);
		p_m0->SetSelected ( 0);
		p_m1->SetSelected ( 0);
	}

	CString Cs;
	m_edit_railId.GetWindowTextA(Cs );
	mMyObjectPtr->SetRailPtrId(atoi(Cs));

	m_edit_railEP.GetWindowTextA(Cs );
	int ep = atoi(Cs);
	mMyObjectPtr->SetRailObjectEndpoint(ep);

	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	mMyObjectPtr->SetRailObjectPtr( px);

	mMyObjectPtr->SetRailControlPoint( px->GetPPoint(ep));
				 
 


    ((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_SWITCH , 0 , NULL ) ; 

	CDialogEx::OnOK();
}


HBRUSH CSwitchControl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CSwitchControl::Verify()
{
     CPoint pt =  mMyObjectPtr->GetRailControlPoint() ;
	 int Id = mMyObjectPtr->GetRailPtrId();
	 int ep = mMyObjectPtr->GetControlEndpoint();
	 CObjRail  *pr =  mCObjRailsColl.GetRailObjPtrByIdIndex( Id  );

	 if ( pr != NULL )
	 {
		CMyPoint   mp( pr->GetPoint( ep));
		if ( GetDistance ( pt , mp)   > 1.2 )
		{
		 AfxMessageBox("Invalid control point - fixing ");
		 mMyObjectPtr->SetRailControlPoint( mp) ;
		}
	 }
}

void CSwitchControl::DisplayData()
{
		CString Cs0;
	Cs0.Format("%d", mMyObjectPtr->GetControlID());
	m_edit_cntId.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailPtrId());
	m_edit_railId.SetWindowTextA(Cs0);

		//  This only applies to the switch control
	Cs0.Format("%d", mMyObjectPtr->GetControlEndpoint());
	m_edit_railEP.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetCenterPoint().x);
	m_edit_cntposX.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetCenterPoint().y);
	m_edit_cntposY.SetWindowTextA(Cs0);

	Cs0.Format("%d", id_m0  );
 	mSwitch0.SetWindowTextA(Cs0);

	Cs0.Format("%d", id_m1  );
	mSwitch1.SetWindowTextA(Cs0);

	mCDebugGraphics.AddPoint(  GetWhiteColor() , mMyObjectPtr->GetRailControlPoint() );
	Invalidate();
 

}

BOOL CSwitchControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCDebugGraphics.EnableGraphics( TRUE);
	mCDebugGraphics.ResetStorage();

 
	Verify();

	p_main = mMyObjectPtr->GetRailObjectPointer();
	i_mept = mMyObjectPtr->GetControlEndpoint();  // 0 or 1
	i_virt_mept = i_mept + (i_mept == 1);

//mDebug.CDebugPut((char *)" ep =%d virt =%d  ", i_mept  , i_virt_mept );

	id_main= mMyObjectPtr->GetRailPtrId() ;

	if ( p_main != NULL )
	{
		id_m0 = p_main->GetRailConnId( i_virt_mept );
		id_m1 = p_main->GetRailConnId( i_virt_mept+1 );
		p_m0 = mCObjRailsColl.GetRailObjPtrByIdIndex( id_m0  );
		p_m1 = mCObjRailsColl.GetRailObjPtrByIdIndex( id_m1  );
	}

	if ( (p_m0 == NULL) || ( p_m1 == NULL ))
		AfxMessageBox("Invalid rail(s) Id(s)");
	else
		DisplayStatus();
 
//	p_main->SetSelected ( 1);
//	p_m0->SetSelected ( 1);
//	p_m1->SetSelected ( 1);
//((CTrainWorldView*)m_pParent)->SwitchDialogMessage( INVALIDATE_MAIN , 0 , NULL ) ; 
 
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSwitchControl::DisplayStatus()
{

	CObjRail *p = p_main;
	
	CString Cs2;
	Cs2.Format("%d/%d",  p->GetRailConnId( i_virt_mept + p->GetSwitchStatus(i_mept) ) ,i_mept );
 
	mSwitchCur.SetWindowTextA(Cs2);

	DisplayData();

}


void CSwitchControl::MarkLineStatus()
{

	int ConId =  p_main->GetRailConnId( i_virt_mept + p_main->GetSwitchStatus(i_mept) )  ;

	CObjRail *pp = mCObjRailsColl.GetRailObjPtrByIdIndex( ConId  ); 

	if ( pp != NULL )
	{
		pp->SetSelected ( 1);
		((CTrainWorldView*)m_pParent)->SwitchDialogMessage( ENABLE_TESTMODE , mTestMode.GetCheck() , NULL ) ; 
	}
}

void CSwitchControl::OnBnClickedCheckTest()
{
	p_main->SetSelected ( 1);
	MarkLineStatus();
}


void CSwitchControl::OnBnClickedButtonTestswitch()
{
	// TODO: Add your control notification handler code here
 
	p_m0->SetSelected ( 0);
	p_m1->SetSelected ( 0);
((CTrainWorldView*)m_pParent)->SwitchDialogMessage( INVALIDATE_MAIN , 0 , NULL ) ; 

	mMyObjectPtr->ToggleStatus();
	p_main->SetSwitch( mMyObjectPtr->GetControlEndpoint() , mMyObjectPtr->GetStatus() ) ;	

	MarkLineStatus();
	DisplayStatus();
}


void CSwitchControl::OnBnClickedButtonSwap()
{
	// swap et end point

	p_m0->SetSelected ( 0);
	p_m1->SetSelected ( 0);

	p_main->SetConnection( i_virt_mept ,id_m1 );
	p_main->SetConnection( i_virt_mept+1 ,id_m0 );

	id_m0 = p_main->GetRailConnId( i_virt_mept );
	id_m1 = p_main->GetRailConnId( i_virt_mept+1 );

	MarkLineStatus();
	DisplayStatus();

}


void CSwitchControl::OnBnClickedButtonLeft()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x -4 ,  mMyObjectPtr->GetCenterPoint().y   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CSwitchControl::OnBnClickedButtonRight()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x + 4 ,  mMyObjectPtr->GetCenterPoint().y   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CSwitchControl::OnBnClickedButtonUp()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x  ,  mMyObjectPtr->GetCenterPoint().y -4   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CSwitchControl::OnBnClickedButtonDown()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x  ,  mMyObjectPtr->GetCenterPoint().y + 4  );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}
 

void CSwitchControl::Invalidate()
{
((CTrainWorldView*)m_pParent)->SwitchDialogMessage( INVALIDATE_MAIN , 0 , NULL ) ; 
}

 

void CSwitchControl::OnBnClickedButtonChangeId()
{  // have to update both rail and control
 
	// updating control

	// new one 
	CString Cs; 
	m_edit_railId.GetWindowTextA(Cs);

	// have ID but need to have pointer

	CObjRail *pObjRail =  mCObjRailsColl.GetRailObjPtrByIdIndex( atoi(Cs) ); 

	if ( pObjRail != NULL )
	{
	mMyObjectPtr->SetRailObjectPtr(pObjRail );

	m_edit_railEP.GetWindowTextA(Cs );
	mMyObjectPtr->SetRailObjectEndpoint( atoi(Cs));

	m_edit_railEP.GetWindowTextA(Cs);
	int ep =   atoi(Cs);
	int epc = ep << 1 ;

	mSwitch0.GetWindowTextA(Cs);
	int cn0 = atoi( Cs);
	mSwitch1.GetWindowTextA(Cs);
	int cn1 = atoi( Cs);

	pObjRail->SetConnection( epc  , cn0  );
	pObjRail->SetConnection( epc +1 ,  cn1 );

	p_main = pObjRail;
	
	}

	DisplayData();
}
