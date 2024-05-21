#define IR_DEBUG


const int IR_PIN[5] = {18, 16, 17, 14, 15};


const int IR_CNT = 5;
int IR_BLACK[IR_CNT] = {930 , 908 , 901 , 902 , 931};
int IR_WHITE[IR_CNT] = { 32 ,  30 ,  29 ,  29 , 37 };
int IR_THRESHOLD[IR_CNT] = { 
    (IR_BLACK[0]+IR_WHITE[0])/2,
    (IR_BLACK[1]+IR_WHITE[1])/2,
    (IR_BLACK[2]+IR_WHITE[2])/2,
    (IR_BLACK[3]+IR_WHITE[3])/2,
    (IR_BLACK[4]+IR_WHITE[4])/2
};
const int IR_WEIGHT[IR_CNT] = { -2, -1, 0, 1, 2 };


bool ir_data[IR_CNT];


float read_ir(){
    static float last_res = 0;

    // read ir sensors
    // > threshold trigger , data = 1 
    for(int i=0 ; i<IR_CNT ; i++){
        ir_data[i] = analogRead(IR_PIN[i]) > IR_THRESHOLD[i];
    }

    int res = 0;
    if(ir_data[0])res =  -2;
    else if(ir_data[4])res =   2;
    else if(ir_data[1])res =   -1;
    else if(ir_data[3])res =   1;
    else if(ir_data[2])res =   0;
    else if(last_res > 0){
        res = 3;
    }
    else if(last_res < 0){
        res = -3;
    }
    last_res = res;

    return res;
    

}


float read_ir__(){
    static float last_res = 0;

    // read ir sensors
    // > threshold trigger , data = 1 
    for(int i=0 ; i<IR_CNT ; i++){
        ir_data[i] = analogRead(IR_PIN[i]) > IR_THRESHOLD[i];
    }


    #ifdef IR_DEBUG
        for(int i=0 ; i<IR_CNT ; i++){
            if(ir_data[i]){
                Serial.print("1");
            }else{
                Serial.print("0");
            }
        }
        Serial.print("\t");
    #endif

    // find max continuous trigger ir sensors , then calculate the average position
    int c_cnt = 0;
    float c_sum = 0;
    int max_cnt = 0;
    float max_sum = 0;

    for(int i=0 ; i<IR_CNT ; i++){
        if(ir_data[i]){
            c_cnt++;
            c_sum += IR_WEIGHT[i];
        }else{
            c_cnt = 0;
            c_sum = 0;
        }
        
        if(c_cnt > max_cnt){
            max_cnt = c_cnt;
            max_sum = c_sum;
        }
    }
    float res;
    if(max_cnt == 0){
        if(last_res > 0){
            res = (IR_CNT/2+0.5);
        }
        else if(last_res < 0){
            res = -(IR_CNT/2+0.5);
        }
        else{
            res = 0;
        }
    }else{
        res = max_sum / max_cnt;
        last_res = res;
    }
    
    #ifdef IR_DEBUG
        Serial.print(res);
        Serial.print("\t");
        Serial.println();
    #endif
    
    return res;

}