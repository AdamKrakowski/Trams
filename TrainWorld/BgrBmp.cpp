
#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <conio.h>
#include "debug.h"

#include "BgrBmp.h"

#ifndef WINAPP_	
#include "AJGfundation.h"
#endif

extern CDebug  mDebug;


#ifndef WINAPP_ 
void ScrCopy( Tbl_mem *mem_out , Tbl_mem *mem_in, int dest_x,int dest_y, int size_x,int size_y,int src_x,int src_y)
{
	int row,col;
#ifdef  DEBUG7
	char text[120];
	sprintf_s( text,   120, "ScCpy : des{ %d,%d} size (%d,%d) src (%d,%d)" ,  dest_x, dest_y , size_x, size_y , src_x , src_y  );
	mDebug.CDebugPut((char *)text);
#endif
	for ( row = 0; row < size_y ;row++)
		for ( col = 0;col < size_x  ;col++)
			{
				mem_out->t[col+dest_x][row+dest_y] = mem_in->t[col+src_x][row+src_y] ;
			}
}
#endif


// constructor default
 CBgrBmp::CBgrBmp()
{
	IvalidateBlocks();
#ifdef WINAPP_
	hdcTmpMem[0] =  NULL;
	hdcTmpMem[1] =  NULL;
	hdcTmpMem[2] =  NULL;
	hdcTmpMem[3] =  NULL;
	pDoc = NULL;
#else
	mem_[0] = NULL;;
	mem_[1] = NULL;
	mem_[2] = NULL;
	mem_[3] = NULL;
#endif
}

#ifndef WINAPP_
void CBgrBmp::BgrBmpTest( CRect rc , int x, int y , int option ) 
{
Copy_Cord  cord;
ComputeMemCoordinates( 0 ,  rc ,&cord);
ComputeMemCoordinates( 1 ,  rc ,&cord);
ComputeMemCoordinates( 2 ,  rc ,&cord);
ComputeMemCoordinates( 3 ,  rc ,&cord);
}
#endif

#ifdef WINAPP_
void CBgrBmp::CBgrBmpUpdateAreas( HDC *mem_out  , int des_off_x , int des_off_y  , CRect rc  )  
#else
void CBgrBmp::CBgrBmpUpdateAreas( Tbl_mem *mem_out   , CRect rc   )  
#endif
{
	Copy_Cord  cord;

#ifdef  DEBUG9
 	sprintf_s( text, 120,"Shift:[%d,%d] Scr win:(%d,%d)(%d,%d)" , ishift_X ,ishift_Y, rc.left ,rc.top ,rc.right , rc.bottom );
	mDebug.CDebugPut((char *)text);
#endif
 
	CBgrBmp::ComputeNewBlocks(rc);
 	CBgrBmp::MarkUnusedBlocks();
	CBgrBmp::UpdateNewBlocks();

	int m;
	for ( m=0; m < 4 ; m++ )  //  4 points of rectangle
	   {
		if  ( CBgrBmp::ComputeMemCoordinates( m ,   rc , &cord ) == TRUE )
			{
				int i;
				for ( i = 0; i < NBR_OF_BUFFERS ; i++ )
					if ( new_block_tbl[m] == block_tbl[i] ) // this is the block to read from
						{
#ifdef  DEBUG9
sprintf_s( text,   120, "use : %d  des{ %d %d} szie (%d,%d) " ,  i , cord.dest_x,cord.dest_y ,cord.size_x,cord.size_y );
mDebug.CDebugPut((char *)text);
#endif
#ifdef WINAPP_	
BitBlt( *(HDC *)mem_out, cord.dest_x +des_off_x ,  cord.dest_y +des_off_y , cord.size_x,cord.size_y  ,*(HDC *)hdcTmpMem[i] , cord.src_x,cord.src_y , SRCCOPY);
#else
ScrCopy( mem_out , mem_[i],  cord.dest_x,cord.dest_y,cord.size_x,cord.size_y,cord.src_x,cord.src_y);
#endif	
						break;
						}
			}
		} 
}


BOOL  CBgrBmp::CBgrBmpNotInitialized() 
{
#ifdef WINAPP_
	if (	hdcTmpMem[0] ==  NULL ) return FALSE;
	if (pDoc == NULL ) return FALSE;
#else
	if (	mem_[0] == NULL ) return FALSE;
#endif
	return TRUE;
}

