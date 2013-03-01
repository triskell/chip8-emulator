/*
 * main.c
 *
 *  Created on: 25 févr. 2013
 *      Author: isen
 */

#include "main.h"


int main(int argc, char **argv){

	int continuer = 1;
	Chip8 chip8;
	SDL_Surface *screen = NULL;
	SDL_Surface *buffer = NULL;

	screen = initSDL();
	buffer = SDL_CreateRGBSurface(SDL_HWSURFACE, 640, 320, 16, 0, 0, 0, 0);
	chip8 = chip8_initialize();
	chip8_load(&chip8, "games/PONG");

	while(continuer){
		continuer = handleEmuEvents();
		chip8_emulateCycle(&chip8);
		updateScreen(chip8, screen, buffer);
	}

	SDL_Quit();
	return 0;

}

SDL_Surface* initSDL(){

	SDL_Surface *screen;

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1 )
	{
		printf( "[ERROR] Can't initialize SDL:  %s\n", SDL_GetError( ) );
		exit(EXIT_FAILURE);
	}

	atexit( SDL_Quit );
	screen = SDL_SetVideoMode( 640, 320, 16, SDL_HWSURFACE | SDL_DOUBLEBUF );

	if( screen == NULL )
	{
		printf( "[ERROR] Can't set video mode: %s\n", SDL_GetError( ) );
		exit(EXIT_FAILURE);
	}

	SDL_WM_SetCaption("Chip8-Emu", NULL);

	return screen;
}

int handleEmuEvents(){

	SDL_Event event;

	if(SDL_PollEvent(&event)){
		switch (event.type) {
			case SDL_QUIT:
				return 0;
				break;
			default:
				break;
		}
	}

	return 1;

}

void updateScreen(Chip8 chip8, SDL_Surface *screen, SDL_Surface *buffer){

	int i;
	SDL_Rect dstrect;
	dstrect.x = 0;
	dstrect.y = 0;

	SDL_FillRect(buffer, NULL, SDL_MapRGB(buffer->format, 0, 0, 0));


	for(i=0 ; i<CHIP8_GFX_SIZE ; i++){

		/*if(chip8.gfx[i] != 0) printf("%d", chip8.gfx[i]);
		else printf(".");
		if(i%64==63)printf("\n");*/

		if(chip8.gfx[i] != 0){
			setPixel(buffer, (i%64), (i/64), SDL_MapRGB(buffer->format, 255, 255, 255));
		}

	}

	SDL_BlitSurface(buffer, NULL, screen, &dstrect);
	SDL_Flip(screen);


}

void setPixel(SDL_Surface *buffer, int x, int y, Uint32 color){
  //*((Uint32*)(screen->pixels) + x + (y * screen->w)) = coul;
	SDL_Rect pixel;

	pixel.x = x * SCREEN_STRETCH;
	pixel.y = y * SCREEN_STRETCH;
	pixel.w = SCREEN_STRETCH;
	pixel.h = SCREEN_STRETCH;
	SDL_FillRect(buffer, &pixel, color);
}
