/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2023/07/08
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *OPA2 is used as a voltage follower output, the external voltage
 *is output to OPA1, and the ADC samples OPA1
 *OPA1_CHP0--PB15
 *OPA1_CHN0--PB11
 *OPA1_OUT--PA3
 *
 *In this example, PA5 and PA4 are short-circuited, and the external voltage is input from PA7.
 *If the negative feedback is connected to a resistor, it can also form an operational amplifier.
 */

#include "debug.h"

//#define OPA_LowPower   1

/*********************************************************************
 * @fn      OPA1_Init
 *
 * @brief   Initializes OPA1.
 *
 * @return  none
 */
void OPA1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    OPA_InitTypeDef  OPA_InitStructure={0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOB, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    OPA_InitStructure.OPA_NUM = OPA1;
    OPA_InitStructure.PSEL = CHP0;
    OPA_InitStructure.NSEL = CHN0;
    OPA_InitStructure.Mode = OUT_IO_OUT0;
    OPA_Init(&OPA_InitStructure);
    OPA_Cmd(OPA1,ENABLE);

#if (OPA_LowPower == 1)
    OPA_LP_Cmd(ENABLE);

#endif
}

/*********************************************************************
 * @fn      ADC_Function_Init
 *
 * @brief   Initializes ADC collection.
 *
 * @return  none
 */
void ADC_Function_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure={0};
    ADC_InitTypeDef ADC_InitStructure={0};

    RCC_PB2PeriphClockCmd(RCC_PB2Periph_GPIOA, ENABLE );
    RCC_PB2PeriphClockCmd(RCC_PB2Periph_ADC1, ENABLE );
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);
}

/*********************************************************************
 * @fn      Get_ADC_Val
 *
 * @brief   Returns ADCx conversion result data.
 *
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 *            ADC_Channel_2 - ADC Channel2 selected.
 *            ADC_Channel_3 - ADC Channel3 selected.
 *            ADC_Channel_4 - ADC Channel4 selected.
 *            ADC_Channel_5 - ADC Channel5 selected.
 *            ADC_Channel_6 - ADC Channel6 selected.
 *            ADC_Channel_7 - ADC Channel7 selected.
 *            ADC_Channel_8 - ADC Channel8 selected.
 *            ADC_Channel_9 - ADC Channel9 selected.
 *            ADC_Channel_16 - ADC Channel16 selected.
 *            ADC_Channel_17 - ADC Channel17 selected.
 *
 * @return  none
 */
u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_CyclesMode7);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));
    val = ADC_GetConversionValue(ADC1);

    return val;
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    u32 adc_val=0;
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );
    OPCM_Unlock();
    OPA1_Init();

    ADC_Function_Init();
    while(1)
    {
        adc_val= Get_ADC_Val(ADC_Channel_3);
        printf("adc_val  %d\r\n",adc_val);
        Delay_Ms(1000);
    }
}


