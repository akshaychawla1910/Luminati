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

SoftwareSerial mySerial(10, 11); // RX, TX
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
   
      color++;
      if(color==7)
      color=1;
      
      }

       if(x==3)
      {
        analogWrite(redpin,255*0.6 );
     
       analogWrite(greenpin,255);
      
      }

       if(x==4)
      {
       analogWrite(redpin,255*0.3 );
      analogWrite(bluepin,255);
       analogWrite(greenpin,255);
      
      }

        if(x==5)
      {
       sound();
      }

  
      else  if(x==6)
      {
        color=0;
        digitalWrite(greenpin,LOW);
        digitalWrite(redpin,LOW);
        digitalWrite(bluepin,LOW);
      }

  }

 if(x==2)
 fade();
if(x==5)
sound();
}


void fade()
{ 

     for(int i=200;i>0;i--)
    {
      if(mySerial.available())
      break;

      if(color==red)
      analogWrite(redpin,i);

      else if(color==green)
      analogWrite(greenpin,i);

      else if(color==blue)
      analogWrite(bluepin,i );

      else if(color==pink)
      {
      analogWrite(redpin,i*0.6 );
      analogWrite(bluepin,i);
      }
      else if(color==cyan)
      {
      analogWrite(greenpin,i);
      analogWrite(bluepin,i);
      }
       else if(color==yellow)
      {
      analogWrite(greenpin,i );
      analogWrite(redpin,i*0.6 );
      }
      for(int j=0;j<15;j++)
      {
      delay(1);
      if(mySerial.available())
      break;

    
      }
    }

    for(int i=0;i<200;i++)
    {
      if(mySerial.available())
      break;

      if(color==red)
      analogWrite(redpin,i);

      else if(color==green)
      analogWrite(greenpin,i);

      else if(color==blue)
      analogWrite(bluepin,i );

      else if(color==pink)
      {
      analogWrite(redpin,i*0.6 );
      analogWrite(bluepin,i);
      }
      else if(color==cyan)
      {
      analogWrite(greenpin,i);
      analogWrite(bluepin,i);
      }
       else if(color==yellow)
      {
      analogWrite(greenpin,i );
      analogWrite(redpin,i*0.6);
      }
      for(int j=0;j<15;j++)
      {
      if(mySerial.available())
      break;

      delay(1);
      }
    }


  }





void rgb(int color)
{
     digitalWrite(greenpin,LOW);
      digitalWrite(redpin,LOW);
      digitalWrite(greenpin,LOW);
    
  if(color==red)
      digitalWrite(redpin,HIGH);

      else if(color==green)
      digitalWrite(greenpin,HIGH);

      else if(color==blue)
      digitalWrite(bluepin,HIGH );

      else if(color==pink)
      {
      digitalWrite(redpin,HIGH );
      digitalWrite(bluepin,HIGH);
      }
      else if(color==cyan)
      {
      digitalWrite(greenpin,HIGH);
      digitalWrite(bluepin,HIGH);
      }
       else if(color==yellow)
      {
      digitalWrite(greenpin,HIGH );
      digitalWrite(redpin,HIGH );
      }
}


void sound() {
  
int sig=analogRead(soundsensor);                                 //reading audio signal from sensor
Serial.println(sig);
if(sig>200)
colorr++;

strip(light[colorr][0],light[colorr][1],light[colorr][2]);     //getting color from light array and calling strip function

if(colorr==9)
colorr=0;

  
}


void strip(int r,int g, int b)                              //gives transition effect to color change
{
  if(r>redd)
  {
    for(int i=redd;i<r;i++)
    {
      rgb(i,greenn,bluee);
      redd++;
      delay(1);
    }
  }

  else if(redd>=r)
  {
    for(int i=redd;i>r;i--)
    {
      rgb(i,greenn,bluee);
      redd--;
      delay(1);
    }
  }

if(g>greenn)
  {
    for(int i=greenn;i<g;i++)
    {
      rgb(redd,i,bluee);
      greenn++;
      delay(1);
    }
  }

  else if(greenn>=g)
  {
    for(int i=greenn;i>g;i--)
    {
      rgb(redd,i,bluee);
      greenn--;
      delay(1);
    }
  }

  if(b>bluee)
  {
    for(int i=bluee;i<b;i++)
    {
      rgb(redd,greenn,i);
      bluee++;
      delay(1);
    }
  }

  else if(bluee>=b)
  {
    for(int i=bluee;i>b;i--)
    {
      rgb(redd,greenn,i);
      bluee--;
      delay(1);
    }
  }

}


void rgb(int r, int g, int b)                               //writing colors to rgb strip
{
  analogWrite(redpin,r);
  analogWrite(greenpin,g);
  analogWrite(bluepin,b);
}



