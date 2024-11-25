// Pines para los LEDs
const int ledPins[] = {2, 3, 4, 5};
// Pines para los botones
const int buttonPins[] = {6, 7, 8, 9};
// Pin para el buzzer
const int buzzerPin = 12;

// Variables para el juego
int sequence[100];  // La secuencia del juego
int sequenceLength = 0;  // Longitud de la secuencia actual
int playerPosition = 0;  // Posición del jugador en la secuencia
bool gameOver = false;  // Estado del juego

void setup() {
  // Configurar los pines de los LEDs como salida
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Configurar los pines de los botones como entrada con resistencia pull-up
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Configurar el pin del buzzer como salida
  pinMode(buzzerPin, OUTPUT);

  // Inicializar la secuencia del juego
  randomSeed(analogRead(0));  // Usar una lectura analógica para generar números aleatorios
  nextRound();  // Comenzar el primer nivel
}

void loop() {
  if (!gameOver) {
    // Mostrar la secuencia actual al jugador
    showSequence();

    // Esperar a que el jugador reproduzca la secuencia
    playerPosition = 0;
    while (playerPosition < sequenceLength && !gameOver) {
      checkPlayerInput();
    }

    // Si el jugador completó la secuencia correctamente, pasar al siguiente nivel
    if (!gameOver) {
      delay(1000);  // Esperar un momento antes del próximo nivel
      nextRound();
    }
  } else {
    // Si el juego ha terminado, reiniciar después de un tiempo
    delay(2000);
    resetGame();
  }
}

void nextRound() {
  // Agregar un nuevo número a la secuencia
  sequence[sequenceLength] = random(0, 4);
  sequenceLength++;
}

void showSequence() {
  for (int i = 0; i < sequenceLength; i++) {
    digitalWrite(ledPins[sequence[i]], HIGH);  // Encender el LED correspondiente
    delay(500);  // Mantener el LED encendido por 500 ms
    digitalWrite(ledPins[sequence[i]], LOW);  // Apagar el LED
    delay(300);  // Pausa entre LEDs
  }
}

void checkPlayerInput() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {  // Si el botón correspondiente está presionado
      delay(50);  // Anti-rebote
      while (digitalRead(buttonPins[i]) == LOW);  // Esperar hasta que se suelte el botón

      // Verificar si la entrada del jugador es correcta
      if (sequence[playerPosition] == i) {
        digitalWrite(ledPins[i], HIGH);  // Encender el LED correspondiente
        delay(300);  // Mantenerlo encendido por 300 ms
        digitalWrite(ledPins[i], LOW);  // Apagar el LED
        playerPosition++;
      } else {
        // Si el jugador se equivoca, activar el buzzer y terminar el juego
         digitalWrite(buzzerPin, HIGH);
        gameOver = true;// Indicar que el juego ha terminado
        delay(1500);// Retraso para agar el led blanco
        digitalWrite(buzzerPin, LOW);
      }
    }
  }
}

void resetGame() {
  // Reiniciar todas las variables
  sequenceLength = 0;
  playerPosition = 0;
  gameOver = false;
  nextRound();  // Comenzar un nuevo juego
}

