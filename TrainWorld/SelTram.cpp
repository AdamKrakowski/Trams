// SelTram.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"
#include "SelTram.h"
#include "afxdialogex.h"

#include "StdTrainDef.h" 
#include "TrainObjects.h"

// CSelTram dialog

IMPLEMENT_DYNAMIC(CSelTram, CDialogEx)

CSelTram::CSelTram(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelTram::IDD, pParent)
{

}

CSelTram::~CSelTram()
{
}

void CSelTram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VAGON1, m_combo_vagon1);
	DDX_Control(pDX, IDC_COMBO_VAGON2, m_combo_vagon2);
	DDX_Control(pDX, IDC_COMBO_VAGON3, m_combo_vagon3);
	DDX_Control(pDX, IDC_COMBO_VAGON4, m_combo_vagon4);
	DDX_Control(pDX, IDC_COMBO_VAGON5, m_combo_vagon5);
	DDX_Control(pDX, IDC_COMBO_VAGON6, m_combo_vagon6);
	DDX_Control(pDX, IDC_COMBO_VAGON7, m_combo_vagon7);
	DDX_Control(pDX, IDC_COMBO_VAGON8, m_combo_vagon8);
	DDX_Control(pDX, IDC_COMBO_VAGON9, m_combo_vagon9);
	DDX_Control(pDX, IDC_EDIT_WIDTH, m_edit_width);
	DDX_Control(pDX, IDC_EDIT_LINEID, m_edit_lineid);
}


BEGIN_MESSAGE_MAP(CSelTram, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSelTram::OnBnClickedOk)
END_MESSAGE_MAP()


// CSelTram message handlers
#include "Debug.h"
extern CDebug mDebug;

int CSelTram::GetSelectedTramId()
{
	return mCurrentCheck;
}

void CSelTram::LoadComboWithColors( CComboBox *p )
{
	p->InsertString(0,"Blue");
	p->InsertString(1,"Green");
	p->InsertString(2,"Red");
	p->InsertString(3,"Yellow");
	p->InsertString(4,"Light Blue");
 	p->InsertString(5,"Orange");
	p->InsertString(6,"Dark Yellow");
	p->InsertString(7,"Dark Green");
}

DWORD CSelTram::GetColorCode ( CComboBox *p )
{
	int sel = p->GetCurSel();

	switch ( sel )
	{
		case 0:
			return 0;
		break;
		case 1:
			return BODY_GREEN;
		break;
		case 2:
			return BODY_RED;
		break;
		case 3:
			return BODY_YELLOW;
		break;
		case 4:
			return BODY_LBLUE;
		break;
		default:
			return 0;
	    break;
	}
}
 


