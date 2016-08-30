
#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TrainWorld.h"
#endif

#include "SystemValues.h"	
#include "TrainWorldDoc.h"
 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Debug.h"
extern CDebug mDebug;

 


// CTrainWorldDoc
#define  _ProjDocument   CTrainWorldDoc 

CString _ProjDocument::GetAuxFilePath (int fformat)
{
	CString CS_Full_path;
	CS_Full_path = mCsHomePath;

	switch ( fformat )
	{
	case FILE_FORMAT_BMP:
		CS_Full_path += _T("Dibs\\KRK256X256.BMP");
		break;
	case FILE_FORMAT_JPG:
		CS_Full_path += _T("Dibs\\KRK256X256.JPG");
		break;
	case FILE_FORMAT_GIF:
		CS_Full_path += _T("Dibs\\KRK256X256.GIF");
		break;
	default:
		CS_Full_path += _T("Dibs\\KRK256X256.BMP");
		break;
	}
	return CS_Full_path;
}

CString _ProjDocument::GetDataBaseFilePath (int row ,int col ,int fformat)
{
	char lpath[32] ;

 
	switch ( fformat )
	{
	case FILE_FORMAT_BMP:
		sprintf_s( lpath, 30, "%02i%02iKRK.BMP", row ,col);
		break;
	case FILE_FORMAT_JPG:
		sprintf_s( lpath, 30, "%02i%02iKRK.JPG", row ,col);
		break;
	case FILE_FORMAT_GIF:
		sprintf_s( lpath, 30, "%02i%02iKRK.GIF", row ,col);
		break;
	default:
		sprintf_s( lpath, 30, "%02i%02iKRK.BMP", row ,col);
		break;
	}	
	
	
	CString CS_Full_path;
	CS_Full_path = mCsHomePath;
	CS_Full_path += _T("Dibs\\");
	CS_Full_path += lpath;
	return CS_Full_path;
}

 

// ===============================================================
//    main exported interface to data base manager - BgrBmp.cpp
//
//
// ===============================================================

BOOL _ProjDocument::Export_LoadDataBaseBlock ( int nbr , HDC hdcMem ,CRect *prcDest )
{

 if ( SystemDbRead == USE_FORMAT_BMP)    
	return LoadDIBBitmap ( nbr , hdcMem , prcDest );
 if ( SystemDbRead == USE_FORMAT_JPG)   
	return  LoadImage (  nbr , hdcMem , prcDest );
 return FALSE;
}


///////////////////////////////////////////////////////////////
//  called from control view
//  load the file if exists
//  create bitmap if not and then crete the file
////////////////////////////////////////////////////////////////

