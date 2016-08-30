// EditStop.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"
///
#include "StdTrainDef.h"
#include "TrainObjects.h"
///
#include "SwitchControl.h"

#include "EditStop.h"
#include "afxdialogex.h"

 

 

// CSwitchControl dialog


#include "TrainWorldDoc.h"
#include "TrainWorldView.h"
 
 
#include "Debug.h"
extern CDebug mDebug;

extern CDebugGraphics mCDebugGraphics;
extern CObjRailsColl  mCObjRailsColl;
extern CObjNames mObjNames;

// CEditStop dialog

IMPLEMENT_DYNAMIC(CEditStop, CDialogEx)

CEditStop::CEditStop(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditStop::IDD, pParent)
{
		m_pParent = pParent;
}

BOOL CEditStop::Create(CObjControls *p)
{
	 mMyObjectPtr =p;  //CObjControls * 

///mDebug.CDebugPut((char *)" Create  ");
	return CDialog::Create(CEditStop::IDD, m_pParent);
}


CEditStop::~CEditStop()
{
}

void CEditStop::Update( CObjControls *p)
{
	mMyObjectPtr =p;
	DisplayData();

}


void CEditStop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STOP_ID0, mStopId);
	DDX_Control(pDX, IDC_EDIT_CNTPOSX, m_edit_cntposX);
	DDX_Control(pDX, IDC_EDIT_CNTPOSY, m_edit_cntposY);
	DDX_Control(pDX, IDC_EDIT_RAIL_ID, m_edit_railId);
	DDX_Control(pDX, IDC_EDIT_RAILPTX_ID, m_edit_railPtX);
	DDX_Control(pDX, IDC_EDIT_RAILPTY_ID, m_edit_railPtY);
	//	DDX_Control(pDX, IDC_EDIT_EP_ID, m_edit_railEP);
	DDX_Control(pDX, IDC_EDIT_GROUP_ID, m_edit_group);
	DDX_Control(pDX, IDC_EDIT_TIMEOUT, m_edit_timeout);
	DDX_Control(pDX, IDC_EDIT_TEXTID, m_edit_textid);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_edit_text);
}

 

void CEditStop::DisplayData()
{
	CString Cs0;
	Cs0.Format("%d", mMyObjectPtr->GetControlID());
	mStopId.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailPtrId());
	m_edit_railId.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailControlPoint().x);
	m_edit_railPtX.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetRailControlPoint().y);
	m_edit_railPtY.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetCenterPoint().x);
	m_edit_cntposX.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetCenterPoint().y);
	m_edit_cntposY.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetGroupId());
	m_edit_group.SetWindowTextA(Cs0);

	Cs0.Format("%d", mMyObjectPtr->GetTimeOut() );
	m_edit_timeout.SetWindowTextA(Cs0);

	int textid  = mMyObjectPtr->GetTextId() ;
	Cs0.Format("%d", textid );
	m_edit_textid.SetWindowTextA(Cs0);
	 
	if ( textid > 0)
	{
	char p[80];
	if ( mObjNames.GetName( textid , 0 , p ) > 0 )
		m_edit_text.SetWindowTextA( p);
	}

	mCDebugGraphics.AddPoint(  GetWhiteColor() , mMyObjectPtr->GetRailControlPoint() );
	Invalidate();

}


BEGIN_MESSAGE_MAP(CEditStop, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_ID, &CEditStop::OnBnClickedButtonChangeId)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CEditStop::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CEditStop::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CEditStop::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CEditStop::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_UPDGROUP, &CEditStop::OnBnClickedButtonUpdgroup)
	ON_BN_CLICKED(IDC_BUTTON_TO1, &CEditStop::OnBnClickedButtonTo1)
	ON_BN_CLICKED(IDC_BUTTON_TO0, &CEditStop::OnBnClickedButtonTo0)
	ON_BN_CLICKED(IDC_BUTTON_UPDTEXT, &CEditStop::OnBnClickedButtonUpdtext)
END_MESSAGE_MAP()


// CEditStop message handlers
void CEditStop::VerifyPointOnLine()
{
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	if ( px != NULL )
	{
		CMyPoint  mp( (float)mMyObjectPtr->GetRailControlPoint().x , (float)mMyObjectPtr->GetRailControlPoint().y);	

				// change this to detect such cases
		int igetd = GetDistanceOfPointFromRail(  px , mp );
		//float dis =  (float)igetd;
		if ( igetd < 0 )
		{
			CString Cs;
			Cs.Format("Invalid control point [err=%d] - check limits" ,-igetd );
			AfxMessageBox(Cs);
		}

		if ( igetd == 2 )  // out of lenght can be corrected
		{
				AfxMessageBox("Invalid control point - fixing ");
				//CMyPoint  mpc( mMyObjectPtr->GetCenterPoint().x , mMyObjectPtr->GetCenterPoint().y);
				//CPoint pt =  GetPointOnRail (  px , mpc ); 

				mDebug.CDebugPut((char *)"Invalid control {idcnt:%d} point:ildId:%d NewId:%d ", mMyObjectPtr->GetControlID() ,mMyObjectPtr->GetRailPtrId() , px->GetRailId()  );
				
				if ( mMyObjectPtr->GetRailPtrId() != px->GetRailId() )
				{
				mDebug.CDebugPut((char *)"Invalid control point:Index error "   );
				}
				else
				{
				CPoint pt =  GetPointOnRail (  px , mMyObjectPtr->GetCenterPoint() ); 
				mMyObjectPtr->SetRailControlPoint( pt);
				mMyObjectPtr->SetRailObjectPtr( px);

				}
		}
	}
}

