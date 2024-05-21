#define IR_DEBUG

// 
// int IR_BLACK[IR_CNT] = {930 , 908 , 901 , 902 , 931};
// int IR_WHITE[IR_CNT] = { 32 ,  30 ,  29 ,  29 , 37 };


int IR_CNT = 5;
int IR_PIN[5] = {18, 16, 17, 14, 15};
double IR_WEIGHT[5] = { -2, -1, 0, 1, 2 };
double MIDDLE_WEIGHT = 1.0;
// const float IR_WEIGHT[IR_CNT] = {  };


// max is black , min is white
u16 ir_max[5] = {0, 0, 0, 0, 0};
u16 ir_min[5] = {1023, 1023, 1023, 1023, 1023};
u16 ir_data[5] = {0, 0, 0, 0, 0};
float ir_error = 0;

float ir_read(bool update_range){
    // save ir data and update range if needed
    for(int i=0 ; i<IR_CNT ; i++){
        ir_data[i] = analogRead(IR_PIN[i]);
        if(update_range){
            if(ir_data[i] > ir_max[i]){
                ir_max[i] = ir_data[i];
            }
            if(ir_data[i] < ir_min[i]){
                ir_min[i] = ir_data[i];
            }
        }
    }

    // calculate error
    ir_error = 0;
    for(int i=0 ; i<IR_CNT ; i++){
        ir_error += (double(ir_data[i] - ir_min[i]) / double(ir_max[i] - ir_min[i])) * IR_WEIGHT[i];
    }
    // process MIDDLE_WEIGHT
    // pull error close to 0, by MIDDLE_WEIGHT
    // float mid_fix = float(ir_data[2] - ir_min[2]) / float(ir_max[2] - ir_min[2]) * MIDDLE_WEIGHT;
    // bool neg = ir_error<0;

    // ir_error = abs(ir_error);
    // ir_error = ir_error - mid_fix;
    // if(ir_error<0)
    //     ir_error = 0;
    // if(neg){
    //     ir_error *= -1;
    // }


    return ir_error;
}


void ir_print_range(){
    Serial.println("\t\t###IR Range###");
    Serial.print("MAX:\t");for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_max[i]);Serial.print("\t");}
    Serial.println();
    Serial.print("MIN:\t");for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_min[i]);Serial.print("\t");}
    Serial.println();
}

void ir_print_data(){
    for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_data[i]);Serial.print("\t");}Serial.println();
}

void ir_print_error(){
    Serial.print("IR Error:\t");Serial.println(ir_error);
}


