/*
    Plotter.h - Library for controlling a XY Plotter
    Created by Leonard Schüngel Feb 2017
*/
#ifndef Plotter_h
#define Plotter_h

#include "Arduino.h"

class Plotter{
    public:
        Plotter();
        void addAxisX( int pinDir, int pinStep, int pinM0, int pinM1 );
    private:
        int _pin;
};

#endif
