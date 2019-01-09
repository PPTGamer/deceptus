#ifndef EXTRASKILL_H
#define EXTRASKILL_H

#include "extra.h"

class ExtraSkill : public Extra
{
public:
   ExtraSkill();

   enum Skill
   {
      SkillClimb = 0x01,
   };

   int mSkills = 0; // SkillClimb;
};

#endif // EXTRASKILL_H
