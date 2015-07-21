#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;   

const int buttonPin = 12;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


int motorPin1 = 8;    // IN 1
int motorPin2 = 9;    // IN 2
int motorPin3 = 10;   // In 3
int motorPin4 = 11;   // IN 4

int motorSpeed = 1000;  //variable to set stepper speed
                        // Experiment with this; too small will not work.
int count = 0;          // count of steps made
int countsperrev = 360; // number of steps per revolution for this motor

int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int btncounter = 0;

void setup() {
  // initialize the LED pin as an output:
   lcd.init();                      // initialize the lcd 
 // Print a message to the LCD.
 lcd.backlight();
 
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  photocellReading = analogRead(photocellPin);  
  float light = photocellReading * 1.0;
   if (photocellReading < 25) {
   lcd.print("Turning Left");
   lcd.print(light);
   
       for (int i = 0; i < countsperrev; i++){clockwise();
       }
       lcd.clear();
   }else if(photocellReading >= 25){
 lcd.print("Turning Right");
   lcd.print(light);
       for (int i = 0; i < countsperrev; i++){clockwise();
       }
       lcd.clear();
   }
    

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH); 
    
     if(btncounter % 2 == 0){
       lcd.print("Turning Left");
       for (int i = 0; i < countsperrev; i++){clockwise();
       }
       lcd.clear();
     }
     else{
       
       lcd.print("Turning Right");
           for (int i = 0; i < countsperrev; i++){anticlockwise();
       }
       lcd.clear();
     }
     
      btncounter++;
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}


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

