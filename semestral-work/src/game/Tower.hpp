#ifndef SEMESTRAL_WORK_TOWER_HPP
#define SEMESTRAL_WORK_TOWER_HPP

#include <vector>

#include "cell/Cell.hpp"

class Tower : public Cell {
public:
  Tower (int cost, int height, int width, int attackPower, int range, int ammoPerRound);

  Tower (const Tower& tower);

  std::vector<Cell> towerCells;

  int getCost ();

  int getHeight ();

  int getWidth ();

  int getAttackPower ();

  int getRange ();

  int getAmmoPerRound ();

  int y;

  int x;

  bool operator== (const Tower b) const;

  int letter;

  void initRound ();

  int currentAmmo;

protected:
  int cost;
  int height;
  int width;
  int attackPower;
  int range;
  int ammoPerRound;
};

#endif // SEMESTRAL_WORK_TOWER_HPP