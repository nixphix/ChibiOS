/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    STM32/adc_lld.h
 * @brief   STM32 ADC subsystem low level driver header.
 *
 * @addtogroup ADC
 * @{
 */

#ifndef _ADC_LLD_H_
#define _ADC_LLD_H_

#if HAL_USE_ADC || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define ADC_CR2_EXTSEL_SRC(n)   ((n) << 17) /**< @brief Trigger source.     */
#define ADC_CR2_EXTSEL_SWSTART  (7 << 17)   /**< @brief Software trigger.   */

#define ADC_CHANNEL_IN0         0   /**< @brief External analog input 0.    */
#define ADC_CHANNEL_IN1         1   /**< @brief External analog input 1.    */
#define ADC_CHANNEL_IN2         2   /**< @brief External analog input 2.    */
#define ADC_CHANNEL_IN3         3   /**< @brief External analog input 3.    */
#define ADC_CHANNEL_IN4         4   /**< @brief External analog input 4.    */
#define ADC_CHANNEL_IN5         5   /**< @brief External analog input 5.    */
#define ADC_CHANNEL_IN6         6   /**< @brief External analog input 6.    */
#define ADC_CHANNEL_IN7         7   /**< @brief External analog input 7.    */
#define ADC_CHANNEL_IN8         8   /**< @brief External analog input 8.    */
#define ADC_CHANNEL_IN9         9   /**< @brief External analog input 9.    */
#define ADC_CHANNEL_IN10        10  /**< @brief External analog input 10.   */
#define ADC_CHANNEL_IN11        11  /**< @brief External analog input 11.   */
#define ADC_CHANNEL_IN12        12  /**< @brief External analog input 12.   */
#define ADC_CHANNEL_IN13        13  /**< @brief External analog input 13.   */
#define ADC_CHANNEL_IN14        14  /**< @brief External analog input 14.   */
#define ADC_CHANNEL_IN15        15  /**< @brief External analog input 15.   */
#define ADC_CHANNEL_SENSOR      16  /**< @brief Internal temperature sensor.*/
#define ADC_CHANNEL_VREFINT     17  /**< @brief Internal reference.         */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   ADC1 driver enable switch.
 * @details If set to @p TRUE the support for ADC1 is included.
 * @note    The default is @p TRUE.
 */
#if !defined(STM32_ADC_USE_ADC1) || defined(__DOXYGEN__)
#define STM32_ADC_USE_ADC1                  TRUE
#endif

/**
 * @brief   ADC1 DMA priority (0..3|lowest..highest).
 */
#if !defined(STM32_ADC_ADC1_DMA_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC1_DMA_PRIORITY         3
#endif

/**
 * @brief   ADC1 interrupt priority level setting.
 */
#if !defined(STM32_ADC_ADC1_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define STM32_ADC_ADC1_IRQ_PRIORITY         5
#endif

/**
 * @brief   ADC1 DMA error hook.
 * @note    The default action for DMA errors is a system halt because DMA error
 *          can only happen because programming errors.
 */
#if !defined(STM32_ADC1_DMA_ERROR_HOOK) || defined(__DOXYGEN__)
#define STM32_ADC1_DMA_ERROR_HOOK() chSysHalt()
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

#if !STM32_ADC_USE_ADC1
#error "ADC driver activated but no ADC peripheral assigned"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   ADC sample data type.
 */
typedef uint16_t adcsample_t;

/**
 * @brief   Channels number in a conversion group.
 */
typedef uint16_t adc_channels_num_t;

/**
 * @brief   Type of a structure representing an ADC driver.
 */
typedef struct ADCDriver ADCDriver;

/**
 * @brief   ADC notification callback type.
 *
 * @param[in] adcp      pointer to the @p ADCDriver object triggering the
 *                      callback
 * @param[in] buffer    pointer to the most recent samples data
 * @param[in] n         number of buffer rows available starting from @p buffer
 */
typedef void (*adccallback_t)(ADCDriver *adcp, adcsample_t *buffer, size_t n);

/**
 * @brief   Conversion group configuration structure.
 * @details This implementation-dependent structure describes a conversion
 *          operation.
 * @note    The use of this configuration structure requires knowledge of
 *          STM32 ADC cell registers interface, please refer to the STM32
 *          reference manual for details.
 */
typedef struct {
  /**
   * @brief Enables the circular buffer mode for the group.
   */
  bool_t                    acg_circular;
  /**
   * @brief Number of the analog channels belonging to the conversion group.
   */
  adc_channels_num_t        acg_num_channels;
  /**
   * @brief Callback function associated to the group or @p NULL.
   * @note  In order to use synchronous functions this field must be set to
   *        @p NULL, callbacks and synchronous operations are mutually
   *        exclusive.
   */
  adccallback_t             acg_endcb;
  /* End of the mandatory fields.*/
  /**
   * @brief ADC CR1 register initialization data.
   * @note  All the required bits must be defined into this field except
   *        @p ADC_CR1_SCAN that is enforced inside the driver.
   */
  uint32_t                  acg_cr1;
  /**
   * @brief ADC CR2 register initialization data.
   * @note  All the required bits must be defined into this field except
   *        @p ADC_CR2_DMA and @p ADC_CR2_ADON that are enforced inside the
   *        driver.
   */
  uint32_t                  acg_cr2;
  /**
   * @brief ADC SMPR1 register initialization data.
   */
  uint32_t                  acg_smpr1;
  /**
   * @brief ADC SMPR2 register initialization data.
   */
  uint32_t                  acg_smpr2;
  /**
   * @brief ADC SQR1 register initialization data.
   */
  uint32_t                  acg_sqr1;
  /**
   * @brief ADC SQR2 register initialization data.
   */
  uint32_t                  acg_sqr2;
  /**
   * @brief ADC SQR3 register initialization data.
   */
  uint32_t                  acg_sqr3;
} ADCConversionGroup;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
} ADCConfig;

