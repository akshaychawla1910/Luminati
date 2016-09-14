int redpin=5;                       //red is connected to D5 of arduino nano
int greenpin=6;                     //green is connected to D6 of arduino nano
int bluepin=9;                      //blue is connected to D9 of arduino nano
int pulse=A0;                       //pulse rate sensor is connected to A0 of arduino nano

int brightness=0;                   //initial brightness of rgb strip
int color=0;                        // color value defines which color is selected
int red=1,blue=2,pink=3,green=4,cyan=5,yellow=6;    //defined colors 
void setup() {

                                    //defining rgb pins as OUTPUT and pulse pin as INPUT

pinMode(redpin,OUTPUT);
pinMode(greenpin,OUTPUT);
pinMode(bluepin,OUTPUT);
pinMode(pulse,INPUT);
Serial.begin(9600);
}

void rgb();                           //rgb function displays beat on RGB LED strip
int beat();                           //beat function returns 1 if beat is deected at sensor
void loop() {
  

while(beat()==0);                     //wait till beat is detected
                            
rgb();                                //displays fading beat effect on RGB LED strip
color++;                              //changes color for next beat
if(color==7)
color=red;

}



void rgb()
{
  analogWrite(redpin,0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin,0);
 
  fade(100, 1, 1);
  fade(30, 1, 1.5);
 // while(beat()==0);
  fade(255, 1, 1);
  fade(30, 1, 2);
  fade(15, 1, 4);
  fade(10, 1, 8);
  fade(8, 1, 20);
  fade(7, 1, 40);
  fade(6, 1, 80);
  fade(5, 1, 160);
  

//  delay(500);
}

void fade(int fadeTo, int fadeSpeed, float delayTime) {
  if (fadeTo > brightness) {
    while (brightness < fadeTo) {

      if(color==red)
      analogWrite(redpin, brightness);

      else if(color==green)
      analogWrite(greenpin, brightness);

      else if(color==blue)
      analogWrite(bluepin, brightness);

      else if(color==pink)
      {
      analogWrite(redpin, brightness);
      analogWrite(bluepin, brightness);
      }
      else if(color==cyan)
      {
      analogWrite(greenpin, brightness);
      analogWrite(bluepin, brightness);
      }
       else if(color==yellow)
      {
      analogWrite(greenpin, brightness);
      analogWrite(redpin, brightness*0.6);
      }
      
      brightness+=fadeSpeed;
      delay(delayTime);
    }
  }
  else {
    while (brightness > fadeTo) {
      
      if(color==red)
      analogWrite(redpin, brightness);

      else if(color==green)
      analogWrite(greenpin, brightness);

      else if(color==blue)
      analogWrite(bluepin, brightness);

      else if(color==pink)
      {
      analogWrite(redpin, brightness);
      analogWrite(bluepin, brightness);
      }
      
      brightness-=fadeSpeed;
       delay(delayTime);
}

}
}


int beat()
{
  
int value=analogRead(pulse);

  if(value>=700)
{
  

 Serial.println("beat!");
 while((analogRead(pulse)>=600));
  return 1;

}
else return 0;
}

//void fade(int r,int g,int b)
//{
//  while(r>0||g>0||b>0)
//  {
//    led(r,g,b);
//    delay(10);
//    
//    if(r>0)
//    r=r-9;
//    
//    if(g>0)
//    g=g-9;
//    
//    if(b>0)
//    b=b-9;
//    
//  }
//  led(0,0,0);
//}
  


