/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX
int soundsensor=A0;
int redpin = 5;
int bluepin = 9;
int greenpin = 6;


int colorr=0;
int redd=0,greenn=0,bluee=0;

int color=0;                                    // color value defines which color is selected
int red=1,blue=2,pink=3,green=4,cyan=5,yellow=6;
int light[10][3]={{255,0,0},{150,150,0},{0,255,0},{0,255,100},{0,100,255},{0,0,255},{100,100,100},{200,200,200},{100,0,200},{255,0,100}};

void setup() {
  pinMode(soundsensor,INPUT);
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}
int x=0;
void loop() { // run over and over
 
  while (mySerial.available()) {
     x=mySerial.read()-'0';
   
     Serial.println(x);
     
  if(x==1)
      {
      rgb(cyan);
      }
  
      
   if(x==2)
      {
rgb(blue);
      
      }

       if(x==3)
      {
 rgb(pink);
      
      }

       if(x==4)
      {
rgb(yellow);
      }

        if(x==5)
      {
rgb(green);
      }

  
      else  if(x==6)
      {
       
        digitalWrite(greenpin,LOW);
        digitalWrite(redpin,LOW);
        digitalWrite(bluepin,LOW);
      }

  }


}



void rgb(int color)
{
     digitalWrite(blue pin,0);
      digitalWrite(redpin,0);
      digitalWrite(greenpin,0);
    
  if(color==red)
      digitalWrite(redpin,HIGH);

      else if(color==green)
      digitalWrite(greenpin,HIGH);

      else if(color==blue)
      digitalWrite(bluepin,HIGH );

      else if(color==pink)
      {
      analogWrite(redpin,100 );
      digitalWrite(bluepin,HIGH);
      }
      else if(color==cyan)
      {
      analogWrite(greenpin,100);
      analogWrite(bluepin,255);
      }
       else if(color==yellow)
      {
      digitalWrite(greenpin,HIGH );
      digitalWrite(redpin,HIGH );
      }
}


void rgb(int r, int g, int b)                               //writing colors to rgb strip
{
  analogWrite(redpin,r);
  analogWrite(greenpin,g);
  analogWrite(bluepin,b);
}



