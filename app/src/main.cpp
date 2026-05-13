// #include "syscalls/sensor.h"
// #include "zephyr/drivers/sensor.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <drivers/our_driver/our_driver.h>

/* The devicetree node identifier for the "led0" alias. */
// #define LED_NODE DT_ALIAS(status_led)

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static const struct device *our_driver0 =
    DEVICE_DT_GET(DT_NODELABEL(our_driver0));
static const struct device *our_driver1 =
    DEVICE_DT_GET(DT_NODELABEL(our_driver1));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void) {
    
  if (!device_is_ready(our_driver0)) {
    return 0;
  }

  auto time_ms = 0;
  while (1) {
    time_ms += 100;
    our_driver_set_blink_time_ms(our_driver0, time_ms);
    
    int ret = our_driver_get_blink_time_ms(our_driver0);

    k_msleep(ret);
  
  }
  return 0;
}
