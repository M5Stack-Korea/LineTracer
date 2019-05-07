#include <M5Stack.h>

/*=============================================================
 define M5STACK IR Sensor position
=============================================================*/
#define x_1       40
#define x_2       120
#define x_3       200
#define x_4       280

#define y_1       150
#define radius    10
/*=============================================================
 define for motor Right Left Direction and Speed
=============================================================*/
#define MotorEn       17
#define MotorR_Dir    2
#define MotorR_Pulse  5
#define MotorL_Dir    21
#define MotorL_Pulse  22

//=======Motor Right ===========================================
#define MotorR_CCW         digitalWrite(MotorR_Dir, HIGH);
#define MotorR_CW        digitalWrite(MotorR_Dir, LOW);
#define MotorR_Pulse_High digitalWrite(MotorR_Pulse, HIGH);
#define MotorR_Pulse_Low  digitalWrite(MotorR_Pulse, LOW);
//=======Motor Left ===========================================
#define MotorL_CW         digitalWrite(MotorL_Dir, HIGH);
#define MotorL_CCW        digitalWrite(MotorL_Dir, LOW);
#define MotorL_Pulse_High digitalWrite(MotorL_Pulse, HIGH);
#define MotorL_Pulse_Low  digitalWrite(MotorL_Pulse, LOW);

#define MotorEnable       digitalWrite(MotorEn, HIGH);
#define MotorDisable       digitalWrite(MotorEn, LOW);
/*=============================================================
 define IR sensor position
 * IR Sensor
   |--------------------------------------------------------|
   |    o           o                  o          o         |
   | IR_Left_2  IR_Left_1   center  IR_Right_1  IR_Right_2  |
   |   pin16     pin26                pin35       pin36     |
   |----------------------|      |--------------------------|
                          |      |      
=============================================================*/
#define IR_Left_2 16
#define IR_Left_1 26
#define IR_Right_1 35
#define IR_Right_2 36

unsigned char L_pulse_High = true;
unsigned char R_pulse_High = true;

unsigned char Left_timer = 1;
unsigned char Right_timer = 1;
uint8_t Initial_Set=0;


void task1(void * pvParameters) {

    for(;;) {    
        if (L_pulse_High == true){
            MotorL_Pulse_High;
            L_pulse_High = false;
            delay(1);
        }else{
            MotorL_Pulse_Low;
            L_pulse_High = true;
            delay(Left_timer);
        }        
    }
}

void task2(void * pvParameters) {

    for(;;) { 
        if (R_pulse_High == true){
            R_pulse_High = false;
            MotorR_Pulse_High;
            delay(1);
        }else{
            R_pulse_High = true;
            MotorR_Pulse_Low;
            delay(Right_timer);
        } 
    }
}


