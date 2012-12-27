#include "monte_carlo.h"

/****** MonteCarloNode ******/

MonteCarloNode::MonteCarloNode()
	: gamesPlayed(0), gamesWon(0), parent(0), move(0) {

}

MonteCarloNode::MonteCarloNode(ColoringMove* colorMove, MonteCarloNode* parent)
	: gamesPlayed(0), gamesWon(0), parent(parent), move(colorMove) {

}

MonteCarloNode::~MonteCarloNode() {
	delete move;
}

MonteCarloNode* MonteCarloNode::getParent() {
	return parent;
}

std::vector<MonteCarloNode*> MonteCarloNode::getChildren() {
	return children;
}

ColoringMove* MonteCarloNode::getMove() {
	return move;
}
