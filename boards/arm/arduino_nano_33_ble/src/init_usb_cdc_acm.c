#include <usb/usb_device.h>
#include <drivers/uart.h>

static int board_internal_usb_cdc_acm_init(const struct device *dev)
{
        ARG_UNUSED(dev);
        const struct device *device = device_get_binding(
                        CONFIG_UART_CONSOLE_ON_DEV_NAME);
        uint32_t dtr = 0;

        if (usb_enable(NULL)) {
                return -1;
        }

        /* Poll if the DTR flag was set, optional */
        while (!dtr) {
                uart_line_ctrl_get(device, UART_LINE_CTRL_DTR, &dtr);
        }

        if (strlen(CONFIG_UART_CONSOLE_ON_DEV_NAME) !=
            strlen("CDC_ACM_0") ||
            strncmp(CONFIG_UART_CONSOLE_ON_DEV_NAME, "CDC_ACM_0",
                    strlen(CONFIG_UART_CONSOLE_ON_DEV_NAME))) {
                printk("Error: Console device name is not USB ACM\n");

                return -1;
        }


	return 0;
}
SYS_INIT(board_internal_usb_cdc_acm_init, APPLICATION, 32);