void CBgrBmp::CBgrBmpInit(  sBgrBmpInit *pin )  
{
	int i;
#ifdef WINAPP_
	for (i =0; i <NBR_OF_BUFFERS;i++) hdcTmpMem[i] =  &pin->p[i];
	pDoc = pin->pDoc;
#else
	for (i =0; i <NBR_OF_BUFFERS;i++) mem_[i] =  &pin->p[i];
#endif
}


////////////////////////////////////////////////////
// Debug utilities 
// valid only for command line test application
// invalid for Windows application

#ifndef WINAPP_	
void CBgrBmp::DebugBlockTable(int loc)
{
	sprintf_s( text,   120, "BlockTable ver{%d} {%d,%d,%d,%d}" ,  loc , block_tbl[0], block_tbl[1], block_tbl[2], block_tbl[3] );
	mDebug.CDebugPut((char *)text);
	sprintf_s( text,   120, "     BlockTable ver{%d} {%d,%d,%d,%d}" ,  loc , block_tbl[4], block_tbl[5], block_tbl[6], block_tbl[7] );
	mDebug.CDebugPut((char *)text);

}

void CBgrBmp::DebugTmpBlockTable(int loc)
{
	sprintf_s( text,   120, "New BlockTable ver{%d} {%d,%d,%d,%d}" ,  loc , new_block_tbl[0], new_block_tbl[1], new_block_tbl[2], new_block_tbl[3] );
	mDebug.CDebugPut((char *)text);
}

void CBgrBmp::DebugUnsBlockTable(int loc)
{
	sprintf_s( text,   120, "Unz BlockTable ver{%d} {%d,%d,%d,%d}" ,  loc , block_uns[0], block_uns[1], block_uns[2], block_uns[3] );
	mDebug.CDebugPut((char *)text);
		sprintf_s( text,   120, "     Unz BlockTable ver{%d} {%d,%d,%d,%d}" ,  loc , block_uns[4], block_uns[5], block_uns[6], block_uns[7] );
	mDebug.CDebugPut((char *)text);
}


void CBgrBmp::DebugMemBlockTable( Tbl_mem *p )
{
	int row,j;
	mDebug.CDebugPut((char *)"");
	for ( row =0;row < 16 ; row++)
	{
		for ( j =0;j < 16; j++)
		{
			sprintf_s( text,   120, "{%02d(%02d,%02d)}," , (p->t[j][row]>>16)&0xFF,  p->t[j][row]&0xFF ,(p->t[j][row]>>8)&0xFF  );
			mDebug.CDebugPutNoLFCr((char *)text);
		}
		mDebug.CDebugPut((char *)"");
	}
}
#endif


////////////////////////////////////////////////////
// ComputeMemCoordinates
// Compute: source coordinates , destination scroll window coordinates & size of the block to transfer 
//  iqn - point to dbase quadrant 
//  rc  - scroll window in dbase coordinates ( map coordinates )
//  p   - return computes parameters
//  return - FALSE  no  intersect   TRUE if there is intersection and data returned . 
//          -------------  
//         |  0   |   1  |
//          -------------
//		   |  2   |   3  |
//			-------------
///////////////////////////////////////////////////


