/*
    SPC5 HAL - Copyright (C) 2013 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * SPC564Axx drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 1...15       Lowest...Highest.
 */

#define SPC564Axx_MCUCONF

/*
 * HAL driver system settings.
 */
#define SPC5_NO_INIT                        FALSE
#define SPC5_CLK_BYPASS                     FALSE
#define SPC5_ALLOW_OVERCLOCK                FALSE
#define SPC5_CLK_PREDIV_VALUE               2
#define SPC5_CLK_MFD_VALUE                  75
#define SPC5_CLK_RFD                        SPC5_RFD_DIV2
#define SPC5_FLASH_BIUCR                    (BIUCR_BANK1_TOO |              \
                                             BIUCR_MASTER4_PREFETCH |       \
                                             BIUCR_MASTER0_PREFETCH |       \
                                             BIUCR_DPFEN |                  \
                                             BIUCR_IPFEN |                  \
                                             BIUCR_PFLIM_ON_MISS |          \
                                             BIUCR_BFEN)

/*
 * ADC driver settings.
 */
#define SPC5_ADC_USE_ADC0_Q0                FALSE
#define SPC5_ADC_USE_ADC0_Q1                FALSE
#define SPC5_ADC_USE_ADC0_Q2                FALSE
#define SPC5_ADC_USE_ADC1_Q3                FALSE
#define SPC5_ADC_USE_ADC1_Q4                FALSE
#define SPC5_ADC_USE_ADC1_Q5                FALSE
#define SPC5_ADC_FIFO0_DMA_PRIO             12
#define SPC5_ADC_FIFO1_DMA_PRIO             12
#define SPC5_ADC_FIFO2_DMA_PRIO             12
#define SPC5_ADC_FIFO3_DMA_PRIO             12
#define SPC5_ADC_FIFO4_DMA_PRIO             12
#define SPC5_ADC_FIFO5_DMA_PRIO             12
#define SPC5_ADC_FIFO0_DMA_IRQ_PRIO         12
#define SPC5_ADC_FIFO1_DMA_IRQ_PRIO         12
#define SPC5_ADC_FIFO2_DMA_IRQ_PRIO         12
#define SPC5_ADC_FIFO3_DMA_IRQ_PRIO         12
#define SPC5_ADC_FIFO4_DMA_IRQ_PRIO         12
#define SPC5_ADC_FIFO5_DMA_IRQ_PRIO         12
#define SPC5_ADC_CR_CLK_PS                  ADC_CR_CLK_PS(5)
#define SPC5_ADC_PUDCR                      {ADC_PUDCR_NONE,ADC_PUDCR_NONE,ADC_PUDCR_NONE,ADC_PUDCR_NONE,ADC_PUDCR_NONE,ADC_PUDCR_NONE,ADC_PUDCR_NONE,ADC_PUDCR_NONE}

/*
 * SERIAL driver system settings.
 */
#define SPC5_USE_ESCIA                      TRUE
#define SPC5_USE_ESCIB                      FALSE
#define SPC5_ESCIA_PRIORITY                 8
#define SPC5_ESCIB_PRIORITY                 8

/*
 * ICU - PWM driver system settings.
 */
#define SPC5_ICU_USE_EMIOS_CH0              TRUE
#define SPC5_ICU_USE_EMIOS_CH1              TRUE
#define SPC5_ICU_USE_EMIOS_CH2              TRUE
#define SPC5_ICU_USE_EMIOS_CH3              TRUE
#define SPC5_ICU_USE_EMIOS_CH4              TRUE
#define SPC5_ICU_USE_EMIOS_CH5              TRUE
#define SPC5_ICU_USE_EMIOS_CH6              TRUE
#define SPC5_ICU_USE_EMIOS_CH7              TRUE
#define SPC5_ICU_USE_EMIOS_CH8              TRUE
#define SPC5_ICU_USE_EMIOS_CH16             TRUE
#define SPC5_ICU_USE_EMIOS_CH17             TRUE
#define SPC5_ICU_USE_EMIOS_CH18             TRUE

#define SPC5_PWM_USE_EMIOS_CH9              TRUE
#define SPC5_PWM_USE_EMIOS_CH10             TRUE
#define SPC5_PWM_USE_EMIOS_CH11             TRUE
#define SPC5_PWM_USE_EMIOS_CH12             TRUE
#define SPC5_PWM_USE_EMIOS_CH13             TRUE
#define SPC5_PWM_USE_EMIOS_CH14             TRUE
#define SPC5_PWM_USE_EMIOS_CH15             TRUE
#define SPC5_PWM_USE_EMIOS_CH19             TRUE
#define SPC5_PWM_USE_EMIOS_CH20             TRUE
#define SPC5_PWM_USE_EMIOS_CH21             TRUE
#define SPC5_PWM_USE_EMIOS_CH22             TRUE
#define SPC5_PWM_USE_EMIOS_CH23             TRUE

#define SPC5_EMIOS_GLOBAL_PRESCALER         200
