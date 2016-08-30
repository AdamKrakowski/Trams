// RoutesRec.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "RoutesRec.h"
#include "afxdialogex.h"

#include "Debug.h"
extern CDebug mDebug;

// static class initiated here
CObjTramLine mCObjTramLine;

// CRoutesRec dialog

IMPLEMENT_DYNAMIC(CRoutesRec, CDialogEx)

CRoutesRec::CRoutesRec(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRoutesRec::IDD, pParent)
{

}

CRoutesRec::~CRoutesRec()
{
}

void CRoutesRec::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROUTE_ID, m_edit_route_id);
	DDX_Control(pDX, IDC_EDIT_CNTR_ID, m_edit_cntr_id);
	DDX_Control(pDX, IDC_EDIT_PARAM, m_edit_param);
	DDX_Control(pDX, IDC_LIST_RECORDS, m_list_records);
	DDX_Control(pDX, IDC_EDIT_TRAMID, m_edit_option);
}


BEGIN_MESSAGE_MAP(CRoutesRec, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BASE, &CRoutesRec::OnBnClickedButtonBase)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CRoutesRec::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CRoutesRec::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_UPD, &CRoutesRec::OnBnClickedButtonUpd)
	ON_BN_CLICKED(IDOK, &CRoutesRec::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CRoutesRec::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_LIST_RECORDS, &CRoutesRec::OnLbnSelchangeListRecords)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CRoutesRec::OnBnClickedButtonPrint)
END_MESSAGE_MAP()



void CRoutesRec::LoadRecords( int route_id )
{
	m_list_records.ResetContent();
	int icur =0;
	for ( int i=0; i < mCObjTramLine.mRecords; i++)
	{
		if ( (mCObjTramLine.mLineDataBase[i].mLineId == route_id )  || ( 0 == route_id ) )
		{
			CString Cs;

			int ilineId = mCObjTramLine.mLineDataBase[i].mLineId;
			int icntr   = mCObjTramLine.mLineDataBase[i].mControlId;
			int iparam  = mCObjTramLine.mLineDataBase[i].mParam;
			int itype   = mCObjTramLine.mLineDataBase[i].mType;

			if ( icntr < 5000 )
			{
				if ( itype == 0 )
					Cs.Format("%03d:Ln:%d SwId:%d NxtTrk:%d", i, ilineId , icntr , iparam );
				else if ( (itype > 0 ) && (itype < 999  ))
					Cs.Format("%03d:Ln:%d StopId:%d Tram Id:%d Time:%02d:%02d", i, ilineId , icntr, itype , iparam/60, iparam%60 );
				else if ( itype == 1024  ) 
					Cs.Format("%03d:Ln:%d SwId:%d {Nite}NxtTrk:%d", i, ilineId , icntr , iparam );
				else
					Cs.Format("%03d:(?)Ln:%d Cntr:%d Type:%d Val:%d", i, ilineId , icntr , itype , iparam );
			}
			else
			{
				if ( itype == 0 )
					Cs.Format("%03d:Ln:%d VCnt:%d Val:%d", i, ilineId , icntr , iparam );
				else
					Cs.Format("%03d:Ln:%d VCnt:%d Tram:%d Val:%d", i, ilineId , icntr , itype, iparam );
			}

			m_list_records.InsertString(icur++,Cs);
		}
	}
}


// CRoutesRec message handlers


void CRoutesRec::OnBnClickedButtonBase()
{
 	CString Cs; 
	m_edit_route_id.GetWindowTextA(Cs);
	m_current_route_slection_Id = atoi(Cs);
	LoadRecords( m_current_route_slection_Id);
}


void CRoutesRec::OnBnClickedButtonAdd()
{
	CString Cs; 
	m_edit_cntr_id.GetWindowTextA(Cs);
	CString Cs1; 
	m_edit_param.GetWindowTextA(Cs1);
	CString Cs2; 
	m_edit_option.GetWindowTextA(Cs2);

	int opt = (WORD) atoi(Cs2);
	int param = (WORD) atoi(Cs1);

	if ( ( opt > 0 ) && (opt < 999) )
		{
			int p1 = (WORD) atoi(Cs1)*60;
			int p2 = 0;
			int ip = Cs1.Find(':' );

			if ( ip > 0 )
			{
				CString Cs22 = Cs1.Mid( ip+1);
				p2 = atoi(Cs22);
				param = p1  +p2;
			}
		}
 

	if ( mCObjTramLine.mRecords < MAX_CNT_RECORDS)
	{
		int i = mCObjTramLine.mRecords;
		mCObjTramLine.mLineDataBase[i].mControlId = (WORD) atoi(Cs);
		mCObjTramLine.mLineDataBase[i].mLineId  = (WORD)m_current_route_slection_Id;
		mCObjTramLine.mLineDataBase[i].mType = opt;
		mCObjTramLine.mLineDataBase[i].mParam  = param;

		mCObjTramLine.mRecords +=1;	
		LoadRecords( m_current_route_slection_Id);
	}
}