BOOL CBgrBmp::ComputeMemCoordinates( int iqn , CRect  rc , Copy_Cord  *p)
{
	CRect rcdb;
	CRect rcx;
	BOOL HasInt = FALSE;

	int lefttopbloc = ComputeCurrentBlocks( rc.left , rc.top );
	rcdb = DbaseSpaceBlockRect( lefttopbloc );

#ifdef DEBUG8
sprintf_s( text,   120, "Scroll Window ( %d %d) (%d,%d) " , rc.left ,rc.top ,rc.right , rc.bottom);
mDebug.CDebugPut((char *)text);
sprintf_s( text,   120, "Main db window ( %d %d) (%d,%d) " , rcdb.left ,rcdb.top ,rcdb.right , rcdb.bottom);
mDebug.CDebugPut((char *)text);
#endif

	rcx.IntersectRect( rcdb , rc );
	int  x_ext =  rcx.right - rcx.left ; // compute width of the main block (0)  - referenced to upper left corner of the scroll window
	int  y_ext =  rcx.bottom -rcx.top  ;

	switch ( iqn )
	{
	case 0:
			rcdb = DbaseSpaceBlockRect( lefttopbloc  );
			HasInt = rcx.IntersectRect( rcdb , rc );
			if ( HasInt == TRUE )
			{
				p->dest_x = 0;
				p->dest_y = 0; 
				p->size_x = rcx.right - rcx.left; 
				p->size_y = rcx.bottom -rcx.top ; 
				p->src_x  = rc.left%BLOCK_SIZE ;    
				p->src_y  = rc.top%BLOCK_SIZE;  
			}
			break;
	case 1:
		    rcdb = DbaseSpaceBlockRect( lefttopbloc+1  );
			HasInt = rcx.IntersectRect( rcdb , rc );
			if ( HasInt == TRUE )
			{
				p->dest_x = x_ext;
				p->dest_y = 0; 
				p->size_x = rcx.right - rcx.left; 
				p->size_y = rcx.bottom -rcx.top ; 
				p->src_x = 0 ; 
				p->src_y = rc.top%BLOCK_SIZE ;   
			}
			break;
	case 2:
			rcdb = DbaseSpaceBlockRect( lefttopbloc+ BLOCKS_IN_ROW  );
			HasInt = rcx.IntersectRect( rcdb , rc );
			if ( HasInt == TRUE )
			{
				p->dest_x = 0;
				p->dest_y = y_ext; 
				p->size_x = rcx.right - rcx.left; 
				p->size_y = rcx.bottom -rcx.top ; 
				p->src_x =  rc.left%BLOCK_SIZE ;  
				p->src_y =  0 ;  
			}
			break;
	case 3:
			rcdb = DbaseSpaceBlockRect( lefttopbloc+ BLOCKS_IN_ROW +1  );
			HasInt = rcx.IntersectRect( rcdb , rc );
			if ( HasInt == TRUE )
			{
				p->dest_x = x_ext;
				p->dest_y = y_ext; 
				p->size_x = rcx.right - rcx.left; 
				p->size_y = rcx.bottom -rcx.top ; 
				p->src_x = 0 ; 
				p->src_y = 0 ;  
			}
			break;
	default:break;

	}

#ifdef DEBUG8
if ( HasInt == TRUE)
{
sprintf_s( text,   120, "(%d) have Intersect:( %d %d) (%d,%d) " , iqn,rcx.left ,rcx.top ,rcx.right , rcx.bottom);
mDebug.CDebugPut((char *)text);
sprintf_s( text,   120, "Coord:dest( %d %d) size(%d,%d)  src(%d,%d)  " , p->dest_x ,p->dest_y , p->size_x,p->size_y ,p->src_x , p->src_y);
mDebug.CDebugPut((char *)text);

}
else 
mDebug.CDebugPut((char *)"No intersection");
#endif

	return HasInt;
}

//////////////////////////////////////////////////////////////
///    Mark dbase buffers as empty (invalid )
///    
/////////////////////////////////////////////////////////////

void CBgrBmp::IvalidateBlocks()
{int i; 
for( i=0; i< NBR_OF_BUFFERS; i++) 
	{
		block_tbl[i] = -1;
		block_uns[i] = 0;
	}
}

/////////////////////////////////////////////////////////////
///  What is the block number containing the point (ptx,pty)
///    
/////////////////////////////////////////////////////////////

int CBgrBmp::ComputeCurrentBlocks( int ptx , int pty )
{
	ptx  = ptx >> WIN_BITS;  pty  = pty >> WIN_BITS;   
	return ptx + pty*BLOCKS_IN_ROW;
}

/////////////////////////////////////////////////////////////
///  What is the Rect containing the point (x,y)
///    
/////////////////////////////////////////////////////////////

CRect CBgrBmp::DbaseSpaceBlockRect( int x,int y )
{
	CRect rc;
	int bl = ComputeCurrentBlocks(  x ,  y );
	rc.left =  WIN_X * (  bl % BLOCKS_IN_ROW );
	rc.top =   WIN_Y * (  bl/BLOCKS_IN_ROW ) ;
	rc.right =  rc.left + WIN_X ;
	rc.bottom = rc.top + WIN_Y ;
	return rc;
}

/////////////////////////////////////////////////////////////
///  What is the Rect of the block number
///    
/////////////////////////////////////////////////////////////

CRect  CBgrBmp::DbaseSpaceBlockRect( int bl )
{
	CRect rc;
	rc.left =  WIN_X * (  bl%BLOCKS_IN_ROW );
	rc.top =   WIN_Y * (  bl/BLOCKS_IN_ROW ) ;
	rc.right =  rc.left + WIN_X ;
	rc.bottom = rc.top + WIN_Y ;
	return rc;
}

