// TramsContr.cpp : implementation file
//

#include "stdafx.h"
#include "TrainWorld.h"
 


#include "StdTrainDef.h"
#include "TrainObjects.h"
 
 #include "TramsContr.h"
#include "afxdialogex.h"

#include "TrainWorldDoc.h"
#include "TrainWorldView.h"
 
#include "Debug.h"
extern CDebug mDebug;

extern CDebugGraphics mCDebugGraphics;
extern CObjRailsColl  mCObjRailsColl;

 

// CTramsContr dialog

IMPLEMENT_DYNAMIC(CTramsContr, CDialogEx)

CTramsContr::CTramsContr(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTramsContr::IDD, pParent)
{
	m_pParent = pParent;
	m_takeControl=0;
	m_goback =0 ;
	m_stop =0;
	m_filter =0;

	mCurItemSelected = -1;
	mCurTrainId = 0;;
	mCurTrainObjectPointer = NULL;
}

CTramsContr::~CTramsContr()
{
}

void CTramsContr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LIST_TRAMS, m_list_trams);
	DDX_Control(pDX, IDC_EDIT_LINE_ID, m_edit_lineid);
	DDX_Control(pDX, IDC_EDIT_LINEFILTER, m_edit_linefilter);
	DDX_Control(pDX, IDC_RADIO_TAKECNTR, m_radio_takecontrol);
	DDX_Control(pDX, IDC_RADIO_STOP, m_radio_stop);
	DDX_Control(pDX, IDC_RADIO_BACK, m_radio_goback);
	DDX_Control(pDX, IDC_EDIT_TIMEOUT, m_edittimeout);
	DDX_Control(pDX, IDC_LIST_CONTROL, m_list_control);
	DDX_Control(pDX, IDC_EDIT_IDRO, m_edit_idro);
	DDX_Control(pDX, IDC_EDIT_LNRO, m_edit_lnro);
	DDX_Control(pDX, IDC_EDIT_STRO, m_edit_stro);
}


BEGIN_MESSAGE_MAP(CTramsContr, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CTramsContr::OnBnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CTramsContr::OnBnClickedButtonDelete)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	//ON_WM_PARENTNOTIFY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CTramsContr::OnBnClickedButtonUpdate)
	ON_BN_CLICKED(IDC_BUTTON_UPLINEID, &CTramsContr::OnBnClickedButtonUplineid)
	ON_BN_CLICKED(IDC_RADIO_TAKECNTR, &CTramsContr::OnBnClickedRadioTakecntr)
	ON_BN_CLICKED(IDC_RADIO_STOP, &CTramsContr::OnBnClickedRadioStop)
	ON_BN_CLICKED(IDC_RADIO_BACK, &CTramsContr::OnBnClickedRadioBack)
	ON_LBN_DBLCLK(IDC_LIST_TRAMS, &CTramsContr::OnLbnDblclkListTrams)
	ON_BN_CLICKED(IDC_RADIO_CLEARTM, &CTramsContr::OnBnClickedRadioCleartm)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_CONTROL, &CTramsContr::OnLvnItemchangedListControl)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_CONTROL, &CTramsContr::OnNMCustomdrawListControl)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONTROL, &CTramsContr::OnNMDblclkListControl)
END_MESSAGE_MAP()


// CTramsContr message handlers

BOOL CTramsContr::Create( int selId  )
{
	initialId = selId;
	return CDialog::Create(CTramsContr::IDD, m_pParent);
}

void CTramsContr::SelectListItem( int iforce )
{
	int sel = mCurItemSelected;
	if ( iforce >= 0 ) sel = iforce;

	m_list_control.SetItem( sel , 0 , LVIF_STATE , NULL , NULL , LVIS_SELECTED | LVIS_FOCUSED , -1 , NULL );
	CRect rc;
	m_list_control.GetItemRect( sel  , &rc ,LVIR_BOUNDS);
	CSize size ( 0 , rc.top -16 );
	m_list_control.Scroll(  size  );


}

