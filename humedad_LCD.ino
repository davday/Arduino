#include <LiquidCrystal.h>

// Inicializamos la pantalla LCD con los pines que usaremos
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Pin A0 del sensor al la entra analoga A0
int SensorPin = A0;

void setup() {
  // Configuramos la pantalla LCD con 16 columnas y 2 filas
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  
  // Mostramos un mensaje inicial en la pantalla LCD
  lcd.print("Humedad: ");
}

void loop() {
  // Leemos el valor del sensor de humedad
  int humedad = analogRead(SensorPin);

  // Convertimos el valor leído (0-1023) a un porcentaje (0-100)
  int porcentajeHumedad = map(humedad, 1023, 0, 0, 100);
  //limpiamos y reescribirmos la primera linea
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Humedad: ");
  
  // Limpiamos la segunda fila de la pantalla LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Borra la segunda fila
  
  // Mostramos el porcentaje de humedad en la pantalla LCD
  lcd.setCursor(0, 1);
  lcd.print(porcentajeHumedad);
  lcd.print("%");

  // Mostramos un mensaje si la humedad es del 40% o menor
  if (porcentajeHumedad <= 45) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hora de regar");
  }

  // Imprimimos el valor en el monitor serial para depuración
  Serial.println(porcentajeHumedad);

  delay(1000); // Esperamos 1 segundo antes de volver a medir
}
