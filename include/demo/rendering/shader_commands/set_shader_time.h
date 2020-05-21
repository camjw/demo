#ifndef DEMO_SET_SHADER_TIME_H
#define DEMO_SET_SHADER_TIME_H

#include <demo/constants/shader_constants.h>
#include <demo/rendering/shader.h>
#include <demo/templates/action.h>
#include <demo/timer.h>

class SetShaderTime : public Action<Shader>
{
public:
    SetShaderTime(Time time): time(time) {};
    void run(std::shared_ptr<Shader> shader);

private:
    Time time;
};

#endif // DEMO_SET_SHADER_TIME_H
