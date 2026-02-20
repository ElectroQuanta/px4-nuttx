/****************************************************************************
 * arch/arm/src/mx8mn/mx8mn_pwm.c
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

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include "arm_internal.h"
#include "hardware/mx8mn_pwm.h"
#include "hardware/mx8mn_pinmux.h"
#include "mx8mn_pwm.h"
#include "mx8mn_ccm.h"
#include "mx8mn_iomux.h"

#include <arch/board/board.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define PWM_MAX_MODULES          4

/* Default configuration for ESC control */

#define PWM_DEFAULT_FREQUENCY    400      /* 400 Hz for standard ESC */
#define PWM_DEFAULT_PRESCALER    1        /* Divide by 2 */
#define PWM_DEFAULT_CLOCK        MX8MN_PWM_IPG_CLK_FREQ

/* Default pin mappings from board.h
 * These can be overridden at board level by defining BOARD_PWMx_PIN
 * before including board.h
 */

#ifndef BOARD_PWM1_PIN
#  define BOARD_PWM1_PIN  IOMUXC_SPDIF_EXT_CLK_PWM1_OUT
#endif

#ifndef BOARD_PWM2_PIN
#  define BOARD_PWM2_PIN  IOMUXC_SPDIF_RX_PWM2_OUT
#endif

#ifndef BOARD_PWM3_PIN
#  define BOARD_PWM3_PIN  IOMUXC_SPDIF_TX_PWM3_OUT
#endif

#ifndef BOARD_PWM4_PIN
#  define BOARD_PWM4_PIN  IOMUXC_SAI3_MCLK_PWM4_OUT
#endif

/****************************************************************************
 * Private Types
 ****************************************************************************/

/* PWM module private data */

struct mx8mn_pwm_priv_s
{
  uint32_t base;                         /* PWM register base address */
  uint32_t pin;                          /* IOMUX pin configuration */
  uint32_t clock_gate;                   /* CCM clock gate index */
  struct mx8mn_pwm_config_s config;      /* Current configuration */
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

/* PWM module configurations */

static struct mx8mn_pwm_priv_s g_pwm_priv[PWM_MAX_MODULES] =
{
  {
    .base       = MX8M_PWM1,
    .pin        = BOARD_PWM1_PIN,
    .clock_gate = CCM_PWM1_CLK_GATE,
    .config     = { 0 }
  },
  {
    .base       = MX8M_PWM2,
    .pin        = BOARD_PWM2_PIN,
    .clock_gate = CCM_PWM2_CLK_GATE,
    .config     = { 0 }
  },
  {
    .base       = MX8M_PWM3,
    .pin        = BOARD_PWM3_PIN,
    .clock_gate = CCM_PWM3_CLK_GATE,
    .config     = { 0 }
  },
  {
    .base       = MX8M_PWM4,
    .pin        = BOARD_PWM4_PIN,
    .clock_gate = CCM_PWM4_CLK_GATE,
    .config     = { 0 }
  }
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: pwm_get_priv
 *
 * Description:
 *   Get the private data structure for a PWM module.
 *
 ****************************************************************************/

static struct mx8mn_pwm_priv_s *pwm_get_priv(int pwm_id)
{
  if (pwm_id < MX8MN_PWM1 || pwm_id > MX8MN_PWM4)
    {
      return NULL;
    }

  return &g_pwm_priv[pwm_id - 1];
}

/****************************************************************************
 * Name: pwm_calculate_parameters
 *
 * Description:
 *   Calculate prescaler and period values for desired frequency.
 *
 ****************************************************************************/

static int pwm_calculate_parameters(uint32_t frequency,
                                     uint32_t *prescaler,
                                     uint32_t *period)
{
  uint32_t best_prescaler = 0;
  uint32_t best_period = 0;
  uint32_t best_error = UINT32_MAX;
  uint32_t pclk;
  uint32_t calc_period;
  uint32_t calc_freq;
  uint32_t error;

  /* Try different prescaler values to find the best fit */

  for (uint32_t psc = 0; psc <= 4095; psc++)
    {
      pclk = PWM_DEFAULT_CLOCK / (psc + 1);
      calc_period = (pclk / frequency) - 2;

      /* Period must fit in 16 bits */

      if (calc_period > 65535)
        {
          continue;
        }

      /* Calculate actual frequency with this configuration */

      calc_freq = pclk / (calc_period + 2);
      error = (calc_freq > frequency) ?
              (calc_freq - frequency) : (frequency - calc_freq);

      /* Update best values if this is closer */

      if (error < best_error)
        {
          best_error = error;
          best_prescaler = psc;
          best_period = calc_period;

          /* Perfect match found */

          if (error == 0)
            {
              break;
            }
        }
    }

  /* Check if we found a valid configuration */

  if (best_error == UINT32_MAX)
    {
      pwmerr("ERROR: Could not find valid PWM parameters for %u Hz\n",
             frequency);
      return -EINVAL;
    }

  *prescaler = best_prescaler;
  *period = best_period;

  pwminfo("Frequency %u Hz: prescaler=%u, period=%u (error=%u Hz)\n",
          frequency, best_prescaler, best_period, best_error);

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mx8mn_pwm_init_with_pin
 ****************************************************************************/

int mx8mn_pwm_init_with_pin(int pwm_id, uint32_t pin)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);
  uint32_t regval;

