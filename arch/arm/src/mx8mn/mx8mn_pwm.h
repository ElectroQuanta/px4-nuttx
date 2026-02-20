/****************************************************************************
 * arch/arm/src/mx8mn/mx8mn_pwm.h
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

#ifndef __ARCH_ARM_SRC_MX8MN_MX8MN_PWM_H
#define __ARCH_ARM_SRC_MX8MN_MX8MN_PWM_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>
#include <stdbool.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* PWM Module IDs */

#define MX8MN_PWM1               1
#define MX8MN_PWM2               2
#define MX8MN_PWM3               3
#define MX8MN_PWM4               4

/* PWM Configuration Flags */

#define MX8MN_PWM_POLARITY_NORMAL   0  /* Active high */
#define MX8MN_PWM_POLARITY_INVERTED 1  /* Active low */

/****************************************************************************
 * Public Types
 ****************************************************************************/

/* PWM configuration structure */

struct mx8mn_pwm_config_s
{
  uint32_t frequency;      /* PWM frequency in Hz (e.g., 400 for ESC) */
  uint32_t prescaler;      /* Clock prescaler value (0-4095) */
  uint32_t period;         /* Period register value (0-65535) */
  uint8_t  polarity;       /* Output polarity (normal/inverted) */
  bool     initialized;    /* Module initialization flag */
};

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: mx8mn_pwm_init
 *
 * Description:
 *   Initialize a PWM module with default pin configuration from board.h
 *   This function:
 *   - Enables the PWM clock gate via CCM
 *   - Performs software reset
 *   - Configures IOMUX pin muxing for PWM output (using BOARD_PWMx_PIN)
 *   - Sets up default control register values
 *
 * Input Parameters:
 *   pwm_id - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_init(int pwm_id);

/****************************************************************************
 * Name: mx8mn_pwm_init_with_pin
 *
 * Description:
 *   Initialize a PWM module with custom pin configuration.
 *   This allows runtime pin selection without modifying driver code.
 *
 *   Use this when you need to override the default board pin configuration,
 *   or when dynamically configuring PWM outputs for different board variants.
 *
 * Input Parameters:
 *   pwm_id - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *   pin    - IOMUX pin configuration constant (e.g., IOMUXC_GPIO1_IO00_PWM1_OUT)
 *            Pass 0 to use the default pin from board.h
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 * Example:
 *   // Use default pin from board.h
 *   mx8mn_pwm_init_with_pin(MX8MN_PWM1, 0);
 *
 *   // Override with GPIO1_IO00
 *   mx8mn_pwm_init_with_pin(MX8MN_PWM1, IOMUXC_GPIO1_IO00_PWM1_OUT);
 *
 ****************************************************************************/

int mx8mn_pwm_init_with_pin(int pwm_id, uint32_t pin);

/****************************************************************************
 * Name: mx8mn_pwm_deinit
 *
 * Description:
 *   Deinitialize a PWM module. This function:
 *   - Disables PWM output
 *   - Disables the PWM clock gate via CCM
 *
 * Input Parameters:
 *   pwm_id - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_deinit(int pwm_id);

/****************************************************************************
 * Name: mx8mn_pwm_configure
 *
 * Description:
 *   Configure PWM frequency and polarity. This function calculates the
 *   appropriate prescaler and period values to achieve the desired output
 *   frequency.
 *
 *   For standard ESC control:
 *     frequency = 400 Hz (2500 us period)
 *     polarity = MX8MN_PWM_POLARITY_NORMAL
 *
 * Input Parameters:
 *   pwm_id    - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *   frequency - Desired PWM frequency in Hz
 *   polarity  - Output polarity (MX8MN_PWM_POLARITY_NORMAL/INVERTED)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_configure(int pwm_id, uint32_t frequency, uint8_t polarity);

/****************************************************************************
 * Name: mx8mn_pwm_set_duty_cycle
 *
 * Description:
 *   Set PWM duty cycle using microsecond timing. This is the primary
 *   interface for ESC control where pulse width in microseconds directly
 *   controls motor speed.
 *
 *   For standard ESC protocol:
 *     duty_us = 1000 (minimum throttle)
 *     duty_us = 1500 (mid throttle)
 *     duty_us = 2000 (maximum throttle)
 *
 * Input Parameters:
 *   pwm_id   - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *   duty_us  - Pulse width in microseconds
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_set_duty_cycle(int pwm_id, uint32_t duty_us);

/****************************************************************************
 * Name: mx8mn_pwm_set_duty_percent
 *
 * Description:
 *   Set PWM duty cycle as a percentage (0-100%). This is an alternative
 *   interface for applications that don't require microsecond timing.
 *
 * Input Parameters:
 *   pwm_id      - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *   duty_percent - Duty cycle percentage (0-100)
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_set_duty_percent(int pwm_id, uint32_t duty_percent);

/****************************************************************************
 * Name: mx8mn_pwm_enable
 *
 * Description:
 *   Enable or disable PWM output. When enabled, the PWM counter starts
 *   and the output pin begins toggling. When disabled, the counter is
 *   reset and the output pin goes to its inactive state.
 *
 * Input Parameters:
 *   pwm_id - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *   enable - true to enable, false to disable
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_enable(int pwm_id, bool enable);

/****************************************************************************
 * Name: mx8mn_pwm_get_config
 *
 * Description:
 *   Retrieve the current PWM configuration.
 *
 * Input Parameters:
 *   pwm_id - PWM module ID (MX8MN_PWM1 to MX8MN_PWM4)
 *   config - Pointer to configuration structure to fill
 *
 * Returned Value:
 *   Zero (OK) on success; a negated errno value on failure.
 *
 ****************************************************************************/

int mx8mn_pwm_get_config(int pwm_id, struct mx8mn_pwm_config_s *config);

#endif /* __ARCH_ARM_SRC_MX8MN_MX8MN_PWM_H */
