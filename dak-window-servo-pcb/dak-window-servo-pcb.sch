EESchema Schematic File Version 4
EELAYER 29 0
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
L 1-Parts:ESP32-DEVKITV1 U1
U 1 1 5DBE6D58
P 4200 2100
F 0 "U1" H 5225 2265 50  0000 C CNN
F 1 "ESP32-DEVKITV1" H 5225 2174 50  0000 C CNN
F 2 "1-MyFootprints:ESP32-DEVKITV1" H 3750 2200 50  0001 C CNN
F 3 "" H 3750 2200 50  0001 C CNN
	1    4200 2100
	1    0    0    -1  
$EndComp
$Comp
L 1-Parts:Motor_Servo M1
U 1 1 5DBE77E8
P 3500 4350
F 0 "M1" H 3494 4043 50  0000 C CNN
F 1 "Motor_Servo" H 3494 4134 50  0000 C CNN
F 2 "1-MyFootprints:Servo-Header" H 3500 4160 50  0001 C CNN
F 3 "http://forums.parallax.com/uploads/attachments/46831/74481.png" H 3500 4160 50  0001 C CNN
	1    3500 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 4250 4100 4250
Wire Wire Line
	4100 4250 4100 4200
Wire Wire Line
	4100 4350 3800 4350
Wire Wire Line
	3800 4450 3500 4450
Wire Wire Line
	3500 4450 3500 4050
Wire Wire Line
	3500 4050 4100 4050
$Comp
L Device:LED D1
U 1 1 5DBE9BE4
P 6750 4050
F 0 "D1" V 6789 3933 50  0000 R CNN
F 1 "LED" V 6698 3933 50  0000 R CNN
F 2 "LED_THT:LED_D3.0mm" H 6750 4050 50  0001 C CNN
F 3 "~" H 6750 4050 50  0001 C CNN
	1    6750 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6750 4200 6350 4200
NoConn ~ 4100 2250
NoConn ~ 4100 2400
NoConn ~ 4100 2550
NoConn ~ 4100 2700
NoConn ~ 4100 2850
NoConn ~ 4100 3000
NoConn ~ 4100 3150
NoConn ~ 4100 3300
NoConn ~ 4100 3450
NoConn ~ 4100 3600
NoConn ~ 4100 3750
NoConn ~ 4100 3900
NoConn ~ 6350 2250
NoConn ~ 6350 2400
NoConn ~ 6350 2550
NoConn ~ 6350 2700
NoConn ~ 6350 2850
NoConn ~ 6350 3000
NoConn ~ 6350 3150
NoConn ~ 6350 3300
NoConn ~ 6350 3450
NoConn ~ 6350 3600
NoConn ~ 6350 4350
NoConn ~ 6350 4050
Wire Wire Line
	6750 3900 6750 3750
Wire Wire Line
	6750 3750 6350 3750
NoConn ~ 6350 3900
$Comp
L Mechanical:MountingHole H?
U 1 1 5DBEECE4
P 3150 1850
F 0 "H?" H 3250 1896 50  0000 L CNN
F 1 "MountingHole" H 3250 1805 50  0000 L CNN
F 2 "" H 3150 1850 50  0001 C CNN
F 3 "~" H 3150 1850 50  0001 C CNN
	1    3150 1850
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 5DBEF41C
P 7450 5200
F 0 "H?" H 7550 5246 50  0000 L CNN
F 1 "MountingHole" H 7550 5155 50  0000 L CNN
F 2 "" H 7450 5200 50  0001 C CNN
F 3 "~" H 7450 5200 50  0001 C CNN
	1    7450 5200
	1    0    0    -1  
$EndComp
$EndSCHEMATC
