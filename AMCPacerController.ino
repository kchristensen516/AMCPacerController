
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
#include "fuelLevelGauge.h"
#include "board.h"

//#define DEBUG_FUEL_LEVEL_SWEEP
//#define DEBUG_FUEL_LEVEL_SERIAL
#define DEBUG_MESSAGES

int fuelLevelSerial = 0;

void setup() 
{

  initFuelLevelGauge();
 
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
    fuelLevelGaugeTask();
  #endif

}
