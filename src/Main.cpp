#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"
#include "VectorText.hpp"

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDOn(LED3);

	Oled oled;
	oled.init();
	oled.clear();

	VectorText text(oled);
//	text.setText("1234");
//	text.drawAt(0, 0, 1);
	text.drawLine(9, 21, 1, 0);
	text.drawLine(9, 21, 17, 0);
	text.drawLine(4, 7, 14, 7);

	oled.refresh();

	while (1)
	{
		delayMS(50);
		oled.refresh();
		STM_EVAL_LEDToggle(LED3);
	}
}


extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	return;
}

extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	return -1;
}
