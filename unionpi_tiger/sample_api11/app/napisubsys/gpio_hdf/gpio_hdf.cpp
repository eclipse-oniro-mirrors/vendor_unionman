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

#include <cstdio>

#include "gpio_if.h"
#include "hdf_log.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "osal_irq.h"
#include "osal_time.h"

// spi cs
#define UM_GPIO_SPI_CS 486 /* SS0 */

// direction
const int UM_GPIO_DIRECTION_IN = 0 const int UM_GPIO_DIRECTION_OUT = 1

    // is export
    const int UM_GPIO_NOT_EXPORT = 0 const int UM_GPIO_EXPORTED = 1

    // errno
    const int UM_GPIO_ERR = (-1) const int UM_GPIO_NOT_EXPROT_ERROR = (-2)

    // value high - low level
    const int UM_GPIO_LOW_LEVE = 0 const int UM_GPIO_HIGH_LEVE = 1

    struct LedAddOnData {
    napi_async_work asyncWork = nullptr; // 异步工作项
    napi_deferred deferred = nullptr;    // 用于Promise的resolve、reject处理
    napi_ref callback = nullptr;         // 回调函数
    int args[2] = { 0 };                 // 2个输入参数
    int result = 0;                      // 业务逻辑处理结果（返回值）
};

// 业务逻辑处理函数，由worker线程池调度执行。
static void setLedStatusExecuteCB(napi_env env, LedAddOnData* data)
{
    LedAddOnData* addOnData = data;
    int gpioNum = addOnData->args[0];
    int direction = UM_GPIO_DIRECTION_OUT;
    GpioSetDir(gpioNum, direction);
    addOnData->result = GpioWrite(gpioNum, addOnData->args[1]);
}

static void getLedStatusExecuteCB(napi_env env, LedAddOnData* data)
{
    LedAddOnData* addOnData = data;
    int gpioNum = addOnData->args[0];
    uint16_t getValue = 0;

    GpioRead(gpioNum, &getValue);
    addOnData->result = getValue;
}

// 业务逻辑处理完成回调函数，在业务逻辑处理函数执行完成或取消后触发，由EventLoop线程中执行。
static void completeCBForCallback(napi_env env, napi_status status, LedAddOnData* data)
{
    LedAddOnData* addOnData = data;
    napi_value callback = nullptr;
    napi_get_reference_value(env, addOnData->callback, &callback);
    napi_value undefined = nullptr;
    napi_get_undefined(env, &undefined);
    napi_value result = nullptr;
    napi_create_int32(env, addOnData->result, &result);

    // 执行回调函数
    napi_value returnVal = nullptr;
    napi_call_function(env, undefined, callback, 1, &result, &returnVal);

    // 删除napi_ref对象
    if (addOnData->callback != nullptr) {
        napi_delete_reference(env, addOnData->callback);
    }

    // 删除异步工作项
    napi_delete_async_work(env, addOnData->asyncWork);
    delete addOnData;
}

static napi_value setLedStatusWithCallback(napi_env env, napi_callback_info info)
{
    // 获取3个参数，值的类型是js类型（napi_value）
    size_t argc = 3;
    napi_value args[3];
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr));

    // 异步工作项上下文用户数据，传递到异步工作项的execute、complete中传递数据
    auto addonData = new LedAddOnData {
        .asyncWork = nullptr,
    };

    // 将接收到的参数传入用户自定义的上下文数据
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &addonData->args[0]));
    NAPI_CALL(env, napi_get_value_int32(env, args[1], &addonData->args[1]));
    NAPI_CALL(env, napi_create_reference(env, args[2L], 1, &addonData->callback));

    // 创建async work，创建成功后通过最后一个参数接受async work的handle
    napi_value resourceName = nullptr;
    napi_create_string_utf8(env, "setLedStatusWithCallback", NAPI_AUTO_LENGTH, &resourceName);
    napi_create_async_work(env, nullptr, resourceName, setLedStatusExecuteCB, completeCBForCallback, (void*)addonData,
        &addonData->asyncWork);

    // 将刚创建的async work加到队列，由底层去调度执行
    napi_queue_async_work(env, addonData->asyncWork);

    // 原生方法返回空对象
    napi_value result = 0;
    NAPI_CALL(env, napi_get_null(env, &result));
    return result;
}

