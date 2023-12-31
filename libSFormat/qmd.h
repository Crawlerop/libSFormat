#pragma once
#include <stdlib.h>
#include <memory.h>
#include "utils.h"

/*
#include "stdio.h"
#define DEBUG_QMD 1
*/

const unsigned short apps[256] =
{
	0x0001, 0x0003, 0x0100, 0x0002, 0x0008, 0x0007, 0x0006, 0x0300,
	0x0010, 0x0004, 0x0200, 0x0009, 0x0040, 0x0018, 0x0005, 0x0020,
	0x000C, 0x000E, 0x000F, 0x000A, 0x00C0, 0x0800, 0x0700, 0x0101,
	0x0400, 0x000B, 0x0030, 0x0011, 0x0080, 0x0600, 0x000D, 0x0012,
	0x001C, 0x0500, 0x001B, 0x001E, 0x0014, 0x001A, 0x0028, 0x0038,
	0x1000, 0x001F, 0x0019, 0x0016, 0x0060, 0x2000, 0x0013, 0x001D,
	0x0103, 0x0024, 0x0017, 0x0015, 0x0102, 0x01C0, 0x0F00, 0x003C,
	0x0301, 0x0C00, 0x1800, 0x0048, 0x0021, 0x0034, 0x0E00, 0x0202,
	0x002C, 0x0070, 0x0A00, 0x0303, 0x0036, 0x0201, 0x003F, 0x0D00,
	0x0180, 0x003E, 0x3000, 0x0900, 0x0078, 0x0022, 0x0050, 0x003A,
	0x0041, 0x0107, 0x0033, 0x0106, 0x0026, 0x002A, 0x00A0, 0x0023,
	0x0029, 0x0088, 0x0044, 0x003D, 0x00E0, 0x0032, 0x002E, 0x0039,
	0x0031, 0x002D, 0x00F0, 0x0140, 0x0B00, 0x003B, 0x0058, 0x4000,
	0x0037, 0x0035, 0x0068, 0x0302, 0x007C, 0x002F, 0x0027, 0x0064,
	0x0090, 0x0074, 0x0203, 0x0104, 0x006C, 0x1100, 0x03C0, 0x00FF,
	0x0025, 0xF000, 0x1F00, 0x0701, 0x0042, 0x007F, 0x002B, 0x0105,
	0x0054, 0x1C00, 0x004C, 0x0801, 0x0043, 0x6000, 0x005C, 0x007E,
	0x00E8, 0x0108, 0x00F8, 0xE000, 0x0206, 0x1E00, 0x0380, 0x0061,
	0x007A, 0x004E, 0x0601, 0x1001, 0x00C8, 0x8000, 0x1D00, 0x00D0,
	0x0072, 0x0049, 0x1600, 0x1A00, 0x0046, 0x7000, 0x010F, 0x0110,
	0x0076, 0x1200, 0x1400, 0x0404, 0x0606, 0x010E, 0x00FC, 0x1700,
	0x006E, 0x00FE, 0x1300, 0x0062, 0x0066, 0xC000, 0x0204, 0x0306,
	0x0063, 0x0707, 0x0280, 0x0602, 0x0055, 0x0047, 0x006A, 0x010C,
	0x0052, 0x0501, 0x00D8, 0x0307, 0x0073, 0x0109, 0x0808, 0x0401,
	0x004A, 0x2020, 0x005A, 0x0702, 0x00B0, 0x0045, 0x0207, 0x0304,
	0x0402, 0x005E, 0x010A, 0x0079, 0x3800, 0x00F4, 0x1500, 0x01E0,
	0x1B00, 0x0071, 0x1010, 0x00C1, 0x00E4, 0x0502, 0x0056, 0x007D,
	0x0081, 0x0077, 0x00CC, 0x0703, 0x010D, 0x0205, 0x0340, 0x5000,
	0x0082, 0x0067, 0xFF00, 0x0120, 0x0069, 0x0098, 0x00C3, 0x1900,
	0x0065, 0x007B, 0x0240, 0x0603, 0x00EC, 0x0059, 0x00FA, 0x0403,
	0x0075, 0x006F, 0x3100, 0x3300, 0x004F, 0x00B8, 0x006D, 0x0208,
	0x004D, 0x0111, 0x0051, 0x020E, 0x00DC, 0x00C4, 0x2100, 0x00A8
};