BOOL _ProjDocument::Interface_LoadAuxImage( HDC hdcMem ,   CRect AuxRect )  
{
	if ( SystemDbRead == USE_FORMAT_BMP )
		return LoadAuxImageFromBMP(  hdcMem   , AuxRect ) ;
	else  if ( SystemDbRead == USE_FORMAT_JPG )
		return LoadAuxImageFromJPG(  hdcMem    , AuxRect ) ;
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////
// Load image with DIB interface
////////////////////////////////////////////////////////////////////////////

BOOL _ProjDocument::LoadAuxImageFromBMP( HDC hdcMem ,   CRect AuxRect ) 
{
	int row,col;
	CRect rc;

	// check if file exists (BMP)
 	if ( LoadAuxBitmapFromBMPFile (   hdcMem , AuxRect) == TRUE )  return TRUE;

	//  no file exist create bitmap
 	for ( row =0;row < BLOCKS_IN_COL; row++)
	 	for ( col =0;col < BLOCKS_IN_ROW; col++)
	//for ( row =0;row < 16; row++)
	//for ( col =0;col < 16 ; col++)
	   {
			rc.left = col*STD_AUX_WIN ;
			rc.top = row*STD_AUX_WIN;
			rc.right =rc.left+STD_AUX_WIN;
			rc.bottom = rc.top +STD_AUX_WIN;
			LoadDIBBitmap (row,col ,hdcMem , &rc );
	   }

   // save the file with common way

	HBITMAP bmap =  (HBITMAP)GetCurrentObject( hdcMem , OBJ_BITMAP );
	SaveAuxImage( bmap , FILE_FORMAT_BJG );  // save both bmp & jpg

	return TRUE;
}
  
BOOL _ProjDocument::LoadAuxBitmapFromBMPFile ( HDC hdcMem ,  CRect AuxRect )  
{
	if (m_hSmallDIB != NULL) {::GlobalFree((HGLOBAL) m_hSmallDIB);m_hSmallDIB = NULL;}

	m_hSmallDIB =::ReadDIBDataFile( GetAuxFilePath ( FILE_FORMAT_BMP ) );
 
	if (m_hSmallDIB != NULL)
		{
			CRect rcDIB;
			LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hSmallDIB );
			rcDIB.right = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
			rcDIB.bottom = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
			::GlobalUnlock((HGLOBAL) m_hSmallDIB);
			::PaintDIB( hdcMem , AuxRect , m_hSmallDIB ,&rcDIB, NULL);
			return TRUE;
		}
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////
// FALSE if jpg file do not exists
////////////////////////////////////////////////////////////////////////////

BOOL _ProjDocument::LoadAuxImageFromJPG( HDC hdcMem    , CRect AuxRect ) 
{
	int row,col;
	//CRect rc(0,0,32,32);
	CRect rc(0,0,WIN_X_AUX,WIN_Y_AUX);

	// check if file exists (BMP)
	if ( LoadAuxBitmapFromJPGFile (   hdcMem , AuxRect) == TRUE )  return TRUE;

	//  small bitmap not initialized - do it now
	// dummy helps
	 LoadDIBBitmap ( GetAuxFilePath (FILE_FORMAT_BMP) , hdcMem , &rc   );

	 for ( row =0;row < BLOCKS_IN_COL; row++)
	   for ( col =0;col < BLOCKS_IN_ROW; col++)
	   {
		    rc.left = col*STD_AUX_WIN ;
			rc.top = row*STD_AUX_WIN;
			rc.right =rc.left+STD_AUX_WIN;
			rc.bottom = rc.top +STD_AUX_WIN;
			//LoadDIBBitmap (row,col ,hdcMem , &rc );
			LoadImage (   row,    col  ,   hdcMem ,&rc );
	   }
	   
	HBITMAP bmap =  (HBITMAP)GetCurrentObject( hdcMem , OBJ_BITMAP );
	SaveAuxImage( bmap ,FILE_FORMAT_BJG );

	return TRUE;
}


BOOL _ProjDocument::LoadAuxBitmapFromJPGFile ( HDC hdcMem ,  CRect AuxRect )  
{	 
 	HBITMAP bmap =  (HBITMAP)GetCurrentObject( hdcMem , OBJ_BITMAP );
 	CImage img;
 
	HRESULT hr =  img.Load(  GetAuxFilePath (FILE_FORMAT_JPG ));
	if ( hr != S_OK ) return FALSE;

	int obpp = GetDeviceCaps(hdcMem , BITSPIXEL );
	HDC hdc = img.GetDC();
	//DebugHDC(100 , hdc  );
	int bpp = GetDeviceCaps(hdc , BITSPIXEL );
	img.ReleaseDC();

	if ( obpp == bpp )
		img.BitBlt( hdcMem ,  0,  0, WIN_X_AUX , WIN_Y_AUX  ,    0,  0 , SRCCOPY );
	else
		return FALSE;
	//mDebug.CDebugPut((char *)"New Stat %d,%d", (int)img.GetWidth(), img.GetHeight()  );
	return TRUE;
}


BOOL _ProjDocument::SaveAuxImage( HBITMAP bitmap ,int fformat  )
{
	CImage img; 
	img.Attach((HBITMAP)bitmap );

	switch ( fformat )
	{
	case FILE_FORMAT_BMP:
		img.Save(GetAuxFilePath (FILE_FORMAT_BMP ),Gdiplus::ImageFormatBMP);
		break;
	case FILE_FORMAT_JPG:
		img.Save(GetAuxFilePath (FILE_FORMAT_JPG ));
		break;
	case FILE_FORMAT_GIF:
		img.Save(GetAuxFilePath (FILE_FORMAT_GIF ) );
		break;
	case FILE_FORMAT_BJG:
		img.Save(GetAuxFilePath (FILE_FORMAT_JPG ));
		img.Save(GetAuxFilePath (FILE_FORMAT_BMP ),Gdiplus::ImageFormatBMP);
		break;

	default:
		img.Save(GetAuxFilePath (FILE_FORMAT_BMP ),Gdiplus::ImageFormatBMP);
		break;
	}	


 //   img.Save(GetAuxFilePath (FILE_FORMAT_BMP ),Gdiplus::ImageFormatBMP);
//	img.Save(GetAuxFilePath (FILE_FORMAT_JPG ));
//	img.Save(GetAuxFilePath (FILE_FORMAT_GIF ) );
 
	return TRUE;
}


////////////////////////////////////////////////////////////////////////////////// 
//
//  loadin bitmap in standrd way

BOOL _ProjDocument::LoadDIBBitmap ( int nbr , HDC hdcMem ,CRect *prcDest )
{
	LoadDIBFile ((int)nbr );
	HDIB hDIB =  GetHDIB();
	if (hDIB != NULL)
		{
			CRect rcDIB;
			rcDIB.top = rcDIB.left = 0;
			LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
			rcDIB.right = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
			rcDIB.bottom = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
			::GlobalUnlock((HGLOBAL) hDIB);
			::PaintDIB( hdcMem , prcDest , hDIB ,&rcDIB, NULL);
			return TRUE;
		}
	return FALSE;
}
 

BOOL _ProjDocument::LoadDIBBitmap (int row,int col , HDC hdcMem ,CRect *prcDest )
{
	LoadDIBFile ((int)row, col );

	HDIB hDIB =  GetHDIB();
	if (hDIB != NULL)
		{
			CRect rcDIB;
			rcDIB.top = rcDIB.left = 0;
			LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
			rcDIB.right = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
			rcDIB.bottom = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
			::GlobalUnlock((HGLOBAL) hDIB);
			::PaintDIB( hdcMem , prcDest , hDIB ,&rcDIB, NULL);
			return TRUE;
		}
	return FALSE;
}


BOOL _ProjDocument::LoadDIBBitmap ( CString filename , HDC hdcMem ,CRect *prcDest )
{
	//LoadDIBFile ((int)row, col );
	LoadDIBFile (  filename );

	HDIB hDIB =  GetHDIB();
	if (hDIB != NULL)
		{
			CRect rcDIB;
			rcDIB.top = rcDIB.left = 0;
			LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
			rcDIB.right = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
			rcDIB.bottom = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
			::GlobalUnlock((HGLOBAL) hDIB);
			::PaintDIB( hdcMem , prcDest , hDIB ,&rcDIB, NULL);
			return TRUE;
		}
	return FALSE;
}


BOOL  _ProjDocument::LoadDIBFile( CString  filename ) 
{

	if (m_hDIB != NULL)
	{::GlobalFree((HGLOBAL) m_hDIB);m_hDIB = NULL;}
	
	DeleteContents();
	BeginWaitCursor();
	m_hDIB =	ReadDIBDataFile(  filename  );
	EndWaitCursor();
	m_sizeDoc =  GetDIBSize(); 
	if ( m_hDIB != NULL ) return TRUE; 
	return FALSE;
}

BOOL _ProjDocument::LoadDIBFile (int nbr)
{
	if (m_hDIB != NULL)
	{::GlobalFree((HGLOBAL) m_hDIB);m_hDIB = NULL;}
	
	int row,col;

	row = nbr/BLOCKS_IN_ROW;
	col = nbr%BLOCKS_IN_ROW;

	DeleteContents();
	BeginWaitCursor();
	m_hDIB =	ReadDIBDataFile(  GetDataBaseFilePath (  row ,  col , FILE_FORMAT_BMP ) );
	EndWaitCursor();
	m_sizeDoc =  GetDIBSize(); 
	if ( m_hDIB != NULL ) return TRUE; 
	return FALSE;
}
 
 
BOOL _ProjDocument::LoadDIBFile (int row, int col)
{
	if (m_hDIB != NULL)
	{::GlobalFree((HGLOBAL) m_hDIB);m_hDIB = NULL;}
	
 
	DeleteContents();
	BeginWaitCursor();
	m_hDIB =	ReadDIBDataFile(  GetDataBaseFilePath (  row ,  col , FILE_FORMAT_BMP ) );
	EndWaitCursor();
	m_sizeDoc =  GetDIBSize(); 
	if ( m_hDIB != NULL ) return TRUE; 
	return FALSE;
}

 

  

/////////////////////////////////////////////////////////////////////
//
// tools ------------------------------
//
/////////////////////////////////////////////////////////////////////
void _ProjDocument::Tool_BMPtoJPGConverstion( HDC hdcMem, HBITMAP bitmap   )
{
	int row,col;
 
   	for ( row =0;row < BLOCKS_IN_COL; row++)
	  for ( col =0;col < BLOCKS_IN_ROW; col++)
	   {
		   /*
		    CRect rc( 0,0,1024,1024 );
		    if (	LoadDIBBitmap (row,col ,hdcMem , &rc ) == TRUE )
		   */
		   if ( LoadImage (   row,    col  ,   hdcMem  ) == TRUE )
			{
			    // bit map must be actual size 
				SaveImage( row,    col  ,  bitmap , 1 );
			}
	   }
}

////////////////////////////////////////////////////////////////////////
//
//  CImage mothod for saving / loading the files
//
 

BOOL _ProjDocument::SaveImage( int row,  int col  , HBITMAP bitmap , int fmt  )
{
	CImage img; 
	img.Attach((HBITMAP)bitmap );
 
	if ( fmt == 0 )
    img.Save(  GetDataBaseFilePath (  row ,  col , FILE_FORMAT_BMP ) ,Gdiplus::ImageFormatBMP);
	else if ( fmt == 1 )
	img.Save(  GetDataBaseFilePath (  row ,  col , FILE_FORMAT_JPG ) );
	else return FALSE;

	return TRUE;
}


BOOL _ProjDocument::LoadImage ( int row,  int col  , HDC hdcMem  )
{
	CImage img; 
 
	HRESULT hr =  img.Load( GetDataBaseFilePath (  row ,  col , FILE_FORMAT_BMP));

	if ( hr != S_OK ) return FALSE;

	int obpp = GetDeviceCaps(hdcMem , BITSPIXEL );
	HDC hdc = img.GetDC();
	//DebugHDC(100 , hdc  );
	int bpp = GetDeviceCaps(hdc , BITSPIXEL );
	img.ReleaseDC();

	if ( obpp == bpp )
		img.BitBlt( hdcMem ,  0,  0, WIN_X , WIN_Y ,    0,  0 , SRCCOPY );
	else
	{
	    mDebug.CDebugPut((char *)"Error loading  %02i%02iKRK.bmp", row, col  );
		return FALSE;
	}

	return TRUE;
}


// load and squize into certain block position

BOOL _ProjDocument::LoadImage ( int row,  int col  , HDC hdcMem ,CRect *prcDest )
{
	CImage img; 
 
	HRESULT hr =  img.Load( GetDataBaseFilePath (  row ,  col , FILE_FORMAT_JPG));

	if ( hr != S_OK ) return FALSE;

	int obpp = GetDeviceCaps(hdcMem , BITSPIXEL );
	HDC hdc = img.GetDC();
	//DebugHDC(100 , hdc  );
	int bpp = GetDeviceCaps(hdc , BITSPIXEL );
	img.ReleaseDC();

//mDebug.CDebugPut((char *)"LOAD1  %02i%02iKRK.jpg   %d %d", row, col,0, img.IsDIBSection( ) );
 
	int nDestWidth = prcDest->right - prcDest->left;
	int nDestHeight = prcDest->bottom - prcDest->top ;


//	mDebug.CDebugPut((char *)"Width hight   %d %d",   img.GetWidth() , img.GetHeight()  );


	if ( obpp == bpp )
	{
		if (( nDestWidth == img.GetWidth() ) && (nDestHeight == img.GetHeight()  ))
			img.BitBlt( hdcMem ,  0,  0, nDestWidth , nDestHeight  ,    0,  0 , SRCCOPY );
		else
			img.StretchBlt( hdcMem , prcDest->left, prcDest->top, nDestWidth, nDestHeight, 0, 0, img.GetWidth(), img.GetHeight(), SRCCOPY );
	}
	else
	{
	    mDebug.CDebugPut((char *)"Error loading  %02i%02iKRK.jpg", row, col  );
		return FALSE;
	}

 
	return TRUE;
}
 
BOOL _ProjDocument::LoadImage (  int nbr , HDC hdcMem ,CRect *prcDest  )
{
	int row = nbr/BLOCKS_IN_ROW;
	int col = nbr%BLOCKS_IN_ROW;
	return LoadImage (   row,    col  ,   hdcMem , prcDest );
}