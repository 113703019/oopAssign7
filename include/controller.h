#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <termios.h>
#include <vector>
#include "view.h"
#include "RPSGameObject.h"

class Controller{
	public:
    	Controller(View&);
	    void run();
	private:
		void moveInMap(RPSGameObject*,Position playerMove={0,0});
    	Position handleInput(int);
    	void update();

    	// Model
	    std::vector<RPSGameObject*> _objs;

    	// View
	    View& _view; 
};

static struct termios old_termios, new_termios;
void reset_terminal();
void configure_terminal();
int read_input();

#endif
