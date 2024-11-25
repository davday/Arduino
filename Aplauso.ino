// Definir pines
const int ledPin = 13;   // Pin donde está el LED
const int soundSensorPin = 2; // Pin donde está conectado el sensor de sonido

// Variables para el estado del LED y el sonido detectado
int soundState;          // Estado del sensor de sonido
int lastSoundState = LOW; // Último estado del sensor de sonido
bool ledOn = false;      // Variable para controlar si el LED está encendido

void setup() {
  // Configurar pin del LED como salida
  pinMode(ledPin, OUTPUT);
  
  // Configurar pin del sensor de sonido como entrada
  pinMode(soundSensorPin, INPUT);
  
  // Inicializar el LED apagado
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Leer el estado del sensor de sonido
  soundState = digitalRead(soundSensorPin);
  
  // Detectar el cambio de estado (transición de LOW a HIGH)
  if (soundState == HIGH && lastSoundState == LOW) {
    // Cambiar el estado del LED
    ledOn = !ledOn;
    // Actualizar el LED
    digitalWrite(ledPin, ledOn ? HIGH : LOW);
    // Pequeño retraso para evitar múltiples detecciones por un solo aplauso
    delay(50);
  }

  // Guardar el estado actual del sensor de sonido como el último estado
  lastSoundState = soundState;
}
