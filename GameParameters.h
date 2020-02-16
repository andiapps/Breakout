/**
    A collection of parameters for game logic. 
	Graphical building parts for user event, window, SDL rendrer and player's life level indicator
*/

struct GameParameters {
	
	bool quit;
 	bool startGame;
 	int brickHits;  	//Counts the bricks which have been hit by the ball
	int numOfBricks; 	//hard coded numbers of bricks
	int lives; 			//Player lives
 	
	SDL_Event event; 
	SDL_Window *gameWindow;
	SDL_Renderer *renderer;		
	
	SDL_Surface *playerLife;
	SDL_Texture *playerLifeTexture;
	SDL_Rect lifeRect[1][3]; 	//Using newly created blocks to indicate player's lives left. 
};
