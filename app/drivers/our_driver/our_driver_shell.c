#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>

extern const struct device *our_driver0;

int cmd_fetch_handler(const struct shell *sh, size_t argc, char **argv) {
    int ret = sensor_sample_fetch(our_driver0);
    shell_info(sh, "sensor read from main sensor_1 %i \n", ret);

    return 0;
}

int cmd_read_handler(const struct shell *sh, size_t argc, char **argv) {
    struct sensor_value val;
    int ret = sensor_channel_get(our_driver0, SENSOR_CHAN_AMBIENT_TEMP, &val);
    
    shell_info(sh, "sensor read from main %i \n", ret);

    return 0;
}

/* Creating subcommands (level 1 command) array for command "sensor". */
SHELL_STATIC_SUBCMD_SET_CREATE(sensor_sub_cmds,
        SHELL_CMD(fetch, NULL, "Turns on LED", cmd_fetch_handler),
        SHELL_CMD(read,   NULL, "Turns off LED.", cmd_read_handler),
        SHELL_SUBCMD_SET_END
);

/* Creating root (level 0) command "sensor" */
SHELL_CMD_REGISTER(sensor, &sensor_sub_cmds, "Sensor commands", NULL);