CString CTramsContr::UpdateTramMoveStatus( CTramTrainVagons *pv  )
{
	CString Cs;
	if ( pv->GetCurState() == StateRUN )
		Cs  = _T( "Run");
	else 
		{
		if ( pv->GetStopReason() == ObjDet  )
			Cs  = _T( "Wait");
		else
			{
			if ( pv->GetDynTimeOut()  < 100 )
				Cs  = _T( "[Stop]");
			else
				Cs  = _T( "[Loop]");
			}
		}
	return Cs;
}

void CTramsContr::UpdateSelectedTramInfo()
{
	UpdateTramInfoPanel();
	if ( mCurTrainObjectPointer != NULL )
	{
		UpdateControlPanel(mCurTrainObjectPointer );
		DisplayTimeOut( mCurTrainObjectPointer );
	}			 
}


void CTramsContr::CreateControlList( int iforce )
{
	int iitemcount = m_list_control.GetItemCount();
	int tcount = mCObjRailsColl.GetNumberOfTrams();

	if ( (iitemcount != tcount) || ( iforce == 1 ) ) m_list_control.DeleteAllItems();
	else return ;

	int ipos=0;

	for ( int i=0;i<tcount;i++)
	{
		int id = mCObjRailsColl.GetTramId(i );
		if ( id > 0 )  
		{
			CTramTrainVagons *pv =  mCObjRailsColl.FindTrainObjectById(  id    );
			if ( pv != NULL )
			{
				if ( m_filter > 0 ) if ( pv->GetLineId() != m_filter )  continue;

				CString Cs;
				Cs.Format("Id:%3d - Line:%d ", id, pv->GetLineId());
				m_list_control.InsertItem(   ipos , Cs  );
				m_list_control.SetItemData( ipos , id );
				ipos++;
			}
		}
	}
}

void  CTramsContr::UpdateTramInfoPanel( )
{
	if ( mCurTrainObjectPointer != NULL )
	{
			CString Cs;
			Cs.Format("%d", mCurTrainObjectPointer->GetLineId() );
			m_edit_lineid.SetWindowTextA(Cs);
			m_edit_lnro.SetWindowTextA(Cs);
			Cs.Format("%d", mCurTrainId );
			m_edit_idro.SetWindowTextA(Cs); 
			Cs = UpdateTramMoveStatus( mCurTrainObjectPointer );
			m_edit_stro.SetWindowTextA(Cs);
	}
}

void CTramsContr::UpdateControlPanel( CTramTrainVagons *pv )
{

	if ( pv == NULL )
	{
		m_takeControl =0;
		m_radio_takecontrol.SetCheck( FALSE );
		m_stop =0;
		m_radio_stop.SetCheck( FALSE );
		m_goback =0;
		m_radio_goback.SetCheck( FALSE );
		return ;
	}
	
	if ( pv->GetManualControlStatus() == TRUE ) 
		{
			m_radio_takecontrol.SetCheck( TRUE);
			m_takeControl =1;
		}
	else
		{
			m_takeControl =0;
			m_radio_takecontrol.SetCheck( FALSE );
		}


	if ( pv->IsTrainStopped() == TRUE ) 
		{
			m_radio_stop.SetCheck( TRUE);
			m_stop =1;
		}
	else
		{
			m_stop =0;
			m_radio_stop.SetCheck( FALSE );
		}


	if ( pv->IsTrainReversed() == TRUE ) 
		{
			m_radio_goback.SetCheck( TRUE);
			m_goback =1;
		}
	else
		{
			m_goback =0;
			m_radio_goback.SetCheck( FALSE );
		} 

}


void CTramsContr::SelectActiveTram( int selId )
{
    int isel = -1;
	
	if ( selId == 0 )
	{
		isel = m_list_control.GetItemCount()-1;
	}
	else
	{
		CTramTrainVagons *pv =  mCObjRailsColl.FindTrainObjectById(  selId    );
		if ( pv != NULL )
		{
			mCurTrainId = selId;;
			mCurTrainObjectPointer = pv;

			int tcount = m_list_control.GetItemCount();


			for ( int i=0;i<tcount;i++)
				{
					int id = m_list_control.GetItemData( i) ;
					if ( id == selId )
					{
						isel = i;
						break;
					}
				}
		}
	}


	if ( isel >= 0 )
	{
		mCurItemSelected  = isel;
		mCurTrainId = m_list_control.GetItemData( mCurItemSelected );
		mCurTrainObjectPointer =   mCObjRailsColl.FindTrainObjectById(  mCurTrainId  ); 
	}

}


