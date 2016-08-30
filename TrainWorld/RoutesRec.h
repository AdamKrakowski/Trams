#pragma once
#include "afxwin.h"


// CRoutesRec dialog

class CRoutesRec : public CDialogEx
{
	DECLARE_DYNAMIC(CRoutesRec)

public:
	CRoutesRec(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRoutesRec();

// Dialog Data
	enum { IDD = IDD_DIALOG_ROUTES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void CRoutesRec::LoadRecords( int route_id );

	int m_current_route_slection_Id;

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_route_id;
	CEdit m_edit_cntr_id;
	CEdit m_edit_param;
	CListBox m_list_records;
	afx_msg void OnBnClickedButtonBase();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonUpd();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnLbnSelchangeListRecords();
	CEdit m_edit_option;
	afx_msg void OnBnClickedButtonPrint();
};
