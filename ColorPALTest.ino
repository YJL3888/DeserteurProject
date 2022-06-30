/* ColorPal Sensor Example for Arduino
  Author: Martin Heermance, with some assistance from Gordon McComb
  This program drives the Parallax ColorPAL color sensor and provides
  serial RGB data in a format compatible with the PC-hosted
  TCS230_ColorPAL_match.exe color matching program.
*/

#include <SoftwareSerial.h>

#define sio      6           // ColorPAL connected to pin 6
#define unused   255         // Non-existant pin # for SoftwareSerial
#define sioBaud  4800

// Received RGB values from ColorPAL
int red;
int grn;
int blu;

// Set up two software serials on the same pin.
SoftwareSerial serin(sio, unused);
SoftwareSerial serout(unused, sio);

void setup() {

  delay(2000);

  Serial.begin(9600);
  reset();                    // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(sio, OUTPUT);
  serout.print("=(00 $ m)!"); // Loop print values, see ColorPAL documentation
  serout.end();               // Discontinue serial port for transmitting
  
  pinMode(sio, INPUT);
  serin.begin(sioBaud);       // Set up serial port for receiving
}

void loop() {
  readData();
}  

// Reset ColorPAL; see ColorPAL documentation for sequence
void reset() {
  delay(200);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  pinMode(sio, INPUT);
  while (digitalRead(sio) != HIGH);
  pinMode(sio, OUTPUT);
  digitalWrite(sio, LOW);
  delay(80);
  pinMode(sio, INPUT);
  delay(200);
}

void readData() {
  char buffer[32];
 
  if (serin.available() > 0) {
    // Wait for a $ character, then read three 3 digit hex numbers
    buffer[0] = serin.read();
    if (buffer[0] == '$') {
      for(int i = 0; i < 9; i++) {
        while (serin.available() == 0);     // Wait for next input character
        buffer[i] = serin.read();
        if (buffer[i] == '$')               // Return early if $ character encountered
          return;
      }
      
      parseAndPrint(buffer);
      delay(10);
    }
  }
}

// Parse the hex data into integers 
void parseAndPrint(char * data) {
  sscanf (data, "%3x%3x%3x", &red, &grn, &blu);  // Pull the R, G, and B values from the data string
  if( 30<red && red<65 && 40<grn && grn<85 && 200<blu && blu<255){ //BLUE
    Serial.println("blue");
  }
  else if( 210<red && red<240 && 160<grn && grn<185 && 185<blu && blu<215){ //YELLOW
    Serial.println("yellow");
  }
  else if( 185<red && red<215 && 20<grn && grn<50 && 85<blu && blu<115){
    Serial.println("pink");
  }
  else {
    char buffer[48];                               // create a buffer
  sprintf(buffer, "r = %4.4d    g = %4.4d    b = %4.4d", red, grn, blu);   //print the values into a buffer as formatted integers
  Serial.println(buffer);
  }
  
}
