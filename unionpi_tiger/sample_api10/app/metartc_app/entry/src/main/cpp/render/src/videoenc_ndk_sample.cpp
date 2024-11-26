/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
#include <arpa/inet.h>
#include <sys/time.h>
#include <utility>
//#include "iconsumer_surface.h"
//#include "openssl/crypto.h"
//#include "openssl/sha.h"
//#include "display_type.h"
#include "videoenc_ndk_sample.h"
#include "log.h"
using namespace OHOS;
using namespace OHOS::Media;
using namespace std;
namespace {
const string MIME_TYPE = "video/avc";
constexpr int64_t NANOS_IN_SECOND = 1000000000L;
constexpr int64_t NANOS_IN_MICRO = 1000L;
constexpr uint32_t FRAME_INTERVAL = 16666;
constexpr uint32_t MAX_PIXEL_FMT = 5;
constexpr uint32_t IDR_FRAME_INTERVAL = 10;
//sptr<Surface> cs = nullptr;
//sptr<Surface> ps = nullptr;
VEncNdkSample *enc_sample = nullptr;

void clearIntqueue(std::queue<uint32_t> &q)
{
    std::queue<uint32_t> empty;
    swap(empty, q);
}

void clearBufferqueue(std::queue<OH_AVCodecBufferAttr> &q)
{
    std::queue<OH_AVCodecBufferAttr> empty;
    swap(empty, q);
}
} // namespace

VEncNdkSample::VEncNdkSample(YangContext *pcontext)
{
    signal_ = nullptr;
    m_context = pcontext;
}

VEncNdkSample::~VEncNdkSample()
{
    LOGI("%{public}s, %{public}d", __FUNCTION__, __LINE__);
}

static void VencError(OH_AVCodec *codec, int32_t errorCode, void *userData)
{
    LOGI("%{public}s, %{public}d, Error errorCode = %{public}d", __FUNCTION__, __LINE__, errorCode);
}

static void VencFormatChanged(OH_AVCodec *codec, OH_AVFormat *format, void *userData)
{
    LOGI("%{public}s, %{public}d, Format Changed", __FUNCTION__, __LINE__);
}

static void VencInputDataReady(OH_AVCodec *codec, uint32_t index, OH_AVMemory *data, void *userData)
{
    VEncSignal *signal = static_cast<VEncSignal *>(userData);
    unique_lock<mutex> lock(signal->inMutex_);

    signal->inIdxQueue_.push(index);
    signal->inBufferQueue_.push(data);
    signal->inCond_.notify_all();
}

static void VencOutputDataReady(OH_AVCodec *codec, uint32_t index, OH_AVMemory *data, OH_AVCodecBufferAttr *attr,
                                void *userData)
{
    VEncSignal *signal = static_cast<VEncSignal *>(userData);
    unique_lock<mutex> lock(signal->outMutex_);
    signal->outIdxQueue_.push(index);
    signal->attrQueue_.push(*attr);
    signal->outBufferQueue_.push(data);
    signal->outCond_.notify_all();
    //LOGI("%{public}s, %{public}d, index = %{public}d, attr->size = %{public}d", __FUNCTION__, __LINE__, index, attr->size);
}
int64_t VEncNdkSample::GetSystemTimeUs()
{
    struct timespec now;
    (void)clock_gettime(CLOCK_BOOTTIME, &now);
    int64_t nanoTime = (int64_t)now.tv_sec * NANOS_IN_SECOND + now.tv_nsec;

    return nanoTime / NANOS_IN_MICRO;
}

