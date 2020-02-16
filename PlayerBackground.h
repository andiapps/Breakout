/**
    Blueprint for creating the game's background.
    Including the background's actual width, hight, minimum width and hight.
	Including the graphical building parts for the game's background

*/

struct PlayerBackground {
	
	int bgwidth;		//background width
	int bgheight;		//background height
	int bgminWidth;		//edge of the window on X axis
	int bgminHeight;	//edge of the window on Y axis
	SDL_Surface *background;
	SDL_Texture *backgroundTexture;
	SDL_Rect backgroundRect;
};
