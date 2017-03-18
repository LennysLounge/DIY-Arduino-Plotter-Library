/*
    Plotter.h - Library for controlling a XY Plotter
    Created by Leonard Schüngel Feb 2017
*/
#include <Arduino.h>
#include <Plotter.h>

Plotter::Plotter(){
    maxMicroStep = 32;
}
void Plotter::addToolAxis( int pinDir, int pinStep, int pinM0, int pinM1,
int pinLimit0, int pinLimit1 ){

    pinToolDir = pinDir;
    pinToolStep = pinStep;
    pinToolM0 = pinM0;
    pinToolM1 = pinM1;
    pinToolLimit0 = pinLimit0;
    pinToolLimit1 = pinLimit1;
    //TODO:this
}
void Plotter::addTableAxis( int pinDir, int pinStep, int pinM0, int pinM1,
int pinLimit0, int pinLimit1 ){

    pinTableDir = pinDir;
    pinTableStep = pinStep;
    pinTableM0 = pinM0;
    pinTableM1 = pinM1;
    pinTableLimit0 = pinLimit0;
    pinTableLimit1 = pinLimit1;
    //TODO:this
}
int Plotter::setMaxMicroStep( unsigned char step ){
    maxMicroStep = 1;
    while( step > 0 ){
        step >>= 1;
        maxMicroStep <<= 1;
    }
    maxMicroStep>>=1;
    return maxMicroStep;
}
int Plotter::setMicroStep( unsigned char step ){
    microStep = 1;
    while( step > 0 ){
        step >>= 1;
        microStep <<= 1;
    }
    microStep>>=1;
    if( microStep > maxMicroStep ) microStep = maxMicroStep;
    return microStep;
}
void setLimitDist( int dist );
void setTimeStep( int time );
