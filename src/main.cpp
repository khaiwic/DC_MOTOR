#include <Arduino.h>
#include "Motor.h"

hw_timer_t *TIMER = NULL;
volatile int target_speed = 0;
volatile int current_speed = 0;
volatile control current_next = stop;

void IRAM_ATTR onTimer(){
    if(current_speed < target_speed){
        current_speed++;
    }
    else if(current_speed > target_speed){
        current_speed--;
    }
    go(current_next, current_speed);
}
void setup(){
    Serial.begin(115200);
    initMotor_A();
    initMotor_B();

    TIMER = timerBegin(0, 80, true);
    timerAttachInterrupt(TIMER, &onTimer, true);
    timerAlarmWrite(TIMER, 50000, true);
    timerAlarmEnable(TIMER);

    Serial.println("Hệ thống sẵn sàng! Timer đang chạy ngầm...");
}

void loop() {
    Serial.println("Lệnh: Tiến thẳng 60%");
    current_next = top;
    target_speed = 60; 
    delay(5000);

    Serial.println("Lệnh: Rẽ trái 40%");
    current_next = left;
    target_speed = 40; 
    delay(3000);

    Serial.println("Lệnh: Lùi 50%");
    current_next = back;
    target_speed = 50; 
    delay(4000);

    Serial.println("Lệnh: Phanh dừng lại!");
    target_speed = 0; 
    delay(5000);
}