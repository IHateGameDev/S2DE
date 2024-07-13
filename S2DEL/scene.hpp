#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <box2d/box2d.h>
#include <entt/entt.hpp>
#include <functional>


namespace stde
{
  class Scene
  {
  private:
    sfg::SFGUI sfgui;
    b2World physicsWorld;
    entt::registry registry;

    std::vector<std::function<void(entt::registry&, sfg::SFGUI&, sf::RenderWindow&, b2World&)>> CustomInitFunctions;
    std::vector<std::function<void()>> CustomStartFunctions;
    std::vector<std::function<void(sf::Event&)>> CustomOnEventFunctions;
    std::vector<std::function<void(sf::Time dt)>> CustomUpdateFunctions;
    std::vector<std::function<void()>> CustomOnDrawFunctions;

  public:
    Scene() : physicsWorld(b2Vec2(0.0f, -9.8f)) {}

    void Init(sf::RenderWindow& renderWindow)
    {
      for(uint32_t i = 0; i < CustomInitFunctions.size(); i++)
        CustomInitFunctions.at(i)(this->registry, this->sfgui, renderWindow, this->physicsWorld);
    }

    void Start()
    {
      for(uint32_t i = 0; i < CustomStartFunctions.size(); i++)
        CustomStartFunctions.at(i)();
    }

    void OnEvent(sf::Event& event)
    {
      for(uint32_t i = 0; i < CustomOnEventFunctions.size(); i++)
        CustomOnEventFunctions.at(i)(event);
    }

    void Update(sf::Time dt)
    {
      for(uint32_t i = 0; i < CustomUpdateFunctions.size(); i++)
        CustomUpdateFunctions.at(i)(dt);
    }

    void OnDraw()
    {
      for(uint32_t i = 0; i < CustomOnDrawFunctions.size(); i++)
        CustomOnDrawFunctions.at(i)();
    }

    friend class REGISTRY_CIF;
    friend class REGISTRY_CSF;
    friend class REGISTRY_COEF;
    friend class REGISTRY_CUF;
    friend class REGISTRY_CODF;
  };

  class REGISTRY_CIF
  {
    public:
      ~REGISTRY_CIF() = default;
      REGISTRY_CIF(Scene& scene, std::function<void(entt::registry&, sfg::SFGUI&, sf::RenderWindow&, b2World&)> func)
      {
        scene.CustomInitFunctions.emplace_back(func);
      }
  };

  class REGISTRY_CSF
  {
    public:
      ~REGISTRY_CSF() = default;
      REGISTRY_CSF(Scene& scene, std::function<void()> func)
      {
        scene.CustomStartFunctions.emplace_back(func);
      }
  };

  class REGISTRY_COEF
  {
    public:
      ~REGISTRY_COEF() = default;
      REGISTRY_COEF(Scene& scene, std::function<void(sf::Event&)> func)
      {
        scene.CustomOnEventFunctions.emplace_back(func);
      }
  };

  class REGISTRY_CUF
  {
    public:
      ~REGISTRY_CUF() = default;
      REGISTRY_CUF(Scene& scene, std::function<void(sf::Time)> func)
      {
        scene.CustomUpdateFunctions.emplace_back(func);
      }
  };

  class REGISTRY_CODF
  {
    public:
      ~REGISTRY_CODF() = default;
      REGISTRY_CODF(Scene& scene, std::function<void()> func)
      {
        scene.CustomOnDrawFunctions.emplace_back(func);
      }
  };
}

#endif // !SCENE_HPP