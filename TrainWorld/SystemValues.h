
#pragma once

#define WINAPP_	


#ifdef WINAPP_	
#define BLOCKS_IN_ROW  23
#define BLOCKS_IN_COL  16

#define STD_AUX_WIN  32
#define SCALE_COEEF 5
// bigger map need to chnage also WIN_X_AUX
//#define STD_AUX_WIN  64
//#define SCALE_COEEF 4

// 1024
/*
#define BLOCK_SIZE  1024
#define PIXEL_BLOCK 1024
#define WIN_X  1024
#define WIN_Y  1024
#define WIN_X_AUX 1024
#define WIN_Y_AUX 1024
#define WIN_BITS 10
#define SCALE_INTRER 5
*/

// 2048  
// size of the memory bitamp 
#define WIN_X_BITMAP  2048
#define WIN_Y_BITMAP  2048

#define BLOCK_SIZE  2048
#define PIXEL_BLOCK 2048
#define WIN_X  2048
#define WIN_Y  2048
#define WIN_X_AUX 1024
#define WIN_Y_AUX 1024
#define WIN_BITS 11
#define SCALE_INTRER 6 
 
// 4096
/*
#define BLOCK_SIZE  4096
#define PIXEL_BLOCK 4096
#define WIN_X  4096
#define WIN_Y  4096
#define WIN_X_AUX 1024
#define WIN_Y_AUX 1024
#define WIN_BITS 12
#define SCALE_INTRER 7 
 */
 
 

#else
#define BLOCKS_IN_ROW  23
#define BLOCKS_IN_COL  16

#define BLOCK_SIZE  16
#define PIXEL_BLOCK 16 
#define WIN_X   16
#define WIN_Y   16
#define WIN_BITS 4
#define Filter   0xF
#endif

#define NBR_OF_BUFFERS  12