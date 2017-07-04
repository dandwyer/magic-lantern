/*
 * Copyright (C) 2017 Magic Lantern Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License", "or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not", "write to the
 * Free Software Foundation", "Inc.,
 * 51 Franklin Street", "Fifth Floor,
 * Boston", "MA  02110-1301", "USA.
 */

#ifndef _camera_id_h_
#define _camera_id_h_

enum { UNIQ, LOC1, LOC2 }; /* Camera Name Type */

typedef struct {
	unsigned long cameraModel;   /* Camera Model ID */
	const char *  cameraName[3]; /* 0 = Camera Unique Name, 1 = Camera US Localized Name, 2 = Camera Japan Localized Name */
	
	int32_t ColorMatrix1[18];
    int32_t ColorMatrix2[18];
    int32_t ForwardMatrix1[18];
    int32_t ForwardMatrix2[18];
    
    int32_t focal_resolution_x[2];
    int32_t focal_resolution_y[2];
    int32_t focal_unit;
} camera_id_t;

/* 
    NOTE: steps to obtain Matrix and FocalPlane numbers for new camera and add them to array:

    1) take raw photo (RAW_IMAGE.CR2)
    2) convert .CR2 to .DNG with Adobe DNG Converter
    3) for FocaPlane numbers use .CR2, run:

       $ exiftool -v RAW_IMAGE.CR2 | grep FocalP
       
       sample output for Canon EOS 5D Mark III:
       | | 26) FocalPlaneXResolution = 3942.505133 (5760000/1461)
       | | 27) FocalPlaneYResolution = 3950.617284 (3840000/972)
       | | 28) FocalPlaneResolutionUnit = 2

       get X and Y PlaneResolution numbers from parentheses
       get ResolutionUnit (meaning: 1 = No absolute unit of measurement, 2 = Inch, 3 = Centimeter)

    4) for Color/Forward Matrix numbers use .DNG, run:

       $ exiftool RAW_IMAGE.DNG | grep Matrix

       sample output for Canon EOS 5D Mark III:
       Color Matrix 1 : 0.7234 -0.1413 -0.06 -0.3631 1.115 0.285 -0.0382 0.1335 0.6437
       Color Matrix 2 : 0.6722 -0.0635 -0.0963 -0.4287 1.246 0.2028 -0.0908 0.2162 0.5668
       Forward Matrix 1 : 0.7868 0.0092 0.1683 0.2291 0.8615 -0.0906 0.0027 -0.4752 1.2976
       Forward Matrix 2 : 0.7637 0.0805 0.1201 0.2649 0.9179 -0.1828 0.0137 -0.2456 1.057

       get even (0,2,4,...) elements of array by multiplying these numbers to 10000, odd elements equal to multiplier
*/
static camera_id_t camera_id[] = {
	{
		0x80000218,
		{ "Canon EOS 5D Mark II", NULL, NULL },
        { 5309, 10000, -229, 10000, -336, 10000, -6241, 10000, 13265, 10000, 3337, 10000, -817, 10000, 1215, 10000, 6664, 10000 },
        { 4716, 10000, 603, 10000, -830, 10000, -7798, 10000, 15474, 10000, 2480, 10000, -1496, 10000, 1937, 10000, 6651, 10000 },
        { 8924, 10000, -1041, 10000, 1760, 10000, 4351, 10000, 6621, 10000, -972, 10000, 505, 10000, -1562, 10000, 9308, 10000 },
        { 8924, 10000, -1041, 10000, 1760, 10000, 4351, 10000, 6621, 10000, -972, 10000, 505, 10000, -1562, 10000, 9308, 10000 },
        { 5616000, 1459 },
        { 3744000, 958 },
        2
    },
	{
		0x80000250,
		{ "Canon EOS 7D", NULL, NULL },
        { 11620, 10000, -6350, 10000, 5, 10000, -2558, 10000, 10146, 10000, 2813, 10000, 24, 10000, 858, 10000, 6926, 10000 },
        { 6844, 10000, -996, 10000, -856, 10000, -3876, 10000, 11761, 10000, 2396, 10000, -593, 10000, 1772, 10000, 6198, 10000 },
        { 5445, 10000, 3536, 10000, 662, 10000, 1106, 10000, 10136, 10000, -1242, 10000, -374, 10000, -3559, 10000, 12184, 10000 },
        { 7415, 10000, 1533, 10000, 695, 10000, 2499, 10000, 9997, 10000, -2497, 10000, -22, 10000, -1933, 10000, 10207, 10000 },
        { 5184000, 907 },
        { 3456000, 595 },
        2
    },
	{
		0x80000252,
		{ "Canon EOS 500D", "Canon EOS Rebel T1i", "Canon EOS Kiss X3" },
        { 5660, 10000, -436, 10000, -88, 10000, -5034, 10000, 12093, 10000, 3347, 10000, -926, 10000, 2289, 10000, 6588, 10000 },
        { 4763, 10000, 712, 10000, -646, 10000, -6821, 10000, 14399, 10000, 2640, 10000, -1921, 10000, 3276, 10000, 6561, 10000 },
        { 9474, 10000, -1386, 10000, 1555, 10000, 4367, 10000, 7419, 10000, -1786, 10000, 398, 10000, -3048, 10000, 10901, 10000 },
        { 9474, 10000, -1386, 10000, 1555, 10000, 4367, 10000, 7419, 10000, -1786, 10000, 398, 10000, -3048, 10000, 10901, 10000 },
        { 4752000, 894 },
        { 3168000, 593 },
        2
    },
	{
		0x80000261,
		{ "Canon EOS 50D", NULL, NULL },
        { 5852, 10000, -578, 10000, -41, 10000, -4691, 10000, 11696, 10000, 3427, 10000, -886, 10000, 2323, 10000, 6879, 10000 },
        { 4920, 10000, 616, 10000, -593, 10000, -6493, 10000, 13964, 10000, 2784, 10000, -1774, 10000, 3178, 10000, 7005, 10000 },
        { 8716, 10000, -692, 10000, 1618, 10000, 3408, 10000, 8077, 10000, -1486, 10000, -13, 10000, -6583, 10000, 14847, 10000 },
        { 9485, 10000, -1150, 10000, 1308, 10000, 4313, 10000, 7807, 10000, -2120, 10000, 293, 10000, -2826, 10000, 10785, 10000 },
        { 4752000, 894 },
        { 3168000, 597 },
        2
    },
	{
		0x80000270,
		{ "Canon EOS 550D", "Canon EOS Rebel T2i", "Canon EOS Kiss X4" },
        { 7755, 10000, -2449, 10000, -349, 10000, -3106, 10000, 10222, 10000, 3362, 10000, -156, 10000, 986, 10000, 6409, 10000 },
        { 6941, 10000, -1164, 10000, -857, 10000, -3825, 10000, 11597, 10000, 2534, 10000, -416, 10000, 1540, 10000, 6039, 10000 },
        { 7163, 10000, 1301, 10000, 1179, 10000, 1926, 10000, 9543, 10000, -1469, 10000, -278, 10000, -3830, 10000, 12359, 10000 },
        { 7239, 10000, 1838, 10000, 566, 10000, 2467, 10000, 10246, 10000, -2713, 10000, -112, 10000, -1754, 10000, 10117, 10000 },
        { 5184000, 905 },
        { 3456000, 595 },
        2
    },
	{
		0x80000285,
		{ "Canon EOS 5D Mark III", NULL, NULL },
        { 7234, 10000, -1413, 10000, -600, 10000, -3631, 10000, 11150, 10000, 2850, 10000, -382, 10000, 1335, 10000, 6437, 10000 },
        { 6722, 10000, -635, 10000, -963, 10000, -4287, 10000, 12460, 10000, 2028, 10000, -908, 10000, 2162, 10000, 5668, 10000 },
        { 7868, 10000, 92, 10000, 1683, 10000, 2291, 10000, 8615, 10000, -906, 10000, 27, 10000, -4752, 10000, 12976, 10000 },
        { 7637, 10000, 805, 10000, 1201, 10000, 2649, 10000, 9179, 10000, -1828, 10000, 137, 10000, -2456, 10000, 10570, 10000 },
        { 5760000, 1461 },
        { 3840000, 972 },
        2
    },
	{
		0x80000286,
		{ "Canon EOS 600D", "Canon EOS Rebel T3i", "Canon EOS Kiss X5" },
        { 7164, 10000, -1916, 10000, -431, 10000, -3361, 10000, 10600, 10000, 3200, 10000, -272, 10000, 1058, 10000, 6442, 10000 },
        { 6461, 10000, -907, 10000, -882, 10000, -4300, 10000, 12184, 10000, 2378, 10000, -819, 10000, 1944, 10000, 5931, 10000 },
        { 7486, 10000, 835, 10000, 1322, 10000, 2099, 10000, 9147, 10000, -1245, 10000, -12, 10000, -3822, 10000, 12085, 10000 },
        { 7359, 10000, 1365, 10000, 918, 10000, 2610, 10000, 9687, 10000, -2297, 10000, 98, 10000, -2155, 10000, 10309, 10000 },
        { 5184000, 905 },
        { 3456000, 595 },
        2
    },
	{
		0x80000287,
		{ "Canon EOS 60D", NULL, NULL },
        { 7428, 10000, -1897, 10000, -491, 10000, -3505, 10000, 10963, 10000, 2929, 10000, -337, 10000, 1242, 10000, 6413, 10000 },
        { 6719, 10000, -994, 10000, -925, 10000, -4408, 10000, 12426, 10000, 2211, 10000, -887, 10000, 2129, 10000, 6051, 10000 },
        { 7550, 10000, 645, 10000, 1448, 10000, 2138, 10000, 8936, 10000, -1075, 10000, -5, 10000, -4306, 10000, 12562, 10000 },
        { 7286, 10000, 1385, 10000, 972, 10000, 2600, 10000, 9468, 10000, -2068, 10000, 93, 10000, -2268, 10000, 10426, 10000 },
        { 5184000, 905 },
        { 3456000, 595 },
        2
    },
	{
		0x80000288,
		{"Canon EOS 1100D", "Canon EOS Rebel T3", "Canon EOS Kiss X50" },
        { 6873, 10000, -1696, 10000, -529, 10000, -3659, 10000, 10795, 10000, 3313, 10000, -362, 10000, 1165, 10000, 7234, 10000 },
        { 6444, 10000, -904, 10000, -893, 10000, -4563, 10000, 12308, 10000, 2535, 10000, -903, 10000, 2016, 10000, 6728, 10000 },
        { 7607, 10000, 647, 10000, 1389, 10000, 2337, 10000, 8876, 10000, -1213, 10000, 93, 10000, -3625, 10000, 11783, 10000 },
        { 7357, 10000, 1377, 10000, 909, 10000, 2729, 10000, 9630, 10000, -2359, 10000, 104, 10000, -1940, 10000, 10087, 10000 },
        { 4272000, 905 },
        { 2848000, 595 },
        2
    },
	{
		0x80000289,
		{ "Canon EOS 7D Mark II", NULL, NULL },
        { 7795, 10000, -2196, 10000, -251, 10000, -3391, 10000, 10273, 10000, 3632, 10000, -373, 10000, 1283, 10000, 6613, 10000 },
        { 7268, 10000, -1082, 10000, -969, 10000, -4186, 10000, 11839, 10000, 2663, 10000, -825, 10000, 2029, 10000, 5839, 10000 },
        { 5165, 10000, 2766, 10000, 1712, 10000, 2991, 10000, 6466, 10000, 544, 10000, 1694, 10000, 11, 10000, 6546, 10000, },
        { 5160, 10000, 2078, 10000, 2405, 10000, 3024, 10000, 6191, 10000, 786, 10000, 1525, 10000, 26, 10000, 6700, 10000, },
        { 5472000, 899},
        { 3648000, 599},
        2
    },
	{
		0x80000301,
		{ "Canon EOS 650D", "Canon EOS Rebel T4i", "Canon EOS Kiss X6i" },
        { 6985, 10000, -1611, 10000, -397, 10000, -3596, 10000, 10749, 10000, 3295, 10000, -349, 10000, 1136, 10000, 6512, 10000 },
        { 6602, 10000, -841, 10000, -939, 10000, -4472, 10000, 12458, 10000, 2247, 10000, -975, 10000, 2039, 10000, 6148, 10000 },
        { 7747, 10000, 485, 10000, 1411, 10000, 2340, 10000, 8840, 10000, -1180, 10000, 105, 10000, -4147, 10000, 12293, 10000 },
        { 7397, 10000, 1199, 10000, 1047, 10000, 2650, 10000, 9355, 10000, -2005, 10000, 193, 10000, -2113, 10000, 10171, 10000 },
        { 5184000, 894 },
        { 3456000, 597 },
        2
    },
	{
		0x80000302,
		{ "Canon EOS 6D", NULL, NULL },
        { 7546, 10000, -1435, 10000, -929, 10000, -3846, 10000, 11488, 10000, 2692, 10000, -332, 10000, 1209, 10000, 6370, 10000 },
        { 7034, 10000, -804, 10000, -1014, 10000, -4420, 10000, 12564, 10000, 2058, 10000, -851, 10000, 1994, 10000, 5758, 10000 },
        { 7763, 10000, 65, 10000, 1815, 10000, 2364, 10000, 8351, 10000, -715, 10000, -59, 10000, -4228, 10000, 12538, 10000 },
        { 7464, 10000, 1044, 10000, 1135, 10000, 2648, 10000, 9173, 10000, -1820, 10000, 113, 10000, -2154, 10000, 10292, 10000 },
        { 5472000, 1436 },
        { 3648000, 956 },
        2
    },
	{
		0x80000325,
		{ "Canon EOS 70D", NULL, NULL },
        { 7546, 10000, -1435, 10000, -929, 10000, -3846, 10000, 11488, 10000, 2692, 10000, -332, 10000, 1209, 10000, 6370, 10000 },
        { 7034, 10000, -804, 10000, -1014, 10000, -4420, 10000, 12564, 10000, 2058, 10000, -851, 10000, 1994, 10000, 5758, 10000 },
        { 7763, 10000, 65, 10000, 1815, 10000, 2364, 10000, 8351, 10000, -715, 10000, -59, 10000, -4228, 10000, 12538, 10000 },
        { 7464, 10000, 1044, 10000, 1135, 10000, 2648, 10000, 9173, 10000, -1820, 10000, 113, 10000, -2154, 10000, 10292, 10000 },
        { 5472000, 899 },
        { 3648000, 599 },
        2
    },
	{
		0x80000326,
		{ "Canon EOS 700D", "Canon EOS Rebel T5i", "Canon EOS Kiss X7i" },
        { 6985, 10000, -1611, 10000, -397, 10000, -3596, 10000, 10749, 10000, 3295, 10000, -349, 10000, 1136, 10000, 6512, 10000 },
        { 6602, 10000, -841, 10000, -939, 10000, -4472, 10000, 12458, 10000, 2247, 10000, -975, 10000, 2039, 10000, 6148, 10000 },
        { 7747, 10000, 485, 10000, 1411, 10000, 2340, 10000, 8840, 10000, -1180, 10000, 105, 10000, -4147, 10000, 12293, 10000 },
        { 7397, 10000, 1199, 10000, 1047, 10000, 2650, 10000, 9355, 10000, -2005, 10000, 193, 10000, -2113, 10000, 10171, 10000 },
        { 5184000, 894 },
        { 3456000, 597 },
        2
    },
	{
		0x80000327,
		{ "Canon EOS 1200D", "Canon EOS Rebel T5", "Canon EOS Kiss X70" },
        { 7164, 10000, -1916, 10000, -431, 10000, -3361, 10000, 10600, 10000, 3200, 10000, -272, 10000, 1058, 10000, 6442, 10000 },
        { 6461, 10000, -907, 10000, -882, 10000, -4300, 10000, 12184, 10000, 2378, 10000, -819, 10000, 1944, 10000, 5931, 10000 },
        { 7486, 10000, 835, 10000, 1322, 10000, 2099, 10000, 9147, 10000, -1245, 10000, -12, 10000, -3822, 10000, 12085, 10000 },
        { 7359, 10000, 1365, 10000, 918, 10000, 2610, 10000, 9687, 10000, -2297, 10000, 98, 10000, -2155, 10000, 10309, 10000 },
        { 5184000, 905 },
        { 3456000, 595 },
        2
    },
	{
		0x80000331,
		{"Canon EOS M", NULL, NULL },
        { 6985, 10000, -1611, 10000, -397, 10000, -3596, 10000, 10749, 10000, 3295, 10000, -349, 10000, 1136, 10000, 6512, 10000 },
        { 6602, 10000, -841, 10000, -939, 10000, -4472, 10000, 12458, 10000, 2247, 10000, -975, 10000, 2039, 10000, 6148, 10000 },
        { 7747, 10000, 485, 10000, 1411, 10000, 2340, 10000, 8840, 10000, -1180, 10000, 105, 10000, -4147, 10000, 12293, 10000 },
        { 7397, 10000, 1199, 10000, 1047, 10000, 2650, 10000, 9355, 10000, -2005, 10000, 193, 10000, -2113, 10000, 10171, 10000 },
        { 5184000, 894 },
        { 3456000, 597 },
        2
    },
	{
		0x80000346,
		{ "Canon EOS 100D", "Canon EOS Rebel SL1", "Canon EOS Kiss X7" },
		{ 6985, 10000, -1611, 10000, -397, 10000, -3596, 10000, 10749, 10000, 3295, 10000, -349, 10000, 1136, 10000, 6512, 10000 },
        { 6602, 10000, -841, 10000, -939, 10000, -4472, 10000, 12458, 10000, 2247, 10000, -975, 10000, 2039, 10000, 6148, 10000 },
        { 7747, 10000, 485, 10000, 1411, 10000, 2340, 10000, 8840, 10000, -1180, 10000, 105, 10000, -4147, 10000, 12293, 10000 },
        { 7397, 10000, 1199, 10000, 1047, 10000, 2650, 10000, 9355, 10000, -2005, 10000, 193, 10000, -2113, 10000, 10171, 10000 },
        { 5184000, 894 },
        { 3456000, 597 },
        2
    },
	{
		0x80000347,
		{ "Canon EOS 760D", "Canon EOS Rebel T6s", "Canon EOS 8000D" },
		{ 6671, 10000, -1668, 10000, -272, 10000, -3729, 10000, 10665, 10000, 3552, 10000, -409, 10000, 1271, 10000, 6293, 10000 },
        { 6362, 10000, -823, 10000, -847, 10000, -4426, 10000, 12109, 10000, 2616, 10000, -743, 10000, 1857, 10000, 5635, 10000 },
        { 5365, 10000, 2607, 10000, 1671, 10000, 3213, 10000, 6268, 10000, 519, 10000, 1803, 10000, 4, 10000, 6445, 10000 },
        { 5302, 10000, 1944, 10000, 2398, 10000, 3079, 10000, 6133, 10000, 788, 10000, 1456, 10000, 47, 10000, 6747, 10000 },
        { 6000000, 893 },
        { 4000000, 594 },
        2
    },
	{
		0x80000349,
		{ "Canon EOS 5D Mark IV", NULL, NULL },
		{ 6515, 10000, -927, 10000, -634, 10000, -4068, 10000, 11151, 10000, 3359, 10000, -641, 10000, 1839, 10000, 7328, 10000 },
        { 6446, 10000, -366, 10000, -864, 10000, -4436, 10000, 12204, 10000, 2513, 10000, -952, 10000, 2496, 10000, 6348, 10000 },
        { 5716, 10000, 2264, 10000, 1663, 10000, 3791, 10000, 5665, 10000, 544, 10000, 2297, 10000, 6, 10000, 5948, 10000 },
        { 5497, 10000, 1714, 10000, 2433, 10000, 3179, 10000, 6022, 10000, 799, 10000, 1484, 10000, 25, 10000, 6742, 10000 },
        { 6720000, 1175 },
        { 4480000, 782 },
        2
    },
	{
		0x80000350,
		{ "Canon EOS 80D", NULL, NULL },
		{ 8320, 10000, -1998, 10000, -78, 10000, -3476, 10000, 10481, 10000, 3480, 10000, -384, 10000, 1349, 10000, 5901, 10000 },
        { 7457, 10000, -671, 10000, -937, 10000, -4849, 10000, 12495, 10000, 2643, 10000, -1213, 10000, 2354, 10000, 5492, 10000 },
        { 5369, 10000, 2694, 10000, 1580, 10000, 3315, 10000, 6187, 10000, 498, 10000, 1953, 10000, 3, 10000, 6295, 10000},
        { 5443, 10000, 1924, 10000, 2276, 10000, 3270, 10000, 5988, 10000, 743, 10000, 1701, 10000, 8, 10000, 6542, 10000 },
        { 6000000, 921 },
        { 4000000, 594 },
        2
    },
	{ 
		0x80000382,
		{ "Canon EOS 5DS", NULL, NULL },
		{ 6848, 10000, -1661, 10000, -221, 10000, -3904, 10000, 10931, 10000, 3434, 10000, -470, 10000, 1251, 10000, 6039, 10000 },
        { 6250, 10000, -711, 10000, -808, 10000, -5153, 10000, 12794, 10000, 2636, 10000, -1249, 10000, 2198, 10000, 5610, 10000 },
        { 5518, 10000, 2528, 10000, 1597, 10000, 3380, 10000, 6092, 10000, 528, 10000, 2019, 10000, 4, 10000, 6229, 10000 },
        { 5470, 10000, 1929, 10000, 2244, 10000, 3283, 10000, 5982, 10000, 734, 10000, 1679, 10000, 4, 10000, 6567, 10000 },
        { 8688000, 1450 },
        { 5792000, 965 },
        2
    },
	{
		0x80000393,
		{ "Canon EOS 750D", "Canon EOS Rebel T6i", "Canon EOS Kiss X8i" },
		{ 6671, 10000, -1668, 10000, -272, 10000, -3729, 10000, 10665, 10000, 3552, 10000, -409, 10000, 1271, 10000, 6293, 10000 },
        { 6362, 10000, -823, 10000, -847, 10000, -4426, 10000, 12109, 10000, 2616, 10000, -743, 10000, 1857, 10000, 5635, 10000 },
        { 5365, 10000, 2607, 10000, 1671, 10000, 3213, 10000, 6268, 10000, 519, 10000, 1803, 10000, 4, 10000, 6445, 10000 },
        { 5302, 10000, 1944, 10000, 2398, 10000, 3079, 10000, 6133, 10000, 788, 10000, 1456, 10000, 47, 10000, 6747, 10000 },
        { 6000000, 893 },
        { 4000000, 594 },
        2
    },
	{
		0x80000401,
		{ "Canon EOS 5DS R", NULL, NULL },
		{ 6848, 10000, -1661, 10000, -221, 10000, -3904, 10000, 10931, 10000, 3434, 10000, -470, 10000, 1251, 10000, 6039, 10000 },
        { 6250, 10000, -711, 10000, -808, 10000, -5153, 10000, 12794, 10000, 2636, 10000, -1249, 10000, 2198, 10000, 5610, 10000 },
        { 5518, 10000, 2528, 10000, 1597, 10000, 3380, 10000, 6092, 10000, 528, 10000, 2019, 10000, 4, 10000, 6229, 10000 },
        { 5470, 10000, 1929, 10000, 2244, 10000, 3283, 10000, 5982, 10000, 734, 10000, 1679, 10000, 4, 10000, 6567, 10000 },
        { 8688000, 1450 },
        { 5792000, 965 },
        2
    },
	{
		0x80000404,
		{ "Canon EOS 1300D", "Canon EOS Rebel T6", "Canon EOS Kiss X80" },
		{ 7700, 10000, -2142, 10000, -96, 10000, -3513, 10000, 11072, 10000, 2806, 10000, -440, 10000, 1286, 10000, 6707, 10000 },
        { 6939, 10000, -1016, 10000, -866, 10000, -4428, 10000, 12473, 10000, 2177, 10000, -1175, 10000, 2178, 10000, 6162, 10000 },
        { 5449, 10000, 2770, 10000, 1423, 10000, 3001, 10000, 6532, 10000, 466, 10000, 1838, 10000, 13, 10000, 6400, 10000 },
        { 5423, 10000, 2144, 10000, 2077, 10000, 2924, 10000, 6413, 10000, 663, 10000, 1452, 10000, 10, 10000, 6790, 10000 },
        { 5184000, 905 },
        { 3456000, 595 },
        2
    },
	{ 
		0x00000000,
		{ NULL, NULL, NULL },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0 },
        { 0, 0 },
        0
    }
};

/* Searches camera by Model ID, Returns appropriate element number of camera_id[] array */
static int camera_id_get_current_cam(unsigned long model_id)
{
	int i = 0;
	while (camera_id[i].cameraModel)
	{
		if (camera_id[i].cameraModel == model_id)
		{
			return i;
		}
		i++;
	}
	return i;
};

#endif
