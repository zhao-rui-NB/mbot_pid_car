int Ltarget_speed = 160;
int Rtarget_speed = 160;

int LMotorSpeed = 0;
int RMotorSpeed = 0;

#define kp 80
#define ki 0
#define kd 0

void pid(float error , float dt){
    static float last_error = 0;
    static float integral = 0;
    float derivative;
    
    integral += error*dt;
    derivative = (error-last_error)/dt;
    int out = kp*error + ki*integral + kd*derivative;


    // v1
    // LMotorSpeed = Ltarget_speed + out;
    // RMotorSpeed = Rtarget_speed - out;


    // v2
    int tgspeed = 200;
    if(out>0){
        LMotorSpeed = tgspeed;
        RMotorSpeed = tgspeed - out*2;
    }
    else{
        LMotorSpeed = tgspeed + out*2;
        RMotorSpeed = tgspeed; 
    }



    // if(LMotorSpeed<35){
    //     LMotorSpeed -= 70;
    // }
    // if(RMotorSpeed<35){
    //     RMotorSpeed -= 70;
    // }
}