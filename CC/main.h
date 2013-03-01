/*
 * main.h
 *
 *  Created on: 26 févr. 2013
 *      Author: isen
 */

#ifndef MAIN_H_
#define MAIN_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <SDL/SDL.h>
	#include "chip8.h"

	#define SCREEN_STRETCH 10

	SDL_Surface* 	initSDL			();
	int 			handleEmuEvents	();
	void 			updateScreen	(Chip8 chip8, SDL_Surface *screen, SDL_Surface *buffer);
	void 			setPixel		(SDL_Surface *buffer, int x, int y, Uint32 coul);

#endif /* MAIN_H_ */
