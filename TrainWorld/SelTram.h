#pragma once
#include "afxwin.h"


// CSelTram dialog
class CTramModelDef;

class CSelTram : public CDialogEx
{
	DECLARE_DYNAMIC(CSelTram)

public:
	CSelTram(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelTram();

	int GetSelectedTramId();
	int GetShape( CTramModelDef *ptm  );
	int mLineId;

// Dialog Data
	enum { IDD = IDD_DIALOG_SEL_TRAM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	int  mCurrentCheck;

	DWORD ccode1 ;
	DWORD ccode2 ;
	DWORD ccode3 ;
	DWORD ccode4 ;
	DWORD ccode5 ;
	int mWidth;
 

	void LoadComboWithColors( CComboBox *p );
	DWORD GetColorCode ( CComboBox *p );
 

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_combo_vagon1;
	CComboBox m_combo_vagon2;
	CComboBox m_combo_vagon3;
	CComboBox m_combo_vagon4;
	CComboBox m_combo_vagon5;
	CComboBox m_combo_vagon6;
	CComboBox m_combo_vagon7;
	CComboBox m_combo_vagon8;
	CComboBox m_combo_vagon9;
	CEdit m_edit_width;
	virtual BOOL OnInitDialog();
	CEdit m_edit_lineid;
};
