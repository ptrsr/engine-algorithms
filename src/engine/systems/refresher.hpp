#ifndef REFRESHER_HPP_
#define REFRESHER_HPP_

#include <engine/core/system.hpp>

class Projection;
class Window;


class Refresher : public System {
private:
    void UpdateScreenSize(Projection& projection, const Window& window) const;

public:
    void Update(UpdateContext& context) override;
};

#endif//REFRESHER_HPP_
