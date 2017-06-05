#include "iodefine.h"
#include "vect.h"
#include <machine.h>

#define NULL ((void *)0)

#define TASK_TIMER_NUM (32)
#define TASK_TIMER_UNUSED (0)
#define TASK_TIMER_RUNNING (1)

typedef struct {
	unsigned char state;		// �^�C�}�[���
	unsigned short time_set;	// �ݒ莞��(0.1msec)
	unsigned short time_remaining;	// �c�莞��
	void (*cbfunc)();		// �R�[���o�b�N�֐�
} T_TASK_TIMER;

// �O���[�o���ϐ�
T_TASK_TIMER gTaskTimer[TASK_TIMER_NUM];

// �v���g�^�C�v�錾
void handleTaskTimer(void);

void initTimer(void)
{
	int i;
	
	// �y�R���y�A�}�b�`�^�C�}�[�����ݒ�z
	// ���W���[���X�g�b�v����
	MSTP(CMT0) = 0;
	
	// �R���y�A�}�b�`�^�C�}�[0�ݒ�
	// ����:PCLK/32(�J�E���^�l750-1��1msec)
	CMT0.CMCR.BIT.CKS = 1;
	// �J�E���^�N���A
	CMT0.CMCNT = (unsigned short)0;
	// �R���y�A�}�b�`�萔
	CMT0.CMCOR = (unsigned short)(75 - 1);
	
	// �y�^�X�N�n���h�����O�^�C�}�[�������z
	for(i = 0; i < TASK_TIMER_NUM; i++) {
		gTaskTimer[i].state = TASK_TIMER_UNUSED;
	}
}

void startTimer(void)
{
//	// �R���y�A�}�b�`�^�C�}�[0���荞�݋���
//	CMT0.CMCR.BIT.CMIE = 1;
	CMT0.CMCR.WORD |= 0x0080 | 0x0040;
	IEN(CMT0, CMI0) = 1;
	IPR(CMT0, CMI0) = 1;

	// CMT0.CMCNT�J�E���g����J�n
	CMT.CMSTR0.BIT.STR0 = 1;
}

// �R���y�A�}�b�`�^�C�}�[0���荞�݃n���h���[
// ����:0.1msec�Ȃ͂�
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