const unsigned short rc1[256] =
{
	0x0001, 0x0002, 0x0003, 0x0800, 0x0100, 0x0004, 0x0020, 0x0008,
	0x0007, 0x0400, 0x0300, 0x0006, 0x0010, 0x0040, 0x0200, 0x000C,
	0x000E, 0x1000, 0x0801, 0x0005, 0x0101, 0x0600, 0x0700, 0x000F,
	0x1800, 0x000A, 0x0C00, 0x001C, 0x0011, 0x0080, 0x0018, 0x00C0,
	0x0500, 0xFFFF, 0x000D, 0x000B, 0x0009, 0xFF00, 0x0014, 0x4000,
	0x001F, 0x001D, 0x001E, 0x0016, 0x0E00, 0x0012, 0x0017, 0x0A00,
	0x0030, 0x0F00, 0x001A, 0x0202, 0x2000, 0x0060, 0x0015, 0x0041,
	0x0019, 0x0021, 0x001B, 0x1C00, 0x1100, 0x0303, 0x0D00, 0x0013,
	0x0900, 0x0404, 0x1400, 0x00C1, 0x3000, 0x0103, 0x2020, 0x0106,
	0x0102, 0x0B00, 0x0038, 0x1A00, 0x1E00, 0x0050, 0x003C, 0x1F00,
	0x0840, 0x1200, 0x1600, 0x0301, 0x0820, 0x0044, 0x1D00, 0x0023,
	0x3800, 0x0606, 0x0028, 0x0841, 0x00FF, 0x5000, 0x0022, 0x0110,
	0x002A, 0x0707, 0x003F, 0x0034, 0x0070, 0x0024, 0x003E, 0x1001,
	0x1500, 0x0107, 0x1300, 0x1700, 0x0104, 0x1900, 0x0802, 0x1010,
	0x0043, 0x0302, 0x0032, 0x0201, 0x003A, 0x0036, 0x0701, 0x1B00,
	0x80C0, 0x4400, 0x0505, 0x003B, 0x0026, 0x00E3, 0x0031, 0x00FA,
	0x003D, 0x0039, 0x0037, 0x0803, 0x0035, 0x002E, 0x0027, 0x00E0,
	0x00A0, 0x0061, 0x0078, 0x002C, 0x0058, 0x0033, 0x7000, 0x0203,
	0x002F, 0x2800, 0x0025, 0x0052, 0x004F, 0x0808, 0x01C0, 0x0042,
	0x1840, 0x002B, 0xF81E, 0x1111, 0x004E, 0x00D0, 0x0029, 0x0105,
	0x0111, 0x0C0C, 0x08C1, 0x0045, 0x0047, 0x0402, 0x010E, 0x0602,
	0x0068, 0x1801, 0x1101, 0x6000, 0x0E0E, 0x002D, 0x0088, 0x0601,
	0x0401, 0x7800, 0x2600, 0x0054, 0x0108, 0x1D1D, 0x1820, 0x0206,
	0x01F0, 0x00E2, 0x0048, 0x010F, 0x0E02, 0x0049, 0x2E00, 0x0082,
	0x00B0, 0x0706, 0x0880, 0x00F8, 0x3400, 0x020C, 0x1040, 0x00D8,
	0x0504, 0x0204, 0x07C0, 0x0063, 0x0821, 0x0090, 0x2400, 0x0410,
	0x0607, 0x0064, 0x0405, 0x00FE, 0x0860, 0x0F0F, 0x1803, 0x2200,
	0x0074, 0x5400, 0x08E3, 0x2A00, 0x0A0A, 0x3C00, 0x1110, 0x0D0D,
	0x0B0B, 0x0703, 0x0C02, 0x005B, 0x5200, 0x0861, 0x0604, 0x0062,
	0x3200, 0x007F, 0x007A, 0x00F0, 0x2C00, 0x004C, 0x4E00, 0x0406,
	0x5B00, 0x5B5B, 0x00C8, 0x4100, 0x010A, 0x0046, 0x3A00, 0x007C,
	0x004D, 0x0A96, 0xFFFE, 0x0304, 0x3600, 0x0501, 0x0F01, 0x3F00
};

const unsigned short* diffTable[2] = { rc1, apps }; // bada 1.2

