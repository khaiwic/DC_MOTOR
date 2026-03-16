#include <Arduino.h>
#include "Motor.h"

hw_timer_t *TIMER = NULL;
volatile int target_speed = 0;
volatile int current_speed = 0;

void IRAM_ATTR onTimer(){
    if(current_speed < target_speed){
        current_speed++;
    }
    else if(current_speed > target_speed){
        current_speed--;
    }
    control(current_speed);
}
void setup(){
    Serial.begin(115200);
    initMotor_A();
    initMotor_B();

    TIMER = timerBegin(1000000);
    TIMER = timerAttachInterrupt(TIMER, &onTimer);
    timerAlarm(TIMER, 50000, true, 0);
    Serial.println("Hệ thống sẵn sàng! Timer đang chạy ngầm...");
}
void loop() {

    Serial.println("Lệnh: Xe chạy thẳng 60%");
    target_speed = 1000; 
    delay(5000);

    Serial.println("Lệnh: Xe phanh từ từ lại!");
    target_speed = 0;
    delay(5000);
}