int32_t VEncNdkSample::ConfigureVideoEncoder()
{
    OH_AVFormat *format = OH_AVFormat_Create();
    if (format == nullptr) {
        LOGI("%{public}s, %{public}d, Fatal: Failed to create format", __FUNCTION__, __LINE__);
        return AV_ERR_UNKNOWN;
    }

    OH_AVPixelFormat pixel_format = AV_PIXEL_FORMAT_YUVI420;
    if(m_context->avinfo.video.videoCaptureFormat == YangNv12){
        pixel_format = AV_PIXEL_FORMAT_NV12;
    }
    
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    (void)OH_AVFormat_SetIntValue(format, OH_MD_KEY_WIDTH, DEFAULT_WIDTH);
    (void)OH_AVFormat_SetIntValue(format, OH_MD_KEY_HEIGHT, DEFAULT_HEIGHT);
    (void)OH_AVFormat_SetIntValue(format, OH_MD_KEY_PIXEL_FORMAT, pixel_format);
    (void)OH_AVFormat_SetDoubleValue(format, OH_MD_KEY_FRAME_RATE, DEFAULT_FRAME_RATE);
    (void)OH_AVFormat_SetLongValue(format, OH_MD_KEY_BITRATE, DEFAULT_BITRATE);
    int ret = OH_VideoEncoder_Configure(venc_, format);
    OH_AVFormat_Destroy(format);
    return ret;
}

int32_t VEncNdkSample::ConfigureVideoEncoder_fuzz(int32_t data)
{
    OH_AVFormat *format = OH_AVFormat_Create();
    if (format == nullptr) {
        LOGI("%{public}s, %{public}d, Fatal: Failed to create format", __FUNCTION__, __LINE__);
        return AV_ERR_UNKNOWN;
    }
    (void)OH_AVFormat_SetIntValue(format, OH_MD_KEY_WIDTH, data);
    DEFAULT_WIDTH = data;
    (void)OH_AVFormat_SetIntValue(format, OH_MD_KEY_HEIGHT, data);
    DEFAULT_HEIGHT = data;
    (void)OH_AVFormat_SetIntValue(format, OH_MD_KEY_PIXEL_FORMAT, data % MAX_PIXEL_FMT);
    double frameRate = data;
    (void)OH_AVFormat_SetDoubleValue(format, OH_MD_KEY_FRAME_RATE, frameRate);

    OH_AVFormat_SetIntValue(format, OH_MD_KEY_RANGE_FLAG, data);
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_COLOR_PRIMARIES, data);
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_TRANSFER_CHARACTERISTICS, data);
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_MATRIX_COEFFICIENTS, data);
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_I_FRAME_INTERVAL, data);
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_VIDEO_ENCODE_BITRATE_MODE, data);
    OH_AVFormat_SetLongValue(format, OH_MD_KEY_BITRATE, data);
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_QUALITY, data);

    int ret = OH_VideoEncoder_Configure(venc_, format);
    OH_AVFormat_Destroy(format);
    return ret;
}

int32_t VEncNdkSample::SetVideoEncoderCallback()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    signal_ = new VEncSignal();
    if (signal_ == nullptr) {
        LOGI("%{public}s, %{public}d, Failed to new VEncSignal", __FUNCTION__, __LINE__);
        return AV_ERR_UNKNOWN;
    }

    cb_.onError = VencError;
    cb_.onStreamChanged = VencFormatChanged;
    cb_.onNeedInputData = VencInputDataReady;
    cb_.onNeedOutputData = VencOutputDataReady;
    return OH_VideoEncoder_SetCallback(venc_, cb_, static_cast<void *>(signal_));
}

int32_t VEncNdkSample::state_EOS()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    unique_lock<mutex> lock(signal_->inMutex_);
    signal_->inCond_.wait(lock, [this]() { return signal_->inIdxQueue_.size() > 0; });
    uint32_t index = signal_->inIdxQueue_.front();
    signal_->inIdxQueue_.pop();
    signal_->inBufferQueue_.pop();
    lock.unlock();
    
    OH_AVCodecBufferAttr attr;
    attr.pts = 0;
    attr.size = 0;
    attr.offset = 0;
    attr.flags = AVCODEC_BUFFER_FLAGS_EOS;
    return OH_VideoEncoder_PushInputData(venc_, index, attr);
}
void VEncNdkSample::ReleaseInFile()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    if (inFileYUV != nullptr) {
        fclose(inFileYUV);
        inFileYUV = nullptr;
    }
}

