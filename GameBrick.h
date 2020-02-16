/**
    Blueprint for creating the bricks in the game.
    Including the height, width of the brick and graphical building parts of bricks. 
*/

struct GameBrick {
	
	int brickH; 	//Brick height
	int brickW;		//Brick width
	SDL_Surface *brick;		
	SDL_Texture *brickTexture;
	SDL_Rect brickRect[3][7];
};
