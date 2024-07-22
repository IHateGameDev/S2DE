#ifndef GUISYS_GUISYSTEM_HPP
#define GUISYS_GUISYSTEM_HPP

#include "GUIWidget.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <entt/entt.hpp>

namespace stde
{
  class GUISystem
  {
    private:
      tgui::Gui& guiSpace;
      entt::registry& registry;

    public:
      GUISystem(tgui::Gui& guiSpace, entt::registry& registry)
        :guiSpace(guiSpace), registry(registry)
      {}

      template<typename WidgetType>
      void addWidgets()
      {
        auto view = this->registry.view<stde::GUIWidget<WidgetType>>();

        for(entt::entity entity : view)
        {
          stde::GUIWidget<WidgetType>& guiWidget = view.template get<stde::GUIWidget<WidgetType>>(entity);

          this->guiSpace.add(guiWidget.widget, guiWidget.name);
        }
      }
  };
}

#endif // !GUISYS_GUISYSTEM_HPP