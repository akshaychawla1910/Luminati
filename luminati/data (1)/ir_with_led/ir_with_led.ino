//rgb pins
int red = 5;
int blue = 9;
int green = 6;

//ir sensor pins
int ir1 = 7  ;
int ir2 = 8;


int color = 10;              //color variable
void setup() {

  //defining rg pins as output
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  //defining ir sensor pins as input
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);

}

void loop() {

if(right_swipe)           //checks if hand is swiped right
color++;                  //if hand is swiped right, change color to next color


else if(left_swipe        //checks if hand is swiped left
color--;                  //if hand is swiped left, change color to previous color

glow();                  //glow RGB leds according to color value
delay(100);     
 
}

int right_swipe()
{
  if (digitalRead(ir1) == HIGH)
  {
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

  }
}

void glow()
{
   if (color % 3 == 0)
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, LOW);
  }

  if (color % 3 == 1)
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
  }

  if (color % 3 == 2)
  {
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
  }
}