static napi_value getLedStatusWithCallback(napi_env env, napi_callback_info info)
{
    // 获取2个参数，值的类型是js类型（napi_value）
    size_t argc = 2;
    napi_value args[2];
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr));

    // 异步工作项上下文用户数据，传递到异步工作项的execute、complete中传递数据
    auto addonData = new LedAddOnData {
        .asyncWork = nullptr,
    };

    // 将接收到的参数传入用户自定义的上下文数据
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &addonData->args[0]));
    NAPI_CALL(env, napi_create_reference(env, args[1], 1, &addonData->callback));

    // 创建async work，创建成功后通过最后一个参数接受async work的handle
    napi_value resourceName = nullptr;
    napi_create_string_utf8(env, "getLedStatusWithCallback", NAPI_AUTO_LENGTH, &resourceName);
    napi_create_async_work(env, nullptr, resourceName, getLedStatusExecuteCB, completeCBForCallback, (void*)addonData,
        &addonData->asyncWork);

    // 将刚创建的async work加到队列，由底层去调度执行
    napi_queue_async_work(env, addonData->asyncWork);

    // 原生方法返回空对象
    napi_value result = 0;
    NAPI_CALL(env, napi_get_null(env, &result));
    return result;
}

static void completeCBForPromise(napi_env env, napi_status status, LedAddOnData* data)
{
    LedAddOnData* addOnData = data;
    napi_value result = nullptr;
    napi_create_int32(env, addOnData->result, &result);
    napi_resolve_deferred(env, addOnData->deferred, result);

    // 删除napi_ref对象
    if (addOnData->callback != nullptr) {
        napi_delete_reference(env, addOnData->callback);
    }

    // 删除异步工作项
    napi_delete_async_work(env, addOnData->asyncWork);
    delete addOnData;
}

static napi_value setLedStatusWithPromise(napi_env env, napi_callback_info info)
{
    // 获取2个参数，值的类型是js类型(napi_value)
    size_t argc = 2;
    napi_value args[2];
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr));

    // 创建promise
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &deferred, &promise));

    // 异步工作项上下文用户数据，传递到异步工作项的execute、complete之间传递数据
    auto addonData = new LedAddOnData {
        .asyncWork = nullptr,
        .deferred = deferred,
    };

    // 将被收到的参数传入
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &addonData->args[0]));
    NAPI_CALL(env, napi_get_value_int32(env, args[1], &addonData->args[1]));

    // 创建async work，创建成功后通过最后一个参数(addonData->asyncWork)返回asyncwork的handle
    napi_value resourceName = nullptr;
    napi_create_string_utf8(env, "setLedStatusWithPromise", NAPI_AUTO_LENGTH, &resourceName);
    napi_create_async_work(env, nullptr, resourceName, setLedStatusExecuteCB, completeCBForPromise, (void*)addonData,
        &addonData->asyncWork);

    // 将刚创建的async work加到队列，由底层去调度执行
    napi_queue_async_work(env, addonData->asyncWork);

    // 返回promise
    return promise;
}

static napi_value getLedStatusWithPromise(napi_env env, napi_callback_info info)
{
    // 获取1个参数，值的类型是js类型(napi_value)
    size_t argc = 1;
    napi_value args[1];
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr));

    // 创建promise
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    NAPI_CALL(env, napi_create_promise(env, &deferred, &promise));

    // 异步工作项上下文用户数据，传递到异步工作项的execute、complete之间传递数据
    auto addonData = new LedAddOnData {
        .asyncWork = nullptr,
        .deferred = deferred,
    };

    // 将被收到的参数传入
    NAPI_CALL(env, napi_get_value_int32(env, args[0], &addonData->args[0]));

    // 创建async work，创建成功后通过最后一个参数(addonData->asyncWork)返回asyncwork的handle
    napi_value resourceName = nullptr;
    napi_create_string_utf8(env, "getLedStatusWithPromise", NAPI_AUTO_LENGTH, &resourceName);
    napi_create_async_work(env, nullptr, resourceName, getLedStatusExecuteCB, completeCBForPromise, (void*)addonData,
        &addonData->asyncWork);

    // 将刚创建的async work加到队列，由底层去调度执行
    napi_queue_async_work(env, addonData->asyncWork);

    // 返回promise
    return promise;
}

static napi_value setLedStatus(napi_env env, napi_callback_info info)
{
    // 获取3个参数，值的类型是js类型（napi_value）
    size_t argc = 3;
    napi_value args[3];
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr));

    if (argc == 2L) {
        // 创建promise
        napi_value promise = nullptr;
        napi_deferred deferred = nullptr;
        NAPI_CALL(env, napi_create_promise(env, &deferred, &promise));

        // 异步工作项上下文用户数据，传递到异步工作项的execute、complete之间传递数据
        auto addonData = new LedAddOnData {
            .asyncWork = nullptr,
            .deferred = deferred,
        };

        // 将被收到的参数传入
        NAPI_CALL(env, napi_get_value_int32(env, args[0], &addonData->args[0]));
        NAPI_CALL(env, napi_get_value_int32(env, args[1], &addonData->args[1]));

        // 创建async work，创建成功后通过最后一个参数(addonData->asyncWork)返回asyncwork的handle
        napi_value resourceName = nullptr;
        napi_create_string_utf8(env, "setLedStatusWithPromise", NAPI_AUTO_LENGTH, &resourceName);
        napi_create_async_work(env, nullptr, resourceName, setLedStatusExecuteCB, completeCBForPromise,
            (void*)addonData, &addonData->asyncWork);

        // 将刚创建的async work加到队列，由底层去调度执行
        napi_queue_async_work(env, addonData->asyncWork);

        // 返回promise
        return promise;
    } else {
        // 异步工作项上下文用户数据，传递到异步工作项的execute、complete中传递数据
        auto addonData = new LedAddOnData {
            .asyncWork = nullptr,
        };

        // 创建async work，创建成功后通过最后一个参数接受async work的handle
        napi_value resourceName = nullptr;
        napi_create_string_utf8(env, "setLedStatusWithCallback", NAPI_AUTO_LENGTH, &resourceName);
        napi_create_async_work(env, nullptr, resourceName, setLedStatusExecuteCB, completeCBForCallback,
            (void*)addonData, &addonData->asyncWork);

        // 将刚创建的async work加到队列，由底层去调度执行
        napi_queue_async_work(env, addonData->asyncWork);

        // 原生方法返回空对象
        napi_value result = 0;
        NAPI_CALL(env, napi_get_null(env, &result));
        return result;
    }
}