void CRoutesRec::OnBnClickedButtonDel()
{
	int csel =  m_list_records.GetCurSel();
	if ( csel >= 0 )
	{
		CString Cs;
		m_list_records.GetText( csel, Cs );
		int rsel = atoi(Cs);

		mCObjTramLine.mRecords -=1;

		for ( int i=  rsel ; i < mCObjTramLine.mRecords; i++)
		{
			mCObjTramLine.mLineDataBase[i] = mCObjTramLine.mLineDataBase[i+1];
		}
		LoadRecords( m_current_route_slection_Id);

	}
}

void CRoutesRec::OnBnClickedButtonUpd()
{
	int csel =  m_list_records.GetCurSel();
	if ( csel >= 0 )
	{
		CString Cs;
		m_list_records.GetText( csel, Cs );
		int rsel = atoi(Cs);

		m_edit_cntr_id.GetWindowTextA(Cs);
		CString Cs1; 
		m_edit_param.GetWindowTextA(Cs1);
		CString Cs2; 
		m_edit_option.GetWindowTextA(Cs2);

		int opt = (WORD) atoi(Cs2);
		int param = (WORD) atoi(Cs1);

		if ( ( opt > 0 ) && (opt < 999) )
		{
			int p1 = (WORD) atoi(Cs1)*60;
			int p2 = 0;
			int ip = Cs1.Find(':' );

			if ( ip > 0 )
			{
				CString Cs22 = Cs1.Mid( ip+1);
				p2 = atoi(Cs22);
				param = p1  +p2;
			}
		}


	 	mCObjTramLine.mLineDataBase[rsel].mControlId = (WORD) atoi(Cs);
		mCObjTramLine.mLineDataBase[rsel].mParam  = param;
		mCObjTramLine.mLineDataBase[rsel].mType = opt;
		LoadRecords( m_current_route_slection_Id);

	}

}


void CRoutesRec::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	mCObjTramLine.DoLineIndex();

	CDialogEx::OnOK();
}


void CRoutesRec::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CRoutesRec::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnOK();
}


BOOL CRoutesRec::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if ( mCObjTramLine.mRecords == 0) 
	{
		m_current_route_slection_Id =1;
		m_edit_route_id.SetWindowTextA("1");
	}
	else
	{  // find first available records
		int min_route_id =1000;
		for ( int i=0; i < mCObjTramLine.mRecords; i++)
			if ( mCObjTramLine.mLineDataBase[i].mLineId < min_route_id ) min_route_id = mCObjTramLine.mLineDataBase[i].mLineId;

		CString Cs;Cs.Format("%d",min_route_id);
		m_edit_route_id.SetWindowTextA(Cs);
		LoadRecords( min_route_id );
		m_current_route_slection_Id = min_route_id; 
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRoutesRec::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}



void CRoutesRec::OnLbnSelchangeListRecords()
{
	int csel =  m_list_records.GetCurSel();
	if ( csel >= 0 )
	{
		CString Cs;
		m_list_records.GetText( csel, Cs );
		int rsel = atoi(Cs);

		int iCnt =  mCObjTramLine.mLineDataBase[rsel].mControlId ;
		int iPar =  mCObjTramLine.mLineDataBase[rsel].mParam ;
		int iOp =  mCObjTramLine.mLineDataBase[rsel].mType ;
 
		Cs.Format("%d" , iCnt);
		m_edit_cntr_id.SetWindowTextA(Cs);
		
		if ( iCnt < 5000 )
			{
				if ( (iOp > 0 ) && (iOp < 999  ))
					Cs.Format("%02d:%02d" , iPar/60 , iPar%60 ); 
				else
					Cs.Format("%d" , iPar);  
			}
		else
			Cs.Format("%d" , iPar);

		m_edit_param.SetWindowTextA(Cs);


		Cs.Format("%d" , iOp); 
		m_edit_option.SetWindowTextA(Cs);

	}
} 

 


void CRoutesRec::OnBnClickedButtonPrint()
{
	int count=  m_list_records.GetCount();

	mDebug.CDebugPut("Programming for line: %d ", (int)m_current_route_slection_Id);

	for ( int i =0 ; i < count ;i++)
	{
		char b[80];
		int blen = m_list_records.GetTextLen(i);

		if ( blen  < 78 )
		{
			m_list_records.GetText ( i , (LPTSTR)b );
			mDebug.CDebugPut( b );
		}
		else  mDebug.CDebugPut( "Buffer to small:%d need:%d", (int)78 , blen );
	}
	mDebug.CDebugPut("Number of entries:%d ", (int)count);

}
