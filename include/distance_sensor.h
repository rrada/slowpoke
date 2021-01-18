/**
 * @file distance_sensor.h
 * @brief Distance sensor driver definition for the SlowPoke robot.
 * @author 
 */

namespace SlowPoke
{
    class DistanceSensorDriver
    {
    public:
        DistanceSensorDriver(unsigned int distance) : maxDistance(distance) {}

        /**
         * @brief Return the distance to the nearest obstacle [centimeters]
         * @return the distance to the closest object in centimeters 
         *   or maxDistance if no object was detected
         */
        virtual unsigned int getDistance() = 0;

    protected:
        uint8_t maxDistance;
    };
};