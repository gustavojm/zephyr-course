#include "zephyr/toolchain.h"
#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*set_blink_time_ms_t) (const struct device*, int time_ms);
typedef int (*get_blink_time_ms_t) (const struct device*);

__subsystem struct custom_driver_api {
                  set_blink_time_ms_t set_blink_time_ms;                  
                  get_blink_time_ms_t get_blink_time_ms;
                };

__syscall  int our_driver_set_blink_time_ms(const struct device* dev, int time_ms);

static inline int z_impl_our_driver_set_blink_time_ms(const struct device* dev, int time_ms) {
  if (DEVICE_API_GET(custom, dev)->get_blink_time_ms != NULL) {
		return -ENOSYS;
	}
  return DEVICE_API_GET(custom, dev)->set_blink_time_ms(dev, time_ms);

}

__syscall int our_driver_get_blink_time_ms(const struct device* dev);

static inline int z_impl_our_driver_get_blink_time_ms(const struct device* dev) {
  if (DEVICE_API_GET(custom, dev)->get_blink_time_ms != NULL) {
		return -ENOSYS;
	}
  return DEVICE_API_GET(custom, dev)->get_blink_time_ms(dev);

}

#include <syscalls/our_driver.h>

#ifdef __cplusplus
}
#endif