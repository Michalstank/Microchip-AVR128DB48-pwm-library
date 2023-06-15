# AVR128DB48-PWM-LIBRARY

This repository hosts a PWM Library for the card AVR128DB48, it is primaly based on the PWM library done for capstone project done for NTNU Course - IELET2111 - Microcontroller Systems.

# Documentation

Summary:

This is an Library for the card AVR128DB48 with main focus on the PWM Generation as well as Measurement. The Library was made in such a way that it would be easy to use for both new and advanced users. It mainly focuses on simplification of existing peripherals for both streamlined and quick way of setting them up.

## Which peripherals are covered

|Peripheral|Covered Functionality|
|----------|--------------------|
|`TCA0`|Dual Slope, Single Mode|
|`TCA1`|Dual Slope, Single Mode|
|`TCB0`|Pulse Width Measurement|
|`EVSYS`|Integration with TCB0 for PWM, Uses Channel 0|
|`PORTMUX`|Waveform Output setup for TCA0 & TCA1|

## How to use the Library

Simply download both the .c and .h files and add them to the project. Therefore Include the PWM.h File where you want to use it. Lastly configure the registers of the library for your goals.

## Example Initialization

An example of quick setup of TCA0 Timer for 25kHz output:

```
#include "PWM.h"

int main(void){
  PWM_CTRL.MAIN_CTRL = PWM_MASTER_ENABLE_bm | PWM_TCA0_ENABLE_bm | PWM_PORTMUX_OVERRIDE_bm;

  PWM_CTRL.CMP_CTRL = PWM_TCA0_CMP_0_bm;
  
  PWM_CTRL.TCA0_PERBUF_VAL = 0x50;
  
  PWM_CTRL.PWM_CMPBUF_DUTYCYCLE[0] = 0x50/2; //50% Duty Cycle
  
  PWM_INIT();
  
  while(1){
  
    PWM_RUN();
  
  }

return 0;
}
```

## Interrupt Handling

WIP

## "Register" Summary

All of the "registers" are part of the main library struct which can be referred to by PWM_CTRL.

List of "Registers in the library and their objectives:

WIP - EXTERNAL FILE



