#include <stdlib.h>
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/device.h>

#include <our_driver/our_driver.h>

extern const struct device *our_driver0;

int cmd_set_blink_time_ms_handler(const struct shell *sh, size_t argc, char **argv) {
    int timeout_ms = atoi(argv[1]);
    our_driver_set_blink_time_ms(our_driver0, timeout_ms);
    return 0;
}

int cmd_get_blink_time_ms_handler(const struct shell *sh, size_t argc, char **argv) {
    int ret = our_driver_get_blink_time_ms(our_driver0);
    return 0;
}

/* Creating subcommands (level 1 command) array for command "sensor". */
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_sub_cmds,
        SHELL_CMD_ARG(set, NULL, "Sets timeout value", cmd_set_blink_time_ms_handler, 2, 0),
        SHELL_CMD(read,   NULL, "Reads timeout value", cmd_get_blink_time_ms_handler),
        SHELL_SUBCMD_SET_END
);

/* Creating root (level 0) command "sensor" */
SHELL_CMD_REGISTER(sensor, &sensor_sub_cmds, "Sensor commands", NULL);

