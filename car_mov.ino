//Pins
int DIR_L = 5;
int DIR_R=6;
int Ch2 = 9;
int Ch1 = 10;
int Ch4 = 11;
int MotorL12 = 7;
int MotorR12 = 8; 
//Variablrs 
int RightMotor = 0;
int LeftMotor = 0;
int SpeedValue = 0;
void setup() {
  Serial.begin(9600);
 pinMode(MotorL12, OUTPUT);
 pinMode(MotorR12, OUTPUT);
 pinMode(9, INPUT);
 pinMode(10, INPUT);
 pinMode(11, INPUT); 
 pinMode(5,OUTPUT);
 pinMode(6,OUTPUT);
}

void loop() {
 if(!pulseIn(10,HIGH))
 {
   Serial.println("OFF");
   digitalWrite(MotorL12,LOW);
   digitalWrite(MotorR12,LOW);
 }
 else
 {
   int  r = map(pulseIn(Ch4, HIGH), 1980, 960,255,0);
   if(r< 20){
    RightMotor=255;
    LeftMotor=-255;
    digitalWrite(MotorL12,HIGH);
    digitalWrite(MotorR12,HIGH);
   }
   else if(r>235){
    RightMotor=-255;
    LeftMotor=255;
    digitalWrite(MotorL12,HIGH);
    digitalWrite(MotorR12,HIGH);
   }
   else{
    SpeedValue = map(pulseIn(Ch2, HIGH), 1965, 980, 255,0);
    RightMotor = SpeedValue - map(pulseIn(Ch1, HIGH), 980, 1965, -70, 70);
    LeftMotor = SpeedValue - map(pulseIn(Ch1, HIGH), 980, 1965, +70, -70) - 2;
    Serial.println("SV:");
    Serial.println(SpeedValue);
    if(SpeedValue>=255)
      SpeedValue=255;
    if(SpeedValue >= 137 && SpeedValue <= 255){
      Serial.println("forward");
      digitalWrite(MotorL12,HIGH);
      digitalWrite(MotorR12,HIGH);
    }
    else if(SpeedValue >= 0 && SpeedValue <= 117){
      Serial.println("backward");
      digitalWrite(MotorL12,HIGH);
      digitalWrite(MotorR12,HIGH);
    }
    else{
      digitalWrite(MotorL12,LOW);
      digitalWrite(MotorR12,LOW);
    }

    if(RightMotor < 5){
      RightMotor = 0;
    }
    if(LeftMotor < 5){
      LeftMotor = 0;
    }
    if(RightMotor >250){
      RightMotor = 255;
    }
    if(LeftMotor > 250){
      LeftMotor = 255;
    }
   }
 
  Serial.print("RIGHT MOTOR: ");
  Serial.print(RightMotor);
  Serial.print("  LEFT MOTOR: ");
  Serial.println(LeftMotor);
  Serial.println(pulseIn(9,HIGH));
  analogWrite(5, LeftMotor);
  analogWrite(6, RightMotor);
 }
}
