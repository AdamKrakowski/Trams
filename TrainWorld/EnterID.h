#pragma once
#include "afxwin.h"


// CEnterID dialog

class CEnterID : public CDialogEx
{
	DECLARE_DYNAMIC(CEnterID)

public:
	CEnterID(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEnterID();

	int m_ID_Selected;

// Dialog Data
	enum { IDD = IDD_DIALOG_FINDBYID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CEdit m_edit_enterid;
	virtual BOOL OnInitDialog();
};
