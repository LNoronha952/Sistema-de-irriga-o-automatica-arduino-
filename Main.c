#include <DHT.h>
#include <LiquidCrystal.h>

// Definição dos pinos
#define DHTPIN 2
#define DHTTYPE DHT22
#define PIRPIN 3
#define RELAYPIN 4
#define SOILMOISTUREPIN A0

// Inicialização dos objetos
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Definição dos níveis de umidade
int soilMoistureThreshold = 500;  // Ajuste este valor conforme necessário

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  pinMode(PIRPIN, INPUT);
  pinMode(RELAYPIN, OUTPUT);
  digitalWrite(RELAYPIN, LOW);  // Relé desativado inicialmente

  lcd.print("Irrigacao Auto");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Leitura do sensor de umidade do solo
  int soilMoistureValue = analogRead(SOILMOISTUREPIN);
  Serial.print("Umidade do solo: ");
  Serial.println(soilMoistureValue);

  // Leitura do sensor de temperatura e umidade
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.print(" *C, Umidade: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Leitura do sensor de movimento
  int motionDetected = digitalRead(PIRPIN);
  Serial.print("Movimento detectado: ");
  Serial.println(motionDetected);

  // Atualização do display LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.print(soilMoistureValue);

  // Controle da bomba de água
  if (soilMoistureValue < soilMoistureThreshold && motionDetected == HIGH) {
    digitalWrite(RELAYPIN, HIGH);  // Liga a bomba de água
    lcd.setCursor(10, 1);
    lcd.print("Irrigando");
  } else {
    digitalWrite(RELAYPIN, LOW);  // Desliga a bomba de água
    lcd.setCursor(10, 1);
    lcd.print("          ");  // Limpa a mensagem de irrigação
  }

  delay(2000);  // Espera 2 segundos antes da próxima leitura
}
