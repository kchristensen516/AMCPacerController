/*
 *	fuelLevelGauge.c
 * 	
 *	Driver to set fuel gauge based on measured fuel level.
 */

#include "board.h"
#include "fuelLevelGauge.h"
#include "fuelLevelMapping.h"
#include "amc_adc.h"


/* fuelLevelSweep
 * 
 * Sweeps fuel gauge output from 0%-100% and back to 0%.
 */
void fuelLevelSweep(int delay_ms)
{
    byte fl;
    for(fl = 0; fl < 200; fl++)
    {
      if(!setFuelGaugeOutput(fl))
        SerialUSB.print("Error: Fuel level out of range\n\n");
      #ifdef DEBUG_MESSAGES
        SerialUSB.print("Spoofed Fuel Level: ");
        SerialUSB.print(fl);
        SerialUSB.print("\n\n");
      #endif
      delay(delay_ms);      
    }
    for(fl = 200; fl > 0; fl--)
    {
      if(!setFuelGaugeOutput(fl))
        SerialUSB.print("Error: Fuel level out of range\n\n");
      #ifdef DEBUG_MESSAGES
        SerialUSB.print("Spoofed Fuel Level: ");
        SerialUSB.print(fl);
        SerialUSB.print("\n\n");
      #endif
      delay(delay_ms);
    }
}


/* getFuelLevelPercentage
 * 
 * Takes ADC value as argument, returns fuel level percentage
 * Returns 255 (error) if ADC value is out of range.
 */
byte getFuelLevelPercentage(int adcValue)
{
  if(adcValue > 4095)
    return 255;
  #ifdef DEBUG_MESSAGES
    SerialUSB.print("Measured fuel level: ");
    SerialUSB.print((long) gFuelLevelMapping[adcValue]/2);
    SerialUSB.print("%\n\n");
  #endif
  return gFuelLevelMapping[adcValue];
}


/*
 * setFuelLevelOutput
 * 
 * Takes fuel level percentage as input, sets fuel gauge output resistors
 * based on fuel level input.
 * fuelLevelPercentage: 0-200 = VALID, 0.05% step
 * 
 * Returns false if fuel level input is out of range
 */
bool setFuelGaugeOutput(byte fuelLevelPercentage)
{
  int graphLevel = 0;

  if(fuelLevelPercentage > 200)
    graphLevel = 0xFF;
  else
    graphLevel = (fuelLevelPercentage / 17); // 12 segments for 200 values --> ~17 values per segment

  switch(graphLevel)
  {
    case 0:
      digitalWrite(FUEL_LED_A_GN, 0);
      digitalWrite(FUEL_LED_A_RD, 1);
      digitalWrite(FUEL_LED_B_GN, 0);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 0);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 0);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 0);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 0);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 1:
      digitalWrite(FUEL_LED_A_GN, 0);
      digitalWrite(FUEL_LED_A_RD, 1);
      digitalWrite(FUEL_LED_B_GN, 0);
      digitalWrite(FUEL_LED_B_RD, 1);
      digitalWrite(FUEL_LED_C_GN, 0);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 0);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 0);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 0);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 2:
      digitalWrite(FUEL_LED_A_GN, 0);
      digitalWrite(FUEL_LED_A_RD, 1);
      digitalWrite(FUEL_LED_B_GN, 0);
      digitalWrite(FUEL_LED_B_RD, 1);
      digitalWrite(FUEL_LED_C_GN, 0);
      digitalWrite(FUEL_LED_C_RD, 1);
      digitalWrite(FUEL_LED_D_GN, 0);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 0);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 0);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break; 
    case 3:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 0);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 0);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 4:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 0);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 5:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 6:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 1);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 7:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 1);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 1);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 8:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 1);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 1);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 1);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 9:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 1);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 1);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 1);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 1);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 10:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 1);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 1);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 1);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 1);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 1);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    case 11:
      digitalWrite(FUEL_LED_A_GN, 1);
      digitalWrite(FUEL_LED_A_RD, 0);
      digitalWrite(FUEL_LED_B_GN, 1);
      digitalWrite(FUEL_LED_B_RD, 0);
      digitalWrite(FUEL_LED_C_GN, 1);
      digitalWrite(FUEL_LED_C_RD, 0);
      digitalWrite(FUEL_LED_D_GN, 1);
      digitalWrite(FUEL_LED_D_RD, 0);
      digitalWrite(FUEL_LED_E_GN, 1);
      digitalWrite(FUEL_LED_E_RD, 0);
      digitalWrite(FUEL_LED_F_GN, 1);
      digitalWrite(FUEL_LED_F_RD, 0);
      digitalWrite(FUEL_LED_G_GN, 1);
      digitalWrite(FUEL_LED_G_RD, 0);
      digitalWrite(FUEL_LED_H_GN, 1);
      digitalWrite(FUEL_LED_H_RD, 0);
      digitalWrite(FUEL_LED_I_GN, 1);
      digitalWrite(FUEL_LED_I_RD, 0);
      digitalWrite(FUEL_LED_J_GN, 1);
      digitalWrite(FUEL_LED_J_RD, 0);
      digitalWrite(FUEL_LED_K_GN, 1);
      digitalWrite(FUEL_LED_K_RD, 0);
      digitalWrite(FUEL_LED_L_GN, 1);
      digitalWrite(FUEL_LED_L_RD, 0);
      break;
    default: // Invalid value
      digitalWrite(FUEL_LED_A_GN, 0);
      digitalWrite(FUEL_LED_A_RD, 1);
      digitalWrite(FUEL_LED_B_GN, 0);
      digitalWrite(FUEL_LED_B_RD, 1);
      digitalWrite(FUEL_LED_C_GN, 0);
      digitalWrite(FUEL_LED_C_RD, 1);
      digitalWrite(FUEL_LED_D_GN, 0);
      digitalWrite(FUEL_LED_D_RD, 1);
      digitalWrite(FUEL_LED_E_GN, 0);
      digitalWrite(FUEL_LED_E_RD, 1);
      digitalWrite(FUEL_LED_F_GN, 0);
      digitalWrite(FUEL_LED_F_RD, 1);
      digitalWrite(FUEL_LED_G_GN, 0);
      digitalWrite(FUEL_LED_G_RD, 1);
      digitalWrite(FUEL_LED_H_GN, 0);
      digitalWrite(FUEL_LED_H_RD, 1);
      digitalWrite(FUEL_LED_I_GN, 0);
      digitalWrite(FUEL_LED_I_RD, 1);
      digitalWrite(FUEL_LED_J_GN, 0);
      digitalWrite(FUEL_LED_J_RD, 1);
      digitalWrite(FUEL_LED_K_GN, 0);
      digitalWrite(FUEL_LED_K_RD, 1);
      digitalWrite(FUEL_LED_L_GN, 0);
      digitalWrite(FUEL_LED_L_RD, 1);
      return false;  
  }

  return true; //success
}


