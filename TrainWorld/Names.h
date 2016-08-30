#pragma once
#include "afxwin.h"


// CNames dialog

class CNames : public CDialogEx
{
	DECLARE_DYNAMIC(CNames)

public:
	CNames(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNames();

// Dialog Data
	enum { IDD = IDD_DIALOG_NAMES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void CNames::LoadRecords();

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listbox_names;
	CEdit m_edit_name;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnLbnSelchangeListNames();
	afx_msg void OnLbnDblclkListNames();
	virtual BOOL OnInitDialog();
};
