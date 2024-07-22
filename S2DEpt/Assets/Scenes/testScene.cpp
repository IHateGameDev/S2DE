#include <S2DEL/scene.hpp>

#include <S2DEL/Graphics/GUI/GUISystem.hpp>
#include <TGUI/Widgets/ChildWindow.hpp>


stde::Scene testScene;

std::unique_ptr<stde::GUISystem> guiSystem;

namespace testSceneRoot
{
  void Init()
  {
    guiSystem = std::make_unique<stde::GUISystem>(testScene.getGUI(), testScene.getRegistry());

    testScene.getGUI().loadWidgetsFromFile("Assets/Forms/halloWorld.tform");
  }

  void OnEvent(sf::Event event)
  {
    testScene.getGUI().handleEvent(event);
  }

  void OnDraw()
  {
    testScene.getGUI().draw();
  }

  void End()
  {
    testScene.getGUI().removeAllWidgets();
  }

  class FI
  {
    public:
      FI()
      {
        testScene.REGISTRY_CIF(Init);
        testScene.REGISTRY_COEF(OnEvent);
        testScene.REGISTRY_CODF(OnDraw);
        testScene.REGISTRY_CEF(End);
      }
  };
}
testSceneRoot::FI testSceneFI;