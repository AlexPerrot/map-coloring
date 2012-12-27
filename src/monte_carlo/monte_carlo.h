#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>

#include "../game/move.h"

class MonteCarloNode {
public:
	MonteCarloNode(ColoringMove colorMove);
	~MonteCarloNode();
	MonteCarloNode* getParent();
	std::vector<MonteCarloNode*> getChildren();
	ColoringMove getMove();
	int gamesPlayed;
	int gamesWon;

private:
	MonteCarloNode* parent;
	std::vector<MonteCarloNode*> children;
	ColoringMove move;
};

#endif
