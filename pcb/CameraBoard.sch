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
LIBS:fifo_74hc40105
LIBS:notgate_74hc04
LIBS:power_connection
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
L arduino_mini U1
U 1 1 57336257
P 2550 3250
F 0 "U1" H 3050 2300 70  0000 C CNN
F 1 "arduino_mini" H 3300 2200 70  0000 C CNN
F 2 "arduino:arduino_mini" H 2550 3200 60  0001 C CNN
F 3 "" H 2550 3250 60  0000 C CNN
	1    2550 3250
	1    0    0    -1  
$EndComp
$Comp
L Camera_OV7670 OV76701
U 1 1 57336349
P 9350 1900
F 0 "OV76701" H 9950 900 60  0000 C CNN
F 1 "Camera_OV7670" H 10100 1050 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x09" H 9300 2950 60  0001 C CNN
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
Text GLabel 3650 3200 2    60   Input ~ 0
Arduino_P7
Text GLabel 3650 3350 2    60   Input ~ 0
Pixel_D6
Text GLabel 3650 3500 2    60   Input ~ 0
Pixel_D5
Text GLabel 3650 3650 2    60   Input ~ 0
Pixel_D4
$Comp
L R R1
U 1 1 57336A05
P 3450 1000
F 0 "R1" V 3530 1000 50  0000 C CNN
F 1 "10k" V 3450 1000 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3380 1000 50  0001 C CNN
F 3 "" H 3450 1000 50  0000 C CNN
	1    3450 1000
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 57336A6C
P 3800 1000
F 0 "R2" V 3880 1000 50  0000 C CNN
F 1 "10k" V 3800 1000 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3730 1000 50  0001 C CNN
F 3 "" H 3800 1000 50  0000 C CNN
	1    3800 1000
	1    0    0    -1  
$EndComp
$Comp
L LevelShifter_74HC4050D LS1
U 1 1 573372B0
P 7050 3100
F 0 "LS1" H 7250 3650 60  0000 C CNN
F 1 "LevelShifter_74HC4050D" H 7850 2400 60  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 7050 3100 60  0001 C CNN
F 3 "" H 7050 3100 60  0000 C CNN
	1    7050 3100
	1    0    0    -1  
$EndComp
$Comp
L TFT_1.8inch TFT1
U 1 1 57337659
P 10350 4150
F 0 "TFT1" H 10100 3550 60  0000 C CNN
F 1 "TFT_1.8inch" V 10800 4600 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04" H 10400 4650 60  0001 C CNN
F 3 "" H 10400 4650 60  0000 C CNN
	1    10350 4150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 57337E50
P 2550 4800
F 0 "#PWR01" H 2550 4550 50  0001 C CNN
F 1 "GND" H 2550 4650 50  0000 C CNN
F 2 "" H 2550 4800 50  0000 C CNN
F 3 "" H 2550 4800 50  0000 C CNN
	1    2550 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 57337E70
P 9500 3250
F 0 "#PWR02" H 9500 3000 50  0001 C CNN
F 1 "GND" H 9500 3100 50  0000 C CNN
F 2 "" H 9500 3250 50  0000 C CNN
F 3 "" H 9500 3250 50  0000 C CNN
	1    9500 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 57337E96
P 10500 4800
F 0 "#PWR03" H 10500 4550 50  0001 C CNN
F 1 "GND" H 10500 4650 50  0000 C CNN
F 2 "" H 10500 4800 50  0000 C CNN
F 3 "" H 10500 4800 50  0000 C CNN
	1    10500 4800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 57338279
P 6900 3900
F 0 "#PWR04" H 6900 3650 50  0001 C CNN
F 1 "GND" H 6900 3750 50  0000 C CNN
F 2 "" H 6900 3900 50  0000 C CNN
F 3 "" H 6900 3900 50  0000 C CNN
	1    6900 3900
	1    0    0    -1  