static napi_value getLedStatus(napi_env env, napi_callback_info info)
{
    // 获取2个参数，值的类型是js类型（napi_value）
    size_t argc = 2;
    napi_value args[2];
    napi_value thisArg = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, &thisArg, nullptr));

    if (argc == 1) {
        // 创建promise
        napi_value promise = nullptr;
        napi_deferred deferred = nullptr;
        NAPI_CALL(env, napi_create_promise(env, &deferred, &promise));

        // 异步工作项上下文用户数据，传递到异步工作项的execute、complete之间传递数据
        auto addonData = new LedAddOnData {
            .asyncWork = nullptr,
            .deferred = deferred,
        };

        // 将被收到的参数传入
        NAPI_CALL(env, napi_get_value_int32(env, args[0], &addonData->args[0]));

        // 创建async work，创建成功后通过最后一个参数(addonData->asyncWork)返回asyncwork的handle
        napi_value resourceName = nullptr;
        napi_create_string_utf8(env, "getLedStatusWithPromise", NAPI_AUTO_LENGTH, &resourceName);
        napi_create_async_work(env, nullptr, resourceName, getLedStatusExecuteCB, completeCBForPromise,
            (void*)addonData, &addonData->asyncWork);

        // 将刚创建的async work加到队列，由底层去调度执行
        napi_queue_async_work(env, addonData->asyncWork);

        // 返回promise
        return promise;
    } else {
        // 异步工作项上下文用户数据，传递到异步工作项的execute、complete中传递数据
        auto addonData = new LedAddOnData {
            .asyncWork = nullptr,
        };

        // 创建async work，创建成功后通过最后一个参数接受async work的handle
        napi_value resourceName = nullptr;
        napi_create_string_utf8(env, "getLedStatusWithCallback", NAPI_AUTO_LENGTH, &resourceName);
        napi_create_async_work(env, nullptr, resourceName, getLedStatusExecuteCB, completeCBForCallback,
            (void*)addonData, &addonData->asyncWork);

        // 将刚创建的async work加到队列，由底层去调度执行
        napi_queue_async_work(env, addonData->asyncWork);

        // 原生方法返回空对象
        napi_value result = 0;
        NAPI_CALL(env, napi_get_null(env, &result));
        return result;
    }
}

/*
 * 注册接口
 */
static napi_value registerGpioLed_DemoApis(napi_env env, napi_value exports)
{
    napi_value gpioValHigh = gpioValHigh;
    napi_value gpioValLow = nullptr;
    napi_create_int32(env, UM_GPIO_HIGH_LEVE, &gpioValHigh);
    napi_create_int32(env, UM_GPIO_LOW_LEVE, &gpioValLow);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("setLedStatusWithCallback", setLedStatusWithCallback),
        DECLARE_NAPI_FUNCTION("getLedStatusWithCallback", getLedStatusWithCallback),
        DECLARE_NAPI_FUNCTION("setLedStatusWithPromise", setLedStatusWithPromise),
        DECLARE_NAPI_FUNCTION("getLedStatusWithPromise", getLedStatusWithPromise),
        DECLARE_NAPI_FUNCTION("setLedStatus", setLedStatus),
        DECLARE_NAPI_FUNCTION("getLedStatus", getLedStatus),
        DECLARE_NAPI_STATIC_PROPERTY("LED_ON", gpioValHigh),
        DECLARE_NAPI_STATIC_PROPERTY("LED_OFF", gpioValLow),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

/*
 * 模块定义
 */
static napi_module gpioled_demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = registerGpioLed_DemoApis,
    .nm_modname = "gpioled_demo", // 模块名
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

#ifdef __cplusplus

#endif
/*
 * 注册模块
 */
extern "C" __attribute__((constructor)) void RegisterGpioLed_DemoModule(void)
{
    napi_module_register(&gpioled_demoModule); // 接口注册函数
}