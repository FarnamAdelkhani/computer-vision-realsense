// All included firmware files are
// INTEL CORPORATION PROPRIETARY INFORMATION
// Copyright(c) 2019 Intel Corporation. All Rights Reserved
const int fw_L5XX_FW_Image_version[4] = {1,5,0,0};
#ifndef _MSC_VER
__asm__(
    "#version 024cc496856db78569edecbbbf681aafd566b41d\n"
#ifdef __APPLE__
    ".const_data\n"
#define _ "_"
#else
    ".section .rodata\n"
#define _ ""
#endif
    ".global "_"fw_L5XX_FW_Image_data\n"
    _"fw_L5XX_FW_Image_data:\n"
    ".incbin \"C:/GIT/librealsense/build/common/fw/L5XX_FW_Image-1.5.0.0.bin\"\n"
    ".global "_"fw_L5XX_FW_Image_size\n"
    _"fw_L5XX_FW_Image_size:\n"
    "1:\n"
    ".int 1b - "_"fw_L5XX_FW_Image_data\n"
    ".previous"
);
#undef _
#endif
