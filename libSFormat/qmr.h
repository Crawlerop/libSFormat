#pragma once
#include <stdlib.h>
#include <memory.h>
#include "utils.h"

#include "stdio.h"
#define DEBUG_QMD 1

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

#define MAGIC_QMR       0x00524D51 // QMD

//#define GET_BYTE( data, pos )           ( ( (unsigned char *)( data ) )[pos] )
//#define GET_HALF( data, pos )           ( ( GET_BYTE ( data, ( ( pos ) + 1 ) ) << 8 ) | GET_BYTE ( data, ( pos ) ) )
//#define GET_WORD( data, pos )           ( ( GET_HALF ( data, ( ( pos ) + 2 ) ) << 16 ) | GET_HALF ( data, ( pos ) ) )
//#define SET_BYTE( data, pos, val )      do { ( (unsigned char *)( data ) )[pos] = val; } while ( 0 )
//#define SET_HALF( data, pos, val )      do { SET_BYTE ( data, ( pos ) + 1, ( ( val ) >> 8 ) & 0xFF ); SET_BYTE ( data, ( pos ), ( val ) & 0xFF ); } while ( 0 )
//#define SET_WORD( data, pos, val )      do { SET_HALF ( data, ( pos ) + 2, ( ( val ) >> 16 ) & 0xFFFF ); SET_HALF ( data, ( pos ), ( val ) & 0xFFFF ); } while ( 0 )

namespace QMR
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

	unsigned int qmd_get_header(unsigned char* data)
	{
		if (MAGIC_QMR == WORD(data, 0))
			return 0;

		if (MAGIC_QMR == WORD(data, 0x40000))
			return 0x40000;

		if (MAGIC_QMR == WORD(data, 0x80000))
			return 0x80000;

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
		entry = (t_qmd_entry*)(data + header + 0x10c);

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
		t_qmd_header* qmd;
		t_qmd_entry* entry;
		unsigned char* srcpos;
		unsigned int bada2, mode, len;


		switch (qmd_get_ver(src))
		{
		case DECOMP_CODE1:		
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
		case 0x2:
			bada2 = 1;
			mode = QMD_DATA;
			break;

		default:						
			return E_FAIL;
		}

		qmd = (t_qmd_header*)(src + qmd_get_header(src));
		entry = (t_qmd_entry*)(src + qmd_get_header(src) + 0x10c);
		printf("0x%x\n", entry->type);

		while (entry->type)
		{
			unsigned int i, len2, pos;

			srcpos = src + entry->offset + qmd->data_offset;
#if DEBUG_QMD
			printf("0x%x\n", entry->offset + qmd->data_offset);
#endif

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
						memcpy(dst, srcpos + pos, len2);
					else if (bada2)
						len = decompress2(dst, srcpos + pos, mode);
					else
						len = decompress1(dst, srcpos + pos, mode);

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