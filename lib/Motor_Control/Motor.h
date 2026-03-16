#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

void initMotor_A();
void initMotor_B();
void stopMotor();
void forWard(int speed);
void backward(int speed);
void left(int speed);
void right(int speed);
void contol(int speed);
#endif