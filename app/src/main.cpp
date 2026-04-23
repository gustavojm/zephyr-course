#include <zephyr/kernel.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define LED_NODE DT_ALIAS(status_led)
#define SW0_NODE DT_ALIAS(sw0)
#define SLEEP_TIME_MS 100

static const struct gpio_dt_spec status_led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
static const struct gpio_dt_spec config_btn = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

int main(void)
{
    const struct device *dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
    uint32_t dtr = 0;

    if (usb_enable(NULL) != 0) {
        return -1;
    }

    /* Wait for a DTR signal (terminal connected) */
    while (!dtr) {
        uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        k_sleep(K_MSEC(100));
    }

    LOG_INF("USB CDC ACM shell/log ready!");
    LOG_DBG("Debug logging active on ttyACM0");

    if (!gpio_is_ready_dt(&status_led)) {        
        return 0;
    }

    if (!gpio_is_ready_dt(&config_btn)) {        
        return 0;
    }

    if (gpio_pin_configure_dt(&status_led, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    if (gpio_pin_configure_dt(&config_btn, GPIO_INPUT | GPIO_PULL_UP) < 0) return 0;

    bool led_state = false;

    while (1) {
        static bool old_btn_pressed = false;

        bool btn_pressed = gpio_pin_get_dt(&config_btn);
        if (btn_pressed) {
            gpio_pin_set_dt(&status_led, 1);            
        } else {
            gpio_pin_set_dt(&status_led, 0);                        
        }
        // if (gpio_pin_toggle_dt(&status_led) < 0) return 0;

        if (btn_pressed != old_btn_pressed) {
            // led_state = !led_state;
            LOG_INF("BTN state: %s", btn_pressed ? "ON" : "OFF");
            old_btn_pressed = btn_pressed;
        }
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
    
}