#include "ir.h"

#include "motor.h"
#include "pid.h"

unsigned long start_time = 0;

void setup(){
    pinMode(8, OUTPUT);

    


    // while(analogRead(A7) > 30){}
    // delay(1000); // wait for serial read
    Serial.begin(115200);
    motor_setup();

    pinMode(A7, INPUT_PULLUP);

    // start calibration the ir sensor, it will rotate the robot
    // and find the max and min value of the ir sensor
    start_time = millis();
    motor_write(150, -150);
    while(millis() - start_time < 2000){
        ir_read(true);
        ir_print_data();
    }

    tone(8, 1200, 20);

    // keep slow rotating to stop at middle of the black line
    motor_write(80, -80);
    start_time = millis();
    while(millis() - start_time < 5000){
        ir_read(true);
        ir_print_data();
        if(float(ir_data[2]-ir_min[2]) / float(ir_max[2]-ir_min[2]) > 0.7){
            break;
        }
    }
    motor_write(0, 0);

    tone(8, 1200, 20);

    ir_print_range();
    // ir_print_error();





    // while(1){
    //     float err = ir_read(true);
    //     Serial.println(err);
    //     delay(100);
    // }
    delay(1000);
}

void loop(){

    const unsigned long update_time = 10;
    if (millis() - start_time > update_time){
        start_time = millis();

        float error = ir_read(false);
        pid(error , update_time);
        motor_write(LMotorSpeed, RMotorSpeed);
    }


    

    // button stop
    if(analogRead(A7) < 30 || Serial.available() > 0){
        tone(8, 3600, 50);
        Serial.println("A7");   
        while(analogRead(A7) < 100){}
        motor_write(0, 0);
        while (1){
            ir_read(false);
            ir_print_error();

        }
    }
    
}
