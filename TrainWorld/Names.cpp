// Names.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "Names.h"
#include "afxdialogex.h"


#include "Debug.h"
extern CDebug mDebug;


// CNames dialog

CObjNames mObjNames;


IMPLEMENT_DYNAMIC(CNames, CDialogEx)

CNames::CNames(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNames::IDD, pParent)
{

}

CNames::~CNames()
{
}

void CNames::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_NAMES, m_listbox_names);
	DDX_Control(pDX, IDC_EDIT_NAME, m_edit_name);
}


BEGIN_MESSAGE_MAP(CNames, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNames::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CNames::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CNames::OnBnClickedButtonAdd)
	ON_LBN_SELCHANGE(IDC_LIST_NAMES, &CNames::OnLbnSelchangeListNames)
	ON_LBN_DBLCLK(IDC_LIST_NAMES, &CNames::OnLbnDblclkListNames)
END_MESSAGE_MAP()


// CNames message handlers

void CNames::LoadRecords()
{
	m_listbox_names.ResetContent();
	int icur =0;
	for ( int i=0; i < mObjNames.mRecords; i++)
	{
			CString Cs; Cs.Format("%d:", mObjNames.mNameDataBase[i].mId );
			Cs += mObjNames.mNameDataBase[i].mName;
			m_listbox_names.InsertString(icur++,Cs);
	}
}


void CNames::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CNames::OnBnClickedButtonDelete()
{
		
	if ( mObjNames.mRecords > 0 )
	{
		mObjNames.mRecords -=1;
		mObjNames.mLastId -=1;
		LoadRecords();
	}
}


void CNames::OnBnClickedButtonAdd()
{
	CString Cs; 
	m_edit_name.GetWindowTextA(Cs);
 
	if ( Cs.GetLength() == 0 ) return;

	if ( mObjNames.mRecords < MAX_NAME_RECORDS)
	{
		int i = mObjNames.mRecords;
		mObjNames.mNameDataBase[i].mName = Cs;
		mObjNames.mRecords +=1;
		mObjNames.mLastId +=1;
		mObjNames.mNameDataBase[i].mId = mObjNames.mLastId;
		LoadRecords();
	}
}


void CNames::OnLbnSelchangeListNames()
{
	int csel =  m_listbox_names.GetCurSel();
	if ( csel >= 0 )
	{
		CString Cs;
		m_listbox_names.GetText( csel, Cs );
		int rsel = atoi(Cs) -1 ;
 
		Cs = mObjNames.mNameDataBase[rsel].mName; 
		m_edit_name.SetWindowTextA(Cs);
	}
}


void CNames::OnLbnDblclkListNames()
{
	// TODO: Add your control notification handler code here
}


BOOL CNames::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LoadRecords();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
