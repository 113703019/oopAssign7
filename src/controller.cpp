#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <unistd.h>
#include <termios.h>

#include "RPSGameObject.h"
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
	int target = 0; // For target changing
					// Initially, the player is the first element added
					// so the target(player) is 0

	// init game objects
	srand(time(NULL));
	GameObjectFactory objFactory = GameObjectFactory::newFactory();
	// Letting the player start easy, okay? R : P : S = 6(5NPC+1Player) : 5 : 5
	_objs.push_back(objFactory.newRPS(
				/*RPSType*/ ROCK,
				/*Random direction*/ static_cast<Direction>(rand()%4),
				/*Random posX*/ rand()%(GAME_WINDOW_WIDTH - RPS_OBJECT_WIDTH),
				/*Random posY*/ rand()%(GAME_WINDOW_HEIGHT - RPS_OBJECT_HEIGHT),
				/*Is Player?*/ true));

	for(int i=0;i<15;i++)
		_objs.push_back(objFactory.newRPS(
					/*RPSType*/ static_cast<RPSType>(i%3),
					/*Random direction*/ static_cast<Direction>(rand()%4),
					/*Random posX*/ rand()%(GAME_WINDOW_WIDTH - RPS_OBJECT_WIDTH),
					/*Random posY*/ rand()%(GAME_WINDOW_HEIGHT - RPS_OBJECT_HEIGHT),
					/*Is Player?*/ false));
	
    int count[3] = {0,0,0}; // Default reset value. ROCK,PAPER,SCISSORS
	
	// Main loop
    while (true) {
        start = clock();
        // game loop goes here
        input = read_input();

        // ESC to exit program
        if(input==27) break;

		// TAB to change target
		if(input==9){
			for(int i=0;i<_objs.size();i++){
				if(i==target){
					_objs[i]->isPlayer = false;
					_objs[i]->setIcon(ROCK,false);
					_view.updateGameObject(_objs[i]);
					continue;
				} else if((_objs[i]->getType()==ROCK && i>target)|| target==count[ROCK]-1){
					_objs[i]->isPlayer = true;
					_objs[i]->setIcon(ROCK,true);
					target = i;
					_view.updateGameObject(_objs[i]);
					break;
				}
			}
		} _view.render();

		// Q to cheer!
		std::string cheer[6] = {
						   "Go go, team rock! Yeah!!",
						   "Team rock biggest flock!",
						   "Rocks rock for the win!!",
						   "Be not afraid of papers!",
						   "Rocks are the best ever!",
						   "Smash 'em scissors open!"};
		srand(time(NULL));
		if(input=='Q' || input=='q')
			std::cout << cheer[rand()%6] << std::endl;

		Position playerMove = this->handleInput(input);

        _view.resetLatest();
        for(RPSGameObject* obj : _objs){
			// Move the objects
			if(obj->isPlayer) moveInMap(obj,playerMove);
			else moveInMap(obj);
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
		for(RPSGameObject* obj : _objs){
			// Count the objects
            // This code seems stupid tbh but I don't know how to fix for now
            if(obj->getType()==ROCK) count[ROCK]++;
            else if(obj->getType()==PAPER) count[PAPER]++;
            else if(obj->getType()==SCISSORS) count[SCISSORS]++;
		}
		for(int cnt : count)
			if(cnt==0) break;

		std::cout << "Press Q to cheer for your team!" << std::endl; // Introduce feature
        end = clock();

        // frame rate normalization
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        if (time_taken > SPF) continue;
        int frameDelay = int((SPF - time_taken) * 500); // 0.05 seconds
        if(frameDelay > 0) std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay)); // frame delay
    }

	// Check the winner
	std::string winner = "None";
	if(count[PAPER]==0 && count[SCISSORS]==0) winner = "You(Rock)";
	else if(count[ROCK]==0 && count[SCISSORS]==0) winner = "Paper";
	else if(count[ROCK]==0 && count[PAPER]==0) winner = "Scissors";
	if(winner!="None") std::cout << winner << " win!!!" << std::endl;
}

void Controller::moveInMap(RPSGameObject *obj,Position playerMove){
	int xCheck,yCheck,x,y;
	if(obj->isPlayer){
		xCheck = obj->getPosition().x()+playerMove.x();
		yCheck = obj->getPosition().y()+playerMove.y();
	} else{
		x = rand()%3-1; y = rand()%3-1; // x & y = [-1,1]
		xCheck = obj->getPosition().x()+x;
		yCheck = obj->getPosition().y()+y;
	}
	if(xCheck>=0 && xCheck<GAME_WINDOW_WIDTH && yCheck>=0 && yCheck<GAME_WINDOW_HEIGHT)
		obj->isPlayer ? obj->update(playerMove) : obj->update({x,y});
}

Position Controller::handleInput(int keyInput){

    // TODO 
    // handle key events.
	switch(keyInput){
		case('w'):{ // y opposite
			return {0,-1};
		} case('a'):{
			return {-1,0};
		} case('s'):{ // y opposite
			return {0,1};
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

