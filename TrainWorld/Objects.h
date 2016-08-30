


#pragma once


#define		ObjNothing				0
#define	 	ObjStraightRail			1
#define	 	ObjBendRail				2
#define	 	ObjRailSwitch			3
#define	 	ObjRailSwitch2			4 
#define	 	ObjRailEnd				5
#define	 	ObjRailControl			6 
#define	 	ObjTrain				7
#define	 	ObjSemaphore			8
#define	 	ObjCntDis    			9



class CRail   
	{

 public:
	 CRail();

public:
	 	  BYTE   mtype,mSelected,mode1,mode2;
 private:
	 //DEBUGDRAWDATASTRUCT mDebugData;
	// DRAWDATASTRUCT  mDrawData;

	 //CRail  *Indexes[3]; //  fast indexing
	 //int     mIndexes[3];

	 //friend class CBendRail ;
	 //friend class CStraightRail ;
 	 //friend class CRailSwitch ;
	 //friend class CEndRail;
	 //friend class CSemphore;
};