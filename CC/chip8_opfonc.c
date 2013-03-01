/*
 * chip8_opfonc.c
 *
 *  Created on: 25 févr. 2013
 *      Author: isen
 */

#include "chip8_opfonc.h"


/*
 * Comments from the documentation at http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
 */




/*
 * Clear the display.
 */
void chip8_OF_cls(Chip8 *chip8){

	int i;

	for(i=0 ; i<CHIP8_GFX_SIZE ; i++){
		chip8->gfx[i]=0;
	}
}

/*
 * Return from a subroutine.
 */
void chip8_OF_ret(Chip8 *chip8){
	chip8->pc = chip8->stack[chip8->sp];
	chip8->sp--;
}


/*
 * Jump to location nnn.
 */
void chip8_OF_jmp(Chip8 *chip8, unsigned short opcode){
	chip8->pc = opcode & 0x0FFF;
}


/*
 * Call subroutine at nnn.
 */
void chip8_OF_call(Chip8 *chip8, unsigned short opcode){
	chip8->sp++;
	chip8->stack[chip8->sp]=chip8->pc;
	chip8_OF_jmp(chip8, opcode);
}

/*
 * Skip next instruction if Vx = kk.
 */
void chip8_OF_se_vx_b(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char kk = opcode & 0x00FF;

	if(chip8->V[x] == kk){
		chip8->pc += 2;
	}
}

/*
 * Skip next instruction if Vx != kk.
 */
void chip8_OF_sne_vx_b(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char kk = opcode & 0x00FF;

	if(chip8->V[x] != kk){
		chip8->pc += 2;
	}
}


/*
 * Skip next instruction if Vx = Vy.
 */
void chip8_OF_se_vx_vy(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;

	if(chip8->V[x] == chip8->V[y]){
		chip8->pc += 2;
	}
}

/*
 * Set Vx = kk.
 */
void chip8_OF_ld_vx_b(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char kk = opcode & 0x00FF;

	chip8->V[x] = kk;
}

/*
 * Set Vx = Vx + kk.
 */
void chip8_OF_add_vx_b(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char kk = opcode & 0x00FF;

	chip8->V[x] += kk;
}

/*
 * Set Vx = Vy.
 */
void chip8_OF_ld_vx_vy(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;

	chip8->V[x] = chip8->V[y];
}

/*
 * Set Vx = Vx OR Vy.
 */
void chip8_OF_or(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;

	chip8->V[x] = chip8->V[x] | chip8->V[y];
}

/*
 * Set Vx = Vx AND Vy.
 */
void chip8_OF_and(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;

	chip8->V[x] = chip8->V[x] & chip8->V[y];
}

/*
 * Set Vx = Vx AND Vy.
 */
void chip8_OF_xor(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;

	chip8->V[x] = chip8->V[x] ^ chip8->V[y];
}

/*
 * Set Vx = Vx + Vy, set VF = carry. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0.
 */
void chip8_OF_add_vx_vy(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;
	unsigned short result;

	result = chip8->V[x] + chip8->V[y];

	if( (result & 0x00FF) != 0x0000 ) chip8->V[15]=1;
	else chip8->V[16]=0;

	chip8->V[x] = result & 0x00FF;
}

/*
 * Set Vx = Vx - Vy, set VF = NOT borrow. If Vx > Vy, then VF is set to 1, otherwise 0.
 */
void chip8_OF_sub(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4 ;

	if(chip8->V[x] > chip8->V[y]) chip8->V[15]=1;
	else chip8->V[16]=0;

	chip8->V[x]= chip8->V[x] - chip8->V[y];
}

/*
 * Set Vx = Vx SHR 1. If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0.
 */
void chip8_OF_shr(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	if(chip8->V[x] % 2 ==1) chip8->V[15]=1;
	else chip8->V[16]=0;

	chip8->V[x] = chip8->V[x] >> 2 ;
}

/*
 * Set Vx = Vy - Vx, set VF = NOT borrow. If Vy > Vx, then VF is set to 1, otherwise 0.
 */
void chip8_OF_subn(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4 ;

	if(chip8->V[y] > chip8->V[x]) chip8->V[15]=1;
	else chip8->V[16]=0;

	chip8->V[x]= chip8->V[y] - chip8->V[x];
}

/*
 * Set Vx = Vx SHL 1. If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0.
 */
