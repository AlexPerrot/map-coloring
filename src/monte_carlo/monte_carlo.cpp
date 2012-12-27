#include "monte_carlo.h"

/****** MonteCarloNode ******/

MonteCarloNode::MonteCarloNode(ColoringMove colorMove) 
	: gamesPlayed(0), gamesWon(0), parent(0), move(colorMove) {

}

MonteCarloNode::~MonteCarloNode() {

}

MonteCarloNode* MonteCarloNode::getParent() {
	return parent;
}

std::vector<MonteCarloNode*> MonteCarloNode::getChildren() {
	return children;
}

ColoringMove MonteCarloNode::getMove() {
	return move;
}
