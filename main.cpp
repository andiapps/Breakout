/**
    Prototype of Breakout 
    main.cpp
    Purpose: Initialize all objects and implement the game

    @author Dian Wang
    @version 2.0 14/02/20 
*/

#include<SDL.h>
#include "PlayerBall.h"
#include "PlayerPaddle.h"
#include "PlayerBackground.h"
#include "GameBrick.h"
#include "GameParameters.h"

PlayerBall theBall;
PlayerPaddle thePaddle;	
PlayerBackground theBackground;
GameBrick theBrick;
GameParameters theGamePara;

void resourceRecycle();


void UserEventHandler(){		//Keyboard input listener
	
	SDL_PollEvent(&theGamePara.event);
	if(theGamePara.event.type==SDL_QUIT){
		theGamePara.quit=true;
	}else if(theGamePara.event.type==SDL_KEYDOWN){
		if(theGamePara.event.key.keysym.sym==SDLK_LEFT && thePaddle.paddleX>0){
			thePaddle.paddleX = thePaddle.paddleX-0.4;
		}
		if(theGamePara.event.key.keysym.sym==SDLK_RIGHT && thePaddle.paddleX<theBackground.bgwidth-60){
			thePaddle.paddleX = thePaddle.paddleX+0.4;
		}
		if(theGamePara.event.key.keysym.sym==SDLK_RETURN){
			theGamePara.startGame = true;
		}	
}
}

void initLives() {		
	theGamePara.lifeRect[0][0] = {8,400,40,40};
	theGamePara.lifeRect[0][1] = {8,455,40,40};
	theGamePara.lifeRect[0][2] = {8,510,40,40};
}
void initBricks(int w, int h){
	
	theBrick.brickRect[0][0] = {50,50,w,h};
	theBrick.brickRect[0][1] = {150,50,w,h};
	theBrick.brickRect[0][2] = {250,50,w,h};
	theBrick.brickRect[0][3] = {350,50,w,h};
	theBrick.brickRect[0][4] = {450,50,w,h};
	theBrick.brickRect[0][5] = {550,50,w,h};
	theBrick.brickRect[0][6] = {650,50,w,h};
	theBrick.brickRect[1][0] = {50,100,w,h};
	theBrick.brickRect[1][1] = {150,100,w,h};
	theBrick.brickRect[1][2] = {250,100,w,h};
	theBrick.brickRect[1][3] = {350,100,w,h};
	theBrick.brickRect[1][4] = {450,100,w,h};
	theBrick.brickRect[1][5] = {550,100,w,h};
	theBrick.brickRect[1][6] = {650,100,w,h};
	theBrick.brickRect[2][0] = {50,150,w,h};
	theBrick.brickRect[2][1] = {150,150,w,h};
	theBrick.brickRect[2][2] = {250,150,w,h};
	theBrick.brickRect[2][3] = {350,150,w,h};
	theBrick.brickRect[2][4] = {450,150,w,h};
	theBrick.brickRect[2][5] = {550,150,w,h};
	theBrick.brickRect[2][6] = {650,150,w,h};
}

void gameOver(){
	SDL_Surface *lifeLoss = SDL_LoadBMP("go.bmp");
	SDL_Texture *lifeLossTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,lifeLoss);
	SDL_Rect lifeLossRect = {0,0,theBackground.bgwidth,theBackground.bgheight};
	SDL_RenderCopy(theGamePara.renderer,lifeLossTexture,NULL,&lifeLossRect);
	SDL_RenderPresent(theGamePara.renderer);
	SDL_Event evt;		
	bool programrunning = true;
	while(programrunning){		//Event loop which ignores all events apart from SDL_QUIT. Prevent program from frozen after game ends
		SDL_WaitEvent(&evt);
		if(evt.type==SDL_QUIT)
		programrunning = false;
	}
	resourceRecycle();
	SDL_Quit();
}

