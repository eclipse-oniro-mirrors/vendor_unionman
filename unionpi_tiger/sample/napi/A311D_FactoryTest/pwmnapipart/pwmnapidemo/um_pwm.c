/*
 * Copyright 2023 Unionman Technology Co., Ltd.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hilog/log.h"
#include "securec.h"
#include "um_pwm.h"

int init_pmw(int pwmChannel)
{
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/export", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/export", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM EXPORT FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    fp = fopen(pwm_file_name, "w");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open export file!");
        return PWM_FILE_NOT_EXIST;
    }
    (void)fprintf(fp, "%d", 0);
    (void)fclose(fp);
    fp = NULL;
    return 0;
}

int set_pwm_period(int pwmChannel, int period)
{
    HILOG_INFO(LOG_CORE, "PWM =======%{public}s\n", __func__);
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/period", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/period", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM PERIOD FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    fp = fopen(pwm_file_name, "r+");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open period file!");
        return PWM_FILE_NOT_EXIST;
    }
    if (period) {
        fprintf(fp, "%d", period);
    }
    (void)fclose(fp);
    fp = NULL;

    return 0;
}

int set_pwm_dutyCycle(int pwmChannel, int dutyCycle)
{
    HILOG_INFO(LOG_CORE, "PWM =======%{public}s\n", __func__);
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/duty_cycle", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/duty_cycle", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM DUTY_CYCLE FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    fp = fopen(pwm_file_name, "r+");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open duty_cycle file!");
        return PWM_FILE_NOT_EXIST;
    }
    if (dutyCycle) {
        fprintf(fp, "%d", dutyCycle);
    }
    (void)fclose(fp);
    fp = NULL;

    return 0;
}

int set_pwm_polarity(int pwmChannel, int polarity)
{
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/polarity", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/polarity", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM POKARITY FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    fp = fopen(pwm_file_name, "rw+");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open polarity file!");
        return PWM_FILE_NOT_EXIST;
    }
    if (polarity == PWM_POLARITY_NORMAL) {
        fprintf(fp, "%s", "normal");
    } else if (polarity == PWM_POLARITY_INVERSED) {
        fprintf(fp, "%s", "inversed");
    }
    (void)fclose(fp);
    fp = NULL;

    return 0;
}

int set_pwm_enable(int pwmChannel, int isEnable)
{
    HILOG_INFO(LOG_CORE, "PWM =======%{public}s\n", __func__);
    int ret = -1;
    char buffer[256] = { 0 };
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/enable", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/enable", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM ENABLE FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    ret = snprintf_s(buffer, sizeof(buffer), sizeof(buffer), "echo %d > %s", isEnable, pwm_file_name);
    if (ret == -1) {
        HILOG_ERROR(LOG_CORE, "WIRITE STRING FAILED\n")
        return PWM_WRITE_FAILED;
    }
    
    system(buffer);

    return 0;
}

int get_pwm_period(int pwmChannel)
{
    int ret = 0;
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/period", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/period", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM PERIOD FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    char buffer[32] = { 0 };
    (void)memset_s(buffer, sizeof(buffer), 0, sizeof(buffer));
    fp = fopen(pwm_file_name, "r");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open period file!");
        return PWM_FILE_NOT_EXIST;
    }
    (void)fread(buffer, sizeof(buffer), 1, fp);
    (void)fclose(fp);
    fp = NULL;

    ret = atoi(buffer);
    return ret;
}

int get_pwm_dutyCycle(int pwmChannel)
{
    int ret = 0;
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));
    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/duty_cycle", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/duty_cycle", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM DUTY_CYCLE FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    char buffer[32] = { 0 };
    (void)memset_s(buffer, sizeof(buffer), 0, sizeof(buffer));
    fp = fopen(pwm_file_name, "r");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open duty_cycle file!");
        return PWM_FILE_NOT_EXIST;
    }
    (void)fread(buffer, sizeof(buffer), 1, fp);
    (void)fclose(fp);
    fp = NULL;

    ret = atoi(buffer);
    return ret;
}

int get_pwm_polarity(int pwmChannel)
{
    int ret = 0;
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/polarity", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/polarity", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM POLARITY FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    char buffer[32] = { 0 };
    (void)memset_s(buffer, sizeof(buffer), 0, sizeof(buffer));
    fp = fopen(pwm_file_name, "r");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open polarity file!");
        return PWM_FILE_NOT_EXIST;
    }
    (void)fread(buffer, sizeof(buffer), 1, fp);
    (void)fclose(fp);
    fp = NULL;

    if (strstr(buffer, "normal") != NULL) {
        ret = PWM_POLARITY_NORMAL;
    } else if (strstr(buffer, "inversed") != NULL) {
        ret = PWM_POLARITY_INVERSED;
    } else {
        HILOG_ERROR(LOG_CORE, "PWM ERROR \n");
        ret = PWM_ERR;
    }

    return ret;
}

int is_pwm_enabled(int pwmChannel)
{
    HILOG_INFO(LOG_CORE, "PWM =======%{public}s\n", __func__);
    int ret = 0;
    char pwm_file_name[128] = { 0 };
    (void)memset_s(pwm_file_name, sizeof(pwm_file_name), 0, sizeof(pwm_file_name));

    if (PWM1 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/enable", PWM1_PEX);
    } else if (PWM2 == pwmChannel) {
        (void)sprintf_s(pwm_file_name, sizeof(pwm_file_name), "%s/pwm0/enable", PWM2_PEX);
    } else {
        HILOG_ERROR(LOG_CORE, "PWM WRONOG CHANEEL\n");
        return PWM_WRONOG_CHANNEL;
    }

    if (access(pwm_file_name, F_OK) != 0) {
        HILOG_ERROR(LOG_CORE, "PWM ENABLE FILE NOT EXIST\n");
        return PWM_FILE_NOT_EXIST;
    }

    FILE* fp = NULL;
    char buffer[32] = { 0 };
    (void)memset_s(buffer, sizeof(buffer), 0, sizeof(buffer));
    fp = fopen(pwm_file_name, "r");
    if (!fp) {
        HILOG_ERROR(LOG_CORE, "Failed to open enable file!");
        return PWM_FILE_NOT_EXIST;
    }
    (void)fread(buffer, sizeof(buffer), 1, fp);
    (void)fclose(fp);
    fp = NULL;

    ret = atoi(buffer);
    return ret;
}