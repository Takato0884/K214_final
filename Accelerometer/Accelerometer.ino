//Processingとの連携


//７セグ
#define PIN_LED_A_10 45    // 0
#define PIN_LED_B_10 44   // 1
#define PIN_LED_C_10 41     // 2
#define PIN_LED_D_10 40    // 3
#define PIN_LED_E_10 39   // 4
#define PIN_LED_F_10 43   // 5
#define PIN_LED_G_10 42  // 6
#define PIN_LED_A_1 46    // 0
#define PIN_LED_B_1 49   // 1
#define PIN_LED_C_1 53     // 2
#define PIN_LED_D_1 51    // 3
#define PIN_LED_E_1 48   // 4
#define PIN_LED_F_1 47   // 5
#define PIN_LED_G_1 52  // 6

byte pinNo_10[7] = {
    PIN_LED_A_10, PIN_LED_B_10, PIN_LED_C_10,
    PIN_LED_D_10,PIN_LED_E_10, PIN_LED_F_10,
    PIN_LED_G_10};
    
byte pinNo_1[7] = {
    PIN_LED_A_1, PIN_LED_B_1, PIN_LED_C_1,
    PIN_LED_D_1,PIN_LED_E_1, PIN_LED_F_1,
    PIN_LED_G_1};

byte onOffTable_10[7 * 10] = {
    //A  B  C  D  E  F  G
    1, 1, 1, 1, 1, 1, 0,   // 0
    0, 1, 1, 0, 0, 0, 0,   // 1
    1, 1, 0, 1, 1, 0, 1,   // 2
    1, 1, 1, 1, 0, 0, 1,   // 3
    0, 1, 1, 0, 0, 1, 1,   // 4
    1, 0, 1, 1, 0, 1, 1,   // 5
    1, 0, 1, 1, 1, 1, 1,   // 6
    1, 1, 1, 0, 0, 1, 0,   // 7
    1, 1, 1, 1, 1, 1, 1,   // 8
    1, 1, 1, 1, 0, 1, 1,   // 9
  };

byte onOffTable_1[7 * 10] = {
    //A  B  C  D  E  F  G
    1, 1, 1, 1, 1, 1, 0,   // 0
    0, 1, 1, 0, 0, 0, 0,   // 1
    1, 1, 0, 1, 1, 0, 1,   // 2
    1, 1, 1, 1, 0, 0, 1,   // 3
    0, 1, 1, 0, 0, 1, 1,   // 4
    1, 0, 1, 1, 0, 1, 1,   // 5
    1, 0, 1, 1, 1, 1, 1,   // 6
    1, 1, 1, 0, 0, 1, 0,   // 7
    1, 1, 1, 1, 1, 1, 1,   // 8
    1, 1, 1, 1, 0, 1, 1,   // 9
  };

void displayNumber_10(int num){
  for (int i= 0; i< 7; i++){
    digitalWrite(pinNo_10[i], !onOffTable_10[num* 7 + i]);
    }} // displayNumber

void displayNumber_1(int num){
  for (int i= 0; i< 7; i++){
    digitalWrite(pinNo_1[i], !onOffTable_1[num* 7 + i]);
    }} // displayNumber

//加速度センサ

#include <Wire.h>
#include <ADXL345.h>

ADXL345 adxl;
int x, y, z, angle, count_train_pro;
int count_train = 0;
boolean step_1 = false;
boolean step_2 = false;

void setup() {
  Serial.begin(9600);
  adxl.powerOn();
  pinMode(PIN_LED_A_10, OUTPUT);  pinMode(PIN_LED_B_10, OUTPUT);
  pinMode(PIN_LED_C_10, OUTPUT);  pinMode(PIN_LED_D_10, OUTPUT);
  pinMode(PIN_LED_E_10, OUTPUT);  pinMode(PIN_LED_F_10, OUTPUT);
  pinMode(PIN_LED_G_10, OUTPUT);
  pinMode(PIN_LED_A_1, OUTPUT);  pinMode(PIN_LED_B_1, OUTPUT);
  pinMode(PIN_LED_C_1, OUTPUT);  pinMode(PIN_LED_D_1, OUTPUT);
  pinMode(PIN_LED_E_1, OUTPUT);  pinMode(PIN_LED_F_1, OUTPUT);
  pinMode(PIN_LED_G_1, OUTPUT);

  /* 初期状態をセットする(アノードコモンなのでHIGHで消灯) */
  digitalWrite(PIN_LED_A_10, HIGH);  digitalWrite(PIN_LED_B_10, HIGH);
  digitalWrite(PIN_LED_C_10, HIGH);  digitalWrite(PIN_LED_D_10, HIGH);
  digitalWrite(PIN_LED_E_10, HIGH);  digitalWrite(PIN_LED_F_10, HIGH);
  digitalWrite(PIN_LED_G_10, HIGH);
  digitalWrite(PIN_LED_A_1, HIGH);  digitalWrite(PIN_LED_B_1, HIGH);
  digitalWrite(PIN_LED_C_1, HIGH);  digitalWrite(PIN_LED_D_1, HIGH);
  digitalWrite(PIN_LED_E_1, HIGH);  digitalWrite(PIN_LED_F_1, HIGH);
  digitalWrite(PIN_LED_G_1, HIGH);
  }
  
void loop() {
  adxl.readXYZ(&x, &y, &z);
  
//  Serial.print(x);
//  Serial.print(" ");
//  Serial.print(y);
//  Serial.print(" ");
//  Serial.println(z);
//  Serial.print(" ");
  angle = (y+280)/3;
//  Serial.println(angle);
  Serial.write('H');             // ヘッダの送信
  Serial.write(highByte(angle)); // 上位バイトの送信
  Serial.write(lowByte(angle));  // 下位バイトの送信
  if (angle >= 150){
    step_1 = true;
  }else if(angle <= 120){
    step_2 = true;
  }

  if (step_1 && step_2){
    count_train = count_train + 1;
    step_1 = false;
    step_2 = false;
    }

  int digit[2];
  digit[0] = count_train % 10;
  count_train_pro = count_train / 10;
  digit[1] = count_train_pro % 10;
//  Serial.println(count_train);
  displayNumber_10(digit[1]);
  displayNumber_1(digit[0]);
  delay(500);
  }
