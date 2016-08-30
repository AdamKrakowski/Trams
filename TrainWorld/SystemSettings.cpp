// SystemSettings.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"
#include "SystemSettings.h"
#include "afxdialogex.h"

#include "StdTrainDef.h"
#include "TrainObjects.h"

#include "Debug.h"
extern CDebug mDebug;


// CSystemSettings dialog

extern CSystem  mSystem;

IMPLEMENT_DYNAMIC(CSystemSettings, CDialogEx)

CSystemSettings::CSystemSettings(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSettings::IDD, pParent)
 
{

}

CSystemSettings::~CSystemSettings()
{
}
 


void CSystemSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INI_TIME, m_edit_initime);
	DDX_Control(pDX, IDC_EDIT_INI_TIMESPAN, m_edit_initimespan);
	DDX_Control(pDX, IDC_EDIT_LAUNCH_RAIL, m_edit_launchrail);
	DDX_Control(pDX, IDC_COMBO_SIMSPEED, m_combo_simspeed);
	DDX_Control(pDX, IDC_EDIT_SIM_DIV, m_edit_simdivisor);
	DDX_Control(pDX, IDC_EDIT_SIM_STEP, m_edit_simstep);
	DDX_Control(pDX, IDC_EDIT_LNIGHTMODE, m_edit_nightmode);
	DDX_Control(pDX, IDC_EDIT_LATEMIN, m_edit_latelookback);
	DDX_Control(pDX, IDC_RADIO_TESTMODE, m_radio_test_enable);
	DDX_Control(pDX, IDC_RADIO_RAILSVISIBLE, m_radio_rail_visible);
	DDX_Control(pDX, IDC_RADIO_TRAMSAVING, m_radio_tram_save_enable);
	DDX_Control(pDX, IDC_EDIT_SPDIDX1, m_edit_spdidx1);
	DDX_Control(pDX, IDC_EDIT_SPDIDX2, m_edit_spdidx2);
	DDX_Control(pDX, IDC_EDIT_CUR_TIME, m_edit_curtime);
	DDX_Control(pDX, IDC_RADIO_TRAMSCHDIS, m_check_schdisable);
}


BEGIN_MESSAGE_MAP(CSystemSettings, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_TESTMODE, &CSystemSettings::OnBnClickedRadioTestmode)
	ON_BN_CLICKED(IDC_RADIO_RAILSVISIBLE, &CSystemSettings::OnBnClickedRadioRailsvisible)
	ON_BN_CLICKED(IDC_RADIO_TRAMSAVING, &CSystemSettings::OnBnClickedRadioTramsaving)
	ON_BN_CLICKED(IDC_RADIO_TRAMSCHDIS, &CSystemSettings::OnBnClickedRadioTramschdis)
END_MESSAGE_MAP()


// CSystemSettings message handlers