void ballMove(){		//Defines the speed ball moves on X and Y axis 
	theBall.ballX = theBall.ballX + theBall.ballVX;
	theBall.ballY = theBall.ballY + theBall.ballVY;
}

void ballCollision() {
	if(theBall.ballX<theBackground.bgminWidth || theBall.ballX>theBackground.bgwidth-30){
		theBall.ballVX=-theBall.ballVX;		//Makes the ball bounce back when it touches the horizontal edges of the game window
	}
	if(theBall.ballY<theBackground.bgminHeight){
		theBall.ballVY=-theBall.ballVY;		//Makes the ball bounce back when it touches the upper edge of the game window
		}
	if(theBall.ballY>theBackground.bgheight-30){		
		theBall.ballVY=-theBall.ballVY;		//Detects whether the ball hits the 'ground'.
		theGamePara.lives--;
		if(theGamePara.lives==0){
			gameOver();		
		}
	}
	int ballScaling = 20;		//Parameter makes sure the edge of the ball collides with the paddle
	if(theBall.ballY+ballScaling>=thePaddle.paddleY&&theBall.ballY+ballScaling<=thePaddle.paddleY+30 && 
	theBall.ballX+ballScaling>=thePaddle.paddleX&&theBall.ballX+ballScaling<=thePaddle.paddleX+60){
		theBall.ballVY=-theBall.ballVY;
		theBall.ballVX=-theBall.ballVX;
	}
}

bool ballBrickCollisionDetect(SDL_Rect rect1,SDL_Rect rect2){
	if(rect1.x>rect2.x+rect2.w){
		return false;
	}
	if(rect1.x+rect1.w<rect2.x){
		return false;
	}
	if(rect1.y>rect2.y+rect2.h){
		return false;
	}
	if(rect1.y+rect1.h<rect2.y){
		return false;
	}
	return true;
}

void ballBrickCollision(){
	bool didCollide;
	for(int i=0;i<3;i++){
		for(int j=0;j<7;j++){
			didCollide=ballBrickCollisionDetect(theBrick.brickRect[i][j],theBall.ballRect);
			if(didCollide==true){
				theBrick.brickRect[i][j].x = 33333;		//Removing the brick from display area
				theBall.ballVY=-theBall.ballVY;
				theGamePara.brickHits++; 				//Count the bricks which have been hit 
			}
			didCollide=false;
		}
	}
}

void resourceRecycle(){
	SDL_DestroyTexture(thePaddle.paddleTexture);
	SDL_DestroyTexture(theBall.ballTexture);
	SDL_DestroyTexture(theBackground.backgroundTexture);
	SDL_DestroyTexture(theBrick.brickTexture);
	SDL_DestroyTexture(theGamePara.playerLifeTexture);
	
	SDL_FreeSurface(thePaddle.paddle);
	SDL_FreeSurface(theBall.ball);
	SDL_FreeSurface(theBackground.background);
	SDL_FreeSurface(theBrick.brick);
	SDL_FreeSurface(theGamePara.playerLife);
	
	SDL_DestroyRenderer(theGamePara.renderer);
	SDL_DestroyWindow(theGamePara.gameWindow);
}

void winning(){
	SDL_Surface *win = SDL_LoadBMP("win.bmp");
	SDL_Texture *winTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,win);
	SDL_Rect winRect = {250,200,350,350};
	SDL_RenderCopy(theGamePara.renderer,winTexture,NULL,&winRect);
	SDL_RenderPresent(theGamePara.renderer);
	SDL_Delay(10000);
	resourceRecycle();
	SDL_Quit();
}
	
