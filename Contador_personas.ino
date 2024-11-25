#include <LiquidCrystal.h>

// Configuración de la pantalla LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pines para el sensor ultrasónico
const int trigPin = 9;
const int echoPin = 10;

// Variables para medir la distancia
long duration;
int distance;
int personCount = 0;

// Distancia mínima para detectar una "persona" (en cm)
const int detectionDistance = 20; // Ajusta según sea necesario
bool objectDetected = false;

void setup() {
  // Iniciar comunicación serie
  //Serial.begin(9600);
  
  // Configurar los pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Iniciar la pantalla LCD
  lcd.begin(16, 2);
  lcd.print("Numero");
  // Mostrar mensaje inicial
  lcd.setCursor(0, 1);
  lcd.print("de personas");
  delay (2500);
  lcd.clear();
  lcd.setCursor(9, 0);
  lcd.print(personCount);
}

void loop() {
  // Enviar pulso del sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Medir duración del eco
  duration = pulseIn(echoPin, HIGH);
  
  // Calcular la distancia en cm
  distance = duration * 0.034 / 2;
  
  // Verificar si un objeto está a la distancia definida
  if (distance > 0 && distance < detectionDistance && !objectDetected) {
    personCount++;
    objectDetected = true; // Evita contar múltiples veces la misma persona
    
    // Actualizar la pantalla LCD con el nuevo conteo
    lcd.setCursor(9, 0);
    lcd.print(personCount);
    
    // Mostrar la distancia en la consola (opcional)
   // Serial.print("Distancia: ");
   // Serial.print(distance);
   // Serial.println(" cm");
  }

  // Reiniciar la detección si no hay objeto en el rango
  if (distance >= detectionDistance) {
    objectDetected = false;
  }

  delay(500); // Pausa entre mediciones
}