#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "hilog/log.h"
#include "securec.h"
#include "um_gpio.h"
//设置GPIO导出
int UM_GPIO_Export(int gpioNum, int bExport)
{
    int ret = -1;
    char buffer[256] = {0};

    if (bExport) {
        (void) snprintf_s(buffer, sizeof(buffer), sizeof(buffer), "echo %d > %s", gpioNum, UM_GPIO_EXPORT);
    } else {
        (void) snprintf_s(buffer, sizeof(buffer), sizeof(buffer), "echo %d > %s", gpioNum, UM_GPIO_UNEXPORT);
    }

    sighandler_t old_handler;
    old_handler = signal(SIGCHLD, SIG_DFL);
    ret = system(buffer);
    if (ret < 0) {
        HILOG_ERROR(LOG_CORE, "set gpio%{public}d %{public}s failed", gpioNum, bExport == 1 ? "export" : "unexport");
        return UM_GPIO_ERR;
    }
    (void) signal(SIGCHLD, old_handler);
    return ret;
}
//设置GPIO方向
int UM_GPIO_SetDirection(int gpioNum, int direction)
{
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void) memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = snprintf_s(gpio_file_name, sizeof(gpio_file_name), sizeof(gpio_file_name), "%s%d/direction",
                               UM_GPIO_PEX, gpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "gpio%{public}d not export", gpioNum);
        return UM_GPIO_NOT_EXPROT_ERROR;
    }
    // set gpio direction

    FILE *fp = NULL;
    fp = fopen(gpio_file_name, "r+");
    if (fp == NULL) {
        HILOG_ERROR(LOG_CORE, "open %{public}s%{public}d/direction failed", UM_GPIO_PEX, gpioNum);
        return UM_GPIO_ERR;
    }

    if (direction == UM_GPIO_DIRECTION_IN) {
        fprintf(fp, "%s", "in");
    } else if (direction == UM_GPIO_DIRECTION_OUT) {
        fprintf(fp, "%s", "out");
    }

    (void) fclose(fp);
    fp = NULL;

    return 0;
}
//设置GPIO值
int UM_GPIO_SetValue(int gpioNum, int value)
{
    int ret_sprintf_s = -1;

    // check gpio export or not
    char gpio_file_name[128];
    (void) memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = snprintf_s(gpio_file_name, sizeof(gpio_file_name), sizeof(gpio_file_name), "%s%d/value",
                               UM_GPIO_PEX, gpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "gpio%{public}d not export", gpioNum);
        return UM_GPIO_NOT_EXPROT_ERROR;
    }
    // set gpio value

    FILE *fp = NULL;
    fp = fopen(gpio_file_name, "r+");
    if (fp == NULL) {
        HILOG_ERROR(LOG_CORE, "open %{public}s%{public}d/value failed", UM_GPIO_PEX, gpioNum);
        return UM_GPIO_ERR;
    }

    if (value == UM_GPIO_LOW_LEVE) {
        fprintf(fp, "%s", "0");
    } else if (value == UM_GPIO_HIGH_LEVE) {
        fprintf(fp, "%s", "1");
    }

    (void) fclose(fp);
    fp = NULL;

    return 0;
}
//检查GPIO是否已导出
int UM_GPIO_IsExport(int gpioNum, int *value)
{
    int ret_sprintf_s = -1;

    if (value == NULL) {
        return UM_GPIO_ERR;
    }
    // check gpio export or not
    char gpio_file_name[128];
    (void) memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = snprintf_s(gpio_file_name, sizeof(gpio_file_name), sizeof(gpio_file_name), "%s%d/value",
                               UM_GPIO_PEX, gpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        HILOG_INFO(LOG_CORE, "gpio%{public}d not export", gpioNum);
        *value = UM_GPIO_NOT_EXPORT;
    } else {
        *value = UM_GPIO_EXPORTED;
    }
    return 0;
}
//获取GPIO方向
int UM_GPIO_GetDirection(int gpioNum, int *value)
{
    int ret = 0;
    int ret_sprintf_s = -1;

    if (value == NULL) {
        return UM_GPIO_ERR;
    }
    // check gpio export or not
    char gpio_file_name[128];
    (void) memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));
    ret_sprintf_s = snprintf_s(gpio_file_name, sizeof(gpio_file_name), sizeof(gpio_file_name), "%s%d/direction",
                               UM_GPIO_PEX, gpioNum);
    if (ret_sprintf_s != 0) {
    }

    if (access(gpio_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "gpio%{public}d not export", gpioNum);
        return UM_GPIO_NOT_EXPROT_ERROR;
    }
    // get gpio direction

    FILE *fp = NULL;
    char buffer[20] = {0};
    fp = fopen(gpio_file_name, "r");
    if (fp == NULL) {
        HILOG_ERROR(LOG_CORE, "read %{public}s%{public}d/direction failed", UM_GPIO_PEX, gpioNum);
        return UM_GPIO_ERR;
    }
    (void) fread(buffer, sizeof(buffer), 1, fp);
    (void) fclose(fp);
    fp = NULL;
    if (strstr(buffer, "out") != NULL) {
        *value = UM_GPIO_DIRECTION_OUT;
    } else if (strstr(buffer, "in") != NULL) {
        *value = UM_GPIO_DIRECTION_IN;
    } else {
        ret = UM_GPIO_ERR;
    }
    return ret;
}
//获取GPIO值
int UM_GPIO_GetValue(int gpioNum, int *value)
{
    int ret = 0;// 定义返回值变量
    int ret_sprintf_s = -1;// 定义snprintf_s函数的返回值变量

    if (value == NULL) {// 检查传入的value指针是否为空
        return UM_GPIO_ERR;// 如果为空，返回错误码
    }
    // 检查gpio是否已经导出
    char gpio_file_name[128];// 定义一个字符数组，用于存储gpio文件名
    (void) memset_s(gpio_file_name, sizeof(gpio_file_name), 0, sizeof(gpio_file_name));// 将数组初始化为0
    ret_sprintf_s = snprintf_s(gpio_file_name, sizeof(gpio_file_name), sizeof(gpio_file_name), "%s%d/value",
                               UM_GPIO_PEX, gpioNum); // 使用snprintf_s函数构造gpio文件名
    if (ret_sprintf_s != 0) {// 如果snprintf_s函数返回非0值，表示出错
    }
    // 检查gpio文件是否存在
    if (access(gpio_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "gpio%{public}d not export", gpioNum); // 如果文件不存在，记录错误日志
        return UM_GPIO_NOT_EXPROT_ERROR;// 返回未导出错误码
    }
    // 获取gpio值

    FILE *fp = NULL;// 定义文件指针
    char buffer[20] = {0};// 定义一个缓冲区，用于读取文件内容
    fp = fopen(gpio_file_name, "r");// 以只读模式打开文件
    if (fp == NULL) {// 如果文件打开失败
        HILOG_ERROR(LOG_CORE, "read %{public}s%{public}d/value failed", UM_GPIO_PEX, gpioNum);// 记录错误日志
        return UM_GPIO_ERR;// 返回错误码
    }
    (void) fread(buffer, sizeof(buffer), 1, fp);// 从文件中读取数据到缓冲区
    (void) fclose(fp);// 关闭文件
    fp = NULL;// 将文件指针设置为NULL
    if (strstr(buffer, "0") != NULL) {// 如果缓冲区中包含字符"0"
        *value = UM_GPIO_LOW_LEVE; // 将value设置为低电平
    } else if (strstr(buffer, "1") != NULL) {// 如果缓冲区中包含字符"1"
        *value = UM_GPIO_HIGH_LEVE;// 将value设置为高电平
    } else {// 如果缓冲区中既没有"0"也没有"1"
        ret = UM_GPIO_ERR;// 设置返回值为错误码
    }
    return ret;
}
