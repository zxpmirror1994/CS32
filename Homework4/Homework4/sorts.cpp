#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <vector>
#include <string>
#include <cstdlib>  // for std::rand
#include <cassert>

using namespace std;

//========================================================================
//  Set this to false to skip the insertion sort tests; you'd do this if
//  you're sorting so many items that insertion_sort would take more time
//  than you're willing to wait.

const bool TEST_INSERTION_SORT = true;

//========================================================================

//========================================================================
// Timer t;                 // create a timer
// t.start();               // start the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#if __cplusplus == 201103L  // C++11

#include <chrono>

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double,std::milli> diff =
        std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
private:
    std::chrono::high_resolution_clock::time_point m_time;
};

#elif defined(_MSC_VER)  // not C++11, but Windows

#include <windows.h>

class Timer
{
public:
    Timer()
    {
        QueryPerformanceFrequency(&ticksPerSecond);
        start();
    }
    void start()
    {
        QueryPerformanceCounter(&m_time);
    }
    double elapsed() const
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000.0 * (now.QuadPart - m_time.QuadPart)) / ticksPerSecond.QuadPart;
    }
private:
    LARGE_INTEGER m_time;
    LARGE_INTEGER ticksPerSecond;
};

#else // not C++11 or Windows, so C++98

#include <ctime>

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::clock();
    }
    double elapsed() const
    {
        return (1000.0 * (std::clock() - m_time)) / CLOCKS_PER_SEC;
    }
private:
    std::clock_t m_time;
};

#endif

//========================================================================

// Here's a class that is not cheap to copy -- the vector holds a pointer
// to dynamic memory, so vector's assignment operator and copy constructor
// have to allocate storage.

// We'll simplify writing our timing tests by declaring everything public
// in this class.  (We wouldn't make data public in a class intended for
// wider use.)

typedef int IdType;

struct Sensor
{
    IdType id;
    double avg;
    vector<double> readings;
    Sensor(IdType i) : id(i)
    {
        // create ten random sensor readings (from 0 to 99)
        for (size_t k = 0; k < 10; k++)
            readings.push_back(rand() % 100);
        // (accumulate computes 0.0 + readings[0] + readings[1] + ...)
        avg = accumulate(readings.begin(), readings.end(), 0.0) / readings.size();
    }
};

inline
bool compareSensor(const Sensor& lhs, const Sensor& rhs)
{
    // The Sensor with the higher average should come first.  If they have
    // the same average, then the Sensor with the smaller id number should
    // come first.  Return true iff lhs should come first.  Notice that
    // this means that a false return means EITHER that rhs should come
    // first, or there's a tie, so we don't care which comes first,
    
    if (lhs.avg > rhs.avg)
        return true;
    if (lhs.avg < rhs.avg)
        return false;
    return lhs.id < rhs.id;
}

inline
bool compareSensorPtr(const Sensor* lhs, const Sensor* rhs)
{
    // TODO: You implement this.  Using the same criteria as compareSensor,
    //       compare two Sensors POINTED TO by lhs and rhs.  Think about
    //       how you can do it in one line by calling compareSensor.
    
    // Just so this will compile, we'll pretend every comparison results in
    // a tie, so there's no preferred ordering.
    return compareSensor(*lhs, *rhs);
}

bool isSorted(const vector<Sensor>& s)
{
    // Return true iff the vector is sorted according to the ordering
    // relationship compareSensor
    
    for (size_t k = 1; k < s.size(); k++)
    {
        if (compareSensor(s[k],s[k-1]))
            return false;
    }
    return true;
}

void insertion_sort(vector<Sensor>& s, bool comp(const Sensor&, const Sensor&))
{
    // TODO: Using the insertion sort algorithm (pp. 463-465), sort s
    //       according to the ordering relationship passed in as the
    //       parameter comp.
    
    // Just to show you how to use the second parameter, we'll write code
    // that sorts only a vector of 2 elements.  (This is *not* the
    // insertion sort algorithm.)
    
    // Note that if comp(x,y) is true, it means x must end up before y in the
    // final ordering.
    for (int unsorted = 1; unsorted < s.size(); unsorted++)
    {
        Sensor m_sensor = s[unsorted];
        int loc = unsorted;
        for (; comp(m_sensor, s[loc - 1]) && loc > 0; loc--)
        {
            s[loc] = s[loc - 1];
        }
        s[loc] = m_sensor;
    }
}

