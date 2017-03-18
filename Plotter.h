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
        void addToolAxis( int pinDir, int pinStep, int pinM0, int pinM1,
            int pinLimit0, int pinLimit1 );
        void addTableAxis( int pinDir, int pinStep, int pinM0, int pinM1,
            int pinLimit0, int pinLimit1 );
        int setMicroStep( unsigned char step );
        int setMaxMicroStep( unsigned char step );
        void setLimitDist( int dist );
        void setTimeStep( int time );
        void init();
        void update();
    private:
        int pinToolDir, pinToolStep, pinToolM0, pinToolM1;
        int pinTableDir, pinTableStep, pinTableM0, pinTableM1;
        int pinToolLimit0, pinToolLimit1;
        int pinTableLimit0, pinTableLimit1;
        int microStep;
        int maxMicroStep;
        int limitDelay;
        int timeStep;
};

#endif
