#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <iostream>

template <class... Ts>
class System {
public:
    virtual void Update(Ts... ts) = 0;

};

#endif//SYSTEM_HPP_
