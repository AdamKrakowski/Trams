// FindStop.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "TrainWorldDoc.h"
#include "TrainWorldView.h"

#include "FindStop.h"
#include "afxdialogex.h"

#include "Debug.h"
extern CDebug mDebug;
#include "Debug.h"
extern CDebug mDebug;

extern CDebugGraphics mCDebugGraphics;
extern CObjRailsColl  mCObjRailsColl;


// CNames dialog

extern CObjNames mObjNames;



// CFindStop dialog

IMPLEMENT_DYNAMIC(CFindStop, CDialogEx)

CFindStop::CFindStop(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindStop::IDD, pParent)
{
		m_pParent = pParent;
}

CFindStop::~CFindStop()
{
}

void CFindStop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STOPNAMES, m_listbox_names);
}


BEGIN_MESSAGE_MAP(CFindStop, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CFindStop::OnBnClickedButtonFind)
	ON_WM_CLOSE()
	ON_LBN_DBLCLK(IDC_LIST_STOPNAMES, &CFindStop::OnLbnDblclkListStopnames)
END_MESSAGE_MAP()

BOOL CFindStop::Create( int selId  )
{
	initialId = selId;
	return CDialog::Create(CFindStop::IDD, m_pParent);
}


// CFindStop message handlers


void CFindStop::OnBnClickedButtonFind()
{
 

	int isel = m_listbox_names.GetCurSel();

 
	if ( isel >= 0 )
	{
		CString Cs;
		m_listbox_names.GetText( isel , Cs );
		mCurSel = atoi( Cs );

		CObjControls *pc;

//mDebug.CDebugPut((char *)"CFindStop:mCurSel:%d  ",(int)mCurSel);	

		pc = mCObjRailsColl.FindControlObjectByTextId( mCurSel );

		if ( pc != NULL )
		{
			CPoint pt = pc->GetCenterPoint();
		    ((CTrainWorldView*)m_pParent)->MoveWindowToTheObject( (int)pt.x ,  (int)pt.y ) ;
		}
	}
}


void CFindStop::OnClose()
{
	((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_STOPS , 0 , NULL ) ; 

	CDialogEx::OnClose();
}


void CFindStop::OnOK()
{
	((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_STOPS , 0 , NULL ) ; 

	CDialogEx::OnOK();
}


BOOL CFindStop::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_listbox_names.ResetContent();
	int icur =0;
	for ( int i=0; i < mObjNames.mRecords; i++)
	{
			CString Cs; Cs.Format("%d:", mObjNames.mNameDataBase[i].mId );
			Cs += mObjNames.mNameDataBase[i].mName;
			m_listbox_names.InsertString(icur++,Cs);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFindStop::OnLbnDblclkListStopnames()
{
	OnBnClickedButtonFind();
}
