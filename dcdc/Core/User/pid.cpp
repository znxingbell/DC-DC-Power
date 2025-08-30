#include "pid.hpp"


PID_TypeDef::PID_TypeDef(const PID_Config& config)
    : config(config), int_error(0.0f), pre_error(0.0f) {}

float32_t ki_output;

float32_t PID_TypeDef::PID_Calculate(float32_t set, float32_t ref) {
    float32_t error;
    float32_t output;
    
    
    error = set - ref;
    int_error += error;

    int_error = clamp(int_error, config.ki_min_out, config.ki_max_out);
    ki_output = config.ki * int_error;

    output = config.kp * error + ki_output + config.kd * (error - pre_error);
    pre_error = error;

    output = clamp(output, config.min_out, config.max_out);
    return output;
}