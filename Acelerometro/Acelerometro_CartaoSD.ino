#include <Wire.h>
#include <SFE_MMA8452Q.h>
MMA8452Q acelerometro(0x1C);
#include <SdFat.h>
SdFat sdCard;
SdFile meuArquivo;
const int chipSelect = 4;
int botao = 2;
bool estadoLed = 0;
void setup()
{
pinMode(botao, INPUT);
Serial.begin(57600);
acelerometro.init();
if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
// Abre o arquivo LER_ACC.TXT
if (!meuArquivo.open("ler_acc.txt", O_RDWR | O_CREAT | O_AT_END))
{
sdCard.errorHalt("Erro na abertura do arquivo LER_acc.TXT!");
}}
void loop()
{
if (acelerometro.available())
{
//Efetua a leitura dos dados do sensor
acelerometro.read();
//acelerometro.read() atualiza dois grupos de variaveis:
//* int x, y, e z armazena o valor de 12 bits lido do
//acelerometro
// * float cx, cy, e cz armazena o calculo da aceleracao
//dos valores de 12 bits. Essas variaveis estao em
//unidades de "g"
//Mostra as coordenadas lidas do sensor
printCalculatedAccels();
meuArquivo.println();
Serial.println();
}
}
void printAccels()
{
Serial.print(acelerometro.x, 3);
Serial.print("t");
Serial.print(acelerometro.y, 3);
Serial.print("t");
Serial.print(acelerometro.z, 3);
Serial.print("t");
}
void printCalculatedAccels()
{
Serial.print(acelerometro.cx, 3);
Serial.print("|\t");
Serial.print(acelerometro.cy, 3);
Serial.print("|\t");
Serial.print(acelerometro.cz, 3);
Serial.print("\t");
meuArquivo.print(acelerometro.cx, 3);
meuArquivo.print("|\t");
meuArquivo.print(acelerometro.cy, 3);
meuArquivo.print("|\t");
meuArquivo.print(acelerometro.cz, 3);
meuArquivo.print("\t");
if (digitalRead(botao) == 1){
// Interrompe o processo e fecha o arquivo
Serial.println("Processo de gravacao interrompido. Retire o SD!");
meuArquivo.close();
while (1) {}
}
delay(20);
}
 
