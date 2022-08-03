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

#ifndef _UAPI_CAN_NETLINK_H
#define _UAPI_CAN_NETLINK_H

#include <linux/types.h>

/*
 * CAN bit-timing parameters
 *
 * For further information, please read chapter "8 BIT TIMING
 * REQUIREMENTS" of the "Bosch CAN Specification version 2.0"
 * at http://www.semiconductors.bosch.de/pdf/can2spec.pdf.
 */
struct can_bittiming {
    __u32 bitrate;      /* Bit-rate in bits/second */
    __u32 sample_point; /* Sample point in one-tenth of a percent */
    __u32 tq;           /* Time quanta (TQ) in nanoseconds */
    __u32 prop_seg;     /* Propagation segment in TQs */
    __u32 phase_seg1;   /* Phase buffer segment 1 in TQs */
    __u32 phase_seg2;   /* Phase buffer segment 2 in TQs */
    __u32 sjw;          /* Synchronisation jump width in TQs */
    __u32 brp;          /* Bit-rate prescaler */
};

/*
 * CAN harware-dependent bit-timing constant
 *
 * Used for calculating and checking bit-timing parameters
 */
struct can_bittiming_const {
    char name[16];   /* Name of the CAN controller hardware */
    __u32 tseg1_min; /* Time segement 1 = prop_seg + phase_seg1 */
    __u32 tseg1_max;
    __u32 tseg2_min; /* Time segement 2 = phase_seg2 */
    __u32 tseg2_max;
    __u32 sjw_max; /* Synchronisation jump width */
    __u32 brp_min; /* Bit-rate prescaler */
    __u32 brp_max;
    __u32 brp_inc;
};

/*
 * CAN clock parameters
 */
struct can_clock {
    __u32 freq; /* CAN system clock frequency in Hz */
};

/*
 * CAN operational and error states
 */
enum can_state {
    CAN_STATE_ERROR_ACTIVE = 0, /* RX/TX error count < 96 */
    CAN_STATE_ERROR_WARNING,    /* RX/TX error count < 128 */
    CAN_STATE_ERROR_PASSIVE,    /* RX/TX error count < 256 */
    CAN_STATE_BUS_OFF,          /* RX/TX error count >= 256 */
    CAN_STATE_STOPPED,          /* Device is stopped */
    CAN_STATE_SLEEPING,         /* Device is sleeping */
    CAN_STATE_MAX
};

/*
 * CAN bus error counters
 */
struct can_berr_counter {
    __u16 txerr;
    __u16 rxerr;
};

/*
 * CAN controller mode
 */
struct can_ctrlmode {
    __u32 mask;
    __u32 flags;
};

#define CAN_CTRLMODE_LOOPBACK 0x01       /* Loopback mode */
#define CAN_CTRLMODE_LISTENONLY 0x02     /* Listen-only mode */
#define CAN_CTRLMODE_3_SAMPLES 0x04      /* Triple sampling mode */
#define CAN_CTRLMODE_ONE_SHOT 0x08       /* One-Shot mode */
#define CAN_CTRLMODE_BERR_REPORTING 0x10 /* Bus-error reporting */
#define CAN_CTRLMODE_FD 0x20             /* CAN FD mode */
#define CAN_CTRLMODE_PRESUME_ACK 0x40    /* Ignore missing CAN ACKs */

/*
 * CAN device statistics
 */
struct can_device_stats {
    __u32 bus_error;        /* Bus errors */
    __u32 error_warning;    /* Changes to error warning state */
    __u32 error_passive;    /* Changes to error passive state */
    __u32 bus_off;          /* Changes to bus off state */
    __u32 arbitration_lost; /* Arbitration lost errors */
    __u32 restarts;         /* CAN controller re-starts */
};

/*
 * CAN netlink interface
 */
enum {
    IFLA_CAN_UNSPEC,
    IFLA_CAN_BITTIMING,
    IFLA_CAN_BITTIMING_CONST,
    IFLA_CAN_CLOCK,
    IFLA_CAN_STATE,
    IFLA_CAN_CTRLMODE,
    IFLA_CAN_RESTART_MS,
    IFLA_CAN_RESTART,
    IFLA_CAN_BERR_COUNTER,
    IFLA_CAN_DATA_BITTIMING,
    IFLA_CAN_DATA_BITTIMING_CONST,
    __IFLA_CAN_MAX
};

#define IFLA_CAN_MAX (__IFLA_CAN_MAX - 1)

#endif /* !_UAPI_CAN_NETLINK_H */
