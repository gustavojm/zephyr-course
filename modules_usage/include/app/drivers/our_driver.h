/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef APP_INCLUDE_APP_DRIVERS_OUR_DRIVER_H_
#define APP_INCLUDE_APP_DRIVERS_OUR_DRIVER_H_

#include <zephyr/device.h>
#include <zephyr/toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @cond INTERNAL_HIDDEN */

typedef int (*set_blink_time_ms_t)(const struct device *dev, int time_ms);
typedef int (*get_blink_time_ms_t)(const struct device *dev);

__subsystem struct custom_driver_api {
	set_blink_time_ms_t set_blink_time_ms;
	get_blink_time_ms_t get_blink_time_ms;
};

/** @endcond */

__syscall int our_driver_set_blink_time_ms(const struct device *dev, int time_ms);

static inline int z_impl_our_driver_set_blink_time_ms(const struct device *dev,
						      int time_ms)
{
	const struct custom_driver_api *api =
		(const struct custom_driver_api *)dev->api;

	return api->set_blink_time_ms(dev, time_ms);
}

__syscall int our_driver_get_blink_time_ms(const struct device *dev);

static inline int z_impl_our_driver_get_blink_time_ms(const struct device *dev)
{
	const struct custom_driver_api *api =
		(const struct custom_driver_api *)dev->api;

	return api->get_blink_time_ms(dev);
}

#include <syscalls/our_driver.h>

#ifdef __cplusplus
}
#endif

#endif /* APP_INCLUDE_APP_DRIVERS_OUR_DRIVER_H_ */
