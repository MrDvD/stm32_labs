/*
 * funcs.h
 *
 *  Created on: Nov 14, 2024
 *      Author: userml
 */

#ifndef INC_FUNCS_H_
#define INC_FUNCS_H_

void SETBIT(uint32_t *Value, uint32_t NumBit);
void CLRBIT(uint32_t *Value, uint32_t NumBit);
int GETBIT(uint32_t *Value, uint32_t NumBit);
void setup_systick();
void func();

#endif /* INC_FUNCS_H_ */
