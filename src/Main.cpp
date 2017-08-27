#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"
#include "Oled.hpp"
#include "VectorText.hpp"
#include "Calendar.hpp"
#include <string>

int main(void)
{
	SysTick_Config(SystemCoreClock / 1000);

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

	Oled oled;
	oled.clear();

	VectorText text(oled);

	Calendar calendar;
//	TimeAndDate x;
//	x.date = 27;
//	x.dayOfWeek = 6;
//	x.hours = 8;
//	x.minutes = 53;
//	x.month = 8;
//	x.seconds = 0;
//	x.year = 17;
//	calendar.setTimeAndDate(x);

	TimeAndDate timeAndDate = calendar.getTimeAndDate();

	std::string time = "00:00";
	std::string dayOfWeek = daysOfTheWeek[timeAndDate.dayOfWeek];
	std::string dateAndMonth = "00/00";

	uint8_t temperatureByte;
	std::string temperature = "00";

	while (1)
	{
		delayMS(1000);
		oled.clear();

		if (STM_EVAL_PBGetState(BUTTON_USER) == 1)
		{
			text.setText("Temperature");
			text.drawAt(16, 0, 0.48);

			temperatureByte = calendar.getTemperature();
			temperature[0] = temperatureByte / 10 + 48;
			temperature[1] = temperatureByte %10 + 48;

			text.setText(temperature);
			text.drawAt(32, 16, 1.5);

			STM_EVAL_LEDToggle(LED4);
		}
		else
		{
			timeAndDate = calendar.getTimeAndDate();
			time[0] = timeAndDate.hours / 10 + 48;
			time[1] = timeAndDate.hours % 10 + 48;
			time[3] = timeAndDate.minutes / 10 + 48;
			time[4] = timeAndDate.minutes % 10 + 48;

			dayOfWeek = daysOfTheWeek[timeAndDate.dayOfWeek];
			dateAndMonth[0] = timeAndDate.date / 10 + 48;
			dateAndMonth[1] = timeAndDate.date % 10 + 48;
			dateAndMonth[3] = timeAndDate.month / 10 + 48;
			dateAndMonth[4] = timeAndDate.month % 10 + 48;

			text.setText(dayOfWeek);
			text.drawAt(0, 0, 0.45);

			text.setText(dateAndMonth);
			text.drawAt(80, 0, 0.48);

			text.setText(time);
			text.drawAt(4, 16, 1.3);

			STM_EVAL_LEDToggle(LED3);
		}

		oled.refresh();
	}
}


extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	return;
}

extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	return -1;
}
