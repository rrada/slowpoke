//#define LOGGING
#define ENABLE_ADAFRUIT_MOTOR_DRIVER_V1
#define ENABLE_NEWPING_DISTANCE_SENSOR
//#define ENABLE_REMOTE_CONTROLLER

#include <Arduino.h>
#include "logging.h"
#include "moving_average.h"

//#include <Arduino.h>
//#include <SoftwareSerial.h>

#define RUN_TIME        30

#define BT_RX           A2
#define BT_TX           A3

#define TRIGGER_PIN     A0
#define ECHO_PIN        A1
#define TOO_CLOSE       10
#define MAX_DISTANCE    400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define MOTOR_L 1
#define MOTOR_R 3
#define FWD_SPEED       200
#define BWD_SPEED       155


#ifdef ENABLE_REMOTE_CONTROLLER
SoftwareSerial BTSerial(BT_RX, BT_TX);
#endif

#ifdef ENABLE_ADAFRUIT_MOTOR_DRIVER_V1
#include "adafruit_motor_driver_v1.h"
#endif

#ifdef ENABLE_NEWPING_DISTANCE_SENSOR
#include "newping_distance_sensor.h"
#define DISTANCE_SENSOR_INIT TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE
#endif

namespace SlowPoke
{
    class Robot
    {
        public:
            Robot()
                : leftMotor(MOTOR_L), rightMotor(MOTOR_R),
                  distanceSensor(DISTANCE_SENSOR_INIT) //, distanceAverage(MAX_DISTANCE)
            {
                initialize();
            }

            void initialize()
            {
                state = state_t::STOPPED;
                startTime = millis();
                endTime = startTime + RUN_TIME * 1000;
                //move();
                move(50); // with forced distance of 30 cm
            }

            void run()
            {
                if (stopped())
                    return;

                unsigned long currentTime = millis();

                // moving average - not useful
                //unsigned int distance = distanceAverage.add(distanceSensor.getDistance());
                unsigned int distance = distanceSensor.getDistance();
                log("state: %u, currentTime: %lu, distance: %u\n", state, currentTime, distance);

                if (doneMoving(currentTime))
                    stop();
                else if (moving())
                {
                    if (obstacleAhead(distance))
                        turn(currentTime);
                }
                else if (turning())
                {
                    if (doneTurning(currentTime, distance))
                        move(distance);
                }
            }

            // state checks
            bool doneMoving(unsigned long currentTime)
            {
                return currentTime >= endTime;
            }

            bool doneTurning(unsigned long currentTime, unsigned int distance)
            {
                if (currentTime >= endStateTime)
                    return distance > TOO_CLOSE;
                return false;
            }

            bool obstacleAhead(unsigned int distance)
            {
                return distance <= TOO_CLOSE;
            }


            // movement commands
            void move(unsigned int distance)
            {
                unsigned int speed = map(distance, 20, 200, 50, FWD_SPEED);

                leftMotor.setSpeed(speed);
                rightMotor.setSpeed(speed);
                //leftMotor.setSpeed(FWD_SPEED);
                //rightMotor.setSpeed(FWD_SPEED);

                state = state_t::MOVING;
            }

            void stop()
            {
                leftMotor.setSpeed(0);
                rightMotor.setSpeed(0);
                state = state_t::STOPPED;
            }

            void turn(unsigned long currentTime)
            {
                if (random(2) == 0)
                {
                    leftMotor.setSpeed(-BWD_SPEED);
                    rightMotor.setSpeed(FWD_SPEED);
                }
                else // turn right
                {
                    leftMotor.setSpeed(FWD_SPEED);
                    rightMotor.setSpeed(-BWD_SPEED);
                }

                state = state_t::TURNING;
                endStateTime = currentTime + random(500, 1000);
            }

            // movement states
            bool moving() { return state == state_t::MOVING; }
            bool turning() { return state == state_t::TURNING; }
            bool stopped() { return state == state_t::STOPPED; }


        private:
            enum state_t {
                STOPPED,
                MOVING,
                TURNING,  
                REMOTE_CONTROL
            };

            state_t state;

            unsigned long startTime;
            unsigned long endTime;
            unsigned long endStateTime;;

            Motor leftMotor;
            Motor rightMotor;

            DistanceSensor distanceSensor;
            //MovingAverage<unsigned int, 10> distanceAverage; // was 3 measurements only
    };
};

SlowPoke::Robot robot;

void setup() {
    Serial.begin(115200);
    //BTSerial.begin(9600);

    robot.initialize();
}

void loop() {
    robot.run();
}