/**
 * @brief Return the distance to the nearest obstacle [centimeters] measured by NewPing device
 * @return the distance to the closest object in centimeters 
 *   or maxDistance if no object was detected
 */

#include <NewPing.h>
#include "distance_sensor.h"

namespace SlowPoke
{
    class DistanceSensor : DistanceSensorDriver
    {
        public:
            DistanceSensor(int triggerPin, int echoPin, unsigned int maxDistance)
                : DistanceSensorDriver(maxDistance),
                  sensor(triggerPin, echoPin, maxDistance)
            {
            }

            /*
            virtual unsigned int getDistance()
            {
                unsigned int distance = sensor.ping_cm();
                if (distance <= 0 || distance > maxDistance)
                    return maxDistance;
                return distance;
            }
            */

            virtual unsigned int getDistance()
            {
                unsigned int dist = sensor.ping_median(3);
                dist = sensor.convert_cm(dist);

                /*
                if (dist > maxDistance)
                    dist = maxDistance;
                else if (dist <= 0 )
                    dist = 0;
                */

                if (dist <= 0)
                    return maxDistance;
                return dist;
            }

/*
            virtual uint8_t getDistance()
            {
                unsigned int filteredDistance;
                unsigned int distance = sensor.ping_cm();

                // filter out values that are over the edges
                if (distance > maxDistance)
                    filteredDistance = maxDistance;
                else if (distance <= 0 )
                    filteredDistance = 0;

                unsigned int smoothedDistance = distance;
                smoothedDistance = (distance * (1 - filteredDistance)) + (smoothedDistance * filteredDistance);

                return smoothedDistance;
            }
*/

        private:
            NewPing sensor;
    };
    
};