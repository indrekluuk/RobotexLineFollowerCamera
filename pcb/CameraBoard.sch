EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:arduino
LIBS:camera_ov7670
LIBS:levelshifter_74hc4050d
LIBS:tft_1.8inch
LIBS:shiftregister_74hc595
LIBS:shiftregister_74hc165
LIBS:CameraBoard-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L arduino_mini U?
U 1 1 57336257
P 2550 3250
F 0 "U?" H 3050 2300 70  0000 C CNN
F 1 "arduino_mini" H 3300 2200 70  0000 C CNN
F 2 "DIL20" H 2550 3200 60  0000 C CNN
F 3 "" H 2550 3250 60  0000 C CNN
	1    2550 3250
	1    0    0    -1  
$EndComp
$Comp
L Camera_OV7670 OV7670?
U 1 1 57336349
P 9350 1900
F 0 "OV7670?" H 9950 900 60  0000 C CNN
F 1 "Camera_OV7670" H 10100 1050 60  0000 C CNN
F 2 "" H 9300 2950 60  0000 C CNN
F 3 "" H 9300 2950 60  0000 C CNN
	1    9350 1900
	1    0    0    -1  
$EndComp
Text GLabel 1650 2450 1    60   Input ~ 0
Pixel_D0
Text GLabel 10150 1350 2    60   Input ~ 0
Pixel_D0
Text GLabel 10150 1500 2    60   Input ~ 0
Pixel_D1
Text GLabel 10150 1650 2    60   Input ~ 0
Pixel_D2
Text GLabel 10150 1800 2    60   Input ~ 0
Pixel_D3
Text GLabel 1500 2450 1    60   Input ~ 0
Pixel_D1
Text GLabel 1350 2450 1    60   Input ~ 0
Pixel_D2
Text GLabel 1200 2450 1    60   Input ~ 0
Pixel_D3
Text GLabel 10150 1950 2    60   Input ~ 0
Pixel_D4
Text GLabel 10150 2100 2    60   Input ~ 0
Pixel_D5
Text GLabel 10150 2250 2    60   Input ~ 0
Pixel_D6
Text GLabel 10150 2400 2    60   Input ~ 0
Pixel_D7
Text GLabel 3650 3200 2    60   Input ~ 0
Pixel_D7
Text GLabel 3650 3350 2    60   Input ~ 0
Pixel_D6
Text GLabel 3650 3500 2    60   Input ~ 0
Pixel_D5
Text GLabel 3650 3650 2    60   Input ~ 0
Pixel_D4
Wire Wire Line
	3250 3200 3650 3200
Wire Wire Line
	3250 3300 3450 3300
Wire Wire Line
	3450 3300 3450 3350
Wire Wire Line
	3450 3350 3650 3350
Wire Wire Line
	3250 3650 3650 3650
Wire Wire Line
	3250 3550 3450 3550
Wire Wire Line
	3450 3550 3450 3500
Wire Wire Line
	3450 3500 3650 3500
Wire Wire Line
	9900 1350 10150 1350
Wire Wire Line
	9900 1500 10150 1500
Wire Wire Line
	9900 1650 10150 1650
Wire Wire Line
	9900 1800 10150 1800
Wire Wire Line
	9900 1950 10150 1950
Wire Wire Line
	9900 2100 10150 2100
Wire Wire Line
	9900 2250 10150 2250
Wire Wire Line
	9900 2400 10150 2400
Wire Wire Line
	950  1650 3800 1650
Wire Wire Line
	3800 1650 8800 1650
Wire Wire Line
	950  1650 950  3450
Wire Wire Line
	950  3450 1850 3450
Wire Wire Line
	800  1500 3450 1500
Wire Wire Line
	3450 1500 8800 1500
Wire Wire Line
	800  1500 800  3550
Wire Wire Line
	800  3550 1850 3550
