/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
 */
import distributedObject from '@ohos.data.distributedDataObject'
import Logger from '../common/utils/Logger';

const TAG: string = 'DistributedObjectModel'

export default class DistributedObjectModel {
  public distributedObject?: any
  public changeCallback?: () => void
  public statusCallback?: (sessionId: string, networkId: string, status: 'online' | 'offline') => void

  constructor() {
    this.distributedObject = distributedObject.createDistributedObject({
      positionList: [],
      exit: false,
    })
  }

  genSessionId() {
    return distributedObject.genSessionId()
  }

  setChangeCallback(changeCallback: () => void) {
    if (this.changeCallback === changeCallback) {
      Logger.info(TAG, 'same callback')
      return
    }
    Logger.info(TAG, 'start off')
    if (this.changeCallback !== undefined) {
      this.distributedObject.off('change', this.changeCallback)
    }
    this.changeCallback = changeCallback
    Logger.info(TAG, 'start watch change')
    this.distributedObject.on('change', this.changeCallback)
  }

  setStatusCallback(callback: (sessionId: string, networkId: string, status: 'online' | 'offline') => void) {
    if (this.statusCallback === callback) {
      Logger.info(TAG, 'same callback')
      return
    }
    Logger.info(TAG, 'start off')
    if (this.statusCallback !== undefined) {
      this.distributedObject.off('status', this.statusCallback)
    }
    this.statusCallback = callback
    Logger.info(TAG, 'start watch change')
    this.distributedObject.on('status', this.statusCallback)
  }

  update(exit: boolean) {
    Logger.info(TAG, `doUpdate,${exit}`)
    this.distributedObject.exit = exit
    Logger.info(TAG, `update exit,${JSON.stringify(this.distributedObject.exit)}`)
  }

  add(isFirstPosition: boolean, isEndPosition: boolean, positionX: number, positionY: number) {
    Logger.info(TAG, `doAdd,${isFirstPosition},${isEndPosition},${positionX},${positionY}`)
    Logger.info(TAG, `doAdd,${JSON.stringify(this.distributedObject.positionList)}`)
    this.distributedObject.positionList = [...this.distributedObject.positionList,
      {
        isFirstPosition: isFirstPosition, isEndPosition: isEndPosition, positionX: positionX, positionY: positionY
      }]
    Logger.info(TAG, `add positionList,${JSON.stringify(this.distributedObject.positionList)}`)
  }

  clear() {
    Logger.info(TAG, 'doClear')
    this.distributedObject.positionList = []
    Logger.info(TAG, 'doClear finish')
  }

  off() {
    this.distributedObject.off('change')
    this.changeCallback = undefined
    this.distributedObject.off('status')
    this.statusCallback = undefined
  }
}