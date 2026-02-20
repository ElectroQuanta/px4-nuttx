/****************************************************************************
 * arch/arm/src/mx8mn/hardware/mx8mn_gpt.h
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
 */

#ifndef __ARCH_ARM_SRC_MX8MN_HARDWARE_MX8MN_GPT_H
#define __ARCH_ARM_SRC_MX8MN_HARDWARE_MX8MN_GPT_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "hardware/mx8mn_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Register Offsets *********************************************************/

#define MX8MN_GPT_CR_OFFSET      0x0000  /* GPT Control Register */
#define MX8MN_GPT_PR_OFFSET      0x0004  /* GPT Prescaler Register */
#define MX8MN_GPT_SR_OFFSET      0x0008  /* GPT Status Register */
#define MX8MN_GPT_IR_OFFSET      0x000c  /* GPT Interrupt Register */
#define MX8MN_GPT_OCR1_OFFSET    0x0010  /* GPT Output Compare Register 1 */
#define MX8MN_GPT_OCR2_OFFSET    0x0014  /* GPT Output Compare Register 2 */
#define MX8MN_GPT_OCR3_OFFSET    0x0018  /* GPT Output Compare Register 3 */
#define MX8MN_GPT_ICR1_OFFSET    0x001c  /* GPT Input Capture Register 1 */
#define MX8MN_GPT_ICR2_OFFSET    0x0020  /* GPT Input Capture Register 2 */
#define MX8MN_GPT_CNT_OFFSET     0x0024  /* GPT Counter Register */

/* Register Addresses *******************************************************/

#define MX8MN_GPT1_CR            (MX8M_GPT1 + MX8MN_GPT_CR_OFFSET)
#define MX8MN_GPT1_PR            (MX8M_GPT1 + MX8MN_GPT_PR_OFFSET)
#define MX8MN_GPT1_SR            (MX8M_GPT1 + MX8MN_GPT_SR_OFFSET)
#define MX8MN_GPT1_IR            (MX8M_GPT1 + MX8MN_GPT_IR_OFFSET)
#define MX8MN_GPT1_OCR1          (MX8M_GPT1 + MX8MN_GPT_OCR1_OFFSET)
#define MX8MN_GPT1_OCR2          (MX8M_GPT1 + MX8MN_GPT_OCR2_OFFSET)
#define MX8MN_GPT1_OCR3          (MX8M_GPT1 + MX8MN_GPT_OCR3_OFFSET)
#define MX8MN_GPT1_ICR1          (MX8M_GPT1 + MX8MN_GPT_ICR1_OFFSET)
#define MX8MN_GPT1_ICR2          (MX8M_GPT1 + MX8MN_GPT_ICR2_OFFSET)
#define MX8MN_GPT1_CNT           (MX8M_GPT1 + MX8MN_GPT_CNT_OFFSET)

#define MX8MN_GPT2_CR            (MX8M_GPT2 + MX8MN_GPT_CR_OFFSET)
#define MX8MN_GPT2_PR            (MX8M_GPT2 + MX8MN_GPT_PR_OFFSET)
#define MX8MN_GPT2_SR            (MX8M_GPT2 + MX8MN_GPT_SR_OFFSET)
#define MX8MN_GPT2_IR            (MX8M_GPT2 + MX8MN_GPT_IR_OFFSET)
#define MX8MN_GPT2_OCR1          (MX8M_GPT2 + MX8MN_GPT_OCR1_OFFSET)
#define MX8MN_GPT2_OCR2          (MX8M_GPT2 + MX8MN_GPT_OCR2_OFFSET)
#define MX8MN_GPT2_OCR3          (MX8M_GPT2 + MX8MN_GPT_OCR3_OFFSET)
#define MX8MN_GPT2_ICR1          (MX8M_GPT2 + MX8MN_GPT_ICR1_OFFSET)
#define MX8MN_GPT2_ICR2          (MX8M_GPT2 + MX8MN_GPT_ICR2_OFFSET)
#define MX8MN_GPT2_CNT           (MX8M_GPT2 + MX8MN_GPT_CNT_OFFSET)

#define MX8MN_GPT3_CR            (MX8M_GPT3 + MX8MN_GPT_CR_OFFSET)
#define MX8MN_GPT3_PR            (MX8M_GPT3 + MX8MN_GPT_PR_OFFSET)
#define MX8MN_GPT3_SR            (MX8M_GPT3 + MX8MN_GPT_SR_OFFSET)
#define MX8MN_GPT3_IR            (MX8M_GPT3 + MX8MN_GPT_IR_OFFSET)
#define MX8MN_GPT3_OCR1          (MX8M_GPT3 + MX8MN_GPT_OCR1_OFFSET)
#define MX8MN_GPT3_OCR2          (MX8M_GPT3 + MX8MN_GPT_OCR2_OFFSET)
#define MX8MN_GPT3_OCR3          (MX8M_GPT3 + MX8MN_GPT_OCR3_OFFSET)
#define MX8MN_GPT3_ICR1          (MX8M_GPT3 + MX8MN_GPT_ICR1_OFFSET)
#define MX8MN_GPT3_ICR2          (MX8M_GPT3 + MX8MN_GPT_ICR2_OFFSET)
#define MX8MN_GPT3_CNT           (MX8M_GPT3 + MX8MN_GPT_CNT_OFFSET)

