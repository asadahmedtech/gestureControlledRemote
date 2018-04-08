#include<Time.h>
#include<TimeAlarms.h>
#include<Wire.h>


// ir sensor
const int ProxSensor=2;
int inputVal = 1;


//Sensor 1 LU
int trigPin1 = 12;
int echoPin1 = 13;

//Sensor 2 LD
int trigPin2 =11;
int echoPin2 = 10;

//Sensor 3 RU
int trigPin3 = 5;
int echoPin3 = 4;

//Sensor 4 RD
int trigPin4 = 7;
int echoPin4 = 8;

long duration1, cm1;
long duration2, cm2;
long duration3, cm3;
long duration4, cm4;

int lu = 0;
int ru = 0;
int ld = 0;
int rd = 0;
int timer = -1;
int secs = -1;
int counter=0;
int gesture[4]={0,0,0,0};


void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT); 

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);

  Wire.begin();
}


void loop()
{
  Wire.beginTransmission(9);
  inputVal = digitalRead(ProxSensor);
  if(inputVal == 0)
  {
    Wire.write(5);
    resetVariable();
    delay(2000);
  }
  
  left_up_check();
  left_down_check();
  right_up_check();
  right_down_check();
  get_gesture();
  check();
  
//  printarr();
  if((lu != 0 || ld !=0 || ru != 0|| rd !=0)){
    if(timer==-1){
      timer = second();
      secs = second();
      timer+=2;
      if(timer>60){timer-=60;secs++;}
    }}
   if(second()>timer && timer !=-1){resetVariable();}
   Wire.endTransmission();
}


void left_up_check(){
  if(lu == 0){
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(5);
    
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin1, LOW);
  
    pinMode(echoPin1, INPUT);
    duration1 = pulseIn(echoPin1, HIGH);
  // convert the time into a distance
    cm1 = (duration1/2) / 29.1;
  }  
}

void left_down_check(){
  if( ld == 0){
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
  // convert the time into a distance
  cm2 = (duration2/2) / 29.1;
  }
}

void right_up_check(){
  if(ru == 0){
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);
  
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);

  pinMode(echoPin3, INPUT);
  duration3 = pulseIn(echoPin3, HIGH);
  // convert the time into a distance
  cm3 = (duration3/2) / 29.1;
  }
}

void right_down_check(){
  if(rd == 0){
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(5);
  
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);

  pinMode(echoPin4, INPUT);
  duration4 = pulseIn(echoPin4, HIGH);
  // convert the time into a distance
  cm4 = (duration4/2) / 29.1;
  }
}

void get_gesture()
{
  if(cm1 < 15 && lu==0){gesture[counter]=1;counter++;lu=1;}
  if(cm2 < 15 && ld==0){gesture[counter]=2;counter++;ld=1;}
  if(cm3 < 15 && ru==0){gesture[counter]=3;counter++;ru=1;}
  if(cm4 < 15 && rd==0){gesture[counter]=4;counter++;rd=1;}

}

void check(){
   int sum1=gesture[0]+gesture[1];
   int sum2=gesture[2]+gesture[3];
   if(sum1==3 && sum2==7){
//        Serial.println("Left");
        
        resetVariable();
        Wire.write(1);
        delay(2000);
    }
    else if(sum1==7 && sum2==3){
//        Serial.println("Right");
        resetVariable();
        Wire.write(2);
        delay(2000);
    }
    else if(sum1==4 && sum2==6){
//        Serial.println("Down");
        resetVariable();
        Wire.write(3);
        delay(2000);
    }
    else if(sum1==6 && sum2==4){
//        Serial.println("Up");
        resetVariable();
        Wire.write(4);
        delay(2000);
    }
  }
void resetVariable(){
  lu = 0;
  ru = 0;
  ld = 0;
  rd = 0;
  timer = -1;
  secs = -1;
  counter=0;
  inputVal=1;
  for(int i=0;i<4;i++)
  {
    gesture[i]=0;
  }
  
}

void printarr()
{
  for(int i=0;i<4;i++)
  {
    Serial.print(gesture[i]);
    
  }
  Serial.println();
}
  

