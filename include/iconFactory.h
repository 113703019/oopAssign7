// TODO 
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller. 

#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include "icon.h"
#include "RPSGameObject.h"

class IconFactory{
	public:
		static IconFactory newFactory() { return IconFactory(); }
		Icon newIcon(RPSType,int,int,bool);
		Color setColor(RPSType type);
		char setChar(RPSType type);
	private:
		IconFactory();
};

#endif
