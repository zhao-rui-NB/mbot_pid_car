const int IR_PIN[5] = {18, 16, 17, 14, 15};


const int IR_CNT = 5;
const int IR_BLACK[IR_CNT] = {930 , 908 , 901 , 902 , 931};
const int IR_WHITE[IR_CNT] = { 32 ,  30 ,  29 ,  29 , 37 };
const int IR_THRESHOLD[IR_CNT] = { 
    (IR_BLACK[0]+IR_WHITE[0])/2,
    (IR_BLACK[1]+IR_WHITE[1])/2,
    (IR_BLACK[2]+IR_WHITE[2])/2,
    (IR_BLACK[3]+IR_WHITE[3])/2,
    (IR_BLACK[4]+IR_WHITE[4])/2
};
const int IR_WEIGHT[IR_CNT] = { -2, -1, 0, 1, 2 };


int ir_data[IR_CNT];
int ir_normalization[IR_CNT];


void setup(){
    for(int i=0 ; i<IR_CNT ; i++){
        pinMode(IR_PIN[i], INPUT);
    }

} 


void loop(){
    for(int i=0 ; i<IR_CNT ; i++){
        ir_data[i] = analogRead(IR_PIN[i]);
    }

    for(int i=0 ; i<IR_CNT ; i++){
        ir_normalization[i] = ir_data;
    }
    
}