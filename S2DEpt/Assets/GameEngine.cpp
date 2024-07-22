#ifndef GAMEENGINE_CPP
#define GAMEENGINE_CPP

#include <S2DEL/engine.hpp>
#include "Scenes/testScene.cpp"

stde::Scene* scenes[] = {&testScene};
stde::GameEngine testGame(scenes, 1u, sf::VideoMode(1920, 1980), "testGame");

#endif // !GAMEENGINE_CPP