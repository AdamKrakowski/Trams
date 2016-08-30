// RailEdit.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "RailEdit.h"
#include "afxdialogex.h"

#include "TrainWorldDoc.h"
#include "TrainWorldView.h"
 
#include "Debug.h"
extern CDebug mDebug;

// CRailEdit dialog

IMPLEMENT_DYNAMIC(CRailEdit, CDialogEx)

CRailEdit::CRailEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRailEdit::IDD, pParent)
{
	m_pParent = pParent;
}

BOOL CRailEdit::Create(CObjRail *p)
{
	 mMyObjectPtr =p;  //CObjControls * 

///mDebug.CDebugPut((char *)" Create  ");
	return CDialog::Create(CRailEdit::IDD, m_pParent);
}

void CRailEdit::Update( CObjRail *p) 
{
	mMyObjectPtr =p; 
	DisplayRailData(); 
}


CRailEdit::~CRailEdit()
{
}

void CRailEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RAIL_ID0, mRailId);
	DDX_Control(pDX, IDC_EDIT_EP00, m_edit_ep00);
	DDX_Control(pDX, IDC_EDIT_EP10, m_edit_ep10);
	DDX_Control(pDX, IDC_EDIT_EP01, m_edit_ep01);
	DDX_Control(pDX, IDC_EDIT_EP11, m_edit_ep11);
	DDX_Control(pDX, IDC_EDIT_EP0X, m_edit_ep0X);
	DDX_Control(pDX, IDC_EDIT_EP0Y, m_edit_ep0Y);
	DDX_Control(pDX, IDC_EDIT_EP1X, m_edit_ep1X);
	DDX_Control(pDX, IDC_EDIT_EP1Y, m_edit_ep1Y);
	DDX_Control(pDX, IDC_EDIT_CPX, m_edit_cpX);
	DDX_Control(pDX, IDC_EDIT_CPY, m_edit_cpY);
	DDX_Control(pDX, IDC_CHECK_LAUNCH, m_check_launch);
	DDX_Control(pDX, IDC_EDIT_INFO1, m_edit_info1);
	DDX_Control(pDX, IDC_EDIT_RAIL_TYPE, m_edit_type);
	DDX_Control(pDX, IDC_CHECK_UNDERGND, m_check_underground);
}


BEGIN_MESSAGE_MAP(CRailEdit, CDialogEx)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CRailEdit::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_UPPOINTS, &CRailEdit::OnBnClickedButtonUppoints)
	ON_BN_CLICKED(IDC_CHECK_UNDERGND, &CRailEdit::OnBnClickedCheckUndergnd)
END_MESSAGE_MAP()


// CRailEdit message handlers
void CRailEdit::DisplayRailData()
{
CString Cs0;
		Cs0.Format("%d", mMyObjectPtr->GetRailId());
		mRailId.SetWindowTextA(Cs0);

		Cs0.Format("%d", mMyObjectPtr->GetRailConnId(0));
		m_edit_ep00.SetWindowTextA(Cs0);

		Cs0.Format("%d", mMyObjectPtr->GetRailConnId(1));
		m_edit_ep01.SetWindowTextA(Cs0);

		Cs0.Format("%d", mMyObjectPtr->GetRailConnId(2));
		m_edit_ep10.SetWindowTextA(Cs0);

		Cs0.Format("%d", mMyObjectPtr->GetRailConnId(3));
		m_edit_ep11.SetWindowTextA(Cs0);

		m_check_underground.SetCheck( mMyObjectPtr->IsUndergroundRail() );

		Cs0.Format("%d", (int)mMyObjectPtr->GetPoint(0).x);
		m_edit_ep0X.SetWindowTextA(Cs0);
		Cs0.Format("%d", (int)mMyObjectPtr->GetPoint(0).y);
		m_edit_ep0Y.SetWindowTextA(Cs0);

		Cs0.Format("%d", (int)mMyObjectPtr->GetPoint(1).x);
		m_edit_ep1X.SetWindowTextA(Cs0);
		Cs0.Format("%d", (int)mMyObjectPtr->GetPoint(1).y);
		m_edit_ep1Y.SetWindowTextA(Cs0);

		if (( mMyObjectPtr->GetObjectType() == ObjBendLeftRail ) || ( mMyObjectPtr->GetObjectType() == ObjBendRightRail ))
		{
			CObjBendRail *pb =  ( CObjBendRail * )mMyObjectPtr;

			Cs0.Format("%9.4f", pb->GetCenterPoint().x);
			m_edit_cpX.SetWindowTextA(Cs0);
			Cs0.Format("%9.4f", pb->GetCenterPoint().y);
			m_edit_cpY.SetWindowTextA(Cs0);	

			m_edit_type.SetWindowTextA("Bend");
		}
		else
			m_edit_type.SetWindowTextA("Stright");

		Cs0.Format("%d", (int)GetDistance( mMyObjectPtr->GetPoint(0),mMyObjectPtr->GetPoint(1)));
		m_edit_info1.SetWindowTextA(Cs0);

		 
}

BOOL CRailEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

		DisplayRailData(); 



	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

 void CRailEdit::OnBnClickedButtonUpdate()
{
	CString Cs; 
	m_edit_ep00.GetWindowTextA(Cs);
	mMyObjectPtr->SetConnection(0 , atoi(Cs) );

	m_edit_ep01.GetWindowTextA(Cs);
	mMyObjectPtr->SetConnection(1 , atoi(Cs) );

	m_edit_ep10.GetWindowTextA(Cs);
	mMyObjectPtr->SetConnection(2 , atoi(Cs) );

	m_edit_ep11.GetWindowTextA(Cs);
	mMyObjectPtr->SetConnection(3 , atoi(Cs) );

}

void CRailEdit::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	mMyObjectPtr->SetUndergroundRail( m_check_underground.GetCheck() );


	((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_RAIL , 0 , NULL ) ; 

	CDialogEx::OnOK();
}


void CRailEdit::OnClose()
{
	// TODO: Add your message handler code here and/or call default
		  ((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_RAIL , 0 , NULL ) ; 

	CDialogEx::OnClose();
}


void CRailEdit::OnBnClickedButtonUppoints()
{

	CString Cs; 
	m_edit_ep0X.GetWindowTextA(Cs);
	int ix =   atoi(Cs);

	m_edit_ep0Y.GetWindowTextA(Cs);
	int iy =   atoi(Cs);

	mMyObjectPtr->SetPoint( 0 , CPoint(ix,iy ) ); 

	m_edit_ep1X.GetWindowTextA(Cs);
	ix =   atoi(Cs);

	m_edit_ep1Y.GetWindowTextA(Cs);
	iy =   atoi(Cs);

	mMyObjectPtr->SetPoint( 1 , CPoint(ix,iy ) ); 

}

 


void CRailEdit::OnBnClickedCheckUndergnd()
{

//	if ( m_check_underground.GetCheck() == TRUE ) m_check_underground.SetCheck(FALSE);
//	else m_check_underground.SetCheck(TRUE);
}
