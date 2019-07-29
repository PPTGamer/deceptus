#include "pathinterpolation.h"


// const float checkRadius = 0.5f;


void PathInterpolation::addKey(const b2Vec2& pos, float time)
{
   Key key;
   key.mPos = pos;
   key.mTime = time;

   mTrack.push_back(key);
}


b2Vec2 PathInterpolation::compute(const b2Vec2& current, float time)
{
   // clamp time
   if (time > 1.0f)
   {
      time = 1.0f;
   }
   else if (time < 0.0f)
   {
      time = 0.0f;
   }

   b2Vec2 velocity;

   switch (mMode)
   {
      case Mode::Linear:
      {
         for (auto indexCurrent = 0u; indexCurrent < mTrack.size(); indexCurrent++)
         {
            size_t indexNext = indexCurrent + 1;
            if (indexNext == mTrack.size())
            {
               indexNext = mTrack.size() - 1;
            }

            Key keyA = mTrack.at(indexCurrent);
            Key keyB = mTrack.at(indexNext);

            if (time >= keyA.mTime && time < keyB.mTime)
            {
               auto a = 1.0f - (time - keyA.mTime);
               auto b = 1.0f - (keyB.mTime - time);

               velocity = (a * keyA.mPos + b * keyB.mPos) - current;
               // printf("a: %f, b: %f, current: %f, %f, velocity: %f, %f\n", a, b, current.x, current.y, velocity.x, velocity.y);
               break;
            }
         }
         break;
      }
   }

   return velocity;
}


float PathInterpolation::updateZeroOneZeroOne(float dt)
{
   if (mTime >= 1.0f)
   {
      mTime = 1.0f;
      mUp = false;
   }
   else if (mTime <= 0.0f)
   {
      mTime = 0.0f;
      mUp = true;
   }

   if (mUp)
   {
      mTime += dt;
   }
   else
   {
      mTime -= dt;
   }

   return mTime;
}



bool PathInterpolation::checkKeyReached(const b2Vec2& currentPos)
{
  auto reached = false;

  if (mTrack.empty())
  {
     return false;
  }

  if ((currentPos - mTrack[mCurrentKeyIndex].mPos).LengthSquared() < 0.1f)
  {
     reached = true;
  }

  return reached;
}



bool PathInterpolation::update(const b2Vec2& currentPos)
{
   auto reached = false;

  // just check whether the speed needs to be updated (i.e. if one of the keys
  // has been reached)
   if (checkKeyReached(currentPos) || !mVelocity.IsValid())
   {
      mCurrentKeyIndex = nextKeyIndex();
      computeVelocity();
      reached = true;
   }

   // b2Vec2 b = mTrack[nextKeyIndex()].mPos;
   // printf("current: %f, %f next: %f: %f, velocity: %f, %f, reached: %d\n", currentPos.x, currentPos.y, b.x, b.y, mVelocity.x, mVelocity.y, reached);

   return reached;
}


void PathInterpolation::computeVelocity()
{
   b2Vec2 a = mTrack[mCurrentKeyIndex].mPos;
   b2Vec2 b = mTrack[nextKeyIndex()].mPos;

   mVelocity = (a - b);
   mVelocity.Normalize();
}


const b2Vec2 PathInterpolation::getVelocity()
{
   return mVelocity;
}


size_t PathInterpolation::nextKeyIndex()
{
  auto nextIndex = mCurrentKeyIndex + 1;
  if (nextIndex == mTrack.size())
  {
    nextIndex = 0;
  }

  return nextIndex;
}


