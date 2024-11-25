#include <LiquidCrystal.h>
#include <TimeLib.h>

// Configurar la pantalla LCD con los pines
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// Pines para los botones
const int buttonHourPin = 2;  // Botón para ajustar la hora o día
const int buttonMinutePin = 3; // Botón para ajustar los minutos o mes
const int buttonModePin = 4;   // Botón para cambiar entre los modos
const int buttonYearPin = 5;   // Botón para ajustar el año

int lastButtonHourState = LOW;
int lastButtonMinuteState = LOW;
int lastButtonModeState = LOW;
int lastButtonYearState = LOW;

// Variables para almacenar la fecha y hora
int hourSet = 12;
int minuteSet = 0;
int daySet = 1;
int monthSet = 1;
int yearSet = 2022;

// Modo de ajuste: 0 = horas/minutos, 1 = día/mes/año
int mode = 0;

unsigned long lastActivityTime = 0;  // Para contar el tiempo desde la última actividad
const unsigned long timeout = 60000; // 1 minuto de inactividad

bool screenOn = true;  // Para controlar si la pantalla está encendida o apagada

void setup() {
  // Inicializar la pantalla LCD
  lcd.begin(16, 2);

  // Configurar los pines de los botones
  pinMode(buttonHourPin, INPUT_PULLUP);
  pinMode(buttonMinutePin, INPUT_PULLUP);
  pinMode(buttonModePin, INPUT_PULLUP);
  pinMode(buttonYearPin, INPUT_PULLUP);

  // Iniciar la fecha y hora inicial
  setTime(hourSet, minuteSet, 0, daySet, monthSet, yearSet);

  lcd.setCursor(0, 0);
  lcd.print("     Reloj");
  delay(2000);
  lastActivityTime = millis();  // Iniciar el contador de inactividad
}

void loop() {
  // Leer el estado de los botones
  int buttonHourState = digitalRead(buttonHourPin);
  int buttonMinuteState = digitalRead(buttonMinutePin);
  int buttonModeState = digitalRead(buttonModePin);
  int buttonYearState = digitalRead(buttonYearPin);

  // Comprobar si ha pasado 1 minuto de inactividad
  if (millis() - lastActivityTime >= timeout && screenOn) {
    lcd.noDisplay();  // Apagar la pantalla
    screenOn = false;
  }

  // Cambiar entre los modos de ajuste
  if (buttonModeState == LOW && lastButtonModeState == HIGH) {
    mode++;
    if (mode > 1) {
      mode = 0;  // Volver al modo 0 si sobrepasa el modo 1
    }
    // Restablecer la pantalla y el tiempo de actividad
    lcd.display();  // Encender la pantalla
    screenOn = true;
    lastActivityTime = millis();
  }
  lastButtonModeState = buttonModeState;

  if (screenOn) {  // Solo actualizar si la pantalla está encendida
    if (mode == 0) {
      // Modo de ajuste de horas y minutos

      // Verificar si el botón de horas fue presionado
      if (buttonHourState == LOW && lastButtonHourState == HIGH) {
        hourSet++;
        if (hourSet > 23) {
          hourSet = 0;  // Reiniciar a 0 si sobrepasa las 23 horas
        }
        setTime(hourSet, minuteSet, 0, daySet, monthSet, yearSet);
        lastActivityTime = millis();  // Actualizar tiempo de actividad
      }
      lastButtonHourState = buttonHourState;

      // Verificar si el botón de minutos fue presionado
      if (buttonMinuteState == LOW && lastButtonMinuteState == HIGH) {
        minuteSet++;
        if (minuteSet > 59) {
          minuteSet = 0;  // Reiniciar a 0 si sobrepasa los 59 minutos
        }
        setTime(hourSet, minuteSet, 0, daySet, monthSet, yearSet);
        lastActivityTime = millis();  // Actualizar tiempo de actividad
      }
      lastButtonMinuteState = buttonMinuteState;

    } else if (mode == 1) {
      // Modo de ajuste de día, mes y año

      // Verificar si el botón de días fue presionado
      if (buttonHourState == LOW && lastButtonHourState == HIGH) {
        daySet++;
        if (daySet > 31) {
          daySet = 1;  // Reiniciar a 1 si sobrepasa los 31 días
        }
        setTime(hourSet, minuteSet, 0, daySet, monthSet, yearSet);
        lastActivityTime = millis();  // Actualizar tiempo de actividad
      }
      lastButtonHourState = buttonHourState;

      // Verificar si el botón de meses fue presionado
      if (buttonMinuteState == LOW && lastButtonMinuteState == HIGH) {
        monthSet++;
        if (monthSet > 12) {
          monthSet = 1;  // Reiniciar a enero si sobrepasa diciembre
        }
        setTime(hourSet, minuteSet, 0, daySet, monthSet, yearSet);
        lastActivityTime = millis();  // Actualizar tiempo de actividad
      }
      lastButtonMinuteState = buttonMinuteState;

      // Verificar si el botón de año fue presionado
      if (buttonYearState == LOW && lastButtonYearState == HIGH) {
        yearSet++;
        setTime(hourSet, minuteSet, 0, daySet, monthSet, yearSet);
        lastActivityTime = millis();  // Actualizar tiempo de actividad
      }
      lastButtonYearState = buttonYearState;
    }

    // Mostrar la hora y la fecha en la pantalla LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora: ");
    printDigits(hour(), 2);
    lcd.print(":");
    printDigits(minute(), 2);

    lcd.setCursor(0, 1);
    lcd.print("Fec.: ");
    printDigits(day(), 2);
    lcd.print("/");
    printDigits(month(), 2);
    lcd.print("/");
    lcd.print(year());
  }

  delay(250);  // Actualizar cada cuarto de segundo
}

void printDigits(int digits, int length) {
  if (digits < 10) {
    lcd.print('0');  // Agregar cero si el número es menor a 10
  }
  lcd.print(digits);
}
