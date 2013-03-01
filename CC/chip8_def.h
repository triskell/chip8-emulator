/*
 * chip8_def.h
 *
 *  Created on: 25 févr. 2013
 *      Author: isen
 */

#ifndef CHIP8_DEF_H_
#define CHIP8_DEF_H_

	#define CHIP8_MEM_SIZE 			4096
	#define CHIP8_MEM_START			0x200
	#define CHIP8_FONTSET_END_ADDR 	0x50
	#define CHIP8_BUFFER_NB 		16
	#define CHIP8_STACK_NB 			16
	#define CHIP8_KEY_NB 			16
	#define CHIP8_GFX_SIZE 			64*32


	typedef struct chip8{
		unsigned char 	memory[CHIP8_MEM_SIZE];
		unsigned char 	V[CHIP8_BUFFER_NB];		// registers with V[16] used as "carry flag"
		unsigned short 	I; 						// index register
		unsigned short 	pc; 					// program counter
		unsigned char 	gfx[CHIP8_GFX_SIZE];	// pixel array printed on screen
		unsigned char 	delay_timer;			// counts to 0 at 60 Hz
		unsigned char 	sound_timer;			// counts to 0 at 60 Hz. system buzzes when it reaches 0
		unsigned short 	stack[CHIP8_STACK_NB];
		unsigned short 	sp;						// stack pointer
		unsigned char	key[CHIP8_KEY_NB];		// stores the 16 bits keyboard status
	} Chip8;

#endif /* CHIP8_DEF_H_ */
