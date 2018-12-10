/// <summary>
///Lab 4 missle one
/// a game where a Asteroid comes fromthe top of the screen
/// towards the bottom if you  hit it with the laser you gain
/// 5 points if it hits the ground you lose
/// Estimated Time : 16 HOURS
/// Actual Time: 20  Hours
/// Would put the times i worked on it on ,but i forgot to keep track.
/// No Known Bugs
/// Extra fEATURES NOT IMPLEMENTED
/// @author Ben Stynes
/// @date 10th December 2018
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include "game.h"
#include <stdlib.h> 
#include <time.h> 


/// <summary>
/// main enrtry point
/// </summary>
/// <returns>zero</returns>
int main()
{
	srand(time(NULL));
	Game game;
	game.run();
	return 0;
}