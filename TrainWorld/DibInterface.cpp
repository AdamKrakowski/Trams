//  myfile.cpp
//
//  Source file for Device-Independent Bitmap (DIB) API.  Provides
//  the following functions:
//
//  SaveDIB()           - Saves the specified dib in a file
//  ReadDIBFile()       - Loads a DIB from a file
//
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include <math.h>
#include <io.h>
#include <direct.h>
#include "dibapi.h"

/*
 * Dib Header Marker - used in writing DIBs to files
 */
#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')


/*************************************************************************

  Function:  OpenDIBData (LPCTSTR lpszPathName)

   Purpose:   

   Returns:  

  Comments:   

*************************************************************************/ 

HANDLE OpenDIBData(LPCTSTR lpszPathName)
{
	HANDLE hFile;

	hFile = CreateFile( lpszPathName , GENERIC_WRITE | GENERIC_READ ,  0 ,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL ,0 );
    if( hFile == INVALID_HANDLE_VALUE)
    {
        return INVALID_HANDLE_VALUE;
    }

	return hFile;
}


/*************************************************************************
 *
 * SaveDIB()
 *
 * Saves the specified DIB into the specified CFile.  The CFile
 * is opened and closed by the caller.
 *
 * Parameters:
 *
 * HDIB hDib - Handle to the dib to save
 *
 * CFile& file - open CFile used to save DIB
 *
 * Return value: TRUE if successful, else FALSE or CFileException
 *
 *************************************************************************/


BOOL WINAPI SaveDIB(HDIB hDib, CFile& file)
{
	BITMAPFILEHEADER bmfHdr; // Header for Bitmap file
	LPBITMAPINFOHEADER lpBI;   // Pointer to DIB info structure
	UINT nDIBSize;

	if (hDib == NULL)
		return FALSE;

	/*
	 * Get a pointer to the DIB memory, the first of which contains
	 * a BITMAPINFO structure
	 */
	lpBI = (LPBITMAPINFOHEADER) ::GlobalLock((HGLOBAL) hDib);
	if (lpBI == NULL)
		return FALSE;

	if (!IS_WIN30_DIB(lpBI))
	{
		::GlobalUnlock((HGLOBAL) hDib);
		return FALSE;       // It's an other-style DIB (save not supported)
	}

	/*
	 * Fill in the fields of the file header
	 */

	/* Fill in file type (first 2 bytes must be "BM" for a bitmap) */
	bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM"

	// Calculating the size of the DIB is a bit tricky (if we want to
	// do it right).  The easiest way to do this is to call GlobalSize()
	// on our global handle, but since the size of our global memory may have
	// been padded a few bytes, we may end up writing out a few too
	// many bytes to the file (which may cause problems with some apps).
	//
	// So, instead let's calculate the size manually (if we can)
	//
	// First, find size of header plus size of color table.  Since the
	// first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
	// the size of the structure, let's use this.

	nDIBSize = *(LPDWORD)lpBI + ::PaletteSize((LPSTR)lpBI);  // Partial Calculation

	// Now calculate the size of the image

	if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
	{
		// It's an RLE bitmap, we can't calculate size, so trust the
		// biSizeImage field

		nDIBSize += lpBI->biSizeImage;
	}
	else
	{
		DWORD dwBmBitsSize;  // Size of Bitmap Bits only

		// It's not RLE, so size is Width (DWORD aligned) * Height

		dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) * lpBI->biHeight;

		nDIBSize += dwBmBitsSize;

		// Now, since we have calculated the correct size, why don't we
		// fill in the biSizeImage field (this will fix any .BMP files which
		// have this field incorrect).

		lpBI->biSizeImage = dwBmBitsSize;
	}


	// Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)

	bmfHdr.bfSize = nDIBSize + sizeof(BITMAPFILEHEADER);
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;

	/*
	 * Now, calculate the offset the actual bitmap bits will be in
	 * the file -- It's the Bitmap file header plus the DIB header,
	 * plus the size of the color table.
	 */
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize
											  + PaletteSize((LPSTR)lpBI);
	TRY
	{
		// Write the file header
		file.Write((LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER));
		//
		// Write the DIB header and the bits
		//
		file.Write(lpBI, nDIBSize);
	}
	CATCH (CFileException, e)
	{
		::GlobalUnlock((HGLOBAL) hDib);
		THROW_LAST();
	}
	END_CATCH

	::GlobalUnlock((HGLOBAL) hDib);
	return TRUE;
}


/*************************************************************************

  Function:  ReadDIBFile (CFile&)

   Purpose:  Reads in the specified DIB file into a global chunk of
			 memory.

   Returns:  A handle to a dib (hDIB) if successful.
			 NULL if an error occurs.

  Comments:  BITMAPFILEHEADER is stripped off of the DIB.  Everything
			 from the end of the BITMAPFILEHEADER structure on is
			 returned in the global memory handle.

*************************************************************************/


HDIB WINAPI ReadDIBFile(CFile& file)
{
	BITMAPFILEHEADER bmfHeader;
	UINT nBitsSize;
	HDIB hDIB;
	LPSTR pDIB;

	/*
	 * get length of DIB in bytes for use when reading
	 */

	nBitsSize = (UINT)file.GetLength();

	/*
	 * Go read the DIB file header and check if it's valid.
	 */
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return NULL;

	if (bmfHeader.bfType != DIB_HEADER_MARKER)
		return NULL;

	/*
	 * Allocate memory for DIB
	 */
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (DWORD)nBitsSize);
	if (hDIB == 0)
	{
		return NULL;
	}
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	/*
	 * Go read the bits.
	 */
	if (file.Read(pDIB, nBitsSize - sizeof(BITMAPFILEHEADER)) !=
		nBitsSize - sizeof(BITMAPFILEHEADER) )
	{
		::GlobalUnlock((HGLOBAL) hDIB);
		::GlobalFree((HGLOBAL) hDIB);
		return NULL;
	}
	::GlobalUnlock((HGLOBAL) hDIB);
	return hDIB;
}

