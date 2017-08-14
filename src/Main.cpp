#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDOn(LED3);

	int y = 0;

	Oled oled;
	oled.init();
	oled.clear();
	oled.refresh();

	while (1)
	{
		delayMS(50);
		oled.setPixel(y, 0);
		oled.refresh();
		y++;
		STM_EVAL_LEDToggle(LED3);
	}
}


extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	return;
}

extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	return -1;
}
