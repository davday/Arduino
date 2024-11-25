/**************************************************************************
Esta práctica consiste en realizar una medición de distancia a través de un
sensor ultrasonico, e imprimir la lectura en una pantalla LCD.
**************************************************************************/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
 int TRIGGER = 9;                    // trigger al pin 9
 int ECHO = 8;                       //  echo al pin 8
 float ESPERA,DISTANCIA;             //  variables tipo flotante.
 
void setup() 
{
  Serial.begin (9600);              // Comucicación serial
  pinMode (TRIGGER, OUTPUT);        //Pin 8 como salida
  pinMode (ECHO, INPUT);            //Pin 9 como entrada
  lcd.begin(16, 2);                 // Asignamos número de columnas y filas del LCD
  lcd.print("Sensor");
  lcd.setCursor(0,1);               //Columna,reglón
  lcd.print("ultrasonico     ");
  delay (2500);
  lcd.clear();
  lcd.print("Distancia:");
}
 
void loop() {
digitalWrite (TRIGGER,LOW);         // Nivel bajo trigger durante 2 microsegundos
delayMicroseconds(2);
digitalWrite (TRIGGER, HIGH);       // Nivel alto trigger durante 10 microsegundos;
delayMicroseconds (10);    
digitalWrite (TRIGGER, LOW);     
ESPERA = pulseIn (ECHO,HIGH);       // Esta función espera la aparición de un pulso y mide su duración                   
DISTANCIA =(ESPERA/2)/29.15;        // Fórmula para calcular distancia
Serial.print (DISTANCIA);           // Imprimimos la distancia en cm por el puerto serial
Serial.println ("cm"); 
lcd.setCursor(0,1);                //Columna,reglón
lcd.print(DISTANCIA);
lcd.print("   cm");
delay (500);
}