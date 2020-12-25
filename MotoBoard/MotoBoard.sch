EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "MotoBoard"
Date "2020-12-19"
Rev "0.1.1"
Comp "Polish Japanese Academy of Information Technology"
Comment1 "Board for Oculi Mobili project"
Comment2 "Author: Piotr 'Regule' Gnyś"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega2560-16AU U1
U 1 1 5FDE22F9
P 2200 3750
F 0 "U1" H 2550 900 50  0000 C CNN
F 1 "ATmega2560-16AU" H 1600 900 50  0000 C CNN
F 2 "Package_QFP:TQFP-100_14x14mm_P0.5mm" H 2200 3750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2549-8-bit-AVR-Microcontroller-ATmega640-1280-1281-2560-2561_datasheet.pdf" H 2200 3750 50  0001 C CNN
	1    2200 3750
	1    0    0    -1  
$EndComp
Text GLabel 1250 1150 0    50   Input ~ 0
RESET
$Comp
L Device:Crystal Y?
U 1 1 5FDEDB19
P 6000 2150
F 0 "Y?" H 6000 2418 50  0000 C CNN
F 1 "16k" H 6000 2327 50  0000 C CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 6000 2150 50  0001 C CNN
F 3 "~" H 6000 2150 50  0001 C CNN
	1    6000 2150
	1    0    0    -1  
$EndComp
Text GLabel 1250 1350 0    50   Input ~ 0
CRYSTAL_1
Text GLabel 1250 1550 0    50   Input ~ 0
CRYSTAL_2
Wire Wire Line
	1250 1350 1400 1350
Wire Wire Line
	1250 1550 1400 1550
$Comp
L Device:C C?
U 1 1 5FDFF243
P 5700 2400
F 0 "C?" H 5815 2446 50  0000 L CNN
F 1 "22p" H 5815 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5738 2250 50  0001 C CNN
F 3 "~" H 5700 2400 50  0001 C CNN
	1    5700 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FDFF9D2
P 6350 2400
F 0 "C?" H 6465 2446 50  0000 L CNN
F 1 "22p" H 6465 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6388 2250 50  0001 C CNN
F 3 "~" H 6350 2400 50  0001 C CNN
	1    6350 2400
	1    0    0    -1  
$EndComp
Text GLabel 5500 1700 0    50   Input ~ 0
CRYSTAL_1
Text GLabel 5500 1900 0    50   Input ~ 0
CRYSTAL_2
Wire Wire Line
	5500 1900 5700 1900
Wire Wire Line
	5700 1900 5700 2150
Wire Wire Line
	5500 1700 6350 1700
Wire Wire Line
	6350 1700 6350 2150
Wire Wire Line
	5850 2150 5700 2150
Connection ~ 5700 2150
Wire Wire Line
	5700 2150 5700 2250
Wire Wire Line
	6150 2150 6350 2150
Connection ~ 6350 2150
Wire Wire Line
	6350 2150 6350 2250
$Comp
L power:GND #PWR?
U 1 1 5FE0211D
P 6000 2750
F 0 "#PWR?" H 6000 2500 50  0001 C CNN
F 1 "GND" H 6005 2577 50  0000 C CNN
F 2 "" H 6000 2750 50  0001 C CNN
F 3 "" H 6000 2750 50  0001 C CNN
	1    6000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2550 5700 2650
Wire Wire Line
	5700 2650 6000 2650
Wire Wire Line
	6000 2650 6000 2750
Wire Wire Line
	6350 2550 6350 2650
Wire Wire Line
	6350 2650 6000 2650
Connection ~ 6000 2650
$Comp
L Device:R R?
U 1 1 5FE032D4
P 6000 3150
F 0 "R?" V 5900 3150 50  0000 C CNN
F 1 "1M" V 6100 3150 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 5930 3150 50  0001 C CNN
F 3 "~" H 6000 3150 50  0001 C CNN
	1    6000 3150
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 3150 5700 3150
Wire Wire Line
	5700 3150 5700 2650
Connection ~ 5700 2650
Wire Wire Line
	6350 2650 6350 3150
Wire Wire Line
	6350 3150 6150 3150
Connection ~ 6350 2650
Text GLabel 1250 1750 0    50   Input ~ 0
A_REF
Wire Wire Line
	1250 1750 1400 1750