int main(int argc, char ** argv){
	
	SDL_Init(SDL_INIT_VIDEO);
	
	theGamePara.quit = false;
	theGamePara.startGame = false;
	theGamePara.brickHits = 0;
	theGamePara.numOfBricks = 21;		//numbers of bricks 
	theGamePara.lives = 3;				//Player lives
	
	theGamePara.gameWindow = SDL_CreateWindow("!Breakout!",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,0);
	theGamePara.renderer = SDL_CreateRenderer(theGamePara.gameWindow,-1,0);	

	theBackground.backgroundRect = {0,0,800,600};
	theBrick.brickH = 35;
	theBrick.brickW = 80;	
	initBricks(theBrick.brickW, theBrick.brickH);
	initLives();   						//Initialize player lives indicitor
	
	theBall.ball = SDL_LoadBMP("ball.bmp");	
	theBackground.background = SDL_LoadBMP("bk.bmp");
	thePaddle.paddle = SDL_LoadBMP("paddle.bmp");
	theBrick.brick = SDL_LoadBMP("brick.bmp");
	theGamePara.playerLife = SDL_LoadBMP("lifeLogo.bmp");
	
	theBall.ballTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,theBall.ball);
	theBackground.backgroundTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,theBackground.background);
	thePaddle.paddleTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,thePaddle.paddle);
	theBrick.brickTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,theBrick.brick);
	theGamePara.playerLifeTexture = SDL_CreateTextureFromSurface(theGamePara.renderer,theGamePara.playerLife);	

//Init ball
	theBall.ballX = 350;
	theBall.ballY = 250;
	theBall.ballVX = 0.12;				//ball moving speed on X 
	theBall.ballVY = 0.12;				//ball moving speed on Y
		
//Init background
	theBackground.bgwidth = 800;
	theBackground.bgheight = 600;
	theBackground.bgminWidth = 0;
	theBackground.bgminHeight = 0;

//Paddle position
	thePaddle.paddleX = 450;
	thePaddle.paddleY = theBackground.bgheight-30;

//Game loop	
	while(!theGamePara.quit){
		UserEventHandler();
	
		theBall.ballRect = {theBall.ballX,theBall.ballY,20,30};			
		thePaddle.paddleRect = {thePaddle.paddleX,thePaddle.paddleY,60,30};	
		
		if(theGamePara.startGame==true)	{						//Freeze the ball until user press ENTER to start
		ballMove();
		ballCollision();
		ballBrickCollision();
		}
		if(theGamePara.brickHits==theGamePara.numOfBricks){		//If all bricks have been hit then player wins.
			winning();
		}
		
		SDL_RenderCopy(theGamePara.renderer,theBackground.backgroundTexture,NULL,&theBackground.backgroundRect);
		SDL_RenderCopy(theGamePara.renderer,theBall.ballTexture,NULL,&theBall.ballRect);
		SDL_RenderCopy(theGamePara.renderer,thePaddle.paddleTexture,NULL,&thePaddle.paddleRect);
		
		for(int i=0; i<3; i++)
		for(int j=0; j<7; j++){
		SDL_RenderCopy(theGamePara.renderer,theBrick.brickTexture,NULL,&theBrick.brickRect[i][j]);
		}		
		if(theGamePara.lives==3){
			for(int i=0; i<1; i++)
			for(int j=0; j<3; j++){
			SDL_RenderCopy(theGamePara.renderer,theGamePara.playerLifeTexture,NULL,&theGamePara.lifeRect[i][j]);
		}
		}		
		if(theGamePara.lives==2){
			SDL_RenderCopy(theGamePara.renderer,theGamePara.playerLifeTexture,NULL,&theGamePara.lifeRect[0][1]);
			SDL_RenderCopy(theGamePara.renderer,theGamePara.playerLifeTexture,NULL,&theGamePara.lifeRect[0][2]);
		}	
		if(theGamePara.lives==1){
			SDL_RenderCopy(theGamePara.renderer,theGamePara.playerLifeTexture,NULL,&theGamePara.lifeRect[0][2]);
		}
	
		SDL_RenderPresent(theGamePara.renderer);
		SDL_RenderClear(theGamePara.renderer);
	}
	
	resourceRecycle();
	SDL_Quit();
}
