#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int64.h>

#define EncoderPinA 2
#define EncoderPinB 3
#define EncoderPinA2 13
#define EncoderPinB2 19

#define Left_Motor_A 4
#define Left_Motor_B 5
#define Right_Motor_A 6
#define Right_Motor_B 7

ros::NodeHandle nh;
std_msgs::Int32 lefttick;
std_msgs::Int32 righttick;

float x;
float y;
long counts = 0;
long counts2 = 0;

void messageCb( const std_msgs::Float64& msg) {
  x = msg.data;
}

void messageCb1( const std_msgs::Float64& msg) {
  y = msg.data;
}

ros::Subscriber<std_msgs::Float64> sub("left_publish", &messageCb);
ros::Subscriber<std_msgs::Float64> sub2("right_publish", &messageCb1);
ros::Publisher tickpubleft("/left/encoderTicks",&lefttick);
ros::Publisher tickpubright("/right/encoderTicks",&righttick);

void setup() {
  pinMode(EncoderPinA, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB, INPUT);
  digitalWrite(EncoderPinA, LOW); //initialize Pin States
  digitalWrite(EncoderPinB, LOW);
  pinMode(EncoderPinA2, INPUT); //initialize Encoder Pins
  pinMode(EncoderPinB2, INPUT);
  digitalWrite(EncoderPinA2, LOW); //initialize Pin States
  digitalWrite(EncoderPinB2, LOW);
  attachInterrupt(digitalPinToInterrupt(2), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(13), readEncoder2, CHANGE);
  pinMode(Left_Motor_A, OUTPUT);
  pinMode(Left_Motor_B, OUTPUT);
  pinMode(Right_Motor_A, OUTPUT);
  pinMode(Right_Motor_B, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub2);
  nh.advertise(tickpubleft);
  nh.advertise(tickpubright);
}

void loop() {
    nh.spinOnce();
    lefttick.data = count;
    righttick.data=count2;
    tickpubleft.publish(&lefttick);
    tickpubright.publish(&righttick);
    
  
  
  if (x>0)
  {
    analogWrite(9,x);
    digitalWrite(6,LOW);
  }
  if (x<0)
  { x=-1*x;
    digitalWrite(9,LOW);
    analogWrite(6,x);
  }
  if(x==0.0)
  {
    digitalWrite(9,LOW);
    digitalWrite(6,LOW);
  }


  if (y>0.0)
  {
    analogWrite(11,y);
    digitalWrite(10,LOW);
  }
  if (y<0.0)
  {
    y=-1*y;
    digitalWrite(11,LOW);
    analogWrite(10,y);
  }
  if(y==0.0)
  {
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
  }


}

void readEncoder() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{
  if (digitalRead(EncoderPinB) == digitalRead(EncoderPinA) )
  {
    counts = counts - 1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts = counts + 1;
  }
}

void readEncoder2() //this function is triggered by the encoder CHANGE, and increments the encoder counter
{
  if (digitalRead(EncoderPinB2) == digitalRead(EncoderPinA2) )
  {
    counts2 = counts2 - 1; //you may need to redefine positive and negative directions
  }
  else
  {
    counts2 = counts2 + 1;
  }
}
