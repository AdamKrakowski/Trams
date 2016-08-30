
// TrainWorldView.h : interface of the CTrainWorldView class
//

#pragma once


#define  SELECT_NONE  0
#define  SELECT_POINT 1
#define  SELECT_RECT  2
#define  HANDLE_BEND  3

#define ADDMODE_NONE 0
#define ADDMODE_STRIGHT		1
#define ADDMODE_BEND_LEFT	2
#define ADDMODE_BEND_RIGHT	3
#define ADDMODE_TERMINATOR	4
#define ADDMODE_DB_STRIGHT	5
#define ADDMODE_STOP		6
#define ADDMODE_SWITCH		7
#define ADDMODE_SEM			8

#define ADDMODE_CONT_GRP	9
#define ADDMODE_STOP_GRP	10

#define  MODE_NONE  0
#define  MODE_RUN   1
#define  MODE_ADD_OBJECT  2
#define  MODE_EDIT_OBJECT  3

#define THIS_VIEW_TIMER  102
#define THIS_VIEW_TIMER_INTERVAL 100

#include "SystemValues.h"

class CObjControls;
class CObjRail;

class CTrainWorldView : public CView
{
protected: // create from serialization only
	CTrainWorldView();
	DECLARE_DYNCREATE(CTrainWorldView)

	int  iSelect;				// how to select by point or rectangle
	int  iAddMode;				// what to add 
	int  iModeOper;				// operation mode
	BOOL bActiveObjects;		// there are selected object

	BOOL MouseStatePressed ;
	CPoint Last_Point_DC;		// the point where mouse was last time - dc ccordinates
	CPoint TotalSpaceEndPoint;  //  determine size of the total space  (0,0,1024*16,1024*16 here)

	CRect  BmpSizeWindow;		// position of the window size(0,0,1024,1024) for the 1024pixx1024 library bit maps  - only to left used !!!  

	BOOL IsBitmap;


	HDC hdcMem;       // contente of the memory compatible bitmap
	HBITMAP bitmap;   // memory bitmap

	HDC hdcMemTmp;       // contente of the memory compatible bitmap
	HBITMAP bitmapTmp;   // memory bitmap

	//HDC hdcMemDbl;
	//HBITMAP bitmapDbl;

	HDC hdcTmpMem[NBR_OF_BUFFERS];       // contente of the memory compatible bitmap
	HBITMAP bitTmpmap[NBR_OF_BUFFERS];   // memory bitmap

	int  current_size_x;
	int  current_size_y;

	void CTrainWorldView::ReloadMemoryBitmap( CRect *updRec );
	void CTrainWorldView::ScrollMapsInRunMode(CPoint point);
	//void CTrainWorldView::SendSizeMsgToControl();


	//CRect testRect;
	//int   testRectEnable;

	int m_divider20;

     CTime  tm_simulation_time;

 
// Attributes
public:
	CTrainWorldDoc* GetDocument() const;
	//  enable graphics debug
	void  SwitchDialogMessage( int msg , int value, CObject *p ) ;
	void  MoveWindowToTheObject(  int ix , int iy  );

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTrainWorldView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
	void OnDrawBgn(   HDC hdc );
	void OnDrawTracker( HDC hdc);
	void  OnSwitchControlEdit(CObjControls *p);
	void  OnSemControlEdit(CObjControls *p);
	void  OnStopControlEdit(CObjControls *p);
	void  OnRailEdit(CObjRail *p);
	void  OnRailUpdateEdit(CObjRail *p);
	void  OnStopUpdateEdit(CObjControls *p);

	void  CTrainWorldView::OnTramsControl( int selId );
	//void  CTrainWorldView::OnTramsUpdate(  );
 


// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:

