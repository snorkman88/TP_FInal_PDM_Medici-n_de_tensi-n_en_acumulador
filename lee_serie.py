# El valor maximo que puede existir en bornes del acumulador es 5V
# tension = valor_adc * 5 / 256

from serial import Serial

s = Serial("/dev/ttyUSB0", 115200)
while True:
	promedio_lecturas = sum(s.read(5))/5
	print("el valor medio de la conversion ADC es: ", promedio_lecturas)
	tension = float(promedio_lecturas*5/255)
	print("el valor de tension es: ", format(tension, '.2f' ))
