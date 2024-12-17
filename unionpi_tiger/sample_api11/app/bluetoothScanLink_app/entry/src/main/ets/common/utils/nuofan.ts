/* Copyright 2023 Unionman Technology Co., Ltd.
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

import ble from '@ohos.bluetooth.ble';

export function NuoFanParseData(res: ble.BLECharacteristic): Record<string, number> {
  let array = Array.from(new Uint8Array(res.characteristicValue));
  if (array[2] === 184) {
    return {
      "bloodMeasureHigh": array[4],
      "bloodMeasureLow": array[5],
      "checkHeartRate": array[6]
    }
  }
}