const unsigned short diffTable2[256] = // bada 2.0
{
	0x0001, 0x0003, 0x0100, 0x0002, 0x0008, 0x0007, 0x0006, 0x0300,
	0x0010, 0x0004, 0x0200, 0x0009, 0x0040, 0x0018, 0x0005, 0x0020,
	0x000C, 0x000E, 0x000F, 0x000A, 0x00C0, 0x0800, 0x0700, 0x0400,
	0x000B, 0x0030, 0x0011, 0x0080, 0x0600, 0x000D, 0x0012, 0x001C,
	0x0500, 0x001B, 0x001E, 0x0014, 0x001A, 0x0028, 0x0038, 0x1000,
	0x001F, 0x0019, 0x0016, 0x0060, 0x2000, 0x0013, 0x001D, 0x0024,
	0x0017, 0x0015, 0x0F00, 0x003C, 0x0C00, 0x1800, 0x0048, 0x0021,
	0x0034, 0x0E00, 0x002C, 0x0070, 0x0A00, 0x0036, 0x003F, 0x0D00,
	0x003E, 0x3000, 0x0900, 0x0078, 0x0022, 0x0050, 0x003A, 0x0041,
	0x0033, 0x0026, 0x002A, 0x00A0, 0x0023, 0x0029, 0x0088, 0x0044,
	0x003D, 0x00E0, 0x0032, 0x002E, 0x0039, 0x0031, 0x002D, 0x00F0,
	0x0B00, 0x003B, 0x0058, 0x4000, 0x0037, 0x0035, 0x0068, 0x007C,
	0x002F, 0x0027, 0x0064, 0x0090, 0x0074, 0x006C, 0x1100, 0x00FF,
	0x0025, 0xF000, 0x1F00, 0x0042, 0x007F, 0x002B, 0x0054, 0x1C00,
	0x004C, 0x0043, 0x6000, 0x005C, 0x007E, 0x00E8, 0x00F8, 0xE000,
	0x1E00, 0x0061, 0x007A, 0x004E, 0x00C8, 0x8000, 0x1D00, 0x00D0,
	0x0072, 0x0049, 0x1600, 0x1A00, 0x0046, 0x7000, 0x0076, 0x1200,
	0x1400, 0x00FC, 0x1700, 0x006E, 0x00FE, 0x1300, 0x0062, 0x0066,
	0xC000, 0x0063, 0x0055, 0x0047, 0x006A, 0x0052, 0x00D8, 0x0073,
	0x004A, 0x005A, 0x00B0, 0x0045, 0x005E, 0x0079, 0x3800, 0x00F4,
	0x1500, 0x1B00, 0x0071, 0x00C1, 0x00E4, 0x0056, 0x007D, 0x0081,
	0x0077, 0x00CC, 0x5000, 0x0082, 0x0067, 0xFF00, 0x0069, 0x0098,
	0x00C3, 0x1900, 0x0065, 0x007B, 0x00EC, 0x0059, 0x00FA, 0x0075,
	0x006F, 0x3100, 0x3300, 0x004F, 0x00B8, 0x006D, 0x004D, 0x0051,
	0x00DC, 0x00C4, 0x2100, 0x00A8, 0x00EE, 0x00F6, 0x00D4, 0x00F2,
	0x00E2, 0x005F, 0x00C6, 0x00E6, 0x00A4, 0x00EA, 0x0053, 0x006B,
	0x00C2, 0x00B4, 0x00DA, 0x00DE, 0x0084, 0x00AC, 0x009C, 0x005D,
	0x00D2, 0x00D6, 0x00CE, 0x008C, 0x00BC, 0x00CA, 0x005B, 0x0094,
	0x0057, 0x004B, 0x008E, 0x00B6, 0x00A2, 0x00A6, 0x00BA, 0x00AA,
	0x00BE, 0x00B2, 0x00FD, 0x00AE, 0x00FB, 0x009A, 0x009E, 0x00F1,
	0x0086, 0x008A, 0x00F5, 0x00F3, 0x00F9, 0x0096, 0x00F7, 0x7F00,
	0x0092, 0x5F00, 0x00E1, 0x00EF, 0x00E7, 0x00E3, 0x00E9, 0x2A00
};

#define QMD_DATA                0
#define QMD_CODE                1

// =============================================================================

#define CURRENT_BIT                     ((BitsBuffer>>--BitCount)&1)
// from fmtBADA.h
#define BYTE(data,pos)                  (*(unsigned char *)((data)+(pos)))
#define HALF(data,pos)                  (*(unsigned short *)((data)+(pos)))
#define WORD(data,pos)                  (*(unsigned int *)((data)+(pos)))

#define E_FAIL			0xFFFFFFFF
#define E_OK			0

#define DECOMP_CODE1    0x503//0x0305
#define DECOMP_DATA1    0x704//0x0407
#define DECOMP_CODE2    0x204//0x0402
#define DECOMP_DATA2    0x205//0x0502

