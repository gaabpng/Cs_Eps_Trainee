const int analogIn = A0;

int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;

void setup(){  
  Serial.begin(9600);
  pinMode(A1, INPUT);
}

void loop(){
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // 5000mV = 5V
  tempC = (Voltage-500) * 0.1; // 10mV = 1 grau celsius
  Serial.println("Temperatura em Graus Celsius = ");
  Serial.println(tempC,1); // 1 casa decimal
  Serial.println();

  delay(2000);
}