$EndComp
NoConn ~ 8800 2250
$Comp
L CONN_01X03 P2
U 1 1 5734BB6C
P 950 3900
F 0 "P2" H 950 4100 50  0000 C CNN
F 1 "CONN_01X03" V 1050 3900 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 950 3900 50  0001 C CNN
F 3 "" H 950 3900 50  0000 C CNN
	1    950  3900
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P3
U 1 1 5734BD03
P 950 4600
F 0 "P3" H 950 4800 50  0000 C CNN
F 1 "CONN_01X03" V 1050 4600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 950 4600 50  0001 C CNN
F 3 "" H 950 4600 50  0000 C CNN
	1    950  4600
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR05
U 1 1 5734BFE1
P 1150 4700
F 0 "#PWR05" H 1150 4450 50  0001 C CNN
F 1 "GND" H 1150 4550 50  0000 C CNN
F 2 "" H 1150 4700 50  0000 C CNN
F 3 "" H 1150 4700 50  0000 C CNN
	1    1150 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5734C005
P 1150 4000
F 0 "#PWR06" H 1150 3750 50  0001 C CNN
F 1 "GND" H 1150 3850 50  0000 C CNN
F 2 "" H 1150 4000 50  0000 C CNN
F 3 "" H 1150 4000 50  0000 C CNN
	1    1150 4000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 5734C1D9
P 1150 3800
F 0 "#PWR07" H 1150 3650 50  0001 C CNN
F 1 "+5V" H 1150 3940 50  0000 C CNN
F 2 "" H 1150 3800 50  0000 C CNN
F 3 "" H 1150 3800 50  0000 C CNN
	1    1150 3800
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR08
U 1 1 5734C1FD
P 1150 4500
F 0 "#PWR08" H 1150 4350 50  0001 C CNN
F 1 "+5V" H 1150 4640 50  0000 C CNN
F 2 "" H 1150 4500 50  0000 C CNN
F 3 "" H 1150 4500 50  0000 C CNN
	1    1150 4500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR09
U 1 1 5734C221
P 2550 2100
F 0 "#PWR09" H 2550 1950 50  0001 C CNN
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
L GND #PWR010
U 1 1 5734C3B6
P 1900 950
F 0 "#PWR010" H 1900 700 50  0001 C CNN
F 1 "GND" H 1900 800 50  0000 C CNN
F 2 "" H 1900 950 50  0000 C CNN
F 3 "" H 1900 950 50  0000 C CNN
	1    1900 950 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR011
U 1 1 5734C451
P 850 950
F 0 "#PWR011" H 850 800 50  0001 C CNN
F 1 "+5V" H 850 1090 50  0000 C CNN
F 2 "" H 850 950 50  0000 C CNN
F 3 "" H 850 950 50  0000 C CNN
	1    850  950 
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 5734C51F
P 6800 1100
F 0 "C1" H 6825 1200 50  0000 L CNN
F 1 "0.1uF" H 6825 1000 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 6838 950 50  0001 C CNN
F 3 "" H 6800 1100 50  0000 C CNN
	1    6800 1100
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR012
U 1 1 5734C846
P 6800 1250
F 0 "#PWR012" H 6800 1000 50  0001 C CNN
F 1 "GND" H 6800 1100 50  0000 C CNN
F 2 "" H 6800 1250 50  0000 C CNN
F 3 "" H 6800 1250 50  0000 C CNN
	1    6800 1250
	1    0    0    -1  
$EndComp
NoConn ~ 1850 2850
NoConn ~ 1850 4550
$Comp
L shiftregister_74HC165 SH1
U 1 1 5738668D
P 7350 5450
F 0 "SH1" H 7050 6050 50  0000 C CNN
F 1 "shiftregister_74HC165" H 7650 4850 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 7350 5450 50  0001 C CNN
F 3 "" H 7350 5450 50  0000 C CNN
	1    7350 5450
	1    0    0    -1  
$EndComp
$Comp
L fifo_74HC40105 FIFO1
U 1 1 57386CF5
P 5150 5050
F 0 "FIFO1" H 4850 5650 50  0000 C CNN
F 1 "fifo_74HC40105" H 5450 4450 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 5150 5050 50  0001 C CNN
F 3 "" H 5150 5050 50  0000 C CNN
	1    5150 5050
	1    0    0    -1  
$EndComp
$Comp
L fifo_74HC40105 FIFO2
U 1 1 57386D44
P 5150 6800
F 0 "FIFO2" H 4850 7400 50  0000 C CNN
F 1 "fifo_74HC40105" H 5450 6200 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 5150 6800 50  0001 C CNN
F 3 "" H 5150 6800 50  0000 C CNN
	1    5150 6800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 57387C85
