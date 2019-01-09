#include "bullethitanimation.h"


//----------------------------------------------------------------------------------------------------------------------
bool BulletHitAnimation::sInitialized = false;
sf::Texture BulletHitAnimation::sTexture;
SfmlAnimation BulletHitAnimation::sAnimation;
std::list<BulletHitAnimation*> BulletHitAnimation::sAnimations;
std::list<BulletHitAnimation*> BulletHitAnimation::sElapsedAnimations;

const auto width = 32;
const auto height = 32;
const auto sprites = 6;
const auto frameTime = 0.075f;
const auto animationDuration = 400;


//----------------------------------------------------------------------------------------------------------------------
BulletHitAnimation::BulletHitAnimation(sf::Time frameTime)
 : SfmlAnimatedSprite(frameTime)
{
   if (!sInitialized)
   {
      initialize();
   }

   setOrigin(width / 2, height / 2);
   setAnimation(sAnimation);
}


//----------------------------------------------------------------------------------------------------------------------
void BulletHitAnimation::initialize()
{
   if (sTexture.loadFromFile("data/weapons/detonation_big.png"))
   {
      sAnimation.setSpriteSheet(sTexture);

      for (int i = 0; i < sprites; i++)
      {
         sAnimation.addFrame(sf::IntRect(i * (width + 1), 0, width, height));
      }

      sInitialized = true;
   }
   else
   {
      printf("failed to load spritesheet!\n");
   }
}


//----------------------------------------------------------------------------------------------------------------------
void BulletHitAnimation::add(float x, float y)
{
   auto anim = new BulletHitAnimation(sf::seconds(frameTime));
   anim->setPosition(x, y);
   anim->play();

   sAnimations.push_back(anim);
}


//----------------------------------------------------------------------------------------------------------------------
void BulletHitAnimation::updateAnimations(float dt)
{
   std::list<BulletHitAnimation*>::iterator it;
   for (it = sAnimations.begin(); it != sAnimations.end();)
   {
      BulletHitAnimation* sprite = (*it);

      if (sprite->getElapsed() > animationDuration)
      {
         delete *it;
         sAnimations.erase(it++);
      }
      else
      {
         it++;
         sprite->update(dt);
         sprite->incrementElapsed(static_cast<int>(dt * 1000.0f));
      }
   }
}


//----------------------------------------------------------------------------------------------------------------------
std::list<BulletHitAnimation*> *BulletHitAnimation::getAnimations()
{
   return &sAnimations;
}


