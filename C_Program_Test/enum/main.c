#include <stdio.h>

typedef enum
{
    UART_FIRST_PORT = 0,
    UART_DEBUG_PORT = UART_FIRST_PORT,

    UART_SECOND_PORT,
    UART_HS_PORT = UART_SECOND_PORT,

    UART_THIRD_PORT,
    UART_MCU_PORT = UART_THIRD_PORT,

    UART_MAX_PORTS,
} uart_port_id;

int main(int argc, char* argv[]) {

    printf("UART_DEBUG_PORT = %d\n", UART_DEBUG_PORT);
    printf("UART_HS_PORT = %d\n", UART_HS_PORT);
    printf("UART_MCU_PORT = %d\n", UART_MCU_PORT);


    return 0;
}

