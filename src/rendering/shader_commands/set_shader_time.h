#ifndef DEMO_SET_SHADER_TIME_H
#define DEMO_SET_SHADER_TIME_H

#include <constants/shader_constants.h>
#include <templates/action.h>
#include <rendering/shader.h>
#include <timer.h>

class SetShaderTime : public Action<Shader>
{
public:
    SetShaderTime(Time time): time(time) {};
    void run(std::shared_ptr<Shader> shader);

private:
    Time time;
};

#endif // DEMO_SET_SHADER_TIME_H