P 5050 7550
F 0 "#PWR013" H 5050 7300 50  0001 C CNN
F 1 "GND" H 5050 7400 50  0000 C CNN
F 2 "" H 5050 7550 50  0000 C CNN
F 3 "" H 5050 7550 50  0000 C CNN
	1    5050 7550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR014
U 1 1 57387CB5
P 5050 5800
F 0 "#PWR014" H 5050 5550 50  0001 C CNN
F 1 "GND" H 5050 5650 50  0000 C CNN
F 2 "" H 5050 5800 50  0000 C CNN
F 3 "" H 5050 5800 50  0000 C CNN
	1    5050 5800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 57387CE5
P 7200 6200
F 0 "#PWR015" H 7200 5950 50  0001 C CNN
F 1 "GND" H 7200 6050 50  0000 C CNN
F 2 "" H 7200 6200 50  0000 C CNN
F 3 "" H 7200 6200 50  0000 C CNN
	1    7200 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR016
U 1 1 57387D15
P 1650 7100
F 0 "#PWR016" H 1650 6850 50  0001 C CNN
F 1 "GND" H 1650 6950 50  0000 C CNN
F 2 "" H 1650 7100 50  0000 C CNN
F 3 "" H 1650 7100 50  0000 C CNN
	1    1650 7100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR017
U 1 1 573888AC
P 5250 6050
F 0 "#PWR017" H 5250 5900 50  0001 C CNN
F 1 "+5V" H 5250 6190 50  0000 C CNN
F 2 "" H 5250 6050 50  0000 C CNN
F 3 "" H 5250 6050 50  0000 C CNN
	1    5250 6050
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR018
U 1 1 573888DC
P 7600 4700
F 0 "#PWR018" H 7600 4550 50  0001 C CNN
F 1 "+5V" H 7600 4840 50  0000 C CNN
F 2 "" H 7600 4700 50  0000 C CNN
F 3 "" H 7600 4700 50  0000 C CNN
	1    7600 4700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR019
U 1 1 5738890C
P 5250 4300
F 0 "#PWR019" H 5250 4150 50  0001 C CNN
F 1 "+5V" H 5250 4440 50  0000 C CNN
F 2 "" H 5250 4300 50  0000 C CNN
F 3 "" H 5250 4300 50  0000 C CNN
	1    5250 4300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR020
U 1 1 5738893C
P 1900 5150
F 0 "#PWR020" H 1900 5000 50  0001 C CNN
F 1 "+5V" H 1900 5290 50  0000 C CNN
F 2 "" H 1900 5150 50  0000 C CNN
F 3 "" H 1900 5150 50  0000 C CNN
	1    1900 5150
	1    0    0    -1  
$EndComp
$Comp
L shiftregister_74HC595 SH2
U 1 1 573892A7
P 1900 6350
F 0 "SH2" H 2050 6950 50  0000 C CNN
F 1 "shiftregister_74HC595" H 2150 5750 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 1900 6350 50  0001 C CNN
F 3 "" H 1900 6350 50  0000 C CNN
	1    1900 6350
	1    0    0    -1  
$EndComp
Text GLabel 4900 2750 2    60   Input ~ 0
Arduino_SPI_Clock
Text GLabel 4900 2950 2    60   Input ~ 0
Arduinio_SPI_Data
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
	950  1650 8800 1650
Wire Wire Line
	950  1650 950  3450
Wire Wire Line
	950  3450 1850 3450
Wire Wire Line
	800  1500 8800 1500
Wire Wire Line
	800  1500 800  3550
Wire Wire Line
	800  3550 1850 3550
Wire Wire Line
	3450 1150 3450 1500
Connection ~ 3450 1500
Wire Wire Line
	3800 1150 3800 1650
Connection ~ 3800 1650
Wire Wire Line
	10400 3250 10850 3250
Wire Wire Line
	7600 3550 8300 3550
Wire Wire Line
	7600 3400 8400 3400
Wire Wire Line
	7600 3250 8500 3250
Wire Wire Line
	7600 3100 8600 3100
Wire Wire Line
	7600 2950 8700 2950
Wire Wire Line
	7600 2800 8700 2800
Wire Wire Line
	8700 2800 8700 1350
Wire Wire Line
	8700 1350 8800 1350
Wire Wire Line
	6450 3550 4400 3550
Wire Wire Line
	4400 3550 4400 3100
Wire Wire Line
	4400 3100 3250 3100
