
#include <stddef.h>
#include <Arduino.h>


/* getADCAverage
 * 
 * Takes ADC input and number of samples as argument, returns averaged value of 20 ADC samples
 */

int getADCAverage(int analogInput, byte samples);