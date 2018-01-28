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
LIBS:Prototype-cache
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
L ATMEGA8A-PU U1
U 1 1 58C81940
P 4900 3050
F 0 "U1" H 4150 4350 50  0000 L BNN
F 1 "ATMEGA8A-PU" H 5400 1600 50  0000 L BNN
F 2 "DIL28" H 4900 3050 50  0001 C CIN
F 3 "" H 4900 3050 50  0001 C CNN
	1    4900 3050
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X03 J1
U 1 1 58C81989
P 1100 1300
F 0 "J1" H 1100 1500 50  0000 C CNN
F 1 "Sensor_CONN" V 1200 1300 50  0000 C CNN
F 2 "" H 1100 1300 50  0001 C CNN
F 3 "" H 1100 1300 50  0001 C CNN
	1    1100 1300
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 J2
U 1 1 58C819BC
P 7050 1300
F 0 "J2" H 7050 1500 50  0000 C CNN
F 1 "Bike_CONN" V 7150 1300 50  0000 C CNN
F 2 "" H 7050 1300 50  0001 C CNN
F 3 "" H 7050 1300 50  0001 C CNN
	1    7050 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR10
U 1 1 58C81BAC
P 6850 1500
F 0 "#PWR10" H 6850 1250 50  0001 C CNN
F 1 "GND" H 6850 1350 50  0000 C CNN
F 2 "" H 6850 1500 50  0001 C CNN
F 3 "" H 6850 1500 50  0001 C CNN
	1    6850 1500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR9
U 1 1 58C81BD0
P 6850 1100
F 0 "#PWR9" H 6850 950 50  0001 C CNN
F 1 "+5V" H 6850 1240 50  0000 C CNN
F 2 "" H 6850 1100 50  0001 C CNN
F 3 "" H 6850 1100 50  0001 C CNN
	1    6850 1100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR1
U 1 1 58C81BEA
P 1300 1100
F 0 "#PWR1" H 1300 950 50  0001 C CNN
F 1 "+5V" H 1300 1240 50  0000 C CNN
F 2 "" H 1300 1100 50  0001 C CNN
F 3 "" H 1300 1100 50  0001 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 58C81C04
P 1300 1500
F 0 "#PWR2" H 1300 1250 50  0001 C CNN
F 1 "GND" H 1300 1350 50  0000 C CNN
F 2 "" H 1300 1500 50  0001 C CNN
F 3 "" H 1300 1500 50  0001 C CNN
	1    1300 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1500 1300 1400
Wire Wire Line
	1300 1200 1300 1100
Wire Wire Line
	6850 1200 6850 1100
Wire Wire Line
	6850 1400 6850 1500
$Comp
L +5V #PWR6
U 1 1 58C81C38
P 4900 1400
F 0 "#PWR6" H 4900 1250 50  0001 C CNN
F 1 "+5V" H 4900 1540 50  0000 C CNN
F 2 "" H 4900 1400 50  0001 C CNN
F 3 "" H 4900 1400 50  0001 C CNN
	1    4900 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1400 4900 1650
$Comp
L GND #PWR7
U 1 1 58C81C61
P 4900 4650
F 0 "#PWR7" H 4900 4400 50  0001 C CNN
F 1 "GND" H 4900 4500 50  0000 C CNN
F 2 "" H 4900 4650 50  0001 C CNN
F 3 "" H 4900 4650 50  0001 C CNN
	1    4900 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 4650 4900 4550
$Comp
L +5V #PWR4
U 1 1 58C81CB5
P 3850 2150
F 0 "#PWR4" H 3850 2000 50  0001 C CNN
F 1 "+5V" H 3850 2290 50  0000 C CNN
F 2 "" H 3850 2150 50  0001 C CNN
F 3 "" H 3850 2150 50  0001 C CNN
	1    3850 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 2150 4000 2150
$Comp
L GND #PWR5
U 1 1 58C81D02
P 3850 2400
F 0 "#PWR5" H 3850 2150 50  0001 C CNN
F 1 "GND" H 3850 2250 50  0000 C CNN
F 2 "" H 3850 2400 50  0001 C CNN
F 3 "" H 3850 2400 50  0001 C CNN
	1    3850 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2400 3850 2350
Wire Wire Line
	3500 2350 4000 2350
$Comp
L C_Small C2
U 1 1 58C81D28
P 3500 2250
F 0 "C2" H 3510 2320 50  0000 L CNN
F 1 "C_Small" H 3510 2170 50  0000 L CNN
F 2 "" H 3500 2250 50  0001 C CNN
F 3 "" H 3500 2250 50  0001 C CNN
	1    3500 2250
	1    0    0    -1  
$EndComp
$Comp
L C_Small C3
U 1 1 58C81D69
P 5200 1450
F 0 "C3" H 5210 1520 50  0000 L CNN
F 1 "C_Small" H 5210 1370 50  0000 L CNN
F 2 "" H 5200 1450 50  0001 C CNN
F 3 "" H 5200 1450 50  0001 C CNN
	1    5200 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 1450 4900 1450
