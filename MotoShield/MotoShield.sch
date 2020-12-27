EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "OculiShield"
Date "2020-12-27"
Rev "0.1.1"
Comp "Polish-Japanese Academy of Information Technology"
Comment1 "Author: Piotr 'Regule' Gnyś"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L arduino:Arduino_Mega2560_Shield XA?
U 1 1 5FE8B956
P 3300 3350
F 0 "XA?" H 3300 969 60  0000 C CNN
F 1 "Arduino_Mega2560_Shield" H 3300 863 60  0000 C CNN
F 2 "" H 4000 6100 60  0001 C CNN
F 3 "" H 4000 6100 60  0001 C CNN
	1    3300 3350
	1    0    0    -1  
$EndComp
Text GLabel 4850 1200 2    50   Input ~ 0
ENC_LEFT_IMPULSE
Text GLabel 4850 1300 2    50   Input ~ 0
ENC_RIGHT_IMPULSE
Wire Wire Line
	4850 1200 4600 1200
Wire Wire Line
	4600 1300 4850 1300
Text GLabel 4850 1400 2    50   Input ~ 0
ENC_LEFT_DIR
Text GLabel 4850 1500 2    50   Input ~ 0
ENC_RIGHT_DIR
Wire Wire Line
	4850 1400 4600 1400
Wire Wire Line
	4600 1500 4850 1500
Text GLabel 4850 1600 2    50   Input ~ 0
MOTOR_LEFT_FWD
Text GLabel 4850 2000 2    50   Input ~ 0
MOTOR_RIGHT_REV
Text GLabel 4850 2100 2    50   Input ~ 0
MOTOR_RIGHT_PWM
Text GLabel 4850 1700 2    50   Input ~ 0
MOTOR_LEFT_REV
Text GLabel 4850 1800 2    50   Input ~ 0
MOTOR_LEFT_PWM
Text GLabel 4850 1900 2    50   Input ~ 0
MOTOR_RIGHT_FWD
Wire Wire Line
	4850 1600 4600 1600
Wire Wire Line
	4850 1700 4600 1700
Wire Wire Line
	4600 1800 4850 1800
Wire Wire Line
	4850 1900 4600 1900
Wire Wire Line
	4600 2000 4850 2000
Wire Wire Line
	4850 2100 4600 2100
Text GLabel 4850 2200 2    50   Input ~ 0
BUMPER_LEFT
Text GLabel 4850 2300 2    50   Input ~ 0
BUMPER_CENTER
Text GLabel 1700 1900 0    50   Input ~ 0
BUMPER_RIGHT
Wire Wire Line
	4600 2200 4850 2200
Wire Wire Line
	4850 2300 4600 2300
Wire Wire Line
	1700 1900 2000 1900
Text GLabel 1700 1800 0    50   Input ~ 0
SONAR_LEFT_TRIG
Text GLabel 1700 1700 0    50   Input ~ 0
SONAR_CENTER_TRIG
Text GLabel 1700 1600 0    50   Input ~ 0
SONAR_RIGHT_TRIG
Wire Wire Line
	1700 1600 2000 1600
Wire Wire Line
	2000 1700 1700 1700
Wire Wire Line
	1700 1800 2000 1800
Text GLabel 1700 1500 0    50   Input ~ 0
SONAR_LEFT_ECHO
Text GLabel 1700 1400 0    50   Input ~ 0
SONAR_CENTER_ECHO
Text GLabel 1700 2000 0    50   Input ~ 0
SONAR_RIGHT_ECHO
Wire Wire Line
	1700 2000 2000 2000
Wire Wire Line
	2000 1500 1700 1500
Wire Wire Line
	1700 1400 2000 1400
$Comp
L power:GND #PWR?
U 1 1 5FEB2C4D
P 1050 5300
F 0 "#PWR?" H 1050 5050 50  0001 C CNN
F 1 "GND" H 1055 5127 50  0000 C CNN
F 2 "" H 1050 5300 50  0001 C CNN
F 3 "" H 1050 5300 50  0001 C CNN
	1    1050 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5000 1050 5000
