
/*
 * Pacer Controller
 * 
 * The controller takes input from the fuel sender in the fuel tank and translates 
 * the measured value to a resistance value that the fuel gauge expects.
 * 
 * Future development may be used to mesure vehicle speed and drive speedometer.
 * 
 */
 
/** Include files **/
#include "amcPacerFuelLevelLookup.h"
#include "fuelLevelMapping.h"

/** Pin definitions **/
#define Q1_G            0
#define Q2_G            2
#define Q3_G            4
#define Q4_G            6
#define Q5_G            8
#define Q6_G            10
#define Q7_G            12
#define FUEL_SENDER_IN  A0

/** System definitions **/
#define ADC_MAX_VALUE   4095
#define ADC_SAMPLES     20

//#define DEBUG_FUEL_LEVEL_SWEEP
#define DEBUG_FUEL_LEVEL_SERIAL
#define DEBUG_MESSAGES

int fuelLevelSerial = 0;

void setup() 
{
  // Initialize digital outputs
  pinMode(Q1_G, OUTPUT);
  pinMode(Q2_G, OUTPUT);
  pinMode(Q3_G, OUTPUT);
  pinMode(Q4_G, OUTPUT);
  pinMode(Q5_G, OUTPUT);
  pinMode(Q6_G, OUTPUT);
  pinMode(Q7_G, OUTPUT);

  // Initialize analog inputs
  analogReadResolution(12);

  // Sweep fuel gauge as startup test
  fuelLevelSweep(20);
}

void loop() 
{
  #ifdef DEBUG_FUEL_LEVEL_SWEEP
    fuelLevelSweep(100);
  #elif defined DEBUG_FUEL_LEVEL_SERIAL
    String serialIn;
    if(SerialUSB.available())
    {
      serialIn = SerialUSB.readString();
      fuelLevelSerial = serialIn.toInt();
      SerialUSB.print("Fuel Level: ");
      SerialUSB.print(fuelLevelSerial);
      SerialUSB.print("\n");
    }
    setFuelGaugeOutput(fuelLevelSerial);
  #else
    fuelGaugeHandler(FUEL_SENDER_IN, ADC_SAMPLES);
  #endif

}

/*
 * fuelGaugeHandler
 * 
 * Function to manage setting of fuel gauge. Reads ADC value and
 * sets fuel gauge output accordingly.
 * 
 * Takes fuel gauge analog input and number of ADC samples as arguments.
 */
void fuelGaugeHandler(int fuelLevelInput, int adcSamples)
{
  byte fuelLevel = 255;
  int adcTemp = 0;

  // Read current fuel level and set fuel gauge output
  adcTemp = getADCAverage(fuelLevelInput, adcSamples);
  fuelLevel = getFuelLevelPercentage(adcTemp);
  if(!setFuelGaugeOutput(fuelLevel))
    SerialUSB.print("Error: Fuel level out of range\n\n");
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
  if(fuelLevelPercentage > 200)
    return false;
  // Get correct gate drive states from lookup table
  digitalWrite(Q1_G,gFuelLevelLookup[fuelLevelPercentage][0]);
  digitalWrite(Q2_G,gFuelLevelLookup[fuelLevelPercentage][1]);
  digitalWrite(Q3_G,gFuelLevelLookup[fuelLevelPercentage][2]);
  digitalWrite(Q4_G,gFuelLevelLookup[fuelLevelPercentage][3]);
  digitalWrite(Q5_G,gFuelLevelLookup[fuelLevelPercentage][4]);
  digitalWrite(Q6_G,gFuelLevelLookup[fuelLevelPercentage][5]);
  digitalWrite(Q7_G,gFuelLevelLookup[fuelLevelPercentage][6]);
  return true;
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