BOOL CSystemSettings::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_combo_simspeed.InsertString(0,"50 msec" );
	m_combo_simspeed.InsertString(1,"100 msec" );
	m_combo_simspeed.InsertString(2,"150 msec" );
	m_combo_simspeed.InsertString(3,"200 msec" );

	m_combo_simspeed.SetCurSel( mSystem.m_SimSpeed);

	CString Cs; 
	Cs.Format("%d",mSystem.m_LaunchRail);
	m_edit_launchrail.SetWindowTextA(Cs);

	Cs.Format("%d",mSystem.m_SimDivisor);
	m_edit_simdivisor.SetWindowTextA(Cs);

	Cs.Format("%d",mSystem.m_SimStep);
	m_edit_simstep.SetWindowTextA(Cs);

	Cs.Format("%d",mSystem.m_LookBackDelay);
	m_edit_latelookback.SetWindowTextA(Cs);

	Cs.Format("%d",mSystem.m_SpeedIndexLimit1);
	m_edit_spdidx1.SetWindowTextA(Cs);

	Cs.Format("%d",mSystem.m_SpeedIndexLimit2);
	m_edit_spdidx2.SetWindowTextA(Cs);


	Cs.Format("%02d:%02d",mSystem.m_NewSimTime.GetHour(), mSystem.m_NewSimTime.GetMinute() );
	m_edit_initime.SetWindowTextA(Cs);

	Cs.Format("%02d:%02d",mSystem.m_TimeSpan.GetHours(), mSystem.m_TimeSpan.GetMinutes() );
	m_edit_initimespan.SetWindowTextA(Cs);

	Cs.Format("%02d:%02d",mSystem.m_SimTime.GetHour() , mSystem.m_SimTime.GetMinute() );
	m_edit_curtime.SetWindowTextA(Cs);

	Cs.Format("%02d:%02d",mSystem.m_NightModeStarts/60 , mSystem.m_NightModeStarts%60 ); 
	m_edit_nightmode.SetWindowTextA(Cs);

	m_radio_test_enable.SetCheck( mSystem.m_SimTestMode );
	m_radio_rail_visible.SetCheck( mSystem.m_SimShowRail );
	m_radio_tram_save_enable.SetCheck(mSystem.m_SaveTrams);

	 m_check_schdisable.SetCheck(mSystem.m_schenable);
  
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSystemSettings::OnOK()
{

	CString Cs; 
	m_edit_launchrail.GetWindowTextA(Cs);	
	mSystem.m_LaunchRail = atoi(Cs);
 
	mSystem.m_SimSpeed = m_combo_simspeed.GetCurSel();
 
	m_edit_simdivisor.GetWindowTextA(Cs);	
	mSystem.m_SimDivisor = atoi(Cs); 
 
 	m_edit_simstep.GetWindowTextA(Cs);	
	mSystem.m_SimStep = atoi(Cs); 

 	m_edit_latelookback.GetWindowTextA(Cs);	
	mSystem.m_LookBackDelay = atoi(Cs); 

	m_edit_spdidx1.GetWindowTextA(Cs);
	mSystem.m_SpeedIndexLimit1 =atoi(Cs); 

	m_edit_spdidx2.GetWindowTextA(Cs);
	mSystem.m_SpeedIndexLimit2 =atoi(Cs); 
 
	m_edit_curtime.GetWindowTextA(Cs);
	
	int itm = BrowseTime(   Cs );
	mSystem.m_SimTime = CTime( 2014,1,1, itm/60 ,itm%60 ,0,0);  
							
	m_edit_nightmode.GetWindowTextA(Cs);	
	mSystem.m_NightModeStarts= BrowseTime(   Cs );
 
	mSystem.m_SimTestMode = m_radio_test_enable.GetCheck();
	mSystem.m_SimShowRail = m_radio_rail_visible.GetCheck();
	mSystem.m_SaveTrams   = m_radio_tram_save_enable.GetCheck();
	mSystem.m_schenable =  m_check_schdisable.GetCheck();;
	 
	CDialogEx::OnOK();
}


void CSystemSettings::OnBnClickedRadioTestmode()
{
	if ( m_radio_test_enable.GetCheck() == TRUE ) m_radio_test_enable.SetCheck(FALSE);
	else m_radio_test_enable.SetCheck(TRUE);
}


void CSystemSettings::OnBnClickedRadioRailsvisible()
{
	if ( m_radio_rail_visible.GetCheck() == TRUE ) m_radio_rail_visible.SetCheck(FALSE);
	else m_radio_rail_visible.SetCheck(TRUE);
}


void CSystemSettings::OnBnClickedRadioTramsaving()
{
	if ( m_radio_tram_save_enable.GetCheck() == TRUE ) m_radio_tram_save_enable.SetCheck(FALSE);
	else m_radio_tram_save_enable.SetCheck(TRUE);
}


void CSystemSettings::OnBnClickedRadioTramschdis()
{
	if ( m_check_schdisable.GetCheck() == TRUE ) m_check_schdisable.SetCheck(FALSE);
	else m_check_schdisable.SetCheck(TRUE);
 
}
