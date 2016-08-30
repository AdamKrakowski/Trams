#pragma once
#include "afxwin.h"


// CSemControl dialog

class CSemControl : public CDialogEx
{
	DECLARE_DYNAMIC(CSemControl)

public:
	CSemControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSemControl();

	BOOL Create( CObjControls *p);
	CWnd* m_pParent;
	void Update(CObjControls *p);

	CObjControls *mMyObjectPtr;

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_SEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void DisplayData();
	void Invalidate();
	void VerifyPointOnLine();

	BOOL  MonoHasChanged;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	CEdit mCntrId;
	afx_msg void OnBnClickedButtonChangeId();
	afx_msg void OnBnClickedButtonLeft();
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	CEdit m_edit_cntposX;
	CEdit m_edit_cntposY;
	CEdit m_edit_railId;
	CEdit m_edit_railPtX;
	CEdit m_edit_railPtY;
	//CEdit m_edit_railEP;
	afx_msg void OnBnClickedButtonUpdgroup();
	CEdit m_edit_group;
	afx_msg void OnBnClickedButtonTo1();
	afx_msg void OnBnClickedButtonTo0();
	int m_edit_timeout;
	CEdit m_edit_tm;
	CButton m_check_mono;
	afx_msg void OnBnClickedCheckMono();
};