  if (priv == NULL)
    {
      pwmerr("ERROR: Invalid PWM ID: %d\n", pwm_id);
      return -EINVAL;
    }

  if (priv->config.initialized)
    {
      pwmwarn("WARNING: PWM%d already initialized\n", pwm_id);
      return OK;
    }

  /* Override default pin if specified (non-zero) */

  if (pin != 0)
    {
      pwminfo("PWM%d: Overriding pin config to 0x%08x\n", pwm_id, pin);
      priv->pin = pin;
    }

  pwminfo("Initializing PWM%d at base 0x%08x with pin 0x%08x\n",
          pwm_id, priv->base, priv->pin);

  /* Enable PWM clock gate */

  mx8mn_ccm_gate_clock(priv->clock_gate, CLK_ALWAYS_NEEDED);

  /* Perform software reset */

  putreg32(PWMCR_SWR, priv->base + MX8MN_PWMCR_OFFSET);

  /* Wait for reset to complete (SWR bit is self-clearing) */

  while (getreg32(priv->base + MX8MN_PWMCR_OFFSET) & PWMCR_SWR)
    {
      /* Busy wait */
    }

  /* Configure IOMUX pin for PWM output */

  mx8mn_iomux_configure(priv->pin);

  /* Configure control register:
   * - Clock source: ipg_clk (24 MHz)
   * - Active in debug mode
   * - Active in wait mode
   * - Normal polarity (set at rollover, clear at compare)
   * - Initial prescaler value
   * - PWM disabled (will be enabled later)
   */

  regval = PWMCR_CLKSRC_IPG |
           PWMCR_DBGEN |
           PWMCR_WAITEN |
           PWMCR_POUTC_SET_ROLL |
           PWMCR_PRESCALER(PWM_DEFAULT_PRESCALER);

  putreg32(regval, priv->base + MX8MN_PWMCR_OFFSET);

  /* Initialize configuration with defaults */

  priv->config.prescaler = PWM_DEFAULT_PRESCALER;
  priv->config.polarity = MX8MN_PWM_POLARITY_NORMAL;
  priv->config.initialized = true;

  /* Configure default frequency (400 Hz for ESC) */

  return mx8mn_pwm_configure(pwm_id, PWM_DEFAULT_FREQUENCY,
                             MX8MN_PWM_POLARITY_NORMAL);
}

/****************************************************************************
 * Name: mx8mn_pwm_init
 ****************************************************************************/

int mx8mn_pwm_init(int pwm_id)
{
  /* Use default pin from board configuration */

  return mx8mn_pwm_init_with_pin(pwm_id, 0);
}

/****************************************************************************
 * Name: mx8mn_pwm_deinit
 ****************************************************************************/

int mx8mn_pwm_deinit(int pwm_id)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);

  if (priv == NULL)
    {
      return -EINVAL;
    }

  /* Disable PWM output */

  mx8mn_pwm_enable(pwm_id, false);

  /* Disable PWM clock gate */

  mx8mn_ccm_gate_clock(priv->clock_gate, CLK_DOMAIN_CONTROLLED);

  /* Mark as uninitialized */

  priv->config.initialized = false;

  return OK;
}

/****************************************************************************
 * Name: mx8mn_pwm_configure
 ****************************************************************************/

