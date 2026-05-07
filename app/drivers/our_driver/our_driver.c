#include "zephyr/devicetree.h"
#include "zephyr/drivers/gpio.h"
#include "zephyr/logging/log_core.h"
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

struct our_driver_config {
    struct gpio_dt_spec led_gpios;
};

LOG_MODULE_REGISTER(
    our_driver, LOG_LEVEL_INF); // Must register ONCE, Other files must call
                                // LOG_MODULE_DECLARE(our_module, LOG_LEVEL_INF)


int sample_fetch_my_impl(const struct device *dev, enum sensor_channel chan) {

  const struct our_driver_config *config = dev->config;
  //LOG_INF("sample_fetch_impl called for chan %d", chan);
  /* For homework l6-task1 it should turn off an LED on the board */
  LOG_INF(" LED STATUS IS OFF");
  gpio_pin_set_dt(&config->led_gpios, 0);

  return 42;
}


int channel_get_my_impl(const struct device *dev, enum sensor_channel chan,
                        struct sensor_value *val) {

  const struct our_driver_config *config = dev->config;                          

  //LOG_INF("channel_get_impl called for chan %d", chan);
  /* For homework l6-task1 it should turn on an LED on the board */
  LOG_INF(" LED STATUS IS ON");

  gpio_pin_set_dt(&config->led_gpios, 1);
  return 42;
}

int init_function(const struct device *dev) {

  const struct our_driver_config *config = dev->config;

  if (!gpio_is_ready_dt(&config->led_gpios)) {
        LOG_ERR("led GPIO not ready");
        return -ENODEV;  
  }

  if (gpio_pin_configure_dt(&config->led_gpios, GPIO_OUTPUT_ACTIVE) < 0) {
        LOG_ERR("unable to set led GPIO not to output");
        return -ENODEV;  
  }

  // printk("driver initialized");  
  LOG_INF("our_driver Initialized");
  return 0;
}

static DEVICE_API(sensor,
                  api_led_driver) = {
                    .channel_get = channel_get_my_impl,
                    .sample_fetch = sample_fetch_my_impl
                };

/* This creates one instance of the driver, if more than one is enabled in the
 * DTS this line should be repeated for the following instance, the first
 * parameter is the instance number DEVICE_DT_INST_DEFINE(0, init_function,
 * NULL, NULL, NULL, POST_KERNEL, 80, &api_led_driver); so instead of repeating
 * this we do:
 */

#define DEV_INST(inst)                                                   \
    static const struct our_driver_config our_driver_config_##inst = {   \
        .led_gpios = GPIO_DT_SPEC_INST_GET(inst, led_gpios)              \
    };                                                                   \
                                                                         \
    DEVICE_DT_INST_DEFINE(inst,                                          \
        init_function,                                                   \
        NULL,                                                            \
        NULL,                                                            \
        &our_driver_config_##inst,                                       \
        POST_KERNEL,                                                     \
        80,                                                              \
        &api_led_driver);

DT_INST_FOREACH_STATUS_OKAY(
    DEV_INST) // It uses DT_DRV_COMPAT macro to filter the DTS searching for
              // nodes with compatible = "our,driver"
