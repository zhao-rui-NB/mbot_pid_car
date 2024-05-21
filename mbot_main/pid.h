int Ltarget_speed = 160;
int Rtarget_speed = 160;

<<<<<<< HEAD
// #define PID_V1
#define PID_V2

int LMotorSpeed = 0;
int RMotorSpeed = 0;



#ifdef PID_V1
float Ltarget_speed = 200;
float Rtarget_speed = 200;


#define kp 70 //80
#define ki 0
#define kd 25
=======
int LMotorSpeed = 0;
int RMotorSpeed = 0;

#define kp 80
#define ki 0
#define kd 0
>>>>>>> 71d6a47e09c2cf59b1923735e42cb0d926cc0d96

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



<<<<<<< HEAD


#ifdef PID_V2




#define kp 120 //80
#define ki 0
#define kd 50
float Ltarget_speed = 250;
float Rtarget_speed = 250;
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

#endif
=======
    // if(LMotorSpeed<35){
    //     LMotorSpeed -= 70;
    // }
    // if(RMotorSpeed<35){
    //     RMotorSpeed -= 70;
    // }
}
>>>>>>> 71d6a47e09c2cf59b1923735e42cb0d926cc0d96