#define MX8MN_GPT4_CR            (MX8M_GPT4 + MX8MN_GPT_CR_OFFSET)
#define MX8MN_GPT4_PR            (MX8M_GPT4 + MX8MN_GPT_PR_OFFSET)
#define MX8MN_GPT4_SR            (MX8M_GPT4 + MX8MN_GPT_SR_OFFSET)
#define MX8MN_GPT4_IR            (MX8M_GPT4 + MX8MN_GPT_IR_OFFSET)
#define MX8MN_GPT4_OCR1          (MX8M_GPT4 + MX8MN_GPT_OCR1_OFFSET)
#define MX8MN_GPT4_OCR2          (MX8M_GPT4 + MX8MN_GPT_OCR2_OFFSET)
#define MX8MN_GPT4_OCR3          (MX8M_GPT4 + MX8MN_GPT_OCR3_OFFSET)
#define MX8MN_GPT4_ICR1          (MX8M_GPT4 + MX8MN_GPT_ICR1_OFFSET)
#define MX8MN_GPT4_ICR2          (MX8M_GPT4 + MX8MN_GPT_ICR2_OFFSET)
#define MX8MN_GPT4_CNT           (MX8M_GPT4 + MX8MN_GPT_CNT_OFFSET)

#define MX8MN_GPT5_CR            (MX8M_GPT5 + MX8MN_GPT_CR_OFFSET)
#define MX8MN_GPT5_PR            (MX8M_GPT5 + MX8MN_GPT_PR_OFFSET)
#define MX8MN_GPT5_SR            (MX8M_GPT5 + MX8MN_GPT_SR_OFFSET)
#define MX8MN_GPT5_IR            (MX8M_GPT5 + MX8MN_GPT_IR_OFFSET)
#define MX8MN_GPT5_OCR1          (MX8M_GPT5 + MX8MN_GPT_OCR1_OFFSET)
#define MX8MN_GPT5_OCR2          (MX8M_GPT5 + MX8MN_GPT_OCR2_OFFSET)
#define MX8MN_GPT5_OCR3          (MX8M_GPT5 + MX8MN_GPT_OCR3_OFFSET)
#define MX8MN_GPT5_ICR1          (MX8M_GPT5 + MX8MN_GPT_ICR1_OFFSET)
#define MX8MN_GPT5_ICR2          (MX8M_GPT5 + MX8MN_GPT_ICR2_OFFSET)
#define MX8MN_GPT5_CNT           (MX8M_GPT5 + MX8MN_GPT_CNT_OFFSET)

#define MX8MN_GPT6_CR            (MX8M_GPT6 + MX8MN_GPT_CR_OFFSET)
#define MX8MN_GPT6_PR            (MX8M_GPT6 + MX8MN_GPT_PR_OFFSET)
#define MX8MN_GPT6_SR            (MX8M_GPT6 + MX8MN_GPT_SR_OFFSET)
#define MX8MN_GPT6_IR            (MX8M_GPT6 + MX8MN_GPT_IR_OFFSET)
#define MX8MN_GPT6_OCR1          (MX8M_GPT6 + MX8MN_GPT_OCR1_OFFSET)
#define MX8MN_GPT6_OCR2          (MX8M_GPT6 + MX8MN_GPT_OCR2_OFFSET)
#define MX8MN_GPT6_OCR3          (MX8M_GPT6 + MX8MN_GPT_OCR3_OFFSET)
#define MX8MN_GPT6_ICR1          (MX8M_GPT6 + MX8MN_GPT_ICR1_OFFSET)
#define MX8MN_GPT6_ICR2          (MX8M_GPT6 + MX8MN_GPT_ICR2_OFFSET)
#define MX8MN_GPT6_CNT           (MX8M_GPT6 + MX8MN_GPT_CNT_OFFSET)

/* Register Bit Definitions *************************************************/

/* GPT Control Register (GPT_CR) */

#define GPT_CR_EN                (1 << 0)   /* Bit 0: GPT Enable */
#define GPT_CR_ENMOD             (1 << 1)   /* Bit 1: GPT Enable Mode */
#define GPT_CR_DBGEN             (1 << 2)   /* Bit 2: GPT Debug Mode Enable */
#define GPT_CR_WAITEN            (1 << 3)   /* Bit 3: GPT Wait Mode Enable */
#define GPT_CR_DOZEEN            (1 << 4)   /* Bit 4: GPT Doze Mode Enable */
#define GPT_CR_STOPEN            (1 << 5)   /* Bit 5: GPT Stop Mode Enable */