BOOL CEditStop::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	mCDebugGraphics.EnableGraphics( TRUE);
	mCDebugGraphics.ResetStorage();

	VerifyPointOnLine();
	DisplayData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CEditStop::OnClose()
{
	// TODO: Add your message handler code here and/or call default

		mCDebugGraphics.EnableGraphics( FALSE );

((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_STOP , 0 , NULL ) ; 

	CDialogEx::OnClose();
}


void CEditStop::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	mCDebugGraphics.EnableGraphics( FALSE );

	CString Cs; 
	m_edit_timeout.GetWindowTextA(Cs);
	mMyObjectPtr->SetTimeOut( atoi(Cs)) ;
 
	m_edit_textid.GetWindowTextA(Cs);
	int textid = atoi(Cs) ;
	mMyObjectPtr->SetTextId(textid );
	 
	((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_STOP , 0 , NULL ) ; 

	CDialogEx::OnOK();
}

//GetRailPtrId
void CEditStop::OnBnClickedButtonChangeId()
{
	CString Cs;
	m_edit_railId.GetWindowTextA(Cs);
	mMyObjectPtr->SetRailPtrId(atoi(Cs));

		//  add this
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());

	if ( px != NULL )
	{
		mMyObjectPtr->SetRailObjectPtr( px);
		CPoint pt =  GetPointOnRail (  px , mMyObjectPtr->GetCenterPoint() ); 
		mMyObjectPtr->SetRailControlPoint( pt);
		mMyObjectPtr->SetRailObjectPtr( px);
		VerifyPointOnLine();
	}
}


void CEditStop::OnBnClickedButtonLeft()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x -4 ,  mMyObjectPtr->GetCenterPoint().y   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CEditStop::OnBnClickedButtonRight()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x + 4 ,  mMyObjectPtr->GetCenterPoint().y   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CEditStop::OnBnClickedButtonUp()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x  ,  mMyObjectPtr->GetCenterPoint().y -4   );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CEditStop::OnBnClickedButtonDown()
{
	CPoint pt( mMyObjectPtr->GetCenterPoint().x  ,  mMyObjectPtr->GetCenterPoint().y + 4  );
	mMyObjectPtr->SetCenterPoint( pt);
	DisplayData();
	Invalidate();
}


void CEditStop::Invalidate()
{
((CTrainWorldView*)m_pParent)->SwitchDialogMessage( INVALIDATE_MAIN , 0 , NULL ) ; 
}

void CEditStop::OnBnClickedButtonUpdgroup()
{
	CString Cs; 
	m_edit_group.GetWindowTextA(Cs);
	mMyObjectPtr->SetGroupId( (WORD) atoi(Cs) ); 
	DisplayData();
}


void CEditStop::OnBnClickedButtonTo1()
{
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	if ( px != NULL )
	{
		if ( GetDistance( px->GetPoint(1),mMyObjectPtr->GetRailControlPoint() ) > 5)	
			if ( px->GetObjectType() == ObjStraightRail  )
			{
				CMyPoint  pt = GetPointFmStart( mMyObjectPtr->GetRailControlPoint() , px->GetPoint(1) ,    (float)4.0 );
				mMyObjectPtr->SetRailControlPoint( pt);
				DisplayData();
				Invalidate();
			}
	}
}


void CEditStop::OnBnClickedButtonTo0()
{
	CObjRail *px = mCObjRailsColl.GetRailObjPtrByIdIndex( mMyObjectPtr->GetRailPtrId());
	if ( px != NULL )
	{
		if ( GetDistance( px->GetPoint(0),mMyObjectPtr->GetRailControlPoint() ) > 5)	
			if ( px->GetObjectType() == ObjStraightRail  )
			{
				CMyPoint  pt = GetPointFmStart( mMyObjectPtr->GetRailControlPoint() , px->GetPoint(0) ,    (float)4.0 );
				mMyObjectPtr->SetRailControlPoint( pt);
				DisplayData();
				Invalidate();
			}
	}
}


void CEditStop::OnBnClickedButtonUpdtext()
{
 
	CString Cs; 
	m_edit_textid.GetWindowTextA(Cs);
	int textid = atoi(Cs) ;

	char p[80];
	if ( mObjNames.GetName( textid , 0 , p ) > 0 )
		m_edit_text.SetWindowTextA( p);
}
