#pragma once
#include "afxwin.h"


// CSystemSettings dialog

class CSystemSettings : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemSettings)

public:
	CSystemSettings(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSystemSettings();

// Dialog Data
	enum { IDD = IDD_DIALOG_SYSSETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_initime;
	CEdit m_edit_initimespan;
	CEdit m_edit_launchrail;
	CComboBox m_combo_simspeed;
	CEdit m_edit_simdivisor;
	CEdit m_edit_simstep;
	CEdit m_edit_nightmode;
	CEdit m_edit_latelookback;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CButton m_radio_test_enable;
	CButton m_radio_rail_visible;
	CButton m_radio_tram_save_enable;
	afx_msg void OnBnClickedRadioTestmode();
	afx_msg void OnBnClickedRadioRailsvisible();
	afx_msg void OnBnClickedRadioTramsaving();
	CEdit m_edit_spdidx1;
	CEdit m_edit_spdidx2;
	CEdit m_edit_curtime;
	afx_msg void OnBnClickedRadioTramschdis();
	CButton m_check_schdisable;
};