#define GPT_CR_CLKSRC_SHIFT      (6)        /* Bits 6-8: Clock Source Select */
#define GPT_CR_CLKSRC_MASK       (7 << GPT_CR_CLKSRC_SHIFT)
#  define GPT_CR_CLKSRC(n)       ((uint32_t)(n) << GPT_CR_CLKSRC_SHIFT)
#  define GPT_CR_CLKSRC_NONE     (0 << GPT_CR_CLKSRC_SHIFT)  /* No clock */
#  define GPT_CR_CLKSRC_IPG      (1 << GPT_CR_CLKSRC_SHIFT)  /* Peripheral Clock (ipg_clk) */
#  define GPT_CR_CLKSRC_IPG_HFR  (2 << GPT_CR_CLKSRC_SHIFT)  /* High Frequency Reference Clock (ipg_clk_highfreq) */
#  define GPT_CR_CLKSRC_EXT      (3 << GPT_CR_CLKSRC_SHIFT)  /* External Clock */
#  define GPT_CR_CLKSRC_IPG_LFR  (4 << GPT_CR_CLKSRC_SHIFT)  /* Low Frequency Reference Clock (ipg_clk_32k) */
#  define GPT_CR_CLKSRC_IPG_24M  (5 << GPT_CR_CLKSRC_SHIFT)  /* Crystal oscillator as Reference Clock (ipg_clk_24M) */

#define GPT_CR_FRR               (1 << 9)   /* Bit 9: Free-Run or Restart Mode */
#define GPT_CR_EN_24M            (1 << 10)  /* Bit 10: Enable 24 MHz Clock Input from Crystal */
                                            /* Bits 11-14: Reserved */
#define GPT_CR_SWR               (1 << 15)  /* Bit 15: Software Reset */

#define GPT_CR_IM1_SHIFT         (16)       /* Bits 16-17: Input Capture Channel 1 Operating Mode */
#define GPT_CR_IM1_MASK          (3 << GPT_CR_IM1_SHIFT)
#  define GPT_CR_IM1(n)          ((uint32_t)(n) << GPT_CR_IM1_SHIFT)
#  define GPT_CR_IM1_DIS         (0 << GPT_CR_IM1_SHIFT)  /* Capture disabled */
#  define GPT_CR_IM1_RISING      (1 << GPT_CR_IM1_SHIFT)  /* Capture on rising edge */
#  define GPT_CR_IM1_FALLING     (2 << GPT_CR_IM1_SHIFT)  /* Capture on falling edge */
#  define GPT_CR_IM1_BOTH        (3 << GPT_CR_IM1_SHIFT)  /* Capture on both edges */

#define GPT_CR_IM2_SHIFT         (18)       /* Bits 18-19: Input Capture Channel 2 Operating Mode */
#define GPT_CR_IM2_MASK          (3 << GPT_CR_IM2_SHIFT)
#  define GPT_CR_IM2(n)          ((uint32_t)(n) << GPT_CR_IM2_SHIFT)
#  define GPT_CR_IM2_DIS         (0 << GPT_CR_IM2_SHIFT)  /* Capture disabled */
#  define GPT_CR_IM2_RISING      (1 << GPT_CR_IM2_SHIFT)  /* Capture on rising edge */
#  define GPT_CR_IM2_FALLING     (2 << GPT_CR_IM2_SHIFT)  /* Capture on falling edge */
#  define GPT_CR_IM2_BOTH        (3 << GPT_CR_IM2_SHIFT)  /* Capture on both edges */

#define GPT_CR_OM1_SHIFT         (20)       /* Bits 20-22: Output Compare Channel 1 Operating Mode */
#define GPT_CR_OM1_MASK          (7 << GPT_CR_OM1_SHIFT)
#  define GPT_CR_OM1(n)          ((uint32_t)(n) << GPT_CR_OM1_SHIFT)
#  define GPT_CR_OM1_DIS         (0 << GPT_CR_OM1_SHIFT)  /* Output disconnected. No response on pin. */
#  define GPT_CR_OM1_TOGGLE      (1 << GPT_CR_OM1_SHIFT)  /* Toggle output pin */
#  define GPT_CR_OM1_CLEAR       (2 << GPT_CR_OM1_SHIFT)  /* Clear output pin */
#  define GPT_CR_OM1_SET         (3 << GPT_CR_OM1_SHIFT)  /* Set output pin */
#  define GPT_CR_OM1_PULSE       (4 << GPT_CR_OM1_SHIFT)  /* Generate an active low pulse */

