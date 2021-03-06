#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "constants.h"


class CameraPane
{
public:

   static CameraPane& getInstance();

   void update();
   void updateLookState(Look look, bool enable);

   bool isLookActive() const;
   const sf::Vector2f& getLookVector() const;


private:

   CameraPane() = default;

   int32_t mLook = LookInactive;
   sf::Vector2f mLookVector;

   static CameraPane sInstance;
};

