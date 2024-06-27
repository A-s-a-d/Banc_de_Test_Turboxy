#ifndef SERVO_RACK_H
#define SERVO_RACK_H

#include <Arduino.h>
#include <Servo.h>

#define Servo_pin 6
#define distance_max 20
#define distance_min 10

#define servo_position_repos 10
#define servo_position_test 15

class Servo_rack : public Servo
{
private:
    float _degree;
    float _distance;
    float _equation_distance_info_degree(float degree);
    float _equation_degree_info_distance(float distance);

public:
    Servo_rack(/* args */);
    void begin();
    void move_in_place(float distance);
};

#endif