#include <S2DEL/scene.hpp>

stde::Scene testScene;

namespace testSceneRootFunctions
{
  void Init(entt::registry& registry, sfg::SFGUI& sfgui, sf::RenderWindow& renderWindow, b2World& physicWorld)
  {

  }

  void OnDraw()
  {

  }
}

std::unique_ptr<stde::REGISTRY_CIF> testSceneAFR(std::make_unique<stde::REGISTRY_CIF>(testScene, testSceneRootFunctions::Init));
std::unique_ptr<stde::REGISTRY_CODF> testSceneODFR(std::make_unique<stde::REGISTRY_CODF>(testScene, testSceneRootFunctions::OnDraw));