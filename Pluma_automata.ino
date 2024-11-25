#include <Servo.h>

// Definición de los pines
const int trigPin = 9;    // Pin del Trig del HC-SR04
const int echoPin = 10;   // Pin del Echo del HC-SR04
const int servoPin = 12;  // Pin del servomotor
const int buttonPin = 7;  // Pin del botón

// Variables para tiempo, distancia y debounce
long duration;
int distance;
Servo servoMotor;
bool isOpen = false;
unsigned long lastDebounceTime = 0;  // Tiempo de último cambio en el botón
const int debounceDelay = 50;        // Tiempo para evitar rebotes en el botón
int lastButtonState = HIGH;          // Último estado del botón
unsigned long gateOpenTime = 0;      // Tiempo en que se abrió la pluma
const int gateDelay = 5000;          // Tiempo que la pluma permanece abierta (5 segundos)

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Botón con resistencia interna activada
  servoMotor.attach(servoPin);
  servoMotor.write(180);             // Iniciar con la pluma cerrada
  Serial.begin(9600);                // Para monitorear en el puerto serie
}

void loop() {
  // Medir distancia con el sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calcular el tiempo que tarda en recibir el eco
  duration = pulseIn(echoPin, HIGH);

  // Convertir el tiempo a distancia (en cm)
  distance = duration * 0.034 / 2;

  // Verificar si la distancia está dentro de un rango razonable (1-400 cm)
  if (distance > 0 && distance <= 400) {
    // Verificar si hay un objeto a 10 cm o menos
    if (distance <= 10 && !isOpen) {
      openGate();  // Si detecta un objeto cercano y la pluma está cerrada
    }
  }

  // Verificar si el botón ha sido presionado (usando debounce)
  int buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();  // Reiniciar el temporizador de debounce
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonState == LOW && !isOpen) {
      openGate();  // Abrir la pluma si el botón ha sido presionado
    }
  }

  lastButtonState = buttonState;

  // Si la pluma está abierta, verificar si ha pasado el tiempo para cerrarla
  if (isOpen && (millis() - gateOpenTime >= gateDelay)) {
    closeGate();  // Cerrar la pluma después de 5 segundos
  }

  delay(100);  // Esperar un poco antes de la siguiente medición
}

void openGate() {
  Serial.println("Abriendo la pluma");
  servoMotor.write(90);  // Abrir la pluma
  isOpen = true;
  gateOpenTime = millis();  // Registrar el tiempo de apertura
}

void closeGate() {
  Serial.println("Cerrando la pluma");
  servoMotor.write(180);  // Cerrar la pluma
  isOpen = false;
}