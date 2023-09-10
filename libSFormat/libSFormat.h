// libSFormat.h : Include file for standard system include files,
// or project specific include files.

#pragma once
using namespace std;
#include "compressLZ.h"
#include "lz16_32.h"
#include "qmd.h"
#include "crypt.h"
#include "qmr.h"

#if defined(_MSC_VER)
//  Microsoft 
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#else
//  do nothing and hope for the best?
#define EXPORT
#define IMPORT
#pragma warning Unknown dynamic link import/export semantics.
#endif

extern "C" {
	EXPORT unsigned int CLZ_decompress(unsigned char* src, unsigned char* pWrite) {		
		return CompressLZ::decompress(src, pWrite);
	};
	EXPORT unsigned int CLZ_decompress_be(unsigned char* src, unsigned char* pWrite) {
		return CompressLZ::decompress_big(src, pWrite);
	};
	EXPORT unsigned int LZ16_decompress(unsigned char* src, unsigned char* dst) {
		return LZIMG::LZ16_decompress(src, dst);
	};
	EXPORT unsigned int LZ16_decompress_be(unsigned char* src, unsigned char* dst) {
		return LZIMG::LZ16_decompress_big(src, dst);
	};
	EXPORT unsigned int LZ32_decompress(unsigned char* src, unsigned char* dst) {
		return LZIMG::LZ32_decompress(src, dst);
	};
	EXPORT unsigned int QMD_decompress(unsigned char* src, unsigned char* dst) {
		return QMD::decompress(src, dst);
	};
	/*
	EXPORT unsigned int QMR_decompress(unsigned char* src, unsigned char* dst) {
		return QMR::decompress(src, dst);
	};
	*/
	EXPORT unsigned int QMD_decompress_data(unsigned char* src, unsigned char* dst, unsigned int mode, unsigned int version) {
		switch (version) {
			case 0:
				return QMD::decompress0(dst, src, mode);
			case 1:
				return QMD::decompress1(dst, src, mode);
			case 2:
				return QMD::decompress2(dst, src, mode);
			default:
				return 0;
		}
	};
	EXPORT unsigned int QMDC_decompress(unsigned char* src, unsigned char* dst, unsigned int mode) {
		return QMD::decompress_qmdc(dst, src, mode);
	};
	EXPORT unsigned int QMD_decompress_raw(unsigned char* src, unsigned char* dst, unsigned int mode, unsigned int raw_size, unsigned int block_size_1, unsigned int block_size_2) {
		return QMD::decompress_raw(dst, src, mode, raw_size, block_size_1, block_size_2);
	};
	EXPORT void TKT_decrypt(unsigned char* src, unsigned int len) {
		SFCrypto::decrypt(src, len, false);
	};
	EXPORT void TKT_decrypt3(unsigned char* src, unsigned int len) {
		SFCrypto::decrypt(src, len, true);
	};
};

//#include <iostream>

// TODO: Reference additional headers your program requires here.
