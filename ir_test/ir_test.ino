const int IR_PIN[5] = {18, 16, 17, 14, 15};
const int IR_CNT = 5;
int IR_BLACK[IR_CNT] = {940 , 914 , 912 , 930 , 923};
int IR_WHITE[IR_CNT] = { 63 ,  53 ,  49 ,  52 , 126 };
int IR_THRESHOLD[IR_CNT] = { 
    (IR_BLACK[0]+IR_WHITE[0])/2,
    (IR_BLACK[1]+IR_WHITE[1])/2,
    (IR_BLACK[2]+IR_WHITE[2])/2,
    (IR_BLACK[3]+IR_WHITE[3])/2,
    (IR_BLACK[4]+IR_WHITE[4])/2
};
const int IR_WEIGHT[IR_CNT] = { -2, -1, 0, 1, 2 };


float ir_data[IR_CNT];


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

void setup(){
    // pinMode(PIN_IR_1, INPUT);
    // pinMode(PIN_IR_2, INPUT);
    // pinMode(PIN_IR_3, INPUT);
    // pinMode(PIN_IR_4, INPUT);
    Serial.begin(115200);


}

void loop(){

    // int ir_data[5];
    // for (int i = 0; i < 5; i++){
    //     ir_data[i] = analogRead(IR_PIN[i]);
    // }
    

    // print ir data 
    // for (int i = 0; i < 5; i++){
    //     Serial.print(ir_data[i]);
    //     Serial.print("\t");
    // }
    Serial.print(read_ir());
    Serial.println();



}
