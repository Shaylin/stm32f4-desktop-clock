#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"
#include "VectorText.hpp"
#include "Calendar.hpp"

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);

	STM_EVAL_LEDInit(LED3);

	Oled oled;

	oled.clear();
	uint8_t contrast = 0x00;

	VectorText text(oled);

	Calendar calendar;

	TimeAndDate timeAndDate;


	text.setText("crab");
	text.drawAt(48, 0, 0.5);

	text.setText("volume");
	text.drawAt(0, 16, 0.7);

	while (1)
	{
		delayMS(50);
		oled.setContrast(contrast += 0x10);
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
