#ifndef PROFILER_HPP_
#define PROFILER_HPP_

#include <engine/core/entity.hpp>
#include <engine/components/timer.hpp>

class Profiler : public Entity {
public:
    Timer& timer;

    Profiler(const unsigned id)
        : Entity(id)
        , timer(AddComponent<Timer>())
        { }
};

#endif//PROFILER_HPP_
