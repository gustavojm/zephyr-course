#include <zephyr/device.h>

typedef int (*set_blink_time_ms_t) (const struct device*, int time_ms);
typedef int (*get_blink_time_ms_t) (const struct device*);

struct custom_driver_api_t {
                  set_blink_time_ms_t set_blink_time_ms;                  
                  get_blink_time_ms_t get_blink_time_ms;
                };


