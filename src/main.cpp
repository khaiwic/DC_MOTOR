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

    // THÊM 3 DÒNG NÀY ĐỂ RA LỆNH CHO XE CHẠY:
    delay(3000);         // Đợi 3 giây để bạn kịp đặt xe xuống đất
    current_next = top;  // Cài số tiến
    target_speed = 100;   // Đặt mục tiêu lên ga 50%
}

void loop() {

}