Text GLabel 6050 1350 0    50   Input ~ 0
A_REF
$Comp
L Device:C C?
U 1 1 5FE0BC14
P 6400 1350
F 0 "C?" V 6148 1350 50  0000 C CNN
F 1 "100n" V 6239 1350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6438 1200 50  0001 C CNN
F 3 "~" H 6400 1350 50  0001 C CNN
	1    6400 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 1350 6050 1350
$Comp
L power:GND #PWR?
U 1 1 5FE0D68A
P 6700 1450
F 0 "#PWR?" H 6700 1200 50  0001 C CNN
F 1 "GND" H 6705 1277 50  0000 C CNN
F 2 "" H 6700 1450 50  0001 C CNN
F 3 "" H 6700 1450 50  0001 C CNN
	1    6700 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1450 6700 1350
Wire Wire Line
	6700 1350 6550 1350
$Comp
L power:+5V #PWR?
U 1 1 5FE1002C
P 1900 700
F 0 "#PWR?" H 1900 550 50  0001 C CNN
F 1 "+5V" V 1915 828 50  0000 L CNN
F 2 "" H 1900 700 50  0001 C CNN
F 3 "" H 1900 700 50  0001 C CNN
	1    1900 700 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1900 700  2200 700 
Wire Wire Line
	2300 700  2300 850 
Wire Wire Line
	2200 850  2200 700 
Connection ~ 2200 700 
Wire Wire Line
	2200 700  2300 700 
$Comp
L power:GND #PWR?
U 1 1 5FE133E9
P 2200 6850
F 0 "#PWR?" H 2200 6600 50  0001 C CNN
F 1 "GND" H 2205 6677 50  0000 C CNN
F 2 "" H 2200 6850 50  0001 C CNN
F 3 "" H 2200 6850 50  0001 C CNN
	1    2200 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 6850 2200 6650
$Comp
L power:+5V #PWR?
U 1 1 5FE17BAB
P 4800 2300
F 0 "#PWR?" H 4800 2150 50  0001 C CNN
F 1 "+5V" H 4815 2473 50  0000 C CNN
F 2 "" H 4800 2300 50  0001 C CNN
F 3 "" H 4800 2300 50  0001 C CNN
	1    4800 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FE18665
P 5200 2650
F 0 "C?" H 5085 2604 50  0000 R CNN
F 1 "100n" H 5085 2695 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5238 2500 50  0001 C CNN
F 3 "~" H 5200 2650 50  0001 C CNN
	1    5200 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5FE1A955
P 4800 2650
F 0 "C?" H 4685 2604 50  0000 R CNN
F 1 "100n" H 4685 2695 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4838 2500 50  0001 C CNN
F 3 "~" H 4800 2650 50  0001 C CNN
	1    4800 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 5FE1AEA0
P 4400 2650
F 0 "C?" H 4285 2604 50  0000 R CNN
F 1 "100n" H 4285 2695 50  0000 R CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4438 2500 50  0001 C CNN
F 3 "~" H 4400 2650 50  0001 C CNN
	1    4400 2650
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FE233E5
P 4800 3050
F 0 "#PWR?" H 4800 2800 50  0001 C CNN
F 1 "GND" H 4805 2877 50  0000 C CNN
F 2 "" H 4800 3050 50  0001 C CNN
F 3 "" H 4800 3050 50  0001 C CNN
	1    4800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2300 4800 2400
Wire Wire Line
	4800 2400 4400 2400
Wire Wire Line
	4400 2400 4400 2500
Wire Wire Line
	4800 2500 4800 2400
Connection ~ 4800 2400
Wire Wire Line
	4800 2400 5200 2400
Wire Wire Line
	5200 2400 5200 2500
Wire Wire Line
	5200 2800 5200 2950
Wire Wire Line
	5200 2950 4800 2950
Wire Wire Line
	4800 2950 4800 3050
Wire Wire Line
	4800 2800 4800 2950
Connection ~ 4800 2950
Wire Wire Line
	4800 2950 4400 2950
Wire Wire Line
	4400 2950 4400 2800
$Comp
L power:+5V #PWR?
U 1 1 5FE28950
P 4450 3600
F 0 "#PWR?" H 4450 3450 50  0001 C CNN
F 1 "+5V" V 4465 3728 50  0000 L CNN
F 2 "" H 4450 3600 50  0001 C CNN
F 3 "" H 4450 3600 50  0001 C CNN
	1    4450 3600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FE294EF
