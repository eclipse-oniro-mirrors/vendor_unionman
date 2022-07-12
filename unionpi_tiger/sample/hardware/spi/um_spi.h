#ifndef __UM_SPI_H__
#define __UM_SPI_H__
#include <stdint.h>

#define SPI_CPHA 0x01
#define SPI_CPOL 0x02
#define SPI_MODE_0 (0 | 0)
#define SPI_MODE_1 (0 | SPI_CPHA)
#define SPI_MODE_2 (SPI_CPOL | 0)
#define SPI_MODE_3 (SPI_CPOL | SPI_CPHA)

#define SPI_DISABLE 0
#define SPI_ENABLE 1

#define SPI_CS_Mode_LOW 0
#define SPI_CS_Mode_HIGH 1
#define SPI_CS_Mode_NONE 3

#define SPI_BIT_ORDER_LSBFIRST 0
#define SPI_BIT_ORDER_MSBFIRST 1

#define SPI_3WIRE_Mode 0
#define SPI_4WIRE_Mode 1

// errno
#define SPI_SUCCESS 0
#define SPI_OPEN_DEV_FAIL -1
#define SPI_NOT_OPENED_FAIL -2
#define SPI_SET_MODE_FAIL -3
#define SPI_GET_MODE_FAIL -4
#define SPI_PARAM_FAIL -5
#define SPI_TRANSFER_FAIL -6

#define DEFAULT_DEV "/dev/spidev32766.0"

#define SPI_CS_HIGH 0x04   // Chip select high
#define SPI_LSB_FIRST 0x08 // LSB
#define SPI_3WIRE 0x10     // 3-wire mode SI and SO same line
#define SPI_LOOP 0x20      // Loopback mode
#define SPI_NO_CS 0x40     // A single device occupies one SPI bus, so there is no chip select
#define SPI_READY 0x80     // Slave pull low to stop data transmission

/**
 * Define SPI attribute
 **/
typedef struct SPIStruct {

    uint32_t speed;
    uint16_t mode;
    uint16_t delay;
    int fd; //
} HARDWARE_SPI;

//�������ܣ���40_ext�ϵ�spi�ӿ�
int DEV_HARDWARE_SPI_begin();

//���ܺ������ر�40_ext�ϵ�spi�ӿ�
int DEV_HARDWARE_SPI_end(void);

/*
���ܺ���������spi�ӿڵ�CPOL��CPHAģʽ
�������壺
int mode: ָ��spi�ӿڵ�CPOL��CPHAλ
*/
int DEV_HARDWARE_SPI_Mode(int mode);

/*
���ܺ�������ȡspi�ӿڵ�CPOL��CPHAģʽ
*/
int DEV_HARDWARE_SPI_GET_Mode(int *mode);

/*
���ܺ���������spi�ӿڵĶ�д����λ��
�������壺
int bits: ָ��spi�ӿڵĶ�д����λ�� Ĭ��Ϊ8
*/
int DEV_HARDWARE_SPI_SET_BitOrder(int order);

/*
���ܺ�������ȡspi�ӿڵĶ�д����λ��
*/
int DEV_HARDWARE_SPI_GET_BitOrder(int *order);

/*
���ܺ���������spi�ӿڵ�Ƭѡ�ź�ģʽ������Ч/����Ч��
�������壺
int mode: ָ��spi�ӿڵ�Ƭѡ�ź�ģʽ��Ĭ��Ϊ����Ч
*/
int DEV_HARDWARE_SPI_SET_ChipSelect(int CS_Mode);

/*
���ܺ���������spi�ӿڵĴ����ֽ���lsb/msb��
�������壺
int mode: ָ��spi�ӿڵĴ����ֽ���ģʽ
*/
int DEV_HARDWARE_SPI_GET_ChipSelect(int *CS_Mode);

/*
���ܺ���������spi�ӿڵĶ�д�����Ƶ��
�������壺
int speed: ָ��spi�ӿڵĶ�д�����Ƶ�� һ������ 10000000
*/
int DEV_HARDWARE_SPI_SET_SPEED(int speed);

/*
���ܺ�������ȡspi�ӿڵĶ�д�����Ƶ��
�������壺��
*/
int DEV_HARDWARE_SPI_GET_SPEED(int *speed);

/*
���ܺ�����spiȫ˫����������
          ��Ҫע�⣬˫��������ʱ������д�����ݳ������
�������壺
int[] txBuf: д����buffer
int txBufLen: д����buffer�ĳ���
����ֵ  �� spiȫ˫���������ݶ�ȡ����buffer�������ݳ�����д�����ݳ�����ͬ
*/
int DEV_HARDWARE_SPI_transferFullDuplex(unsigned char *txbuf, int len, unsigned char *rxbuf);

#endif // endif __UM_SPI_H__
