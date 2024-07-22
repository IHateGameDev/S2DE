#ifndef SCENE_HPP
#define SCENE_HPP

#include "engine.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <functional>

namespace stde
{
  class Scene
  {
    private:
      entt::registry registry;
      sf::RenderWindow* renderWindow;
      tgui::Gui* guiSpace;

      std::vector<std::function<void()>> CustomInitFunctions;
      std::vector<std::function<void()>> CustomStartFunctions;
      std::vector<std::function<void(sf::Event&)>> CustomOnEventFunctions;
      std::vector<std::function<void(sf::Time)>> CustomUpdateFunctions;
      std::vector<std::function<void()>> CustomOnDrawFunctions;
      std::vector<std::function<void()>> CustomEndFunctions;

      ///def func
      void load(sf::RenderWindow& renderWindow, tgui::Gui& guiSpace)
      {
        this->renderWindow = &renderWindow;
        this->guiSpace = &guiSpace;
      }

      void Init()
      {
        for(uint32_t i = 0; i < CustomInitFunctions.size(); i++)
          CustomInitFunctions.at(i)();
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

      void End()
      {
        for(uint32_t i = 0; i < CustomEndFunctions.size(); i++)
          CustomEndFunctions.at(i)();
      }

    public:
      entt::registry& getRegistry()
      {return this->registry;}

      sf::RenderWindow& getWindow()
      {return *this->renderWindow;}

      tgui::Gui& getGUI()
      {return *this->guiSpace;}

    ///init func
      void REGISTRY_CIF(std::function<void()> func)
      {
        CustomInitFunctions.emplace_back(func);
      }

      void REGISTRY_CSF(std::function<void()> func)
      {
        CustomStartFunctions.emplace_back(func);
      }

      void REGISTRY_COEF(std::function<void(sf::Event&)> func)
      {
        CustomOnEventFunctions.emplace_back(func);
      }

      void REGISTRY_CUF(std::function<void(sf::Time)> func)
      {
        CustomUpdateFunctions.emplace_back(func);
      }

      void REGISTRY_CODF(std::function<void()> func)
      {
        CustomOnDrawFunctions.emplace_back(func);
      }

      void REGISTRY_CEF(std::function<void()> func)
      {
        CustomEndFunctions.emplace_back(func);
      }

      friend class GameEngine;
  };
}

#endif // !SCENE_HPP