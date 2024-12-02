/* Copyright 2022 Unionman Technology Co., Ltd.
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

/**
 * unionman a311d
 * @since 8
 * @devices phone, tablet
 * @import import um_gpio from '@ohos.um_a311d';
 * @permission N/A
 */

declare namespace pwmtest {

    /**
     * 设置RGB灯的PWM占空比并控制绿色灯的开关
     * @param redDuty 红色通道的PWM占空比 (0-100)
     * @param blueDuty 蓝色通道的PWM占空比 (0-100)
     * @param greenLedOn 控制绿色灯的开关 (1: 亮, 0: 灭)
     * @returns Promise 返回PWM控制的启用状态（1为启用，0为未启用）
     */
    function setPwmGpioStatus(redDuty: number, blueDuty: number, greenLedOn: number): Promise<number>;
}

export default pwmtest;
