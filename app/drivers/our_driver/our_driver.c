#include "zephyr/device.h"
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver

int channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val) {
    return 42;
}

int init_function(const struct device* dev) {
   // printk("driver initialized");
    return 0;
}

static DEVICE_API(sensor, api_led_driver) = {
    .channel_get = channel_get_my_impl
};

DEVICE_DT_INST_DEFINE(0, init_function, NULL, NULL, NULL, POST_KERNEL, 80, &api_led_driver);

