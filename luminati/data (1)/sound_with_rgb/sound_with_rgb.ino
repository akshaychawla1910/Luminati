
int sound=A0;
int redpin=5;
int greenpin=6;
int bluepin=9;
int color=0;
int red=0,green=0,blue=0;
int light[10][3]={{255,0,0},{150,150,0},{0,255,0},{0,255,100},{0,100,255},{0,0,255},{100,100,100},{200,200,200},{100,0,200},{255,0,100}};
void setup() {
  // put your setup code here, to run once:
pinMode(sound,INPUT);
pinMode(redpin,OUTPUT);
pinMode(greenpin,OUTPUT);
pinMode(bluepin,OUTPUT);
Serial.begin(9600);
}

void loop() {
  
int sig=analogRead(sound);                                 //reading audio signal from sensor
Serial.println(sig);
if(sig>500)
color++;

strip(light[color][0],light[color][1],light[color][2]);     //getting color from light array and calling strip function

if(color==9)
color=0;

  
}

void rgb(int r, int g, int b)                               //writing colors to rgb strip
{
  analogWrite(redpin,r);
  analogWrite(greenpin,g);
  analogWrite(bluepin,b);
}


void strip(int r,int g, int b)                              //gives transition effect to color change
{
  if(r>red)
  {
    for(int i=red;i<r;i++)
    {
      rgb(i,green,blue);
      red++;
      delay(1);
    }
  }

  else if(red>=r)
  {
    for(int i=red;i>r;i--)
    {
      rgb(i,green,blue);
      red--;
      delay(1);
    }
  }

if(g>green)
  {
    for(int i=green;i<g;i++)
    {
      rgb(red,i,blue);
      green++;
      delay(1);
    }
  }

  else if(green>=g)
  {
    for(int i=green;i>g;i--)
    {
      rgb(red,i,blue);
      green--;
      delay(1);
    }
  }

  if(b>blue)
  {
    for(int i=blue;i<b;i++)
    {
      rgb(red,green,i);
      blue++;
      delay(1);
    }
  }

  else if(blue>=b)
  {
    for(int i=blue;i>b;i--)
    {
      rgb(red,green,i);
      blue--;
      delay(1);
    }
  }

}