void VEncNdkSample::StopInloop()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    if (inputLoop_ != nullptr && inputLoop_->joinable()) {
        unique_lock<mutex> lock(signal_->inMutex_);
        clearIntqueue(signal_->inIdxQueue_);
        isRunning_.store(false);
        signal_->inCond_.notify_all();
        lock.unlock();

        inputLoop_->join();
        inputLoop_ = nullptr;
    }
    LOGI("%{public}s, %{public}d, end", __FUNCTION__, __LINE__);
}

void VEncNdkSample::testApi()
{
    OH_VideoEncoder_GetSurface(venc_, &nativeWindow);
    OH_VideoEncoder_Prepare(venc_);
    OH_VideoEncoder_GetInputDescription(venc_);
    OH_VideoEncoder_Start(venc_);
    OH_AVFormat *format = OH_AVFormat_Create();
    OH_AVFormat_SetIntValue(format, OH_MD_KEY_REQUEST_I_FRAME, 1);
    OH_VideoEncoder_SetParameter(venc_, format);
    OH_VideoEncoder_NotifyEndOfStream(venc_);
    OH_VideoEncoder_GetOutputDescription(venc_);
    OH_AVFormat_Destroy(format);
    OH_VideoEncoder_Flush(venc_);
    bool isValid = false;
    OH_VideoEncoder_IsValid(venc_, &isValid);
    OH_VideoEncoder_Stop(venc_);
    OH_VideoEncoder_Reset(venc_);
}

int32_t VEncNdkSample::CreateSurface()
{
    int32_t ret = 0;
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    #if 0
    ret = OH_VideoEncoder_GetSurface(venc_, &nativeWindow);
    if (ret != AV_ERR_OK) {
        LOGI("%{public}s, %{public}d, OH_VideoEncoder_GetSurface fail", __FUNCTION__, __LINE__);
        return ret;
    }
    ret = OH_NativeWindow_NativeWindowHandleOpt(nativeWindow, SET_FORMAT, GRAPHIC_PIXEL_FMT_YCBCR_420_SP);
    if (ret != AV_ERR_OK) {
        LOGI("%{public}s, %{public}d, NativeWindowHandleOpt SET_FORMAT fail", __FUNCTION__, __LINE__);
        return ret;
    }
    ret = OH_NativeWindow_NativeWindowHandleOpt(nativeWindow, SET_BUFFER_GEOMETRY, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    if (ret != AV_ERR_OK) {
        LOGI("%{public}s, %{public}d, NativeWindowHandleOpt SET_BUFFER_GEOMETRY fail", __FUNCTION__, __LINE__);
        return ret;
    }
    #endif
    return AV_ERR_OK;
}

int32_t VEncNdkSample::OpenFileFail()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    isRunning_.store(false);
    (void)OH_VideoEncoder_Stop(venc_);
    return AV_ERR_UNKNOWN;
}