// newly seleted ID is passed
void CTramsContr::Update(int selId )
{
	m_filter = 0;
	m_edit_linefilter.SetWindowTextA("0");

	CreateControlList( 0 );
	UpdateStatusForList();
	SelectActiveTram(  selId );
	SelectListItem( -1 );
	UpdateSelectedTramInfo();
}

void CTramsContr::DisplayTimeOut( CTramTrainVagons *pv )
{
	if ( pv != NULL )
	{
		CString Cs;
		int tm = pv->GetDynTimeOut();
		Cs.Format("%d:%d", tm/320 , (tm%320)>> 5 );   
		m_edittimeout.SetWindowTextA(Cs);
	}
}

void CTramsContr::OnBnClickedButtonFind()   
{
    if ( mCurTrainObjectPointer != NULL )
	{
		CFPoint p1 = mCurTrainObjectPointer->GetHeadPoint();
		((CTrainWorldView*)m_pParent)->MoveWindowToTheObject( (int)p1.x ,  (int)p1.y ) ;
	}
}


void CTramsContr::OnBnClickedButtonDelete() // delete last train
{
	/*
	 
	if ( mCurItemSelected > 0 )
		if ( mCObjRailsColl.DeleteTramById(mCurItemSelected  ) == TRUE )
			ReloadList(0);
			*/
}

 

