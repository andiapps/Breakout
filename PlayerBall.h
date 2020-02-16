/**
    Blueprint for creating the ball in the game.
    Including the position, speed of the ball and graphical building parts of the ball. 
*/

struct PlayerBall {
	
	double ballX;
	double ballY;
	double ballVX;		//ball moving speed on X 
	double ballVY; 		//ball moving speed on Y
	SDL_Surface *ball;
	SDL_Texture *ballTexture;
	SDL_Rect ballRect;
};
