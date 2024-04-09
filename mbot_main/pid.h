#define kp 120 //80
#define ki 0
#define kd 50



float Ltarget_speed = 255;
float Rtarget_speed = 255;

int LMotorSpeed = 0;
int RMotorSpeed = 0;



void pid(float error , float dt){

    static float last_error = 0;
    static float integral = 0;
    float derivative;
    
    integral += error*dt;
    derivative = (error-last_error)/dt;
    int out = kp*error + ki*integral + kd*derivative;

    // int left_speed = Ltarget_speed + out;
    // int right_speed = Rtarget_speed - out;

    int left_speed = Ltarget_speed;
    int right_speed = Rtarget_speed;

    if(out > 0){
        right_speed -= out;
    }
    else if(out < 0){
        left_speed += out;
    }

    LMotorSpeed = left_speed;
    RMotorSpeed = right_speed;

    last_error = error;
}
