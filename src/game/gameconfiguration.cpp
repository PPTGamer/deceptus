#include "gameconfiguration.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <sstream>

#include "json/json.hpp"

using json = nlohmann::json;


bool GameConfiguration::sInitialized = false;
GameConfiguration GameConfiguration::sInstance;
GameConfiguration GameConfiguration::mDefaults;


std::string GameConfiguration::serialize()
{
   json config =
   {
      {
         "GameConfiguration",
         {
            {"video_mode_width",  mVideoModeWidth},
            {"video_mode_height", mVideoModeHeight},
            {"view_width",        mViewWidth},
            {"view_height",       mViewHeight},
            {"fullscreen",        mFullscreen},
            {"brightness",        mBrightness},
            {"vsync",             mVSync},

            {"audio_volume_master", mAudioVolumeMaster},
            {"audio_volume_sfx",    mAudioVolumeSfx},
            {"audio_volume_music",  mAudioVolumeMusic},
         }
      }
   };

   std::stringstream sstream;
   sstream << std::setw(4) << config << "\n\n";
   return sstream.str();
}


void GameConfiguration::deserialize(const std::string& data)
{
   json config = json::parse(data);

   try {
       mVideoModeWidth  = config["GameConfiguration"]["video_mode_width"].get<int32_t>();
       mVideoModeHeight = config["GameConfiguration"]["video_mode_height"].get<int32_t>();
       mViewWidth       = config["GameConfiguration"]["view_width"].get<int32_t>();
       mViewHeight      = config["GameConfiguration"]["view_height"].get<int32_t>();
       mFullscreen      = config["GameConfiguration"]["fullscreen"].get<bool>();
       mBrightness      = config["GameConfiguration"]["brightness"].get<float>();
       mVSync           = config["GameConfiguration"]["vsync"].get<bool>();

       mViewScaleWidth = static_cast<float>(mViewWidth) / static_cast<float>(mVideoModeWidth);
       mViewScaleHeight = static_cast<float>(mViewHeight) / static_cast<float>(mVideoModeHeight);

       mAudioVolumeMaster = config["GameConfiguration"]["audio_volume_master"].get<int32_t>();
       mAudioVolumeSfx    = config["GameConfiguration"]["audio_volume_sfx"].get<int32_t>();
       mAudioVolumeMusic  = config["GameConfiguration"]["audio_volume_music"].get<int32_t>();
   }
   catch (const std::exception& e)
   {
       std::cout << e.what() << std::endl;
   }
}


void GameConfiguration::deserializeFromFile(const std::string& filename)
{
   std::ifstream ifs (filename, std::ifstream::in);

   char c = ifs.get();
   std::string data;

   while (ifs.good())
   {
      data.push_back(c);
      c = ifs.get();
   }

   ifs.close();

   deserialize(data);
}


void GameConfiguration::serializeToFile(const std::string &filename)
{
  std::string data = serialize();
  std::ofstream file(filename);
  file << data;
}


GameConfiguration& GameConfiguration::getDefaults()
{
   return mDefaults;
}


GameConfiguration& GameConfiguration::getInstance()
{
   if (!sInitialized)
   {
      sInstance.deserializeFromFile();
      sInitialized = true;
   }

   return sInstance;
}


void GameConfiguration::resetAudioDefaults()
{
   getInstance().mAudioVolumeMaster = getDefaults().mAudioVolumeMaster;
   getInstance().mAudioVolumeMusic = getDefaults().mAudioVolumeMusic;
   getInstance().mAudioVolumeSfx = getDefaults().mAudioVolumeSfx;
}

