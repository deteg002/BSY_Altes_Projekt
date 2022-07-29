#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "project.h"


void Send16bits (unsigned short output)
{
	
  unsigned char i;

  for (i=16; i>0; i--) 
  {
    unsigned short mask = 1 << (i - 1); // berechne bitmaske
  
    digitalWrite(CLOCK, 0);  // setze clock auf 0
    
    // Sende Bit an den Datenpin
    
    if (output & mask)   
      digitalWrite(DATA, 1);          
		else                              
      digitalWrite(DATA, 0);  
        
    digitalWrite(CLOCK, 1);  // setze clock auf 1
  	 
  }

}

void MAX7219Send (unsigned char reg_number, unsigned char dataout)
{
  digitalWrite(LOAD, 1);  // setze LOAD auf 1 zum starten
  Send16bits((reg_number << 8) + dataout);   // sende 16 bits ( reg number + dataout )
  digitalWrite(LOAD, 0);  // LOAD 0 zum verriegeln
  digitalWrite(LOAD, 1);  // LOAD 1 zum schluss
} 

void SetupConfig ()
{
  if (wiringPiSetup () == -1) exit (1) ;

//Es werden 3 Ausgabepins benötigt um den Max7219 zu steuern: Data, Clock und Load

  pinMode(DATA, OUTPUT);  
  pinMode(CLOCK, OUTPUT);
  pinMode(LOAD, OUTPUT);  
	
  MAX7219Send(SCAN_LIMIT, 7);     // SCAN_LIMIT-Register so einstellen, dass die komplette Matrix ausgegeben werden kann

/* 

 BCD decode mode aus : Datenbits entsprechen den Segmenten der 7-Segment Anzeige

 BCD mode an :  0 to 15 =  0 to 9, -, E, H, L, P, und ' '
	
*/

  MAX7219Send(DECODE_MODE, 0);   // setze BCD decode mode auf aus
 
  /* ALLE LEDs DER MATRIX AN: NUR ZUM DEBUGGEN */
  //MAX7219Send(DISPLAY_TEST, 0);  // Disable test mode

  MAX7219Send(INTENSITY, 1);     // setze Helligkeit auf maximalen Wert (15)
  	
  MAX7219Send(SHUTDOWN, 1);      // startet in shutdown mode	// macht alle LEDs aus


  MAX7219Send(1,0x00); // Setze die Reihen die nicht für unsere Messungen gebraucht werden auf 0.
  MAX7219Send(4,0x00);
  MAX7219Send(5,0x00);
  MAX7219Send(8,0x00);
}

void display_luminosity()
{
  int wmin = 200;   // Intervall zwischen 200 und 1250 LUX gewählt
  int wmax = 1250;

  int lux_var = lux;

  int LED_Anzahl = (lux_var - wmin) * 8 / (wmax - wmin); // Berechne Anzahl der anzuschaltenden LEDs

  switch(LED_Anzahl)    //  Anhand der berechneten LED_Anzahl werden die LEDs angeschaltet
  {
    case 0:
      MAX7219Send(2,0x00);
      MAX7219Send(3,0x00);
      break;
    case 1:
      MAX7219Send(2,0x80);
      MAX7219Send(3,0x80);
      break;
    case 2:
      MAX7219Send(2,0xC0);
      MAX7219Send(3,0xC0);
      break;
    case 3:
      MAX7219Send(2,0xE0);
      MAX7219Send(3,0xE0);
      break;
    case 4:
      MAX7219Send(2,0xF0);
      MAX7219Send(3,0xF0);
      break;
    case 5:
      MAX7219Send(2,0xF8);
      MAX7219Send(3,0xF8);
      break;
    case 6:
      MAX7219Send(2,0xFC);
      MAX7219Send(3,0xFC);
      break;
    case 7:
      MAX7219Send(2,0xFE);
      MAX7219Send(3,0xFE);
      break;
    case 8:
      MAX7219Send(2,0xFF);
      MAX7219Send(3,0xFF);
      break;
    
    default:
      perror("berechneter LED_Anzahl Wert (luminosity) ist nicht 0-8!");
      break;
  }
}

void display_pressure()
{
  int wmin = 960;   // Intervall zwischen 960 und 1070 hPa gewählt
  int wmax = 1070;

  int hPa_var = hPa;

  int LED_Anzahl = (hPa_var - wmin) * 8 / (wmax - wmin);  // Berechne Anzahl der anzuschaltenden LEDs

  switch(LED_Anzahl)
  {
    case 0:
      MAX7219Send(6,0x00);
      MAX7219Send(7,0x00);
      break;
    case 1:
      MAX7219Send(6,0x80);
      MAX7219Send(7,0x80);
      break;
    case 2:
      MAX7219Send(6,0xC0);
      MAX7219Send(7,0xC0);
      break;
    case 3:
      MAX7219Send(6,0xE0);
      MAX7219Send(7,0xE0);
      break;
    case 4:
      MAX7219Send(6,0xF0);
      MAX7219Send(7,0xF0);
      break;
    case 5:
      MAX7219Send(6,0xF8);
      MAX7219Send(7,0xF8);
      break;
    case 6:
      MAX7219Send(6,0xFC);
      MAX7219Send(7,0xFC);
      break;
    case 7:
      MAX7219Send(6,0xFE);
      MAX7219Send(7,0xFE);
      break;
    case 8:
      MAX7219Send(6,0xFF);
      MAX7219Send(7,0xFF);
      break;
    
    default:
      perror("berechneter LED_Anzahl Wert (pressure) ist nicht 0-8!");
      break;
  }
}