#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600UL 
#define BRC ((F_CPU)/(BAUD*16UL)-1)  

void usartInit();
void send( unsigned char data);
void putstring(char* StringPtr);

char string[] = "hello world!";
int main(){
usartInit();
while(1){
putstring(string);
_delay_ms(1000);
}
}

void usartInit(){
UBRR0H = (uint8_t)(BRC >> 8);
UBRR0L = (uint8_t)(BRC);
UCSR0B = (1 << TXEN0) | (1 << RXEN0); 
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}

void putstring(char* StringPtr){
while(*StringPtr != 0x00){
send(*StringPtr);
StringPtr++;
}
}

void send(unsigned char data){
while(!(UCSR0A & (1<<UDRE0)));
UDR0 = data;
}

