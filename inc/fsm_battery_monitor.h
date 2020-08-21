#include "perifericos.h"

uint8_t v_batt[5];

enum estados{
	MONITOREO,
	LECTURA,
	TRANSMISION
}estado_actual;

void inicializa_fsm(void);

void actualizar_fsm(void);
