#ifndef WORLD_PHYSICSWORLD_HPP
#define WORLD_PHYSICSWORLD_HPP

#include <box2d/b2_world.h>

namespace stde
{
  struct PhysicsWorld
  {
    b2World world;
  };

  using World = PhysicsWorld;
}

#endif // !WORLD_PHYSICSWORLD_HPP
