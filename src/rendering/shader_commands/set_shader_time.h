#ifndef DEMO_SET_SHADER_TIME_H
#define DEMO_SET_SHADER_TIME_H

#include <constants/shader_constants.h>
#include <rendering/shader.h>
#include <templates/action.h>
#include <timer.h>

class SetShaderTime
{
public:
    SetShaderTime(Time time)
        : time(time) {};

    inline void operator()(std::shared_ptr<Shader> shader)
    {
        shader->bind();
        shader->set_float(DEMO_CONSTANTS_TOTAL_TIME, time.total_time);
        shader->set_float(DEMO_CONSTANTS_DELTA_TIME, time.delta_time);
    }

private:
    Time time;
};

#endif // DEMO_SET_SHADER_TIME_H
