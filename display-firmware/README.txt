
SEE motd.ino



Wiring between the Spark and 16x32 display is as follows:

16x32 Pin		Spark Pin
--------------------------
  GND				GND
  CLK 				D6
  OE  				D7
  LAT 				A3
  A   				A0
  B   				A1
  C   				A2
  R1				D0				
  G1				D1				
  B1				D2				
  R2				D3				
  G2				D4				
  B2				D5				

The display needs its own 5V supply.

Connect, compile, flash and run.  The demo is Plasma_16x32.