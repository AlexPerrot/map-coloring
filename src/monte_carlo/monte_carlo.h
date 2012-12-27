#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>

#include "../game/move.h"

class MonteCarloNode {
public:
	MonteCarloNode();
	MonteCarloNode(ColoringMove* colorMove, MonteCarloNode* parent);
	~MonteCarloNode();
	MonteCarloNode* getParent();
	std::vector<MonteCarloNode*> getChildren();
	ColoringMove* getMove();
	int gamesPlayed;
	int gamesWon;

private:
	MonteCarloNode* parent;
	std::vector<MonteCarloNode*> children;
	ColoringMove* move;
};

#endif
