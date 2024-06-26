#include "ir.h"

#include "motor.h"
#include "pid.h"

unsigned long start_time = 0;
unsigned long start_run_time = 0;
int stop_count = 0;



float read_ultrasonic() {
    const int ultr_pin = 12;

    long duration;
    float distance;
    
    pinMode(ultr_pin, OUTPUT);
    digitalWrite(ultr_pin, HIGH);
    delayMicroseconds(2);
    digitalWrite(ultr_pin, LOW);
    delayMicroseconds(10);
    digitalWrite(ultr_pin, HIGH);

    delayMicroseconds(10);

    pinMode(ultr_pin, INPUT);

    duration = pulseIn(ultr_pin, HIGH, 3000);
    distance = duration * 0.034 / 2;
    return distance;
}

void avoidance(){
    static unsigned long utl_start_time = 0;

    if(millis() - utl_start_time > 30){
        utl_start_time = millis();
    
        float d = read_ultrasonic();
        Serial.print("ultrasonic: ");
        Serial.println(d);
        if(d < 15 && d > 0){
            motor_write(200, 0);
            delay(300);
            
            motor_write(130, 255);
            delay(800);

            motor_write(160, 80);
            delay(190);

            motor_write(150, 150);  
            // while(1){}
        }
    
    
    }
    

}

void setup(){
    pinMode(8, OUTPUT);

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

    // wait for the user to press the button
    while(analogRead(A7) > 30){}
    start_run_time = millis();


    // while(1){
    //     float err = ir_read(true);
    //     Serial.println(err);
    //     delay(100);
    // }



    // irdebug 
    // while(1){
    //     ir_read(false);
    //     // ir_print_data(false);
    //     ir_print_norm_data(false);
    //     ir_print_error();
    //     delay(100);
    // }

    // irdebug 
    // while(1){
    //     ir_read(false);
    //     float res = calc_ir_digital_error();
    //     ir_print_data(false);
    //     ir_print_norm_data(false);
    //     ir_print_digital_data(false);
    //     Serial.print("ir_digital_error: ");Serial.println(res);
        
    // }



}

void loop(){
    static bool stable_flag = true;
    static int stable_cnt = 0;
    const unsigned long update_time = 1;
    
    if (millis() - start_time > update_time){


    bool stable = (ir_digital_data[2] || ir_digital_data[1] || ir_digital_data[3]) && !ir_digital_data[0] && !ir_digital_data[4];
    if(stable){
        stable_cnt++;
        if(stable_cnt > 120){
            stable_flag = true;
        }
    }
    else{
        stable_cnt = 0;
        stable_flag = false;
    }

    bool update = true;
    if(stable_flag){
        //############# fast pid #############
        // start_time = millis();
        float error = ir_read(update);
        pid(error , update_time);
        motor_write(LMotorSpeed, RMotorSpeed);
    }
    else{
        //############# slow pid #############
        ir_read(update);
        float error = calc_ir_digital_error();
        pid_slow(error, update_time);
        motor_write(LMotorSpeed, RMotorSpeed);

        // Serial.print("ir_digit_error: ");Serial.print(error);Serial.print("\t");
        // ir_print_digital_data();
    }   

    avoidance();

    } // end of if (millis() - start_time > update_time)

    // all ir is not triger 
    bool stop_dect = ir_digital_data[0] && ir_digital_data[1] && ir_digital_data[2] && ir_digital_data[3] && ir_digital_data[4];
    if(stop_dect && millis()-start_run_time > 20000){
        stop_count++;
        if(stop_count > 20){
            motor_write(0, 0);
            while(1){}
        }
        
    }
        

    // button stop
    // if(stop ||analogRead(A7) < 30 || Serial.available() > 0){
    if((analogRead(A7) < 30 && millis()-start_run_time > 1000) || Serial.available() > 0){
        tone(8, 3600, 50);
        Serial.println("A7");   
        while(analogRead(A7) < 100){}
        motor_write(0, 0);
        while (1){
            ir_read(false);
            ir_print_error();

            if(analogRead(A7) < 30 || Serial.available() > 0){
                delay(100);
                break;
            }

        }
    }
    
}
