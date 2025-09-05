int led1 = 2; 
int led2 = 3; 
int switchPin = 4; // Switch general 
int switchLed1 = 10; // Switch asociado al LED1 
int switchLed2 = 9; // Switch asociado al LED2 
int ledPrendido = 0; // 0 = ninguno, 1 = LED1, 2 = LED2 
bool sistemaActivo;
bool primeraVez; // Para controlar el arranque inicial

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(switchLed1, INPUT_PULLUP);
  pinMode(switchLed2, INPUT_PULLUP);

  primeraVez = true;   // IMPORTANTE: inicializar
}

void loop() {
  sistemaActivo = (digitalRead(switchPin) == HIGH);
  if (sistemaActivo) {
    primeraVez = true;
    ledPrendido = 0;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    return;
  }

  int p0 = analogRead(A0);
  int p1 = analogRead(A1);

  int tp1 = map(p0, 0, 1023, 0, 5000);
  int tp2 = map(p1, 0, 1023, 0, 5000);

  bool estadoSwitch1 = (digitalRead(switchLed1) == LOW);
  bool estadoSwitch2 = (digitalRead(switchLed2) == LOW);

  // --- Arranque inicial ---
  if (primeraVez) {
    if (estadoSwitch1 && estadoSwitch2) {
      digitalWrite(led1, HIGH);
      ledPrendido = 1;
      delay(tp1);
      digitalWrite(led1, LOW);
      primeraVez = false;
    }
    return;   // esperar hasta que ambos estén abiertos
  }

  // --- Funcionamiento normal ---
  if (ledPrendido == 1 && estadoSwitch1 && estadoSwitch2) {
    // LED1 → LED2
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(tp2);
    digitalWrite(led2, LOW);
    ledPrendido = 2;
  }
  else if (ledPrendido == 2 && estadoSwitch1 && estadoSwitch2) {
    // LED2 → LED1
    digitalWrite(led1, HIGH);
    delay(tp1);
    digitalWrite(led1, LOW);
    ledPrendido = 1;
  }
}
