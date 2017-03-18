/*
    Plotter.h - Library for controlling a XY Plotter
    Created by Leonard Schüngel Feb 2017
*/
#include <Arduino.h>
#include <Plotter.h>

Plotter::Plotter(){
    maxMicroStep = 32;
    time = micros();;
    timeStep = 1000000;
}
void Plotter::update(){
    unsigned long microseconds = micros();
    if( time+timeStep < microseconds ){
        Serial.println( microseconds - time );
        time = microseconds;

        if( Serial.available() ){
            Serial.println( Serial.read() );
        }




    }
}
void Plotter::addToolAxis( int pinDir, int pinStep, int pinM0, int pinM1,
int pinLimit0, int pinLimit1 ){

    pinToolDir = pinDir;
    pinToolStep = pinStep;
    pinToolM0 = pinM0;
    pinToolM1 = pinM1;
    pinToolLimit0 = pinLimit0;
    pinToolLimit1 = pinLimit1;
}
void Plotter::addTableAxis( int pinDir, int pinStep, int pinM0, int pinM1,
int pinLimit0, int pinLimit1 ){

    pinTableDir = pinDir;
    pinTableStep = pinStep;
    pinTableM0 = pinM0;
    pinTableM1 = pinM1;
    pinTableLimit0 = pinLimit0;
    pinTableLimit1 = pinLimit1;
}
void Plotter::setMaxMicroStep( unsigned char step ){
    maxMicroStep = 1;
    for(; step>1 ; step>>=1, maxMicroStep<<=1 );
    if( microStep > maxMicroStep ) microStep = maxMicroStep;
}
char Plotter::getMaxMicroStep(){
    return maxMicroStep;
}
void Plotter::setMicroStep( unsigned char step ){
    microStep = 1;
    for(; step>1 ; step>>=1, microStep<<=1 );
    if( microStep > maxMicroStep ) microStep = maxMicroStep;
}
char Plotter::getMicroStep(){
    return microStep;
}
void Plotter::setLimitDist( int dist ){
    limitDist = dist;
}
char Plotter::getLimitDist(){
    return limitDist;
}
void Plotter::setTimeStep( int time ){
    timeStep = time;
}
char Plotter::getTimeStep(){
    return timeStep;
}
