#include <S2DEL/scene.hpp>

stde::Scene testScene;

namespace testSceneRootFunctions
{
  void Init(entt::registry& registry, sfg::SFGUI& sfgui, sf::RenderWindow& renderWindow, b2World& physicWorld)
  {
    
  }
}

std::unique_ptr<stde::REGISTRY_CIF> testSceneAFR(std::make_unique<stde::REGISTRY_CIF>(testScene, testSceneRootFunctions::Init));