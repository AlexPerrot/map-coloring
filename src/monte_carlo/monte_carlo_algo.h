#ifndef MONTE_CARLO_ALGO_H
#define MONTE_CARLO_ALGO_H

#include "monte_carlo.h"
#include "../game/game.h"

class MonteCarloSelection : public SelectionAlgorithm {
public:
	MonteCarloSelection(MapGame& game, bool minimize=false);
	virtual ColoringMove selectMove();
protected:
	MonteCarloNode* tree;
	bool minimize;
};

#endif
