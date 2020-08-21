#include "chip.h"
#include "adc_18xx_43xx.h"


void inicia_periferico(void);

void configura_pines(void);

void inicia_uart0(void);

void inicia_ADC(void);

void leer_adc(uint16_t *analogValue);

bool lee_boton(void);

void delay_ms (uint16_t ms);
