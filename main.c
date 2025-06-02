#define F_CPU   16000000UL
#include <util/delay.h>
#include <avr/io.h>

// Definições simbólicas para os pinos (PORTB)
#define Bt   PB0   // Botão - entrada (pino digital 8)
#define Vm   PB1   // LED vermelho - saída (pino digital 9)
#define Am   PB2   // LED amarelo - saída (pino digital 10)
#define Vd   PB3   // LED verde - saída (pino digital 11)
#define Vmp  PB4   // LED verde piscante - saída (pino digital 12)
#define Vdp  PB5   // LED vermelho piscante - saída (pino digital 13)


void semaforo_init(void)
{
    // Bt como entrada (PB0)
    DDRB &= ~(1 << Bt);    // Limpa bit → entrada
    PORTB |= (1 << Bt);    // Ativa pull-up interno (opcional)

	// Saídas: PB1 a PB5
	DDRB |= (1 << Vm) | (1 << Am) | (1 << Vd) | (1 << Vdp) | (1 << Vmp);
}

void amarelo()
{
	PORTB &= ~((1 << Vm) | (1 << Vd) | (1 << Vdp));
	PORTB |= ((1 << Am) | (1 << Vmp));
}

void vermelho()
{
	PORTB &= ~((1 << Am) | ( 1<< Vd) | (1 << Vmp));
	PORTB |= ((1 << Vm) | (1 <<Vdp));
}

void verde()
{
	PORTB &= ~((1 << Am) | ( 1<< Vm) | (1 << Vdp));
	PORTB |= ((1 << Vd) | (1 <<Vmp));
}

void pisca_vmp()
{
	PORTB &= ~(1 << Vdp);
	PORTB ^= (1 << Vmp);
}

int main (void)
{
	unsigned int c = 0;
	semaforo_init();
	
	while ( 1 )
	{	
		if (c < 3000)
		{
			amarelo();
			
		}
		else if (c < 15000)
		{
			vermelho();
			
		}
		else if (c < 18000)
		{
			if( (c % 500) == 0)
			{
				pisca_vmp();
			
			}
		}
		else if (c < 60000)
		{
			verde();
			
			if(c < 50000 && ( !(PINB & (1 << Bt))))
			{
				c = 50000;
			}
		
		}
		else
		{
			c = 0;  // Reinicia o ciclo
		}
		
		_delay_ms(1);
		c++;
		
	}
}