#include "Game.hpp"


int main(){
    Game game(1200, 800);
    while(game.isRunning()){
        game.update();
        game.render();
    }
    return 0;
}