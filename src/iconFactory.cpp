// TODO implementation
#include <vector>
#include "icon.h"
#include "iconFactory.h"

IconFactory::IconFactory(){}

Icon IconFactory::newIcon(Color color, int width, int height){
	Cell cell(color,' ');
	Icon icon;
	for(int i=0;i<height;i++){
		std::vector<Cell> cellVec;
		for(int j=0;j<width;j++)
			cellVec.push_back(cell);
		icon.push_back(cellVec);
	} return icon;
}
