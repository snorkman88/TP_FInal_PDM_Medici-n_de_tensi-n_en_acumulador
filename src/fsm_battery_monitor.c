#include "fsm_battery_monitor.h"

uint8_t contador_lecturas=0;
void inicializa_fsm(void)
{
	inicia_periferico();
}

void actualizar_fsm(void)
{
	switch(estado_actual){
	case MONITOREO:
		if (lee_boton())
			estado_actual = LECTURA;
		break;
	case LECTURA:
		leer_adc(&v_batt[0]);
		estado_actual = TRANSMISION;
		break;

	case TRANSMISION:

		for(contador_lecturas=0; contador_lecturas<5; contador_lecturas++){
		Chip_UART_SendBlocking ( LPC_USART0 , &v_batt, 1);
		}
		estado_actual = MONITOREO;
		break;
	}
}
