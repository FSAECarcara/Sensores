// Codigo MONITOR SERIAL
// https://www.embarcados.com.br/timers-do-atmega328-no-arduino/ (Mais informações sobre o timer)

#include <SPI.h>

int rotacao = 0, rpm1 = 0, repet = 0;                // Inicialização das variaveis (rotação com contador => ZERADO) (rpm1 que recebe rotação => ZERADO)

void setup(void){
  Serial.begin(9600);                     // Inicialização do monitor serial (9600 bits por segundo)
  attachInterrupt(1, rpm, FALLING);       // **Função de interrupção (Pino 3, função rpm, na borda de descida)

  //Inicializa timer1 
  noInterrupts();                         // Desabilita todas as interrupções

  // Controle do modo de operação do TIMER1
  TCCR1A = 0;                             // Registrador A (configura o timer para operação normal) [pinos OC1A e OC1B desconectados]
  TCCR1B = 0;                             // Registrador B (limpa registrador)
  TCNT1  = 0;                             // Registradores de armazenamento de contagem do timer.

  // Timer
  OCR1A = 0X3D09;                       // Carrega registrador de comparação: 16MHz/1024/1Hz = 15625 = 0X3D09
  //OCR1A = 15625;                          // ** Registradores para comparação de contagem com o TCNT1. 
                                          // Cont... A igualdade pode gerar uma interrupção ou gera uma saída de onda nos pinos OC1A ou OC1B.
  
  TCCR1B |= (1 << WGM12)|(1<<CS10)|(1 << CS12);                // MODO CTC interrupção por comparação //
  // **Configura prescaler para 1024: CS12 = 1 e CS10 = 1
  // NÃO USAR: TCNT1 = 0xC2F7; inicia timer com valor para que estouro ocorra em 1 segundo... 65536-(16MHz/1024/1Hz) = 49911 = 0xC2F7
  
  TIMSK1 |= (1 << OCIE1A);                // Habilita interrupção por igualdade de comparação
  // NÃO USAR: TIMSK1 |= (1 << TOIE1) habilita a interrupção do TIMER1
  
  interrupts();                           // Habilita todas as interrupções
}

ISR(TIMER1_COMPA_vect){                   // Interrupção por igualdade de comparação no TIMER1
 rpm1 = rotacao * (60/2); 
 rotacao = 0;
}

void loop(void){
  Serial.print("RPM: ");
 if(rpm1>0){
  Serial.println(rpm1);
 }else{
  Serial.println("OFF");
 } 
 delay(500);
}

void rpm(){                              // Função que contabiliza o RPM ("Ativação" por interrupção)
  rotacao++;
}
