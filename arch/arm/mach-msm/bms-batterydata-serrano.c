/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/mfd/pm8xxx/batterydata-lib.h>

static struct single_row_lut fcc_temp = {
	.x		= {-20, 0, 25, 40, 60},
#if defined(CONFIG_MACH_SERRANO_DV_LTE)	
	.y		= {2092, 2090, 2087, 2085, 2082},
#else	
	.y		= {1928, 1941, 1940, 1940, 1926},
#endif
	.cols	= 5
};

static struct single_row_lut fcc_sf = {
	.x		= {0},
	.y		= {100},
	.cols	= 1
};

#if defined(CONFIG_MACH_SERRANO_DV_LTE)
static struct sf_lut rbatt_sf = {
	.rows		= 31,
	.cols		= 5,
	.row_entries		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf		= {
				{823, 207, 100, 89, 91},
				{831, 215, 102, 90, 92},
				{831, 215, 102, 90, 92},
				{817, 224, 105, 93, 93},
				{803, 230, 108, 94, 94},
				{789, 225, 113, 98, 96},
				{783, 218, 120, 101, 98},
				{780, 212, 130, 106, 101},
				{783, 208, 132, 116, 107},
				{787, 208, 106, 100, 99},
				{796, 208, 101, 92, 93},
				{815, 209, 102, 93, 94},
				{850, 211, 103, 95, 97},
				{899, 213, 105, 97, 100},
				{971, 219, 107, 96, 100},
				{1078, 225, 110, 95, 97},
				{1219, 220, 106, 93, 96},
				{1345, 218, 105, 93, 96},
				{1552, 229, 101, 91, 94},
				{1736, 245, 102, 92, 95},
				{1766, 252, 103, 93, 96},
				{2005, 263, 105, 95, 97},
				{2442, 284, 107, 96, 99},
				{3139, 320, 111, 98, 101},
				{4306, 380, 116, 101, 103},
				{6281, 494, 119, 103, 102},
				{9993, 738, 117, 100, 99},
				{16955, 1179, 118, 100, 101},
				{29342, 1875, 128, 108, 110},
				{55272, 9100, 164, 136, 155},	
	}
};
#else
static struct sf_lut rbatt_sf = {
	.rows		= 30,
	.cols		= 5,
	.row_entries		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf		= {
				{1804, 285, 100, 80, 72},
				{1804, 285, 100, 80, 72},
				{1753, 287, 101, 82, 73},
				{1735, 292, 105, 83, 74},
				{1717, 294, 108, 86, 77},
				{1504, 310, 116, 89, 79},
				{1456, 274, 116, 91, 82},
				{1434, 267, 127, 97, 84},
				{1452, 262, 129, 103, 88},
				{1505, 252, 113, 101, 89},
				{1594, 250, 99, 80, 74},
				{1704, 250, 99, 82, 75},
				{1834, 254, 101, 85, 78},
				{1978, 270, 104, 88, 81},
				{2125, 293, 107, 86, 82},
				{2280, 322, 110, 85, 74},
				{2450, 346, 108, 85, 75},
				{2617, 353, 106, 84, 76},
				{2766, 359, 100, 81, 74},
				{2782, 342, 98, 80, 74},
				{2852, 351, 99, 82, 76},
				{2946, 365, 102, 84, 77},
				{3053, 380, 105, 86, 79},
				{3173, 402, 108, 89, 80},
				{3307, 425, 114, 92, 83},
				{3464, 449, 116, 92, 82},
				{3664, 462, 110, 86, 78},
				{3929, 494, 111, 88, 80},
				{4356, 563, 121, 95, 87},
				{4356, 563, 121, 95, 87},
	}
};
#endif

