/****************************************************************************
 * arch/arm/src/mx8mn/hardware/mx8mn_pwm.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/* Reference:
 *   "i.MX 8M Nano Applications Processor Reference Manual",
 *   Document Number: IMX8MNRM Rev. 2, 07/2022. NXP
 *   Section 12.2: Pulse Width Modulation (PWM), pages 2791-2812
 */

#ifndef __ARCH_ARM_SRC_MX8MN_HARDWARE_MX8MN_PWM_H
#define __ARCH_ARM_SRC_MX8MN_HARDWARE_MX8MN_PWM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/mx8mn_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PWM Register Offsets *****************************************************/

#define MX8MN_PWMCR_OFFSET       0x00  /* PWM Control Register */
#define MX8MN_PWMSR_OFFSET       0x04  /* PWM Status Register */
#define MX8MN_PWMIR_OFFSET       0x08  /* PWM Interrupt Register */
#define MX8MN_PWMSAR_OFFSET      0x0C  /* PWM Sample Register */
#define MX8MN_PWMPR_OFFSET       0x10  /* PWM Period Register */
#define MX8MN_PWMCNR_OFFSET      0x14  /* PWM Counter Register */

/* PWM Register Addresses ***************************************************/

/* PWM1 */

#define MX8MN_PWM1_PWMCR         (MX8M_PWM1 + MX8MN_PWMCR_OFFSET)
#define MX8MN_PWM1_PWMSR         (MX8M_PWM1 + MX8MN_PWMSR_OFFSET)
#define MX8MN_PWM1_PWMIR         (MX8M_PWM1 + MX8MN_PWMIR_OFFSET)
#define MX8MN_PWM1_PWMSAR        (MX8M_PWM1 + MX8MN_PWMSAR_OFFSET)
#define MX8MN_PWM1_PWMPR         (MX8M_PWM1 + MX8MN_PWMPR_OFFSET)
#define MX8MN_PWM1_PWMCNR        (MX8M_PWM1 + MX8MN_PWMCNR_OFFSET)

/* PWM2 */

#define MX8MN_PWM2_PWMCR         (MX8M_PWM2 + MX8MN_PWMCR_OFFSET)
#define MX8MN_PWM2_PWMSR         (MX8M_PWM2 + MX8MN_PWMSR_OFFSET)
#define MX8MN_PWM2_PWMIR         (MX8M_PWM2 + MX8MN_PWMIR_OFFSET)
#define MX8MN_PWM2_PWMSAR        (MX8M_PWM2 + MX8MN_PWMSAR_OFFSET)
#define MX8MN_PWM2_PWMPR         (MX8M_PWM2 + MX8MN_PWMPR_OFFSET)
#define MX8MN_PWM2_PWMCNR        (MX8M_PWM2 + MX8MN_PWMCNR_OFFSET)

/* PWM3 */

#define MX8MN_PWM3_PWMCR         (MX8M_PWM3 + MX8MN_PWMCR_OFFSET)
#define MX8MN_PWM3_PWMSR         (MX8M_PWM3 + MX8MN_PWMSR_OFFSET)
#define MX8MN_PWM3_PWMIR         (MX8M_PWM3 + MX8MN_PWMIR_OFFSET)
#define MX8MN_PWM3_PWMSAR        (MX8M_PWM3 + MX8MN_PWMSAR_OFFSET)
#define MX8MN_PWM3_PWMPR         (MX8M_PWM3 + MX8MN_PWMPR_OFFSET)
#define MX8MN_PWM3_PWMCNR        (MX8M_PWM3 + MX8MN_PWMCNR_OFFSET)

/* PWM4 */

#define MX8MN_PWM4_PWMCR         (MX8M_PWM4 + MX8MN_PWMCR_OFFSET)
#define MX8MN_PWM4_PWMSR         (MX8M_PWM4 + MX8MN_PWMSR_OFFSET)
#define MX8MN_PWM4_PWMIR         (MX8M_PWM4 + MX8MN_PWMIR_OFFSET)
#define MX8MN_PWM4_PWMSAR        (MX8M_PWM4 + MX8MN_PWMSAR_OFFSET)
#define MX8MN_PWM4_PWMPR         (MX8M_PWM4 + MX8MN_PWMPR_OFFSET)
#define MX8MN_PWM4_PWMCNR        (MX8M_PWM4 + MX8MN_PWMCNR_OFFSET)

