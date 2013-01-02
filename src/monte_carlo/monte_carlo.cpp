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

ColoringMove* MonteCarloNode::getMove() {
	return move;
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

void MonteCarloNode::deleteChildren() {
	for(std::vector<MonteCarloNode*>::iterator it=children.begin() ;
	    it != children.end() ; ++it) {
		(*it)->deleteChildren();
		delete (*it);
	}
}

void MonteCarloNode::deleteParent() {
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
int simulate(MonteCarloNode* node, int nbGames, bool minimize, MCSelection selectNode) {
	MapGame* game = node->getGame();
	int nbWon = 0;
	if (game->isFinished())
		nbWon = nbGames;
	else if (game->canContinue()) {
		for (int i=nbGames ; i>0 ; --i) {
			MonteCarloNode* child = selectNode(node->getChildren(), minimize);
			child->playMove();
			nbWon += simulate(child, 1, !minimize, selectNode);
			child->undoMove();
		}
	}
	node->gamesPlayed += nbGames;
	node->gamesWon += nbWon;
	return nbWon;
}

MonteCarloNode* selectNodeEquiprob(std::vector<MonteCarloNode*>& nodes, bool minimize) {
	return nodes.at(rand()%nodes.size()); //dummy for testing purposes
}

double getPossibleRatio(MonteCarloNode* node, int totalMoves, bool minimize) {
	double avg = (1.0*node->gamesWon)/node->gamesPlayed;
	double cb = sqrt(2.0*log(totalMoves)/node->gamesPlayed);
	return (minimize ? avg-cb : avg + cb);
}

MonteCarloNode* UCB1(std::vector<MonteCarloNode*>& nodes, bool minimize) {
	int totalPlayed = 0;
	for(std::vector<MonteCarloNode*>::iterator it=nodes.begin() ;
	    it != nodes.end() ; ++it) {
		totalPlayed += (*it)->gamesPlayed;
	}

	std::vector<MonteCarloNode*> maxVector;
	double pRatio, ratioMax=(minimize?1:0);
	int gP;
	MonteCarloNode *curr = 0;
	for(std::vector<MonteCarloNode*>::iterator it=nodes.begin() ;
	    it != nodes.end() ; ++it) {
		curr = *it;
		gP = curr->gamesPlayed;
		pRatio = (gP>0 ? getPossibleRatio(curr, totalPlayed, minimize) : (minimize?0:1));
		if (pRatio == ratioMax) {
			maxVector.push_back(curr);
		} else {
			switch (minimize) {
			case false:
				if (pRatio > ratioMax) {
					maxVector.clear();
					maxVector.push_back(curr);
					ratioMax = pRatio;
				}
				break;
			case true:
				if (pRatio < ratioMax) {
					maxVector.clear();
					maxVector.push_back(curr);
					ratioMax = pRatio;
				}
				break;
			}
		}
	}
	return selectNodeEquiprob(maxVector, minimize);
}
