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


float read_ir(){
    for(int i=0 ; i<IR_CNT ; i++){
        float v  = analogRead(IR_PIN[i]);
        // ir_data[i] = v > IR_THRESHOLD[i];
        ir_data[i] = (v-IR_WHITE[i])/ (IR_BLACK[i]-IR_WHITE[i]);
        Serial.print(ir_data[i]);
        Serial.print("\t");
    }

    float res = 0;
    for(int i=0 ; i<IR_CNT ; i++){
        res = res + ir_data[i] * IR_WEIGHT[i];
        
        // if(ir_data[i]){
        //     res += IR_WEIGHT[i];
        // }
    }


    return res;
}