/* PWM Control Register (PWMCR) Bit Definitions *****************************/

#define PWMCR_FWM_SHIFT          (26)      /* Bits 26-27: FIFO Water Mark */
#define PWMCR_FWM_MASK           (0x3 << PWMCR_FWM_SHIFT)
#  define PWMCR_FWM_1SLOT        (0x0 << PWMCR_FWM_SHIFT) /* FIFO empty when >= 1 slot */
#  define PWMCR_FWM_2SLOT        (0x1 << PWMCR_FWM_SHIFT) /* FIFO empty when >= 2 slots */
#  define PWMCR_FWM_3SLOT        (0x2 << PWMCR_FWM_SHIFT) /* FIFO empty when >= 3 slots */
#  define PWMCR_FWM_4SLOT        (0x3 << PWMCR_FWM_SHIFT) /* FIFO empty when >= 4 slots */

#define PWMCR_STOPEN             (1 << 25) /* Bit 25: Stop Mode Enable */
#define PWMCR_DOZEN              (1 << 24) /* Bit 24: Doze Mode Enable */
#define PWMCR_WAITEN             (1 << 23) /* Bit 23: Wait Mode Enable */
#define PWMCR_DBGEN              (1 << 22) /* Bit 22: Debug Mode Enable */
#define PWMCR_BCTR               (1 << 21) /* Bit 21: Byte Data Swap Control */
#define PWMCR_HCTR               (1 << 20) /* Bit 20: Half-word Data Swap Control */

#define PWMCR_POUTC_SHIFT        (18)      /* Bits 18-19: PWM Output Configuration */
#define PWMCR_POUTC_MASK         (0x3 << PWMCR_POUTC_SHIFT)
#  define PWMCR_POUTC_SET_ROLL   (0x0 << PWMCR_POUTC_SHIFT) /* Set at rollover, clear at compare */
#  define PWMCR_POUTC_CLR_ROLL   (0x1 << PWMCR_POUTC_SHIFT) /* Clear at rollover, set at compare */
#  define PWMCR_POUTC_DISC1      (0x2 << PWMCR_POUTC_SHIFT) /* Output disconnected */
#  define PWMCR_POUTC_DISC2      (0x3 << PWMCR_POUTC_SHIFT) /* Output disconnected */

#define PWMCR_CLKSRC_SHIFT       (16)      /* Bits 16-17: Clock Source Select */
#define PWMCR_CLKSRC_MASK        (0x3 << PWMCR_CLKSRC_SHIFT)
#  define PWMCR_CLKSRC_OFF       (0x0 << PWMCR_CLKSRC_SHIFT) /* Clock off */
#  define PWMCR_CLKSRC_IPG       (0x1 << PWMCR_CLKSRC_SHIFT) /* ipg_clk (24 MHz) */
#  define PWMCR_CLKSRC_HIGHFREQ  (0x2 << PWMCR_CLKSRC_SHIFT) /* ipg_clk_highfreq */
#  define PWMCR_CLKSRC_32K       (0x3 << PWMCR_CLKSRC_SHIFT) /* ipg_clk_32k (32 kHz) */

#define PWMCR_PRESCALER_SHIFT    (4)       /* Bits 4-15: Clock Prescaler */
#define PWMCR_PRESCALER_MASK     (0xfff << PWMCR_PRESCALER_SHIFT)
#define PWMCR_PRESCALER(n)       (((n) << PWMCR_PRESCALER_SHIFT) & PWMCR_PRESCALER_MASK)

#define PWMCR_SWR                (1 << 3)  /* Bit 3: Software Reset */

#define PWMCR_REPEAT_SHIFT       (1)       /* Bits 1-2: Sample Repeat */
#define PWMCR_REPEAT_MASK        (0x3 << PWMCR_REPEAT_SHIFT)
#  define PWMCR_REPEAT_1X        (0x0 << PWMCR_REPEAT_SHIFT) /* Use each sample once */
#  define PWMCR_REPEAT_2X        (0x1 << PWMCR_REPEAT_SHIFT) /* Use each sample twice */
#  define PWMCR_REPEAT_4X        (0x2 << PWMCR_REPEAT_SHIFT) /* Use each sample 4 times */
#  define PWMCR_REPEAT_8X        (0x3 << PWMCR_REPEAT_SHIFT) /* Use each sample 8 times */

