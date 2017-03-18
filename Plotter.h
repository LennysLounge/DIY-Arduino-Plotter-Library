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

        void setMicroStep( unsigned char step );
        void setMaxMicroStep( unsigned char step );
        void setLimitDist( int dist );
        void setTimeStep( int time );

        char getMicroStep();
        char getMaxMicroStep();
        char getLimitDist();
        char getTimeStep();

        void update();
    private:
        char pinToolDir, pinToolStep, pinToolM0, pinToolM1;
        char pinTableDir, pinTableStep, pinTableM0, pinTableM1;
        char pinToolLimit0, pinToolLimit1;
        char pinTableLimit0, pinTableLimit1;
        char microStep;
        char maxMicroStep;
        int limitDist;
        unsigned long timeStep;
        unsigned long time;
        unsigned long lastTimeStep;
};

#endif