Connection ~ 4900 1450
Connection ~ 3850 2150
Connection ~ 3850 2350
$Comp
L GND #PWR8
U 1 1 58C81E2F
P 5400 1550
F 0 "#PWR8" H 5400 1300 50  0001 C CNN
F 1 "GND" H 5400 1400 50  0000 C CNN
F 2 "" H 5400 1550 50  0001 C CNN
F 3 "" H 5400 1550 50  0001 C CNN
	1    5400 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1550 5400 1450
Wire Wire Line
	5400 1450 5300 1450
$Comp
L CP1 C4
U 1 1 58C81F39
P 6200 1150
F 0 "C4" H 6225 1250 50  0000 L CNN
F 1 "CP1" H 6225 1050 50  0000 L CNN
F 2 "" H 6200 1150 50  0001 C CNN
F 3 "" H 6200 1150 50  0001 C CNN
	1    6200 1150
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 58C81FBA
P 1700 1200
F 0 "C1" H 1725 1300 50  0000 L CNN
F 1 "CP1" H 1725 1100 50  0000 L CNN
F 2 "" H 1700 1200 50  0001 C CNN
F 3 "" H 1700 1200 50  0001 C CNN
	1    1700 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1450 1700 1450
Wire Wire Line
	1700 1450 1700 1350
Connection ~ 1300 1450
Wire Wire Line
	1300 1150 1500 1150
Wire Wire Line
	1500 1150 1500 1050
Wire Wire Line
	1500 1050 1700 1050
Connection ~ 1300 1150
Wire Wire Line
	6850 1150 6600 1150
Wire Wire Line
	6600 1150 6600 1000
Wire Wire Line
	6600 1000 6200 1000
Connection ~ 6850 1150
Wire Wire Line
	6850 1450 6200 1450
Wire Wire Line
	6200 1450 6200 1300
Connection ~ 6850 1450
Wire Wire Line
	5900 3550 6150 3550
Wire Wire Line
	6150 3550 6150 5000
Wire Wire Line
	6150 5000 1500 5000
Wire Wire Line
	1500 5000 1500 1300
Wire Wire Line
	1500 1300 1300 1300
Wire Wire Line
	5900 2050 6650 2050
Wire Wire Line
	6650 2050 6650 1300
Wire Wire Line
	6650 1300 6850 1300
$Comp
L CONN_02X05 J3
U 1 1 58C823AD
P 7450 3050
F 0 "J3" H 7450 3350 50  0000 C CNN
F 1 "Prog_CONN" H 7450 2750 50  0000 C CNN
F 2 "" H 7450 1850 50  0001 C CNN
F 3 "" H 7450 1850 50  0001 C CNN
	1    7450 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 2800 7650 2250
Wire Wire Line
	7650 2250 5900 2250
$Comp
L R R1
U 1 1 58C82431
P 3800 1600
F 0 "R1" V 3880 1600 50  0000 C CNN
F 1 "R" V 3800 1600 50  0000 C CNN
F 2 "" V 3730 1600 50  0001 C CNN
F 3 "" H 3800 1600 50  0001 C CNN
	1    3800 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1950 3800 1950
Wire Wire Line
	3800 1950 3800 1750
$Comp
L +5V #PWR3
U 1 1 58C82490
P 3800 1350
F 0 "#PWR3" H 3800 1200 50  0001 C CNN
F 1 "+5V" H 3800 1490 50  0000 C CNN
F 2 "" H 3800 1350 50  0001 C CNN
F 3 "" H 3800 1350 50  0001 C CNN
	1    3800 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1450 3800 1350
Wire Wire Line
	7450 2800 7450 900 
Wire Wire Line
	7450 900  3950 900 
Wire Wire Line
	3950 900  3950 1950
Connection ~ 3950 1950
Wire Wire Line
	7350 2800 7350 2450
Wire Wire Line
	7350 2450 5900 2450
Wire Wire Line
	5900 2350 7250 2350
Wire Wire Line
	7250 2350 7250 2800
$Comp
L +5V #PWR12
U 1 1 58C825C2
P 7900 3400
F 0 "#PWR12" H 7900 3250 50  0001 C CNN
F 1 "+5V" H 7900 3540 50  0000 C CNN
F 2 "" H 7900 3400 50  0001 C CNN
F 3 "" H 7900 3400 50  0001 C CNN
	1    7900 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 58C825E8
P 7450 3500
F 0 "#PWR11" H 7450 3250 50  0001 C CNN
F 1 "GND" H 7450 3350 50  0000 C CNN
F 2 "" H 7450 3500 50  0001 C CNN
F 3 "" H 7450 3500 50  0001 C CNN
	1    7450 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3300 7250 3500
Wire Wire Line
	7250 3500 7550 3500
Wire Wire Line
	7350 3300 7350 3500
Connection ~ 7350 3500
Wire Wire Line
	7450 3500 7450 3300
Wire Wire Line
	7550 3500 7550 3300
Connection ~ 7450 3500
Wire Wire Line
	7900 3400 7650 3400
Wire Wire Line
	7650 3400 7650 3300
$EndSCHEMATC