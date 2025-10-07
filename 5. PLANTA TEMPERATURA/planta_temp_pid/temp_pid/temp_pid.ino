#include <PID_v1.h>
#define PIN_INPUT A0
#define PIN_OUTPUT 3

unsigned long periodo = 1000;//Periodo de muestreo en terminal en ms
unsigned long nowTime = 0;
float millis_div_1000 = 0;
float millisLast_div_1000 = 0;
float aux=0;
float tempC = 0.0; //Temperatura del Heater 1
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
double Kp=15.6, Ki=0.079, Kd=0.0;

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup()
{
  Input = analogRead(PIN_INPUT);
  Setpoint = 0.0;
  analogReference (INTERNAL); //Referencia analógica PIN AREF (1.1v)
  Serial.begin(9600);
  myPID.SetSampleTime(1000);
  myPID.SetMode(AUTOMATIC);
}
void loop()
{
  while (Serial.available() > 0)
  {
    Setpoint=Serial.parseFloat();//Introducir el setpoint desde el terminal
  }
    aux=0;
  for(int i=0;i<10;i++)
  {
    tempC = analogRead(PIN_INPUT);
    tempC = (1.1 * tempC * 100.0)/1024.0;
    aux = aux + tempC;
    delay(5);
  }
    Input = aux/10.0;
    myPID.Compute();
    analogWrite(PIN_OUTPUT, Output);
  if(millis() > nowTime + periodo)
  {
    nowTime=millis();
    millis_div_1000 = (float)nowTime/1000 - millisLast_div_1000;
    Serial.print(Setpoint);
    Serial.print(",");
    Serial.print(Input);
    Serial.print(",");
    Serial.println(Output/10);
    //Serial.print(",");
    //Serial.println(millis_div_1000);
  }
}