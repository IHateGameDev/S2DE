#ifndef GAMEENGINE_ENGINE_HPP
#define GAMEENGINE_ENGINE_HPP

#include "scene.hpp"
#include <vector>

namespace stde
{
  class GameEngine
  {
  private:
    uint16_t playedScene;

    Scene** scenes;
    uint16_t sceneCount;

    sf::RenderWindow renderWindow;
    sf::Clock clock;

    tgui::Gui guiSpace;

  public:
    GameEngine(Scene** scenes, uint16_t sceneCount, sf::VideoMode videoMode, const sf::String& title, uint16_t startScene = 0u, sf::Uint32 style = 7u)
      : scenes(scenes), sceneCount(sceneCount), playedScene(startScene)
    {
      this->renderWindow.create(videoMode, title, style);

      guiSpace.setTarget(this->renderWindow);

      if (playedScene >= sceneCount)
        playedScene = 0;
    }

    int play()
    {
      for (uint16_t i = 0; i < sceneCount; i++)
      {
        scenes[i]->load(this->renderWindow, this->guiSpace);
        scenes[i]->Init();
      }

      scenes[playedScene]->Start();

      while (this->renderWindow.isOpen())
      {
        sf::Event event;

        while (this->renderWindow.pollEvent(event))
        {
          if (event.type == sf::Event::Closed)
            renderWindow.close();

          this->scenes[playedScene]->OnEvent(event);
        }

        this->scenes[playedScene]->Update(clock.restart());

        this->renderWindow.clear();

        this->scenes[playedScene]->OnDraw();

        this->renderWindow.display();
      }

      return 0;
    }

    void launchScene(uint16_t Id)
    {
      if (Id < sceneCount)
      {
        this->scenes[playedScene]->End();
        
        this->playedScene = Id;

        this->scenes[playedScene]->Start();
      }
    }
  };
}

#endif // GAMEENGINE_ENGINE_HPP