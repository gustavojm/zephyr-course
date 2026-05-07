#include "zephyr/devicetree.h"
#include "zephyr/logging/log_core.h"
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(
    our_driver, LOG_LEVEL_INF); // Must register ONCE, Other files must call
                                // LOG_MODULE_DECLARE(our_module, LOG_LEVEL_INF)

int channel_get_my_impl(const struct device *dev, enum sensor_channel chan,
                        struct sensor_value *val) {

  LOG_INF("channel_get_impl called for chan %d", chan);

  return 42;
}

int init_function(const struct device *dev) {
  // printk("driver initialized");
  LOG_INF("our_driver Initialized");
  return 0;
}

static DEVICE_API(sensor,
                  api_led_driver) = {.channel_get = channel_get_my_impl};

/* This creates one instance of the driver, if more than one is enabled in the
 * DTS this line should be repeated for the following instance, the first
 * parameter is the instance number DEVICE_DT_INST_DEFINE(0, init_function,
 * NULL, NULL, NULL, POST_KERNEL, 80, &api_led_driver); so instead of repeating
 * this we do:
 */

#define DEV_INST(inst)                                                         \
  DEVICE_DT_INST_DEFINE(inst, init_function, NULL, NULL, NULL, POST_KERNEL,    \
                        80, &api_led_driver);

DT_INST_FOREACH_STATUS_OKAY(
    DEV_INST) // It uses DT_DRV_COMPAT macro to filter the DTS searching for
              // nodes with compatible = "our,driver"
