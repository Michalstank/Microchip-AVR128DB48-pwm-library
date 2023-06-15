# AVR128DB48-PWM-LIBRARY

This repository hosts a PWM Library for the card AVR128DB48, it is primaly based on the PWM library done for capstone project done for NTNU Course - IELET2111 - Microcontroller Systems.

# Documentation

Summary:

An overview over the functionality of the library.

## Which peripherals are covered

|Peripheral|Covered Functionality|
|----------|--------------------|
|TCA0|Dual Slope, Single Mode|
|TCA1|Dual Slope, Single Mode|
|TCB0|Pulse Width Measurement|
|EVSYS|Integration with TCB0 for PWM, Uses Channel 0|
|PORTMUX|Waveform Output setup for TCA0 & TCA1|

## How to use the Library

Simply download both the .c and .h files and add them to the project. Therefore Include the PWM.h File where you want to use it. Lastly configure the registers of the library for your goals.

## Example Initialization

## Interrupt Handling

## "Register" Summary

