#ifndef __M_USART_H__
#define __M_USART_H__

#include "main.h"

#define RX_CMD_LEN 5
extern UART_HandleTypeDef huart1;
extern uint8_t rxBuffer[];
extern uint8_t proBuffer[];

void on_UART_IDLE(UART_HandleTypeDef *huart);

#endif