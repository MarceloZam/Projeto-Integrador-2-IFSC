//Neste arquivo está presente o código que foi utilizado para fazer o controle do projeto de domótica da residência criada durante a concepção deste projeto.
//Cabe lembrar que algumas partes do código podem vir a serem alteradas no futuro.

//Inclusão da(s) biblioteca(s)
#include <Servo.h>

//Atribuição dos pinos do arduino mega
#define LED_Quarto1 22
#define LED_Quarto2 23
#define LED_Banheiro 24
#define LED_Corredor 25
#define LED_Sala_de_Estar 26
#define LED_Cozinha 27
#define LED_Area_de_servico 28
#define LED_Garagem 29
#define LED_Jardim 30
#define MQ2 A5
#define BUZZER 51
#define Servomotor 52
#define Sensormov 53

//Declaração das variáveis
const unsigned long periodo_tarefa_1 = 1000;
unsigned long tempo_tarefa_1 = millis();
const unsigned long periodo_tarefa_2 = 2000;
unsigned long tempo_tarefa_2 = millis();
char dados;
int Estado_PIR = LOW; //Coloca o sensor de presença do seu estado desligado
int PIR_VALUE; //
int Limite_MQ2 = 400;
int MQ2_VALUE;
Servo s;

//Inicialização dos pinos

void setup()
{

  Serial.begin(9600);
  while (!Serial);
  pinMode(LED_Quarto1, OUTPUT);
  pinMode(LED_Quarto2, OUTPUT);
  pinMode(LED_Banheiro, OUTPUT);
  pinMode(LED_Corredor, OUTPUT);
  pinMode(LED_Sala_de_Estar, OUTPUT);
  pinMode(LED_Cozinha, OUTPUT);
  pinMode(LED_Area_de_servico, OUTPUT);
  pinMode(LED_Garagem, OUTPUT);
  pinMode(LED_Jardim, OUTPUT);
  pinMode(Sensormov, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MQ2, INPUT);
  s.attach(Servomotor); // Associa o pino digital com o servomotor
  s.write(30); // Coloca o servo motorna posição inicial de 30 graus.
  Serial.begin(9600);
}

//Controle do sistema de domótica

void controle_sistema()
{
  if (Serial.available() > 0)
  {
    dados = Serial.read();
    //Serial.print("Entrada recebida: ");
    Serial.println(dados);
    switch (dados)
    {
      case '1':
        digitalWrite(LED_Quarto1, !digitalRead(LED_Quarto1));
        Serial.print("O estado do led 1 foi alterado.\n");
        break;
      case '2':
        digitalWrite(LED_Quarto2, !digitalRead(LED_Quarto2));
        Serial.print("O estado do led 2 foi alterado.\n");
        break;
      case '3':
        digitalWrite(LED_Banheiro, !digitalRead(LED_Banheiro));
        Serial.print("O estado do led 3 foi alterado.\n");
        break;
      case '4':
        digitalWrite(LED_Corredor, !digitalRead(LED_Corredor));
        Serial.print("O estado do led 4 foi alterado.\n");
        break;
      case '5':
        digitalWrite(LED_Sala_de_Estar, !digitalRead(LED_Sala_de_Estar));
        Serial.print("O estado do led 5 foi alterado.\n");
        break;
      case '6':
        digitalWrite(LED_Cozinha, !digitalRead(LED_Cozinha));
        Serial.print("O estado do led 6 foi alterado.\n");
        break;
      case '7':
        digitalWrite(LED_Area_de_servico, !digitalRead(LED_Area_de_servico));
        Serial.print("O estado do led 7 foi alterado.\n");
        break;
      case '8':
        digitalWrite(LED_Garagem, !digitalRead(LED_Garagem));
        Serial.print("O estado do led 8 foi alterado.\n");
        break;
      case '9':
        digitalWrite(LED_Jardim, !digitalRead(LED_Jardim));
        Serial.print("O estado do led 9 foi alterado.\n");
        break;
      case 'F':
        MQ2_VALUE = analogRead(MQ2);
        Serial.print("Pin A5: ");
        Serial.println(MQ2_VALUE);
        break;
      case 'g':
        Serial.println("Abrindo o portão");
        s.write(120);
        break;
      case 'G':
        Serial.println("Fechando o portão");
        s.write(27);
        break;
    }
  }
}

void Sensormov1(unsigned long tempo_atual) //Sensor de movimento (PIR)
{
  if (tempo_atual - tempo_tarefa_1 > periodo_tarefa_1)
  {
    tempo_tarefa_1 = tempo_atual;
    PIR_VALUE = digitalRead(Sensormov);
    if (PIR_VALUE == HIGH)
    {
      digitalWrite(LED_Jardim, HIGH);
      if (Estado_PIR == LOW)
        Serial.println("Movimento detectado!");
      Estado_PIR = HIGH;
    }
    else
    {
      digitalWrite(LED_Jardim, LOW);
      if (Estado_PIR == HIGH)
        Serial.println("Fim do movimento!");
      Estado_PIR = LOW;
    }
  }
}

void mq2(unsigned long tempo_atual) //Sensor de gás (MQ2+Buzzer)
{
  if (tempo_atual - tempo_tarefa_2 > periodo_tarefa_2)
  {
    tempo_tarefa_2 = tempo_atual;
    int MQ2_VALUE = analogRead(MQ2);
    if (MQ2_VALUE > Limite_MQ2)
      digitalWrite(BUZZER, LOW);
    else
      digitalWrite(BUZZER, HIGH);
  }
}

void loop() //Loop das funções
{
  unsigned long meu_tempo_atual = millis();
  controle_sistema();
  Sensormov1(meu_tempo_atual);
  mq2(meu_tempo_atual);
}
