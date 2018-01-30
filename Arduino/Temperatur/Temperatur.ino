/*  Mats-Vanselow.de
Temperatur auslesen mit einem Sensor

Lizenz (Deutsch): creative commons Namensnennung - Keine kommerzielle Nutzung - Weitergabe unter gleichen Bedingungen 3.0 Unported - http://creativecommons.org/licenses/by-nc-sa/3.0/deed.de
Bei Verwendung und Weitergabe des Quellcodes muss ein Verweis auf den Autor und die Webseite erfolgen. In Begleitdokumentationen ist ebenfalls in angemessener Weise dieser Verweis anzubringen.

License (English): creative commons Attribution-Noncommercial-Share Alike 3.0 Unported - http://creativecommons.org/licenses/by-nc-sa/3.0/
When using and distributing this source code a reference to the author and the web page must take place. In accompanying documents this reference must also be attached.

Code by Mats Vanselow - http://www.mats-vanselow.de

*/

int inPin = 5;          // input pin 1
float inValTotal;
int i;
int runs = 5;          // Anzahl der Durchl&auml;ufe
int waittime = 20;     // ms zwischen Durchl&auml;ufen
int delayVal = 1000;   // Intervall f&uuml;r Serial Output


void setup() {
Serial.begin(9600);
}

void loop() {
  Serial.println(getTemperatur());
    delay(delayVal);
}

int getTemperatur() {

  inValTotal = 0;
  for(i = 0;i<runs;i++){
    inValTotal = inValTotal + analogRead(inPin);
    delay(waittime);
  }

  inValTotal = inValTotal / runs / 2;
  return(int(inValTotal));
}
