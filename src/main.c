#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"
bool on = true;
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
    on = !on;
    if(on) GPIO_WriteHigh(GPIOD, GPIO_PIN_3); else GPIO_WriteLow(GPIOD, GPIO_PIN_3);
}
void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    //GPIO_Init(GPIO_MODE_OUT_OD_LOW_SLOW);
    GPIO_Init(GPIOE,GPIO_PIN_0,GPIO_MODE_OUT_OD_LOW_SLOW); //D2
    GPIO_Init(GPIOD,GPIO_PIN_1,GPIO_MODE_IN_PU_IT);        //D7
    GPIO_Init(GPIOD,GPIO_PIN_3,GPIO_MODE_OUT_PP_LOW_SLOW); //D8

    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);     // nastavení priority přerušení     
    ITC_SetSoftwarePriority(ITC_IRQ_PORTD, ITC_PRIORITYLEVEL_1);     // povolení přeruření     
    enableInterrupts();


    init_milis();
    //init_uart1();
}


int main(void){ 

  
    uint32_t time = 0;

    init();
    
    while (1) {



        if (milis() - time > 1000 ) {
            GPIO_WriteHigh(GPIOE, GPIO_PIN_0);
            
            GPIO_WriteLow(GPIOE, GPIO_PIN_0);
            //on = !on;
            //if(on) GPIO_WriteHigh(GPIOD, GPIO_PIN_3); else GPIO_WriteLow(GPIOD, GPIO_PIN_3);
            time = milis();
            //printf("%ld\n", time);
        }
        //delay_ms(333);
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"

