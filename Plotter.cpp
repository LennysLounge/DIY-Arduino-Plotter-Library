/*
    Plotter.h - Library for controlling a XY Plotter
    Created by Leonard Schüngel Feb 2017
*/
#include <Arduino.h>
#include <Plotter.h>

//////////////////////////////////////////////////
//  PUBLIC                                      //
//////////////////////////////////////////////////

Plotter::Plotter(){
    maxMicroStep = 32;
    time = micros();
    timeStep = 1000;
    analogLimit = false;
}
void Plotter::init(){
    findLimit();
}
void Plotter::update(){
    unsigned long microseconds = micros();
    if( time+timeStep < microseconds ){
        time = microseconds;
        if( Serial.available() ){

            char c = Serial.read();
            if( c == '\n' ){
                Serial.println( "echo->" + gcodeString );
                gcodeString = "";
            }else{
                gcodeString += c;
            }
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
    pinMode( pinToolDir, OUTPUT );
    pinMode( pinToolStep, OUTPUT );
    pinMode( pinToolM0, OUTPUT );
    pinMode( pinToolM1, OUTPUT );
    pinMode( pinToolLimit0, INPUT );
    pinMode( pinToolLimit1, INPUT );

}
void Plotter::addTableAxis( int pinDir, int pinStep, int pinM0, int pinM1,
int pinLimit0, int pinLimit1 ){

    pinTableDir = pinDir;
    pinTableStep = pinStep;
    pinTableM0 = pinM0;
    pinTableM1 = pinM1;
    pinTableLimit0 = pinLimit0;
    pinTableLimit1 = pinLimit1;
    pinMode( pinTableDir, OUTPUT );
    pinMode( pinTableStep, OUTPUT );
    pinMode( pinTableM0, OUTPUT );
    pinMode( pinTableM1, OUTPUT );
    pinMode( pinTableLimit0, INPUT );
    pinMode( pinTableLimit1, INPUT );
}
void Plotter::setMaxMicroStep( unsigned char step ){
    maxMicroStep = 1;
    for(; step>1 ; step>>=1, maxMicroStep<<=1 );
    if( microStep > maxMicroStep ) microStep = maxMicroStep;
    setMicroStepPin( microStep );
}
char Plotter::getMaxMicroStep(){
    return maxMicroStep;
}
void Plotter::setMicroStep( unsigned char step ){
    microStep = 1;
    for(; step>1 ; step>>=1, microStep<<=1 );
    if( microStep > maxMicroStep ) microStep = maxMicroStep;
    setMicroStepPin( microStep );
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
void Plotter::setAnalogLimit( bool b ){
    analogLimit = b;
    //set ADC to 2 bit to increase speed when reading
    ADCSRA &= ~7;
    ADCSRA |= 2;
}
bool Plotter::getAnalogLimit(){
    return analogLimit;
}

//////////////////////////////////////////////////
//  PRIVATE                                     //
//////////////////////////////////////////////////

void Plotter::findLimit(){
    Serial.println("initing");
    setMicroStep( maxMicroStep );
    setDir( pinToolDir, 0 );
    setDir( pinTableDir, 0 );

    bool tool = !( isLimit( pinToolLimit0 ) || isLimit( pinToolLimit1 ) );
    bool table = !( isLimit( pinTableLimit0 ) || isLimit( pinTableLimit1 ) );


    unsigned long microseconds;
    int n = 0;
    unsigned long sum = 0;
    //move until Limit
    while( tool == true || table == true ){
        microseconds = micros();
        if( time+timeStep > microseconds )  continue;
        sum += microseconds - time;
        time = microseconds;

        if( n == 1000 ){
            Serial.println( sum/1000 );
            n = 0;
            sum = 0;
            time = micros();
        }
        n++;


        digitalWrite( pinToolStep, LOW );
        digitalWrite( pinTableStep, LOW );

        if( tool == true ) step( pinToolStep );
        if( table == true ) step( pinTableStep );

        tool = !( isLimit( pinToolLimit0 ) || isLimit( pinToolLimit1 ) );
        table = !( isLimit( pinTableLimit0 ) || isLimit( pinTableLimit1 ) );
    }


    clearLimit( pinToolStep, pinToolDir, toolDir );
    clearLimit( pinTableStep, pinTableDir, tableDir );
}
bool Plotter::isLimit( char pinLimit ){
    if( analogLimit == true ){
        return analogRead( pinLimit ) > 512;
    }else{
        return digitalRead( pinLimit );
    }
}
void Plotter::setMicroStepPin( char step ){
    digitalWrite( pinToolM1, LOW );
    digitalWrite( pinToolM0, LOW );
    digitalWrite( pinTableM1, LOW );
    digitalWrite( pinTableM0, LOW );
    if( step > 4 ){
        digitalWrite( pinToolM1, HIGH );
        digitalWrite( pinTableM1, HIGH );
    }
    pinMode( pinToolM0, OUTPUT );
    pinMode( pinTableM0, OUTPUT );
    if( step == 4 || step == 32 ){
        pinMode( pinToolM0, INPUT );
        pinMode( pinTableM0, INPUT );
    }
    if( step == 2 || step == 16 ){
        digitalWrite( pinToolM0, HIGH );
        digitalWrite( pinTableM0, HIGH );
    }
}
void Plotter::setDir( char pin, bool dir ){
    digitalWrite( pin, dir );
    if( pin == pinTableDir )    tableDir = dir;
    if( pin == pinToolDir )     toolDir = dir;
}
void Plotter::step( char pin ){
    digitalWrite( pin, HIGH );
}
void Plotter::clearLimit( char st, char pinDir, char dir){
    int s = microStep;
    setMicroStep( 1 );
    setDir( pinDir, !dir );
    for( int i=0; i<limitDist; i++ ){
        step( st );
        delay(1);
        digitalWrite( st, LOW );
        delay(1);
    }
    setDir( pinDir, dir );
    setMicroStep( s );
    Serial.println("Tool Limit reached!");
}