int32_t VEncNdkSample::StartVideoEncoder()
{
    isRunning_.store(true);
    int32_t ret = 0;
    LOGI("%{public}s, %{public}d, SURFACE_INPUT = %{public}d", __FUNCTION__, __LINE__, SURFACE_INPUT);
    if (SURFACE_INPUT) {
        ret = CreateSurface();
        if (ret != AV_ERR_OK) {
            return ret;
        }
    }
    OH_VideoEncoder_Prepare(venc_);
    ret = OH_VideoEncoder_Start(venc_);
    if (ret != AV_ERR_OK) {
        LOGI("%{public}s, %{public}d, Failed to start codec", __FUNCTION__, __LINE__);
        isRunning_.store(false);
        signal_->inCond_.notify_all();
        signal_->outCond_.notify_all();
        return ret;
    }
    //inFileYUV = fopen("/data/storage/el2/base/haps/entry/files/soft.yuv", "rb");
    //inFileYUV = fopen("/data/storage/el2/base/haps/entry/files/1280_720_nv.yuv", "rb");
    inFileYUV = fopen("/data/storage/el2/base/haps/entry/files/video_001.yuv", "rb");
    if (SURFACE_INPUT) {
        inputLoop_ = make_unique<thread>(&VEncNdkSample::InputFuncSurface, this);
    } else {
        inputLoop_ = make_unique<thread>(&VEncNdkSample::InputFunc, this);
    }
    if (inputLoop_ == nullptr) {
        LOGI("%{public}s, %{public}d, Failed to create input loop", __FUNCTION__, __LINE__);
        isRunning_.store(false);
        (void)OH_VideoEncoder_Stop(venc_);
        ReleaseInFile();
        return AV_ERR_UNKNOWN;
    }
    outputLoop_ = make_unique<thread>(&VEncNdkSample::OutputFunc, this);
    if (outputLoop_ == nullptr) {
        LOGI("%{public}s, %{public}d, Failed to create output loop", __FUNCTION__, __LINE__);
        isRunning_.store(false);
        (void)OH_VideoEncoder_Stop(venc_);
        ReleaseInFile();
        StopInloop();
        Release();
        return AV_ERR_UNKNOWN;
    }
    return AV_ERR_OK;
}

int32_t VEncNdkSample::CreateVideoEncoder(const char *codecName)
{
    LOGI("%{public}s, %{public}d, codecName = %{public}s", __FUNCTION__, __LINE__, codecName);
    venc_ = OH_VideoEncoder_CreateByName(codecName);
    enc_sample = this;
    return venc_ == nullptr ? AV_ERR_UNKNOWN : AV_ERR_OK;
}

void VEncNdkSample::WaitForEOS()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    if (inputLoop_)
        inputLoop_->join();
    if (outputLoop_)
        outputLoop_->join();
    inputLoop_ = nullptr;
    outputLoop_ = nullptr;
}

uint32_t VEncNdkSample::ReadOneFrameYUV420SP(uint8_t *dst)
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    uint8_t *start = dst;
    #if 0
    // copy Y
    for (uint32_t i = 0; i < DEFAULT_HEIGHT; i++) {
        inFile_->read(reinterpret_cast<char *>(dst), DEFAULT_WIDTH);
        if (!ReturnZeroIfEOS(DEFAULT_WIDTH))
            return 0;
        dst += stride_;
    }
    // copy UV
    for (uint32_t i = 0; i < DEFAULT_HEIGHT / SAMPLE_RATIO; i++) {
        inFile_->read(reinterpret_cast<char *>(dst), DEFAULT_WIDTH);
        if (!ReturnZeroIfEOS(DEFAULT_WIDTH))
            return 0;
        dst += stride_;
    }
    #endif
    return dst - start;
}

uint32_t VEncNdkSample::FlushSurf(OHNativeWindowBuffer *ohNativeWindowBuffer, OH_NativeBuffer *nativeBuffer)
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    #if 0
    struct Region region;
    struct Region::Rect *rect = new Region::Rect();
    rect->x = 0;
    rect->y = 0;
    rect->w = DEFAULT_WIDTH;
    rect->h = DEFAULT_HEIGHT;
    region.rects = rect;
    NativeWindowHandleOpt(nativeWindow, SET_UI_TIMESTAMP, GetSystemTimeUs());
    int32_t err = OH_NativeBuffer_Unmap(nativeBuffer);
    if (err != 0) {
        LOGI("%{public}s, %{public}d, OH_NativeBuffer_Unmap failed", __FUNCTION__, __LINE__,);
        return 1;
    }
    err = OH_NativeWindow_NativeWindowFlushBuffer(nativeWindow, ohNativeWindowBuffer, -1, region);
    delete rect;
    if (err != 0) {
        LOGI("%{public}s, %{public}d, FlushBuffer failed", __FUNCTION__, __LINE__);
        return 1;
    }
    #endif
    return 0;
}

