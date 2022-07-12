#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <asm/ioctl.h>
#include <stdint.h>

#include "um_i2c.h"

char *i2c_dev_3 = I2C_DEV_CHAR_3;
char *i2c_dev_4 = I2C_DEV_CHAR_4;

HARDWARE_I2C hardware_I2C;

int i2c_read(int i2cChannel, int device_addr, int sub_addr, unsigned char *buff, int ByteNo)
{
    int fd, ret;
    unsigned char buftmp[32];
    struct i2c_rdwr_ioctl_data i2c_data;

    uint32_t result = 0;

    uint8_t _pBuf[2];

    if (i2cChannel == I2C_DEV_3) {
        fd = open(i2c_dev_3, O_RDWR);
    } else if (i2cChannel == I2C_DEV_4) {
        fd = open(i2c_dev_4, O_RDWR);
    } else {
        printf("wrong i2c channel %d\n", i2cChannel);
        return I2C_PARAM_FAIL;
    }

    if (fd < 0) {
        printf("can not open dev %d\n", i2cChannel);
        return I2C_OPEN_DEV_FAIL;
    }

    i2c_data.nmsgs = 2;
    i2c_data.msgs = (struct i2c_msg *)malloc(i2c_data.nmsgs * sizeof(struct i2c_msg));
    if (i2c_data.msgs == NULL) {
        printf("malloc error \n");
        close(fd);
        return I2C_OPEN_DEV_FAIL;
    }

    ioctl(fd, I2C_TIMEOUT, 1);
    ioctl(fd, I2C_RETRIES, 2);

    // write reg
    memset(buftmp, 0, 32);
    buftmp[0] = sub_addr;
    i2c_data.msgs[0].len = 1;
    i2c_data.msgs[0].addr = device_addr;
    i2c_data.msgs[0].flags = 0; // 0: write 1:read
    i2c_data.msgs[0].buf = buftmp;
    // read data
    i2c_data.msgs[1].len = ByteNo;
    i2c_data.msgs[1].addr = device_addr;
    i2c_data.msgs[1].flags = 1; // 0: write 1:read
    i2c_data.msgs[1].buf = buff;

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&i2c_data);
    if (ret < 0) {
        printf("read data %x %x error\r\n", device_addr, sub_addr);
        close(fd);
        free(i2c_data.msgs);
        return I2C_TRANSFER_FAIL;
    }
    free(i2c_data.msgs);
    close(fd);

    return I2C_SUCCESS;
}

int i2c_write(int i2cChannel, unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo)
{
    int fd, ret;
    unsigned char buftmp[32];
    struct i2c_rdwr_ioctl_data i2c_data;

    if (i2cChannel == I2C_DEV_3) {
        fd = open(i2c_dev_3, O_RDWR);
    } else if (i2cChannel == I2C_DEV_4) {
        fd = open(i2c_dev_4, O_RDWR);
    } else {
        printf("wrong i2c channel %d\n", i2cChannel);
        return I2C_PARAM_FAIL;
    }

    if (fd < 0) {
        printf("can not open dev %d\n", i2cChannel);
        return I2C_OPEN_DEV_FAIL;
    }

    i2c_data.nmsgs = 1;
    i2c_data.msgs = (struct i2c_msg *)malloc(i2c_data.nmsgs * sizeof(struct i2c_msg));
    if (i2c_data.msgs == NULL) {
        printf("malloc error \n");
        close(fd);
        return I2C_OPEN_DEV_FAIL;
    }

    ioctl(fd, I2C_TIMEOUT, 1);
    ioctl(fd, I2C_RETRIES, 2);

    memset(buftmp, 0, 32);
    buftmp[0] = sub_addr;
    memcpy(buftmp + 1, buff, ByteNo);
    i2c_data.msgs[0].len = ByteNo + 1;
    ;
    i2c_data.msgs[0].addr = device_addr;
    i2c_data.msgs[0].flags = 0; // 0: write 1:read
    i2c_data.msgs[0].buf = buftmp;
    ret = ioctl(fd, I2C_RDWR, (unsigned long)&i2c_data);
    if (ret < 0) {
        printf("write reg %x %x error\r\n", device_addr, sub_addr);
        close(fd);
        free(i2c_data.msgs);
        return I2C_TRANSFER_FAIL;
    }
    free(i2c_data.msgs);
    close(fd);

    usleep(50000);

    return I2C_SUCCESS;
}

