float Ltarget_speed = 130;
float Rtarget_speed = 130;

int LMotorSpeed = 0;
int RMotorSpeed = 0;

#define kp 100 //80
#define ki 0
#define kd 40

void pid(float error , float dt){
    static float last_error = 0;
    static float integral = 0;
    float derivative;
    
    integral += error*dt;
    derivative = (error-last_error)/dt;
    int out = kp*error + ki*integral + kd*derivative;

    LMotorSpeed = Ltarget_speed + out;
    RMotorSpeed = Rtarget_speed - out;

    // if(LMotorSpeed<35){
    //     LMotorSpeed -= 70;
    // }
    // if(RMotorSpeed<35){
    //     RMotorSpeed -= 70;
    // }
}