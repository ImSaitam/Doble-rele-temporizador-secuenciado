int piston1 = 2; // Piston 1 = D2
int piston2 = 3; // Piston 2 = D3
int switchPin = 4;
int switchPiston1 = 10; // Switch Piston 1 = D10
int switchPiston2 = 9; // Switch Piston 2 = D9
int pistonPrendido = 0;  // 0 = ninguno, 1 = piston1, 2 = piston2 
bool sistemaActivo;
bool primeraVez; 
bool apagadoPendiente = false;

void setup() {
  Serial.begin(9600);
  pinMode(piston1, OUTPUT);
  pinMode(piston2, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(switchPiston1, INPUT_PULLUP);
  pinMode(switchPiston2, INPUT_PULLUP);

  primeraVez = true;
}

void loop() {
  sistemaActivo = (digitalRead(switchPin) == HIGH);

  int p0 = analogRead(A0);
  int p1 = analogRead(A1);

  int tp1 = map(p0, 0, 1023, 0, 5000);
  int tp2 = map(p1, 0, 1023, 0, 5000);

  bool estadoSwitch1 = (digitalRead(switchPiston1) == LOW);
  bool estadoSwitch2 = (digitalRead(switchPiston2) == LOW);

  if (!sistemaActivo) {
    apagadoPendiente = true;
  }

  // --- Arranque inicial ---
  if (primeraVez && sistemaActivo) {
    if (estadoSwitch1 && estadoSwitch2) {
      digitalWrite(piston1, HIGH);
      pistonPrendido = 1;
      delay(tp1);
      digitalWrite(piston1, LOW);
      primeraVez = false;
    }
    return;
  }

  // --- Funcionamiento normal ---
  if (pistonPrendido == 1 && estadoSwitch1 && estadoSwitch2) {
    digitalWrite(piston1, LOW);
    digitalWrite(piston2, HIGH);
    delay(tp2);
    digitalWrite(piston1, LOW);
    
    if (apagadoPendiente) {
      digitalWrite(piston2, LOW);
      apagadoPendiente = false;
      primeraVez = true;
      pistonPrendido = 0;
      return;
    }

    digitalWrite(piston2, LOW);
    pistonPrendido = 2;
  }
  else if (pistonPrendido == 2 && estadoSwitch1 && estadoSwitch2) {
    digitalWrite(piston1, HIGH);
    delay(tp1);

    if (apagadoPendiente) {
      digitalWrite(piston1, LOW);
      apagadoPendiente = false;
      primeraVez = true;
      pistonPrendido = 0;
      return;
    }

    digitalWrite(piston1, LOW);
    pistonPrendido = 1;
  }
}
