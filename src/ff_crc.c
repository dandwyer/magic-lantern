/*****************************************************************************
 *     FullFAT - High Performance, Thread-Safe Embedded FAT File-System      *
 *                                                                           *
 *        Copyright(C) 2009  James Walmsley  <james@fullfat-fs.co.uk>        *
 *        Copyright(C) 2011  Hein Tibosch    <hein_tibosch@yahoo.es>         *
 *                                                                           *
 *    See RESTRICTIONS.TXT for extra restrictions on the use of FullFAT.     *
 *                                                                           *
 *    WARNING : COMMERCIAL PROJECTS MUST COMPLY WITH THE GNU GPL LICENSE.    *
 *                                                                           *
 *  Projects that cannot comply with the GNU GPL terms are legally obliged   *
 *    to seek alternative licensing. Contact James Walmsley for details.     *
 *                                                                           *
 *****************************************************************************
 *           See http://www.fullfat-fs.co.uk/ for more information.          *
 *****************************************************************************
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation, either version 3 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 *  The Copyright of Hein Tibosch on this project recognises his efforts in  *
 *  contributing to this project. The right to license the project under     *
 *  any other terms (other than the GNU GPL license) remains with the        *
 *  original copyright holder (James Walmsley) only.                         *
 *                                                                           *
 *****************************************************************************
 *  Modification/Extensions/Bugfixes/Improvements to FullFAT must be sent to *
 *  James Walmsley for integration into the main development branch.         *
 *****************************************************************************/

/**
 *	@file		ff_crc.c
 *	@author		James Walmsley
 *	@ingroup	CRC
 *
 *	@defgroup	CRC CRC Checksums for Strings
 *	@brief		Provides fast hashing functions.
 *
 **/

#include "ff_crc.h"


