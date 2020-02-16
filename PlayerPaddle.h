/**
    Blueprint for creating the paddle in the game.
    Including the position of the paddle and graphical building parts of the paddle 

*/

struct PlayerPaddle {
	
	double paddleX;
	double paddleY;
	SDL_Surface *paddle;
	SDL_Texture *paddleTexture;
	SDL_Rect paddleRect;
};
