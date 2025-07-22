#pragma once
#include "main.h"
#include "pid.hpp"

enum class ControllerMode : uint8_t {
    CURRENT = 0,  // 电流控制
    VOLTAGE = 1,   // 电压控制
};

class Controller {
public:
    static constexpr uint32_t TOTAL_COUNTER = 46080;
    void controller_init();
    void implement_control(float32_t vhs, float32_t vls, float32_t is);
    void ToggleMode();
    void AddCureent();
    void MinusCurrent();
private:
    PID_TypeDef* Ipid;  // 电流PID控制器
    PID_TypeDef* Vpid;  // 电压PID控制器
    float32_t current_setpoint;
    float32_t voltage_setpoint;
    ControllerMode mode;  // 控制模式
};

extern Controller controller;