void CTramsContr::OnOK()
{
	KillTimer( 104 );  
	((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_TRAMS , 0 , NULL ) ; 
	CDialogEx::OnOK();
}
 

//////////////////////////////////////////////////////////////////
//  The function updates only the status of the object

void  CTramsContr::UpdateStatusForList()
{
	int tcount = mCObjRailsColl.GetNumberOfTrams();	
	int ipos=0;
 
	for ( int i=0;i<tcount;i++)
	{
		int id = mCObjRailsColl.GetTramId(i );
		if ( id > 0 )
		{
			CTramTrainVagons *pv =  mCObjRailsColl.FindTrainObjectById( id );
			if ( pv != NULL )
			{
				if ( m_filter > 0 ) if ( pv->GetLineId() != m_filter )  continue;
				CString Cs =  UpdateTramMoveStatus( pv );
 				m_list_control.SetItemText( ipos , 1 ,Cs );
				ipos++;
			}
		}
	}

}

BOOL CTramsContr::OnInitDialog()
{
	CDialogEx::OnInitDialog();

		//m_list_trams.SetHorizontalExtent( 320);
	m_list_control.SetItemCount(256);
	m_list_control.InsertColumn( 0 , "Tram Id & Line" , LVCFMT_LEFT , 120 , -1 );
	//m_list_control.InsertColumn( 1 , "Line " , LVCFMT_LEFT , 56 , -1 );
	m_list_control.InsertColumn( 1 , "Status" , LVCFMT_LEFT , 56 , -1 );

	m_list_control.SetBkColor(  GetYellowColor());
    m_list_control.SetTextColor( GetBlueColor());
 
	CreateControlList(0);   // create the list list control do not force
	UpdateStatusForList();

	SelectActiveTram(  initialId );
	SelectListItem( -1 );
	UpdateSelectedTramInfo();
 
	// don't forget to cloase on exit ???
	SetTimer( 104 ,10000 ,NULL);  // every second

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTramsContr::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer( 104 );
	((CTrainWorldView*)m_pParent)->SwitchDialogMessage( CLOSE_DIALOG_TRAMS , 0 , NULL ) ; 
	CDialogEx::OnClose();
}


HBRUSH CTramsContr::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

/*
void CTramsContr::OnParentNotify(UINT message, LPARAM lParam)
{
	CDialogEx::OnParentNotify(message, lParam);

	// TODO: Add your message handler code here
}
*/

void CTramsContr::OnTimer(UINT_PTR nIDEvent)
{	
	if ( mCurTrainObjectPointer != NULL )  
	{
		UpdateStatusForList();
		DisplayTimeOut( mCurTrainObjectPointer );
	}
}
 

// set filter to display line
//
void CTramsContr::OnBnClickedButtonUpdate()
{
	CString Cs;
	m_edit_linefilter.GetWindowTextA(Cs);
	m_filter =  atoi(Cs);
	CreateControlList(1);
	UpdateStatusForList();
 

	if ( m_list_control.GetItemCount() > 0 ) // // [select tram]
	{
		mCurItemSelected  = 0;
		mCurTrainId = m_list_control.GetItemData( mCurItemSelected );
		mCurTrainObjectPointer =   mCObjRailsColl.FindTrainObjectById(  mCurTrainId  ); 
		SelectListItem( -1 );
		UpdateSelectedTramInfo();
	}

 

	// must select the first one on the list  !!!


}

 


void CTramsContr::OnBnClickedButtonUplineid()
{
	if ( mCurTrainObjectPointer != NULL )  
	{
		CString Cs;
		m_edit_lineid.GetWindowText(Cs);
		mCurTrainObjectPointer->SetLineId(atoi(Cs));  
	}
}


void CTramsContr::OnBnClickedRadioTakecntr()
{
	if ( mCurTrainObjectPointer != NULL )  
	{
		if ( m_takeControl == 0 )
		{
			m_radio_takecontrol.SetCheck( TRUE);
			m_takeControl = 1;
			mCurTrainObjectPointer->SetManualControlMode( TRUE );
		}
		else
		{
			m_radio_takecontrol.SetCheck( FALSE );
			m_takeControl = 0;
			mCurTrainObjectPointer->SetManualControlMode( FALSE );
		}
	}
}

 

void CTramsContr::OnBnClickedRadioStop()
{
	if ( mCurTrainObjectPointer != NULL )  
	{
		if ( m_stop == 0 )
		{
			m_radio_stop.SetCheck( TRUE);
			m_stop = 1;
			mCurTrainObjectPointer->StopTrain( TRUE );
		}
		else
		{
			m_radio_stop.SetCheck( FALSE );
			m_stop = 0;
			mCurTrainObjectPointer->StopTrain( FALSE );
		}
	}
}


void CTramsContr::OnBnClickedRadioBack()
{

	if ( mCurTrainObjectPointer != NULL )  
	{
		if ( m_goback == 0 )
		{
			m_radio_goback.SetCheck( TRUE);
			m_goback = 1;
			mCurTrainObjectPointer->ChangeMoveObjectDir();
		}
		else
		{
			m_radio_goback.SetCheck( FALSE );
			m_goback = 0;
			mCurTrainObjectPointer->ChangeMoveObjectDir();
		}
	}
}


void CTramsContr::OnLbnDblclkListTrams()
{
	 OnBnClickedButtonFind();
}


void CTramsContr::OnBnClickedRadioCleartm()
{
	if ( mCurTrainObjectPointer != NULL )  
			 mCurTrainObjectPointer->SetDynTimeOut( 2 );
}

 

void CTramsContr::OnLvnItemchangedListControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;

	if ( LVIS_SELECTED&pNMLV->uNewState)
	{
		int sel = (int)pNMLV->iItem;
		if ( sel < 0 ) return  ;

		int  id = m_list_control.GetItemData(sel );
		CTramTrainVagons *pv =  mCObjRailsColl.FindTrainObjectById(  id    );
		if ( pv != NULL )
		{
			// [select tram]
			mCurItemSelected = sel;
			mCurTrainId = id;;
			mCurTrainObjectPointer = pv;
			UpdateSelectedTramInfo();
			//SelectListItem( -1 );
 
		}
	}
//mDebug.CDebugPut((char *)"ListControl: %d  %d  %d ",(int)pNMLV->iItem  , (int)pNMLV->uNewState  , (int)LVIS_SELECTED );	
}




/*
 
-0-:10001 ItemSt:1 ((116)) 
-1-:10001  It:((116)) Sbt:1 Tp:7F011230
-0-:30001 ItemSt:1 ((116)) 
-2-:30001  It:((116)) Sbt:0 Tp:7F011230
-0-:30001 ItemSt:1 ((116)) 
-2-:30001  It:((116)) Sbt:1 Tp:7F011230


*/
 


