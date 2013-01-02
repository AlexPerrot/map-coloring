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
	std::vector<MonteCarloNode*>& getChildren();
	void playMove();
	void undoMove();
	MapGame* getGame();
	ColoringMove* getMove();
	int gamesPlayed;
	int gamesWon;

	void deleteChildren();
	void deleteParent();

private:
	void generateChildren();
	MonteCarloNode* parent;
	std::vector<MonteCarloNode*> children;
	ColoringMove* move;
	bool childrenGenerated;
	MapGame* game;
};

typedef MonteCarloNode* (*MCSelection)(std::vector<MonteCarloNode*>&, bool);

MonteCarloNode* selectNodeEquiprob(std::vector<MonteCarloNode*>& nodes, bool minimize=false);
MonteCarloNode* UCB1(std::vector<MonteCarloNode*>& nodes, bool minimize=false);
int simulate(MonteCarloNode* node, int nbGames, bool minimize, MCSelection selectNode=selectNodeEquiprob);
#endif
