#include <zephyr/device.h>

typedef int (*set_blink_time_ms_t) (const struct device*, int time_ms);
typedef int (*get_blink_time_ms_t) (const struct device*);

struct custom_driver_api_t {
                  set_blink_time_ms_t set_blink_time_ms;                  
                  get_blink_time_ms_t get_blink_time_ms;
                };

static inline int our_driver_set_blink_time_ms(const struct device* dev, int time_ms) {
  const struct custom_driver_api_t *api = (const struct custom_driver_api_t*)dev->api;

  return api->set_blink_time_ms(dev, time_ms);

}

static inline int our_driver_get_blink_time_ms(const struct device* dev) {
  const struct custom_driver_api_t *api = (const struct custom_driver_api_t*)dev->api;

  return api->get_blink_time_ms(dev);

}
