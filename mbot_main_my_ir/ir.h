#define DS 16
#define STCP 18
#define SHCP 19
#define ana_pin 17

const byte ir_addr[11] = {
    3<<5 | 0<<2,
    3<<5 | 1<<2,
    3<<5 | 2<<2,
    3<<5 | 4<<2,
    3<<5 | 6<<2,
    // 3<<5 | 7<<2, // not use 

    0<<5,
    1<<5,
    2<<5,
    4<<5,
    6<<5,
    7<<5,

};  

void writeData_595(int data) {
    digitalWrite(STCP, LOW);
    shiftOut(DS, SHCP, MSBFIRST, data);
    digitalWrite(STCP, HIGH);
}


#define IR_DEBUG




const int IR_CNT = 11;
// int IR_BLACK[IR_CNT] = {930 , 908 , 901 , 902 , 931};
// int IR_WHITE[IR_CNT] = { 32 ,  30 ,  29 ,  29 , 37 };
// int IR_THRESHOLD[IR_CNT] = { 
//     (IR_BLACK[0]+IR_WHITE[0])/2,
//     (IR_BLACK[1]+IR_WHITE[1])/2,
//     (IR_BLACK[2]+IR_WHITE[2])/2,
//     (IR_BLACK[3]+IR_WHITE[3])/2,
//     (IR_BLACK[4]+IR_WHITE[4])/2
// };
const int IR_WEIGHT[IR_CNT] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

bool ir_data[IR_CNT];

const int threshold = 550;

void ir_setup(){
    pinMode(DS, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(SHCP, OUTPUT);

    pinMode(ana_pin, INPUT);

}


float read_ir(){
    static float last_res = 0;




    // read ir sensors
    // > threshold trigger , data = 1 
    for(int i=0 ; i<IR_CNT ; i++){
        writeData_595(ir_addr[i]);
        int val = analogRead(ana_pin);

        ir_data[i] = val < threshold;

        #ifdef IR_DEBUG
        // Serial.print(val);
        Serial.print(ir_data[i]);
        Serial.print("\t");
        #endif
    }


    bool all_white = true;
    int res = 0;
    for(int i=0 ; i<IR_CNT ; i++){
        res += ir_data[i] * IR_WEIGHT[i];
        all_white &= !ir_data[i];
    }
    


    last_res = res;

    if (all_white){
        res = last_res;
    }

    #ifdef IR_DEBUG
    Serial.println(res);
    #endif


    return res;
    

}

