#include "main.h"

extern UART_HandleTypeDef huart2; //소스가 여러개 있어도 모두 모여서 하나의 실행파일로 만들어진다.

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart2, &ch, 1, 10);
	return ch;
}

int __io_getchar(void)
{
	char ch;
	/*
	while(1)
	{
		int r = HAL_UART_Receive(&huart2, &ch, 1, 10);
		if(r == HAL_OK) break;
	}
	*/
	while(HAL_UART_Receive(&huart2, &ch, 1, 10) != HAL_OK);
	HAL_UART_Transmit(&huart2, &ch, 1, 10);	// echo
	if(ch == '\r') HAL_UART_Transmit(&huart2, "\n", 1, 10);
	return ch;
}

void ProgramStart(char *name)
{
	printf("\033[2J\033[1;1H\n"); // [y;xH : move cur to (x,y)
	printf("Program(%s) started... Blue button to start\r\n", name);
	while(HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) != 0);;
}