#define PWMCR_EN                 (1 << 0)  /* Bit 0: PWM Enable */

/* PWM Status Register (PWMSR) Bit Definitions ******************************/

#define PWMSR_FWE                (1 << 6)  /* Bit 6: FIFO Write Error Status */
#define PWMSR_CMP                (1 << 5)  /* Bit 5: Compare Event */
#define PWMSR_ROV                (1 << 4)  /* Bit 4: Rollover Status */
#define PWMSR_FE                 (1 << 3)  /* Bit 3: FIFO Empty */

#define PWMSR_FIFOAV_SHIFT       (0)       /* Bits 0-2: FIFO Available Slots */
#define PWMSR_FIFOAV_MASK        (0x7 << PWMSR_FIFOAV_SHIFT)

/* PWM Interrupt Register (PWMIR) Bit Definitions ***************************/

#define PWMIR_CIE                (1 << 2)  /* Bit 2: Compare Interrupt Enable */
#define PWMIR_RIE                (1 << 1)  /* Bit 1: Rollover Interrupt Enable */
#define PWMIR_FIE                (1 << 0)  /* Bit 0: FIFO Empty Interrupt Enable */

/* PWM Sample Register (PWMSAR) Bit Definitions *****************************/

#define PWMSAR_SAMPLE_SHIFT      (0)       /* Bits 0-15: Sample Value */
#define PWMSAR_SAMPLE_MASK       (0xffff << PWMSAR_SAMPLE_SHIFT)
#define PWMSAR_SAMPLE(n)         (((n) << PWMSAR_SAMPLE_SHIFT) & PWMSAR_SAMPLE_MASK)

/* PWM Period Register (PWMPR) Bit Definitions ******************************/

#define PWMPR_PERIOD_SHIFT       (0)       /* Bits 0-15: Period Value */
#define PWMPR_PERIOD_MASK        (0xffff << PWMPR_PERIOD_SHIFT)
#define PWMPR_PERIOD(n)          (((n) << PWMPR_PERIOD_SHIFT) & PWMPR_PERIOD_MASK)

/* PWM Counter Register (PWMCNR) Bit Definitions ****************************/

#define PWMCNR_COUNT_SHIFT       (0)       /* Bits 0-15: Counter Value */
#define PWMCNR_COUNT_MASK        (0xffff << PWMCNR_COUNT_SHIFT)

/* PWM Clock Frequencies ****************************************************/

#define MX8MN_PWM_IPG_CLK_FREQ   24000000  /* 24 MHz ipg_clk */
#define MX8MN_PWM_32K_CLK_FREQ   32768     /* 32 kHz ipg_clk_32k */

/* PWM Calculation Macros ***************************************************/

/* Calculate prescaler value for desired output frequency
 * freq_out = freq_in / ((prescaler + 1) * (period + 2))
 */

#define PWM_CALC_PRESCALER(freq_in, freq_out, period) \
  (((freq_in) / ((freq_out) * ((period) + 2))) - 1)

/* Calculate period value for desired output frequency
 * period = (freq_in / ((prescaler + 1) * freq_out)) - 2
 */

#define PWM_CALC_PERIOD(freq_in, freq_out, prescaler) \
  (((freq_in) / (((prescaler) + 1) * (freq_out))) - 2)

/* Calculate sample value (duty cycle) from microseconds
 * sample = (duty_us * pclk) / 1000000
 * where pclk = freq_in / (prescaler + 1)
 */

#define PWM_CALC_SAMPLE_US(freq_in, prescaler, duty_us) \
  (((uint64_t)(duty_us) * ((freq_in) / ((prescaler) + 1))) / 1000000)

/* Calculate duty cycle percentage
 * duty_pct = (sample * 100) / (period + 2)
 */

#define PWM_CALC_DUTY_PCT(sample, period) \
  (((sample) * 100) / ((period) + 2))

#endif /* __ARCH_ARM_SRC_MX8MN_HARDWARE_MX8MN_PWM_H */
