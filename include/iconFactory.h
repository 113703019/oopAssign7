// TODO 
// Finish the declaration of IconFactory that
// 1. offers some methods to create an Icon.
// 2. encapsulates the constructor from the caller. 

#ifndef ICONFACTORY_H
#define ICONFACTORY_H

#include "icon.h"
#include "gameObject.h"

class IconFactory{
	public:
		static IconFactory newFactory() { return IconFactory(); }
		Icon newIcon(Color,int,int);
	private:
		IconFactory();
};

#endif
