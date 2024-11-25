// Pines para los LEDs
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;

// Pines para las salidas digitales del módulo RF
const int D0 = 10;  // Botón A
const int D1 = 9;  // Botón B
const int D2 = 8;  // Botón C
const int D3 = 7;  // Botón D
const int VT = 6;  // Pin de transmisión válida

// Variables para almacenar el estado de los LEDs
bool estadoLed1 = false;
bool estadoLed2 = false;
bool estadoLed3 = false;
bool estadoLed4 = false;

// Variables para manejar el debounce
unsigned long debounceDelay = 200; // Tiempo de debounce en milisegundos
unsigned long lastDebounceTime[4] = {0, 0, 0, 0}; // Última vez que se presionó cada botón

void setup() {
  // Configuración de los pines de los LEDs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  // Configuración de los pines del módulo RF
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(VT, INPUT_PULLUP);  // Pin de transmisión válida

  // Inicializa los LEDs apagados
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  Serial.begin(9600);  // Para monitorear los datos en el puerto serie
}

void loop() {
  // Verifica si hay una transmisión válida
  if (digitalRead(VT) == HIGH) {
    // Debounce para cada botón
    verificarBoton(D0, &estadoLed1, led1, 0);  // Botón A -> Led1
    verificarBoton(D1, &estadoLed2, led2, 1);  // Botón B -> Led2
    verificarBoton(D2, &estadoLed3, led3, 2);  // Botón C -> Led3
    verificarBoton(D3, &estadoLed4, led4, 3);  // Botón D -> Led4
  }
}

// Función para verificar el estado de cada botón con debounce
void verificarBoton(int pinBoton, bool *estadoLed, int led, int index) {
  int lectura = digitalRead(pinBoton);
  
  if (lectura == HIGH && (millis() - lastDebounceTime[index]) > debounceDelay) {
    *estadoLed = !*estadoLed;  // Cambia el estado del LED
    digitalWrite(led, *estadoLed ? HIGH : LOW);  // Enciende o apaga el LED
    lastDebounceTime[index] = millis();  // Actualiza el tiempo de debounce
  }
}