$Comp
L R R?
U 1 1 57336A05
P 3450 1000
F 0 "R?" V 3530 1000 50  0000 C CNN
F 1 "10k" V 3450 1000 50  0000 C CNN
F 2 "" V 3380 1000 50  0000 C CNN
F 3 "" H 3450 1000 50  0000 C CNN
	1    3450 1000
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 57336A6C
P 3800 1000
F 0 "R?" V 3880 1000 50  0000 C CNN
F 1 "10k" V 3800 1000 50  0000 C CNN
F 2 "" V 3730 1000 50  0000 C CNN
F 3 "" H 3800 1000 50  0000 C CNN
	1    3800 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3450 1150 3450 1500
Connection ~ 3450 1500
Wire Wire Line
	3800 1150 3800 1650
Connection ~ 3800 1650
$Comp
L LevelShifter_74HC4050D LS?
U 1 1 573372B0
P 6000 3100
F 0 "LS?" H 6200 3650 60  0000 C CNN
F 1 "LevelShifter_74HC4050D" H 6850 2300 60  0000 C CNN
F 2 "" H 6000 3100 60  0000 C CNN
F 3 "" H 6000 3100 60  0000 C CNN
	1    6000 3100
	1    0    0    -1  
$EndComp
$Comp
L TFT_1.8inch TFT?
U 1 1 57337659
P 9350 4600
F 0 "TFT?" H 9850 4200 60  0000 C CNN
F 1 "TFT_1.8inch" V 9800 5050 60  0000 C CNN
F 2 "" H 9400 5100 60  0000 C CNN
F 3 "" H 9400 5100 60  0000 C CNN
	1    9350 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 57337E50
P 2550 4800
F 0 "#PWR?" H 2550 4550 50  0001 C CNN
F 1 "GND" H 2550 4650 50  0000 C CNN
F 2 "" H 2550 4800 50  0000 C CNN
F 3 "" H 2550 4800 50  0000 C CNN
	1    2550 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 57337E70
P 9500 3250
F 0 "#PWR?" H 9500 3000 50  0001 C CNN
F 1 "GND" H 9500 3100 50  0000 C CNN
F 2 "" H 9500 3250 50  0000 C CNN
F 3 "" H 9500 3250 50  0000 C CNN
	1    9500 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 57337E96
P 9500 5250
F 0 "#PWR?" H 9500 5000 50  0001 C CNN
F 1 "GND" H 9500 5100 50  0000 C CNN
F 2 "" H 9500 5250 50  0000 C CNN
F 3 "" H 9500 5250 50  0000 C CNN
	1    9500 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3700 9600 3700
Wire Wire Line
	9600 3700 10850 3700
Connection ~ 9600 3700
$Comp
L GND #PWR?
U 1 1 57338279
P 5850 3900
F 0 "#PWR?" H 5850 3650 50  0001 C CNN
F 1 "GND" H 5850 3750 50  0000 C CNN
F 2 "" H 5850 3900 50  0000 C CNN
F 3 "" H 5850 3900 50  0000 C CNN
	1    5850 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 3550 7600 3550
Wire Wire Line
	7600 3550 7600 4900
Wire Wire Line
	7600 4900 8800 4900
Wire Wire Line
	6550 3400 7750 3400
Wire Wire Line
	7750 3400 7750 4750
Wire Wire Line
	7750 4750 8800 4750
Wire Wire Line
	6550 3250 7900 3250
Wire Wire Line
	7900 3250 7900 4600
Wire Wire Line
	7900 4600 8800 4600
Wire Wire Line
	6550 3100 8050 3100
Wire Wire Line
	8050 3100 8050 4450
Wire Wire Line
	8050 4450 8800 4450
Wire Wire Line
	6550 2950 8200 2950
Wire Wire Line
	8200 2950 8200 4300
Wire Wire Line
	8200 4300 8800 4300
Wire Wire Line
	6550 2800 7050 2800
Wire Wire Line
	7050 2800 7050 1350
Wire Wire Line
	7050 1350 8800 1350
NoConn ~ 8800 2250
Wire Wire Line
	5400 3550 4300 3550
Wire Wire Line
	4300 3550 4300 3100
Wire Wire Line
	4300 3100 3250 3100
