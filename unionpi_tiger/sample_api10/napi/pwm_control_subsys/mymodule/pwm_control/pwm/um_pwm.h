/* Copyright 2024 Unionman Technology Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef __UM_PWM_H__
#define __UM_PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif
// errno
#define PWM_ERR (-1)
#define PWM_WRONOG_CHANNEL (-2)
#define PWM_FILE_NOT_EXIST (-3)
#define PWM_SPRINTF_ERR (-4)
// pwm enable
#define PWM_NOT_ENABLED 0
#define PWM_IS_ENABLED 1

// pwm polarity
#define PWM_POLARITY_NORMAL 0
#define PWM_POLARITY_INVERSED 1

#define PWM1 1
#define PWM2 2

// pwm的引脚目录
#define PWM1_PEX "/sys/class/pwm/pwmchip0"
#define PWM2_PEX "/sys/class/pwm/pwmchip2"

// Hilog
#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0  // 标识业务领域，范围0x0~0xFFFFF
#define LOG_TAG "Pwm_Test"

/*
 * 作用：初始化引脚，生成对应的引脚目录
 * 参数：pwmChannel 为选择的引脚
 */
int UmInitPwm(int pwmChannel);

/*
 * 设置pwm的溢出值
 * 参数：pwmChannel 为选择的引脚，period 为溢出值
 */
int UmSetPwmPeriod(int pwmChannel, int period);

/*
 * 设置pwm一个周期高电平时间
 * 参数：pwmChannel 为选择的引脚，dutyCycle 为一个周期高电平的值
 */
int UmSetPwmDutyCycle(int pwmChannel, int dutyCycle);

/*
 * 设置pwm的极性
 * 参数：pwmChannel 为选择的引脚，polarity 为极性
 */
int UmSetPwmPolarity(int pwmChannel, int polarity);

/*
 * 打开pwm引脚，使其使能
 * 参数：pwmChannel 为选择的引脚，isEnable 为开关值
 */
int UmSetPwmEnable(int pwmChannel, int isEnable);

/*
 * 得到pwm的溢出值
 * 参数：pwmChannel 为选择的引脚
 */
int UmGetPwmPeriod(int pwmChannel);

/*
 * 得到pwm的一个周期高电平的值
 * 参数：pwmChannel 为选择的引脚
 */
int UmGetPwmDutyCycle(int pwmChannel);

/*
 * 得到pwm的极性
 * 参数：pwmChannel 为选择的引脚
 */
int UmGetPwmPolarity(int pwmChannel);

/*
 * 查看pwm的引脚使能值
 * 参数：pwmChannel 为选择的引脚
 */
int UmIsPwmEnabled(int pwmChannel);
#ifdef __cplusplus
}
#endif

#endif // endif __UM_PWM_H__
