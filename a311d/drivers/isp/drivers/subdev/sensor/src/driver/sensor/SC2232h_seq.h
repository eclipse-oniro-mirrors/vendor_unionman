/*
*
* SPDX-License-Identifier: GPL-2.0
*
* Copyright (C) 2011-2018 ARM or its affiliates
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; version 2.
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#if !defined(__SC2232H_SEQ_H__)
#define __SC2232H_SEQ_H__

static acam_reg_t linear_1920_1080_30fps_390Mbps_2lane_10bits[] = {
    {0x0103, 0x01, 0xFF, 1},
    {0x0100, 0x00, 0xFF, 1},
    {0x3034, 0x80, 0xFF, 1},
    {0x3039, 0x80, 0xFF, 1},
    {0x3001, 0xfe, 0xFF, 1},
    {0x3018, 0x33, 0xFF, 1},
    {0x301c, 0x78, 0xFF, 1},
    {0x301f, 0x05, 0xFF, 1},
    {0x3031, 0x0a, 0xFF, 1},
    {0x3035, 0x9b, 0xFF, 1},
    {0x3037, 0x20, 0xFF, 1},
    {0x3038, 0xff, 0xFF, 1},
    {0x303a, 0xb3, 0xFF, 1},
    {0x303b, 0x16, 0xFF, 1},
    {0x303c, 0x0e, 0xFF, 1},
    {0x320c, 0x08, 0xFF, 1},
    {0x320d, 0x20, 0xFF, 1},
    {0x320e, 0x04, 0xFF, 1},
    {0x320f, 0xe2, 0xFF, 1},
    {0x3211, 0x0c, 0xFF, 1},
    {0x3213, 0x04, 0xFF, 1},
    {0x3222, 0x29, 0xFF, 1},
    {0x3235, 0x09, 0xFF, 1},
    {0x3236, 0xc2, 0xFF, 1},
    {0x3301, 0x12, 0xFF, 1},
    {0x3302, 0x1f, 0xFF, 1},
    {0x3303, 0x20, 0xFF, 1},
    {0x3306, 0x48, 0xFF, 1},
    {0x3308, 0x10, 0xFF, 1},
    {0x3309, 0x60, 0xFF, 1},
    {0x330b, 0xcd, 0xFF, 1},
    {0x330e, 0x30, 0xFF, 1},
    {0x3314, 0x04, 0xFF, 1},
    {0x331b, 0x83, 0xFF, 1},
    {0x331e, 0x19, 0xFF, 1},
    {0x331f, 0x59, 0xFF, 1},
    {0x3320, 0x01, 0xFF, 1},
    {0x3326, 0x00, 0xFF, 1},
    {0x3333, 0x30, 0xFF, 1},
    {0x335e, 0x01, 0xFF, 1},
    {0x335f, 0x03, 0xFF, 1},
    {0x3366, 0x7c, 0xFF, 1},
    {0x3367, 0x08, 0xFF, 1},
    {0x3368, 0x04, 0xFF, 1},
    {0x3369, 0x00, 0xFF, 1},
    {0x336a, 0x00, 0xFF, 1},
    {0x336b, 0x00, 0xFF, 1},
    {0x337c, 0x04, 0xFF, 1},
    {0x337d, 0x06, 0xFF, 1},
    {0x337f, 0x03, 0xFF, 1},
    {0x33a0, 0x05, 0xFF, 1},
    {0x33aa, 0x10, 0xFF, 1},
    {0x360f, 0x01, 0xFF, 1},
    {0x3614, 0x80, 0xFF, 1},
    {0x3620, 0x28, 0xFF, 1},
    {0x3621, 0x28, 0xFF, 1},
    {0x3622, 0x06, 0xFF, 1},
    {0x3624, 0x08, 0xFF, 1},
    {0x3625, 0x02, 0xFF, 1},
    {0x3630, 0x9c, 0xFF, 1},
    {0x3631, 0x84, 0xFF, 1},
    {0x3632, 0x08, 0xFF, 1},
    {0x3633, 0x4f, 0xFF, 1},
    {0x3635, 0xa0, 0xFF, 1},
    {0x3636, 0x25, 0xFF, 1},
    {0x3637, 0x55, 0xFF, 1},
    {0x3638, 0x1f, 0xFF, 1},
    {0x3639, 0x09, 0xFF, 1},
    {0x363a, 0x9f, 0xFF, 1},
    {0x363b, 0x26, 0xFF, 1},
    {0x363c, 0x05, 0xFF, 1},
    {0x3641, 0x01, 0xFF, 1},
    {0x366e, 0x08, 0xFF, 1},
    {0x366f, 0x2c, 0xFF, 1},
    {0x3670, 0x0c, 0xFF, 1},
    {0x3671, 0xc6, 0xFF, 1},
    {0x3672, 0x06, 0xFF, 1},
    {0x3673, 0x16, 0xFF, 1},
    {0x3677, 0x86, 0xFF, 1},
    {0x3678, 0x88, 0xFF, 1},
    {0x3679, 0x88, 0xFF, 1},
    {0x367a, 0x28, 0xFF, 1},
    {0x367b, 0x3f, 0xFF, 1},
    {0x367e, 0x08, 0xFF, 1},
    {0x367f, 0x28, 0xFF, 1},
    {0x3690, 0x33, 0xFF, 1},
    {0x3691, 0x11, 0xFF, 1},
    {0x3692, 0x43, 0xFF, 1},
    {0x369c, 0x08, 0xFF, 1},
    {0x369d, 0x28, 0xFF, 1},
    {0x3802, 0x00, 0xFF, 1},
    {0x3900, 0x19, 0xFF, 1},
    {0x3901, 0x02, 0xFF, 1},
    {0x3902, 0xc5, 0xFF, 1},
    {0x3903, 0x08, 0xFF, 1},
    {0x3905, 0x98, 0xFF, 1},
    {0x3907, 0x00, 0xFF, 1},
    {0x3908, 0x11, 0xFF, 1},
    {0x391d, 0x04, 0xFF, 1},
    {0x391e, 0x00, 0xFF, 1},
    {0x3933, 0x0a, 0xFF, 1},
    {0x3934, 0x18, 0xFF, 1},
    {0x3940, 0x60, 0xFF, 1},
    {0x3942, 0x02, 0xFF, 1},
    {0x3943, 0x1f, 0xFF, 1},
    {0x395e, 0xc0, 0xFF, 1},
    {0x3960, 0xba, 0xFF, 1},
    {0x3961, 0xae, 0xFF, 1},
    {0x3962, 0x89, 0xFF, 1},
    {0x3963, 0x80, 0xFF, 1},
    {0x3966, 0xba, 0xFF, 1},
    {0x3980, 0xa0, 0xFF, 1},
    {0x3981, 0x40, 0xFF, 1},
    {0x3982, 0x18, 0xFF, 1},
    {0x3984, 0x08, 0xFF, 1},
    {0x3985, 0x18, 0xFF, 1},
    {0x3986, 0x28, 0xFF, 1},
    {0x3987, 0x70, 0xFF, 1},
    {0x3988, 0x08, 0xFF, 1},
    {0x3989, 0x10, 0xFF, 1},
    {0x398a, 0x20, 0xFF, 1},
    {0x398b, 0x30, 0xFF, 1},
    {0x398c, 0x60, 0xFF, 1},
    {0x398d, 0x20, 0xFF, 1},
    {0x398e, 0x10, 0xFF, 1},
    {0x398f, 0x08, 0xFF, 1},
    {0x3990, 0x40, 0xFF, 1},
    {0x3991, 0x24, 0xFF, 1},
    {0x3992, 0x15, 0xFF, 1},
    {0x3993, 0x08, 0xFF, 1},
    {0x3994, 0x0a, 0xFF, 1},
    {0x3995, 0x20, 0xFF, 1},
    {0x3996, 0x38, 0xFF, 1},
    {0x3997, 0x70, 0xFF, 1},
    {0x3998, 0x08, 0xFF, 1},
    {0x3999, 0x10, 0xFF, 1},
    {0x399a, 0x18, 0xFF, 1},
    {0x399b, 0x30, 0xFF, 1},
    {0x399c, 0x30, 0xFF, 1},
    {0x399d, 0x18, 0xFF, 1},
    {0x399e, 0x10, 0xFF, 1},
    {0x399f, 0x08, 0xFF, 1},
    {0x3e00, 0x00, 0xFF, 1},
    {0x3e01, 0x9c, 0xFF, 1},
    {0x3e02, 0x00, 0xFF, 1},
    {0x3e03, 0x0b, 0xFF, 1},
    {0x3e06, 0x00, 0xFF, 1},
    {0x3e07, 0x80, 0xFF, 1},
    {0x3e08, 0x03, 0xFF, 1},
    {0x3e09, 0x10, 0xFF, 1},
    {0x3e1e, 0x34, 0xFF, 1},
    {0x3f00, 0x07, 0xFF, 1},
    {0x3f04, 0x03, 0xFF, 1},
    {0x3f05, 0xec, 0xFF, 1},
    {0x4603, 0x00, 0xFF, 1},
    {0x4809, 0x01, 0xFF, 1},
    {0x4827, 0x48, 0xFF, 1},
    {0x4837, 0x33, 0xFF, 1},
    {0x5000, 0x06, 0xFF, 1},
    {0x5780, 0x7f, 0xFF, 1},
    {0x5781, 0x04, 0xFF, 1},
    {0x5782, 0x03, 0xFF, 1},
    {0x5783, 0x02, 0xFF, 1},
    {0x5784, 0x01, 0xFF, 1},
    {0x5785, 0x18, 0xFF, 1},
    {0x5786, 0x10, 0xFF, 1},
    {0x5787, 0x08, 0xFF, 1},
    {0x5788, 0x02, 0xFF, 1},
    {0x57a0, 0x00, 0xFF, 1},
    {0x57a1, 0x71, 0xFF, 1},
    {0x57a2, 0x01, 0xFF, 1},
    {0x57a3, 0xf1, 0xFF, 1},
    {0x3034, 0x01, 0xFF, 1},
    {0x3039, 0x24, 0xFF, 1},
    //{0x0100, 0x01, 0xFF, 1},

    { 0x0000, 0x0000, 0x0000, 0x0000 },
};

static acam_reg_t settings_context_sc2232h[] = {
    //stop sequence - address is 0x0000
    { 0x0000, 0x0000, 0x0000, 0x0000 }
};

static const acam_reg_t *sc2232h_seq_table[] = {
        linear_1920_1080_30fps_390Mbps_2lane_10bits,
};

static const acam_reg_t *isp_seq_table[] = {
        settings_context_sc2232h,
};

#define SENSOR_SC2232H_SEQUENCE_DEFAULT sc2232h_seq_table
#define SENSOR_SC2232H_ISP_CONTEXT_SEQUENCE isp_seq_table

#define SENSOR_SC2232H_SEQUENCE_1080P_30FPS_PREVIEW  0

#define SENSOR_SC2232H_CONTEXT_SEQ  0

#endif // __SC2232H_SEQ_H__
