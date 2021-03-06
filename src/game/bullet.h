#pragma once

// sfml
#include <SFML/Graphics.hpp>

// box2d
#include <Box2D/Box2D.h>

// base
#include "gamenode.h"
#include "fixturenode.h"

#include <functional>
#include <list>
#include <set>

class b2Body;

class Bullet : public FixtureNode
{

public:

   using DestroyedCallback = std::function<void(void)>;

   Bullet();
   ~Bullet();

   bool isScheduledForRemoval() const;
   void setScheduledForRemoval(bool isScheduledForRemoval);

   b2Body *getBody() const;
   void setBody(b2Body *body);

   static void clear();
   static void cleanup();
   static void updateHitAnimations(const sf::Time& dt);

   void setDestroyedCallback(const DestroyedCallback& destroyedCallback);


protected:

   bool mScheduledForRemoval = false;
   b2Body* mBody = nullptr;
   DestroyedCallback mDestroyedCallback;

   static std::set<Bullet*> sBullets;
   static std::list<b2Vec2> sDetonationPositions;
};


