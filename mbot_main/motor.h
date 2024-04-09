#define M1_DIR 4
#define M1_PWM 5
#define M2_DIR 7
#define M2_PWM 6

#define M1_FORWARD 0
#define M1_BACKWARD 1
#define M2_FORWARD 1
#define M2_BACKWARD 0


void motor_setup(){
    pinMode(M1_DIR, OUTPUT);
    pinMode(M1_PWM, OUTPUT);
    pinMode(M2_DIR, OUTPUT);
    pinMode(M2_PWM, OUTPUT);

    digitalWrite(M1_DIR, M1_FORWARD);
    digitalWrite(M2_DIR, M2_FORWARD);
}

void motor_write(int left_speed, int right_speed){
    if(left_speed > 0){
        digitalWrite(M1_DIR, M1_FORWARD);
    }else{
        digitalWrite(M1_DIR, M1_BACKWARD);
        left_speed = -left_speed;
    }

    if(right_speed > 0){
        digitalWrite(M2_DIR, M2_FORWARD);
    }else{
        digitalWrite(M2_DIR, M2_BACKWARD);
        right_speed = -right_speed;
    }

    if(left_speed > 255) 
        left_speed = 255;
    if(right_speed > 255) 
        right_speed = 255;
    if(left_speed < 0) 
        left_speed = 0;
    if(right_speed < 0)
        right_speed = 0;

    analogWrite(M1_PWM, left_speed);
    analogWrite(M2_PWM, right_speed);
}

