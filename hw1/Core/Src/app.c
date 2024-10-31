#include "stm32g0xx_hal.h"

void app3() {
	GPIO_PinState prev_button_state = GPIO_PIN_RESET;
	int button_state = 0, prev_timestamp = 0;
	while (1) {
		GPIO_PinState current_button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
		if (button_state == 2 && HAL_GetTick() - prev_timestamp >= 1000) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
			prev_timestamp = HAL_GetTick();
		}
		if (prev_button_state == GPIO_PIN_RESET && current_button_state == GPIO_PIN_SET) {
			button_state = (button_state + 1) % 3;
			switch (button_state) {
				case 0:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
					break;
				case 1:
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
					break;
				case 2:
					break;
			}
		}
		prev_button_state = current_button_state;
	}
}

void app() {
	GPIO_PinState prev_button_state = GPIO_PIN_RESET;
	while (1) {
		GPIO_PinState current_button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
		if (prev_button_state == GPIO_PIN_RESET && current_button_state == GPIO_PIN_SET) {
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		}
		prev_button_state = current_button_state;
	}
}