#define MAGIC_QMD       0x00444D51 // QMD
#define MAGIC_QMDC      0x43444D51 // QMDC

//#define GET_BYTE( data, pos )           ( ( (unsigned char *)( data ) )[pos] )
//#define GET_HALF( data, pos )           ( ( GET_BYTE ( data, ( ( pos ) + 1 ) ) << 8 ) | GET_BYTE ( data, ( pos ) ) )
//#define GET_WORD( data, pos )           ( ( GET_HALF ( data, ( ( pos ) + 2 ) ) << 16 ) | GET_HALF ( data, ( pos ) ) )
//#define SET_BYTE( data, pos, val )      do { ( (unsigned char *)( data ) )[pos] = val; } while ( 0 )
//#define SET_HALF( data, pos, val )      do { SET_BYTE ( data, ( pos ) + 1, ( ( val ) >> 8 ) & 0xFF ); SET_BYTE ( data, ( pos ), ( val ) & 0xFF ); } while ( 0 )
//#define SET_WORD( data, pos, val )      do { SET_HALF ( data, ( pos ) + 2, ( ( val ) >> 16 ) & 0xFFFF ); SET_HALF ( data, ( pos ), ( val ) & 0xFFFF ); } while ( 0 )

namespace QMD
{	
	// =============================================================================

	typedef struct
	{
		unsigned int type;
		unsigned int length;
		unsigned int offset;
	} t_qmd_entry;

	typedef struct
	{
		unsigned int magic;         // MAGIC_QMD
		unsigned int data_offset;   // data offset, 0x40000
		unsigned char version[4];   //
		unsigned int unk0;          // 1
		unsigned int decomp_len;    // decompressed length
		unsigned int comp_len;      // compressed length (with header)
		unsigned int unk1;          // SBZ
		unsigned int decomp_len2;   // decomp_len
		unsigned int unk2;          // SBZ
		unsigned int page_offset;   // page table offset ;)
		unsigned int page_size;     // page table length ( 0x40000 - page_offset )
		unsigned int unk3;          // 0x0F000000
		unsigned char unk4[0x10];   // 0
		unsigned int unk5;          // differ, CBZ?
		unsigned int comp_len2;     // comp_len
		unsigned int unk6;          // SBZ
		unsigned int header_size;   // 0x40000
		unsigned int header_size2;  // header_size
		unsigned int header_size2_1;  // header_size
		unsigned int page_len;      // 0x1000
		unsigned int unk7;          // SBZ
		unsigned int page_len2;     // page_len
		unsigned char unk8[0x20];   // 0
		unsigned int tab[8][4];     //
		t_qmd_entry entry[];              // (page_offset - 0x100) / sizeof(t_qmd_entry)
	} t_qmd_header;