int i2c_writeWithoutSub(int i2cChannel, unsigned char device_addr, unsigned char *buff, int ByteNo)
{

    int fd, ret;
    unsigned char buftmp[32];
    struct i2c_rdwr_ioctl_data i2c_data;

    uint32_t result = 0;

    if (i2cChannel == I2C_DEV_3) {
        fd = open(i2c_dev_3, O_RDWR);
    } else if (i2cChannel == I2C_DEV_4) {
        fd = open(i2c_dev_4, O_RDWR);
    } else {
        printf("wrong i2c channel %d\n", i2cChannel);
        return I2C_PARAM_FAIL;
    }

    if (fd < 0) {
        printf("can not open dev %d\n", i2cChannel);
        return I2C_OPEN_DEV_FAIL;
    }

    i2c_data.nmsgs = 1;
    i2c_data.msgs = (struct i2c_msg *)malloc(i2c_data.nmsgs * sizeof(struct i2c_msg));
    if (i2c_data.msgs == NULL) {
        printf("malloc error \n");
        close(fd);
        return I2C_OPEN_DEV_FAIL;
    }

    ioctl(fd, I2C_TIMEOUT, 1);
    ioctl(fd, I2C_RETRIES, 2);

    // write reg
    i2c_data.msgs[0].len = ByteNo;
    i2c_data.msgs[0].addr = device_addr;
    i2c_data.msgs[0].flags = 0; // 0: write 1:read
    i2c_data.msgs[0].buf = buff;

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&i2c_data);
    if (ret < 0) {
        printf("i2c_writeWithoutSub %x  error", device_addr);
        close(fd);
        free(i2c_data.msgs);
        return I2C_TRANSFER_FAIL;
    }
    free(i2c_data.msgs);
    close(fd);
    usleep(50000);

    return I2C_SUCCESS;
}

int i2c_readWithoutSub(int i2cChannel, int device_addr, unsigned char *buff, int ByteNo)
{

    int fd, ret;
    int i;
    struct i2c_rdwr_ioctl_data i2c_data;
    uint32_t result = 0;

    if (i2cChannel == I2C_DEV_3) {
        fd = open(i2c_dev_3, O_RDWR);
    } else if (i2cChannel == I2C_DEV_4) {
        fd = open(i2c_dev_4, O_RDWR);
    } else {
        printf("wrong i2c channel %d\n", i2cChannel);
        return I2C_PARAM_FAIL;
    }

    if (fd < 0) {
        printf("can not open dev %d\n", i2cChannel);
        return I2C_OPEN_DEV_FAIL;
    }

    i2c_data.nmsgs = 1;
    i2c_data.msgs = (struct i2c_msg *)malloc(i2c_data.nmsgs * sizeof(struct i2c_msg));
    if (i2c_data.msgs == NULL) {
        printf("malloc error \n");
        close(fd);
        return I2C_OPEN_DEV_FAIL;
    }

    ioctl(fd, I2C_TIMEOUT, 2);
    ioctl(fd, I2C_RETRIES, 2);

    // read data
    i2c_data.msgs[0].len = ByteNo;
    i2c_data.msgs[0].addr = device_addr;
    i2c_data.msgs[0].flags = 1; // 0: write 1:read
    i2c_data.msgs[0].buf = buff;

    ret = ioctl(fd, I2C_RDWR, (unsigned long)&i2c_data);
    if (ret < 0) {
        printf("i2c_readWithoutSub read data 0x%x  error", device_addr);
        close(fd);
        free(i2c_data.msgs);
        return I2C_TRANSFER_FAIL;
    }
    free(i2c_data.msgs);
    close(fd);

    return 0;
}
