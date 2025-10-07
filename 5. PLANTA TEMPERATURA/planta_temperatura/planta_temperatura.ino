#define sensor1 A0
#define heater1 3
#define hot 9
//Variables Globales
unsigned long periodo = 1000;//Periodo de muestreo en ms
unsigned long nowTime = 0;
float millis_div_1000 = 0;
float millisLast_div_1000 = 0;
float aux=0;
float tempC = 0.0;
float T1 = 0.0;

void setup() {
  pinMode(hot,OUTPUT); //Led "Caliente" como salida
  digitalWrite(hot,LOW);
  analogReference (INTERNAL); //
  //Configuramos el puerto serial
  Serial.begin(9600);e
}
void loop() {
  //Filtro de promedio movil en la lectura ADC
  aux=0;
  if(millis() > nowTime + periodo)
  {
    nowTime=millis();
    millis_div_1000 = (float)nowTime/1000 - millisLast_div_1000;
    for(int i=0;i<10;i++){
    tempC = analogRead(sensor1);
    tempC = (1.1 * tempC * 100.0)/1024.0;
    aux = aux + tempC;
    delay(5);
    }
    T1 = aux/10.0;
    analogWrite(heater1,200);
    Serial.println(T1);
    //Serial.print(",");
    //Serial.println(millis_div_1000);
  }
}