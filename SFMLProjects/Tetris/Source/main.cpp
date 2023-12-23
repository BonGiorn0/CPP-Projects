#include "Game.hpp"

int main(){
    Game demo;
    while(demo.isRunning()){
        demo.PollEvent();
        demo.Update();
        demo.Render();
    }
    return 0;
}