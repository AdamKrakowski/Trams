#pragma once
#include "afxwin.h"


// CEditStop dialog

class CEditStop : public CDialogEx
{
	DECLARE_DYNAMIC(CEditStop)

public:
	CEditStop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditStop();

	BOOL Create( CObjControls *p);
	CWnd* m_pParent;
	CObjControls *mMyObjectPtr;

	void Update( CObjControls *p);

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_STOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void DisplayData();
	void Invalidate();
	void VerifyPointOnLine();

	DECLARE_MESSAGE_MAP()
public:
	CEdit mStopId;
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	CEdit m_edit_cntposX;
	CEdit m_edit_cntposY;
	CEdit m_edit_railId;
	CEdit m_edit_railPtX;
	CEdit m_edit_railPtY;
//	CEdit m_edit_railEP;
	afx_msg void OnBnClickedButtonChangeId();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	CEdit m_edit_group;
	afx_msg void OnBnClickedButtonUpdgroup();
	afx_msg void OnBnClickedButtonTo1();
	afx_msg void OnBnClickedButtonTo0();
	CEdit m_edit_timeout;
	CEdit m_edit_textid;
	CEdit m_edit_text;
	afx_msg void OnBnClickedButtonUpdtext();
};
