#pragma once
#include "utils.h"

namespace CompressLZ
{
	unsigned int decompress(unsigned char* src, unsigned char* pWrite) {
		unsigned int count_in1 = 0, count_in2 = 0, count_write = 0;
		unsigned char* src1, * src2, * pRead;
		unsigned int data = 0, count = 0;

		unsigned int offset = (GET_HALF(src, 0) << 0x8 | GET_HALF(src, 0) >> 0x8) & 0xFFFF;
		src2 = src + 2 + offset;
		src1 = src + 2;

		if ((offset & 1) != 0) { //Если установлен младший бит, т.е. офсет нечетное число

			offset = (offset & 0xFFFE) | (GET_BYTE(src, 2) << 15) | (GET_BYTE(src, 3) << 23);
			src2 = src + 4 + offset;
			src1 = src + 4;
		}

		do {
			data = GET_HALF(src2, (count_in2 << 1));
			SET_HALF(pWrite, (count_write << 1), data);
			count_write++; count_in2++;

		} while ((data & 0x20) == 0);

		SET_HALF(pWrite, (count_write - 1) << 1, (data & ~0x20));

		if (offset > 0) { // Если старший бит не установлен

			do {

				unsigned short  a = BYTE(src1, count_in1);
				unsigned short  b = BYTE(src1, (count_in1 + 1));


				pRead = pWrite + ((count_write - ((a & 7) << 8 | b)) << 1);

				count = 0;

				do {
					SET_HALF(pWrite, (count_write) << 1, GET_HALF(pRead, count << 1));
					SET_HALF(pWrite, (count_write + 1) << 1, GET_HALF(pRead, (count + 1) << 1));
					count_write += 2; count += 2;
				} while (count < (a >> 4) - 2);

				while (count < (a >> 4)) {
					SET_HALF(pWrite, count_write << 1, GET_HALF(pRead, count << 1));
					count_write++; count++;

				}

				if ((a & 8) != 0) { // если 4й бит не установлен

					do {
						data = GET_HALF(src2, (count_in2 << 1));
						SET_HALF(pWrite, (count_write << 1), data);
						count_write++; count_in2++;

					} while ((data & 0x20) == 0);

					SET_HALF(pWrite, (count_write - 1) << 1, (data & ~0x20));
				}

				count_in1 += 2;

			} while (count_in1 < offset);

		}
		if ((offset & 1) != 0) {
			data = GET_HALF(src2, (count_in2 << 1));
			SET_HALF(pWrite, (count_write << 1), data);
			count_write++; count_in2++;
		}
		return count_write;
	}
};