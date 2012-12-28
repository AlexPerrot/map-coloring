#include "monte_carlo.h"

/****** MonteCarloNode ******/

MonteCarloNode::MonteCarloNode(MapGame* game)
	: gamesPlayed(0), gamesWon(0), parent(0),
	  move(0), childrenGenerated(false), game(game) {

}

MonteCarloNode::MonteCarloNode(MapGame* game, ColoringMove* colorMove, MonteCarloNode* parent)
	: gamesPlayed(0), gamesWon(0), parent(parent),
	  move(colorMove), childrenGenerated(false), game(game) {

}

MonteCarloNode::~MonteCarloNode() {
	delete move;
}

MonteCarloNode* MonteCarloNode::getParent() {
	return parent;
}

std::vector<MonteCarloNode*> MonteCarloNode::getChildren() {
	if (!childrenGenerated)
		generateChildren();
	return children;
}

void MonteCarloNode::playMove() {
	move->play(game->getGraph());
}

void MonteCarloNode::undoMove() {
	move->undo(game->getGraph());
}

MapGame* MonteCarloNode::getGame() {
	return game;
}

void MonteCarloNode::generateChildren() {
	childrenGenerated = true;
	// complete whith children generation
}

/****** Other functions ******/
int simulate(MonteCarloNode* node, int nbGames) {
	MapGame* game = node->getGame();
	int nbWon = 0;
	if (game->isFinished())
		nbWon = nbGames;
	else if (game->canContinue()) {
		for (int i=nbGames ; i>0 ; --i) {
			MonteCarloNode* child = selectNode(node->getChildren());
			child->playMove();
			nbWon += simulate(child, 1);
			child->undoMove();
		}
	}
	node->gamesPlayed += nbGames;
	node->gamesWon += nbWon;
	return nbWon;
}

MonteCarloNode* selectNode(std::vector<MonteCarloNode*> nodes) {
	return nodes.front(); //dummy for testing purposes
}
