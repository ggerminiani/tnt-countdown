#define IN1 8
#define IN2 9

#define FIM_DE_CURSO 6
#define REVERSO 5
#define RESET 4
#define BUZZER 3

bool liberado = false;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(FIM_DE_CURSO, INPUT_PULLUP);
  pinMode(REVERSO, INPUT_PULLUP);
  pinMode(RESET, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);

  iniciarCountdown();
}

void loop() {
  // Se o botão RESET for pressionado
  if (digitalRead(RESET) == LOW) {
    Serial.println("🔁 RESET acionado. Reiniciando countdown...");
    pararMotor();
    iniciarCountdown();
  }

  if (!liberado) return;

  bool fimDeCurso = digitalRead(FIM_DE_CURSO) == LOW;
  bool reverso = digitalRead(REVERSO) == LOW;

  if (fimDeCurso) {
    Serial.println("⏩ Girando sentido horário (fim de curso acionado)");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (reverso) {
    Serial.println("⏪ Girando sentido anti-horário (reverso acionado)");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else {
    pararMotor();
  }

  delay(100);
}

void pararMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void iniciarCountdown() {
  liberado = false;

  Serial.println("🔊 Iniciando contagem regressiva...");
  tone(BUZZER, 1000); delay(1000); noTone(BUZZER); delay(300);
  Serial.println("🔉 Apito inicial OK");

  int duracao = 500;
  int pausa = 500;

  for (int i = 0; i < 30; i++) {
    tone(BUZZER, 1200);
    delay(duracao);
    noTone(BUZZER);
    delay(pausa);
    duracao = max(50, duracao - 15);
    pausa = max(40, pausa - 15);
  }

  for (int i = 0; i < 15; i++) {
    tone(BUZZER, 1500);
    delay(70);
    noTone(BUZZER);
    delay(50);
  }

  Serial.println("✅ Countdown finalizado. Controle do motor liberado!");
  liberado = true;
}
