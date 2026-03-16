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

#define freq 50000
#define resolution 10

const int NUM_POINTS = 11;

int speed_percent[NUM_POINTS] = {0, 10, 20, 30, 40, 50, 60,70, 80, 90, 100};
int pwm_left[NUM_POINTS] = {0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1023};
int pwm_right[NUM_POINTS] = {0, 50, 150, 200, 350, 500, 550, 700, 770, 880, 1023};

void initMotor_A(){
    ledcSetup(pwma, freq, resolution);
    ledcAttachPin(pwma, pwma_channel);
}
void initMotor_B(){
    ledcSetup(pwmb, freq, resolution);
    ledcAttachPin(pwmb, pwmb_channel);
}
void forward(int speed){
    digitalWrite(ina_1, HIGH);
    digitalWrite(ina_2, LOW);
    digitalWrite(inb_1, HIGH);
    digitalWrite(inb_2, LOW);
    ledcWrite(pwma, speed);
    ledcWrite(pwmb, speed);
}
void backward(int speed){
    digitalWrite(ina_1, LOW);
    digitalWrite(ina_2, HIGH);
    digitalWrite(inb_1, LOW);
    digitalWrite(inb_2, HIGH);
    ledcWrite(pwma, speed);
    ledcWrite(pwmb, speed);   
}
void right(int speed){
    digitalWrite(ina_1, HIGH);
    digitalWrite(ina_2, LOW);
    digitalWrite(inb_1, LOW);
    digitalWrite(inb_2, LOW);
    ledcWrite(pwma, speed);
    ledcWrite(pwmb, 0);
}
void left(int speed){
    digitalWrite(ina_1, LOW);
    digitalWrite(ina_2, LOW);
    digitalWrite(inb_1, HIGH);
    digitalWrite(inb_2, LOW);
    ledcWrite(pwma, 0);
    ledcWrite(pwmb, speed);
}
void stopMotor(int speed){
    digitalWrite(ina_1, LOW);
    digitalWrite(ina_2, LOW);
    digitalWrite(inb_1, LOW);
    digitalWrite(inb_2, LOW);
    ledcWrite(pwma, 0);
    ledcWrite(pwmb, 0);
}
void control(int speed){
    if(speed <= 0){
        ledcWrite(pwma, 0);
        ledcWrite(pwmb, 0);
        return;
    }
    if(speed > 0){
        ledcWrite(pwma, 1023);
        ledcWrite(pwmb, 1023);
    }
    int i = 0;
    while (i < NUM_POINTS - 1 && speed > speed_percent[i + 1]) {
        i++;
    }
    int pwm_L = map(speed, speed_percent[i], speed_percent[i + 1], pwm_left[i], pwm_left[i + 1]);
    int pwm_R = map(speed, speed_percent[i], speed_percent[i + 1], pwm_right[i], pwm_right[i + 1]);
    ledcWrite(pwma, pwm_L);
    ledcWrite(pwmb, pwm_R);
}