BOOL CSelTram::OnInitDialog()
{
	CDialogEx::OnInitDialog();
 
	LoadComboWithColors( &m_combo_vagon1 );
	LoadComboWithColors( &m_combo_vagon2 );
	LoadComboWithColors( &m_combo_vagon3 );
	LoadComboWithColors( &m_combo_vagon4 );
	LoadComboWithColors( &m_combo_vagon5 );
	LoadComboWithColors( &m_combo_vagon6 );
	LoadComboWithColors( &m_combo_vagon7 );
	LoadComboWithColors( &m_combo_vagon8 );
	LoadComboWithColors( &m_combo_vagon9 );

	m_combo_vagon1.SetCurSel(0);
	m_combo_vagon2.SetCurSel(0);
	m_combo_vagon3.SetCurSel(0);
	m_combo_vagon4.SetCurSel(0);
	m_combo_vagon5.SetCurSel(0);
	m_combo_vagon6.SetCurSel(0);
	m_combo_vagon7.SetCurSel(0);
	m_combo_vagon8.SetCurSel(0);
	m_combo_vagon9.SetCurSel(0);

	CString Cs0;
	Cs0.Format("%d", (int)5);
	m_edit_width.SetWindowTextA(Cs0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CSelTram::GetShape( CTramModelDef *mModel  )
{
	int width = mWidth ;

	if ( mCurrentCheck  == IDC_RADIO_SBT9 )
	{
			mModel[0].len = 38;
			mModel[0].style = FRONT_DRW | BACK_SHD | ccode1;
			mModel[0].width = width;

			mModel[1].len = 14;
			mModel[1].style = FRONT_SHD| BACK_SHD | ccode2;
			mModel[1].width = width;
 
			mModel[2].len = 38;
			mModel[2].style = FRONT_SHD |  ccode3 ;
			mModel[2].width = width;
 		return 3;
	}

	if ( mCurrentCheck  == IDC_RADIO_SBT8 )
	{
			mModel[0].len = 38;
			mModel[0].style = FRONT_DRW | BACK_SHD | ccode1;
			mModel[0].width = width;

			mModel[1].len = 34;
			mModel[1].style = FRONT_SHD| BACK_SHD | ccode2;
			mModel[1].width = width;

			mModel[2].len = 38;
			mModel[2].style = FRONT_SHD | ccode3;
			mModel[2].width = width;
 		return 3;
	}

	if ( mCurrentCheck  == IDC_RADIO_SKRK )
	{
			mModel[0].len = 36;
			mModel[0].style = FRONT_DRW | BACK_SHD | ccode1;
			mModel[0].width = width;

			mModel[1].len = 34;
			mModel[1].style = FRONT_SHD| BACK_SHD | ccode2;
			mModel[1].width = width;

			mModel[2].len = 34;
			mModel[2].style = FRONT_SHD| BACK_SHD | ccode3;
			mModel[2].width = width;

			mModel[3].len = 36;
			mModel[3].style = FRONT_SHD | ccode4;
			mModel[3].width = width;
 		return 4;
	}

		if ( mCurrentCheck  == IDC_RADIO_SA2 )
	{
			mModel[0].len = 44;
			mModel[0].style =   ccode1  ;
			mModel[0].width = width;

			mModel[1].len = 44;
			mModel[1].style =  ccode2;
			mModel[1].width = width;
 		return 2;
	}

	if ( mCurrentCheck  == IDC_RADIO_SA3 )
	{
			mModel[0].len = 44;
			mModel[0].style =  ccode1 ;
			mModel[0].width = width;

			mModel[1].len = 44;
			mModel[1].style =  ccode2;
			mModel[1].width = width;

			mModel[2].len = 44;
			mModel[2].style =   ccode3;
			mModel[2].width = width;
 		return 3;
	}


	if ( mCurrentCheck  == IDC_RADIO_SP5 )
	{
			mModel[0].len = 38;
			mModel[0].style = FRONT_DRW | BACK_SHD | ccode1;
			mModel[0].width = width;

			mModel[1].len = 32;
			mModel[1].style = FRONT_SHD| BACK_SHD | ccode2;
			mModel[1].width = width;

			mModel[2].len = 32;
			mModel[2].style = FRONT_SHD| BACK_SHD | ccode3;
			mModel[2].width = width;

			mModel[3].len = 32;
			mModel[3].style = FRONT_SHD| BACK_SHD | ccode4;
			mModel[3].width = width;

			mModel[4].len = 32;
			mModel[4].style = FRONT_SHD | ccode5;
			mModel[4].width = width;

 		return 5;
	}

	if (  mCurrentCheck  == IDC_RADIO_SINGL )
	{
			mModel[0].len = 44;
			mModel[0].style = ccode1   ;
			mModel[0].width = width;
			return 1;
	}
 
	if (  mCurrentCheck  == IDC_RADIO_NORBG )
	{
			mModel[0].len = 38;
			mModel[0].style = FRONT_DRW | BACK_SHD | ccode1;
			mModel[0].width = width;

			mModel[1].len = 38;
			mModel[1].style = FRONT_SHD | ccode2;
			mModel[1].width = width;
			return 2;
	}

	if (  mCurrentCheck  == IDC_RADIO_NORBG2 )
	{
			mModel[0].len = 34;
			mModel[0].style = FRONT_DRW | BACK_SHD | ccode1;
			mModel[0].width = width;

			mModel[1].len = 34;
			mModel[1].style = FRONT_SHD | ccode2;
			mModel[1].width = width;

			mModel[2].len = 44;
			mModel[2].style =  ccode3;
			mModel[2].width = width;

			return 3;
	}
 
	return 0;
}

void CSelTram::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here


	//	mDebug.CDebugPut((char *)" IDC_RADIO_SBT8 (%d  " , IsDlgButtonChecked(   IDC_RADIO_SBT8  )  );
	//	mDebug.CDebugPut((char *)" IDC_RADIO_SBT9 (%d  " , IsDlgButtonChecked(   IDC_RADIO_SBT9  )  );
	//	mDebug.CDebugPut((char *)" IDC_RADIO_SKRK (%d  " , IsDlgButtonChecked(   IDC_RADIO_SKRK  )  );
	//	mDebug.CDebugPut((char *)" IDC_RADIO_SA2 (%d  " , IsDlgButtonChecked(   IDC_RADIO_SA2  )  );
	//	mDebug.CDebugPut((char *)" IDC_RADIO_SA3 (%d  " , IsDlgButtonChecked(   IDC_RADIO_SA3  )  );
	//	mDebug.CDebugPut((char *)" IDC_RADIO_SP5 (%d  " , IsDlgButtonChecked(   IDC_RADIO_SP5  )  );
	mCurrentCheck =0;
	if (  IsDlgButtonChecked(   IDC_RADIO_SBT8  )  )  mCurrentCheck = IDC_RADIO_SBT8;
	if (  IsDlgButtonChecked(   IDC_RADIO_SBT9  )  )  mCurrentCheck  = IDC_RADIO_SBT9;
	if (  IsDlgButtonChecked(   IDC_RADIO_SKRK  )  )  mCurrentCheck = IDC_RADIO_SKRK;
	if (  IsDlgButtonChecked(   IDC_RADIO_SA2  )  )  mCurrentCheck = IDC_RADIO_SA2;
	if (  IsDlgButtonChecked(   IDC_RADIO_SA3  )  )  mCurrentCheck = IDC_RADIO_SA3;
	if (  IsDlgButtonChecked(   IDC_RADIO_SP5  )  )  mCurrentCheck = IDC_RADIO_SP5;
	if (  IsDlgButtonChecked(   IDC_RADIO_SINGL  )  )  mCurrentCheck = IDC_RADIO_SINGL;
	if (  IsDlgButtonChecked(   IDC_RADIO_NORBG  )  )  mCurrentCheck = IDC_RADIO_NORBG;
	if (  IsDlgButtonChecked(   IDC_RADIO_NORBG2  )  )  mCurrentCheck = IDC_RADIO_NORBG2;
 

 	ccode1 =  GetColorCode ( &m_combo_vagon1 );
	ccode2 =  GetColorCode ( &m_combo_vagon2 );
	ccode3 =  GetColorCode ( &m_combo_vagon3 );
	ccode4 =  GetColorCode ( &m_combo_vagon4 );
	ccode5 =  GetColorCode ( &m_combo_vagon5 );

	CString Cs; 
	m_edit_width.GetWindowTextA(Cs);
	mWidth =   atoi(Cs);

	m_edit_lineid.GetWindowTextA(Cs);
	mLineId =   atoi(Cs);


	CDialogEx::OnOK();
}


 
