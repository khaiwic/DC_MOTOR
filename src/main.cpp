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

    // 1. timerBegin(ID của Timer, Bộ chia Prescaler, Đếm tiến hay lùi)
    // - Dùng Timer số 0 (ESP32 có 4 timer từ 0 đến 3)
    // - Bộ chia 80: Ép xung 80MHz / 80 = 1MHz (1 micro-giây/nhịp)
    // - true: Đếm tiến (count up)
    TIMER = timerBegin(0, 80, true);
    
    // 2. Gắn hàm ngắt (Thêm chữ true ở cuối để ngắt theo sườn tín hiệu)
    timerAttachInterrupt(TIMER, &onTimer, true);
    
    // 3. Đặt báo thức (Dùng hàm timerAlarmWrite thay vì timerAlarm)
    // - 50000 micro-giây = 50 mili-giây
    // - true = tự động lặp lại báo thức
    timerAlarmWrite(TIMER, 50000, true);
    
    // 4. Phải có thêm lệnh này để kích hoạt báo thức chạy ngầm
    timerAlarmEnable(TIMER);

    Serial.println("Hệ thống sẵn sàng! Timer đang chạy ngầm...");
}
void loop() {

    Serial.println("Lệnh: Xe chạy thẳng 60%");
    target_speed = 100; 
    delay(5000);

    Serial.println("Lệnh: Xe phanh từ từ lại!");
    target_speed = 0;
    delay(5000);
}