void chip8_OF_shl(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	if((chip8->V[x] << 15) == 1) chip8->V[16]=1;
	else chip8->V[16]=0;

	chip8->V[x] = chip8->V[x] << 2 ;
}


/*
 * Skip next instruction if Vx != Vy.
 */
void chip8_OF_sne_vx_vy(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char y = (opcode & 0x00F0) >> 4;

	if(chip8->V[x] != chip8->V[y]){
		chip8->pc += 2;
	}
}

/*
 * Set I = nnn.
 */
void chip8_OF_ld_i_addr(Chip8 *chip8, unsigned short opcode){
	chip8->I = opcode & 0x0FFF;
}

/*
 * Jump to location nnn + V0.
 */
void chip8_OF_jmp_vo(Chip8 *chip8, unsigned short opcode){
	chip8->I = (opcode & 0x0FFF) + chip8->V[0];
}


/*
 * Set Vx = random byte AND kk.
 */
void chip8_OF_rnd(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char kk = opcode & 0x00FF;
	char random = (char) rand() % 256;

	chip8->V[x] = random & kk;
}

/*
 * Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
 */
void chip8_OF_drw(Chip8 *chip8, unsigned short opcode){

	char x = chip8->V[(opcode & 0x0F00) >> 8];
	char y = chip8->V[(opcode & 0x00F0) >> 4];
	char n =  opcode & 0x000F;
	int a, b;
	char pixel;

	chip8->V[15] = 0;
	for(a=0 ; a<n ; a++){
		pixel = chip8->memory[(chip8->I)+a];
		for(b=0; b<8 ; b++){
			if((pixel & (0x80 >> b)) != 0){
				if(chip8->gfx[x+b+((y+a)*64)] == 1){
					chip8->V[15] = 1;
				}
				chip8->gfx[x+b+((y+a)*64)] ^= 1 ;
			}
		}
	}
}

/*
 * Skip next instruction if key with the value of Vx is pressed.
 */
void chip8_OF_skp(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	if ( chip8->key[x] == 1){
		chip8->pc += 2;
	}
}

/*
 * Skip next instruction if key with the value of Vx is not pressed.
 */
void chip8_OF_sknp(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	if ( chip8->key[x] == 0){
		chip8->pc += 2;
	}
}


/*
 * Set Vx = delay timer value.
 */
void chip8_OF_ld_vx_dt(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->V[x] = chip8->delay_timer;
}

/*
 * Wait for a key press, store the value of the key in Vx.
 */
void chip8_OF_ld_vx_k(Chip8 *chip8, unsigned short opcode){

	int i, event = 0;
	char x = (opcode & 0x0F00) >> 8;

	while(!event){
		for(i=0 ; i<CHIP8_KEY_NB && event!=0 ; i++){
			event += chip8->key[i];
		}
	}

	chip8->V[x] = (char) --i;
}

/*
 * Set delay timer = Vx.
 */
void chip8_OF_ld_dt_vx(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->delay_timer = chip8->V[x];
}

/*
 * Set sound timer = Vx.
 */
void chip8_OF_ld_st_vx(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->sound_timer = chip8->V[x];
}

/*
 * Set I = I + Vx.
 */
void chip8_OF_add_i_vx(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->I += chip8->V[x];
}

/*
Fx29 - LD F, Vx
Set I = location of sprite for digit Vx.

The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font.
 */
/*
 * Set I = location of sprite for digit Vx.
 */
void chip8_OF_ld_f_vx(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->I = chip8->memory[chip8->V[x]] * 5;
}

/*
 * Store BCD representation of Vx in memory locations I, I+1, and I+2.
 */
void chip8_OF_ld_b_vx(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;
	char bcd = chip8->V[x];

	chip8->memory[chip8->I] = bcd / 100;
	bcd %= 100;
	chip8->memory[chip8->I+1] = bcd / 10;
	bcd %= 10;
	chip8->memory[chip8->I+2] = bcd;
}

/*
 * Store registers V0 through Vx in memory starting at location I.
 */
void chip8_OF_ld_i_vx(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->V[x] = chip8->V[0];
	chip8->memory[chip8->I] = chip8->V[x];
}

/*
 * Read registers V0 through Vx from memory starting at location I.
 */
void chip8_OF_ld_vx_i(Chip8 *chip8, unsigned short opcode){
	char x = (opcode & 0x0F00) >> 8;

	chip8->V[x] = chip8->V[chip8->I];
	chip8->memory[0] = chip8->V[x];
}
