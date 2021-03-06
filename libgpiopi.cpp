// File: libgpiorpi.cpp

// Compile with -std=c++11

#include <iostream> //remove this after better error handling is done
#include <fstream>
#include <string>
#include "libgpiopi.hpp"

rpi_pin::rpi_pin( int new_pin ) : pin( new_pin )
{
    // Standard constructor
}

int rpi_pin::pin_export()
{
    std::ofstream export_file( "/sys/class/gpio/export" );
    if ( export_file < 0 ) // Anything less than 0 signifys an error
    {
        return -1; // error
    }
    export_file << pin;
    export_file.close();
    return 0;
}

int rpi_pin::pin_unexport()
{
    std::ofstream unexport_file( "/sys/class/gpio/unexport" );
    if (unexport_file < 0 )
    {
        return -1; //error
    }
    unexport_file << pin;
    unexport_file.close();
    return 0;
}

int rpi_pin::input()
{
    std::ofstream fdirection( "/sys/class/gpio/gpio" + std::to_string(pin) + "/direction" );
    if (fdirection < 0 )
    {
        return -1; //error
    }
    fdirection << "in";
    fdirection.close();
    return 0;
}

int rpi_pin::output()
{
    std::ofstream fdirection( "/sys/class/gpio/gpio" + std::to_string(pin) + "/direction" );
    if (fdirection < 0 )
    {
        return -1; //error
    }
    fdirection << "out";
    fdirection.close();
    return 0;
}

int rpi_pin::set_value( std::string value )
{
    std::ofstream fvalue( "/sys/class/gpio/gpio" + std::to_string(pin) + "/value" );
    if ( fvalue < 0 )
    {
        return -1; //error
    }
    fvalue << value;
    fvalue.close();
    return 0;
}

int rpi_pin::get_value( std::string& value )
{
    std::ifstream fvalue( "/sys/class/gpio/gpio" + std::to_string(pin) + "/value" );
    if ( fvalue < 0 )
    {
        return -1; //error
    }
    fvalue >> value;
    if( value != "0" )
        value = "1";
    else
        value = "0";
    
    fvalue.close();
    return 0;
}