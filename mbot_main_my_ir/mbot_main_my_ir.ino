#include "ir.h"

#include "motor.h"
#include "pid.h"


unsigned long start_time = 0;

void setup(){
    // while(analogRead(A7) > 30){}
    // delay(1000); // wait for serial read
    Serial.begin(115200);
    motor_setup();
    ir_setup();


    while (1){
        read_ir();
    }
    

}

void loop(){

    const unsigned long update_time = 10;

    if (millis() - start_time > update_time){
        start_time = millis();


        float error = read_ir();
        Serial.println(error);
        pid(error , update_time);
        // Serial.print(error);
        // Serial.print("\t");
        // Serial.print(LMotorSpeed);
        // Serial.print("\t");
        // Serial.println(RMotorSpeed);
        // Serial.print("\t");
        // Serial.println();


        // Serial.print(LMotorSpeed);
        // Serial.print("\t");
        // Serial.println(RMotorSpeed);
        // Serial.print("\t");
        // Serial.println();
        motor_write(LMotorSpeed, RMotorSpeed);
    }



    // button stop
    if(analogRead(A7) < 30 || Serial.available() > 0){
        Serial.println("A7");   
        while(analogRead(A7) < 30){}
        motor_write(0, 0);
        while (1){}
    }

}
