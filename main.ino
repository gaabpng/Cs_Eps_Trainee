// NO TINKERCAD ESTÁ COMO ARDUINO UNO, MAS DEVE SER COMPILADO EM UM ARDUINO MEGA POR CONTA DO TAMANHO DOS HALLS INFRA VERMELHO

// #include "PinDefinitionsAndMore.h"

const int analogIn = A0;

int RawValue = 0;
double Voltage = 0;
double tempC = 0;

int TempoDoArCondicionado = 0;
int TempoDoAquecedor = 0;

void setup() {  
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // 5000mV = 5V
  tempC = (Voltage - 500) * 0.1; // 10mV = 1 grau celsius
  Serial.print("Temperatura em Graus Celsius = ");
  Serial.println(tempC, 1); // 1 casa decimal
  Serial.println();
  
  //controle Aquecedor
  if (tempC < 10) {
    TempoDoAquecedor++;
  } else {
    digitalWrite(2, LOW);
    TempoDoAquecedor = 0;
  }
  
  if (TempoDoAquecedor >= 120) {
    digitalWrite(2, HIGH);
  }

  if (TempoDoAquecedor == 360) {
    if (tempC < 10) {
      digitalWrite(2, HIGH);
      TempoDoAquecedor = 121;
    } else {
      digitalWrite(2, LOW);
      TempoDoAquecedor = 0;
    }
  }

  //controle Ar Condicionado
  if (tempC > 30) {
    TempoDoArCondicionado += 1;
  }

  if (TempoDoArCondicionado > 60) {
    const uint16_t rawData[] = {3064, 1624, 452, 1128, 452, 1124, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1128, 456, 1124, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1124, 456, 1124, 456, 360, 456, 1124, 456, 1124, 456, 360, 456, 360, 456, 1124, 452, 364, 456, 360, 456, 360, 452, 1128, 456, 360, 456, 360, 452, 360, 460, 360, 452, 364, 452, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 360, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 364, 452, 360, 456, 364, 452, 360, 456, 360, 452, 364, 452, 364, 452, 364, 456, 360, 452, 364, 452, 364, 456, 360, 452, 364, 456, 360, 452, 364, 452, 360, 452, 368, 452, 364, 452, 360, 456, 360, 452, 364, 452, 364, 452, 364, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 456, 360, 456, 356, 456, 336, 480, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 1124, 456, 360, 452, 364, 452, 1124, 456, 1128, 452, 360, 456, 4456, 3060, 1628, 452, 1124, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 360, 452, 1128, 456, 1124, 456, 360, 452, 1128, 452, 360, 456, 360, 456, 1124, 456, 1124, 456, 360, 452, 1128, 456, 1124, 452, 364, 452, 364, 452, 1124, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 1124, 456, 360, 456, 360, 452, 1128, 456, 360, 456, 360, 456, 1124, 452, 1128, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 1124, 456, 1124, 456, 360, 456, 1124, 452, 364, 456, 360, 456, 360, 456, 360, 452, 1128, 456, 1124, 452, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 364, 452, 360, 456, 360, 452, 364, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 456, 360, 452, 364, 456, 360, 452, 364, 452, 1128, 452, 360, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 1124, 456, 360, 456, 360, 456, 1124, 456, 360, 456, 1120, 460, 1124, 452};
    IrSender.sendRaw(rawData, sizeof(rawData) / sizeof(rawData[0]), NEC_KHZ);
    TempoDoArCondicionado = 0;
  }
  
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