Wire Wire Line
	5400 3400 4400 3400
Wire Wire Line
	4400 3400 4400 3000
Wire Wire Line
	4400 3000 3250 3000
Wire Wire Line
	5400 3250 4500 3250
Wire Wire Line
	4500 3250 4500 2900
Wire Wire Line
	4500 2900 3250 2900
Wire Wire Line
	5400 3100 4600 3100
Wire Wire Line
	4600 3100 4600 2800
Wire Wire Line
	4600 2800 3250 2800
Wire Wire Line
	5400 2950 4700 2950
Wire Wire Line
	4700 2950 4700 2600
Wire Wire Line
	4700 2600 3250 2600
Wire Wire Line
	3400 2400 8800 2400
Wire Wire Line
	9500 3250 9500 3150
Wire Wire Line
	9500 3150 9200 3150
Wire Wire Line
	3250 3750 5150 3750
Wire Wire Line
	5150 3750 5150 2800
Wire Wire Line
	5150 2800 5400 2800
Wire Wire Line
	3250 3850 5300 3850
Wire Wire Line
	5300 3850 5300 2100
Wire Wire Line
	5300 2100 8800 2100
Wire Wire Line
	3250 2700 3400 2700
Wire Wire Line
	3400 2700 3400 2400
Wire Wire Line
	1850 3050 1650 3050
Wire Wire Line
	1650 3050 1650 2450
Wire Wire Line
	1850 3150 1500 3150
Wire Wire Line
	1500 3150 1500 2450
Wire Wire Line
	1850 3250 1350 3250
Wire Wire Line
	1350 3250 1350 2450
Wire Wire Line
	1850 3350 1200 3350
Wire Wire Line
	1200 3350 1200 2450
Wire Wire Line
	10850 3700 10850 650 
Wire Wire Line
	2700 650  2700 2100
Wire Wire Line
	10850 650  9500 650 
Wire Wire Line
	9500 650  9200 650 
Wire Wire Line
	9200 650  6000 650 
Wire Wire Line
	6000 650  3800 650 
Wire Wire Line
	3800 650  3450 650 
Wire Wire Line
	3450 650  2700 650 
Connection ~ 9200 650 
Connection ~ 9500 650 
Wire Wire Line
	3450 850  3450 650 
Connection ~ 3450 650 
Wire Wire Line
	3800 850  3800 650 
Connection ~ 3800 650 
Wire Wire Line
	6000 2450 6000 950 
Wire Wire Line
	6000 950  6000 650 
Connection ~ 6000 650 
$Comp
L CONN_01X03 P?
U 1 1 5734BB6C
P 950 3900
F 0 "P?" H 950 4100 50  0000 C CNN
F 1 "CONN_01X03" V 1050 3900 50  0000 C CNN
F 2 "" H 950 3900 50  0000 C CNN
F 3 "" H 950 3900 50  0000 C CNN
	1    950  3900
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P?
U 1 1 5734BD03
P 950 4600
F 0 "P?" H 950 4800 50  0000 C CNN
F 1 "CONN_01X03" V 1050 4600 50  0000 C CNN
F 2 "" H 950 4600 50  0000 C CNN
F 3 "" H 950 4600 50  0000 C CNN
	1    950  4600
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 3900 1500 3900
Wire Wire Line
	1500 3900 1500 3650
Wire Wire Line
	1500 3650 1850 3650
Wire Wire Line
	1150 4600 1600 4600
Wire Wire Line
	1600 4600 1600 3750
Wire Wire Line
	1600 3750 1850 3750
$Comp
L GND #PWR?
U 1 1 5734BFE1
P 1150 4700
F 0 "#PWR?" H 1150 4450 50  0001 C CNN
F 1 "GND" H 1150 4550 50  0000 C CNN
F 2 "" H 1150 4700 50  0000 C CNN
F 3 "" H 1150 4700 50  0000 C CNN
	1    1150 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5734C005
