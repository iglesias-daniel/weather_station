// ULP RISC-V program for the ESP32-S3 sensor node.
//
// Runs periodically while the main CPU is in deep sleep. Counts pulses
// from the rain gauge (and/or anemometer) on a GPIO and wakes the main
// CPU once `wake_threshold` events have been seen, so the main core only
// has to run when there's meaningful data to send.

#include <stdbool.h>
#include <stdint.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"

// Exported to the main core via the generated ulp_main.h header.
uint32_t pulse_count = 0;
uint32_t wake_threshold = 10;

#define RAIN_GPIO GPIO_NUM_4

int main(void)
{
    static bool last_level = false;
    bool level = ulp_riscv_gpio_get_level(RAIN_GPIO);

    if (level && !last_level) {
        pulse_count++;
    }
    last_level = level;

    if (pulse_count >= wake_threshold) {
        ulp_riscv_wakeup_main_processor();
    }

    return 0;
}
