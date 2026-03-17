#include <Arduino.h>
#include "Motor.h"
#include "Matrix_button.h"

#define ar 37

int state = 0;

char save[ar];
int walk = 0;

enum State{IDLE, RECORD, PLAYING, ERROR_STATE};
State current_state = IDLE;

char lastscan = {'0'};
char lastkhai = {'0'};

unsigned long pressTimeState = 0;

void run(){
  char khai = scanMatrix();
  if(khai != '0'){
    if(khai == lastscan){
      if(millis() - pressTimeState > 5000){
        current_state = ERROR_STATE;
      }
      else{
        pressTimeState = millis();
        lastscan = khai;
      }
      lastscan = '0';
    }
    if(current_state == ERROR_STATE){
        //change ham
      delay(1000);
    }
    if(khai == '='){
      current_state = IDLE;
      walk = 0;
      Serial.println("EXIT ERROR");
      delay(300);
    }
    return;
  }
  if(khai != lastkhai){
    delay(50);
    khai = scanMatrix();
    if(khai != '0'){
      switch(current_state){
        case IDLE:
          Serial.println("Chế độ chờ");
          walk = 0;
          delay(400);
        case RECORD:
          if(khai == '='){
            current_state = PLAYING;
            Serial.println("Chuyến sang chế độ phát");
            delay(300);
          }
          else{
            if (walk > 0){
              char BuocTruoc = save[walk - 1];
              if((BuocTruoc == 'B' && save[walk] == 'T') ||
                (BuocTruoc == 'T' && save[walk] == 'B') ||
                (BuocTruoc == 'L' && save[walk] == 'R') ||
                (BuocTruoc == 'R' && save[walk] == 'L')){
                  current_state = ERROR_STATE;
                  break;
                }
            }
            if(walk < ar){
              save[walk] = khai;
              Serial.println("Bấm nút: ");
              Serial.println(save[walk]);
              walk++;
              delay(500);
            }
          }
          break;
      }
    }
    lastkhai = khai;
  }
  if(current_state == PLAYING){
    for(int i = 0; i < walk; i++){
        // change  ham
      delay(1000);
    }
    current_state = IDLE;
    delay(300);
  }
}

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

}