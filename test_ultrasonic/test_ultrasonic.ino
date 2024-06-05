// 定義超音波感測器的引腳
// const int trigPin = 9;
// const int echoPin = 10;

// const int ultr_pin = 12;



void setup() {
  Serial.begin(115200);

}


float read_ultrasonic() {
  const int ultr_pin = 12;

  long duration;
  float distance;
  
  pinMode(ultr_pin, OUTPUT);
  digitalWrite(ultr_pin, HIGH);
  delayMicroseconds(2);
  digitalWrite(ultr_pin, LOW);
  delayMicroseconds(10);
  digitalWrite(ultr_pin, HIGH);

  pinMode(ultr_pin, INPUT);

  duration = pulseIn(ultr_pin, HIGH, 3000);
  distance = duration * 0.034 / 2;
  return distance;
}


void loop() {

  float d = read_ultrasonic();

  Serial.println(d);

  delay(100);
}