Wire Wire Line
	6450 3400 4500 3400
Wire Wire Line
	4500 3400 4500 3000
Wire Wire Line
	4500 3000 3250 3000
Wire Wire Line
	6450 3250 4600 3250
Wire Wire Line
	4600 3250 4600 2900
Wire Wire Line
	4600 2900 3250 2900
Wire Wire Line
	4700 3100 6450 3100
Wire Wire Line
	4700 2800 4700 3100
Wire Wire Line
	4700 2800 3250 2800
Wire Wire Line
	6450 2950 5950 2950
Wire Wire Line
	5950 2950 5950 2600
Wire Wire Line
	3400 2400 8800 2400
Wire Wire Line
	9500 3250 9500 3150
Wire Wire Line
	9500 3150 9200 3150
Wire Wire Line
	3250 3750 6200 3750
Wire Wire Line
	6200 3750 6200 2800
Wire Wire Line
	6200 2800 6450 2800
Wire Wire Line
	3250 3850 6350 3850
Wire Wire Line
	6350 3850 6350 2100
Wire Wire Line
	6350 2100 8800 2100
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
	10850 3250 10850 650 
Wire Wire Line
	2700 650  2700 2100
Wire Wire Line
	10850 650  2700 650 
Connection ~ 9200 650 
Connection ~ 9500 650 
Wire Wire Line
	3450 850  3450 650 
Connection ~ 3450 650 
Wire Wire Line
	3800 850  3800 650 
Connection ~ 3800 650 
Wire Wire Line
	7050 650  7050 2450
Connection ~ 7050 650 
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
Wire Wire Line
	6800 950  7050 950 
Connection ~ 7050 950 
Wire Wire Line
	8700 2950 8700 3850
Wire Wire Line
	8700 3850 9800 3850
Wire Wire Line
	8600 3100 8600 4000
Wire Wire Line
	8600 4000 9800 4000
Wire Wire Line
	8500 3250 8500 4150
Wire Wire Line
	8500 4150 9800 4150
Wire Wire Line
	8400 3400 8400 4300
Wire Wire Line
	8400 4300 9800 4300
Wire Wire Line
	8300 3550 8300 4450
Wire Wire Line
	8300 4450 9800 4450
Connection ~ 10600 3250
Wire Wire Line
	2600 5900 2750 5900
Wire Wire Line
	2750 5900 2750 5200
Wire Wire Line
	2750 5200 4450 5200
Wire Wire Line
	2600 6000 2850 6000
Wire Wire Line
	2850 6000 2850 5300
Wire Wire Line
	2850 5300 4450 5300
Wire Wire Line
	2600 6100 2950 6100
Wire Wire Line
	2950 6100 2950 5400
Wire Wire Line
	2950 5400 4450 5400
Wire Wire Line
	2600 6200 3050 6200
Wire Wire Line
	3050 6200 3050 5500
Wire Wire Line
	3050 5500 4450 5500
Wire Wire Line
	2600 6300 3050 6300
Wire Wire Line
	3050 6300 3050 6950
Wire Wire Line
	3050 6950 4450 6950
Wire Wire Line
	2600 6400 2950 6400
Wire Wire Line
	2950 6400 2950 7050
Wire Wire Line
	2950 7050 4450 7050
Wire Wire Line
	2600 6500 2850 6500
Wire Wire Line
	2850 6500 2850 7150
Wire Wire Line
	2850 7150 4450 7150
Wire Wire Line
	2600 6600 2750 6600
Wire Wire Line
	2750 6600 2750 7250
Wire Wire Line
	2750 7250 4450 7250
Wire Wire Line
	5850 5200 6650 5200
Wire Wire Line
	5850 5300 6650 5300
Wire Wire Line
	5850 5400 6650 5400
Wire Wire Line
	5850 5500 6650 5500
Wire Wire Line
	5850 7250 6500 7250
Wire Wire Line
	6500 7250 6500 5900
Wire Wire Line
	6500 5900 6650 5900
Wire Wire Line
	5850 7150 6400 7150
Wire Wire Line
	6400 7150 6400 5800
Wire Wire Line
	6400 5800 6650 5800
Wire Wire Line
	5850 7050 6300 7050
Wire Wire Line
	6300 7050 6300 5700
Wire Wire Line
	6300 5700 6650 5700
Wire Wire Line
	5850 6950 6200 6950
