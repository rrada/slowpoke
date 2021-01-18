/**
 * @brief Moving Average(circular buffer) for various input sensor data smoothing
 * @return Smoothed average value for N items
 */

template <typename V, int N> class MovingAverage
{
public:
    MovingAverage(V def = 0) : sum(0), ptr(0)
    {
        for (int i = 0; i < N; i++)
        {
            samples[i] = def;
            sum += samples[i];
        }
    }

    /**
     * @return Smoothened average value for N items
     */
    V add(V new_sample)
    {
        sum = sum - samples[ptr] + new_sample;
        samples[ptr++] = new_sample;
        if (ptr > N)
            ptr = 0;
        return sum / N;
    }

private:
    V samples[N];
    V sum;
    V ptr;
};

