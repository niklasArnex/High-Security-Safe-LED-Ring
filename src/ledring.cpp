#include "ledring.h"
 
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, LEDBandIN, NEO_GRB + NEO_KHZ800);

uint32_t btn_state = BTN_NOT_PRESSED;
int btn_counter = 0;
int selectedNumber = 0;
int eingabeArrayMain[3];
int eingabeArrayMainIndex = 0;
int vorgabeCodeArrayMain[3] = {1,1,1};
int vorgabeCodeArrayMainIndex = 0;

void led_ring_setup() {
    pinMode(LEDBandIN, OUTPUT);
    strip.begin();
    strip.show();
    Serial.begin(9600);
}


void setLEDColorAusgabe(int pixel, int red, int green, int blue) {
    strip.setPixelColor(pixel, strip.Color(red, green, blue));
    strip.show();
}
 
void clearLEDs() {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}

void verbindung(int selectedNumber){
 
    clearLEDs();
    //den counter wert verändere das die vorherige LED nicht gespeichert bleibt sondern alles resetet wird
    int EingabePIN = -1;
   //static variable ???
 
    if ((selectedNumber - 0) % 12 == 0)
    {
        setLEDColorAusgabe(0,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=0;
            }
 
    }
    else if((selectedNumber - 1) % 12 == 0){
         setLEDColorAusgabe(1,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=1;
            }
               
    }    
    else if ((selectedNumber - 2) % 12 == 0){
 
        setLEDColorAusgabe(2,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=2;
            }
 
    }else if ((selectedNumber - 3) % 12 == 0){
 
        setLEDColorAusgabe(3,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=3;
            }
   
    }else if ((selectedNumber - 4) % 12 == 0){
 
        setLEDColorAusgabe(4,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=4;
            }
 
    }else if ((selectedNumber - 5) % 12 == 0){
 
        setLEDColorAusgabe(5,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=5;
            }
 
    }else if ((selectedNumber - 6) % 12 == 0){
 
        setLEDColorAusgabe(6,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=6;
            }
 
    }else if ((selectedNumber - 7) % 12 == 0){
 
        setLEDColorAusgabe(7,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=7;
            }
 
    }else if ((selectedNumber - 8) % 12 == 0){
 
        setLEDColorAusgabe(8,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=8;
            }
 
    }else if ((selectedNumber - 9) % 12 == 0){
 
        setLEDColorAusgabe(9,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=9;
            }
 
    }else if ((selectedNumber - 10) % 12 == 0){
 
        setLEDColorAusgabe(10,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=10;
            }
 
    }else if ((selectedNumber - 11) % 12 == 0){
 
        setLEDColorAusgabe(11,0,0,255);
            if (btn_state == BTN_PRESSED)
            {
                EingabePIN=11;
            }
 
    }

    if (EingabePIN > -1 && eingabeArrayMainIndex < 3)
    //Wenn der eingabe Wert sich nicht im eingangszustand befindet und das Array nicht voll ist wird der Wert in das Array reingespeichert
    {
        eingabeArrayMain[eingabeArrayMainIndex]=EingabePIN;
          //Dann wird "EingabePIN WErt" in das Array reingeschrieben  
        eingabeArrayMainIndex++;                        
    }
 
}
void arrayVergleich(){
 
if (eingabeArrayMain[0] == vorgabeCodeArrayMain[0] && eingabeArrayMain[1] == vorgabeCodeArrayMain[1] &&eingabeArrayMain[2] == vorgabeCodeArrayMain[2] )
{
    clearLEDs();
    for (int i = 0; i < 13; i++)
    {
        setLEDColorAusgabe(i,0,255,0);
    }
 
    //Platz für Funktion Schloss öffnen oder sowas
 
    //10 Sekunden leuchtet das Band bei richtiger eingabe grün
    delay(10000);
    //eingabe Array wird auf 0 gesetzt und man kann neu eingeben
    std::fill(std::begin(eingabeArrayMain), std::end(eingabeArrayMain), 0);
    //Den index auf 0 setzten vom Array damit man mehrmals hintereinander das Array befüllen kann weil sonst würde nichtsmehr reingespeichert (weil index dann größer als 3 wäre) werden siehe zeile 214
    eingabeArrayMainIndex = 0;
 
    //Platz für Funktion Schloss öffnen oder sowas oder an der Stelle kommt auf den Funktionsaufbau drauf an
 
}else if(eingabeArrayMainIndex >= 3 &&(!(eingabeArrayMain[0] == vorgabeCodeArrayMain[0] && eingabeArrayMain[1] == vorgabeCodeArrayMain[1] &&eingabeArrayMain[2] == vorgabeCodeArrayMain[2]))){
   
    clearLEDs();
    for (int i = 0; i < 13; i++)
    {
        setLEDColorAusgabe(i,255,0,0);
    }
    //10 Sekunden leuchtet das Band bei falscher eingabe rot
    delay(10000);
    //eingabe Array wird auf 0 gesetzt und man kann neu eingeben
    std::fill(std::begin(eingabeArrayMain), std::end(eingabeArrayMain), 0);
    //Den index auf 0 setzten vom Array damit man mehrmals hintereinander das Array befüllen kann weil sonst würde nichtsmehr reingespeichert (weil index dann größer als 3 wäre) werden siehe zeile 214
    eingabeArrayMainIndex = 0;  
 
}
 
}