Wire Wire Line
	6200 6950 6200 5600
Wire Wire Line
	6200 5600 6650 5600
Wire Wire Line
	5950 2600 3250 2600
Wire Wire Line
	4900 2950 4700 2950
Connection ~ 4700 2950
Wire Wire Line
	4900 2750 4850 2750
Wire Wire Line
	4850 2750 4850 2600
Connection ~ 4850 2600
Text GLabel 1000 5850 1    60   Input ~ 0
Arduino_SPI_Clock
Text GLabel 1150 5850 1    60   Input ~ 0
Arduinio_SPI_Data
Wire Wire Line
	1200 5900 1150 5900
Wire Wire Line
	1150 5900 1150 5850
Wire Wire Line
	1200 6100 1000 6100
Wire Wire Line
	1000 6100 1000 5850
$Comp
L +5V #PWR021
U 1 1 5738BE43
P 850 5850
F 0 "#PWR021" H 850 5700 50  0001 C CNN
F 1 "+5V" H 850 5990 50  0000 C CNN
F 2 "" H 850 5850 50  0000 C CNN
F 3 "" H 850 5850 50  0000 C CNN
	1    850  5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  5850 850  6200
Wire Wire Line
	850  6200 1200 6200
$Comp
L GND #PWR022
U 1 1 5738BF34
P 850 6600
F 0 "#PWR022" H 850 6350 50  0001 C CNN
F 1 "GND" H 850 6450 50  0000 C CNN
F 2 "" H 850 6600 50  0000 C CNN
F 3 "" H 850 6600 50  0000 C CNN
	1    850  6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  6600 850  6500
Wire Wire Line
	850  6500 1200 6500
NoConn ~ 2600 6800
$Comp
L notgate_74HCT04 U2
U 2 1 5738C8A7
P 3700 5850
F 0 "U2" H 3850 5950 50  0000 C CNN
F 1 "notgate_74HCT04" H 4100 5750 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 3700 5850 50  0001 C CNN
F 3 "" H 3700 5850 50  0000 C CNN
	2    3700 5850
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR023
U 1 1 5738C9D7
P 3650 5750
F 0 "#PWR023" H 3650 5600 50  0001 C CNN
F 1 "+5V" H 3650 5890 50  0000 C CNN
F 2 "" H 3650 5750 50  0000 C CNN
F 3 "" H 3650 5750 50  0000 C CNN
	1    3650 5750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR024
U 1 1 5738CA09
P 3650 5950
F 0 "#PWR024" H 3650 5700 50  0001 C CNN
F 1 "GND" H 3650 5800 50  0000 C CNN
F 2 "" H 3650 5950 50  0000 C CNN
F 3 "" H 3650 5950 50  0000 C CNN
	1    3650 5950
	1    0    0    -1  
$EndComp
NoConn ~ 9900 2400
Text GLabel 3200 6100 3    60   Input ~ 0
Arduino_P7
Wire Wire Line
	3200 6100 3200 5850
Wire Wire Line
	3200 5850 3250 5850
Wire Wire Line
	4150 5050 4150 6800
Wire Wire Line
	4150 5050 4450 5050
Wire Wire Line
	4150 6800 4450 6800
Connection ~ 4150 5850
Text GLabel 700  5850 1    60   Input ~ 0
Arduino_P7
Wire Wire Line
	700  5850 700  6400
Wire Wire Line
	700  6400 1200 6400
$Comp
L GND #PWR025
U 1 1 5738DA94
P 4450 4600
F 0 "#PWR025" H 4450 4350 50  0001 C CNN
F 1 "GND" H 4450 4450 50  0000 C CNN
F 2 "" H 4450 4600 50  0000 C CNN
F 3 "" H 4450 4600 50  0000 C CNN
	1    4450 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 5738DAC6
P 4450 6350
F 0 "#PWR026" H 4450 6100 50  0001 C CNN
F 1 "GND" H 4450 6200 50  0000 C CNN
F 2 "" H 4450 6350 50  0000 C CNN
F 3 "" H 4450 6350 50  0000 C CNN
	1    4450 6350
	1    0    0    -1  
$EndComp
NoConn ~ 4450 4950
NoConn ~ 4450 6700
$Comp
L GND #PWR027
U 1 1 5738DBB4
P 5850 4600
F 0 "#PWR027" H 5850 4350 50  0001 C CNN
F 1 "GND" H 5850 4450 50  0000 C CNN
F 2 "" H 5850 4600 50  0000 C CNN
F 3 "" H 5850 4600 50  0000 C CNN
	1    5850 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 5738DBE6
