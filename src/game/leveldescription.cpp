#include "leveldescription.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

using json = nlohmann::json;


void to_json(json &j, const LevelDescription &d)
{
   j = json{
      {"filename", d.mFilename},
      {"startposition", d.mStartPosition},
      {"enemies", d.mEnemies}
   };
}


void from_json(const json &j, LevelDescription &d)
{
   d.mFilename = j.at("filename").get<std::string>();
   d.mStartPosition = j.at("startposition").get<std::vector<int>>();

   if (j.find("enemies") != j.end())
   {
      d.mEnemies = j.at("enemies").get<std::vector<EnemyDescription>>();
   }
}


std::shared_ptr<LevelDescription> LevelDescription::load(const std::string &path)
{
   std::ifstream ifs (path, std::ifstream::in);

   auto c = ifs.get();
   std::string data;

   while (ifs.good())
   {
     data.push_back(static_cast<char>(c));
     c = ifs.get();
   }

   ifs.close();

   std::shared_ptr<LevelDescription> description;

   try
   {
     json config = json::parse(data);
     description = std::make_shared<LevelDescription>();
     *description = config;
   }
   catch (const std::exception& e)
   {
     std::cout << e.what() << std::endl;
   }

   return description;
}