void task3(void * pvParameters) {
  
int IR_Left_2_Value=  LOW;
int IR_Left_1_Value=  LOW;
int IR_Right_1_Value= LOW; 
int IR_Right_2_Value= LOW;
int IR_Right_1_AdValue, IR_Right_2_AdValue=0;
int IR_Left_1_AdValue, IR_Left_2_AdValue=0;

    for(;;) {
                IR_Left_2_Value = digitalRead(IR_Left_2);
             
                IR_Left_1_AdValue= analogRead(IR_Left_1); 
                if(IR_Left_1_AdValue > 4000) IR_Left_1_Value=HIGH;
                else IR_Left_1_Value=LOW;
               
                IR_Right_1_AdValue= analogRead(IR_Right_1); 
                if(IR_Right_1_AdValue > 4000) IR_Right_1_Value=HIGH;
                else IR_Right_1_Value=LOW;
                
                IR_Right_2_AdValue= analogRead(IR_Right_2);
                if(IR_Right_2_AdValue > 4000) IR_Right_2_Value=HIGH;
                else IR_Right_2_Value=LOW;

                // Serial.print(IR_Left_2_Value);Serial.print(IR_Left_1_Value); Serial.print(IR_Right_1_Value); Serial.println(IR_Right_2_Value);
                
                if      ((IR_Left_2_Value==HIGH) && (IR_Left_1_Value==HIGH) && (IR_Right_1_Value==HIGH) && (IR_Right_2_Value==HIGH)){
                    MotorEnable;
                    Right_timer= 2;
                    Left_timer = 2;
                    M5.Lcd.fillCircle(x_1, y_1, radius, WHITE);    
                    M5.Lcd.fillCircle(x_2, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_3, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_4, y_1, radius, WHITE);                 
                }else if((IR_Left_2_Value==HIGH) && (IR_Left_1_Value==LOW) && (IR_Right_1_Value==HIGH) && (IR_Right_2_Value==HIGH)){
                    MotorEnable;                  
                    Right_timer= 2; 
                    Left_timer = 5; 
                    M5.Lcd.fillCircle(x_1, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_2, y_1, radius, RED);
                    M5.Lcd.fillCircle(x_3, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_4, y_1, radius, WHITE);
                }else if((IR_Left_2_Value==LOW) && (IR_Left_1_Value==HIGH) && (IR_Right_1_Value==HIGH) && (IR_Right_2_Value==HIGH)){
                    MotorEnable;                  
                    Right_timer= 2; 
                    Left_timer = 10;
                    M5.Lcd.fillCircle(x_1, y_1, radius, RED);
                    M5.Lcd.fillCircle(x_2, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_3, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_4, y_1, radius, WHITE);
                }else if((IR_Left_2_Value==HIGH) && (IR_Left_1_Value==HIGH) && (IR_Right_1_Value==LOW) && (IR_Right_2_Value==HIGH)){
                    MotorEnable;
                    Right_timer= 5; 
                    Left_timer = 2;                   
                    M5.Lcd.fillCircle(x_1, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_2, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_3, y_1, radius, RED);
                    M5.Lcd.fillCircle(x_4, y_1, radius, WHITE);           
                }else if((IR_Left_2_Value==HIGH) && (IR_Left_1_Value==HIGH) && (IR_Right_1_Value==HIGH) && (IR_Right_2_Value==LOW)){
                    MotorEnable;                  
                    Right_timer= 10; 
                    Left_timer =2;  
                    M5.Lcd.fillCircle(x_1, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_2, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_3, y_1, radius, WHITE);
                    M5.Lcd.fillCircle(x_4, y_1, radius, RED);                    
                }else if((IR_Left_2_Value==LOW) && (IR_Left_1_Value==LOW) && (IR_Right_1_Value==LOW) && (IR_Right_2_Value==LOW)){
                    MotorDisable;
                    Right_timer= 2; 
                    Left_timer =2;
                    M5.Lcd.fillCircle(x_1, y_1, radius, RED);
                    M5.Lcd.fillCircle(x_2, y_1, radius, RED);
                    M5.Lcd.fillCircle(x_3, y_1, radius, RED);
                    M5.Lcd.fillCircle(x_4, y_1, radius, RED);
                }
        delay(100);
    }
}


void setup() {
    M5.begin();
    M5.Lcd.clear(BLACK);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(65, 10);
    M5.Lcd.println("Line Scaner");
    M5.Lcd.setTextSize(2);    
    M5.Lcd.setCursor(55, 35);
    M5.Lcd.println("name: Go-Go-Sing");

    pinMode(MotorR_Dir, OUTPUT);
    pinMode(MotorR_Pulse, OUTPUT);  
    pinMode(MotorL_Dir, OUTPUT);
    pinMode(MotorL_Pulse, OUTPUT);  
    pinMode(MotorEn, OUTPUT); 

    pinMode(IR_Left_1, INPUT);
    pinMode(IR_Left_2, INPUT);  
    pinMode(IR_Right_1, INPUT);
    pinMode(IR_Right_2, INPUT);  

    M5.Lcd.setCursor(0, 60);
    M5.Lcd.printf("Start: press A_button");

    while (Initial_Set==0){
        if (M5.BtnA.wasPressed()){
            Initial_Set=1;
            goto main_task_creat;
        }
        M5.update();    //M5.BtnA.wasPressed() <-----
    }

main_task_creat:

    M5.Lcd.clear(BLACK);
    M5.Lcd.setCursor(30, 60);  
    M5.Lcd.print("^______________^a");

    MotorL_CW;
    MotorR_CW;
    MotorEnable;


   
    // Task 1
    xTaskCreatePinnedToCore(
                    task1,     /* Function to implement the task */
                    "task1",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    1,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    0);        /* Core where the task should run */

    // Task 2
    xTaskCreatePinnedToCore(
                    task2,     /* Function to implement the task */
                    "task2",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    2,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    0);        /* Core where the task should run */

    // Task 3
    xTaskCreatePinnedToCore(
                    task3,     /* Function to implement the task */
                    "task3",   /* Name of the task */
                    4096,      /* Stack size in words */
                    NULL,      /* Task input parameter */
                    3,         /* Priority of the task */
                    NULL,      /* Task handle. */
                    0);        /* Core where the task should run */
}

void loop() {

    M5.update();
}
