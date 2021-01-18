/**
 * @file adafruit_motor_driver_v1.h
 * @brief Motor device driver for the Adafruit motor shield
 * @author 
 */

#include <AFMotor.h>
#include "motor_driver.h"

namespace SlowPoke
{
    class Motor : MotorDriver
    {
    public:
        /**
         * @brief Class constructor.
         * @param number the DC motor number to control, from 1 to 4.
         */
        Motor(int number)
            : MotorDriver(), motor(number), currentSpeed(0)
        {
        }

        void setSpeed(int speed)
        {
            currentSpeed = speed;
            if (speed >= 0) {
                motor.setSpeed(speed);
                motor.run(FORWARD);
            }
                motor.setSpeed(speed);
                motor.run(BACKWARD);
        }

        int getSpeed() const
        {
            return currentSpeed;
        }

    private:
        AF_DCMotor motor;
        int currentSpeed;
    };
};