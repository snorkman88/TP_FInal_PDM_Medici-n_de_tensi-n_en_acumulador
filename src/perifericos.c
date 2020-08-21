#include "perifericos.h"

/* Config ADC0*/
ADC_CLOCK_SETUP_T ADCSetup = {
   ADC_MAX_SAMPLE_RATE,   // ADC Sample rate:ADC_MAX_SAMPLE_RATE = 400KHz
   8,                    // ADC resolution: ADC_8BITS = 8
   0                      // ADC Burst Mode: (true or false)
};

const int TEC1[2] = {3, 12}; // Pulsador 1 corresponde a GPIO 3 bit 12


void inicia_periferico(void)
{
	Chip_SetupXtalClocking ();
	SystemCoreClockUpdate ();
	configura_pines();
	inicia_uart0();
	inicia_ADC();
}


void configura_pines(void)
{
	/*Configuracion de los pines para pulsador y ADC*/
	Chip_SCU_PinMuxSet(7, 4,  SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN);
	Chip_SCU_PinMuxSet(4, 1,  SCU_MODE_FUNC0 | SCU_MODE_INACT); //
	Chip_SCU_ADC_Channel_Config(0, 1);//Cconfigura UART0 y canal 1
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, TEC1[0], TEC1[1]); //Configuro el pin como entrada para el pulsador
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 2, 3);//Configuro el pin como entrada para el potenciometro
}


void inicia_uart0(void)
{
	/*Configuracion e inicializacion de la UART0*/
	Chip_SCU_PinMuxSet (2 , 0 , SCU_MODE_PULLDOWN | SCU_MODE_FUNC1 );
	Chip_SCU_PinMuxSet (2 , 1 , SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1 );
	Chip_UART_Init ( LPC_USART0 );
	Chip_UART_ConfigData ( LPC_USART0 , UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS );
	Chip_UART_SetBaud ( LPC_USART0 , 115200);
	Chip_UART_TXEnable ( LPC_USART0 );
	Chip_UART_SendBlocking ( LPC_USART0 , " UART CONFIG OK!\n \r" , 20);
}

void inicia_ADC(void)
{
	/*Configuracion e inicilizacion del ADC*/
	Chip_ADC_Init( LPC_ADC0, &ADCSetup );
    Chip_ADC_SetBurstCmd( LPC_ADC0, DISABLE ); //Deshabilita el modo rafaga
    Chip_ADC_SetSampleRate( LPC_ADC0, &ADCSetup, ADC_MAX_SAMPLE_RATE/2 );
    Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH1, DISABLE ); // Deshabilita canal 1
    Chip_ADC_Int_SetChannelCmd( LPC_ADC0, ADC_CH1, DISABLE );//Deshabilita interrupcion para el canal 1
}

void leer_adc(uint16_t *analogValue)
{
	uint8_t contador_lecturas=0;
	for(contador_lecturas=0; contador_lecturas<5; contador_lecturas++){
		Chip_ADC_EnableChannel(LPC_ADC0, ADC_CH1, ENABLE);
		Chip_ADC_SetStartMode(LPC_ADC0, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
		delay_ms(1000);
		Chip_ADC_ReadValue( LPC_ADC0, ADC_CH1, analogValue );
		Chip_ADC_EnableChannel( LPC_ADC0, ADC_CH1, DISABLE );
	}
}

bool lee_boton(void)
{
	return !Chip_GPIO_GetPinState(LPC_GPIO_PORT, TEC1[0], TEC1[1]);
}


void delay_ms (uint16_t ms)
{
	uint16_t delay;
	volatile uint32_t i;
	for (delay = ms; delay >0 ; delay--)
	{
		for (i=3500; i >0;i--){};
	}
}