/*static*/ const FF_T_UINT32 crc32_table[256] = {
	0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 
    0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 
    0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2, 
    0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 
    0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 
    0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C, 
    0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 
    0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 
    0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106, 
    0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433, 
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 
    0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 
    0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950, 
    0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 
    0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 
    0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA, 
    0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F, 
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 
    0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 
    0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84, 
    0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, 
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 
    0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 
    0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E, 
    0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, 
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 
    0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28, 
    0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, 
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 
    0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 
    0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242, 
    0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, 
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 
    0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 
    0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC, 
    0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9, 
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 
    0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 
    0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

FF_T_UINT32 FF_GetCRC32(FF_T_UINT8 *pbyData, FF_T_UINT32 stLength) {
	
	register FF_T_UINT32 crc = 0xFFFFFFFF;
	
	while(stLength--) {
		crc = ((crc >> 8) & 0x00FFFFFF) ^ crc32_table[(crc^*pbyData++) & 0x000000FF];
	}

	return (crc ^ 0xFFFFFFFF);
}




static const FF_T_UINT8 crc16_table_low[256] = 
{
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040, 
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x000, 0x0c1, 0x081, 0x040, 0x001, 0x0c0, 0x080, 0x041,
    0x001, 0x0c0, 0x080, 0x041, 0x000, 0x0c1, 0x081, 0x040,
};

static const FF_T_UINT8 crc16_table_high[256] = 
{
    0x000, 0x0c0, 0x0c1, 0x001, 0x0c3, 0x003, 0x002, 0x0c2,
    0x0c6, 0x006, 0x007, 0x0c7, 0x005, 0x0c5, 0x0c4, 0x004,
    0x0cc, 0x00c, 0x00d, 0x0cd, 0x00f, 0x0cf, 0x0ce, 0x00e,
    0x00a, 0x0ca, 0x0cb, 0x00b, 0x0c9, 0x009, 0x008, 0x0c8,
    0x0d8, 0x018, 0x019, 0x0d9, 0x01b, 0x0db, 0x0da, 0x01a,
    0x01e, 0x0de, 0x0df, 0x01f, 0x0dd, 0x01d, 0x01c, 0x0dc,
    0x014, 0x0d4, 0x0d5, 0x015, 0x0d7, 0x017, 0x016, 0x0d6,
    0x0d2, 0x012, 0x013, 0x0d3, 0x011, 0x0d1, 0x0d0, 0x010,
    0x0f0, 0x030, 0x031, 0x0f1, 0x033, 0x0f3, 0x0f2, 0x032,
    0x036, 0x0f6, 0x0f7, 0x037, 0x0f5, 0x035, 0x034, 0x0f4,
    0x03c, 0x0fc, 0x0fd, 0x03d, 0x0ff, 0x03f, 0x03e, 0x0fe,
    0x0fa, 0x03a, 0x03b, 0x0fb, 0x039, 0x0f9, 0x0f8, 0x038,
    0x028, 0x0e8, 0x0e9, 0x029, 0x0eb, 0x02b, 0x02a, 0x0ea,
    0x0ee, 0x02e, 0x02f, 0x0ef, 0x02d, 0x0ed, 0x0ec, 0x02c,
    0x0e4, 0x024, 0x025, 0x0e5, 0x027, 0x0e7, 0x0e6, 0x026,
    0x022, 0x0e2, 0x0e3, 0x023, 0x0e1, 0x021, 0x020, 0x0e0,
    0x0a0, 0x060, 0x061, 0x0a1, 0x063, 0x0a3, 0x0a2, 0x062,
    0x066, 0x0a6, 0x0a7, 0x067, 0x0a5, 0x065, 0x064, 0x0a4,
    0x06c, 0x0ac, 0x0ad, 0x06d, 0x0af, 0x06f, 0x06e, 0x0ae,
    0x0aa, 0x06a, 0x06b, 0x0ab, 0x069, 0x0a9, 0x0a8, 0x068,
    0x078, 0x0b8, 0x0b9, 0x079, 0x0bb, 0x07b, 0x07a, 0x0ba,
    0x0be, 0x07e, 0x07f, 0x0bf, 0x07d, 0x0bd, 0x0bc, 0x07c,
    0x0b4, 0x074, 0x075, 0x0b5, 0x077, 0x0b7, 0x0b6, 0x076,
    0x072, 0x0b2, 0x0b3, 0x073, 0x0b1, 0x071, 0x070, 0x0b0,
    0x050, 0x090, 0x091, 0x051, 0x093, 0x053, 0x052, 0x092,
    0x096, 0x056, 0x057, 0x097, 0x055, 0x095, 0x094, 0x054,
    0x09c, 0x05c, 0x05d, 0x09d, 0x05f, 0x09f, 0x09e, 0x05e,
    0x05a, 0x09a, 0x09b, 0x05b, 0x099, 0x059, 0x058, 0x098,
    0x088, 0x048, 0x049, 0x089, 0x04b, 0x08b, 0x08a, 0x04a,
    0x04e, 0x08e, 0x08f, 0x04f, 0x08d, 0x04d, 0x04c, 0x08c,
    0x044, 0x084, 0x085, 0x045, 0x087, 0x047, 0x046, 0x086,
    0x082, 0x042, 0x043, 0x083, 0x041, 0x081, 0x080, 0x040,
};

/*****************************************************************************
 * Description: Function to 16 bit CRC check a block of memory

 *
 * Parameters:  pbyData - Pointer to the source data
 *              stLength - The length to CRC
 *
 * Return value: The 16 bit CRC value
 *
 *****************************************************************************/

FF_T_UINT16 FF_GetCRC16(FF_T_UINT8 *pbyData, FF_T_UINT32 stLength) {
    FF_T_UINT8	bTableValue;
    FF_T_UINT16 wCRC = 0;

    while (stLength--)    {
        bTableValue = (FF_T_UINT8)((wCRC & 0x00FF) ^ *pbyData++);
        wCRC = (FF_T_UINT16)(((crc16_table_high[bTableValue]) << 8)
             + (crc16_table_low[bTableValue] ^ ((wCRC >> 8) & 0x00FF)));
    }

    return wCRC;
}


static const FF_T_UINT8 crc8_table[256] =
{
    0,   94,  188, 226, 97,  63,  221, 131, 
    194, 156, 126, 32,  163, 253, 31,  65,
    157, 195, 33,  127, 252, 162, 64,  30,
    95,  1,   227, 189, 62,  96,  130, 220,
    35,  125, 159, 193, 66,  28,  254, 160,
    225, 191, 93,  3,   128, 222, 60,  98,
    190, 224, 2,   92,  223, 129, 99,  61,
    124, 34,  192, 158, 29,  67,  161, 255,
    70,  24,  250, 164, 39,  121, 155, 197,
    132, 218, 56,  102, 229, 187, 89,  7,
    219, 133, 103, 57,  186, 228, 6,   88,
    25,  71,  165, 251, 120, 38,  196, 154,
    101, 59,  217, 135, 4,   90,  184, 230,
    167, 249, 27,  69,  198, 152, 122, 36,
    248, 166, 68,  26,  153, 199, 37,  123,
    58,  100, 134, 216, 91,  5,   231, 185,
    140, 210, 48,  110, 237, 179, 81,  15, 
    78,  16,  242, 172, 47,  113, 147, 205,
    17,  79,  173, 243, 112, 46,  204, 146,
    211, 141, 111, 49,  178, 236, 14,  80,
    175, 241, 19,  77,  206, 144, 114, 44,
    109, 51,  209, 143, 12,  82,  176, 238,
    50,  108, 142, 208, 83,  13,  239, 177,
    240, 174, 76,  18,  145, 207, 45,  115,
    202, 148, 118, 40,  171, 245, 23,  73, 
    8,   86,  180, 234, 105, 55,  213, 139,
    87,  9,   235, 181, 54,  104, 138, 212,
    149, 203, 41,  119, 244, 170, 72,  22,
    233, 183, 85,  11,  136, 214, 52,  106,
    43,  117, 151, 201, 74,  20,  246, 168,
    116, 42,  200, 150, 21,  75,  169, 247,
    182, 232, 10,  84,  215, 137, 107, 53
};
 
/*****************************************************************************
 * Description: Function to CRC check a block of memory
 *
 * Parameters:  pbyData - Pointer to the source data
 *              stLength - The length to CRC
 *
 * Return value: The 8 bit CRC value
 *
 *****************************************************************************/

FF_T_UINT8 FF_GetCRC8(FF_T_UINT8 *pbyData, FF_T_UINT32 stLength) {
    FF_T_UINT8 byCRC = 0, byData;
    while (stLength--) {
        byData = *pbyData++;
        byCRC = crc8_table[(byCRC ^ byData)];
    }
    return byCRC;
}
