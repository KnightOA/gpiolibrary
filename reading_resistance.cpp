// file : reading_resistance.cpp

#include <unistd.h>
#include <iostream>
#include <chrono>
#include "libgpiopi.hpp"

using namespace std;

class Timer // Class to accurately measure the enlapsed time
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const { 
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

// We want to measure the time it takes to charge a capacitor of a known amount from 0->3.3volts
// This time can be aproximated by t=RC from an RC ciruit

int main(void)
{
    rpi_pin voltage_pin(17); // This will apply power to our circuit
    rpi_pin sense_pin(27); // This will sense when the voltage across the capacitor reaches 3.3volts
    voltage_pin.pin_export(); sense_pin.pin_export();
    voltage_pin.output(); sense_pin.input();
    
    double R; // unknown resistence
    double C = 0.0001; // our known capacitence in farads
    bool voltage_trigger = false;
    string high_or_low;
    double total_time;
    
    cout << "Starting timer" << endl;
    Timer rise_time(); voltage_pin.set_value("1");

    while(voltage_trigger)
    {
        sense_pin.getvalue(high_or_low); // dump pin result into var
        if(high_or_low == "1")
        {
            total_time = rise_time.elapsed(); // Total time should be in seconds
            voltage_trigger = true;
        }
    }
    
    // Do math here t=RC, where we know C
    R = total_time/C;
    cout << "Our value of resistence is: " << R << endl;
    return 0;
}