
int gasPin = A0;
int ledPin = 4;
int buzzerPin = 2;

int warningLevel = 15;
int dangerLevel = 24;

unsigned long lastRead = 0;
unsigned long lastBeep = 0;

bool buzzerState = false;
int currentMode = -1;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, );
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead < 500) {
    updateAlarm(now);
    return;
  }

  lastRead = now;

  int gasValue = analogRead(gasPin);
  int newMode;

  if (gasValue < warningLevel) {
    newMode = 0;
  } else if (gasValue < dangerLevel) {
    newMode = 1;
  } else {
    newMode = 2;
  }

  if (newMode != currentMode) {
    currentMode = newMode;

    Serial.print("Gas: ");
    Serial.print(gasValue);
    Serial.print(" | Status: ");

    if (currentMode == 0) Serial.println("NORMAL");
    if (currentMode == 1) Serial.println("WARNING");
    if (currentMode == 2) Serial.println("DANGER");
  }

  updateAlarm(now);
}

void updateAlarm(unsigned long now) {
  if (currentMode == 0 || currentMode == -1) {
    digitalWrite(ledPin, 0);
    noTone(buzzerPin);
    buzzerState = false;
    return;
  }

  unsigned long interval =
      (currentMode == 1) ? 800 : 200;

  if (now - lastBeep >= interval) {
    lastBeep = now;
    buzzerState = !buzzerState;

   digital
    Write(
      ledPin,
      currentMode == 1 ? buzzerState : HIGH
    );

    if (buzzerState) {
      tone(buzzerPin, currentMode == 1 ? 900 : 1500);
    } else {
      noTone(buzzerPin);
    }
  }
}
