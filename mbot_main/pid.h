int LMotorSpeed = 0;
int RMotorSpeed = 0;

// V1
// #define kp 270
// #define ki 0
// #define kd 100

// V2 // speed 200
#define kp 110
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
    // int Ltarget_speed = 150;
    // int Rtarget_speed = 150;
    // LMotorSpeed = Ltarget_speed + out;
    // RMotorSpeed = Rtarget_speed - out;

    // v2
    int tgspeed = 255;
    if(out>0){
        LMotorSpeed = tgspeed;
        RMotorSpeed = tgspeed - out*2;
    }
    else{
        LMotorSpeed = tgspeed + out*2;
        RMotorSpeed = tgspeed; 
    }

}


#define kp_slow 45
#define ki_slow 0
#define kd_slow 0

// speed 160 , kp 40

void pid_slow(float error , float dt){
    // use ir digital data
    static float last_error = 0;
    static float integral = 0;
    float derivative;
    
    integral += error*dt;
    derivative = (error-last_error)/dt;
    int out = kp_slow*error + ki_slow*integral + kd_slow*derivative;

    // v1
    int Ltarget_speed = 180;
    int Rtarget_speed = 180;
    LMotorSpeed = Ltarget_speed + out;
    RMotorSpeed = Rtarget_speed - out;
    

    // cut the speed range -40~40, bbcause the motor can't run at low speed
    const int min_speed = 30;
    if(LMotorSpeed<min_speed){
        LMotorSpeed -= 2*min_speed;
    }
    if(RMotorSpeed<min_speed){
        RMotorSpeed -= 2*min_speed;
    }

}