#ifndef __Game_Kaboom_include_GameScene_Constants_h__
#define __Game_Kaboom_include_GameScene_Constants_h__

////////////////////////////////////////////////////////////////////////////////
// Constants                                                                  //
////////////////////////////////////////////////////////////////////////////////
// Text //
const char * const kFontName = "nokiafc22.ttf";

constexpr int kFontSize_PauseText = 100;
constexpr int kFontSize_ScoreText = 20;
constexpr int kFontSize_TurnText  = 20;
constexpr int kTextOffset         = 20;

// Timers //
constexpr float kClockInterval_PauseText = 0.5; //Half a second.

// Positions / Sizes //
constexpr int kSize_SkyHeight = 150;
constexpr int kPos_Bomber     = kSize_SkyHeight;
constexpr int kPos_Player     = 400;

//Score
constexpr int kScoreMutilplier = 50;

//Sounds
static const char * const kSoundName_LevelStart = "level_start.wav";
static const char * const kSoundName_Victory    = "victory.wav";
static const char * const kSoundName_Defeat     = "defeat.wav";
static const char * const kSoundName_GameOver   = "gameover.wav";

//String Formats
static const char * kStringFormat_Score = "Score %06d";
static const char * kStringFormat_Level = "Level %03d";

#endif // __Game_Kaboom_include_GameScene_Constants_h__ //
