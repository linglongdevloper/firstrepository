/*
使用说明：
1、需要在usart.h中导入头文件
2、在main.c中开启中断，即
  USER CODE BEGIN 2 
	HAL_UART_Receive_IT(&huart1,rxBuffer,RX_CMD_LEN);
  USER CODE END 2 
3、在stm32f1xx_it.c中的 HAL_UART_IRQHandler(&huart1);下方写入 on_UART_IDLE(&huart1);
//ssvoid USART1_IRQHandler(void)
//{

//  HAL_UART_IRQHandler(&huart1);
//   USER CODE BEGIN USART1_IRQn 1 
//	on_UART_IDLE(&huart1);
//   USER CODE END USART1_IRQn 1 
//}
*/
#include "m_usart.h"
#include <string.h>

uint8_t proBuffer[10]="#S45;\n";// 这是最后的存储数组
uint8_t rxBuffer[10]="#H12;\n";//这是从串口暂存的数据
uint8_t rxCompleted=RESET;//用来指示接受是否完成



void fasong(UART_HandleTypeDef *huart,char* m_string){
	HAL_UART_Transmit(huart,m_string,strlen(m_string),100);

}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){


	if(huart->Instance == USART1){
		fasong(huart,"发送成功11\n");
//		__HAL_UART_CLEAR_FLAG(huart,UART_FLAG_TXE);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART1){
		rxCompleted = SET;
    for(uint16_t i=0;i<RX_CMD_LEN;i++){
      proBuffer[i]=rxBuffer[i];
    }
    __HAL_UART_ENABLE_IT(huart,UART_IT_IDLE);
	}
}

void on_UART_IDLE(UART_HandleTypeDef *huart){
  if(__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) == RESET){
    return;
  }
  __HAL_UART_CLEAR_IDLEFLAG(huart);
  __HAL_UART_DISABLE_IT(huart,UART_IT_IDLE);
  if(rxCompleted){
    HAL_UART_Transmit_IT(huart,proBuffer,strlen(proBuffer));
    rxCompleted =RESET;
    HAL_UART_Receive_IT(huart,rxBuffer,RX_CMD_LEN);
  }



}