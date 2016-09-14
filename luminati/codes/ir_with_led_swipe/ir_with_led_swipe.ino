//rgb pins
int redpin   = 5;
int bluepin = 9;
int greenpin = 6;

//ir sensor pins
int ir1 = 7;
int ir2 = 8;

int red=1,blue=2,pink=3,green=4,yellow=5; 
int color = 100;              //color variable
void setup() {
Serial.begin(9600);
  //defining rg pins as output
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  //defining ir sensor pins as input
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

}
int right_swipe();
int left_swipe();
void loop() {
Serial.println("in");
if(left_swipe())           //checks if hand is swiped right
{
color++; 
rgb((color% 5)+1);                 //glow RGB leds according to color value
  
Serial.println("right");//if hand is swiped right, change color to next color
}

else if(right_swipe())        //checks if hand is swiped left
{
  color--;
fade();                //glow RGB leds according to color val
 Serial.println("left");//if hand is swiped right, change color to next color
}         //if hand is swiped left, change color to previous color

  
// Serial.println(color);
}

int right_swipe()
{
  // Serial.println("High");
  if (digitalRead(ir1) == HIGH)
  {
   // Serial.println("High");
    int time = millis() / 1000;
    while (((millis() / 1000) - time) < 2)
    {
      if (digitalRead(ir2) == HIGH)
      {
   
         while(digitalRead(ir2));
       return 1;
      }
    }
    delay(100);
  }
  else
  return 0;
}

int left_swipe()
{
  if (digitalRead(ir2) == HIGH)
  {
    int time = millis() / 1000;
    while ((millis() / 1000) - time < 2)
    {  
      if (digitalRead(ir1) == HIGH)
      {
      
        while(digitalRead(ir1));
        break;
      }
    }

    delay(100);
  }
  else
  return 0;
}

void fade()
{ 
int color1=(color%5)+1;
     for(int i=200;i>0;i--)
    {
      if(digitalRead(ir1)==1||digitalRead(ir2)==1)
      break;

      if(color1==red)
      analogWrite(redpin,i);

      else if(color1==green)
      analogWrite(greenpin,i);

      else if(color1==blue)
      analogWrite(bluepin,i );

      else if(color1==pink)
      {
      analogWrite(redpin,i*0.6 );
      analogWrite(bluepin,i);
      }
     
       else if(color1==yellow)
      {
      analogWrite(greenpin,i );
      analogWrite(redpin,i*0.6 );
      }
      for(int j=0;j<15;j++)
      {
      delay(1);
      if(digitalRead(ir1)==1||digitalRead(ir2)==1)
      break;
      }
    }

    for(int i=0;i<200;i++)
    {
      if(digitalRead(ir1)==1||digitalRead(ir2)==1)
      break;

      if(color1==red)
      analogWrite(redpin,i);

      else if(color1==green)
      analogWrite(greenpin,i);

      else if(color1==blue)
      analogWrite(bluepin,i );

      else if(color1==pink)
      {
      analogWrite(redpin,i*0.6 );
      analogWrite(bluepin,i);
      }
    
       else if(color1==yellow)
      {
      analogWrite(greenpin,i );
      analogWrite(redpin,i*0.6);
      }
      for(int j=0;j<15;j++)
      {
      if(digitalRead(ir1)==1||digitalRead(ir2)==1)
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
  {
      digitalWrite(redpin,HIGH);
      
  }
      else if(color==green)
      digitalWrite(greenpin,HIGH);

      else if(color==blue)
      digitalWrite(bluepin,HIGH );

      else if(color==pink)
      {
      digitalWrite(redpin,HIGH );
      digitalWrite(bluepin,HIGH);
      }

       else if(color==yellow)
      {
      digitalWrite(greenpin,HIGH );
      digitalWrite(redpin,HIGH );
      }
}





