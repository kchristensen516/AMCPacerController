
#include <Servo.h>
#include "speedometer.h"
#include "speedometerLookup.h"
#include "board.h"

#define SPEEDO_MIN_ANGLE    0
#define SPEEDO_MAX_ANGLE    180
#define SERVO_MIN_PULSE     500
#define SERVO_MAX_PULSE     2500
#define SPEED_SNDR_AVG_CNT  20
#define SPEED_SNDR_TMOUT    10000

Servo speedoServo;

int speedoAngle;        // Speedometer needle angle
uint32_t speedSenderPulse;    // Average pulse width for speed sender;
int vehicleSpeed;       // Vehicle speed in kph

void initSpeedometer(void)
{
    speedoServo.attach(SPEEDO_SERVO_PIN, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
    pinMode(SPEEDO_SENDER_PIN, INPUT);
    speedSenderPulse = 0;
}

bool speedometerSetSpeed(int vehicleSpeed)
{
    bool status = true;

    if(vehicleSpeed < 0)
        speedoAngle = SPEEDO_MIN_ANGLE;
    else if (vehicleSpeed > 149)
        speedoAngle = SPEEDO_MAX_ANGLE;
    else
        speedoAngle = gSpeedometerMapping[vehicleSpeed];
    
    speedoServo.write(speedoAngle);

    return status;
}

void speedometerCalculateSpeed(void)
{
    static uint32_t sum;    // accumulator for pulse duration in us
    static uint8_t cnt;     // averaging counter

    sum += pulseIn(SPEEDO_SENDER_PIN, HIGH, SPEED_SNDR_TMOUT);
    if(++cnt > SPEED_SNDR_AVG_CNT)
    {
        speedSenderPulse = sum / SPEED_SNDR_AVG_CNT;
        cnt = 0;
        sum = 0;
    }

    /* TODO calculate speed from speed sender pulse period */
    // 8 pulse per revolution
    // TBD rpm per kph
    // 0.002155 km / wheel revolution
    // speed = 1/(pulseWidth*2) * us/hr * rev/#pulse * km/rev
    // 3600000000us/hr
    // 1 speedometer revolution / 8 pulses
    // 1km / 464.14 wheel revolutions

    vehicleSpeed = 484763 / speedSenderPulse;

}

void speedometerTask(void)
{
    speedometerCalculateSpeed();
    speedometerSetSpeed(vehicleSpeed);
    return;
}