void VEncNdkSample::InputFuncSurface()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    #if 0
    while (true) {
        OHNativeWindowBuffer *ohNativeWindowBuffer;
        int fenceFd = -1;
        if (nativeWindow == nullptr) {
            LOGI("%{public}s, %{public}d, nativeWindow == nullptr", __FUNCTION__, __LINE__);
            break;
        }

        int32_t err = OH_NativeWindow_NativeWindowRequestBuffer(nativeWindow, &ohNativeWindowBuffer, &fenceFd);
        if (err != 0) {
            LOGI("%{public}s, %{public}d, RequestBuffer failed, GSError = %{public}d", __FUNCTION__, __LINE__, err);
            continue;
        }
        if (fenceFd > 0) {
            close(fenceFd);
        }
        OH_NativeBuffer *nativeBuffer = OH_NativeBufferFromNativeWindowBuffer(ohNativeWindowBuffer);
        void *virAddr = nullptr;
        err = OH_NativeBuffer_Map(nativeBuffer, &virAddr);
        if (err != 0) {
            LOGI("%{public}s, %{public}d, OH_NativeBuffer_Map failed, GSError = %{public}d", __FUNCTION__, __LINE__, err);
            isRunning_.store(false);
            break;
        }
        uint8_t *dst = (uint8_t *)virAddr;
        const SurfaceBuffer *sbuffer = SurfaceBuffer::NativeBufferToSurfaceBuffer(nativeBuffer);
        int stride = sbuffer->GetStride();
        if (dst == nullptr || stride < DEFAULT_WIDTH) {
            LOGI("%{public}s, %{public}d, invalid va or stride = %{public}d", __FUNCTION__, __LINE__, stride);
            err = NativeWindowCancelBuffer(nativeWindow, ohNativeWindowBuffer);
            isRunning_.store(false);
            break;
        }
        stride_ = stride;
        if (!ReadOneFrameYUV420SP(dst)) {
            err = OH_VideoEncoder_NotifyEndOfStream(venc_);
            if (err != 0) {
                LOGI("%{public}s, %{public}d, OH_VideoEncoder_NotifyEndOfStream failed", __FUNCTION__, __LINE__);
            }
            break;
        }
        if (FlushSurf(ohNativeWindowBuffer, nativeBuffer))
            break;
        usleep(FRAME_INTERVAL);
    }
    #endif
}

void VEncNdkSample::Flush_buffer()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    unique_lock<mutex> inLock(signal_->inMutex_);
    clearIntqueue(signal_->inIdxQueue_);
    std::queue<OH_AVMemory *> empty;
    swap(empty, signal_->inBufferQueue_);
    signal_->inCond_.notify_all();
    inLock.unlock();
    unique_lock<mutex> outLock(signal_->outMutex_);
    clearIntqueue(signal_->outIdxQueue_);
    clearBufferqueue(signal_->attrQueue_);
    signal_->outCond_.notify_all();
    outLock.unlock();
}

void VEncNdkSample::RepeatStartBeforeEOS()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    if (REPEAT_START_FLUSH_BEFORE_EOS > 0) {
        REPEAT_START_FLUSH_BEFORE_EOS--;
        OH_VideoEncoder_Flush(venc_);
        Flush_buffer();
        OH_VideoEncoder_Start(venc_);
    }
    
    if (REPEAT_START_STOP_BEFORE_EOS > 0) {
        REPEAT_START_STOP_BEFORE_EOS--;
        OH_VideoEncoder_Stop(venc_);
        Flush_buffer();
        OH_VideoEncoder_Start(venc_);
    }
}

