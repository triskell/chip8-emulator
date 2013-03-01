/*
 * chip8.h
 *
 *  Created on: 25 févr. 2013
 *      Author: isen
 */

#ifndef CHIP8_H_
#define CHIP8_H_

	#include <stdio.h>
	#include <math.h>
	#include <time.h>
	#include <SDL/SDL.h>
	#include "chip8_def.h"
	#include "chip8_opfonc.h"


	Chip8 			chip8_initialize	();
	void 			chip8_load			(Chip8 *chip8, char *filePath);
	void 			chip8_emulateCycle	(Chip8 *chip8);
	void 			chip8_handleKey		(Chip8 *chip8);
	unsigned short 	chip8_fecthOpcode	(Chip8 *chip8);
	void 			chip8_processOpcode	(unsigned short opcode, Chip8 *chip8);
	void 			chip8_updateTimers	(Chip8 *chip8);

#endif /* CHIP8_H_ */
