#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>

//Define Pins
#define EncoderPinA 2   // Encoder Pin A pin 2 and pin 3 are inturrpt pins
#define EncoderPinB 3   // Encoder Pin B
#define EncoderPinA2 13
#define EncoderPinB2 19



//Initialize Variables
long counts = 0; //counts the encoder counts. The encoder has ~233counts/rev
long counts2 = 0;

void setup() {
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);  
  digitalWrite(EncoderPinA, LOW); //initialize Pin States
  digitalWrite(EncoderPinB, LOW);
  attachInterrupt(0, readEncoder, CHANGE); //attach interrupt to PIN 2 
  pinMode(EncoderPinA2, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB2, INPUT);  
  digitalWrite(EncoderPinA2, LOW); //initialize Pin States
  digitalWrite(EncoderPinB2, LOW);
  attachInterrupt(digitalPinToInterrupt(2),readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(13),readEncoder2, CHANGE);  
  }

void loop() {
  Serial.println(counts);
}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts-1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts+1;
  }
}

void readEncoder2() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{ 
  if(digitalRead(EncoderPinB2) == digitalRead(EncoderPinA2) )
  {
    counts2 = counts2-1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts2 = counts2+1;
  }
}
