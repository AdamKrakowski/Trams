#pragma once
#include "afxwin.h"


// CSwitchControl dialog
class CObjControls;

class CSwitchControl : public CDialogEx
{
	DECLARE_DYNAMIC(CSwitchControl)

public:
	CSwitchControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSwitchControl();

	BOOL Create( CObjControls *p);
	CWnd* m_pParent;
	void Update(CObjControls *p);

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_SWITCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CObjControls *mMyObjectPtr;

	CObjRail *p_main;
	CObjRail *p_m0;
	CObjRail *p_m1;
	int      id_main;
	int      id_m0;
	int      id_m1;
	int		 i_mept;
	int		 i_virt_mept;

	void DisplayData();
	void DisplayStatus();
	void MarkLineStatus();
	void Invalidate();
	void Verify();

	 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CEdit mSwitch0;
	CEdit mSwitch1;
	afx_msg void OnBnClickedCheckTest();
	afx_msg void OnBnClickedButtonTestswitch();
	CEdit mSwitchCur;
	afx_msg void OnBnClickedButtonSwap();
	CButton mTestMode;
	CEdit m_edit_cntId;
	CEdit m_edit_cntposX;
	CEdit m_edit_cntposY;
	CEdit m_edit_railId;
	CEdit m_edit_railEP;
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedButtonChangeId();
};