bool VEncNdkSample::RandomEOS(uint32_t index)
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    uint32_t random_eos = rand() % 25;
    if (enable_random_eos && random_eos == frameCount) {
        OH_AVCodecBufferAttr attr;
        attr.pts = 0;
        attr.size = 0;
        attr.offset = 0;
        attr.flags = AVCODEC_BUFFER_FLAGS_EOS;
        OH_VideoEncoder_PushInputData(venc_, index, attr);
        LOGI("%{public}s, %{public}d, random eos", __FUNCTION__, __LINE__);
        frameCount++;
        unique_lock<mutex> lock(signal_->inMutex_);
        signal_->inIdxQueue_.pop();
        signal_->inBufferQueue_.pop();
        return true;
    }
    return false;
}

void VEncNdkSample::SetEOS(uint32_t index)
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    OH_AVCodecBufferAttr attr;
    attr.pts = 0;
    attr.size = 0;
    attr.offset = 0;
    attr.flags = AVCODEC_BUFFER_FLAGS_EOS;
    int32_t res = OH_VideoEncoder_PushInputData(venc_, index, attr);
    LOGI("%{public}s, %{public}d, OH_VideoEncoder_PushInputData    EOS   res:%{public}d", __FUNCTION__, __LINE__, res);
    unique_lock<mutex> lock(signal_->inMutex_);
    signal_->inIdxQueue_.pop();
    signal_->inBufferQueue_.pop();
}

int32_t VEncNdkSample::PushData(OH_AVMemory *avBuffer, uint32_t index, int32_t &result)
{
    int32_t res = -2;
    OH_AVCodecBufferAttr attr;
    YangFrame yuvFrame;
    YangFrame *p_yuvFrame = &yuvFrame;
    uint8_t *fileBuffer = OH_AVMemory_GetAddr(avBuffer);

    if(m_context->metaCaptureVideoBuffer && m_context->metaCaptureVideoBuffer->size() < 1){
        usleep(10*1000);
        result = 0;
        return 0;
    }
    if (fileBuffer == nullptr) {
        LOGI("%{public}s, %{public}d, Fatal: no memory", __FUNCTION__, __LINE__);
        return -1;
    }
    
    yang_memset(p_yuvFrame, 0x0, sizeof(YangFrame));
    m_context->metaCaptureVideoBuffer->peakVideo(p_yuvFrame);
    
    attr.pts = GetSystemTimeUs();
    attr.size = p_yuvFrame->nb;
    attr.offset = 0;
    attr.flags = AVCODEC_BUFFER_FLAGS_NONE;
    int32_t size = OH_AVMemory_GetSize(avBuffer);
    if (size < p_yuvFrame->nb) {
        LOGI("%{public}s, %{public}d, bufferSize smaller than yuv size, size:%{public}d, p_yuvFrame->nb:%{public}d", 
            __FUNCTION__, __LINE__, size, p_yuvFrame->nb);
        return -1;
    }
    
    if (enableForceIDR && (frameCount % IDR_FRAME_INTERVAL == 0)) {
        OH_AVFormat *format = OH_AVFormat_Create();
        OH_AVFormat_SetIntValue(format, OH_MD_KEY_REQUEST_I_FRAME, 1);
        OH_VideoEncoder_SetParameter(venc_, format);
        OH_AVFormat_Destroy(format);
        format = nullptr;
    }
    
    yang_memcpy(fileBuffer, p_yuvFrame->payload, p_yuvFrame->nb);
    m_context->metaCaptureVideoBuffer->getVideoRef(p_yuvFrame);//release

    //LOGI("%{public}s, %{public}d, index = %{public}d, size = %{public}d", __FUNCTION__, __LINE__, index, size);
    result = OH_VideoEncoder_PushInputData(venc_, index, attr);
    unique_lock<mutex> lock(signal_->inMutex_);
    signal_->inIdxQueue_.pop();
    signal_->inBufferQueue_.pop();

    return res;
}

