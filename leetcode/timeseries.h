//
// Created by ZhouP on 4/8/2019.
//

#ifndef CPPSANDBOX_TIMESERIES_H
#define CPPSANDBOX_TIMESERIES_H


#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include <chrono>

typedef std::pair<time_t, double> TimeValue;
typedef std::vector<TimeValue> VTimeValues;

class TimeSeries {
private:
    int m_window;
    VTimeValues m_timedValues;
    time_t m_current;

    // m_start_boundary(1), m_end_boundary (window+2) to avoid m_start == m_end during
    int m_start_boundary;
    int m_end_boundary;

    // The current valid is from [m_start to m_end]. However, m_start may be bigger than m_end with more and more values added.
    int m_start;
    int m_end;

private:
    // Search in a rotated sorted array, the time complexity is still O(log(N))
    // But if N is not big enough, the overhead of recursion will be more than the search time saved over linear search
    int getLowerBound(int start, int end, time_t t) {
        if (end < start)
        {
            int value_e = m_timedValues[m_end_boundary].second;
            int value_s = m_timedValues[m_start_boundary].second;

            if (t==value_e)
                return m_end_boundary;
            else if (t==value_s)
                return m_start_boundary;
            else if (t<value_e)
                return getLowerBound(start, m_end_boundary, t);             // search start~m_end_boundary
            else if (t>value_s)
                return getLowerBound(m_start_boundary, end, t);             // search m_start_boundary~end
            else
                return m_end_boundary;
        }
        else
        {
            if (start == end)
            {
                if(m_timedValues[start].first<=t)
                    return start;
                else
                    return (start>=m_start_boundary)?start-1:start;
            }
            else if (start+1==end)
            {
                int s = m_timedValues[start].first;
                int e = m_timedValues[end].first;
                if (t==s)
                    return start;
                else if (t==e)
                    return end;
                else if (t < s)
                    return start -1;
                else if (t> e)
                    return end;
                else
                    return start;
            }
            else
            {
                // search between start and end
                size_t half_size = (start+end) / 2;
                if (m_timedValues[half_size].first == t)
                {
                    return half_size;
                }
                else if (m_timedValues[half_size].first > t)
                {
                    // search between 0 and half_size
                    return getLowerBound(start, half_size, t);
                }
                else
                {
                    //search between half_size and size
                    return getLowerBound(half_size, end, t);
                }
            }
        }
    }

    int getHigherBound (int start, int end, time_t t)
    {
        int low_bound_index = getLowerBound(start, end, t);
        if (low_bound_index==m_end_boundary)
        {
            return 1;
        }
        else {
            return low_bound_index+1;
        }
    }

    bool isVallidIndex (int index)
    {
        if (index==0)
            return true;

        if (m_end < m_start)
        {
            if (index<m_start && index>m_end)
                return false;
        }
        else
        {
            if(index<m_start || index>m_end)
                return false;
        }
        return true;
    }

public:
    TimeSeries(size_t window) : m_window(window), m_start(0), m_end(0), m_current(0), m_start_boundary(1), m_end_boundary (window+2), m_timedValues(window+2+1)
    {
//        m_timedValues.resize(m_end_boundary+1);
        m_timedValues[0].first = 0.0;
        m_timedValues[0].second = 0.0;
    }

    virtual  ~TimeSeries()
    {
//        m_timedValues.clear();
    }

    void AddValue(time_t current_time, double value)
    {
        m_current = current_time;
        if (current_time==m_timedValues[m_end].first)
        {
            m_timedValues[m_end].second = value;
        }
        else
        {
            // clear out the current_time - window
            time_t max_timevalue_to_keep = current_time - m_window;

            // do you need to move start? yes, move it to the first that is more than max_timevalue_to_keep
            m_start = getHigherBound (m_start, m_end, max_timevalue_to_keep);

            // you sure need to move end one position further
            if (m_end==m_end_boundary)
            {
                m_end = 1;
            }
            else
            {
                ++m_end;
            }
            m_timedValues[m_end].first = current_time;
            m_timedValues[m_end].second = value;
        }
    }
    double GetValue(time_t desired_time)
    {
        if (m_window < m_current-desired_time)
        {
            throw std::invalid_argument("undefined");
        }
        else
        {
            int index = getLowerBound(m_start, m_end, desired_time);
            if (isVallidIndex(index))
                return m_timedValues[index].second;
            else
                return m_timedValues[0].second;
        }
    }

    void AGetValue(time_t desired_time)
    {
        try
        {
            std::cout << GetValue (desired_time) << std::endl;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
};

void test_timeseries ()
{
    TimeSeries ts(5000);  // object saves the most recent 5001

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    ts.AddValue(10, 2.0);
    ts.AddValue(12, 3.0);
    ts.AddValue(14, 3.5);
    ts.AGetValue(13);  // returns 3.0
    ts.AGetValue(14);  // returns 3.5
    ts.AGetValue(9);   // returns 0
    ts.AddValue(5011, 4.0);
    ts.AGetValue(9);  // undefined -- more than 5000 seconds ago
    ts.AGetValue(11);
    ts.AGetValue(16);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ).count();

    printf("\nProgram takes %d ns\n", duration);
}

#endif //CPPSANDBOX_TIMESERIES_H
