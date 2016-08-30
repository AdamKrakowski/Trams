
// TrainWorldDoc.h : interface of the CTrainWorldDoc class
//

#include "dibapi.h"

 

#pragma once

#define FILE_FORMAT_BMP  0
#define FILE_FORMAT_JPG  1
#define FILE_FORMAT_GIF  2
// both file format use
#define FILE_FORMAT_BJG  3

#define USE_FORMAT_BMP  0
#define USE_FORMAT_JPG  1
#define USE_FORMAT_GIF  2
#define USE_FORMAT_BJG  3

#define USE_DIB_IFACE   0
#define USE_CIM_IFACE   1


class CTrainWorldDoc : public CDocument
{
protected: // create from serialization only
	CTrainWorldDoc();
	DECLARE_DYNCREATE(CTrainWorldDoc)

// Attributes
public:
	 

// Operations
public:
	void Interface_RegisterViewWindow( HWND hWnd ); 
	void Interface_RegisterCtrlWindow( HWND hWnd );
	void Interface_SendMessageToView(int iuser,int ix,int lp);
	void Interface_SendMessageToCntr(int iuser,int ix,int lp);
	// update the oposite view
	void Interface_UpdateTrainView(  CView *pv, int func , CRect *pr );
	void Interface_UpdateControlView(CView *pv, int func , CRect *pr );
	// which window supposed to get focus at start up
	void Interface_RegisterActiveView( CView *pv );
	// setup the data base structure
	void Interface_SetupDataBase(  HDC  *hdcTmpMem );  
	// main exported interface to data base manager
	BOOL Export_LoadDataBaseBlock ( int nbr , HDC hdcMem ,CRect *prcDest );
	//  public called from control view
	BOOL Interface_LoadAuxImage( HDC hdcMem , CRect AuxRect ) ;
    // called from train view
	BOOL Interface_UpdateShadowImage( HDC hdcMem , int des_off_x, int des_off_y , CRect rc  ) ;
 
	CTime  GetSimulationStartTime();
	CTimeSpan GetSimulationIncTimeSpan();

	// tools
	void Tool_BMPtoJPGConverstion( HDC hdcMem , HBITMAP bitmap );
    //  debug tools
	void DebugHDC( int id , HDC hdcMem );
	void DebugHDC(  int id , CDC *dc   );
	void DebugCImage(int id , CImage *pim  );

protected:

	CString GetAuxFilePath (int fformat);
	CString GetDataBaseFilePath (int row ,int col ,int fformat);

	BOOL  LoadAuxImageFromBMP( HDC hdcMem  , CRect AuxRect ); 
	BOOL  LoadAuxImageFromJPG( HDC hdcMem  , CRect AuxRect ); 

	BOOL  LoadAuxBitmapFromBMPFile ( HDC hdcMem ,  CRect AuxRect ) ;
	BOOL  LoadAuxBitmapFromJPGFile ( HDC hdcMem ,  CRect AuxRect ) ;

	HDIB GetHDIB();
	HDIB GetAuxHDIB();
 
	//  Loading dib file from data base
	BOOL LoadDIBFile (int nbr);
	BOOL LoadDIBFile (int rw, int cl);
	BOOL LoadDIBFile( CString  filename ); 

	//  Loading the bitmap to memory context
	BOOL LoadDIBBitmap (int nbr , HDC hdcMem, CRect *prcDest );
	BOOL LoadDIBBitmap (int row,int col , HDC hdcMem ,CRect *prcDest );
	BOOL LoadDIBBitmap ( CString filename , HDC hdcMem ,CRect *prcDest );

    // CImage method used
	BOOL SaveAuxImage( HBITMAP bitmap ,int fformat   );

	//  load/save  image  with CImage method
	BOOL LoadImage ( int row,  int col  , HDC hdcMem  );
	BOOL LoadImage ( int row,  int col  , HDC hdcMem , CRect *prcDest );
	BOOL LoadImage ( int nbr , HDC hdcMem ,CRect *prcDest  );

	BOOL SaveImage( int row,  int col  , HBITMAP bitmap , int format );

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CTrainWorldDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HDIB m_hDIB;
	HDIB m_hSmallDIB;
	CSize m_sizeDoc;
	CString mCsHomePath;
	int m_scaledown;
	int SystemDbRead;
	HWND m_view_hWnd;
	HWND m_ctrl_hWnd;
	CString CVersion;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnToolsDebugRails();
	afx_msg void OnUpdateToolsDebugRails(CCmdUI *pCmdUI);
	afx_msg void OnToolsDebugClose();
	afx_msg void OnUpdateToolsDebugClose(CCmdUI *pCmdUI);
	afx_msg void OnToolsDebugOpen();
	afx_msg void OnUpdateToolsDebugOpen(CCmdUI *pCmdUI);
	afx_msg void OnToolsCheckswitches();
	afx_msg void OnToolsFixswitches();
	afx_msg void OnSetupTestmode();
	afx_msg void OnUpdateSetupTestmode(CCmdUI *pCmdUI);
	afx_msg void OnSetupRvisible();
	afx_msg void OnUpdateSetupRvisible(CCmdUI *pCmdUI);
	afx_msg void OnSetupDonotsavetrams();
	afx_msg void OnSetuSetlaunchrail();
	afx_msg void OnUpdateSetupDonotsavetrams(CCmdUI *pCmdUI);
	afx_msg void OnToolsStat();
	afx_msg void OnToolsCheckflt();
	afx_msg void OnManageRoutes();
	afx_msg void OnDelControl();
	afx_msg void OnManageNames();
	afx_msg void OnSystemSettings();
	afx_msg void OnCheckStop();
	afx_msg void OnCheckRails();
};
