#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


int main(void)
{
  int i = 0;

  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  /* Turn on LEDs */
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED5);
  STM_EVAL_LEDOn(LED6);

  /* Infinite loop */
  while (1)
  {
	i++;
  }
}


extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  return;
}

extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  return -1;
}