	unsigned int decompress2(unsigned char* dst, unsigned char* src, unsigned int mode/*, BackgroundWorker ^ bwAsync*/)
	{
		unsigned int BitCount;
		unsigned int BitOperation;
		unsigned int CountWord;
		unsigned int CaseSwitch;
		unsigned int OffsetDivOn2;
		unsigned int BitsBuffer;

		unsigned int len0, blen1, blen2, pos1, pos2, pos3, outpos;
		unsigned char* block1, * block2, * block3, * out;

		len0 = WORD(src, 0);
		blen1 = WORD(src, 4);
		blen2 = WORD(src, 8);

		block1 = src + 12;
		block2 = block1 + blen1;
		block3 = block2 + blen2;

		pos1 = 0;
		pos2 = 0;
		pos3 = 0;
		out = dst;
		outpos = 0;
		BitCount = 0;
		BitOperation = 0;
		CountWord = len0 >> 4;
		CaseSwitch = 0;
		BitsBuffer = 0;
		OffsetDivOn2 = 1 << mode;

		memcpy(out + outpos, block3 + pos3, 0x10);
		outpos += 0x10;
		pos3 += 0x10;

		CountWord--;
		while (CountWord)
		{
			if (BitCount <= 0x10 && pos1 < blen1)
			{
				BitsBuffer = BYTE(block1, pos1++) | (BitsBuffer << 8);
				BitsBuffer = BYTE(block1, pos1++) | (BitsBuffer << 8);
				BitCount += 0x10;
			}

			if (CURRENT_BIT)
			{
				int i;
				CaseSwitch = BYTE(block2, pos2++);
				BitCount -= 4;
				BitOperation = BitsBuffer >> BitCount & 15;

				for (i = 7; i >= 0; i--)
				{
					if (i & 1)
					{
						if (BitOperation & (1 << (i >> 1)))
						{
							if (CURRENT_BIT)
								OffsetDivOn2 = BYTE(block2, pos2++);
							else
							{
								OffsetDivOn2 = HALF(block3, pos3);
								pos3 += 2;
							}
						}
					}

					if (CaseSwitch >> i & 1)
					{
						int offset = OffsetDivOn2 << mode;
						BYTE(out, outpos) = BYTE(out, outpos - offset);
						outpos++;
						BYTE(out, outpos) = BYTE(out, outpos - offset);
						outpos++;
					}
					else if (CURRENT_BIT)
					{
						HALF(out, outpos) = HALF(block3, pos3);
						outpos += 2;
						pos3 += 2;
					}
					else
					{
						int offset = OffsetDivOn2 << mode;
						unsigned short c = diffTable2[BYTE(block2, pos2++)];
						BYTE(out, outpos) = BYTE(out, outpos - offset) ^ c;
						outpos++;
						BYTE(out, outpos) = BYTE(out, outpos - offset) ^ (c >> 8);
						outpos++;
					}

					if (4 == i && BitCount <= 0x10 && pos1 < blen1)
					{
						BitsBuffer = BYTE(block1, pos1++) | (BitsBuffer << 8);
						BitsBuffer = BYTE(block1, pos1++) | (BitsBuffer << 8);
						BitCount += 0x10;
					}
				}

				CountWord--;
			}
			else
			{
				if (CURRENT_BIT)
				{
					memcpy(out + outpos, block3 + pos3, 0x10);
					outpos += 0x10;
					pos3 += 0x10;
					CountWord--;
				}
				else
				{
					unsigned int i, m = CURRENT_BIT;
					int offset = OffsetDivOn2 << mode;

					if (CURRENT_BIT)
						CaseSwitch = BYTE(block2, pos2++);
					else
					{
						BitCount -= 4;
						CaseSwitch = BitsBuffer >> BitCount & 15;
					}

					CountWord -= CaseSwitch;

					while (CaseSwitch--)
					{
						for (i = 0; i < 0x10; i++)
						{
							if (m)
								BYTE(out, outpos) = BYTE(out, outpos - offset);
							else
								BYTE(out, outpos) = BYTE(block3, pos3++);

							outpos++;
						}
					}
				}
			}
		}

		return len0;
	}

