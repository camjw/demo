#include <demo/engine.hpp>
#include <demo/timer.hpp>

#include <chrono>
#include <cstdio>
#include <thread>

int main()
{
    Engine engine;

    const int UPDATE_FREQUENCY = 60;
    const float CYCLE_TIME = 1000.0f / UPDATE_FREQUENCY;

    static Timer system_timer;
    static Timer physics_timer;

    float accumulated_milliseconds = 0.0f;

    while (engine.is_running())
    {
        system_timer.tick();
        engine.process_input();
        accumulated_milliseconds += system_timer.get_time().delta_time;

        if (accumulated_milliseconds >= CYCLE_TIME)
        {
            accumulated_milliseconds -= CYCLE_TIME;

            physics_timer.tick();

            Time time = physics_timer.get_time();
            engine.update(time);

            engine.late_update(time);

            engine.draw();
        }
    }
}
