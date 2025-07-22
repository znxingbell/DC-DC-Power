#include "controller.hpp"
#include "oled.hpp"
#include "hrtim_manager.hpp"

void Controller::controller_init() {
    // 初始化PID控制器
    PID_Config Ipid_config{0.0046035f, 41.8663f, 0.0f, 1.0f, -1.0f, 1.0f, -1.0f};
    Ipid = new PID_TypeDef(Ipid_config);
    PID_Config Vpid_config{0.295160f, 20.9333f, 0.0f, 1.0f, -1.0f, 1.0f, -1.0f};
    Vpid = new PID_TypeDef(Vpid_config);
    // 初始化控制模式
    mode = ControllerMode::CURRENT;
    OLED_ShowString(1, 1, "Mode: Current");
    OLED_ShowString(2, 1, "SetI:+0.5A");
    OLED_ShowString(3, 1, "vi");
    OLED_ShowString(3, 9, "vo");
    OLED_ShowString(4, 1, "ih");
    // 初始化设定点
    current_setpoint = 0.5f;  // 初始电流设定点
    voltage_setpoint = 30.0f; // 初始电压设定点
}

void Controller::implement_control(float32_t vhs, float32_t vls, float32_t is) {
    
    SetCompareValue(TOTAL_COUNTER/8, TOTAL_COUNTER*7/8);
    // 根据当前控制模式进行控制
    // if (mode == ControllerMode::CURRENT) {
    //     // 电流控制逻辑
    //     if(vls > 21.0f) { //锂电池过压保护
    //         current_setpoint = 0.0f;
    //         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    //     }
        
    //     float32_t duty_ratio = Ipid->PID_Calculate(current_setpoint, is);
    //     uint32_t pwm_value = static_cast<uint32_t>(duty_ratio * TOTAL_COUNTER);
    //     SetCompareValue(TOTAL_COUNTER/2 - pwm_value, TOTAL_COUNTER/2 + pwm_value);

    // } else if (mode == ControllerMode::VOLTAGE) {
    //     // 电压控制逻辑
    //     float32_t duty_ratio = Ipid->PID_Calculate(current_setpoint, is);
    //     uint32_t pwm_value = static_cast<uint32_t>(duty_ratio * TOTAL_COUNTER);
    //     SetCompareValue(TOTAL_COUNTER/2 - pwm_value, TOTAL_COUNTER/2 + pwm_value);
    //     current_setpoint = Vpid->PID_Calculate(voltage_setpoint, vls);

    // }

}

void Controller::ToggleMode() {
    if (mode == ControllerMode::CURRENT) {
        mode = ControllerMode::VOLTAGE;
        OLED_ShowString(1, 7, "Voltage");
        OLED_ShowFloat(2, 7, voltage_setpoint, 2);
        OLED_ShowChar(2, 4, 'V');

    } else {
        mode = ControllerMode::CURRENT;
        current_setpoint = 0.5f;
        OLED_ShowString(1, 7, "Current");
        OLED_ShowFloat(2, 7, current_setpoint, 1);
        OLED_ShowChar(2, 4, 'I');

    }
}

void Controller::AddCureent(){
    current_setpoint += 0.1f;
    OLED_ShowFloat(2, 7, current_setpoint, 1);
}

void Controller::MinusCurrent(){
    current_setpoint -= 0.1f;
    OLED_ShowFloat(2, 7, current_setpoint, 1);
}



Controller controller;

