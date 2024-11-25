// Definir pines del sensor HC-SR04 y LED
const int trigPin = 9;      // Pin TRIG del sensor
const int echoPin = 10;     // Pin ECHO del sensor
const int ledPin = 13;      // Pin del LED

// Umbral de distancia (en centímetros) para encender el LED
const int thresholdDistance = 20; // 20 cm

void setup() {
  // Configurar los pines
  pinMode(trigPin, OUTPUT);    // Pin TRIG como salida
  pinMode(echoPin, INPUT);     // Pin ECHO como entrada
  pinMode(ledPin, OUTPUT);     // Pin LED como salida

  // Iniciar la comunicación serial (opcional, para depuración)
  Serial.begin(9600);
}

void loop() {
  // Variables para calcular la distancia
  long duration;
  int distance;

  // Generar un pulso de 10us en el TRIG para iniciar la medición
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer el tiempo que tarda en regresar el pulso desde el ECHO
  duration = pulseIn(echoPin, HIGH);

  // Calcular la distancia (tiempo * velocidad del sonido / 2)
  distance = duration * 0.034 / 2;

  // Mostrar la distancia en el monitor serial (opcional)
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Encender el LED si la distancia es menor al umbral
  if (distance <= thresholdDistance) {
    digitalWrite(ledPin, HIGH); // Encender el LED
  } else {
    digitalWrite(ledPin, LOW);  // Apagar el LED
  }

  // Pequeño retraso para evitar lecturas demasiado rápidas
  delay(100);
}
