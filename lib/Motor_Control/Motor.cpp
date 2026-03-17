#include "Motor.h"

#define pwma 14
#define pwmb 13

#define ina_1 12
#define ina_2 11

#define inb_1 10
#define inb_2 9

#define STBY 4
#define pwma_channel 0
#define pwmb_channel 1

#define freq 20000 /// 50000 ///
#define resolution 10

const int NUM_POINTS = 11;

// Blan
int speed_percent[NUM_POINTS] = {0, 10, 20, 30, 40, 50, 60,70, 80, 90, 100};
int pwm_left[NUM_POINTS] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1023};
int pwm_right[NUM_POINTS] = {0, 50, 150, 200, 350, 500, 550, 700, 770, 880, 1023};

void initMotor_A(){
    pinMode(ina_1, OUTPUT);
    pinMode(ina_2, OUTPUT);
    ledcSetup(pwma_channel, freq, resolution);
    ledcAttachPin(pwma, pwma_channel);
}
void initMotor_B(){
    pinMode(inb_2, OUTPUT);
    pinMode(inb_2, OUTPUT);
    ledcSetup(pwmb_channel, freq, resolution);
    ledcAttachPin(pwmb, pwmb_channel);
}
void go(control next, int speed){
    int pwmRight = 0;
    int pwmLeft = 0;
    if(speed >= 100){
        ledcWrite(pwma_channel, 1023);
        ledcWrite(pwmb_channel, 1023);
    }
    else{
        int i = 0; 
        while(i < NUM_POINTS && speed > speed_percent[i + 1]){
            i++;
        }
        pwmRight = map(speed, speed_percent[i], speed_percent[i + 1], pwm_right[i], pwm_right[i + 1]);
        pwmLeft = map(speed, speed_percent[i], speed_percent[i + 1], pwm_left[i], pwm_left[i + 1]);
    }
    switch(next){
        case top:
            digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
            digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
            ledcWrite(pwma_channel, pwmRight);
            ledcWrite(pwmb_channel, pwmLeft);
            break;
            
        case back:
            digitalWrite(ina_1, LOW); digitalWrite(ina_2, HIGH);
            digitalWrite(inb_1, LOW); digitalWrite(inb_2, HIGH);
            ledcWrite(pwma_channel, pwmLeft);
            ledcWrite(pwmb_channel, pwmRight);
            break;
            
        case left: 
            digitalWrite(ina_1, LOW); digitalWrite(ina_2, LOW); 
            digitalWrite(inb_1, HIGH); digitalWrite(inb_2, LOW);
            ledcWrite(pwma_channel, 0); 
            ledcWrite(pwmb_channel, pwmRight); 
            break;
            
        case right: 
            digitalWrite(ina_1, HIGH); digitalWrite(ina_2, LOW);
            digitalWrite(inb_1, LOW); digitalWrite(inb_2, LOW);
            ledcWrite(pwma_channel, pwmLeft); 
            ledcWrite(pwmb_channel, 0);
            break;
            
        case stop:
        default:
            digitalWrite(ina_1, LOW); digitalWrite(ina_2, LOW);
            digitalWrite(inb_1, LOW); digitalWrite(inb_2, LOW);
            ledcWrite(pwma_channel, 0);
            ledcWrite(pwmb_channel, 0);
            break;
    }
}
