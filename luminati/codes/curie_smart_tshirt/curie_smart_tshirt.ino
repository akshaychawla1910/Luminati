 #include <CurieBLE.h>


BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
// Nordic's UART Characteristics:    https://devzone.nordicsemi.com/documentation/nrf51/6.0.0/s110/html/a00066.html
BLEService UARTService ("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"); // Nordic UART Service

// BLE UART Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic RXCharacteristic ("6E400002-B5A3-F393-E0A9-E50E24DCCA9E", BLEWrite);  // The Nordic Semiconductor UART App sends chars over this RXCharacteristic.
BLEUnsignedCharCharacteristic TXCharacteristic ("6E400003-B5A3-F393-E0A9-E50E24DCCA9E", BLERead);


int timer=0;
int ir = A0;
int buzzer = 9;

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
  // put your setup code here, to run once:
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);

  Serial.begin (9600);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName ("UART");
  blePeripheral.setAdvertisedServiceUuid (UARTService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute (UARTService);
  blePeripheral.addAttribute (RXCharacteristic);
  blePeripheral.addAttribute (TXCharacteristic);

  // set the initial value for the characeristic:
  RXCharacteristic.setValue (0);

  // begin advertising BLE service:
  blePeripheral.begin ();

  Serial.println ("BLE UART Peripheral");
//
//  pinMode(3, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(5, OUTPUT);
//  pinMode(6, OUTPUT);
//  pinMode(11, OUTPUT);
//  pinMode(A0, INPUT);


timer=millis()/1000;

}

void loop() {
  // put your main code here, to run repeatedly:

  if(analogRead(A0)>500)
  timer=millis()/1000;

  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central ();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print ("Connected to central: ");
    // print the central's MAC address:
    Serial.println (central.address ());

    // while the central is still connected to peripheral:
    while (central.connected ()) {
      
    if(analogRead(A0)>500)
    timer=millis()/1000;
      // if the remote device wrote to the characteristic,
      if (RXCharacteristic.written()) {
        Serial.print ("Received: ");
        Serial.print (RXCharacteristic.value ());  // RX Characteristic
        Serial.print (", ");
        Serial.println (TXCharacteristic.value ());  // TX Characteristic

        led(RXCharacteristic.value ());
      }

      // https://github.com/sandeepmistry/arduino-BLEPeripheral/blob/master/BLETypedCharacteristic.h
      RXCharacteristic.setValue (0);

    }
  int x= RXCharacteristic.value ()-'0';
 if(x==2)
 fade();
if(x==5)
 sound();
  }


}
void led(int x)
{
    x=x-'0';
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




void fade()
{ 

     for(int i=200;i>0;i--)
    {
//      if(mySerial.available())
//      break;

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
//      if(mySerial.available())
//      break;

    
      }
    }

    for(int i=0;i<200;i++)
    {
//      if(mySerial.available())
//      break;

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
delay(15);
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

  


