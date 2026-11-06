#ifndef APP_CFG_H
#define APP_CFG_H

/* Task priorities: smaller number = higher priority. */
#define APP_TASK_LED1_PRIO          2u
#define APP_TASK_LED2_PRIO          3u
#define APP_TASK_UART_PRIO          4u

/* Stack sizes are in CPU_STK elements (32-bit words on Cortex-M3). */
#define APP_TASK_LED1_STK_SIZE      128u
#define APP_TASK_LED2_STK_SIZE      128u
#define APP_TASK_UART_STK_SIZE      256u

#define APP_TASK_LED1_STK_LIMIT     (APP_TASK_LED1_STK_SIZE / 10u)
#define APP_TASK_LED2_STK_LIMIT     (APP_TASK_LED2_STK_SIZE / 10u)
#define APP_TASK_UART_STK_LIMIT     (APP_TASK_UART_STK_SIZE / 10u)

#endif
