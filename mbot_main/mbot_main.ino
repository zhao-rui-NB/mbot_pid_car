#include "ir.h"

#include "motor.h"
#include "pid.h"




unsigned long start_time = 0;

void setup(){
    // while(analogRead(A7) > 30){}
    // delay(1000); // wait for serial read
    Serial.begin(115200);
    motor_setup();
    // motor_write(150, 150);
    pinMode(A7, INPUT_PULLUP);
    // pinMode(8 , OUTPUT);

        // digitalWrite(8, HIGH);delay(2000);



    if(0){
        Serial.println("start calibrate IR");
        for(int i=0 ; i<5 ; i++){
            IR_BLACK[i] = 0;
            IR_WHITE[i] = 1024;
        }

        while(analogRead(A7) > 30){
            // Serial.println(analogRead(A7));
        }
        // digitalWrite(6, HIGH);delay(100);digitalWrite(6, LOW);
        Serial.println("start find black");
        // find black
        for(int j=0 ; j<100 ; j++){
            for(int i=0 ; i<5 ; i++){
                int val = analogRead(IR_PIN[i]);
                if(val > IR_BLACK[i]){
                    IR_BLACK[i] = val;
                }
                delay(10);
            }
        }

        while(analogRead(A7) > 30){}
        Serial.println("start find white");
        // find white
        for(int j=0 ; j<100 ; j++){
            for(int i=0 ; i<5 ; i++){
                int val = analogRead(IR_PIN[i]);
                if(val < IR_WHITE[i]){
                    IR_WHITE[i] = val;
                }
                delay(10);
            }
        }

        for(int i=0 ; i<5 ; i++){
            IR_THRESHOLD[i] = (IR_BLACK[i]+IR_WHITE[i])/2;
        }

        // print resault 
        Serial.println("IR_BLACK");
        for(int i=0 ; i<5 ; i++){
            Serial.print(IR_BLACK[i]);
            Serial.print("\t");
        }
        Serial.println();

        Serial.println("IR_WHITE");
        for(int i=0 ; i<5 ; i++){
            Serial.print(IR_WHITE[i]);
            Serial.print("\t");
        }
        Serial.println();

        Serial.println("IR_THRESHOLD");
        for(int i=0 ; i<5 ; i++){
            Serial.print(IR_THRESHOLD[i]);
            Serial.print("\t");
        }
        Serial.println();

        while(analogRead(A7) > 30){}
        delay(300);

    }


}

#define filter_size 3
int filter[filter_size] = {0};
int filter_pos = 0;

void loop(){

    const unsigned long update_time = 10;

    if (millis() - start_time > update_time){
        start_time = millis();


        float error = read_ir();
        // add to filter 
        filter[filter_pos] = error;
        filter_pos = (filter_pos+1)%filter_size;
        // get filter aveg
        error = 0;
        for(int i=0 ; i<filter_size ; i++){
            error += filter[i];
        }
        error /= filter_size;



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
