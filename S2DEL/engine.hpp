#ifndef GAMEENGINE_ENGINE_HPP
#define GAMEENGINE_ENGINE_HPP

#include "scene.hpp"

namespace stde
{
  class GameEngine
  {
    private:
      uint16_t playedScene;

      sf::RenderWindow renderWindow;
      sf::Clock clock;

      stde::Scene** scenes;

    public:
      GameEngine(stde::Scene** scenes, sf::VideoMode videoMode, const sf::String& title, uint16_t startScene = 0u, sf::Uint32 style = 7u)
        :scenes(scenes), playedScene(startScene)
      {this->renderWindow.create(videoMode, title, style);}

      int play()
      {
        for(uint16_t i = 0; i < sizeof(this->scenes) / sizeof(this->scenes[0]); i++)
          this->scenes[i]->Init(this->renderWindow);

        this->scenes[playedScene]->Start();

        while(this->renderWindow.isOpen())
        {
          sf::Event event;
          while(this->renderWindow.pollEvent(event))
          {
            if(event.type == sf::Event::Closed)
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
        this->playedScene = Id;
        this->scenes[playedScene]->Start();
      }
  };
}

#endif //GAMEENGINE_ENGINE_HPP