P 1150 4000
F 0 "#PWR?" H 1150 3750 50  0001 C CNN
F 1 "GND" H 1150 3850 50  0000 C CNN
F 2 "" H 1150 4000 50  0000 C CNN
F 3 "" H 1150 4000 50  0000 C CNN
	1    1150 4000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5734C1D9
P 1150 3800
F 0 "#PWR?" H 1150 3650 50  0001 C CNN
F 1 "+5V" H 1150 3940 50  0000 C CNN
F 2 "" H 1150 3800 50  0000 C CNN
F 3 "" H 1150 3800 50  0000 C CNN
	1    1150 3800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5734C1FD
P 1150 4500
F 0 "#PWR?" H 1150 4350 50  0001 C CNN
F 1 "+5V" H 1150 4640 50  0000 C CNN
F 2 "" H 1150 4500 50  0000 C CNN
F 3 "" H 1150 4500 50  0000 C CNN
	1    1150 4500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5734C221
P 2550 2100
F 0 "#PWR?" H 2550 1950 50  0001 C CNN
F 1 "+5V" H 2550 2240 50  0000 C CNN
F 2 "" H 2550 2100 50  0000 C CNN
F 3 "" H 2550 2100 50  0000 C CNN
	1    2550 2100
	1    0    0    -1  
$EndComp
NoConn ~ 2400 2100
NoConn ~ 3250 3950
NoConn ~ 3250 4050
$Comp
L CONN_01X02 P?
U 1 1 5734C2FB
P 950 700
F 0 "P?" H 950 850 50  0000 C CNN
F 1 "CONN_01X02" V 1050 700 50  0000 C CNN
F 2 "" H 950 700 50  0000 C CNN
F 3 "" H 950 700 50  0000 C CNN
	1    950  700 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5734C3B6
P 900 900
F 0 "#PWR?" H 900 650 50  0001 C CNN
F 1 "GND" H 900 750 50  0000 C CNN
F 2 "" H 900 900 50  0000 C CNN
F 3 "" H 900 900 50  0000 C CNN
	1    900  900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 900  1400 900 
$Comp
L +5V #PWR?
U 1 1 5734C451
P 1400 900
F 0 "#PWR?" H 1400 750 50  0001 C CNN
F 1 "+5V" H 1400 1040 50  0000 C CNN
F 2 "" H 1400 900 50  0000 C CNN
F 3 "" H 1400 900 50  0000 C CNN
	1    1400 900 
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5734C51F
P 5700 1100
F 0 "C?" H 5725 1200 50  0000 L CNN
F 1 "0.1uF" H 5725 1000 50  0000 L CNN
F 2 "" H 5738 950 50  0000 C CNN
F 3 "" H 5700 1100 50  0000 C CNN
	1    5700 1100
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 5734C846
P 5700 1250
F 0 "#PWR?" H 5700 1000 50  0001 C CNN
F 1 "GND" H 5700 1100 50  0000 C CNN
F 2 "" H 5700 1250 50  0000 C CNN
F 3 "" H 5700 1250 50  0000 C CNN
	1    5700 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 950  6000 950 
Connection ~ 6000 950 
NoConn ~ 1850 2850
NoConn ~ 1850 4550
$Comp
L shiftregister_74HC595 U?
U 1 1 5734D2CE
P 4050 6900
F 0 "U?" H 4200 7500 50  0000 C CNN
F 1 "shiftregister_74HC595" H 4050 6300 50  0000 C CNN
F 2 "" H 4050 6900 50  0000 C CNN
F 3 "" H 4050 6900 50  0000 C CNN
	1    4050 6900
	1    0    0    -1  
$EndComp
$Comp
L shiftregister_74HC595 U?
U 1 1 5734D34E
P 4050 5500
F 0 "U?" H 4200 6100 50  0000 C CNN
F 1 "shiftregister_74HC595" H 4050 4900 50  0000 C CNN
F 2 "" H 4050 5500 50  0000 C CNN
F 3 "" H 4050 5500 50  0000 C CNN
	1    4050 5500
	1    0    0    -1  
$EndComp
$EndSCHEMATC
