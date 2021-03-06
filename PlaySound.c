#include "iodefine.h"
#include "vect.h"
#include <machine.h>
//#include <stdio.h>
//#include "lowsrc.h"


enum {
	PITCH_RST = 0,	// 休符
	PITCH_2C_,
	PITCH_2CS,
	PITCH_2D_,
	PITCH_2DS,
	PITCH_2E_,
	PITCH_2F_,
	PITCH_2FS,
	PITCH_2G_,
	PITCH_2GS,
	PITCH_2A_,
	PITCH_2AS,
	PITCH_3B_,

	PITCH_3C_,
	PITCH_3CS,
	PITCH_3D_,
	PITCH_3DS,
	PITCH_3E_,
	PITCH_3F_,
	PITCH_3FS,
	PITCH_3G_,
	PITCH_3GS,
	PITCH_3A_,
	PITCH_3AS,
	PITCH_4B_,

	PITCH_4C_,
	PITCH_4CS,
	PITCH_4D_,
	PITCH_4DS,
	PITCH_4E_,
	PITCH_4F_,
	PITCH_4FS,
	PITCH_4G_,
	PITCH_4GS,
	PITCH_4A_,
	PITCH_4AS,
	PITCH_5B_,
};


int gScaleTable[] = {
	   0,	// PITCH_RST
	7645,	// PITCH_2C_
	7215,	// PITCH_2CS
	6810,	// PITCH_2D_
	6428,	// PITCH_2DS
	6067,	// PITCH_2E_
	5727,	// PITCH_2F_
	5405,	// PITCH_2FS
	5102,	// PITCH_2G_
	4816,	// PITCH_2GS
	4545,	// PITCH_2A_
	4290,	// PITCH_2AS
	4050,	// PITCH_3B_

	3822,	// PITCH_3C_
	3608,	// PITCH_3CS
	3405,	// PITCH_3D_
	3214,	// PITCH_3DS
	3034,	// PITCH_3E_
	2863,	// PITCH_3F_
	2703,	// PITCH_3FS
	2551,	// PITCH_3G_
	2408,	// PITCH_3GS
	2273,	// PITCH_3A_
	2145,	// PITCH_3AS
	2025,	// PITCH_4B_

	1911,	// PITCH_4C_
	1804,	// PITCH_4CS
	1703,	// PITCH_4D_
	1607,	// PITCH_4DS
	1517,	// PITCH_4E_
	1432,	// PITCH_4F_
	1351,	// PITCH_4FS
	1276,	// PITCH_4G_
	1204,	// PITCH_4GS
	1136,	// PITCH_4A_
	1073,	// PITCH_4AS
	1012,	// PITCH_5B_
};


#if 0
// カエルの歌
int soundTable[][2] = {	
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_3F_, 100},
		{PITCH_3E_, 100},
		{PITCH_3D_, 100},
		{PITCH_3C_, 100},
		{PITCH_RST, 100},
		
		{PITCH_3E_, 100},
		{PITCH_3F_, 100},
		{PITCH_3G_, 100},
		{PITCH_3A_, 100},
		{PITCH_3G_, 100},
		{PITCH_3F_, 100},
		{PITCH_3E_, 100},
		{PITCH_RST, 100},
		
		{PITCH_3C_, 100},
		{PITCH_RST, 100},
		{PITCH_3C_, 100},
		{PITCH_RST, 100},
		{PITCH_3C_, 100},
		{PITCH_RST, 100},
		{PITCH_3C_, 100},
		{PITCH_RST, 100},

		{PITCH_3C_, 25},
		{PITCH_RST, 25},
		{PITCH_3C_, 25},
		{PITCH_RST, 25},

		{PITCH_3D_, 25},
		{PITCH_RST, 25},
		{PITCH_3D_, 25},
		{PITCH_RST, 25},

		{PITCH_3E_, 25},
		{PITCH_RST, 25},
		{PITCH_3E_, 25},
		{PITCH_RST, 25},

		{PITCH_3F_, 25},
		{PITCH_RST, 25},
		{PITCH_3F_, 25},
		{PITCH_RST, 25},

		{PITCH_3E_, 100},
		{PITCH_3D_, 100},
		{PITCH_3C_, 100},
		{PITCH_RST, 100},
};

#else