/*************************************************************************

  Function:  ReadDIBFile (CFile&)

   Purpose:  Reads in the specified DIB file into a global chunk of
			 memory.

   Returns:  A handle to a dib (hDIB) if successful.
			 NULL if an error occurs.

  Comments:  BITMAPFILEHEADER is stripped off of the DIB.  Everything
			 from the end of the BITMAPFILEHEADER structure on is
			 returned in the global memory handle.

*************************************************************************/

DWORD  DibOpenError , LastSysError ;

DWORD GetDIBEror(){ return DibOpenError;}


HDIB WINAPI ReadDIBEx( HANDLE hFile )
{
	BITMAPFILEHEADER bmfHeader;
	DWORD nBitsSize;
	HDIB hDIB;
	LPSTR pDIB;

	/*
	 * get length of DIB in bytes for use when reading
	 */

	DibOpenError = LastSysError =0 ;

	nBitsSize = GetFileSize (hFile, NULL) ; 

	 //mDebug.CDebugPut("Size %d",nBitsSize );

	if (nBitsSize == 0xFFFFFFFF) {
         
		DibOpenError = 1;
		LastSysError = GetLastError() ; 

		// mDebug.CDebugPut("Error 0  (%d)[%X]"  , (int)LastSysError, (int)LastSysError );

		 return NULL;
	}

	 

	/*
	 * Go read the DIB file header and check if it's valid.
	 */


	//	mDebug.CDebugPut("Reading header"  );

	DWORD lpNumberOfBytesRead;
	ReadFile( hFile, (LPSTR)&bmfHeader , sizeof(bmfHeader), &lpNumberOfBytesRead, NULL );

 	//mDebug.CDebugPut("Read %d "  , lpNumberOfBytesRead );


	if (bmfHeader.bfType != DIB_HEADER_MARKER)
	{
		//mDebug.CDebugPut("Error 1"  );
			DibOpenError = 2;
		return NULL;
	}
	//	mDebug.CDebugPut("GlobalAlloc"  );


	 


	/*
	 * Allocate memory for DIB
	 */
	hDIB = (HDIB) ::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (DWORD)nBitsSize);
	if (hDIB == 0)
	{
	//	mDebug.CDebugPut("Error 2"  );
			DibOpenError = 3;
		return NULL;
	}
	pDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);

	/*
	 * Go read the bits.
	 */

	//mDebug.CDebugPut("Bits read"  );

	ReadFile( hFile, (LPSTR)pDIB , nBitsSize - sizeof(BITMAPFILEHEADER) , &lpNumberOfBytesRead, NULL );

	// mDebug.CDebugPut("Read %d "  , lpNumberOfBytesRead );

	//if (file.Read(pDIB, nBitsSize - sizeof(BITMAPFILEHEADER)) !=
	//	nBitsSize - sizeof(BITMAPFILEHEADER) )

	if ( lpNumberOfBytesRead != ( nBitsSize - sizeof(BITMAPFILEHEADER) ) )
	{
		::GlobalUnlock((HGLOBAL) hDIB);
		::GlobalFree((HGLOBAL) hDIB);

		DibOpenError = 4;
		//mDebug.CDebugPut("Error 3"  );

		return NULL;
	}
	::GlobalUnlock((HGLOBAL) hDIB);

	//mDebug.CDebugPut("OK"  );

	return hDIB;
}



HDIB InitDIBDataEx( HDIB tmpDIB , CSize *csp )
{
 
	if (tmpDIB == NULL)
	{
		return NULL;
	}
	// Set up document size
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) tmpDIB);
	if (::DIBWidth(lpDIB) > INT_MAX ||::DIBHeight(lpDIB) > INT_MAX)
	{
		::GlobalUnlock((HGLOBAL) tmpDIB);
		::GlobalFree((HGLOBAL) tmpDIB);
		tmpDIB = NULL;
		CString strMsg;
 		//strMsg.LoadString(IDS_DIB_TOO_BIG);
		//MessageBox(NULL, strMsg, NULL, MB_ICONINFORMATION | MB_OK);
		 MessageBox(NULL, "DIB_TOO_BIG", NULL, MB_ICONINFORMATION | MB_OK);
		return NULL;
	}
	//m_sizeDoc = CSize((int)::DIBWidth(lpDIB), (int) ::DIBHeight(lpDIB));

	::GlobalUnlock((HGLOBAL) tmpDIB);
 
	return tmpDIB;
}


CSize dibsize;

CSize   GetDIBSize()
{ return dibsize;}

HDIB	ReadDIBDataFile( LPCTSTR lpszPathName )
{
	HANDLE hFile;

	hFile = OpenDIBData( lpszPathName );

	if (   INVALID_HANDLE_VALUE ==   hFile   ) return NULL;

	HDIB hDIB = ReadDIBEx(  hFile );

	if ( hDIB == NULL ) return NULL;

	if ( InitDIBDataEx( hDIB , &dibsize ) == NULL )
		return NULL;

	CloseHandle( hFile);
	return hDIB;
}