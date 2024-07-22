#ifndef WIDGET_GUIWIDGET_HPP
#define WIDGET_GUIWIDGET_HPP

#include <string>

namespace stde
{
  template<typename WidgetType>
  struct GUIWidget
  {
    typename WidgetType::Ptr widget;
    std::string name;

    GUIWidget(const std::string& name)
      :name(name)
    {}

    void create()
    {widget = WidgetType::create();}
  };
}

#endif // !WIDGET_GUIWIDGET_HPP
