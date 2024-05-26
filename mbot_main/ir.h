#define IR_DEBUG

// 
// int IR_BLACK[IR_CNT] = {930 , 908 , 901 , 902 , 931};
// int IR_WHITE[IR_CNT] = { 32 ,  30 ,  29 ,  29 , 37 };

int IR_CNT = 5;
int IR_PIN[5] = {18, 16, 17, 14, 15};
float IR_WEIGHT[5] = { 1,2,3,4,5 };


// max is black , min is white
int ir_max[5] = {0, 0, 0, 0, 0};
int ir_min[5] = {1023, 1023, 1023, 1023, 1023};
int ir_data[5] = {0, 0, 0, 0, 0}; // raw data
double ir_norm_data[5] = {0, 0, 0, 0, 0};
float ir_error = 0;


float ir_digital_weight[5] = { -2 , -1 , 0 , 1 , 2 };
bool ir_digital_data[5];
float ir_digital_error = 0;


// if car not stop at middle of the black line
// will use this function to calculate error
// when black all out of range , will check last error > 0 or not
// if last error > 0 , means car is on the right side of the black line , so error = 3
// if last error < 0 , means car is on the left side of the black line , so error = -3
float calc_ir_digital_error(){
    static float last_digital_error = 0;
    // merge all digital data to one byte 
    // 0b00000
    byte dig_ir_data = ir_digital_data[0]<<4 | ir_digital_data[1]<<3 | ir_digital_data[2]<<2 | ir_digital_data[3]<<1 | ir_digital_data[4];

    if(dig_ir_data == 0b00100){
        last_digital_error = 0;
        return 0;
    }
    else if(dig_ir_data == 0b00000){
        if(last_digital_error == 0){
            return 0;
        }
        else if(last_digital_error > 0){
            return 3.5;
        }        
        else{
            return -3.5;
        }
    }
    else{
        int cnt_trigger = 0;
        float error = 0;
        for(int i=0 ; i<5 ; i++){
            if(ir_digital_data[i]){
                error += ir_digital_weight[i];
                cnt_trigger++;
            }
        }
        // error /= cnt_trigger; // kp 90
        last_digital_error = error;
        return  error;
    }
}





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

    // normalize data
    for(int i=0 ; i<IR_CNT ; i++){
        ir_norm_data[i] = float(ir_data[i] - ir_min[i]) / float(ir_max[i] - ir_min[i]);
        // debug 
        
        // // Serial.print("\n\n");
        // Serial.print("x");Serial.print(ir_data[i]);Serial.print("\t");
        // Serial.print("max");Serial.print(ir_max[i]);Serial.print("\t");
        // Serial.print("min");Serial.print(ir_min[i]);Serial.print("\t");

        // //u
        // Serial.print("u");Serial.print(float(ir_data[i] - ir_min[i]));Serial.print("\t");

        // //d
        // Serial.print("d");Serial.print(float(ir_max[i] - ir_min[i]));Serial.print("\t");


        // Serial.print("n");Serial.print(ir_norm_data[i]);Serial.println("\t");


    }

    // save digital data
    for(int i=0 ; i<IR_CNT ; i++){
        ir_digital_data[i] = ir_norm_data[i] > 0.5;
    }


    // calculate error
    ir_error = 0;
    for(int i=0 ; i<IR_CNT ; i++){
        ir_error += ir_norm_data[i] * IR_WEIGHT[i];
    }

    // Serial.print("[debug] Error:\t");Serial.println(ir_error);

    float ir_sum = 0;
    for(int i=0 ; i<IR_CNT ; i++){
        ir_sum += ir_norm_data[i];
    }

    if(ir_sum == 0){
        ir_error = 0;
    }
    else{
        ir_error = ir_error / ir_sum - 3.0;
    }


    return ir_error;
}


void ir_print_range(bool endline = true){
    Serial.println("\t\t###IR Range###");
    Serial.print("MAX:\t");for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_max[i]);Serial.print("\t");}
    Serial.println();
    Serial.print("MIN:\t");for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_min[i]);Serial.print("\t");}
    if(endline)Serial.println();
}

void ir_print_data(bool endline = true){
    for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_data[i]);Serial.print("\t");}
    if(endline)Serial.println();
}

void ir_print_digital_data(bool endline = true){
    for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_digital_data[i]);Serial.print("\t");}
    if(endline)Serial.println();
}

void ir_print_norm_data(bool endline = true){
    for(int i=0 ; i<IR_CNT ; i++){Serial.print(ir_norm_data[i]);Serial.print("\t");}
    if(endline)Serial.println();
}

void ir_print_error(bool endline = true){
    Serial.print("IR Error:\t");Serial.print(ir_error);
    if(endline)Serial.println();
}


