
int motorPin1 = 8;    // IN 1
int motorPin2 = 9;    // IN 2
int motorPin3 = 10;   // In 3
int motorPin4 = 11;   // IN 4

int motorSpeed = 1000;  //variable to set stepper speed
                        // Experiment with this; too small will not work.
int count = 0;          // count of steps made
int countsperrev = 360; // number of steps per revolution for this motor

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};


void setup() 
  {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  }

void loop()
  {
  int i;  
    for (i = 0; i < countsperrev; i++){clockwise();}
    delay(5000);
    for (i = 0; i < countsperrev; i++){   anticlockwise();}
    delay(5000);
  }

/////
//set pins to ULN2003 high in sequence from 1 to 4
//delay "motorSpeed" between each pin setting (to determine speed)
/////
void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
   		

