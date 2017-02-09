/*
    Plotter.h - Library for controlling a XY Plotter
    Created by Leonard Schüngel Feb 2017
*/
#include <Arduino.h>
#include <Plotter.h>

Plotter::Plotter(){
}
void Plotter::addAxis(){
    digitalWrite( _pin, 1 );
    delay(10);
    digitalWrite( _pin, 0 );
    delay(10);
}
