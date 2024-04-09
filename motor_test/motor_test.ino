#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6

#define M1_FORWARD 0
#define M1_BACKWARD 1
#define M2_FORWARD 1
#define M2_BACKWARD 0


void setup(){
    pinMode(M1_DIR, OUTPUT);
    pinMode(M1_PWM, OUTPUT);
    pinMode(M2_DIR, OUTPUT);
    pinMode(M2_PWM, OUTPUT);

    digitalWrite(M1_DIR, M1_FORWARD);
    digitalWrite(M2_DIR, M2_FORWARD);


    analogWrite(M1_PWM, 30);
    analogWrite(M2_PWM, 200);


}

void loop(){

    // analogWrite(M1_PWM,255);
    // analogWrite(M2_PWM,255);


    // for(int i=0; i<255; i++){
    //     analogWrite(M1_PWM, i);
    //     analogWrite(M2_PWM, i);
    //     delay(50);
    // }
}
