/*
* Copyright (c) 2022 Unionman Technology Co., Ltd.
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "um_gpio.h"

int UM_GPIO_Export(int s32GpioNum, int bExport)
{
    int ret = 0;
    char buffer[256];

    if (bExport) {
        (void)snprintf_s(buffer, sizeof(buffer), sizeof(buffer), "echo %d > %s", s32GpioNum, UM_GPIO_EXPORT);
    } else {
        (void)snprintf_s(buffer, sizeof(buffer), sizeof(buffer), "echo %d > %s", s32GpioNum, UM_GPIO_UNEXPORT);
    }

    system(buffer);

    return ret;
}

int UM_GPIO_SetDirection(int s32GpioNum, int direction)
{
    int ret = 0;
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void)memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = sprintf_s(gpio_file_name, sizeof(gpio_file_name), "%s%d/direction", UM_GPIO_PEX, s32GpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        return UM_GPIO_NOT_EXPROT_ERROR;
    }
    // set gpio direction

    FILE *fp;
    fp = fopen(gpio_file_name, "r+");

    if (direction == UM_GPIO_IN) {
        fprintf(fp, "%s", "in");
    } else if (direction == UM_GPIO_OUT) {
        fprintf(fp, "%s", "out");
    }

    (void)fclose(fp);

    return ret;
}

int UM_GPIO_SetValue(int s32GpioNum, int s32Value)
{
    int ret = 0;
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void)memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = sprintf_s(gpio_file_name, sizeof(gpio_file_name), "%s%d/value", UM_GPIO_PEX, s32GpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        return UM_GPIO_NOT_EXPROT_ERROR;
    }
    // set gpio s32Value

    FILE *fp;
    fp = fopen(gpio_file_name, "r+");

    if (s32Value == UM_GPIO_LOW_LEVE) {
        fprintf(fp, "%s", "0");
    } else if (s32Value == UM_GPIO_HIGH_LEVE) {
        fprintf(fp, "%s", "1");
    }

    (void)fclose(fp);

    return ret;
}

int UM_GPIO_IsExport(int s32GpioNum, int *ps32Value)
{
    int ret = 0;
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void)memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = sprintf_s(gpio_file_name, sizeof(gpio_file_name), "%s%d/value", UM_GPIO_PEX, s32GpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        *ps32Value = UM_GPIO_NOT_EXPORT;
    } else {
        *ps32Value = UM_GPIO_EXPORTED;
    }
    return ret;
}

int UM_GPIO_GetDirection(int s32GpioNum, int *ps32Value)
{
    int ret = 0;
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void)memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = sprintf_s(gpio_file_name, sizeof(gpio_file_name), "%s%d/direction", UM_GPIO_PEX, s32GpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        return UM_GPIO_NOT_EXPROT_ERROR;
    }

    FILE *fp;
    char buffer[20];
    fp = fopen(gpio_file_name, "r");
    (void)fread(buffer, sizeof(buffer), 1, fp);
    (void)fclose(fp);
    if (strstr(buffer, "out") != NULL) {
        *ps32Value = UM_GPIO_OUT;
    } else if (strstr(buffer, "in") != NULL) {
        *ps32Value = UM_GPIO_IN;
    } else {
        ret = UM_GPIO_ERR;
    }
    return ret;
}

int UM_GPIO_GetValue(int s32GpioNum, int *ps32Value)
{
    int ret = 0;
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void)memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = sprintf_s(gpio_file_name, sizeof(gpio_file_name), "%s%d/s32Value", UM_GPIO_PEX, s32GpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        return UM_GPIO_NOT_EXPROT_ERROR;
    }

    FILE *fp;
    char buffer[20];
    fp = fopen(gpio_file_name, "r");
    (void)fread(buffer, sizeof(buffer), 1, fp);

    (void)fclose(fp);
    if (strstr(buffer, "0") != NULL) {
        *ps32Value = UM_GPIO_LOW_LEVE;
    } else if (strstr(buffer, "1") != NULL) {
        *ps32Value = UM_GPIO_HIGH_LEVE;
    } else {
        ret = UM_GPIO_ERR;
    }
    return ret;
}