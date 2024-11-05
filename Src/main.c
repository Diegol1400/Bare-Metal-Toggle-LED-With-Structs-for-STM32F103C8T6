//LED CONNECTED
//PORT C 0x4001 1000
//PIN 13
#include <stdint.h>

#define PERIPH_BASE  		(0x40000000UL) // Definición de la dirección base para los periféricos

#define APB2PERIPH_OFFSET 	(0x00011000UL) // Definición del offset para el bus APB2 (Advanced Peripheral Bus 2)
#define APB2PERIPH_BASE 	(PERIPH_BASE + APB2PERIPH_OFFSET) //0x4001 1000 Cálculo de la dirección base para los periféricos en el bus APB2

#define GPIOC_OFFSET 		(0x0000UL)	   // Offset para el puerto GPIOC
#define GPIOC_BASE 			(APB2PERIPH_BASE + GPIOC_OFFSET) //0x4001 1000 Cálculo de la dirección base para GPIOC

#define RCC_OFFSET 			(0x00010000UL) // Offset para el registro RCC (Reset and Clock Control)
#define RCC_BASE    		(APB2PERIPH_BASE + RCC_OFFSET)  //0x4002 1000 Cálculo de la dirección base para el registro RCC

#define GPIOCEN 			(1U<<4)  //0000 0000 0000 0000 0000 0000 0001 0000 Máscara para habilitar el reloj de GPIOC (Bit 4 en el registro RCC)

#define PIN_13				(1U<<13) // Máscara para el pin 13 de GPIOC (Bit 13)
#define LED_PIN				PIN_13

typedef struct
{
	volatile uint32_t DUMMY[6];
	volatile uint32_t APB2ENR;	 //Peripheral clock enable register (RCC_APB2ENR) Address: 0x18

}RCC_TypeDef;

typedef struct
{
	volatile uint32_t DUMMY_1;
	volatile uint32_t CRH;	   //Port configuration register high Offset Addres: 0x04
	volatile uint32_t DUMMY_2;
	volatile uint32_t ODR;	   //Port output data register		  Offset Addres: 0x0C

}GPIOC_TypeDef;

#define RCC 	((RCC_TypeDef*) RCC_BASE)
#define GPIOC	((GPIOC_TypeDef*) GPIOC_BASE)


int main(void){

	//Habilitar el reloj para GPIOC

	RCC->APB2ENR |= GPIOCEN;

	// Configurar el pin 13 de GPIOC como salida (modo general de salida)

	GPIOC->CRH   |= (1U<<21);

	while(1){
		 // Establecer el pin 13 en bajo para encender el LED
		 //GPIOC_OD_R &=~ LED_PIN;

		 // Si quieres alternar el estado del LED
		 GPIOC->ODR ^= LED_PIN;

		 // La línea siguiente es para un retraso
		 for(int i = 0; i<400000; i++){}

	}
}


