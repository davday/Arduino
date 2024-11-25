// Pines para los LEDs
int ledVerde1 = 7;
int ledVerde2 = 6;
int ledAmarillo1 = 5;
int ledAmarillo2 = 4;
int ledRojo1 = 3;
int ledRojo2 = 2;

// Pin para medir el voltaje de la pila
int pinVoltaje = A0;

// Voltajes de referencia para determinar el nivel de la pila
float voltajeMax = 1.5;   // Voltaje máximo de una pila AA o AAA completamente cargada
float voltajeAlto = 1.4;  // Pila con buena carga
float voltajeMedio = 1.2; // Voltaje a mitad de carga
float voltajeBajo = 1.0;  // Pila descargada
float voltajeMin = 0.8;   // Pila completamente descargada

void setup() {
  // Configurar los pines de los LEDs como salida
  pinMode(ledVerde1, OUTPUT);
  pinMode(ledVerde2, OUTPUT);
  pinMode(ledAmarillo1, OUTPUT);
  pinMode(ledAmarillo2, OUTPUT);
  pinMode(ledRojo1, OUTPUT);
  pinMode(ledRojo2, OUTPUT);

}

void loop() {
  // Leer el voltaje de la pila en el pin A0
  int lecturaAnalogica = analogRead(pinVoltaje);
  
  // Convertir la lectura analógica (0-1023) a voltaje (0-5V)
  float voltaje = lecturaAnalogica * (5.0 / 1023.0);


  // Determinar el estado de la carga y encender los LEDs correspondientes
  if (voltaje >= voltajeMax) {
    // Pila completamente cargada, encender todos los LEDs
    digitalWrite(ledVerde1, HIGH);
    digitalWrite(ledVerde2, HIGH);
    digitalWrite(ledAmarillo1, HIGH);
    digitalWrite(ledAmarillo2, HIGH);
    digitalWrite(ledRojo1, HIGH);
    digitalWrite(ledRojo2, HIGH);
  } 
  else if (voltaje >= voltajeAlto && voltaje < voltajeMax) {
    // Pila en buen estado, encender todos menos un LED Verde
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, HIGH);
    digitalWrite(ledAmarillo1, HIGH);
    digitalWrite(ledAmarillo2, HIGH);
    digitalWrite(ledRojo1, HIGH);
    digitalWrite(ledRojo2, HIGH);
  }
  else if (voltaje >= voltajeMedio && voltaje < voltajeAlto) {
    // Pila a mitad de carga, encender 2 rojos y 2 amarillo
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledAmarillo1, HIGH);
    digitalWrite(ledAmarillo2, HIGH);
    digitalWrite(ledRojo1, HIGH);
    digitalWrite(ledRojo2, HIGH);
  }
  else if (voltaje >= voltajeBajo && voltaje < voltajeMedio) {
    // Pila baja, encender 2 rojos y 1 amarillo
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledAmarillo1, LOW);
    digitalWrite(ledAmarillo2, HIGH);
    digitalWrite(ledRojo1, HIGH);
    digitalWrite(ledRojo2, HIGH);
  }
  else if (voltaje >= voltajeMin && voltaje < voltajeBajo) {
    // Pila muy baja, encender solo 2 LED rojo
   digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledAmarillo1, LOW);
    digitalWrite(ledAmarillo2, LOW);
    digitalWrite(ledRojo1, HIGH);
    digitalWrite(ledRojo2, HIGH);
  }
  else {
    // Pila completamente descargada o mal conectada, apagar todos los LEDs
    digitalWrite(ledVerde1, LOW);
    digitalWrite(ledVerde2, LOW);
    digitalWrite(ledAmarillo1, LOW);
    digitalWrite(ledAmarillo2, LOW);
    digitalWrite(ledRojo1, LOW);
    digitalWrite(ledRojo2, HIGH);
  }

  // Pausa antes de la próxima lectura
  delay(500);
}

// Función para encender LEDs específicos y apagar el resto
void encenderLEDs(int led1, int led2 = -1, int led3 = -1, int led4 = -1, int led5 = -1) {
  // Apagar todos los LEDs primero para evitar interferencias
  apagarTodosLEDs();

  // Encender los LEDs especificados
  if (led1 != -1) digitalWrite(led1, HIGH);
  if (led2 != -1) digitalWrite(led2, HIGH);
  if (led3 != -1) digitalWrite(led3, HIGH);
  if (led4 != -1) digitalWrite(led4, HIGH);
  if (led5 != -1) digitalWrite(led5, HIGH);
}

// Función para encender todos los LEDs
void encenderTodosLEDs() {
  digitalWrite(ledVerde1, HIGH);
  digitalWrite(ledVerde2, HIGH);
  digitalWrite(ledAmarillo1, HIGH);
  digitalWrite(ledAmarillo2, HIGH);
  digitalWrite(ledRojo1, HIGH);
  digitalWrite(ledRojo2, HIGH);
}

// Función para apagar todos los LEDs
void apagarTodosLEDs() {
  digitalWrite(ledVerde1, LOW);
  digitalWrite(ledVerde2, LOW);
  digitalWrite(ledAmarillo1, LOW);
  digitalWrite(ledAmarillo2, LOW);
  digitalWrite(ledRojo1, LOW);
  digitalWrite(ledRojo2, LOW);
}
