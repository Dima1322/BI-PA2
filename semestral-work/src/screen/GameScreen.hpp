#ifndef SEMESTRAL_WORK_GAMESCREEN_HPP
#define SEMESTRAL_WORK_GAMESCREEN_HPP

#include <string>

#include "Screen.hpp"

/**
 * Displays and process a game screen and it's functionality.
 */
class GameScreen : public Screen {
public:
  /**
   * A constructor.
   *
   * @param fileName input file name of the game
   */
  GameScreen (std::string fileName, bool newGame);

  ScreenState process () override;

protected:
  /**
   * Name of the input file.
   */
  std::string fileName;

  bool newGame;
};

#endif // SEMESTRAL_WORK_GAMESCREEN_HPP