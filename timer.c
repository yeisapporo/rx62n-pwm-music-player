#include "iodefine.h"
#include "vect.h"
#include <machine.h>

#define NULL ((void *)0)

#define TASK_TIMER_NUM (32)
#define TASK_TIMER_UNUSED (0)
#define TASK_TIMER_RUNNING (1)

typedef struct {
	unsigned char state;		// タイマー状態
	unsigned short time_set;	// 設定時間(0.1msec)
	unsigned short time_remaining;	// 残り時間
	void (*cbfunc)();		// コールバック関数
} T_TASK_TIMER;

// グローバル変数
T_TASK_TIMER gTaskTimer[TASK_TIMER_NUM];

// プロトタイプ宣言
void handleTaskTimer(void);

void initTimer(void)
{
	int i;
	
	// 【コンペアマッチタイマー初期設定】
	// モジュールストップ解除
	MSTP(CMT0) = 0;
	
	// コンペアマッチタイマー0設定
	// 分周:PCLK/32(カウンタ値750-1で1msec)
	CMT0.CMCR.BIT.CKS = 1;
	// カウンタクリア
	CMT0.CMCNT = (unsigned short)0;
	// コンペアマッチ定数
	CMT0.CMCOR = (unsigned short)(75 - 1);
	
	// 【タスクハンドリングタイマー初期化】
	for(i = 0; i < TASK_TIMER_NUM; i++) {
		gTaskTimer[i].state = TASK_TIMER_UNUSED;
	}
}

void startTimer(void)
{
//	// コンペアマッチタイマー0割り込み許可
//	CMT0.CMCR.BIT.CMIE = 1;
	CMT0.CMCR.WORD |= 0x0080 | 0x0040;
	IEN(CMT0, CMI0) = 1;
	IPR(CMT0, CMI0) = 1;

	// CMT0.CMCNTカウント動作開始
	CMT.CMSTR0.BIT.STR0 = 1;
}

// コンペアマッチタイマー0割り込みハンドラー
// 周期:0.1msecなはず
void Excep_CMT0_CMI0(void)
{
#if 0
	static int cnt = 0;
	cnt++;
	if(cnt >= 500) {
		PORT0.DR.BIT.B5 ^= 1;
		cnt = 0;
	}
	
	//beep
	PORT0.DR.BIT.B7 ^= 1;
#endif
	handleTaskTimer();
}

__inline void handleTaskTimer(void)
{
	int i;
	for(i = 0; i < TASK_TIMER_NUM; i++) {
		if(gTaskTimer[i].state == TASK_TIMER_RUNNING && gTaskTimer[i].time_set != 0) {
			gTaskTimer[i].time_remaining--;
			if(gTaskTimer[i].time_remaining == 0) {
				gTaskTimer[i].state = TASK_TIMER_UNUSED;
				gTaskTimer[i].cbfunc();
			}
		}
	}
}

int setTimer(unsigned short time, void (*cbfunc)(void))
{
	int i;
	
	if(time != 0 && cbfunc != NULL) {
		for(i = 0; i < TASK_TIMER_NUM; i++) {
			if(gTaskTimer[i].state == TASK_TIMER_UNUSED) {
				gTaskTimer[i].state = TASK_TIMER_RUNNING;
				gTaskTimer[i].time_set = time;
				gTaskTimer[i].time_remaining = time;
				gTaskTimer[i].cbfunc = cbfunc;
				
				return i;
			}
		}
		
		return -2;
	} else {
		return -1;
	}
}
