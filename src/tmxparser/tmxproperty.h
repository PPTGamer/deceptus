#pragma once

#include "tmxelement.h"

#include <cstdint>

struct TmxProperty : TmxElement
{
   TmxProperty() = default;

   void deserialize(tinyxml2::XMLElement* e) override;

   std::string mType;
   std::string mValueStr;
   float mValueFloat = 0.0f;
   int32_t mValueInt = 0;
};

