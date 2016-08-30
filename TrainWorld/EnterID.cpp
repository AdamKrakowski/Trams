// EnterID.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"
#include "EnterID.h"
#include "afxdialogex.h"


// CEnterID dialog

IMPLEMENT_DYNAMIC(CEnterID, CDialogEx)

CEnterID::CEnterID(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnterID::IDD, pParent)
{
	m_ID_Selected =0;
}

CEnterID::~CEnterID()
{
}

void CEnterID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ENTERID, m_edit_enterid);
}


BEGIN_MESSAGE_MAP(CEnterID, CDialogEx)
END_MESSAGE_MAP()


// CEnterID message handlers


void CEnterID::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CString Cs; 
	m_edit_enterid.GetWindowTextA(Cs);

	m_ID_Selected = atoi(Cs) ;

	CDialogEx::OnOK();
}


BOOL CEnterID::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	CString Cs0;
	Cs0.Format("%d", m_ID_Selected );
	m_edit_enterid.SetWindowTextA(Cs0);

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
