#pragma once
#include "afxwin.h"


// CRailEdit dialog

class CRailEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CRailEdit)

public:
	CRailEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRailEdit();

	BOOL Create( CObjRail *p);
	void Update( CObjRail *p);
	CWnd* m_pParent;

	CObjRail *mMyObjectPtr;   

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_RAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void DisplayRailData();

	DECLARE_MESSAGE_MAP()
public:
	CEdit mRailId;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	CEdit m_edit_ep00;
	CEdit m_edit_ep10;
	CEdit m_edit_ep01;
	CEdit m_edit_ep11;
	CEdit m_edit_ep0X;
	CEdit m_edit_ep0Y;
	CEdit m_edit_ep1X;
	CEdit m_edit_ep1Y;
	CEdit m_edit_cpX;
	CEdit m_edit_cpY;
	afx_msg void OnBnClickedButtonUpdate();
	CButton m_check_launch;
	afx_msg void OnBnClickedButtonUppoints();
	CEdit m_edit_info1;
	CEdit m_edit_type;
 
 
	CButton m_check_underground;
	afx_msg void OnBnClickedCheckUndergnd();
};
