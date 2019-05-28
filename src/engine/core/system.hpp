#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <memory>

struct Context;

class Engine;

class System {
friend class Engine;
friend std::unique_ptr<System>::deleter_type;

public:
    bool enabled;
    virtual void Update(Context& scene) = 0;


};

#endif//SYSTEM_HPP_
