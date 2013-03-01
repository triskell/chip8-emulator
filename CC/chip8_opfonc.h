/*
 * chip8_opfonc.h
 *
 *  Created on: 25 févr. 2013
 *      Author: isen
 */

#ifndef CHIP8_OPFONC_H_
#define CHIP8_OPFONC_H_

	#include <math.h>
	#include "chip8_def.h"

	void chip8_OF_cls(Chip8 *chip8);
	void chip8_OF_ret(Chip8 *chip8);
	void chip8_OF_jmp(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_call(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_se_vx_b(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_sne_vx_b(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_se_vx_vy(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_se_vx_vy(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_vx_b(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_add_vx_b(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_vx_vy(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_or(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_and(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_xor(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_add_vx_vy(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_sub(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_shr(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_subn(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_shl(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_sne_vx_vy(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_i_addr(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_jmp_vo(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_rnd(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_drw(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_skp(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_sknp(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_vx_dt(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_vx_k(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_dt_vx(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_st_vx(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_add_i_vx(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_f_vx(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_b_vx(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_i_vx(Chip8 *chip8, unsigned short opcode);
	void chip8_OF_ld_vx_i(Chip8 *chip8, unsigned short opcode);

#endif /* CHIP8_OPFONC_H_ */
