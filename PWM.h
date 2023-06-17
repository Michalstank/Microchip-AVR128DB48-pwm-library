#pragma once

/*
	NAME: MICROCHIP-AVR128DB48-PWM-LIBRARY
	AUTHOR: MICHALSTANK
	VERSION: 0.5.0
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef uint8_t BITMASK;

//BITMASKS FOR MAIN_CTRL
#define	PWM_MASTER_ENABLE_bm		0b00000001
#define	PWM_TCA0_ENABLE_bm			0b00000010
#define	PWM_TCA1_ENABLE_bm			0b00000100
#define	PWM_TCB_ENABLE_bm			0b00001000
#define	PWM_PORTMUX_OVERRIDE_bm		0b00010000
#define	PWM_INTERRUPT_ENABLE_bm		0b00100000
#define	PWM_AUTOMODE_ENABLE_bm		0b01000000
#define	PWM_DATASAVING_ENABLE_bm	0b10000000

//BITMASKS FOR CMP_CTRL
#define	PWM_TCA0_CMP_0_bm			0b00000001
#define	PWM_TCA0_CMP_1_bm			0b00000010
#define	PWM_TCA0_CMP_2_bm			0b00000100
#define	PWM_TCA1_CMP_0_bm			0b00010000
#define	PWM_TCA1_CMP_1_bm			0b00100000
#define	PWM_TCA1_CMP_2_bm			0b01000000

//FUNCTION POINTERS
typedef void (*PWM_RUN_POINTER)(void);

typedef void (*TCB0_OVF_POINTER)(void);
typedef void (*TCB0_CAPT_POINTER)(void);

typedef void (*TCA0_OVF_POINTER)(void);
typedef void (*TCA0_CMP0_POINTER)(void);
typedef void (*TCA0_CMP1_POINTER)(void);
typedef void (*TCA0_CMP2_POINTER)(void);

//STORAGE STRUCT USED FOR DATALOGGING
struct PWM_DATA{
	BITMASK FAN_ID;															//		 NR
	uint16_t PWM_OUTPUT;													//	  DUTY CYCLE
	uint16_t PWM_READ;														//  R_FAN1 R_FAN2
};

struct PWM_CONTROLLER{
	BITMASK MAIN_CTRL;
	/*
	0 - MASTER PWM ENABLE													
	1 - ENABLE TCA0															
	2 - ENABLE TCA1															
	3 - ENABLE TCB0															
	4 - ENABLE PORTMUX OVERRIDE												
	5 - ENABLE MASTER INTERRUPT												
	6 - ENABLE AUTO RUN														
	7 - ENABLE DATA SAVING													
	*/
	
	BITMASK CMP_CTRL;
	//CONTROLS WHICH FAN IS TO BE TURNED ON
	//PORT NAME: -CCC-DDD
	//TCAn CMPn: -210-210
	//REGISTER: b00000000;
		
	BITMASK READ_CTRL;
	//ENABLES WHICH FAN IS TO BE READ
	//0b00000000, 1 to enable reading of PWM signal
	
	uint8_t READ_SELECT;
	//Value of which pin to read, 0x40 to 0x47
	
	uint16_t TCA0_PERBUF_VAL;
	uint16_t TCA1_PERBUF_VAL;
	//CONTROLS WHICH VALUE TO LOAD AS PERBUF MAX
	
	uint16_t PWM_CMPBUF_DUTYCYCLE[6];
	//CONTROLS DUTY CYCLE OF THE FANS
	
	uint8_t AUTOSCALER[6];
	//TEMPERATURE VALUE
	
	volatile struct PWM_DATA DATALOG[96];
	//LIBRARY INTERNAL MEMORY FOR DATASAVING
	
	//Function Pointer to PWM_RUN in case the user wants to write their own.
	PWM_RUN_POINTER PWM_RUN_fp;
		
	//Function pointer for TCB0 OVF, Counter Overflow Interrupt.
	TCB0_OVF_POINTER TCB0_OVF_INT_fp;
	
	//Function pointer for TCB0 CAPT, Event capture interrupt.
	TCB0_CAPT_POINTER TCB0_CAPT_INT_fp;
	
	//Function Pointer for TCA0 OVF, Counter Overflow Interrupt. 
	TCA0_OVF_POINTER TCA0_OVF_INT_fp;
	
	//Function Pointer for TCA0 CMP0 Match Interrupt
	TCA0_CMP0_POINTER TCA0_CMP0_INT_fp;
	
	//Function Pointer for TCA0 CMP1 Match Interrupt
	TCA0_CMP1_POINTER TCA0_CMP1_INT_fp;
	
	//Function Pointer for TCA0 CMP2 Match Interrupt
	TCA0_CMP2_POINTER TCA0_CMP2_INT_fp;
};

//initalization of ctrl for the library
struct PWM_CONTROLLER PWM_CTRL;

//INIT FUNCTIONS

void PWM_INIT();															//Main Init Function

void TCA0_CMP_INIT();														//TCA0 Compare Channel Initialization
void TCA0_CMP_INIT();														//TCA1 Compare Channel Initialization

void TCA0_SINGLE_INIT();													//TCA0 Init Function
void TCA1_SINGLE_INIT();													//TCA1 Init Function

void TCB_INIT();															//TCB0 Init Function

//FUNCTIONS
void PWM_RUN();																//'Update()' esque function
void PWM_Preload();														

void FP_INIT();																//Connects functions listed above to the struct
void FP_HOLDER();															//Temporary Function for the Function Pointers, just so you dont get a NULL pointer.
