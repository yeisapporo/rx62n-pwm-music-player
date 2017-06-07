/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"

#include "iodefine.h"
#include <machine.h>

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif



		
void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif


void taskBeep(void)
{
	static unsigned short d = 440;
	static unsigned short cnt = 0;
	cnt++;
	if(cnt >= 7500 / d) {
		d--;
		cnt = 0;
	}
	setTimer(d, taskBeep);
	PORT0.DR.BIT.B7 ^= 1;
}

void taskBlink(void)
{
	setTimer(5000, taskBlink);
	PORT0.DR.BIT.B5 ^= 1;
}



void main(void)
{
//	int cnt = 0;
//	int cnt2 = 0;
	
	volatile int xx;
	
	//�y�N���b�N�ݒ�z
	// EXTAL = 12000000Hz
	// ICLK = EXTAL * 2 = 96000000Hz
	// PCLK = EXTAL * 2 = 24000000Hz
	SYSTEM.SCKCR.LONG = (unsigned long)0x00c20200;
	
	// �y�|�[�g(LED)�ݒ�z
	PORT0.DDR.BYTE = 0xff;
	PORT0.DR.BIT.B5 = 0;	// user LED
	PORT0.DR.BIT.B7 = 0;	// buzzer
	
	// ���Ӄ��W���[���X�g�b�v��Ԃ̉���(CMT0)
//	SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;
	
	// PWM(MTU0�����ݒ�)
	initPWM();
	// PWM�X�^�[�g
	startPWM();

	// �R���y�A�}�b�`�^�C�}�[�����ݒ�
	initTimer();
	
	// �R���y�A�}�b�`�^�C�}�[�n��
	startTimer();
	
	// interrupt enable(CPU)
	setpsw_i();

	
	taskBlink();
	//taskBeep();

	taskPlaySound();
	taskVibrato();
	
	for(;;) {
	
		
		
		
	}

}

#ifdef __cplusplus
void abort(void)
{

}
#endif
