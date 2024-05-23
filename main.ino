// NO TINKERCAD ESTÁ COMO ARDUINO UNO, MAS DEVE SER COMPILADO EM UM ARDUINO MEGA POR CONTA DO TAMANHO DOS HALLS INFRA VERMELHO

// inclusão do arquivo com o nome entre aspas que está no repositório
// o arquivo incluído é uma biblioteca para controle de infra-vermelho

#include "PinDefinitionsAndMore.h"

// definição dos pinos e declaração das variáveis
const int analogIn = A0;

int RawValue = 0;
double Voltage = 0;
double tempC = 0;

int TempoDoArCondicionado = 0;
int TempoDoAquecedor = 0;

// void setup é uma função executada por padrão no arduino que faz as primeiras considerações do código, que 
//no caso é definir o pino 2 (responsável pelo relé) como desligado por padrão
void setup() {  
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

// void loop é outra função executada por padrão, em que é executado enquanto o arduino estiver ligado
void loop() {
  // conversão do valor de entrada do sensor para uma temperatura compreensível até a linha 30
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // 5000mV = 5V
  tempC = (Voltage - 500) * 0.1; // 10mV = 1 grau celsius

  Serial.print("Temperatura em Graus Celsius = ");
  Serial.println(tempC, 1); // 1 casa decimal
  Serial.println();
  
  //controle Aquecedor
  // se a temperatura é menor que 10, acrescenta-se 1 a variável 
  if (tempC < 10) {
    TempoDoAquecedor++;
  } else { // senão, reinicia o contador
    digitalWrite(2, LOW);
    TempoDoAquecedor = 0;
  }
  
  // se o contador chegar a 120, o relé é ativado e o contador recebe o valor 360
  if (TempoDoAquecedor == 120) {
    digitalWrite(2, HIGH);
    TempoDoAquecedor == 360;
  }

  // se o contador é maior que 120, faz-se uma contagem regressiva
  if (TempoDoAquecedor > 120) {
    TempoDoAquecedor += 1;
  }
  // se o valor for 121, faz-se uma verificação de temperatura novamente, se ainda for abaixo do esperado, reinicia a contagem regressiva
  if (TempoDoAquecedor == 121) {
    if (tempC < 10) {
      digitalWrite(2, HIGH);
      TempoDoAquecedor = 360;
    } else { //se for acima do esperado, é atribuido o valor 0 ao contador
      digitalWrite(2, LOW);
      TempoDoAquecedor = 0;
    }
  }

  //controle Ar Condicionado
  // inicia o contador se estiver quente
  if (tempC > 30) {
    TempoDoArCondicionado += 1;
  }
  // se o contador chegar a 1 minuto, liga o ar condicionado
  if (TempoDoArCondicionado > 60) {
    const uint16_t rawData[] = {3064, 1624, 452, 1128, 452, 1124, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1128, 456, 1124, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1124, 456, 1124, 456, 360, 456, 1124, 456, 1124, 456, 360, 456, 360, 456, 1124, 452, 364, 456, 360, 456, 360, 452, 1128, 456, 360, 456, 360, 452, 360, 460, 360, 452, 364, 452, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 360, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 364, 452, 360, 456, 364, 452, 360, 456, 360, 452, 364, 452, 364, 452, 364, 456, 360, 452, 364, 452, 364, 456, 360, 452, 364, 456, 360, 452, 364, 452, 360, 452, 368, 452, 364, 452, 360, 456, 360, 452, 364, 452, 364, 452, 364, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 456, 360, 456, 356, 456, 336, 480, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1124, 456, 1128, 452, 360, 456, 4456, 3060, 1628, 452, 1124, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 360, 452, 1128, 456, 1124, 456, 360, 452, 1128, 452, 360, 456, 360, 456, 1124, 456, 1124, 456, 360, 452, 1128, 456, 1124, 452, 364, 452, 364, 452, 1124, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 1124, 456, 360, 456, 360, 452, 1128, 456, 360, 456, 360, 456, 1124, 452, 1128, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 1124, 456, 1124, 456, 360, 456, 1124, 452, 364, 456, 360, 456, 360, 456, 360, 452, 1128, 456, 1124, 452, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 452, 364, 452, 1128, 452, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 1124, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 1120, 460, 1124, 452};
    IrSender.sendRaw(rawData, sizeof(rawData) / sizeof(rawData[0]), NEC_KHZ);
    TempoDoArCondicionado = 0;
  }
  
  // se esfriar, desliga o ar-condicionado
  if (TempoDoArCondicionado != 0 && tempC < 30) {
    const uint16_t rawData[] = {3064, 1620, 456, 1124, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1124, 460, 1124, 452, 360, 456, 1124, 456, 360, 456, 364, 452, 1124, 456, 1124, 456, 360, 452, 1128, 456, 1124, 452, 364, 452, 364, 456, 1124, 452, 360, 460, 356, 460, 356, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 360, 460, 360, 456, 356, 456, 360, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 356, 456, 364, 452, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 452, 360, 456, 364, 456, 356, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 456, 360, 452, 364, 452, 364, 452, 360, 456, 360, 456, 364, 452, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 452, 364, 452, 364, 456, 356, 456, 364, 456, 1120, 456, 360, 456, 1124, 456, 360, 456, 360, 456, 1124, 456, 1124, 456, 360, 456, 3972, 3088, 1596, 484, 1096, 480, 1100, 480, 336, 480, 336, 452, 364, 480, 1100, 480, 336, 480, 336, 480, 1096, 484, 1096, 484, 332, 480, 1100, 480, 336, 480, 336, 480, 1100, 480, 1100, 480, 336, 480, 1096, 480, 1100, 480, 336, 480, 336, 484, 1096, 480, 336, 480, 336, 480, 1100, 480, 336, 480, 336, 480, 332, 484, 332, 484, 332, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 484, 332, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 476, 1100, 480, 336, 484, 332, 480, 1100, 452, 1128, 480, 336, 480, 336, 476, 340, 480, 336, 480, 332, 484, 332, 484, 1096, 484, 1096, 480, 336, 480, 1100, 480, 336, 480, 336, 480, 336, 452, 364, 480, 1100, 476, 1104, 480, 336, 480, 336, 476, 340, 476, 336, 480, 336, 484, 332, 480, 336, 456, 360, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 452, 364, 480, 336, 476, 340, 480, 332, 484, 336, 476, 336, 480, 336, 480, 336, 480, 336, 480, 336, 480, 336, 452, 364, 480, 336, 476, 1104, 452, 364, 452, 364, 452, 364, 452, 1124, 456, 360, 452, 1128, 452, 1128, 452, 1124, 456, 360, 456, 364, 452, 1124, 452, 1128, 452};
    IrSender.sendRaw(rawData, sizeof(rawData) / sizeof(rawData[0]), NEC_KHZ); // Note the approach used to automatically calculate the size of the array.
  }

  //debug
  Serial.println("TempoDoArCondicionado: ");
  Serial.println(TempoDoArCondicionado);
  Serial.println();
  Serial.println("TempoDoAquecedor: ");
  Serial.println(TempoDoAquecedor);
  delay(1000);
}
