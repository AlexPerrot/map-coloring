#ifndef MONTE_CARLO_ALGO_H
#define MONTE_CARLO_ALGO_H

#include "monte_carlo.h"
#include "../game/game.h"

void setNumberOfSimulations(int nb);

class MonteCarloSelection : public SelectionAlgorithm {
public:
	MonteCarloSelection(MapGame& game, bool minimize=false);
	virtual ColoringMove selectMove();
	void reset();
protected:
	MonteCarloNode* tree;
	bool minimize;
};

#endif