	afx_msg void OnEditterainAddstright();
	afx_msg void OnUpdateEditterainAddstright(CCmdUI *pCmdUI);
	afx_msg void OnEditterainAddbend();
	afx_msg void OnUpdateEditterainAddbend(CCmdUI *pCmdUI);
	afx_msg void OnEditterainAddterminator();
	afx_msg void OnUpdateEditterainAddterminator(CCmdUI *pCmdUI);
	afx_msg void OnSelPoint();
	afx_msg void OnUpdateSelPoint(CCmdUI *pCmdUI);
	afx_msg void OnSelRect();
	afx_msg void OnUpdateSelRect(CCmdUI *pCmdUI);

	afx_msg void OnTrackMove();
	afx_msg void OnUpdateTrackMove(CCmdUI *pCmdUI);
	afx_msg void OnTrackDel();
	afx_msg void OnUpdateTrackDel(CCmdUI *pCmdUI);
	afx_msg void OnTrackShow();
	afx_msg void OnUpdateTrackShow(CCmdUI *pCmdUI);	
	afx_msg void OnTracksSnap();
	afx_msg void OnUpdateTracksSnap(CCmdUI *pCmdUI);
	afx_msg void OnTrackDelSel();
	afx_msg void OnUpdateTrackDelSel(CCmdUI *pCmdUI);
	afx_msg void OnTrackShowConn();
	afx_msg void OnUpdateTrackShowConn(CCmdUI *pCmdUI);
	afx_msg void OnAddDblTracks();
	afx_msg void OnEditterainDblStright();
	afx_msg void OnUpdateEditterainDblStright(CCmdUI *pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnModeRun();
	afx_msg void OnUpdateModeRun(CCmdUI *pCmdUI);
	afx_msg void OnModeEditInf();
	afx_msg void OnUpdateModeEditInf(CCmdUI *pCmdUI);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnToolsCnvbmptojpg();
	afx_msg void OnUpdateToolsCnvbmptojpg(CCmdUI *pCmdUI);
	afx_msg void OnModeEditTrains();
	afx_msg void OnUpdateModeEditTrains(CCmdUI *pCmdUI);
	afx_msg void OnEditterainAddbendleft();
	afx_msg void OnUpdateEditterainAddbendleft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRunStart(CCmdUI *pCmdUI);
	afx_msg void OnRunStart();
	afx_msg void OnUpdateRunStop(CCmdUI *pCmdUI);
	afx_msg void OnRunStop();
	afx_msg void OnUpdateRunStep(CCmdUI *pCmdUI);
	afx_msg void OnRunStep();
	afx_msg void OnUpdateRunRevers(CCmdUI *pCmdUI);
	afx_msg void OnRunRevers();
	afx_msg void OnUpdateAddTram(CCmdUI *pCmdUI);
	afx_msg void OnAddTram();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUpdateEditUndoRail(CCmdUI *pCmdUI);
	afx_msg void OnEditUndoRail();
	afx_msg void OnUpdateEditUndoCtrl(CCmdUI *pCmdUI);
	afx_msg void OnEditUndoCtrl();
	afx_msg void OnAddSem();
	afx_msg void OnUpdateAddSem(CCmdUI *pCmdUI);
	afx_msg void OnContGroup();
	afx_msg void OnUpdateContGroup(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTrackFind(CCmdUI *pCmdUI);
	afx_msg void OnTrackFind();
	afx_msg void OnUpdateEditUndotram(CCmdUI *pCmdUI);
	afx_msg void OnEditUndotram();
	afx_msg void OnUpdateEditUndocontrolgroup(CCmdUI *pCmdUI);
	afx_msg void OnEditUndocontrolgroup();
	afx_msg void OnUpdateAddStopGrp(CCmdUI *pCmdUI);
	afx_msg void OnAddStopGrp();
	afx_msg void OnTramsControlCenter();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFindTrack();
	afx_msg void OnFindStop();
	afx_msg void OnFindEndstopbyname();

	afx_msg void OnRunStopfind();
};

#ifndef _DEBUG  // debug version in TrainWorldView.cpp
inline CTrainWorldDoc* CTrainWorldView::GetDocument() const
   { return reinterpret_cast<CTrainWorldDoc*>(m_pDocument); }
#endif

