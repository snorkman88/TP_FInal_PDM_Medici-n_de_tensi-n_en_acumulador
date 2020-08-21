#include "fsm_battery_monitor.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;


/**
 * @brief	main routine
 * @return	Function should not exit.
 */
int main(void)
{
	inicializa_fsm();
	while (1)
	{
		actualizar_fsm();
		delay_ms(1000);
	}
	return 0;
}
