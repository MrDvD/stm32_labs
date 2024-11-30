#include "stm32g0xx_hal.h"

void SETBIT(uint32_t *Value, uint32_t NumBit) {
	// sets the input bit to 1
	if (0 <= NumBit && NumBit < 32) {
		uint32_t mask = 1 << NumBit;
		*Value |= mask;
	}
}

void CLRBIT(uint32_t *Value, uint32_t NumBit) {
	// sets the input bit to 0
	if (0 <= NumBit && NumBit < 32) {
		uint32_t mask = 1 << NumBit;
		*Value &= ~mask;
	}
}

int GETBIT(uint32_t *Value, uint32_t NumBit) {
	// reads the value of input bit
	if (0 <= NumBit && NumBit < 32) {
		uint32_t mask = 1 << NumBit;
		return (*Value & mask) > 0;
	}
	return 0;
}

uint32_t *STK_CSR = (uint32_t *) 0xE000E010UL;
uint32_t *STK_RVR = (uint32_t *) 0xE000E014UL;

void setup_systick() {
	CLRBIT(STK_CSR, 0);
	CLRBIT(STK_CSR, 1);
	SETBIT(STK_CSR, 2);
	*STK_RVR = 16000UL - 1UL;
	SETBIT(STK_CSR, 0);
}

void func() {
	int percentage_normalized = 0;
	int rising = 1;
	int loop = 0;
	setup_systick();
	while (1) {
		if (GETBIT(STK_CSR, 16)) {
			loop = (loop + 1) % 250;
			if (!loop) {
				percentage_normalized += rising ? 1 : -1;
				if (percentage_normalized % 20 == 0) {
					rising ^= 1;
				}
			}
			if (loop % 20 < percentage_normalized) {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			} else {
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
			}
		}
	}
}
