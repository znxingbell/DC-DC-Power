#include "pid.hpp"

class Controller {
public:
    void controller_init();
private:
    PID_TypeDef* Ipid;  // 电流PID控制器
    PID_TypeDef* Vpid;  // 电压PID控制器
};
