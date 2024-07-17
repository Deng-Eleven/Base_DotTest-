#include "led_font.h"

const uint32_t c_pic_1[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x00060006, 0x00060006},
	{0x60066006, 0x60066006, 0x00060006, 0x00060006},
	{0x00060006, 0x00060006, 0x00060006, 0x00060006},
	{0x00060006, 0x00060006, 0x00060006, 0x00060006},
	{0x00060006, 0x00060006, 0x00060006, 0x00060006},
	{0x1FFC1FFC, 0x1FFC1FFC, 0x1FFC1FFC, 0x1FFC1FFC},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_2[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x00060006, 0x00060006},
	{0x60066006, 0x60066006, 0x00060006, 0x00060006},
	{0x00060006, 0x00060006, 0x00060006, 0x00060006},
	{0x00060006, 0x00060006, 0x00060006, 0x00060006},
	{0x00060006, 0x00060006, 0x00060006, 0x00060006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};
	
const uint32_t c_pic_3[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x03F803F8, 0x03F803F8, 0x00F800F8, 0x00F800F8},
	{0x03FC03FC, 0x03FC03FC, 0x00FC00FC, 0x00FC00FC},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_4[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1C781C78, 0x1C781C78, 0x1C181C18, 0x1C181C18},
	{0x3C7C3C7C, 0x3C7C3C7C, 0x3C1C3C1C, 0x3C1C3C1C},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_5[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x3FF83FF8, 0x3FF83FF8, 0x3FF83FF8, 0x3FF83FF8},
	{0x60006000, 0x60006000, 0x60006000, 0x60006000},
	{0x60006000, 0x60006000, 0x60006000, 0x60006000},
	{0x60006000, 0x60006000, 0x60006000, 0x60006000},
	{0x60066006, 0x60066006, 0x60006000, 0x60006000},
	{0x60066006, 0x60066006, 0x60006000, 0x60006000},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_6[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60006000, 0x60006000, 0x60006000, 0x60006000},
	{0x60006000, 0x60006000, 0x60006000, 0x60006000},
	{0x60006000, 0x60006000, 0x60006000, 0x60006000},
	{0x60066006, 0x60066006, 0x60006000, 0x60006000},
	{0x60066006, 0x60066006, 0x60006000, 0x60006000},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_7[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3FC03FC0, 0x3FC03FC0, 0x3F003F00, 0x3F003F00},
	{0x1FC01FC0, 0x1FC01FC0, 0x1F001F00, 0x1F001F00},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_8[16][4] = {
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
	{0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8, 0x1FF81FF8},
	{0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC, 0x3FFC3FFC},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x60066006, 0x60066006, 0x60066006, 0x60066006},
	{0x3E3C3E3C, 0x3E3C3E3C, 0x383C383C, 0x383C383C},
	{0x1E381E38, 0x1E381E38, 0x18381838, 0x18381838},
	{0x00000000, 0x00000000, 0x00000000, 0x00000000},
};

const uint32_t c_pic_full[16][4] = 
{
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},
	{0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF},	
};




// 初始化 wait 数组
const Picture_Type animation_wait[8] = {
    {(uint32_t (*)[4])c_pic_1,5},
    {(uint32_t (*)[4])c_pic_2,5},
    {(uint32_t (*)[4])c_pic_3,5},
    {(uint32_t (*)[4])c_pic_4,5},
    {(uint32_t (*)[4])c_pic_5,5},
    {(uint32_t (*)[4])c_pic_6,5},
    {(uint32_t (*)[4])c_pic_7,5},
    {(uint32_t (*)[4])c_pic_8,5},
};

const Picture_Type full = {(uint32_t (*)[4])c_pic_full,10};
