#include <Stepper.h>
const int stepsPerRevolution = 600;
Stepper myStepper(stepsPerRevolution, 8, 5, 2, 11);

char dataString[50] = {0};
float calibration = 0.00;
const int analogInPin = A0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10],temp;

void setup() {
  myStepper.setSpeed(90);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myStepper.step(stepsPerRevolution*10);
  delay(500);
  myStepper.step(-stepsPerRevolution*10);

  delay(500);
   for(int i=0;i<10;i++)
 {
  buf[i]=analogRead(analogInPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = 3 * pHVol + calibration;
 //Serial.print("sensor = ");
 //Serial.println(phValue);
 //sprintf(dataString,"%f",phValue);
 String dataPh = String (phValue);
 Serial.println(dataPh);
 delay(100);
 
}