#define GPT_CR_OM2_SHIFT         (23)       /* Bits 23-25: Output Compare Channel 2 Operating Mode */
#define GPT_CR_OM2_MASK          (7 << GPT_CR_OM2_SHIFT)
#  define GPT_CR_OM2(n)          ((uint32_t)(n) << GPT_CR_OM2_SHIFT)
#  define GPT_CR_OM2_DIS         (0 << GPT_CR_OM2_SHIFT)  /* Output disconnected. No response on pin. */
#  define GPT_CR_OM2_TOGGLE      (1 << GPT_CR_OM2_SHIFT)  /* Toggle output pin */
#  define GPT_CR_OM2_CLEAR       (2 << GPT_CR_OM2_SHIFT)  /* Clear output pin */
#  define GPT_CR_OM2_SET         (3 << GPT_CR_OM2_SHIFT)  /* Set output pin */
#  define GPT_CR_OM2_PULSE       (4 << GPT_CR_OM2_SHIFT)  /* Generate an active low pulse */

#define GPT_CR_OM3_SHIFT         (26)       /* Bits 26-28: Output Compare Channel 3 Operating Mode */
#define GPT_CR_OM3_MASK          (7 << GPT_CR_OM3_SHIFT)
#  define GPT_CR_OM3(n)          ((uint32_t)(n) << GPT_CR_OM3_SHIFT)
#  define GPT_CR_OM3_DIS         (0 << GPT_CR_OM3_SHIFT)  /* Output disconnected. No response on pin. */
#  define GPT_CR_OM3_TOGGLE      (1 << GPT_CR_OM3_SHIFT)  /* Toggle output pin */
#  define GPT_CR_OM3_CLEAR       (2 << GPT_CR_OM3_SHIFT)  /* Clear output pin */
#  define GPT_CR_OM3_SET         (3 << GPT_CR_OM3_SHIFT)  /* Set output pin */
#  define GPT_CR_OM3_PULSE       (4 << GPT_CR_OM3_SHIFT)  /* Generate an active low pulse */

#define GPT_CR_FO1               (1 << 29)  /* Bit 29: Force Output Compare Channel 1 */
#define GPT_CR_FO2               (1 << 30)  /* Bit 30: Force Output Compare Channel 2 */
#define GPT_CR_FO3               (1 << 31)  /* Bit 31: Force Output Compare Channel 3 */

/* GPT Prescaler Register (GPT_PR) */

#define GPT_PR_PRESCALER_SHIFT   (0)        /* Bits 0-11: Prescaler Value */
#define GPT_PR_PRESCALER_MASK    (0xfff << GPT_PR_PRESCALER_SHIFT)
#  define GPT_PR_PRESCALER(n)    ((uint32_t)(n) << GPT_PR_PRESCALER_SHIFT)

#define GPT_PR_PRESCALER24M_SHIFT (12)      /* Bits 12-15: Prescaler Value for 24M Clock */
#define GPT_PR_PRESCALER24M_MASK (0xf << GPT_PR_PRESCALER24M_SHIFT)
#  define GPT_PR_PRESCALER24M(n) ((uint32_t)(n) << GPT_PR_PRESCALER24M_SHIFT)
                                            /* Bits 16-31: Reserved */

/* GPT Status Register (GPT_SR) */

#define GPT_SR_OF1               (1 << 0)   /* Bit 0: Output Compare 1 Flag */
#define GPT_SR_OF2               (1 << 1)   /* Bit 1: Output Compare 2 Flag */
#define GPT_SR_OF3               (1 << 2)   /* Bit 2: Output Compare 3 Flag */
#define GPT_SR_IF1               (1 << 3)   /* Bit 3: Input Capture 1 Flag */
#define GPT_SR_IF2               (1 << 4)   /* Bit 4: Input Capture 2 Flag */
#define GPT_SR_ROV               (1 << 5)   /* Bit 5: Rollover Flag */
                                            /* Bits 6-31: Reserved */

/* GPT Interrupt Register (GPT_IR) */

#define GPT_IR_OF1IE             (1 << 0)   /* Bit 0: Output Compare 1 Interrupt Enable */
#define GPT_IR_OF2IE             (1 << 1)   /* Bit 1: Output Compare 2 Interrupt Enable */
#define GPT_IR_OF3IE             (1 << 2)   /* Bit 2: Output Compare 3 Interrupt Enable */
#define GPT_IR_IF1IE             (1 << 3)   /* Bit 3: Input Capture 1 Interrupt Enable */
#define GPT_IR_IF2IE             (1 << 4)   /* Bit 4: Input Capture 2 Interrupt Enable */
#define GPT_IR_ROVIE             (1 << 5)   /* Bit 5: Rollover Interrupt Enable */
                                            /* Bits 6-31: Reserved */

#endif /* __ARCH_ARM_SRC_MX8MN_HARDWARE_MX8MN_GPT_H */
