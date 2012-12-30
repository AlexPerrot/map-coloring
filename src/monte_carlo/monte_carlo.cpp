#include <cmath>

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

std::vector<MonteCarloNode*>& MonteCarloNode::getChildren() {
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
	std::vector<ColoringMove*> moves = getPossibleMoves(game);
	for(std::vector<ColoringMove*>::iterator it=moves.begin() ;
	    it != moves.end() ; ++it) {
		children.push_back(new MonteCarloNode(game, *it, this));
	}
}

void deleteChildren() {
	for(std::vector<MonteCarloNode*>::iterator it=children.begin() ;
	    it != children.end() ; ++it) {
		(*it)->deleteChildren();
		delete (*it);
	}
}

void deleteParent() {
	if (parent != 0) {
		std::vector<MonteCarloNode*>& bro = parent->getChildren();
		for(std::vector<MonteCarloNode*>::iterator it=bro.begin() ;
		    it != bro.end() ; ++it) {
			if ((*it)!=this)
				delete (*it);
		}
		delete parent;
	}
}

/****** Other functions ******/
int simulate(MonteCarloNode* node, int nbGames, MCSelection selectNode) {
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

MonteCarloNode* selectNodeEquiprob(std::vector<MonteCarloNode*>& nodes) {
	return nodes.at(rand()%nodes.size()); //dummy for testing purposes
}

double getPossibleRatio(MonteCarloNode* node, int totalMoves) {
	return (1.0*node->gamesWon)/node->gamesPlayed + sqrt(2.0*log(totalMoves)/node->gamesPlayed);
}

MonteCarloNode* UCB1(std::vector<MonteCarloNode*>& nodes) {
	int totalPlayed = 0;
	for(std::vector<MonteCarloNode*>::iterator it=nodes.begin() ;
	    it != nodes.end() ; ++it) {
		totalPlayed += (*it)->gamesPlayed;
	}

	double pRatio, ratioMax=0;
	int gP;
	MonteCarloNode* max = 0, *curr = 0;
	for(std::vector<MonteCarloNode*>::iterator it=nodes.begin() ;
	    it != nodes.end() ; ++it) {
		curr = *it;
		gP = curr->gamesPlayed;
		pRatio = (gP>0 ? getPossibleRatio(curr, totalPlayed) : 1);
		if (pRatio > ratioMax) {
			max = curr;
			ratioMax = pRatio;
		}
	}
	return max;
}
