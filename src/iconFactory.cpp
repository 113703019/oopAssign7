// TODO implementation
#include <vector>
#include "icon.h"
#include "iconFactory.h"
#include "RPSGameObject.h"

IconFactory::IconFactory(){}

Icon IconFactory::newIcon(RPSType type, int width, int height, bool isPlayer){
	Color color = setColor(type);
	char word = setChar(type);
	Icon icon;

	// Make RPS icon
	std::vector<Cell> cellVec;
	// Hardcoded everything due to same format
	if(isPlayer) cellVec.push_back({color,word-32});
	else cellVec.push_back({color,word});
	icon.push_back(cellVec);
	return icon;
}

Color IconFactory::setColor(RPSType type){
    if(type==ROCK) return RED;
    else if(type==PAPER) return GREEN;
    else if(type==SCISSORS) return CYAN;
}

char IconFactory::setChar(RPSType type){
    if(type==ROCK) return 'r';
    else if(type==PAPER) return 'p';
    else if(type==SCISSORS) return 's';
}
