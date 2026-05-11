#ifndef ZEPHYR_INCLUDE_SYSCALLS_OUR_DRIVER_H_
#define ZEPHYR_INCLUDE_SYSCALLS_OUR_DRIVER_H_

static inline int our_driver_set_blink_time_ms(const struct device *dev,
                                               int time_ms)
{
	return z_impl_our_driver_set_blink_time_ms(dev, time_ms);
}

static inline int our_driver_get_blink_time_ms(const struct device *dev)
{
	return z_impl_our_driver_get_blink_time_ms(dev);
}

#endif /* ZEPHYR_INCLUDE_SYSCALLS_OUR_DRIVER_H_ */