/**
 * @brief   Structure representing an ADC driver.
 */
struct ADCDriver {
  /**
   * @brief Driver state.
   */
  adcstate_t                ad_state;
  /**
   * @brief Current configuration data.
   */
  const ADCConfig           *ad_config;
  /**
   * @brief Current samples buffer pointer or @p NULL.
   */
  adcsample_t               *ad_samples;
  /**
   * @brief Current samples buffer depth or @p 0.
   */
  size_t                    ad_depth;
  /**
   * @brief Current conversion group pointer or @p NULL.
   */
  const ADCConversionGroup  *ad_grpp;
#if ADC_USE_WAIT || defined(__DOXYGEN__)
  /**
   * @brief Waiting thread.
   */
  Thread                    *ad_thread;
#endif
#if ADC_USE_MUTUAL_EXCLUSION || defined(__DOXYGEN__)
#if CH_USE_MUTEXES || defined(__DOXYGEN__)
  /**
   * @brief Mutex protecting the peripheral.
   */
  Mutex                     ad_mutex;
#elif CH_USE_SEMAPHORES
  Semaphore                 ad_semaphore;
#endif
#endif /* ADC_USE_MUTUAL_EXCLUSION */
#if defined(ADC_DRIVER_EXT_FIELDS)
  ADC_DRIVER_EXT_FIELDS
#endif
  /* End of the mandatory fields.*/
  /**
   * @brief Pointer to the ADCx registers block.
   */
  ADC_TypeDef               *ad_adc;
  /**
   * @brief Pointer to the DMA registers block.
   */
  stm32_dma_channel_t       *ad_dmachp;
  /**
   * @brief DMA CCR register bit mask.
   */
  uint32_t                  ad_dmaccr;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

#define ADC_SQR1_NUM_CH(n)      (((n) - 1) << 20)

#define ADC_SQR3_SQ0_N(n)       ((n) << 0)
#define ADC_SQR3_SQ1_N(n)       ((n) << 5)
#define ADC_SQR3_SQ2_N(n)       ((n) << 10)
#define ADC_SQR3_SQ3_N(n)       ((n) << 15)
#define ADC_SQR3_SQ4_N(n)       ((n) << 20)
#define ADC_SQR3_SQ5_N(n)       ((n) << 25)

#define ADC_SQR2_SQ6_N(n)       ((n) << 0)
#define ADC_SQR2_SQ7_N(n)       ((n) << 5)
#define ADC_SQR2_SQ8_N(n)       ((n) << 10)
#define ADC_SQR2_SQ9_N(n)       ((n) << 15)
#define ADC_SQR2_SQ10_N(n)      ((n) << 20)
#define ADC_SQR2_SQ11_N(n)      ((n) << 25)

#define ADC_SQR1_SQ13_N(n)      ((n) << 0)
#define ADC_SQR1_SQ14_N(n)      ((n) << 5)
#define ADC_SQR1_SQ15_N(n)      ((n) << 10)
#define ADC_SQR1_SQ16_N(n)      ((n) << 15)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if STM32_ADC_USE_ADC1 && !defined(__DOXYGEN__)
extern ADCDriver ADCD1;
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void adc_lld_init(void);
  void adc_lld_start(ADCDriver *adcp);
  void adc_lld_stop(ADCDriver *adcp);
  void adc_lld_start_conversion(ADCDriver *adcp);
  void adc_lld_stop_conversion(ADCDriver *adcp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_ADC */

#endif /* _ADC_LLD_H_ */

/** @} */