Wire Wire Line
	1050 5000 1050 5300
Wire Wire Line
	2000 4900 1050 4900
Wire Wire Line
	1050 4900 1050 5000
Connection ~ 1050 5000
Wire Wire Line
	2000 4800 1050 4800
Wire Wire Line
	1050 4800 1050 4900
Connection ~ 1050 4900
Wire Wire Line
	2000 4700 1050 4700
Wire Wire Line
	1050 4700 1050 4800
Connection ~ 1050 4800
Wire Wire Line
	2000 4600 1050 4600
Wire Wire Line
	1050 4600 1050 4700
Connection ~ 1050 4700
$Comp
L power:+5V #PWR?
U 1 1 5FEB5474
P 1500 5350
F 0 "#PWR?" H 1500 5200 50  0001 C CNN
F 1 "+5V" V 1515 5478 50  0000 L CNN
F 2 "" H 1500 5350 50  0001 C CNN
F 3 "" H 1500 5350 50  0001 C CNN
	1    1500 5350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 5200 1650 5200
Wire Wire Line
	1650 5200 1650 5300
Wire Wire Line
	1650 5350 1500 5350
Wire Wire Line
	2000 5500 1650 5500
Wire Wire Line
	1650 5500 1650 5400
Connection ~ 1650 5350
Wire Wire Line
	2000 5400 1650 5400
Connection ~ 1650 5400
Wire Wire Line
	1650 5400 1650 5350
Wire Wire Line
	2000 5300 1650 5300
Connection ~ 1650 5300
Wire Wire Line
	1650 5300 1650 5350
Text GLabel 1700 4300 0    50   Input ~ 0
RESET
Wire Wire Line
	1700 4300 2000 4300
NoConn ~ 2000 1200
NoConn ~ 2000 1300
NoConn ~ 2000 2100
NoConn ~ 2000 2200
NoConn ~ 2000 2300
NoConn ~ 2000 2500
NoConn ~ 2000 2600
NoConn ~ 2000 2700
NoConn ~ 2000 2800
NoConn ~ 2000 2900
NoConn ~ 2000 3000
NoConn ~ 2000 3100
NoConn ~ 2000 3200
NoConn ~ 2000 3300
NoConn ~ 2000 3400
NoConn ~ 2000 3500
NoConn ~ 2000 3600
NoConn ~ 2000 3700
NoConn ~ 2000 3800
NoConn ~ 2000 3900
NoConn ~ 2000 4000
NoConn ~ 2000 4100
NoConn ~ 4600 2400
NoConn ~ 4600 2500
NoConn ~ 4600 2600
NoConn ~ 4600 2700
NoConn ~ 4600 2900
NoConn ~ 4600 2800
NoConn ~ 4600 3000
NoConn ~ 4600 3100
NoConn ~ 4600 3200
NoConn ~ 4600 3300
NoConn ~ 4600 3400
NoConn ~ 4600 3500
NoConn ~ 4600 3600
NoConn ~ 4600 3700
NoConn ~ 4600 3800
NoConn ~ 4600 3900
NoConn ~ 4600 4000
NoConn ~ 4600 4100
NoConn ~ 4600 4200
NoConn ~ 4600 4300
NoConn ~ 4600 4400
NoConn ~ 4600 4500
NoConn ~ 4600 4600
NoConn ~ 4600 4700
NoConn ~ 4600 4800
NoConn ~ 4600 4900
NoConn ~ 4600 5000
NoConn ~ 4600 5100
NoConn ~ 4600 5200
NoConn ~ 4600 5300
NoConn ~ 4600 5400
NoConn ~ 4600 5500
NoConn ~ 2000 5100
NoConn ~ 2000 4400
NoConn ~ 3050 750 
NoConn ~ 3150 750 
NoConn ~ 3250 750 
NoConn ~ 3550 750 
NoConn ~ 3450 750 
NoConn ~ 3350 750 
$EndSCHEMATC
