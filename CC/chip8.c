/*
 * chip8.c
 *
 *  Created on: 25 févr. 2013
 *      Author: Thomas Abot
 */

#include "chip8.h"


	unsigned const char chip8_fontset[80] =
	{
	  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	  0x20, 0x60, 0x20, 0x20, 0x70, // 1
	  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

Chip8 chip8_initialize(){

	Chip8 chip8;
	int i;

	/*
	 * Clearing all entries
	 */

	chip8.I = 0;
	chip8.sp = 0;

	// Clear display
	for(i = 0 ; i<CHIP8_GFX_SIZE ; i++){
		chip8.gfx[i] = 0;
	}
	// Clear stack
	for(i = 0 ; i<CHIP8_STACK_NB ; i++){
		chip8.stack[i] = 0;
	}
	// Clear registers V0-VF
	for(i = 0 ; i<CHIP8_BUFFER_NB ; i++){
		chip8.V[i] = 0;
	}
	// Clear memory
	for(i = 0 ; i<CHIP8_MEM_SIZE ; i++){
		chip8.memory[i] = 0;
	}


	/*
	 * Setting initial values
	 */

	chip8.pc = CHIP8_MEM_START; //programs starts at 0x200 in memory

	// Load fontset
	for(i = 0; i < CHIP8_FONTSET_END_ADDR; ++i){
	    chip8.memory[i] = chip8_fontset[i];
	}


	/*
	 * Setting up random generation
	 */
	srand(time(NULL));

	return chip8;
}

void chip8_load(Chip8 *chip8, char *filePath){

	FILE *file = NULL;

	file = fopen(filePath, "rb");
	if(file != NULL){
		fread(chip8->memory + CHIP8_MEM_START, (CHIP8_MEM_SIZE - CHIP8_MEM_START)*sizeof(char), 1, file);
	} else{
		printf("[ERROR] Can't load %s\n", filePath);
	}

	fclose(file);
}

void chip8_emulateCycle(Chip8 *chip8)
{
  unsigned short opcode = 0;

  // Handle Key
  chip8_handleKey(chip8);

  // Handle opcode
  opcode = chip8_fecthOpcode(chip8);
  chip8_processOpcode(opcode, chip8);

  // Update timers
  chip8_updateTimers(chip8);

}

void chip8_handleKey(Chip8 *chip8){

	SDL_Event event;

	/* MAP DU TABLEAU KEY :
	 *  hexadecimal order : from 0 to 15(E) : characters 0123456789azerty
	 */

	if( SDL_PollEvent( &event ) ) {
		printf("event !\n");
		if( event.type == SDL_KEYDOWN ) {
			printf("key down!\n");
			switch (event.key.keysym.sym) {
				case SDLK_0:
					chip8->key[0] = 1;
					break;
				case SDLK_1:
					chip8->key[1] = 1;
					break;
				case SDLK_2:
					chip8->key[2] = 1;
					break;
				case SDLK_3:
					chip8->key[3] = 1;
					break;
				case SDLK_4:
					chip8->key[4] = 1;
					break;
				case SDLK_5:
					chip8->key[5] = 1;
					break;
				case SDLK_6:
					chip8->key[6] = 1;
					break;
				case SDLK_7:
					chip8->key[7] = 1;
					break;
				case SDLK_8:
					chip8->key[8] = 1;
					break;
				case SDLK_9:
					chip8->key[9] = 1;
					break;
				case SDLK_a:
					chip8->key[10] = 1;
					break;
				case SDLK_z:
					chip8->key[11] = 1;
					break;
				case SDLK_e:
					chip8->key[12] = 1;
					break;
				case SDLK_r:
					chip8->key[13] = 1;
					break;
				case SDLK_t:
					chip8->key[14] = 1;
					break;
				case SDLK_y:
					chip8->key[15] = 1;
					break;
				default:
					break;
			}
		}
		if( event.type == SDL_KEYUP ) {
			printf("key up!\n");
			switch (event.key.keysym.sym) {
				case SDLK_0:
					chip8->key[0] = 0;
					break;
				case SDLK_1:
					chip8->key[1] = 0;
					break;
				case SDLK_2:
					chip8->key[2] = 0;
					break;
				case SDLK_3:
					chip8->key[3] = 0;
					break;
				case SDLK_4:
					chip8->key[4] = 0;
					break;
				case SDLK_5:
					chip8->key[5] = 0;
					break;
				case SDLK_6:
					chip8->key[6] = 0;
					break;
				case SDLK_7:
					chip8->key[7] = 0;
					break;
				case SDLK_8:
					chip8->key[8] = 0;
					break;
				case SDLK_9:
					chip8->key[9] = 0;
					break;
				case SDLK_a:
					chip8->key[10] = 0;
					break;
				case SDLK_z:
					chip8->key[11] = 0;
					break;
				case SDLK_e:
					chip8->key[12] = 0;
					break;
				case SDLK_r:
					chip8->key[13] = 0;
					break;
				case SDLK_t:
					chip8->key[14] = 0;
					break;
				case SDLK_y:
					chip8->key[15] = 0;
					break;
				default:
					break;
			}
		}
	}

}


unsigned short chip8_fecthOpcode(Chip8 *chip8){

	unsigned short opcode = chip8->memory[chip8->pc] <<8 | chip8->memory[chip8->pc + 1];

	chip8->pc += 2;

	return opcode;
}

void chip8_processOpcode(unsigned short opcode, Chip8 *chip8){

	switch(opcode & 0xF000)
	  {
		case 0x0000:
			switch (opcode & 0x0FF) {
				case 0x00E0:
					chip8_OF_cls(chip8);
					break;
				case 0x00EE:
					chip8_OF_ret(chip8);
					break;
				default:
					printf ("Unknown opcode: 0x%X\n", opcode);
					break;
			}
			break;
		case 0x1000:
			chip8_OF_jmp(chip8, opcode);
	      break;
		case 0x2000:
			chip8_OF_call(chip8, opcode);
		  break;
		case 0x3000:
			chip8_OF_se_vx_b(chip8, opcode);
		  break;
		case 0x4000:
			chip8_OF_sne_vx_b(chip8, opcode);
		  break;
		case 0x5000:
			chip8_OF_se_vx_vy(chip8, opcode);
		  break;
		case 0x6000:
			chip8_OF_ld_vx_b(chip8, opcode);
		  break;
		case 0x7000:
			chip8_OF_add_vx_b(chip8, opcode);
		  break;
		case 0x8000:
			switch (opcode & 0x000F) {
				case 0x0000:
					chip8_OF_ld_vx_vy(chip8, opcode);
					break;
				case 0x0001:
					chip8_OF_or(chip8, opcode);
					break;
				case 0x0002:
					chip8_OF_and(chip8, opcode);
					break;
				case 0x0003:
					chip8_OF_xor(chip8, opcode);
					break;
				case 0x0004:
					chip8_OF_add_vx_vy(chip8, opcode);
					break;
				case 0x0005:
					chip8_OF_sub(chip8, opcode);
					break;
				case 0x0006:
					chip8_OF_shr(chip8, opcode);
					break;
				case 0x0007:
					chip8_OF_subn(chip8, opcode);
					break;
				case 0x000E:
					chip8_OF_shl(chip8, opcode);
					break;
				default:
					printf ("Unknown opcode: 0x%X\n", opcode);
					break;
			}
		  break;
		case 0x9000:
			chip8_OF_sne_vx_vy(chip8, opcode);
		  break;
		case 0xA000:
			chip8_OF_ld_i_addr(chip8, opcode);
	      break;
		case 0xB000:
			chip8_OF_jmp_vo(chip8, opcode);
	      break;
		case 0xC000:
			chip8_OF_rnd(chip8, opcode);
	      break;
		case 0xD000:
			chip8_OF_drw(chip8, opcode);
		  break;
		case 0xE000:
			switch (opcode & 0x00FF) {
				case 0x09E:
					chip8_OF_skp(chip8, opcode);
					break;
				case 0x0A1:
					chip8_OF_skp(chip8, opcode);
					break;
				default:
					break;
			}
	      break;
		case 0xF000:
			switch (opcode & 0x00FF) {
				case 0x0007:
					chip8_OF_ld_vx_dt(chip8, opcode);
					break;
				case 0x000A:
					chip8_OF_ld_vx_k(chip8, opcode);
					break;
				case 0x0015:
					chip8_OF_ld_dt_vx(chip8, opcode);
					break;
				case 0x0018:
					chip8_OF_ld_st_vx(chip8, opcode);
					break;
				case 0x001E:
					chip8_OF_add_i_vx(chip8, opcode);
					break;
				case 0x0029:
					chip8_OF_ld_f_vx(chip8, opcode);
					break;
				case 0x0033:
					chip8_OF_ld_b_vx(chip8, opcode);
					break;
				case 0x0055:
					chip8_OF_ld_i_vx(chip8, opcode);
					break;
				case 0x0065:
					chip8_OF_ld_vx_i(chip8, opcode);
					break;
				default:
					printf ("Unknown opcode: 0x%X\n", opcode);
					break;
			}
	      break;

	    default:
	      printf ("Unknown opcode: 0x%X\n", opcode);
	      break;
	  }

}

void chip8_updateTimers(Chip8 *chip8){

	//update delay_timer
	if(chip8->delay_timer > 0){
		chip8->delay_timer--;
	}

	//update sound_timer
	if(chip8->sound_timer > 0){
		if(chip8->sound_timer == 1) printf("TODO : Timer says \"Buzz !\"\n");
		chip8->sound_timer--;
	}
}