int32_t VEncNdkSample::CheckResult(bool isRandomEosSuccess, int32_t pushResult)
{
    if (isRandomEosSuccess) {
        if (pushResult == 0) {
            errCount = errCount + 1;
            LOGI("%{public}s, %{public}d, push input after eos should be failed!  pushResult = %{public}d", __FUNCTION__, __LINE__, pushResult);
        }
        return -1;
    } else if (pushResult != 0) {
        errCount = errCount + 1;
        LOGI("%{public}s, %{public}d, push input data failed, error:%{public}d", __FUNCTION__, __LINE__, pushResult);
        return -1;
    }
    return 0;
}

void VEncNdkSample::InputFunc()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    errCount = 0;
    while (true) {
        if (!isRunning_.load()) {
            break;
        }
        //RepeatStartBeforeEOS();
        unique_lock<mutex> lock(signal_->inMutex_);
        signal_->inCond_.wait(lock, [this]() {
            if (!isRunning_.load()) {
                return true;
            }
            return signal_->inIdxQueue_.size() > 0;
        });
        if (!isRunning_.load()) {
            break;
        }
        uint32_t index = signal_->inIdxQueue_.front();
        auto buffer = signal_->inBufferQueue_.front();

        lock.unlock();
        bool isRandomEosSuccess = false;
        #if 0
        bool isRandomEosSuccess = RandomEOS(index);
        if (isRandomEosSuccess) {
            continue;
        }
        #endif
        int32_t pushResult = 0;
        int32_t ret = PushData(buffer, index, pushResult);
        if (CheckResult(isRandomEosSuccess, pushResult) == -1) {
            break;
        }
        frameCount++;
        if (sleepOnFPS) {
            usleep(FRAME_INTERVAL);
        }
        usleep(10*1000);
    }
    LOGI("%{public}s, %{public}d, end", __FUNCTION__, __LINE__);
}

int32_t VEncNdkSample::CheckAttrFlag(OH_AVCodecBufferAttr attr)
{
    if (attr.flags == AVCODEC_BUFFER_FLAGS_EOS) {
        LOGI("%{public}s, %{public}d, attr.flags == AVCODEC_BUFFER_FLAGS_EOS", __FUNCTION__, __LINE__);
        unique_lock<mutex> inLock(signal_->inMutex_);
        isRunning_.store(false);
        signal_->inCond_.notify_all();
        signal_->outCond_.notify_all();
        inLock.unlock();
        return -1;
    }
    if (attr.flags == AVCODEC_BUFFER_FLAGS_CODEC_DATA) {
        LOGI("%{public}s, %{public}d, enc AVCODEC_BUFFER_FLAGS_CODEC_DAT", __FUNCTION__, __LINE__);
    }
    outCount = outCount + 1;
    return 0;
}

void VEncNdkSample::OutputFuncFail()
{
    LOGI("%{public}s, %{public}d, errCount > 0", __FUNCTION__, __LINE__);
    unique_lock<mutex> inLock(signal_->inMutex_);
    isRunning_.store(false);
    signal_->inCond_.notify_all();
    signal_->outCond_.notify_all();
    inLock.unlock();
    (void)Stop();
    Release();
}

