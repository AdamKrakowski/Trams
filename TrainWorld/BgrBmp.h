
 
// this is the data base block size
// system dependent do not change

#pragma once

#include "SystemValues.h"	

#ifdef WINAPP_	
#include "TrainWorldDoc.h"
#endif
 
#ifndef WINAPP_	
#include "AJGfundation.h"
#endif

 
 
 
 
typedef struct
{
	int dest_x;
	int dest_y;
	int size_x;
	int size_y;
	int src_x;
	int src_y;
}  Copy_Cord;

#ifndef WINAPP_	
typedef struct  
{
	int t[16][16]; 
}  Tbl_mem ;

#endif

typedef struct
{
	int x_wide;
	int y_wide;
#ifdef WINAPP_
	HDC  *p;
	CTrainWorldDoc *pDoc;
#else
	Tbl_mem  *p;
#endif
}  sBgrBmpInit; 
 
// interfaces
#ifndef WINAPP_	
void InterfaceInitBgrBmp( 	sBgrBmpInit  *p ) ;
void InterfaceUpdateBgrBmp( Tbl_mem *mem_out  ,  CRect rc   ) ;
void InterfaceTestBgrBmp (  CRect rc , int x, int y );
#endif
 
 class CBgrBmp {
 public:
	CBgrBmp();
	void CBgrBmpInit( sBgrBmpInit *p );
#ifdef WINAPP_
	void CBgrBmpUpdateAreas( HDC *mem_out  , int des_off_x , int des_off_y  ,  CRect rc   ) ;
#else    
	void CBgrBmpUpdateAreas( Tbl_mem *mem_out  ,   CRect rc   ) ;
#endif	
	CRect CBgrBmp::DbaseSpaceBlockRect( int lefttopbloc  );
	BOOL CBgrBmpNotInitialized();
#ifndef WINAPP_	
	void CBgrBmp::BgrBmpTest( CRect rc , int x, int y , int option );
	void CBgrBmp::DebugBlockTable(int loc);
	void CBgrBmp::DebugTmpBlockTable(int loc);
	void CBgrBmp::DebugMemBlockTable( Tbl_mem *p );
	void CBgrBmp::DebugUnsBlockTable(int loc);
#endif
 private:
	int block_tbl[NBR_OF_BUFFERS];
	int block_uns[NBR_OF_BUFFERS];
	int new_block_tbl[4];
#ifdef WINAPP_	
	HDC  *hdcTmpMem[NBR_OF_BUFFERS];
#else
	Tbl_mem  *mem_[NBR_OF_BUFFERS];  // keep pointer to the bmp space  or bitmap space
#endif
 
#ifndef WINAPP_	
	char text[128];  // only for debug
#else
		CTrainWorldDoc *pDoc;
#endif

	void CBgrBmp::IvalidateBlocks();
	int  CBgrBmp::ComputeCurrentBlocks(int ptx , int pty );
	void CBgrBmp::ComputeNewBlocks( CRect rc );
	void CBgrBmp::LoadBlock ( int block );
	void CBgrBmp::MarkUnusedBlocks();
	void CBgrBmp::UpdateNewBlocks();
	int CBgrBmp::FreeOneBlock();
	// initialization of the test pattern for test application
#ifndef WINAPP_		
	void CBgrBmp::LoadMemPoint ( Tbl_mem  *p , int block );
#endif
	BOOL CBgrBmp::ComputeMemCoordinates( int iqn , CRect  rc , Copy_Cord  *p);
	//  x,y represents the left,top coordinate of the scroll window
	CRect CBgrBmp::DbaseSpaceBlockRect( int x,int y );
	//  lefttopbloc represents the left,top block number of the scroll window
	//CRect CBgrBmp::DbaseSpaceBlockRect( int lefttopbloc  );
 };


 