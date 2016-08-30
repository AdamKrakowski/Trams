// dibapi.h
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.


#ifndef _INC_DIBAPI
#define _INC_DIBAPI

/* Handle to a DIB */
DECLARE_HANDLE(HDIB);

/* DIB constants */
#define PALVERSION   0x300

/* DIB Macros*/

#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// WIDTHBYTES performs DWORD-aligning of DIB scanlines.  The "bits"
// parameter is the bit count for the scanline (biWidth * biBitCount),
// and this macro returns the number of DWORD-aligned bytes needed
// to hold those bits.

#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

/* Function prototypes */
BOOL      WINAPI  PaintDIB (HDC, LPRECT, HDIB, LPRECT, CPalette* pPal);
BOOL      WINAPI  CreateDIBPalette(HDIB hDIB, CPalette* cPal);
LPSTR     WINAPI  FindDIBBits (LPSTR lpbi);
DWORD     WINAPI  DIBWidth (LPSTR lpDIB);
DWORD     WINAPI  DIBHeight (LPSTR lpDIB);
WORD      WINAPI  PaletteSize (LPSTR lpbi);
WORD      WINAPI  DIBNumColors (LPSTR lpbi);
HGLOBAL   WINAPI  CopyHandle (HGLOBAL h);
HGLOBAL   WINAPI  CopyHandleEx (HGLOBAL h , CRect rect );
DWORD     WINAPI GetBitCount(LPSTR lpDIB);

BOOL      WINAPI  SaveDIB (HDIB hDib, CFile& file);
HDIB      WINAPI  ReadDIBFile(CFile& file);

HDIB	ReadDIBDataFile( LPCTSTR lpszPathName );
CSize   GetDIBSize();

#endif //!_INC_DIBAPI


/*

Bitmap File Header [14]
----- DIB start here
DIB Header 


Bitmap File Header 	No 	14 Bytes 
To store general information about the Bitmap Image File 	
Not needed after the file is loaded in memory

ffset# 	Size 	Purpose
0000h 	2 bytes 	the header field used to identify the BMP & DIB file is 0x42 0x4D in
hexadecimal, same as BM in ASCII. The following entries are possible:

    BM – Windows 3.1x, 95, NT, ... etc.
    BA – OS/2 struct Bitmap Array
    CI – OS/2 struct Color Icon
    CP – OS/2 const Color Pointer
    IC – OS/2 struct Icon
    PT – OS/2 Pointer

0002h 	4 bytes 	the size of the BMP file in bytes
0006h 	2 bytes 	reserved; actual value depends on the application that creates the image
0008h 	2 bytes 	reserved; actual value depends on the application that creates the image
000Ah 	4 bytes 	the offset, i.e. starting address, of the byte where
the bitmap image data (pixel array) can be found.



DIB Header 	No 	Fixed-size
(however 7 different versions exist) 
To store detailed information about the bitmap image and define the pixel format 
Immediately follows the Bitmap File Header

Size 	Header Name 	OS support 	Features Added (incremental) 	in Bitmap Files Written by
12 	BITMAPCOREHEADER
OS21XBITMAPHEADER 	OS/2 and also all Windows versions since Windows 3.0 		
64 	BITMAPCOREHEADER2
OS22XBITMAPHEADER 	OS/2 	Adds halftoning. Adds RLE and Huffman 1D compression. 	
40 	BITMAPINFOHEADER 	all Windows versions since Windows 3.0 	Removes RLE-24 and Huffman 1D compression. Adds 16bpp and 32bpp pixel formats. Adds optional RGB bit masks. 	Adobe Photoshop
52 	BITMAPV2INFOHEADER 	Undocumented. 	Removes optional RGB bit masks. Adds mandatory RGB bit masks. 	
56 	BITMAPV3INFOHEADER 	Undocumented. 	Adds mandatory alpha channel bit mask. 	Adobe Photoshop
108 	BITMAPV4HEADER 	all Windows versions since Windows 95/NT4 	Adds color space type and gamma correction 	
124 	BITMAPV5HEADER 	Windows 98/2000 and newer 	Adds ICC color profiles



Extra bit masks 	Yes 	3 or 4 DWORDs[2]
(12 or 16 Bytes) 	To define the pixel format 	Present only in case the DIB Header is the BITMAPINFOHEADER

ixel Array 	No 	Variable-size 
To define the actual values of the pixels 	The pixel format is defined by the DIB Header or Extra bit masks. 
Each row in the Pixel Array is padded to a multiple of 4 bytes in size

*/