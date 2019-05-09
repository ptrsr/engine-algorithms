#include <gtest/gtest.h>

#include <engine/core/engine.hpp>

TEST(Component, AddComponent) {
    Engine engine = Engine();
    Entity& entity = engine.AddEntity<Entity>();
}
