#include "ir.h"

#include "motor.h"
#include "pid.h"





unsigned long start_time = 0;

void setup(){
    Serial.begin(115200);
    motor_setup();
    pinMode(A7, INPUT_PULLUP);



}

void loop(){

    const unsigned long update_time = 10;

    if (millis() - start_time > update_time){
        start_time = millis();


        float error = read_ir();
        pid(error , update_time);
        motor_write(LMotorSpeed, RMotorSpeed);
    }



}