#if  defined(CONFIG_MACH_SERRANO_KOR_LTE)
static struct sf_lut rbatt_sf_dummy = {
	.rows		= 30,
	.cols		= 5,
	.row_entries		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40,
		35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf		= {
				{100, 100, 100, 80, 72},
				{100, 100, 100, 80, 72},
				{101, 101, 101, 82, 73},
				{105, 105, 105, 83, 74},
				{108, 108, 108, 86, 77},
				{116, 116, 116, 89, 79},
				{116, 116, 116, 91, 82},
				{127, 127, 127, 97, 84},
				{129, 129, 129, 103, 88},
				{113, 113, 113, 101, 89},
				{99, 99, 99, 80, 74},
				{99, 99, 99, 82, 75},
				{101, 101, 101, 85, 78},
				{104, 104, 104, 88, 81},
				{107, 107, 107, 86, 82},
				{110, 110, 110, 85, 74},
				{108, 108, 108, 85, 75},
				{106, 106, 106, 84, 76},
				{100, 100, 100, 81, 74},
				{98, 98, 98, 80, 74},
				{99, 99, 99, 82, 76},
				{102, 102, 102, 84, 77},
				{105, 105, 105, 86, 79},
				{108, 108, 108, 89, 80},
				{114, 114, 114, 92, 83},
				{116, 116, 116, 92, 82},
				{110, 110, 110, 86, 78},
				{111, 111, 111, 88, 80},
				{121, 121, 121, 95, 87},
				{121, 121, 121, 95, 87},
	}
};
#endif
#if defined(CONFIG_MACH_SERRANO_DV_LTE)
static struct pc_temp_ocv_lut pc_temp_ocv = {
	.rows		= 31,
	.cols		= 5,
	.temp		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv		= {
				{4333, 4329, 4324, 4318, 4310},
				{4248, 4255, 4254, 4251, 4245},
				{4177, 4193, 4194, 4192, 4186},
				{4108, 4135, 4137, 4135, 4130},
				{4045, 4078, 4084, 4082, 4077},
				{3988, 4021, 4034, 4033, 4027},
				{3939, 3967, 3989, 3988, 3983},
				{3896, 3921, 3949, 3948, 3944},
				{3859, 3883, 3908, 3912, 3908},
				{3827, 3852, 3857, 3860, 3858},
				{3798, 3826, 3827, 3827, 3825},
				{3778, 3804, 3805, 3805, 3802},
				{3764, 3786, 3788, 3788, 3785},
				{3750, 3771, 3774, 3773, 3771},
				{3737, 3761, 3765, 3761, 3755},
				{3721, 3749, 3755, 3747, 3734},
				{3701, 3725, 3735, 3725, 3711},
				{3680, 3703, 3706, 3697, 3683},
				{3661, 3690, 3679, 3671, 3660},
				{3644, 3681, 3670, 3663, 3651},
				{3634, 3676, 3668, 3661, 3649},
				{3623, 3671, 3665, 3658, 3646},
				{3610, 3666, 3662, 3655, 3644},
				{3593, 3659, 3658, 3651, 3640},
				{3573, 3649, 3652, 3646, 3633},
				{3547, 3632, 3641, 3632, 3614},
				{3512, 3599, 3609, 3598, 3570},
				{3463, 3545, 3552, 3540, 3509},
				{3387, 3463, 3473, 3461, 3426},
				{3238, 3332, 3360, 3349, 3306},
				{3000, 3000, 3000, 3000, 3000}
	}
};
#else
static struct pc_temp_ocv_lut pc_temp_ocv = {
	.rows		= 31,
	.cols		= 5,
	.temp		= {-20, 0, 25, 40, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40,
		35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv		= {
				{4340, 4339, 4335, 4330, 4323},
				{4229, 4261, 4265, 4266, 4260},
				{4159, 4203, 4208, 4208, 4203},
				{4105, 4150, 4153, 4153, 4149},
				{4051, 4099, 4101, 4101, 4097},
				{3969, 4056, 4057, 4051, 4048},
				{3917, 3975, 3994, 3999, 4003},
				{3874, 3928, 3962, 3965, 3962},
				{3843, 3895, 3925, 3927, 3925},
				{3823, 3860, 3877, 3885, 3884},
				{3810, 3832, 3838, 3840, 3839},
				{3798, 3808, 3815, 3816, 3816},
				{3786, 3791, 3796, 3798, 3797},
				{3773, 3780, 3782, 3782, 3781},
				{3758, 3771, 3771, 3768, 3765},
				{3740, 3759, 3762, 3754, 3741},
				{3720, 3740, 3744, 3736, 3722},
				{3704, 3715, 3719, 3712, 3700},
				{3692, 3699, 3692, 3685, 3675},
				{3683, 3693, 3687, 3680, 3668},
				{3678, 3690, 3686, 3679, 3668},
				{3671, 3688, 3685, 3678, 3667},
				{3663, 3686, 3684, 3677, 3666},
				{3651, 3683, 3682, 3676, 3665},
				{3634, 3679, 3680, 3673, 3661},
				{3609, 3669, 3672, 3663, 3648},
				{3575, 3638, 3638, 3628, 3612},
				{3529, 3585, 3580, 3571, 3556},
				{3463, 3508, 3501, 3493, 3480},
				{3351, 3388, 3380, 3377, 3365},
				{3000, 3000, 3000, 3000, 3000}
	}
};
#endif

struct bms_battery_data Samsung_8930_Serrano_1900mAh_data = {
#if defined(CONFIG_MACH_SERRANO_DV_LTE)
	.fcc				= 2100,
#else
	.fcc				= 1900,
#endif
	.fcc_temp_lut		= &fcc_temp,
	.fcc_sf_lut			= &fcc_sf,
	.pc_temp_ocv_lut	= &pc_temp_ocv,
	.rbatt_sf_lut		= &rbatt_sf,
#if  defined(CONFIG_MACH_SERRANO_KOR_LTE)
	.rbatt_sf_lut_dummy		= &rbatt_sf_dummy,
#endif
#if defined(CONFIG_MACH_SERRANO_DV_LTE)
	.default_rbatt_mohm		= 159,
#else
	.default_rbatt_mohm		= 167,
#endif
#if !defined(CONFIG_MACH_SERRANO_DV_LTE)
	.rbatt_capacitive_mohm	= 160,
#endif
};
