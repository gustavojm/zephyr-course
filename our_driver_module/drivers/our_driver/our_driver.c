#include <string.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/logging/log_core.h>

#include <drivers/our_driver/our_driver.h>

#define DT_DRV_COMPAT our_driver

struct our_driver_config {
  struct gpio_dt_spec led_gpios;
};

struct custom_driver_data_t {
  int blink_time_ms;
};

LOG_MODULE_REGISTER(
    our_driver, LOG_LEVEL_INF); // Must register ONCE, Other files must call
                                // LOG_MODULE_DECLARE(our_module, LOG_LEVEL_INF)

int set_blink_time_ms_impl(const struct device *dev, int time_ms) {

  // const struct our_driver_config *config = dev->config;

  struct custom_driver_data_t *data = dev->data;

  // LOG_INF("sample_fetch_impl called for chan %d", chan);
  /* For homework l6-task1 it should turn off an LED on the board */
  LOG_INF(" Setting blink_time_ms to %i", time_ms);
  // gpio_pin_set_dt(&config->led_gpios, 0);
  data->blink_time_ms = time_ms;

  return 42;
}

int get_blink_time_ms_impl(const struct device *dev) {

  // const struct our_driver_config *config = dev->config;

  struct custom_driver_data_t *data = dev->data;

  // LOG_INF("sample_fetch_impl called for chan %d", chan);
  /* For homework l6-task1 it should turn off an LED on the board */
  LOG_INF(" Getting  blink_time_ms to %i", data->blink_time_ms);
  // gpio_pin_set_dt(&config->led_gpios, 0);

  return data->blink_time_ms;
}

int init_function(const struct device *dev) {

  const struct our_driver_config *config = dev->config;

  if (!gpio_is_ready_dt(&config->led_gpios)) {
    LOG_ERR("led GPIO not ready");
    // return -ENODEV;
  } else {
    if (gpio_pin_configure_dt(&config->led_gpios, GPIO_OUTPUT_ACTIVE) < 0) {
      LOG_ERR("unable to set led GPIO not to output");
      // return -ENODEV;
    }
  }

  // printk("driver initialized");
  LOG_INF("our_driver Initialized");
  return 0;
}

struct custom_driver_api api_custom_driver = {
    .set_blink_time_ms = set_blink_time_ms_impl,
    .get_blink_time_ms = get_blink_time_ms_impl,

};

/* This creates one instance of the driver, if more than one is enabled in the
 * DTS this line should be repeated for the following instance, the first
 * parameter is the instance number DEVICE_DT_INST_DEFINE(0, init_function,
 * NULL, NULL, NULL, POST_KERNEL, 80, &api_led_driver); so instead of repeating
 * this we do:
 */

#define DEV_INST(inst)                                                         \
  static const struct our_driver_config our_driver_config_##inst = {           \
      .led_gpios = GPIO_DT_SPEC_INST_GET_OR(inst, led_gpios, NULL)};           \
                                                                               \
  static struct custom_driver_data_t our_driver_data_##inst = {                \
      .blink_time_ms = 300,                                                    \
  };                                                                           \
                                                                               \
  DEVICE_DT_INST_DEFINE(inst, init_function, /* Init function */               \
                        NULL,                /* Power management resources */  \
                        &our_driver_data_##inst,   /* Mutable data */          \
                        &our_driver_config_##inst, /* Constant data */         \
                        POST_KERNEL,               /* Initialization level */  \
                        80, /* Device priority within this level */            \
                        &api_custom_driver); /* Pointer to the API */

DT_INST_FOREACH_STATUS_OKAY(
    DEV_INST) // It uses DT_DRV_COMPAT macro to filter the DTS searching for
              // nodes with compatible = "our,driver"
