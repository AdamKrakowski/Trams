#pragma once


// CViewContr view

class CViewContr : public CScrollView
{
	DECLARE_DYNCREATE(CViewContr)

protected:
	CViewContr();           // protected constructor used by dynamic creation
	virtual ~CViewContr();

	void OnDrawBgn(   CDC* pDC  );
	void CViewContr::OnDrawNet(   HDC hdc );
	void CViewContr::OnDrawNetSelection(   CDC* pDC );
	void CViewContr::OnDrawNetSelectionTemp(   CDC* pDC );
	void CViewContr::OnDrawRemoteNetSelection(   CDC* pDC );

	HDC hdcMem;       // contente of the memory compatible bitmap
	HBITMAP bitmap;   // memory bitmap
	BOOL IsBitmap;

 
	int m_mouse_move;

	CRect mSelRect;
	CRect mMoveRect;
	CRect mOldRect;

public:
	
	CTrainWorldDoc* GetDocument() const;
	void DocToClient(CRect& rect);
	void ClientToDoc(CPoint& point);
	void ClientToDoc(CRect& rect);
	void DocToClient(CPoint& point);




	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


#ifndef _DEBUG  // debug version in TrainWorldView.cpp
inline CTrainWorldDoc* CViewContr::GetDocument() const
   { return reinterpret_cast<CTrainWorldDoc*>(m_pDocument); }
#endif