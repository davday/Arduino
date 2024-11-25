// Pines para los sensores ultrasónicos
const int trigPin1 = 2;  // TRIG del sensor de frecuencia
const int echoPin1 = 3;  // ECHO del sensor de frecuencia
const int trigPin2 = 4;  // TRIG del sensor de volumen
const int echoPin2 = 5;  // ECHO del sensor de volumen

// Pin del buzzer
const int buzzerPin = 9;

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);  // Para depuración opcional
}

// Función para obtener la distancia desde un sensor ultrasónico
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Distancia en cm
  return distance;
}

void loop() {
  // Obtener distancias de los sensores ultrasónicos
  long distance1 = getDistance(trigPin1, echoPin1);  // Sensor 1 para frecuencia
  long distance2 = getDistance(trigPin2, echoPin2);  // Sensor 2 para volumen

  // Mapear la distancia a un rango de frecuencias y volumen
  int frequency = map(distance1, 10, 200, 200, 5000); // Rango de 200 Hz a 5 kHz
  int volume = map(distance2, 10, 200, 0, 255);  // Rango de volumen de 0 a 255

  // Limitar los valores para evitar errores
  frequency = constrain(frequency, 200, 5000);
  volume = constrain(volume, 0, 255);

  // Si la mano está dentro del rango, generar sonido
  if (distance1 <= 200 && distance2 <= 200) {
    tone(buzzerPin, frequency, 100);  // Generar el tono con la frecuencia
    analogWrite(buzzerPin, volume);   // Controlar el volumen
  } else {
    noTone(buzzerPin);  // Apagar el buzzer si no hay manos cerca
  }

  delay(50);  // Pequeña pausa para suavizar la lectura
}
