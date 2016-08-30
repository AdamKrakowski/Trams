#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTramsContr dialog

class CTramsContr : public CDialogEx
{
	DECLARE_DYNAMIC(CTramsContr)

public:
	CTramsContr(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTramsContr();

	BOOL Create( int selId  );
	CWnd* m_pParent;
	void Update(int selId );

// Dialog Data
	enum { IDD = IDD_DIALOG_CNTR_TRAINS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void  ReloadList( int iId );

	int initialId;
	int m_takeControl;
	int m_goback;
	int m_stop;
	int m_filter;

	void  CreateControlList( int iforce );
	void  UpdateControlPanel( CTramTrainVagons *pv );
	void  DisplayTimeOut( CTramTrainVagons *pv );
	void  UpdateTramInfoPanel( );
	void  UpdateStatusForList( );
	CString UpdateTramMoveStatus( CTramTrainVagons *pv  );
	int  mCurItemSelected ;
	int  mCurTrainId;
	CTramTrainVagons *mCurTrainObjectPointer;

	void  SelectListItem( int iforce );
	void UpdateSelectedTramInfo();
	void SelectActiveTram( int selId );

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list_trams;
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnBnClickedButtonDelete();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_edit_lineid;
	afx_msg void OnBnClickedButtonUpdate();
	afx_msg void OnBnClickedButtonUplineid();
	CEdit m_edit_linefilter;
	afx_msg void OnBnClickedRadioTakecntr();
	CButton m_radio_takecontrol;
	afx_msg void OnBnClickedRadioStop();
	CButton m_radio_stop;
	CButton m_radio_goback;
	afx_msg void OnBnClickedRadioBack();
	afx_msg void OnLbnDblclkListTrams();
	CEdit m_edittimeout;
	afx_msg void OnBnClickedRadioCleartm();
	CListCtrl m_list_control;
	afx_msg void OnLvnItemchangedListControl(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit m_edit_idro;
	CEdit m_edit_lnro;
	CEdit m_edit_stro;
//	afx_msg void OnLvnBeginScrollListControl(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnLvnEndScrollListControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawListControl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListControl(NMHDR *pNMHDR, LRESULT *pResult);
};
