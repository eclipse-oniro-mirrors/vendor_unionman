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

#ifndef __UM_I2C_H__
#define __UM_I2C_H__

// i2c channel
#define I2C_DEV_3 3
#define I2C_DEV_4 4

// i2c dev
#define I2C_DEV_CHAR_3 "/dev/i2c-3"
#define I2C_DEV_CHAR_4 "/dev/i2c-4"

// errno
#define I2C_SUCCESS 0
#define I2C_OPEN_DEV_FAIL (-1)
#define I2C_NOT_OPENED_FAIL (-2)
#define I2C_PARAM_FAIL (-3)
#define I2C_TRANSFER_FAIL (-4)

// vaild device address
#define I2C_MIN_DEVICE_ADDRESS 0x03
#define I2C_MAX_DEVICE_ADDRESS 0x77

/**
 * Define I2C attribute
 **/
typedef struct I2CStruct {
    int fd; //
} HARDWARE_I2C;

int i2c_read(int i2cChannel, int device_addr, int sub_addr, unsigned char *buff, int ByteNo);
int i2c_write(int i2cChannel, unsigned char device_addr, unsigned char sub_addr, unsigned char *buff, int ByteNo);
int i2c_writeWithoutSub(int i2cChannel, unsigned char device_addr, unsigned char *buff, int ByteNo);
int i2c_readWithoutSub(int i2cChannel, int device_addr, unsigned char *buff, int ByteNo);

#endif // endif __UM_I2C_H__