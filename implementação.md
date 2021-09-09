# Implementação
Com intuito de colocar em prática o que foi descrevido nas etapas anteriores do projeto, na presente etapa de implementação foi criada a maquete física, que servirá como uma base de operação para o projeto, além da explicação das tarefas encontradas no código final utilizado para manipular o arduino e os componentes eletrônicos à ele acoplados.

## Maquete
Durante a construção da maquete, foi-se utilizado uma folha de isopor de 5cm de grossura para servir como a base do projeto, uma folha de isopor 2,5cm de grossura para criar as paredes da casa, estilete para cortar o isopor, cola de isopor para colar as paredes e por último alfinetes com intuito de manter as paredes acopladas. O primeiro passo do projeto foi desenhar a planta baixa da casa no isopor 5cm para servir como esboço para a maquete, em seguida foi cortado as 4 paredes exteriores da casa, com suas devidas janelas e portas e por ultimo as paredes interiores da casa com suas devidas portas. A ordem em que as paredes foram coladas no isopor base foi a mesma em que foram cortadas. Em seguida veremos imagens representando a maquete com suas paredes exteriores coladas e na figura 2 a maquete completa.

Figura 1 - Maquete com as paredes exteriores
![Maquete 1/2](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/imagens/Maquete%20com%20as%20paredes%20exteriores.jpeg)


Figura 2 - Maquete completa
![Maquete Completa](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/imagens/Maquete%20finalizada2.jpeg)

### Instalação do hardware na maquete
A instalação do hardware na maquete ainda não foi realizada por falta dos jumpers necessários para alcançar a maquete.

## Código
Nas etapas anteriores, os códigos utilizados para testar os diversos componentes já foram criados, logo no momento só precisamos junta-los em um único programa, tendo em mente que a prática de subprogramas foi adotada durante o desenvolvimento dos códigos do projeto a integração dos códigos individuais em um único código se torna algo trivial. No programa final, foi-se utilizado o metódo de multitarefas que será exemplificado ao final deste texto, vale lembrar que os subprogramas criados serão atribuidos dentro da função loop, função cujo funcionamento também será explicada em breve. Abaixo segue o link para acesso do código completo, assim como a explicação de algumas de suas funções e tarefas.
* [Codigo completo utilizado no projeto](https://github.com/MarceloZam/Projeto-Integrador-2-IFSC/blob/main/codigo.ino)

### Iluminação
O controle da iluminação da maquete foi realizado utilizando 9 LED's conectados as suas respectivas teclas (1 a 9 no teclado númerico), caso um número seja pressionado, o LED correspondente acenderá, caso o mesmo número seja pressionado novamente o LED apagará. Todos os LED's podem ser acesos ao mesmo tempo. A tarefa que controla o comportamento da iluminação da residência é a seguinte:
~~~~C
void controle_sistema()
~~~~

### PIR
O controle do sensor PIR é bem simples, quando o sensor detecta movimento no jardim da casa, ele automaticamente acende o LED de número 9 intitulado no código como LED_Jardim, o LED só será desligado caso a presença não seja mais detectada. Caso o LED já esteja aceso, e uma presença seja detectada o LED continuará aceso, porém apagará quando a presença parar de ser detectada. A tarefa que controla o sensor PIR é a seguinte:
~~~~C
void Sensormov1(unsigned long tempo_atual)
~~~~

### Sensor MQ2
O sensor MQ2, tem a função de detectar fumaça e gás na residência, ele funciona da seguinte maneira, caso detecte um valor que esteja acima do limite estipulado pelo programador, o arduino enviará um sinal para o buzzer fazendo com que um alarme seja disparado. Com intuito de melhorar a visualização do código, foi estipulado uma regra para que o valor detectado pelo sensor MQ2 só seja disponibilizado para o usuário caso o mesmo notifique o programa utilizando a tecla 'F'. A tarefa que realiza o controle do sensor MQ2 é a seguinte:
~~~~C
void mq2(unsigned long tempo_atual)
~~~~

### Servomotor
O servomotor possui uma função bem simples no projeto, quando acionado fazer uma mudança de angulo equivalente a 90º positivos, assim 'abrindo' o portão, caso acionado novamente ele faz uma mudança de posição de 90º negativos, assim 'fechando' o portão. A tarefa que controla o servomorto é a seguinte:
~~~~C
void controle_sistema()
~~~~

### Loop
Com intuito de certificar-se que as tarefas serão analisadas de maneira continua foi-se utilizado a função loop () provida pelo próprio arduino. A função faz com que todos os subprogramas adicionados a ela, sejam "ativados" continuamente e com grande velocidade. A tarefa está dispónivel na seguinte parte do código:
~~~~C
void loop()
~~~~

