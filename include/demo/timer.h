#ifndef DEMO_TIMER_HPP
#define DEMO_TIMER_HPP

#include <chrono>
#include <iostream>
#include <thread>

struct Time
{
    float delta_time;
    float total_time;
};

struct Timer
{
    std::chrono::high_resolution_clock::time_point start_ticks = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point previous_ticks = std::chrono::high_resolution_clock::now();

    float frame_milliseconds = 0.0f;
    float milliseconds_since_start = 0.0f;

    void tick()
    {
        std::chrono::high_resolution_clock::time_point current_ticks = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> frame_duration = current_ticks - previous_ticks;
        previous_ticks = current_ticks;

        frame_milliseconds = frame_duration.count();

        std::chrono::duration<float, std::milli> duration_since_start = current_ticks - start_ticks;
        milliseconds_since_start = duration_since_start.count();
    }

    Time get_time()
    {
        return { frame_milliseconds, milliseconds_since_start };
    }
};

#endif