/*
 *  initFuelLevelGauge 
 * 
 *  Initialize fuel level gauge
 * 
 */
void initFuelLevelGauge(void)
{
    // Initialize digital outputs
    pinMode(FUEL_LED_A_GN, OUTPUT);
    pinMode(FUEL_LED_A_RD, OUTPUT);
    pinMode(FUEL_LED_B_GN, OUTPUT);
    pinMode(FUEL_LED_B_RD, OUTPUT);
    pinMode(FUEL_LED_C_GN, OUTPUT);
    pinMode(FUEL_LED_C_RD, OUTPUT);
    pinMode(FUEL_LED_D_GN, OUTPUT);
    pinMode(FUEL_LED_D_RD, OUTPUT);
    pinMode(FUEL_LED_E_GN, OUTPUT);
    pinMode(FUEL_LED_E_RD, OUTPUT);
    pinMode(FUEL_LED_F_GN, OUTPUT);
    pinMode(FUEL_LED_F_RD, OUTPUT);
    pinMode(FUEL_LED_G_GN, OUTPUT);
    pinMode(FUEL_LED_G_RD, OUTPUT);
    pinMode(FUEL_LED_H_GN, OUTPUT);
    pinMode(FUEL_LED_H_RD, OUTPUT);
    pinMode(FUEL_LED_I_GN, OUTPUT);
    pinMode(FUEL_LED_I_RD, OUTPUT);
    pinMode(FUEL_LED_J_GN, OUTPUT);
    pinMode(FUEL_LED_J_RD, OUTPUT);
    pinMode(FUEL_LED_K_GN, OUTPUT);
    pinMode(FUEL_LED_K_RD, OUTPUT);
    pinMode(FUEL_LED_L_GN, OUTPUT);
    pinMode(FUEL_LED_L_RD, OUTPUT);

    // Initialize analog inputs
    analogReadResolution(12);
}


/*
 * fuelLevelGaugeTask
 * 
 * Function to manage setting of fuel gauge. Reads ADC value and
 * sets fuel gauge output accordingly.
 * 
 * Takes fuel gauge analog input and number of ADC samples as arguments.
 */
void fuelLevelGaugeTask(void)
{
  byte fuelLevel = 255;
  int adcTemp = 0;

  // Read current fuel level and set fuel gauge output
  adcTemp = getADCAverage(FUEL_SENDER_IN, ADC_SAMPLES);
  fuelLevel = getFuelLevelPercentage(adcTemp);
  if(!setFuelGaugeOutput(fuelLevel))
    SerialUSB.print("Error: Fuel level out of range\n\n");
}