// Report the results of a timing test

void report(string caption, double t, const vector<Sensor>& s)
{
    cout << t << " milliseconds; " << caption
    << "; first few sensors are\n\t";
    size_t n = s.size();
    if (n > 5)
        n = 5;
    for (size_t k = 0; k < n; k++)
        cout << " (" << s[k].id << ", " << s[k].avg << ")";
    cout << endl;
}

int main()
{
    size_t nsensors;
    cout << "Enter number of sensors to sort: ";
    cin >> nsensors;
    if ( !cin  ||  nsensors <= 0)
    {
        cout << "You must enter a positive number.  Goodbye." << endl;
        return 1;
    }
    
    // Create a random ordering of id numbers 0 through nsensors-1
    vector<IdType> ids;
    for (size_t j = 0; j < nsensors; j++)
        ids.push_back(IdType(j));
    random_shuffle(ids.begin(), ids.end());  // from <algorithm>
    
    // Create a bunch of Sensors
    vector<Sensor> unorderedSensors;
    for (size_t k = 0; k < ids.size(); k++)
        unorderedSensors.push_back(Sensor(ids[k]));
    
    // Create a timer
    
    Timer timer;
    
    // Sort the Sensors using the STL sort algorithm.  It uses a variant
    // of quicksort called introsort.
    
    vector<Sensor> sensors(unorderedSensors);
    timer.start();
    sort(sensors.begin(), sensors.end(), compareSensor);
    report("STL sort", timer.elapsed(), sensors);
    assert(isSorted(sensors));
    
    // Sort the already sorted array using the STL sort.  This should be
    // fast.
    timer.start();
    sort(sensors.begin(), sensors.end(), compareSensor);
    report("STL sort if already sorted", timer.elapsed(), sensors);
    assert(isSorted(sensors));
    
    if (TEST_INSERTION_SORT)
    {
        // Sort the original unsorted array using insertion sort.  This
        // should be really slow.  If you have to wait more than a minute,
        // try rerunning the program with a smaller number of Sensors.
        
        sensors = unorderedSensors;
        timer.start();
        insertion_sort(sensors, compareSensor);
        report("insertion sort if not already sorted", timer.elapsed(), sensors);
        assert(isSorted(sensors));
        
        // Sort the already sorted array using insertion sort.  This should
        // be fast.
        
        timer.start();
        insertion_sort(sensors, compareSensor);
        report("insertion sort if already sorted", timer.elapsed(), sensors);
        assert(isSorted(sensors));
    }
    
    // Since Sensors are expensive to copy, and since the STL's sort copies
    // Sensors O(N log N) times, let's sort POINTERS to the Sensors, then
    // make one final pass to rearrange the Sensors according to the
    // reordered pointers.  We'll write some code; you write the rest.
    
    // Set sensors to the original unsorted sequence
    sensors = unorderedSensors;
    
    // Start the timing
    timer.start();
    
    // Create a auxiliary copy of sensors, to faciliate the later reordering.
    // We create it in a local scope so that we also account for the
    // destruction time.
    {
        vector<Sensor> auxSensors(sensors);
        
        // TODO:  Create a vector of Sensor pointers, and set each pointer
        //        to point to the corresponding Sensor in auxSensors.
        vector<Sensor*> sensorPtr;
        for (int k = 0; k < auxSensors.size(); k++)
        {
            sensorPtr.push_back(&auxSensors.at(k));
        }
        
        // TODO:  Sort the vector of pointers using the STL sort algorithm
        //        with compareSensorPtr as the ordering relationship.
       
        sort(sensorPtr.begin(), sensorPtr.end(), compareSensorPtr);
        
        // TODO:  Using the now-sorted vector of pointers, replace each Sensor
        //        in sensors with the Sensors from auxSensors in the correct
        //        order.
        for (int i = 0; i < sensors.size(); i++)
        {
            sensors[i] = *sensorPtr.at(i);
        }
        
    } // auxSensors will be destroyed here
    
    // Report the timing and verify that the sort worked
    report("STL sort of pointers", timer.elapsed(), sensors);
    assert(isSorted(sensors));
}