P 5850 6350
F 0 "#PWR028" H 5850 6100 50  0001 C CNN
F 1 "GND" H 5850 6200 50  0000 C CNN
F 2 "" H 5850 6350 50  0000 C CNN
F 3 "" H 5850 6350 50  0000 C CNN
	1    5850 6350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5738E659
P 6400 5000
F 0 "#PWR029" H 6400 4750 50  0001 C CNN
F 1 "GND" H 6400 4850 50  0000 C CNN
F 2 "" H 6400 5000 50  0000 C CNN
F 3 "" H 6400 5000 50  0000 C CNN
	1    6400 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 5000 6400 5000
Wire Wire Line
	5850 4950 6100 4950
Wire Wire Line
	6100 4950 6100 4200
Wire Wire Line
	6100 4200 8200 4200
$Comp
L notgate_74HCT04 U2
U 1 1 5738EBCE
P 6700 4500
F 0 "U2" H 6850 4600 50  0000 C CNN
F 1 "notgate_74HCT04" H 6900 4300 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 6700 4500 50  0001 C CNN
F 3 "" H 6700 4500 50  0000 C CNN
	1    6700 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	6250 5050 6250 4500
Wire Wire Line
	5850 5050 6250 5050
Wire Wire Line
	7150 4500 7150 4750
Wire Wire Line
	7150 4750 6650 4750
Wire Wire Line
	6650 4750 6650 5100
Wire Wire Line
	7150 4500 8100 4500
Wire Wire Line
	8050 5450 9450 5450
NoConn ~ 8050 5900
Wire Wire Line
	5850 6800 6100 6800
Wire Wire Line
	6100 6800 6100 5050
Connection ~ 6100 5050
NoConn ~ 5850 6700
Wire Wire Line
	8050 5550 9450 5550
Wire Wire Line
	8050 5800 8100 5800
Wire Wire Line
	8100 5800 8100 5650
Wire Wire Line
	8100 5650 9450 5650
Wire Wire Line
	8100 4500 8100 5350
Wire Wire Line
	8100 5350 9450 5350
Wire Wire Line
	8200 4200 8200 5250
Wire Wire Line
	8200 5250 9450 5250
$Comp
L C C2
U 1 1 573903B5
P 2250 5350
F 0 "C2" H 2275 5450 50  0000 L CNN
F 1 "1uF" H 2275 5250 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 2288 5200 50  0001 C CNN
F 3 "" H 2250 5350 50  0000 C CNN
	1    2250 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 57390416
P 2250 5500
F 0 "#PWR030" H 2250 5250 50  0001 C CNN
F 1 "GND" H 2250 5350 50  0000 C CNN
F 2 "" H 2250 5500 50  0000 C CNN
F 3 "" H 2250 5500 50  0000 C CNN
	1    2250 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 5150 1900 5600
Wire Wire Line
	2250 5200 1900 5200
Connection ~ 1900 5200
$Comp
L CONN_01X08 P4
U 1 1 573882A7
P 9650 5600
F 0 "P4" H 9650 6050 50  0000 C CNN
F 1 "CONN_01X08" V 9750 5600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x04" H 9650 5600 50  0001 C CNN
F 3 "" H 9650 5600 50  0000 C CNN
	1    9650 5600
	1    0    0    -1  
$EndComp
NoConn ~ 9450 5750
NoConn ~ 9450 5850
NoConn ~ 1850 4450
$Comp
L power_connection PWR1
U 1 1 5738A1B5
P 1250 950
F 0 "PWR1" V 1500 700 60  0000 C CNN
F 1 "power_connection" V 1000 1000 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 1250 950 60  0001 C CNN
F 3 "" H 1250 950 60  0000 C CNN
	1    1250 950 
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5738DE02
P 9450 5950
F 0 "#PWR?" H 9450 5700 50  0001 C CNN
F 1 "GND" H 9450 5800 50  0000 C CNN
F 2 "" H 9450 5950 50  0000 C CNN
F 3 "" H 9450 5950 50  0000 C CNN
	1    9450 5950
	1    0    0    -1  
$EndComp
$EndSCHEMATC