#if 0
// チューリップ
int soundTable[][2] = {	
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_RST, 100},
		
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_RST, 100},

		{PITCH_3G_, 100},
		{PITCH_3E_, 100},
		{PITCH_3D_, 100},
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_3D_, 100},
		{PITCH_RST, 100},
		
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_RST, 100},
		
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_RST, 100},

		{PITCH_3G_, 100},
		{PITCH_3E_, 100},
		{PITCH_3D_, 100},
		{PITCH_3C_, 100},
		{PITCH_3D_, 100},
		{PITCH_3E_, 100},
		{PITCH_3C_, 100},
		{PITCH_RST, 100},

		{PITCH_3G_,  90},
		{PITCH_RST,  10},
		{PITCH_3G_,  90},
		{PITCH_RST,  10},
		{PITCH_3E_, 100},
		{PITCH_3G_, 100},
		{PITCH_3A_,  90},
		{PITCH_RST,  10},
		{PITCH_3A_,  90},
		{PITCH_RST,  10},
		{PITCH_3G_, 100},
		{PITCH_RST, 100},

		{PITCH_3E_,  90},
		{PITCH_RST,  10},
		{PITCH_3E_,  90},
		{PITCH_RST,  10},
		{PITCH_3D_,  90},
		{PITCH_RST,  10},
		{PITCH_3D_,  90},
		{PITCH_RST,  10},
		{PITCH_3C_, 200},
		{PITCH_RST, 200},
};
#else
int soundTable[][2] = {	
		{PITCH_2AS,  60},
		
		{PITCH_3G_, 240},
		{PITCH_3F_,  60},
		{PITCH_3G_,  60},
		{PITCH_3F_, 180},
		{PITCH_3DS, 120},
		{PITCH_2AS,  60},
		
		{PITCH_3G_, 110},
		{PITCH_3C_,  20},
		{PITCH_3CS,  10},
		{PITCH_2AS,  10},
		{PITCH_3C_,  10},
		{PITCH_3C_,  10},
		{PITCH_4C_, 120},
		{PITCH_3G_,  60},
		{PITCH_3AS, 180},
		{PITCH_3GS, 120},
		{PITCH_3G_,  60},
		
		{PITCH_3F_, 180},
		{PITCH_3G_, 120},
		{PITCH_3D_,  60},
		{PITCH_3DS, 180},
		{PITCH_3C_, 180},
		
		{PITCH_2AS,  60},
		{PITCH_4D_,  60},
		{PITCH_4C_,  60},
		{PITCH_3AS,  30},
		{PITCH_3GS,  30},
		{PITCH_3G_,  30},
		{PITCH_2GS,  30},
		{PITCH_3C_,  30},
		{PITCH_3D_,  30},
		{PITCH_3DS, 300},
		
//		{PITCH_RST, 0},
		
		
		
		

		
		
};
#endif

#endif

int gTGRD = 0;
int gTGRC = 0;

void initPWM(void)
{
	// wakeup MTU0
	MSTP(MTU0) = 0;
	// counts on PCLK/1
	MTU0.TCR.BIT.TPSC = 0;
	// TCNT0 is cleared by TGRC compare match
	MTU0.TCR.BIT.CCLR = 5;
	// PWM mode
	MTU0.TMDR.BIT.MD = 2;
	// initial:L -> compare match:H
	MTU0.TIORL.BIT.IOC = 2;
	// initial:L -> compare match:L
	MTU0.TIORL.BIT.IOD = 1;
	// count is 24MHz*100us-1
	MTU0.TGRC = 24 * 1000 - 1;
	// PWM duty is 50%
	MTU0.TGRD = 24 * 1000 * 0.5 - 1;
}

void startPWM(void)
{
	// count start
	MTUA.TSTR.BIT.CST0 = 1;
}

void cutSound(void)
{
#if 1
	MTU0.TGRC = gTGRC = 0;
	MTU0.TGRD = gTGRD = 0;
#else
	MTU0.TGRC += 800;
	MTU0.TGRD += 100;
	
	gTGRC = MTU0.TGRC;
	gTGRD = MTU0.TGRD;
#endif
}

#if 0
void taskPlaySound(void)
{
	static int cursor = 0;

	setTimer(soundTable[cursor][1] * 75/* tempo */, taskPlaySound);
		
	MTU0.TGRC = gTGRC = 12 * gScaleTable[soundTable[cursor][0]] - 1;
	MTU0.TGRD = gTGRD = 12 * gScaleTable[soundTable[cursor][0]] * 0.5 - 1;

	if(++cursor == sizeof(soundTable) / sizeof(int) / 2) {
		cursor = 0;
	}
}
#else
void taskPlaySound(void)
{
	static int cursor = 0;
	int timeout;
	int cut_time;

	timeout = soundTable[cursor][1] * 75; /* tempo */
	setTimer(timeout, taskPlaySound);
	if(timeout > 800) {
		cut_time = timeout - 800;
	} else {
		cut_time = 0;
	}
	if(cut_time != 0) {
		setTimer(cut_time, cutSound);
	}
	
	MTU0.TGRC = gTGRC = 12 * gScaleTable[soundTable[cursor][0]] - 1;
	MTU0.TGRD = gTGRD = 12 * gScaleTable[soundTable[cursor][0]] * 0.5 - 1;

///////////////// debug out //////////////
//	printf("Note:%d:%d\n", soundTable[cursor][0], timeout);


//////////////////////////////////////////
	
	if(++cursor == sizeof(soundTable) / sizeof(int) / 2) {
		cursor = 0;
	}
	
}
#endif

void taskVibrato(void)
{
#if 1
	static int cnt = 0;
	static int variational = -4;

	setTimer(5, taskVibrato);

	gTGRC = MTU0.TGRC;
	gTGRC += variational;
	if(++cnt >= 128) {
		cnt = 0;
		variational = -variational;
	}
	MTU0.TGRC = gTGRC;
#else
	static int cnt = 0;
	static int variational = -32;

	setTimer(10, taskVibrato);

	gTGRD = MTU0.TGRD;
	gTGRD += variational;
	if(++cnt >= 128) {
		cnt = 0;
		variational = -variational;
	}
	MTU0.TGRD = gTGRD;
#endif
}
