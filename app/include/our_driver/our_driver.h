#ifndef APP_INCLUDE_OUR_DRIVER_OUR_DRIVER_H_
#define APP_INCLUDE_OUR_DRIVER_OUR_DRIVER_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*set_blink_time_ms_t)(const struct device *dev, int time_ms);
typedef int (*get_blink_time_ms_t)(const struct device *dev);

struct custom_driver_api {
	set_blink_time_ms_t set_blink_time_ms;
	get_blink_time_ms_t get_blink_time_ms;
};

static inline int our_driver_set_blink_time_ms(const struct device *dev,
						   int time_ms)
{
	const struct custom_driver_api *api = (const struct custom_driver_api *)dev->api;

	return api->set_blink_time_ms(dev, time_ms);
}

static inline int our_driver_get_blink_time_ms(const struct device *dev)
{
	const struct custom_driver_api *api = (const struct custom_driver_api *)dev->api;

	return api->get_blink_time_ms(dev);
}

#ifdef __cplusplus
}
#endif

#endif /* APP_INCLUDE_OUR_DRIVER_OUR_DRIVER_H_ */
