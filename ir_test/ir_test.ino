// #define PIN_IR_1 18
// #define PIN_IR_2 16
// #define PIN_IR_3 17
// #define PIN_IR_4 14
// #define PIN_IR_5 15

const int IR_PIN[5] = {18, 16, 17, 14, 15};


void setup(){
    // pinMode(PIN_IR_1, INPUT);
    // pinMode(PIN_IR_2, INPUT);
    // pinMode(PIN_IR_3, INPUT);
    // pinMode(PIN_IR_4, INPUT);
    Serial.begin(9600);


}

void loop(){

    int ir_data[5];
    for (int i = 0; i < 5; i++){
        ir_data[i] = analogRead(IR_PIN[i]);
    }
    

    // print ir data 
    for (int i = 0; i < 5; i++){
        Serial.print(ir_data[i]);
        Serial.print("\t");
    }


    for (int i = 0; i < 5; i++){
        Serial.print(ir_data[i]/1024.0);
        Serial.print("\t");
    }
    Serial.println();

}
