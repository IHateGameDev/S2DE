#ifndef WINDOWPAINTER_HPP
#define WINDOWPAINTER_HPP

#include "Drawable.hpp"

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

namespace stde
{
  class WindowPainter
  {
    private:
      sf::RenderWindow& renderWindow;
      entt::registry& registry;

    public:
      WindowPainter() = default;

      WindowPainter(entt::registry& registry, sf::RenderWindow& renderWindow)
        :registry(registry), renderWindow(renderWindow)
      {}

      template<typename DrawableType>
      void drawSFML()
      {
        auto view = this->registry.view<stde::Drawable<DrawableType>>();

        for(entt::entity entity : view)
        {
          stde::Drawable<DrawableType>& drawC = view.template get<stde::Drawable<DrawableType>>(entity);

          this->renderWindow.draw(drawC.drawTarget);
        }
      }
  };
}

#endif // !WINDOWPAINTER_HPP
