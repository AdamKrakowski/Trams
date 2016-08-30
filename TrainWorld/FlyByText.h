#pragma once


// CFlyByText

class CFlyByText : public CWnd
{
	DECLARE_DYNAMIC(CFlyByText)

public:
	CFlyByText();
	virtual ~CFlyByText();

	void SetTipText( CPoint  cp , CString Cs );

protected:

	CString mCString;
	int mTextToDisplay;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


