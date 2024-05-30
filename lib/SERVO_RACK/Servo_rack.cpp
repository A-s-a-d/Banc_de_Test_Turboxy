#include "Servo_rack.h"

Servo_rack::Servo_rack()
{
    _degree = 0;
    _distance = 0;
}

void Servo_rack::begin()
{
    attach(Servo_pin);
    move_in_place(20);
}

void Servo_rack::move_in_place(float distance)
{
    _distance = distance;
    if (_distance < distance_min && _distance > distance_max)
    {
        Serial.print("error");
        return;
    }
    else
    {
        _degree = _equation_degree_info_distance(_distance);
        
        write(_degree);
        delay(1000);
    }
}

float Servo_rack::_equation_distance_info_degree(float degree)
{
    return 28 - 0.1555556 * degree;
}
float Servo_rack::_equation_degree_info_distance(float distance)
{
    return 180 - 6.42857 * distance;
}