/////////////////////////////////////////////////////////////
///  find the new dbase blocks which needs to be used
///  for current scroll  
/////////////////////////////////////////////////////////////

void CBgrBmp::ComputeNewBlocks( CRect rc )
{
	new_block_tbl[0] = ComputeCurrentBlocks (   rc.left , rc.top );
	new_block_tbl[1] = ComputeCurrentBlocks (   rc.right , rc.top );
	new_block_tbl[2] = ComputeCurrentBlocks (   rc.left , rc.bottom );
	new_block_tbl[3] = ComputeCurrentBlocks (   rc.right , rc.bottom );
}

/////////////////////////////////////////////////////////////
///  Mark the blocks which are not going to be used
///  in current scroll ( to empty for new blocks )   
/////////////////////////////////////////////////////////////

void CBgrBmp::MarkUnusedBlocks()
{
	int i;  
	for ( i=0;i< NBR_OF_BUFFERS; i++)
		{	 
			 if (  ( block_tbl[i] == new_block_tbl[0]) || 
					 ( block_tbl[i] == new_block_tbl[1]) || 
						( block_tbl[i] == new_block_tbl[2]) || 
							( block_tbl[i] == new_block_tbl[3]) ) // in use
									continue;
			 if( block_tbl[i] != -1 ) block_uns[i] +=1 ;
		 }
#ifdef  DEBUG9
	DebugTmpBlockTable(0);
	 DebugUnsBlockTable(0);
	 DebugBlockTable(0);
#endif
}

/////////////////////////////////////////////////////////////
///  free block if there is no space
///  using the most not used    
/////////////////////////////////////////////////////////////

int CBgrBmp::FreeOneBlock()
{
	int i;  
	for ( i=0;i< NBR_OF_BUFFERS; i++)  if (  block_tbl[i] == -1 ) return i;
	// need to free block - find the mostly unused block
		
	int j =-1 ; int iuz= 0;
	for ( i=0;i< NBR_OF_BUFFERS; i++)
		if ( block_uns[i] > iuz  ) { j =i; iuz = block_uns[i];}
	
	if ( (j >= 0 )  && ( j < NBR_OF_BUFFERS))
		{  block_tbl[j] = -1; return j; }
	
#ifdef  DEBUG9
 	sprintf_s( text, 120,"Free: fail j =%d  %d" , j, iuz );
	mDebug.CDebugPut((char *)text);
#endif
	return 0;
}

/////////////////////////////////////////////////////////////
///  Verify if new dbase memory block needs to be loaded
///  or already exisitng   
/////////////////////////////////////////////////////////////

void CBgrBmp::UpdateNewBlocks()
{
	int i,j;
	for ( i=0; i< 4; i++)
		 {
			BOOL block_exists = FALSE;
			for ( j=0; j< NBR_OF_BUFFERS; j++)
				if (   new_block_tbl[i] == block_tbl[j] ) { block_exists = TRUE; break;}

			if ( block_exists == FALSE ) LoadBlock ( new_block_tbl[i] );

		 }
}

////////////////////////////////////////////////////////////////
// only for simulation - load block pattern
////////////////////////////////////////////////////////////////

#ifndef WINAPP_	
void  CBgrBmp::LoadMemPoint ( Tbl_mem  *p , int block )
{
	int row ,col;
	for ( row =0; row < 16; row++)
		for ( col =0;col < 16; col++)
		{
		    int n = block << 16;
			n += row << 8; n += col; p->t[col][row] = n;
		}
}
#endif

/////////////////////////////////////////////////////////////
///  Load dbase memory block to the free buffer and
///  mark the buffer for current scroll   
/////////////////////////////////////////////////////////////

void CBgrBmp::LoadBlock ( int block )
{
	int i;
#ifdef WINAPP_
	CRect std(0,0,WIN_X,WIN_Y);
#endif

	i = FreeOneBlock();

#ifdef  DEBUG9
 	sprintf_s( text, 120,"Free:[%d]" , i );
	mDebug.CDebugPut((char *)text);
#endif

#ifdef WINAPP_
	pDoc->Export_LoadDataBaseBlock  ( block  , *( HDC*)hdcTmpMem[i] , &std ) ;
#else
	LoadMemPoint ( mem_[i] , block );
	printf("\nLoad block : dest storage:(%d) block_no:%d ", i , block ); 
#endif
	block_tbl[i]  = block;
	block_uns[i]  = 0;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
 
 
