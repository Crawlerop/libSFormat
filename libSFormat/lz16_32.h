#pragma once
#include "utils.h"

namespace LZIMG {
	unsigned int LZ16_decompress(unsigned char* src, unsigned char* dst) {
		unsigned int count_in1 = 0, count_in2 = 0, count_write = 0;
		unsigned char* src1, * src2;
		unsigned int data = 0, count = 0;

		unsigned int offset = ((GET_HALF(src, 0) << 0x8) | GET_HALF(src, 0) >> 0x8) & 0xFFFF;
		src2 = src + 2 + offset;
		src1 = src + 2;

		if ((offset & 1) != 0) { //Если установлен младший бит, т.е. офсет нечетное число

			offset = (offset & 0xFFFE) | (GET_BYTE(src, 2) << 15) | (GET_BYTE(src, 3) << 23);
			src2 = src + 4 + offset;
			src1 = src + 4;
		}



		while (count_in1 < offset) {

			unsigned short  a = BYTE(src1, count_in1);

			if ((a >> 4) != 0) {

				unsigned short  b = BYTE(src1, (count_in1 + 1));
				unsigned int off = (count_write - (unsigned int)(((a & 7) << 8) | b));
				count = 0;

				while (count < (a >> 4)) {
					SET_HALF(dst, count_write << 1, GET_HALF(/*pRead*/dst, (off + count) << 1));
					count_write++; count++;
				}

			}
			else {

				data = GET_HALF(src2, (count_in2 << 1));
				SET_HALF(dst, (count_write << 1), data);
				count_write++; count_in2++;
			}

			count_in1 += 2;

		}//while(count_in1 < offset);

			//data = GET_HALF(src2, (count_in2<<1));
			//SET_HALF( dst, (count_write<<1)-2, data );
			//count_write++; count_in2++;

		return count_write;
	}

	unsigned int/*void*/ LZ32_decompress(unsigned char* src, unsigned char* dst) {
		unsigned int count_in1 = 0, len1, count_in2 = 0, len2, count_in3 = 0, count_write = 0;
		unsigned char* src1, * src2, * src3;
		unsigned int data = 0, count = 0, offset_src3 = 0;
		unsigned char  shift = 0;

		char  header[8] = { 0,0,0,0,0,0,0,0 };

		src1 = src + 0x8;
		len1 = (unsigned int)(BYTE(src, 2) << 0xF) | (unsigned int)(BYTE(src, 0) << 0x8) | (unsigned int)(BYTE(src, 1));
		len1 = len1 & ~1;
		src2 = src1 + len1;
		len2 = (unsigned int)(BYTE(src, 6) << 0xF) | (unsigned int)(BYTE(src, 4) << 0x8) | (unsigned int)(BYTE(src, 5));
		src3 = src2 + len2;
		//len3 = 

		do {
			SET_HALF(dst, count_write << 1, GET_HALF(src2, count_in2 << 1));
			count_write++;	count_in2++;

			offset_src3 = ((count_in2 - 1) >> 2) & 0x1FFFFFFF;
			shift = 7 & ((count_in2 - 1) << 1);

			//}while(BYTE(src3, offset_src3) & header[shift] == 0);
		} while (((signed char)(GET_BYTE(src3, offset_src3) >> shift) & 0x3)/* & header[shift]*/ == 0);


		while (count_in1 < len1) {

			unsigned char repeat_count = ((BYTE(src1, count_in1)) >> 1) & 0x3F;
			unsigned int offset = count_write - BYTE(src1, count_in1 + 1);


			unsigned char count = 0;
			//unsigned int repeat = repeat_count&~1;
			while (count < (repeat_count & ~1)) {

				SET_HALF(dst, count_write << 1, GET_HALF(dst, (offset + count) << 1));
				SET_HALF(dst, (count_write + 1) << 1, GET_HALF(dst, (offset + count + 1) << 1));
				count += 2; count_write += 2;//count_write в халфах

			}

			while (count < repeat_count) {

				SET_HALF(dst, count_write << 1, GET_HALF(dst, (offset + count) << 1));
				count++; count_write++;

			}

			if ((signed char)(BYTE(src1, count_in1)) < 0) {

				do {
					SET_HALF(dst, count_write << 1, GET_HALF(src2, count_in2 << 1));
					count_write++;	count_in2++;

					offset_src3 = ((count_in2 - 1) >> 2) & 0x1FFFFFFF;
					shift = 7 & ((count_in2 - 1) << 1);

					//}while(BYTE(src3, offset_src3) & header[shift] == 0);
				} while (((GET_BYTE(src3, offset_src3) >> shift) & 0x3)/* & header[shift]*/ == 0);

			}

			count_in1 += 2;

		}//while(count_in1 < len1);


		return count_write;
	}
}