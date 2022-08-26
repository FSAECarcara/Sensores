
#include <Wire.h>
#include <SFE_MMA8452Q.h>
MMA8452Q acelerometro(0x1C);

void setup()
{
  Serial.begin(57600); 
  acelerometro.init();
}

void loop()
{
  
  if (acelerometro.available())
  {
    
    acelerometro.read();
  printCalculatedAccels();
  
    
   Serial.println();
  }
}

void printAccels()
{
  Serial.print(acelerometro.x, 3); 
  Serial.print(acelerometro.y, 3);
  Serial.print(acelerometro.z, 3);

}
void printCalculatedAccels()
{ 
  Serial.print(acelerometro.cx, 3);
  Serial.print("|\t");
  Serial.print(acelerometro.cy, 3);
  Serial.print("|\t");
  Serial.print(acelerometro.cz, 3);
  Serial.print("\t");
}

 
