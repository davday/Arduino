int Vibration_signal = 2; //Define el valor incial para el sensor
int Sensor_State = 1;
int RojoLed = 5;
int buzzerPin = 4;
int var=0;

void setup() {  
  pinMode(Vibration_signal, INPUT); //Set pin as input
  pinMode(RojoLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{
  Sensor_State = digitalRead(Vibration_signal);
  if (Sensor_State == 1) {
    while(var < 5){
     tone(buzzerPin, 1000);  // Tocar el buzzer a 1000 Hz
    delay(80);  // Sonar el buzzer por 300 ms
    noTone(buzzerPin);  // Apagar el buzzer
    // Encender el LED
    digitalWrite(RojoLed, HIGH);
    delay(100);  // Esperar 1 segundo
     // Apagar el LED
    digitalWrite(RojoLed, LOW);
   delay(100);  // Esperar 1 segundo
    var++;
    }
    tone(buzzerPin, 526);  // Tocar el buzzer a 1000 Hz
    delay(200);  // Sonar el buzzer por 300 ms
    noTone(buzzerPin);  // Apagar el buzzer
    // Encender el LED
  }
  else {
      digitalWrite(RojoLed, LOW);
      var=0;
  }
  delay(50);
}