int mx8mn_pwm_configure(int pwm_id, uint32_t frequency, uint8_t polarity)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);
  uint32_t prescaler;
  uint32_t period;
  uint32_t regval;
  int ret;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  if (!priv->config.initialized)
    {
      pwmerr("ERROR: PWM%d not initialized\n", pwm_id);
      return -EINVAL;
    }

  /* Validate polarity */

  if (polarity != MX8MN_PWM_POLARITY_NORMAL &&
      polarity != MX8MN_PWM_POLARITY_INVERTED)
    {
      pwmerr("ERROR: Invalid polarity: %u\n", polarity);
      return -EINVAL;
    }

  /* Calculate prescaler and period for desired frequency */

  ret = pwm_calculate_parameters(frequency, &prescaler, &period);
  if (ret < 0)
    {
      return ret;
    }

  /* Read current control register */

  regval = getreg32(priv->base + MX8MN_PWMCR_OFFSET);

  /* Clear prescaler and polarity fields */

  regval &= ~(PWMCR_PRESCALER_MASK | PWMCR_POUTC_MASK);

  /* Set new prescaler value */

  regval |= PWMCR_PRESCALER(prescaler);

  /* Set output polarity */

  if (polarity == MX8MN_PWM_POLARITY_NORMAL)
    {
      regval |= PWMCR_POUTC_SET_ROLL;  /* Set at rollover, clear at compare */
    }
  else
    {
      regval |= PWMCR_POUTC_CLR_ROLL;  /* Clear at rollover, set at compare */
    }

  /* Write back control register */

  putreg32(regval, priv->base + MX8MN_PWMCR_OFFSET);

  /* Set period register */

  putreg32(PWMPR_PERIOD(period), priv->base + MX8MN_PWMPR_OFFSET);

  /* Update configuration */

  priv->config.frequency = frequency;
  priv->config.prescaler = prescaler;
  priv->config.period = period;
  priv->config.polarity = polarity;

  pwminfo("PWM%d configured: freq=%u Hz, prescaler=%u, period=%u\n",
          pwm_id, frequency, prescaler, period);

  return OK;
}

/****************************************************************************
 * Name: mx8mn_pwm_set_duty_cycle
 ****************************************************************************/

int mx8mn_pwm_set_duty_cycle(int pwm_id, uint32_t duty_us)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);
  uint32_t pclk;
  uint32_t sample;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  if (!priv->config.initialized)
    {
      pwmerr("ERROR: PWM%d not initialized\n", pwm_id);
      return -EINVAL;
    }

  /* Calculate prescaled clock frequency */

  pclk = PWM_DEFAULT_CLOCK / (priv->config.prescaler + 1);

  /* Convert microseconds to sample value
   * sample = (duty_us * pclk) / 1000000
   */

  sample = ((uint64_t)duty_us * pclk) / 1000000;

  /* Clamp sample to valid range [0, period+1] */

  if (sample > (priv->config.period + 1))
    {
      pwmwarn("WARNING: Duty cycle %u us exceeds period, clamping\n",
              duty_us);
      sample = priv->config.period + 1;
    }

  /* Write sample register */

  putreg32(PWMSAR_SAMPLE(sample), priv->base + MX8MN_PWMSAR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: mx8mn_pwm_set_duty_percent
 ****************************************************************************/

int mx8mn_pwm_set_duty_percent(int pwm_id, uint32_t duty_percent)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);
  uint32_t sample;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  if (!priv->config.initialized)
    {
      pwmerr("ERROR: PWM%d not initialized\n", pwm_id);
      return -EINVAL;
    }

  /* Validate percentage */

  if (duty_percent > 100)
    {
      pwmerr("ERROR: Invalid duty cycle: %u%%\n", duty_percent);
      return -EINVAL;
    }

  /* Calculate sample value from percentage
   * sample = (duty_percent * (period + 2)) / 100
   */

  sample = ((uint64_t)duty_percent * (priv->config.period + 2)) / 100;

  /* Write sample register */

  putreg32(PWMSAR_SAMPLE(sample), priv->base + MX8MN_PWMSAR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: mx8mn_pwm_enable
 ****************************************************************************/

int mx8mn_pwm_enable(int pwm_id, bool enable)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);
  uint32_t regval;

  if (priv == NULL)
    {
      return -EINVAL;
    }

  if (!priv->config.initialized)
    {
      pwmerr("ERROR: PWM%d not initialized\n", pwm_id);
      return -EINVAL;
    }

  /* Read current control register */

  regval = getreg32(priv->base + MX8MN_PWMCR_OFFSET);

  if (enable)
    {
      /* Enable PWM */

      regval |= PWMCR_EN;
      pwminfo("PWM%d enabled\n", pwm_id);
    }
  else
    {
      /* Disable PWM */

      regval &= ~PWMCR_EN;
      pwminfo("PWM%d disabled\n", pwm_id);
    }

  /* Write back control register */

  putreg32(regval, priv->base + MX8MN_PWMCR_OFFSET);

  return OK;
}

/****************************************************************************
 * Name: mx8mn_pwm_get_config
 ****************************************************************************/

int mx8mn_pwm_get_config(int pwm_id, struct mx8mn_pwm_config_s *config)
{
  struct mx8mn_pwm_priv_s *priv = pwm_get_priv(pwm_id);

  if (priv == NULL || config == NULL)
    {
      return -EINVAL;
    }

  /* Copy configuration */

  *config = priv->config;

  return OK;
}
