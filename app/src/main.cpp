// #include "syscalls/sensor.h"
#include "zephyr/drivers/sensor.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

/* The devicetree node identifier for the "led0" alias. */
// #define LED_NODE DT_ALIAS(status_led)

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static const struct device *our_driver0 =
    DEVICE_DT_GET(DT_NODELABEL(our_driver0));
static const struct device *our_driver1 =
    DEVICE_DT_GET(DT_NODELABEL(our_driver1));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void) {
  struct sensor_value val;
  // bool led_state = true;

  // if (!gpio_is_ready_dt(&led)) return 0;

  // if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;
  
  if (!device_is_ready(our_driver0)) {
    return 0;
  }

  while (1) {

    auto ret = sensor_channel_get(our_driver0, SENSOR_CHAN_AMBIENT_TEMP, &val);

    printk("sensor read from main %i \n", ret);
    k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);

    ret = sensor_sample_fetch(our_driver0);
    printk("sensor read from main sensor_1 %i \n", ret);

    //     if (gpio_pin_toggle_dt(&led) < 0) return 0;

    //     led_state = !led_state;
    //     LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
    k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);


    ret = sensor_channel_get(our_driver1, SENSOR_CHAN_AMBIENT_TEMP, &val);

    printk("sensor read from main %i \n", ret);
    k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);

    ret = sensor_sample_fetch(our_driver1);
    printk("sensor read from main sensor_1 %i \n", ret);

    k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);
  
  }
  return 0;
}
