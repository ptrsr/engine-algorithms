#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_


struct Context;

class System {
public:
    bool enabled;
    virtual void Update(Context& scene) = 0;


};

#endif//SYSTEM_HPP_
