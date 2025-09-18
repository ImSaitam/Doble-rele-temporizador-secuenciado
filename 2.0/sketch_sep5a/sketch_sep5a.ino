int piston1 = 5; // D5
int piston2 = 3; // D3
int switchPin = 4; // D4
int switchPiston1 = 12; // D12
int switchPiston2 = 13; // D13
int pistonPrendido = 0;  // 0 = ninguno, 1 = piston1, 2 = piston2
bool sistemaActivo;
bool primeraVez; 
bool apagadoPendiente = false;

void setup() {
  pinMode(piston1, OUTPUT);
  pinMode(piston2, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(switchPiston1, INPUT_PULLUP);
  pinMode(switchPiston2, INPUT_PULLUP);
  digitalWrite(piston1, HIGH);
  digitalWrite(piston2, HIGH);

  primeraVez = true;
}

void loop() {
  sistemaActivo = (digitalRead(switchPin) == LOW);

  int p0 = analogRead(A0);
  int p1 = analogRead(A1);

  int tp1 = map(p0, 0, 1023, 0, 4000);
  int tp2 = map(p1, 0, 1023, 0, 4000);

  bool estadoSwitch1 = (digitalRead(switchPiston1) == LOW);
  bool estadoSwitch2 = (digitalRead(switchPiston2) == LOW);

  if (!sistemaActivo) {
    apagadoPendiente = true;
  }

  // --- Arranque inicial ---
  if (primeraVez && sistemaActivo) {
    if (estadoSwitch1 && estadoSwitch2) {
      digitalWrite(piston1, LOW);
      pistonPrendido = 1;
      delay(tp1);
      digitalWrite(piston1, HIGH);
      delay(tp1 * 0.95);
      primeraVez = false;
    }
    return;
  }

  // --- Funcionamiento normal ---
  if (pistonPrendido == 1 && estadoSwitch1 && estadoSwitch2) {
    digitalWrite(piston1, HIGH);
    digitalWrite(piston2, LOW);
    delay(tp2);
    digitalWrite(piston2, HIGH);
    delay(tp2 * 0.95);
    if (apagadoPendiente) {
      apagadoPendiente = false;
      primeraVez = true;
      pistonPrendido = 0;
      return;
    }

    pistonPrendido = 2;
  }
  else if (pistonPrendido == 2 && estadoSwitch1 && estadoSwitch2) {
    if (!sistemaActivo) {
      pistonPrendido = 0;
      primeraVez = true;
      apagadoPendiente = false;
      return;
    }

    digitalWrite(piston1, LOW);
    delay(tp1);
    digitalWrite(piston1, HIGH);
    delay(tp1 * 0.95);
    pistonPrendido = 1;
  }
}