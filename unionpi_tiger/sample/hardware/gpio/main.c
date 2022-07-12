
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "um_gpio.h"

int main(int argc, char **argv)
{
    int s32GpioNum = UM_GPIO_09;
    int bExport = UM_GPIO_EXPORTED;
    int direction = UM_GPIO_DIRECTION_OUT;
    int s32Value = UM_GPIO_HIGH_LEVE;
    int s32GetValue = -1;

    /* ������ֻ��ģ��һ��gpio�ڣ�GPIO_09��
    ��������outģʽ���ҽ�������Ϊ�ߵ�ƽ
    ����Ҫ�Ļ������Լ����ó���������gpio */
    if (NULL != argv[1]) {
        s32GpioNum = atoi(argv[1]);
    }

    UM_GPIO_IsExport(s32GpioNum, &s32GetValue);
    if (s32GetValue == UM_GPIO_NOT_EXPORT) {
        UM_GPIO_Export(s32GpioNum, bExport);
    }

    UM_GPIO_SetDirection(s32GpioNum, direction);
    UM_GPIO_SetValue(s32GpioNum, s32Value);

    UM_GPIO_GetDirection(s32GpioNum, &s32GetValue);
    printf("s32GpioNum:[%d], direction:[%d]\n", s32GpioNum, s32GetValue);

    UM_GPIO_GetValue(s32GpioNum, &s32GetValue);
    printf("s32GpioNum:[%d], value:[%d]\n", s32GpioNum, s32GetValue);

    return 0;
}