P 4850 3600
F 0 "R?" V 4643 3600 50  0000 C CNN
F 1 "10K" V 4734 3600 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4780 3600 50  0001 C CNN
F 3 "~" H 4850 3600 50  0001 C CNN
	1    4850 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 3600 4550 3600
$Comp
L Device:D D?
U 1 1 5FE2AADB
P 4850 3900
F 0 "D?" H 4850 4024 50  0000 C CNN
F 1 "D" H 4850 4025 50  0001 C CNN
F 2 "Diode_SMD:D_0805_2012Metric" H 4850 3900 50  0001 C CNN
F 3 "~" H 4850 3900 50  0001 C CNN
	1    4850 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3900 4550 3900
Wire Wire Line
	4550 3900 4550 3600
Connection ~ 4550 3600
Wire Wire Line
	4550 3600 4450 3600
Wire Wire Line
	1250 1150 1400 1150
Text GLabel 6050 3600 2    50   Input ~ 0
RESET
Wire Wire Line
	5000 3600 5150 3600
Wire Wire Line
	5000 3900 5150 3900
Wire Wire Line
	5150 3900 5150 3600
Connection ~ 5150 3600
Wire Wire Line
	5150 3600 5450 3600
$Comp
L Device:C C?
U 1 1 5FE37612
P 5450 4050
F 0 "C?" H 5565 4096 50  0000 L CNN
F 1 "22p" H 5565 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5488 3900 50  0001 C CNN
F 3 "~" H 5450 4050 50  0001 C CNN
	1    5450 4050
	1    0    0    -1  
$EndComp
Connection ~ 5450 3600
Wire Wire Line
	5450 3600 5900 3600
$Comp
L Switch:SW_DIP_x01 SW?
U 1 1 5FE41E97
P 5900 4050
F 0 "SW?" V 5854 4180 50  0000 L CNN
F 1 "RESET_BTN" V 5945 4180 50  0000 L CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 5900 4050 50  0001 C CNN
F 3 "~" H 5900 4050 50  0001 C CNN
	1    5900 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 3600 5450 3900
Wire Wire Line
	5900 3750 5900 3600
Connection ~ 5900 3600
Wire Wire Line
	5900 3600 6050 3600
$Comp
L power:GND #PWR?
U 1 1 5FE4795C
P 5650 4600
F 0 "#PWR?" H 5650 4350 50  0001 C CNN
F 1 "GND" H 5655 4427 50  0000 C CNN
F 2 "" H 5650 4600 50  0001 C CNN
F 3 "" H 5650 4600 50  0001 C CNN
	1    5650 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4600 5650 4500
Wire Wire Line
	5650 4500 5450 4500
Wire Wire Line
	5450 4500 5450 4200
Wire Wire Line
	5900 4350 5900 4500
Wire Wire Line
	5900 4500 5650 4500
Connection ~ 5650 4500
Wire Notes Line
	6850 900  4050 900 
Wire Notes Line
	4050 4850 6850 4850
Text Notes 4100 850  0    50   ~ 0
Must be placed as close to U1 as possible.
Wire Notes Line
	4050 750  6850 750 
Wire Notes Line
	6850 750  6850 4850
Wire Notes Line
	4050 750  4050 4850
Text GLabel 3250 5150 2    50   Input ~ 0
ENC_LEFT_IMP
Text GLabel 1300 6150 0    50   Input ~ 0
ENC_LEFT_DR
Wire Wire Line
	1300 6150 1400 6150
Wire Wire Line
	3250 5150 3000 5150
Text GLabel 3250 5250 2    50   Input ~ 0
ENC_RIGHT_IMP
Wire Wire Line
	3250 5250 3000 5250
Text GLabel 3250 5050 2    50   Input ~ 0
ENC_RIGHT_DIR
Wire Wire Line
	3250 5050 3000 5050
Text GLabel 1300 5050 0    50   Input ~ 0
MTR_LEFT_FWD
Text GLabel 1300 5150 0    50   Input ~ 0
MTR_LEFT_REV
Text GLabel 1300 5250 0    50   Input ~ 0
MTR_LEFT_PWM
Wire Wire Line
	1300 5050 1400 5050
Wire Wire Line
	1300 5150 1400 5150
