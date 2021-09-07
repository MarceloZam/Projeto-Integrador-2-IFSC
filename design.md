# Design do projeto
Com o objetivo de implementar as funções anteriormente definidas na etapa de concepção do projeto, segue a lista de componentes que será necessária para alcançar os objetivos definidos, assim como uma maquete eletrônica que auxilia na demonstração do design eletrônico do projeto.
## Componentes utilizados

Componentes   | Quantidade
--------- | ------
LED  | 9
Resistores 330 ohms | 9
Servomotor (Micro Servo SG92R 9g)| 1
Módulo Buzzer 5V Passivo | 1
Sensor de Gás e fumaça MQ2 | 1
Sensor de Movimento PIR (HC-SR501)| 1
Arduino Mega 2560 | 1
Protoboard | 1

## Maquete Eletrônica

Figura 1 - Maquete eletrônica do projeto
![Maquete eletrônica](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/imagens/Maquete%20eletr%C3%B4nica%20att.png)
OBS: Diferente da maquete eletrônica, o buzzer utilizado nesse projeto possui 3 pinos, logo a entrada DO do sensor de gás e fumaça MQ2 é utilizada para representar a ligação da saída digital do buzzer.

## Teste dos componentes

### LED's e PIR
Figura 2 - Sistema de iluminação
![Sistema de iluminação](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/imagens/Sistema%20de%20ilumina%C3%A7%C3%A3o.png)

~~~~C
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
~~~~

### MQ2 e Buzzer
Figura 3 - Controle de fumaça e gás
![Controle de fumaça e gás](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/imagens/Controle%20de%20g%C3%A1s%20e%20fuma%C3%A7a.png)

~~~~C
void controle_sistema()
{
  if (Serial.available() > 0)
  {
    dados = Serial.read();
    //Serial.print("Entrada recebida: ");
    Serial.println(dados);
    switch (dados)
    { 
     case 'F':
       MQ2_VALUE = analogRead(MQ2);
       Serial.print("Pin A5: ");
       Serial.println(MQ2_VALUE);
       break;
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
~~~~
### Servomotor
Figura 4 - Controle do servomotor
![Controle do servomotor](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/imagens/Controle%20do%20servomotor.png)

~~~~C
//Inclusão da(s) biblioteca(s)
#include <Servo.h>
int Posicao;
Servo s;

void setup()
{
  s.attach(Servomotor); // Associa o pino digital com o servomotor
  s.write(30); // Coloca o servo motorna posição inicial de 30 graus.
}

void controle_sistema()
{
  if (Serial.available() > 0)
  {
    dados = Serial.read();
    //Serial.print("Entrada recebida: ");
    Serial.println(dados);
    switch (dados)
    {      
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
~~~~