void CTramsContr::OnNMCustomdrawListControl(NMHDR *pNMHDR, LRESULT *pResult)
{
   //LPNMCUSTOMDRAW lpLVCustomDraw1 = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); is in the below
  LPNMLVCUSTOMDRAW lpLVCustomDraw = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
   *pResult = CDRF_DODEFAULT;

//mDebug.CDebugPut((char *)"-0-:%X ItemSt:%X ((%d)) ",(int)lpLVCustomDraw->nmcd.dwDrawStage ,(int)lpLVCustomDraw->nmcd.uItemState, (int)lpLVCustomDraw->nmcd.dwItemSpec);

 switch( lpLVCustomDraw->nmcd.dwDrawStage )
    {
		 case CDDS_PREPAINT:
			*pResult = CDRF_NOTIFYITEMDRAW;
			return;
		 
		case CDDS_ITEMPREPAINT:
			*pResult |= CDRF_NOTIFYSUBITEMDRAW;
			return ;
			break;
 
		case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
			{

 /*
  mDebug.CDebugPut((char *)"-2-:%X  It:((%d)) Sbt:%d St:%X",
	 (int)lpLVCustomDraw->nmcd.dwDrawStage,
	  (int)lpLVCustomDraw->nmcd.dwItemSpec,  
	 (int)lpLVCustomDraw->iSubItem,
	 (int)lpLVCustomDraw->nmcd.uItemState 
	 );
	 */
    		if ( lpLVCustomDraw->nmcd.dwItemSpec  == mCurItemSelected )
			{
 
				lpLVCustomDraw->clrText = RGB(255,255,255); // white text
				lpLVCustomDraw->clrTextBk = RGB(0,0,0); // black background
			}
			else
			{
				CString sCs = m_list_control.GetItemText( lpLVCustomDraw->nmcd.dwItemSpec , 1  );

				if ( sCs == _T( "[Loop]") )
					lpLVCustomDraw->clrText = RGB(255,0,0); // white text
				else if ( sCs == _T( "Run") ) lpLVCustomDraw->clrText = RGB(0,255,0); // white text
				else
					lpLVCustomDraw->clrText = CLR_DEFAULT;
				lpLVCustomDraw->clrTextBk = CLR_DEFAULT;
			}
		}


		*pResult |= CDRF_NOTIFYPOSTPAINT;

		return ;
        break;
 
		case CDDS_ITEMPOSTPAINT: 
			return ;
        break;

		case CDDS_ITEMPOSTPAINT | CDDS_SUBITEM: 	

	        if ( lpLVCustomDraw->nmcd.dwItemSpec  == mCurItemSelected )
			{
				if ( lpLVCustomDraw->iSubItem  == 0 )
				{
					CString sItem = m_list_control.GetItemText( mCurItemSelected , 0  );
					CRect rc;
					m_list_control.GetItemRect( mCurItemSelected ,&rc , LVIR_LABEL );
					CDC *pDC = CDC::FromHandle( lpLVCustomDraw->nmcd.hdc ); 
					//CPen pen( PS_SOLID, 1 , RGB(0,0,255  ));
					//CPen *pOldPen = (CPen*)pDC->SelectObject( &pen);
					//CBrush brush( RGB(0,0,0)   );
					//CBrush *pOldBrush = (CBrush*)pDC->SelectObject( &brush);
					pDC->Rectangle( rc  );
					pDC->SetBkColor( RGB(0,0,0) );
					pDC->SetTextColor( RGB(0,0,255)  );
					rc.DeflateRect(2,0);		
					pDC->DrawText( sItem ,&rc , DT_LEFT );
					//pDC->SelectObject(  pOldPen );
					//pDC->SelectObject(  pOldBrush );
					*pResult = CDRF_SKIPDEFAULT;
				}
 
			}

 
			return ;
        break;

		case CDDS_POSTPAINT:
			return ;
        break;
		
    default:
 
		break;
    }

    *pResult = 0;
 
}


void CTramsContr::OnNMDblclkListControl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	OnBnClickedButtonFind() ;

	*pResult = 0;
}