Wire Wire Line
	1300 5250 1400 5250
Text GLabel 1300 5350 0    50   Input ~ 0
MTR_RIGHT_FWD
Wire Wire Line
	1300 5350 1400 5350
Text GLabel 3150 2450 2    50   Input ~ 0
MTR_RIGHT_REV
Wire Wire Line
	3150 2450 3000 2450
Text GLabel 3150 2550 2    50   Input ~ 0
MTR_RIGHT_PWM
Wire Wire Line
	3150 2550 3000 2550
Text GLabel 3150 2650 2    50   Input ~ 0
BMPR_LEFT
Text GLabel 1250 3950 0    50   Input ~ 0
BMPR_RIGHT
Text GLabel 3150 2750 2    50   Input ~ 0
BMPR_CENTER
Wire Wire Line
	3150 2750 3000 2750
Wire Wire Line
	3000 2650 3150 2650
Wire Wire Line
	1250 3950 1400 3950
Text GLabel 1250 3850 0    50   Input ~ 0
SONAR_LEFT_TRG
Wire Wire Line
	1250 3850 1400 3850
Text GLabel 3200 4150 2    50   Input ~ 0
SONAR_LEFT_ECHO
Text GLabel 1300 4850 0    50   Input ~ 0
SONAR_CNTR_TRG
Wire Wire Line
	1300 4850 1400 4850
Text GLabel 1300 4750 0    50   Input ~ 0
SONAR_RIGHT_TRG
Wire Wire Line
	1300 4750 1400 4750
Text GLabel 3200 4050 2    50   Input ~ 0
SONAR_CNTR_ECHO
Text GLabel 3200 3950 2    50   Input ~ 0
SONAR_RIGHT_ECHO
Wire Wire Line
	3000 3950 3200 3950
Wire Wire Line
	3000 4050 3200 4050
Wire Wire Line
	3000 4150 3200 4150
Text GLabel 3250 4750 2    50   Input ~ 0
RXD0
Wire Wire Line
	3250 4750 3000 4750
Text GLabel 3250 4850 2    50   Input ~ 0
TXD0
Wire Wire Line
	3250 4850 3000 4850
Text GLabel 3150 2350 2    50   Input ~ 0
MISO_MAIN
Wire Wire Line
	3150 2350 3000 2350
Text GLabel 3150 2250 2    50   Input ~ 0
MOSI_MAIN
Wire Wire Line
	3150 2250 3000 2250
Text GLabel 3150 2150 2    50   Input ~ 0
SCK_MAIN
Wire Wire Line
	3150 2150 3000 2150
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J?
U 1 1 5FE77BF2
P 4600 1300
F 0 "J?" H 4650 1617 50  0000 C CNN
F 1 "ISP" H 4650 1526 50  0000 C CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_2x03_P1.00mm_Vertical" H 4600 1300 50  0001 C CNN
F 3 "~" H 4600 1300 50  0001 C CNN
	1    4600 1300
	1    0    0    -1  
$EndComp
Text GLabel 4150 1550 3    50   Input ~ 0
MISO_MAIN
Text GLabel 4250 1550 3    50   Input ~ 0
SCK_MAIN
Text GLabel 4350 1550 3    50   Input ~ 0
RESET
Wire Wire Line
	4350 1550 4350 1400
Wire Wire Line
	4350 1400 4400 1400
Wire Wire Line
	4400 1300 4250 1300
Wire Wire Line
	4250 1300 4250 1550
Wire Wire Line
	4400 1200 4150 1200
Wire Wire Line
	4150 1200 4150 1550
$Comp
L power:+5V #PWR?
U 1 1 5FE8DFD2
P 5150 1150
F 0 "#PWR?" H 5150 1000 50  0001 C CNN
F 1 "+5V" H 5165 1323 50  0000 C CNN
F 2 "" H 5150 1150 50  0001 C CNN
F 3 "" H 5150 1150 50  0001 C CNN
	1    5150 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 1150 5150 1200
Wire Wire Line
	5150 1200 4900 1200
Text GLabel 5050 1300 2    50   Input ~ 0
MOSI_MAIN
Wire Wire Line
	5050 1300 4900 1300
