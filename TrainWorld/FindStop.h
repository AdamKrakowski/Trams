#pragma once
#include "afxwin.h"


// CFindStop dialog

class CFindStop : public CDialogEx
{
	DECLARE_DYNAMIC(CFindStop)
	int mCurSel;


public:
	CFindStop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFindStop();

	BOOL Create( int selId  );
	CWnd* m_pParent;
	int initialId;

// Dialog Data
	enum { IDD = IDD_DIALOG_FIND_STOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFind();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CListBox m_listbox_names;
	afx_msg void OnLbnDblclkListStopnames();
};
