#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <termios.h>

#include "environment.h"
#include "controller.h"
#include "gameObjectFactory.h"

Controller::Controller(View& view) : _view(view){}

void Controller::run() {
    // initial setup
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    configure_terminal();

    // init state
    int input = -1;
    clock_t start, end;

	// init game objects
	srand(time(NULL));
	GameObjectFactory objFactory = GameObjectFactory::newFactory();
	
	// Player
	_objs.push_back(objFactory.newPlayer(1,1)); // Starting position
		
	// Map
	_objs.push_back(objFactory.newWall(1,3,7,0));
	_objs.push_back(objFactory.newWall(3,18,2,0));
	_objs.push_back(objFactory.newWall(5,16,2,0));
	_objs.push_back(objFactory.newWall(7,14,10,0));
	_objs.push_back(objFactory.newWall(7,8,6,0));
	_objs.push_back(objFactory.newWall(20,3,-2,0));
	_objs.push_back(objFactory.newWall(18,3,0,6));
	
	// Enemies
	_objs.push_back(objFactory.newEnemy(10,1));

	// Goal
	
    int hp = 3;
	int enemyLogic = -5; // Controls enemy movement: [-5,5]
	
	// Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if(input==27) break;

		Position playerMove = this->handleInput(input);
		if(enemyLogic>5) enemyLogic = -5; // Controls enemy movement: [-5,5]

        _view.resetLatest();
        for(GameObject* obj : _objs){
			if(dynamic_cast<Player*>(obj)) moveInMap(obj,playerMove);
			else if(dynamic_cast<Enemy*>(obj)) moveInMap(obj,{0,0},enemyLogic++);
            _view.updateGameObject(obj);
        } _view.render();

		// Collision
		for(int A=0;A<_objs.size();A++){
			for(int B=A+1;B<_objs.size();B++){
				if(_objs[A]->intersect(_objs[B])){
					_objs[A]->onCollision(_objs[B]);
					_objs[B]->onCollision(_objs[A]);
					_view.updateGameObject(_objs[A]);
					_view.updateGameObject(_objs[B]);
				}
			}
		} _view.render();

		// Check if game ended
		if(hp<=0/* || Reached goal*/) break;

        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 50); // 0.005 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }

	// Check win / lose
	if(hp<=0) std::cout << "Wasted." << std::endl;
	else std::cout << "Congradulations!" << std::endl;
	//std::cout << "(Some key) Replay" << std::endl;
}

void Controller::moveInMap(GameObject *obj,Position playerMove,int enemyLogic){
	int xCheck,yCheck,x,y;
	if(dynamic_cast<Player*>(obj)){
		xCheck = obj->getPosition().x()+playerMove.x();
		yCheck = obj->getPosition().y()+playerMove.y()+1; // Free fall, y opposite
	} else if(dynamic_cast<Enemy*>(obj)){
		x = (enemyLogic==0 ? 0 : (enemyLogic>0 ? 1 : -1)); y = 0; // Enemy movements
		xCheck = obj->getPosition().x()+x;
		yCheck = obj->getPosition().y()+y+1; // Free fall, y opposite
	}

	if(xCheck>=0 && xCheck<GAME_WINDOW_WIDTH){
		if(dynamic_cast<Player*>(obj)){ // Player
			obj->update({playerMove.x(),(yCheck<GAME_WINDOW_HEIGHT ? playerMove.y()+1/*Free fall, y opposite*/ : 0)});
			//std::cout << "[DEBUG] (controller.cpp - moveInMap) (xCheck,yCheck) = (" << xCheck << "," << yCheck << ")" << std::endl; //debug
			//std::cout << "[DEBUG] (controller.cpp - moveInMap) playerMove = (" << playerMove.x() << "," << playerMove.y() << ")" << std::endl; //debug
			//std::cout << "[DEBUG] (controller.cpp - moveInMap) Player movement: (" << playerMove.x() << ","
			//	  << playerMove.y()+(yCheck>=0 ? 0 : yCheck) << ")" << std::endl; //debug
		}else if(dynamic_cast<Enemy*>(obj)) // Enemies
			obj->update({x,(yCheck<GAME_WINDOW_HEIGHT ? y+1/*Free fall, y opposite*/ : 0)});
	}
}

Position Controller::handleInput(int keyInput){
	GameObject*& player = _objs[0];

    // TODO 
    // handle key events.
	switch(keyInput){
		case('w'):
		case(' '):{ // y opposite
			// Make the player jump
			// Touch the map border
			if(player->getPosition().y()==GAME_WINDOW_HEIGHT-1)
				return {0,-3};
			for(int i=1;i<_objs.size();i++){
				// Touch the ground / Climb walls
				if(dynamic_cast<Wall*>(_objs[i]) && player->intersect(_objs[i]))
					return {0,-3};
			} return {0,0};
		} case('a'):{
			return {-1,0};
		} case('d'):{
			return {1,0};
		} default:
			return {0,0};
	}
}

void Controller::update(){}

void reset_terminal() {
    printf("\e[m"); // reset color changes
    printf("\e[?25h"); // show cursor
    fflush(stdout);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

// terminal initial configuration setup
void configure_terminal() {
    tcgetattr(STDIN_FILENO, &old_termios);
	new_termios = old_termios; // save it to be able to reset on exit
    
    new_termios.c_lflag &= ~(ICANON | ECHO); // turn off echo + non-canonical mode
    new_termios.c_cc[VMIN] = 0;
    new_termios.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("\e[?25l"); // hide cursor
    std::atexit(reset_terminal);
}

int read_input() {
    fflush(stdout);
   	char buf[4096]; // maximum input buffer
	int n = read(STDIN_FILENO, buf, sizeof(buf));
    return n > 0 ? buf[n - 1] : -1;
}