$Comp
L power:GND #PWR?
U 1 1 5FE946B6
P 4950 1550
F 0 "#PWR?" H 4950 1300 50  0001 C CNN
F 1 "GND" H 4955 1377 50  0000 C CNN
F 2 "" H 4950 1550 50  0001 C CNN
F 3 "" H 4950 1550 50  0001 C CNN
	1    4950 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1550 4950 1400
Wire Wire Line
	4950 1400 4900 1400
NoConn ~ 1400 2050
NoConn ~ 1400 2150
NoConn ~ 1400 2250
NoConn ~ 1400 2350
NoConn ~ 1400 2450
NoConn ~ 1400 2550
NoConn ~ 1400 2650
NoConn ~ 1400 2750
NoConn ~ 1400 2950
NoConn ~ 1400 3050
NoConn ~ 1400 3150
NoConn ~ 1400 3250
NoConn ~ 1400 3350
NoConn ~ 1400 3450
NoConn ~ 1400 3550
NoConn ~ 1400 3650
NoConn ~ 1400 4050
NoConn ~ 1400 4150
NoConn ~ 1400 4250
NoConn ~ 1400 4350
NoConn ~ 1400 4450
NoConn ~ 1400 4550
NoConn ~ 1400 4950
NoConn ~ 1400 5450
NoConn ~ 1400 5650
NoConn ~ 1400 5750
NoConn ~ 1400 5850
NoConn ~ 1400 5950
NoConn ~ 1400 6050
NoConn ~ 3000 6350
NoConn ~ 3000 6250
NoConn ~ 3000 6150
NoConn ~ 3000 6050
NoConn ~ 3000 5950
NoConn ~ 3000 5850
NoConn ~ 3000 5750
NoConn ~ 3000 5650
NoConn ~ 3000 5450
NoConn ~ 3000 5350
NoConn ~ 3000 4950
NoConn ~ 3000 4550
NoConn ~ 3000 4450
NoConn ~ 3000 4350
NoConn ~ 3000 4250
NoConn ~ 3000 3850
NoConn ~ 3000 3650
NoConn ~ 3000 3550
NoConn ~ 3000 3450
NoConn ~ 3000 3350
NoConn ~ 3000 3250
NoConn ~ 3000 3150
NoConn ~ 3000 3050
NoConn ~ 3000 2950
NoConn ~ 3000 2050
NoConn ~ 3000 1850
NoConn ~ 3000 1750
NoConn ~ 3000 1650
NoConn ~ 3000 1550
NoConn ~ 3000 1450
NoConn ~ 3000 1350
NoConn ~ 3000 1250
NoConn ~ 3000 1150
$Comp
L MCU_Microchip_ATmega:ATmega16U2-AU U?
U 1 1 5FDFCC29
P 9200 2450
F 0 "U?" H 9200 961 50  0000 C CNN
F 1 "ATmega16U2-AU" H 9200 870 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 9200 2450 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc7799.pdf" H 9200 2450 50  0001 C CNN
	1    9200 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_B J?
U 1 1 5FE000CF
P 7350 1950
F 0 "J?" H 7407 2417 50  0000 C CNN
F 1 "USB_B" H 7407 2326 50  0000 C CNN
F 2 "" H 7500 1900 50  0001 C CNN
F 3 " ~" H 7500 1900 50  0001 C CNN
	1    7350 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5FE00E61
P 8100 1950
F 0 "R?" V 7893 1950 50  0000 C CNN
F 1 "22R" V 7984 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8030 1950 50  0001 C CNN
F 3 "~" H 8100 1950 50  0001 C CNN
	1    8100 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5FE016D7
P 8100 2050
F 0 "R?" V 8200 2050 50  0000 C CNN
F 1 "22R" V 8300 2050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 8030 2050 50  0001 C CNN
F 3 "~" H 8100 2050 50  0001 C CNN
	1    8100 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	8250 2050 8500 2050
Wire Wire Line
	8250 1950 8500 1950
Wire Wire Line
	7950 1950 7650 1950
Wire Wire Line
	7650 2050 7950 2050
$Comp
L power:GND #PWR?
U 1 1 5FE1B4B1
P 7650 2850
F 0 "#PWR?" H 7650 2600 50  0001 C CNN
F 1 "GND" H 7655 2677 50  0000 C CNN
F 2 "" H 7650 2850 50  0001 C CNN
F 3 "" H 7650 2850 50  0001 C CNN
	1    7650 2850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