void VEncNdkSample::OutputFunc()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    int outFile_count = 0;
    uint8_t *srcVideo = new uint8_t[1024*1024];
    while (true) {
        if (!isRunning_.load()) {
            break;
        }
        OH_AVCodecBufferAttr attr;
        uint32_t index;
        unique_lock<mutex> lock(signal_->outMutex_);
        signal_->outCond_.wait(lock, [this]() {
            if (!isRunning_.load()) {
                return true;
            }
            return signal_->outIdxQueue_.size() > 0;
        });
        if (!isRunning_.load()) {
            break;
        }
        index = signal_->outIdxQueue_.front();
        attr = signal_->attrQueue_.front();
        OH_AVMemory *buffer = signal_->outBufferQueue_.front();
        signal_->outBufferQueue_.pop();
        signal_->outIdxQueue_.pop();
        signal_->attrQueue_.pop();
        lock.unlock();
        if (CheckAttrFlag(attr) == -1) {
            break;
        }
        int size = attr.size;
        YangFrame videoFrame;
        memset(&videoFrame,0,sizeof(YangFrame));
        videoFrame.payload = srcVideo;
        videoFrame.nb = size;
        videoFrame.pts = attr.pts;
        memcpy(videoFrame.payload, OH_AVMemory_GetAddr(buffer), size);

//        LOGI("%{public}s, %{public}d, index = %{public}d, size = %{public}d, pts = %{public}lld, flags=%{public}d start=0x%{public}x",
//             __FUNCTION__, __LINE__, index, size, attr.pts, attr.flags, *(uint32_t*)srcVideo);

        if(attr.flags == AVCODEC_BUFFER_FLAGS_SYNC_FRAME)
            videoFrame.frametype = YANG_Frametype_I;
        else if(attr.flags == AVCODEC_BUFFER_FLAGS_NONE)
            videoFrame.frametype = YANG_Frametype_P;
        else if(attr.flags == AVCODEC_BUFFER_FLAGS_CODEC_DATA)
            videoFrame.frametype = YANG_Frametype_Spspps;
        else
            videoFrame.frametype = YANG_Frametype_P; 
        m_context->metaVideoEncoderBuffer->putEVideo(&videoFrame);
        if (OH_VideoEncoder_FreeOutputData(venc_, index) != AV_ERR_OK) {
            LOGI("%{public}s, %{public}d, Fatal: ReleaseOutputBuffer fail", __FUNCTION__, __LINE__);
            errCount = errCount + 1;
        }
        if (errCount > 0) {
            OutputFuncFail();
            break;
        }
    }
    yang_deleteA(srcVideo);
    LOGI("%{public}s, %{public}d, end", __FUNCTION__, __LINE__);
}

int32_t VEncNdkSample::Flush()
{
    unique_lock<mutex> inLock(signal_->inMutex_);
    clearIntqueue(signal_->inIdxQueue_);
    signal_->inCond_.notify_all();
    inLock.unlock();
    unique_lock<mutex> outLock(signal_->outMutex_);
    clearIntqueue(signal_->outIdxQueue_);
    clearBufferqueue(signal_->attrQueue_);
    signal_->outCond_.notify_all();
    outLock.unlock();
    return OH_VideoEncoder_Flush(venc_);
}

int32_t VEncNdkSample::Reset()
{
    isRunning_.store(false);
    StopInloop();
    StopOutloop();
    ReleaseInFile();
    return OH_VideoEncoder_Reset(venc_);
}

int32_t VEncNdkSample::Release()
{
    int ret = OH_VideoEncoder_Destroy(venc_);
    venc_ = nullptr;
    if (signal_ != nullptr) {
        delete signal_;
        signal_ = nullptr;
    }
    LOGI("%{public}s, %{public}d, end", __FUNCTION__, __LINE__);
    return ret;
}

int32_t VEncNdkSample::Stop()
{
    StopInloop();
    StopOutloop();
    clearIntqueue(signal_->outIdxQueue_);
    clearBufferqueue(signal_->attrQueue_);
    ReleaseInFile();
    return OH_VideoEncoder_Stop(venc_);
}

int32_t VEncNdkSample::Start()
{
    return OH_VideoEncoder_Start(venc_);
}

void VEncNdkSample::StopOutloop()
{
    LOGI("%{public}s, %{public}d, start", __FUNCTION__, __LINE__);
    if (outputLoop_ != nullptr && outputLoop_->joinable()) {
        unique_lock<mutex> lock(signal_->outMutex_);
        clearIntqueue(signal_->outIdxQueue_);
        clearBufferqueue(signal_->attrQueue_);
        signal_->outCond_.notify_all();
        lock.unlock();
    }
    LOGI("%{public}s, %{public}d, end", __FUNCTION__, __LINE__);
}

void VEncNdkSample::SetParameter(OH_AVFormat *format)
{
    if (venc_) {
        OH_VideoEncoder_SetParameter(venc_, format);
    }
}