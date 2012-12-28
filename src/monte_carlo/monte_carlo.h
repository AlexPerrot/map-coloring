#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>

#include "../game/move.h"
#include "../game/game.h"

class MonteCarloNode {
public:
	MonteCarloNode(MapGame* game);
	MonteCarloNode(MapGame* game, ColoringMove* colorMove, MonteCarloNode* parent);
	~MonteCarloNode();
	MonteCarloNode* getParent();
	std::vector<MonteCarloNode*> getChildren();
	void playMove();
	void undoMove();
	MapGame* getGame();
	int gamesPlayed;
	int gamesWon;

private:
	void generateChildren();
	MonteCarloNode* parent;
	std::vector<MonteCarloNode*> children;
	ColoringMove* move;
	bool childrenGenerated;
	MapGame* game;
};

int simulate(MonteCarloNode* node, int nbGames);
MonteCarloNode* selectNodeForSimu(std::vector<MonteCarloNode*> nodes);
#endif
