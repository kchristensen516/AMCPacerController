
#include <stddef.h>
#include <Arduino.h>
#include "amc_adc.h"

/* getADCAverage
 * 
 * Takes ADC input and number of samples as argument, returns averaged value of 20 ADC samples
 */
int getADCAverage(int analogInput, byte samples)
{
  unsigned long average = 0;
  for(byte i=0;i<samples;i++)
    average += analogRead(analogInput);
  average = average/samples;
  
  #ifdef DEBUG_MESSAGES
    SerialUSB.print("Average ADC Reading (");
    SerialUSB.print(samples);
    SerialUSB.print(" samples): ");
    SerialUSB.print((int) average);
    SerialUSB.print("\n\n");
  #endif
  
  return (int) average;
}