	unsigned int decompress1(unsigned char* dst, unsigned char* src, unsigned int mode /*, BackgroundWorker ^ bwAsync*/)
	{
		unsigned int BitOperation = 0, BitCount = 0, OffsetDivOn2 = 1, pos, pos1, pos2, pos3;
		unsigned int len0, len1, len2, count;

		len0 = WORD(src, 0);
		len1 = WORD(src, 4);
		len2 = WORD(src, 8);

		pos = 0;
		pos1 = 12;
		pos2 = pos1 + len1;
		pos3 = pos2 + len2;

		memcpy(dst + pos, src + pos3, 0x10);
		pos += 0x10;
		pos3 += 0x10;

		count = len0 >> 4;
		while (--count)
		{
			while (BitCount <= 2)
			{
				if (pos1 < pos2)
				{
					BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
					pos1++;
				}

				BitCount += 8;
			}

			BitCount--;

			if (0 == (BitOperation & 0x80000000)) // bit unset
			{
				int i;

				BitOperation <<= 1;

				if (0 == (BitOperation & 0x80000000)) // bit unset
				{
					memcpy(dst + pos, src + pos3, 0x10);
					pos += 0x10;
					pos3 += 0x10;
				}
				else for (i = 0; i < 8; i++) // bit set
				{
					int off = OffsetDivOn2 << mode;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
				}

				BitOperation <<= 1;
				BitCount--;
			}
			else // bit set
			{
				unsigned int i, b2 = BYTE(src, pos2);
				pos2++;

				BitOperation <<= 1;

				while (BitCount <= 0x10)
				{
					if (pos1 < pos2)
					{
						BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
						pos1++;
					}

					BitCount += 8;
				}

				for (i = 0; i < 8; i++)
				{
					if (0 == (i & 1)) // 0 2 4 6
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							BitOperation <<= 1;
							BitCount--;

							if (0 == (BitOperation & 0x80000000)) // bit unset
							{
								OffsetDivOn2 = HALF(src, pos3);
								pos3 += 2;
							}
							else // bit set
							{
								OffsetDivOn2 = BYTE(src, pos2);
								pos2++;
							}
						}

						BitCount--;
						BitOperation <<= 1;
					}

					if (b2 & (0x80 >> i)) // bit set
					{
						int off = OffsetDivOn2 << mode;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
					}
					else // bit unset
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							int off = OffsetDivOn2 << mode;
							unsigned short c = diffTable[mode][BYTE(src, pos2)];
							pos2++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ c;
							pos++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ (c >> 8);
							pos++;
						}
						else // bit set
						{
							HALF(dst, pos) = HALF(src, pos3);
							pos += 2;
							pos3 += 2;
						}

						BitCount--;
						BitOperation <<= 1;
					}
				}
			}
		}

		return len0;
	}

	unsigned int decompress0(unsigned char* dst, unsigned char* src, unsigned int mode /*, BackgroundWorker ^ bwAsync*/)
	{
		unsigned int BitOperation = 0, BitCount = 0, OffsetDivOn2 = 1, pos, pos1, pos2, pos3;
		unsigned int len0, len1, len2, count;

		len0 = WORD(src, 0);
		len1 = WORD(src, 4);
		len2 = WORD(src, 8);

		pos = 0;
		pos1 = 12;
		pos2 = pos1 + len1;
		pos3 = pos2 + len2;

		memcpy(dst + pos, src + pos3, 0x10);
		pos += 0x10;
		pos3 += 0x10;

		count = len0 >> 4;
		while (--count)
		{
			while (BitCount <= 2)
			{
				if (pos1 < pos2)
				{
					BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
					pos1++;
				}

				BitCount += 8;
			}

			BitCount--;

			if (0 == (BitOperation & 0x80000000)) // bit unset
			{
				int i;

				BitOperation <<= 1;

				if (0 == (BitOperation & 0x80000000)) // bit unset
				{
					memcpy(dst + pos, src + pos3, 0x10);
					pos += 0x10;
					pos3 += 0x10;
				}
				else for (i = 0; i < 8; i++) // bit set
				{
					int off = OffsetDivOn2 << mode;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
				}

				BitOperation <<= 1;
				BitCount--;
			}
			else // bit set
			{
				unsigned int i, b2 = BYTE(src, pos2);
				pos2++;

				BitOperation <<= 1;

				while (BitCount <= 0x10)
				{
					if (pos1 < pos2)
					{
						BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
						pos1++;
					}

					BitCount += 8;
				}

				for (i = 0; i < 8; i++)
				{
					if (0 == (i & 1)) // 0 2 4 6
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							BitOperation <<= 1;
							BitCount--;

							if (0 == (BitOperation & 0x80000000)) // bit unset
							{
								OffsetDivOn2 = HALF(src, pos3);
								pos3 += 2;
							}
							else // bit set
							{
								OffsetDivOn2 = BYTE(src, pos2);
								pos2++;
							}
						}

						BitCount--;
						BitOperation <<= 1;
					}

					if (b2 & (0x80 >> i)) // bit set
					{
						int off = OffsetDivOn2 << mode;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
					}
					else // bit unset
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							int off = OffsetDivOn2 << mode;
							unsigned short c = diffTable[1][BYTE(src, pos2)];
							pos2++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ c;
							pos++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ (c >> 8);
							pos++;
						}
						else // bit set
						{
							HALF(dst, pos) = HALF(src, pos3);
							pos += 2;
							pos3 += 2;
						}

						BitCount--;
						BitOperation <<= 1;
					}
				}
			}
		}

		return len0;
	}

	unsigned int decompress_qmdc(unsigned char* dst, unsigned char* src, unsigned int mode /*, BackgroundWorker ^ bwAsync*/)
	{
		unsigned int BitOperation = 0, BitCount = 0, OffsetDivOn2 = 1, pos, pos1, pos2, pos3;
		unsigned int len0, len1, len2, count;

		if (MAGIC_QMDC != WORD(src, 0x0)) return 0;

		len0 = WORD(src, 0x8);
		len1 = WORD(src, 0xc);
		len2 = WORD(src, 0x10);

		pos = 0;
		pos1 = 0x14;
		pos2 = pos1 + len1;
		pos3 = pos2 + len2;

		memcpy(dst + pos, src + pos3, 0x10);
		pos += 0x10;
		pos3 += 0x10;

		count = len0 >> 4;
		while (--count)
		{
			while (BitCount <= 2)
			{
				if (pos1 < pos2)
				{
					BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
					pos1++;
				}

				BitCount += 8;
			}

			BitCount--;

			if (0 == (BitOperation & 0x80000000)) // bit unset
			{
				int i;

				BitOperation <<= 1;

				if (0 == (BitOperation & 0x80000000)) // bit unset
				{
					memcpy(dst + pos, src + pos3, 0x10);
					pos += 0x10;
					pos3 += 0x10;
				}
				else for (i = 0; i < 8; i++) // bit set
				{
					int off = OffsetDivOn2 << mode;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
				}

				BitOperation <<= 1;
				BitCount--;
			}
			else // bit set
			{
				unsigned int i, b2 = BYTE(src, pos2);
				pos2++;

				BitOperation <<= 1;

				while (BitCount <= 0x10)
				{
					if (pos1 < pos2)
					{
						BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
						pos1++;
					}

					BitCount += 8;
				}

				for (i = 0; i < 8; i++)
				{
					if (0 == (i & 1)) // 0 2 4 6
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							BitOperation <<= 1;
							BitCount--;

							if (0 == (BitOperation & 0x80000000)) // bit unset
							{
								OffsetDivOn2 = HALF(src, pos3);
								pos3 += 2;
							}
							else // bit set
							{
								OffsetDivOn2 = BYTE(src, pos2);
								pos2++;
							}
						}

						BitCount--;
						BitOperation <<= 1;
					}

					if (b2 & (0x80 >> i)) // bit set
					{
						int off = OffsetDivOn2 << mode;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
					}
					else // bit unset
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							int off = OffsetDivOn2 << mode;
							unsigned short c = diffTable[mode][BYTE(src, pos2)];
							pos2++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ c;
							pos++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ (c >> 8);
							pos++;
						}
						else // bit set
						{
							HALF(dst, pos) = HALF(src, pos3);
							pos += 2;
							pos3 += 2;
						}

						BitCount--;
						BitOperation <<= 1;
					}
				}
			}
		}

		return len0;
	}

	unsigned int decompress_raw(unsigned char* dst, unsigned char* src, unsigned int mode, unsigned int raw_size, unsigned int bits_size1, unsigned int bits_size2 /*, BackgroundWorker ^ bwAsync*/)
	{
		unsigned int BitOperation = 0, BitCount = 0, OffsetDivOn2 = 1, pos, pos1, pos2, pos3;
		unsigned int len0, len1, len2, count;

		len0 = raw_size;
		len1 = bits_size1;
		len2 = bits_size2;

		pos = 0;
		pos1 = 0;
		pos2 = pos1 + len1;
		pos3 = pos2 + len2;

		memcpy(dst + pos, src + pos3, 0x10);
		pos += 0x10;
		pos3 += 0x10;

		count = len0 >> 4;
		while (--count)
		{
			while (BitCount <= 2)
			{
				if (pos1 < pos2)
				{
					BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
					pos1++;
				}

				BitCount += 8;
			}

			BitCount--;

			if (0 == (BitOperation & 0x80000000)) // bit unset
			{
				int i;

				BitOperation <<= 1;

				if (0 == (BitOperation & 0x80000000)) // bit unset
				{
					memcpy(dst + pos, src + pos3, 0x10);
					pos += 0x10;
					pos3 += 0x10;
				}
				else for (i = 0; i < 8; i++) // bit set
				{
					int off = OffsetDivOn2 << mode;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
					BYTE(dst, pos) = BYTE(dst, pos - off);
					pos++;
				}

				BitOperation <<= 1;
				BitCount--;
			}
			else // bit set
			{
				unsigned int i, b2 = BYTE(src, pos2);
				pos2++;

				BitOperation <<= 1;

				while (BitCount <= 0x10)
				{
					if (pos1 < pos2)
					{
						BitOperation |= BYTE(src, pos1) << (0x18 - BitCount);
						pos1++;
					}

					BitCount += 8;
				}

				for (i = 0; i < 8; i++)
				{
					if (0 == (i & 1)) // 0 2 4 6
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							BitOperation <<= 1;
							BitCount--;

							if (0 == (BitOperation & 0x80000000)) // bit unset
							{
								OffsetDivOn2 = HALF(src, pos3);
								pos3 += 2;
							}
							else // bit set
							{
								OffsetDivOn2 = BYTE(src, pos2);
								pos2++;
							}
						}

						BitCount--;
						BitOperation <<= 1;
					}

					if (b2 & (0x80 >> i)) // bit set
					{
						int off = OffsetDivOn2 << mode;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
						BYTE(dst, pos) = BYTE(dst, pos - off);
						pos++;
					}
					else // bit unset
					{
						if (0 == (BitOperation & 0x80000000)) // bit unset
						{
							int off = OffsetDivOn2 << mode;
							unsigned short c = diffTable[mode][BYTE(src, pos2)];
							pos2++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ c;
							pos++;
							BYTE(dst, pos) = BYTE(dst, pos - off) ^ (c >> 8);
							pos++;
						}
						else // bit set
						{
							HALF(dst, pos) = HALF(src, pos3);
							pos += 2;
							pos3 += 2;
						}

						BitCount--;
						BitOperation <<= 1;
					}
				}
			}
		}

		return len0;
	}

	unsigned int qmd_get_header(unsigned char* data)
	{
		if (MAGIC_QMD == WORD(data, 0))
			return 0;

		if (MAGIC_QMD == WORD(data, 0x40000))
			return 0x40000;

		if (MAGIC_QMD == WORD(data, 0x80000))
			return 0x80000;

		if (MAGIC_QMD == WORD(data, 0xa0000))
			return 0xa0000;

		return E_FAIL;
	}

	unsigned int qmd_get_ver(unsigned char* data)
	{
		unsigned int /*ver,*/ header;

		header = qmd_get_header(data);
		if (E_FAIL == header)
			return 0;

		return GET_HALF/*_RAW*/(data, header + 8);
	}

	unsigned int qmd_get_decompress_size(unsigned char* data)
	{
		unsigned int /*size,*/ header;

		header = qmd_get_header(data);
		if (E_FAIL == header)
			return 0;

		return GET_WORD/*_RAW*/(data, header + 16);
	}

	unsigned int qmd_get_size(unsigned char* data)
	{
		t_qmd_entry* entry;
		t_qmd_header* qmd;
		unsigned int size = 0, header;

		header = qmd_get_header(data);
		if (E_FAIL == header)
			return 0;

		qmd = (t_qmd_header*)(data + header);
		entry = (t_qmd_entry*)(data + header + 0x100);

		while (entry->type)
		{
			size += qmd->header_size;
			entry++;
		}

		if (size > 0 && size < 0x10000000) // 256MB
			return size;

		return 0;
	}

	unsigned int qmd_parser(unsigned char* dst, unsigned char* src /*, BackgroundWorker ^ bwAsync*/)
	{
		t_qmd_entry* entry;
		unsigned char* srcpos;
		unsigned int bada2, mode, len;


		switch (qmd_get_ver(src))
		{
		case DECOMP_CODE1:
		case 0x2:
			bada2 = 0;
			mode = QMD_CODE;
			break;

		case DECOMP_DATA1:
			bada2 = 0;
			mode = QMD_DATA;
			break;

		case DECOMP_CODE2:
			bada2 = 1;
			mode = QMD_CODE;
			break;

		case DECOMP_DATA2:
			bada2 = 1;
			mode = QMD_DATA;
			break;

		default:
			return E_FAIL;
		}


		entry = (t_qmd_entry*)(src + qmd_get_header(src) + 0x100);
		while (entry->type)
		{
			unsigned int i, len2, pos;

			srcpos = src + entry->offset;

			switch (entry->type)
			{
			case 0x0F:
			case 0x0A:
			case 0x03:
				memcpy(dst, srcpos, entry->length);
				dst += entry->length;
				break;

			case 0x01:
				if (bada2)
					len = decompress2(dst, srcpos, mode);
				else
					len = decompress1(dst, srcpos, mode);
				if (!len)
					return E_FAIL;

				dst += len;
				break;

			case 0x08:
				pos = 0;

				for (i = 0; i < 0x40; i++)
				{
					len = len2 = HALF(srcpos, i << 1);

					if (0x1000 == len2)
						memcpy(dst, srcpos + 0x80 + pos, len2);
					else if (bada2)
						len = decompress2(dst, srcpos + 0x80 + pos, mode);
					else
						len = decompress1(dst, srcpos + 0x80 + pos, mode);

					if (!len)
						return E_FAIL;

					dst += len;
					pos += len2;
				}
				break;
			}

			entry++;
		}

		return E_OK;
	}

	//unsigned int qmd_compose ( unsigned char *dst, unsigned char *src, unsigned int mode )
	//{
	//	// TODO
	//
	//	return E_FAIL;
	//}





	unsigned int decompress(unsigned char* src, unsigned char* dst)
	{		
		unsigned int length = qmd_get_size(src);
		if (length <= 0)
			return E_FAIL;		

		if (E_FAIL == qmd_parser(dst, src))
		{			
			return E_FAIL;
		}

		return length;
	}
}