#include <stdio.h>
#include <string.h>
#include <string>
#include <xbyak/xbyak.h>
#include <cybozu/inttype.hpp>
#include <cybozu/test.hpp>

using namespace Xbyak;

CYBOZU_TEST_AUTO(setSize)
{
	struct Code : Xbyak::CodeGenerator {
		Code() : Xbyak::CodeGenerator(4096)
		{
			setSize(4095);
			db(1);
			size_t size = getSize();
			CYBOZU_TEST_EQUAL(size, 4096u);
			CYBOZU_TEST_NO_EXCEPTION(setSize(size));
			CYBOZU_TEST_EXCEPTION(db(1), Xbyak::Error);
		}
	} code;
}

CYBOZU_TEST_AUTO(compOperand)
{
	using namespace Xbyak::util;
	CYBOZU_TEST_ASSERT(eax == eax);
	CYBOZU_TEST_ASSERT(ecx != xmm0);
	CYBOZU_TEST_ASSERT(ptr[eax] == ptr[eax]);
	CYBOZU_TEST_ASSERT(dword[eax] != ptr[eax]);
	CYBOZU_TEST_ASSERT(ptr[eax] != ptr[eax+3]);
}

CYBOZU_TEST_AUTO(mov_const)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			const struct {
				uint64_t v;
				int bit;
				bool error;
			} tbl[] = {
				{ uint64_t(-1), 8, false },
				{ 0x12, 8, false },
				{ 0x80, 8, false },
				{ 0xff, 8, false },
				{ 0x100, 8, true },

				{ 1, 16, false },
				{ uint64_t(-1), 16, false },
				{ 0x7fff, 16, false },
				{ 0xffff, 16, false },
				{ 0x10000, 16, true },

				{ uint64_t(-1), 32, false },
				{ 0x7fffffff, 32, false },
				{ uint64_t(-0x7fffffff), 32, false },
				{ 0xffffffff, 32, false },
				{ 0x100000000ull, 32, true },

#ifdef XBYAK64
				{ uint64_t(-1), 64, false },
				{ 0x7fffffff, 64, false },
				{ 0xffffffffffffffffull, 64, false },
				{ 0x80000000, 64, true },
				{ 0xffffffff, 64, true },
#endif
			};
			for (size_t i = 0; i < CYBOZU_NUM_OF_ARRAY(tbl); i++) {
				const int bit = tbl[i].bit;
				const uint64_t v = tbl[i].v;
				const Xbyak::AddressFrame& af = bit == 8 ? byte : bit == 16 ? word : bit == 32 ? dword : qword;
				if (tbl[i].error) {
					CYBOZU_TEST_EXCEPTION(mov(af[eax], v), Xbyak::Error);
				} else {
					CYBOZU_TEST_NO_EXCEPTION(mov(af[eax], v));
				}
			}
		}
	} code;
}

CYBOZU_TEST_AUTO(align)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			const size_t alignSize = 16;
			for (int padding = 0; padding < 20; padding++) {
				for (int i = 0; i < padding; i++) {
					db(1);
				}
				align(alignSize);
				CYBOZU_TEST_EQUAL(size_t(getCurr()) % alignSize, 0u);
			}
			align(alignSize);
			const uint8 *p = getCurr();
			// do nothing if aligned
			align(alignSize);
			CYBOZU_TEST_EQUAL(p, getCurr());
		}
	} c;
}

#ifdef XBYAK64
CYBOZU_TEST_AUTO(vfmaddps)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			v4fmaddps(zmm1, zmm8, ptr [rdx + 64]);
			v4fmaddss(xmm15, xmm8, ptr [rax + 64]);
			v4fnmaddps(zmm5 | k5, zmm2, ptr [rcx + 0x80]);
			v4fnmaddss(xmm31, xmm2, ptr [rsp + 0x80]);
			vp4dpwssd(zmm23 | k7 | T_z, zmm1, ptr [rax + 64]);
			vp4dpwssds(zmm10 | k4, zmm3, ptr [rsp + rax * 4 + 64]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf2, 0x3f, 0x48, 0x9a, 0x4a, 0x04,
		0x62, 0x72, 0x3f, 0x08, 0x9b, 0x78, 0x04,
		0x62, 0xf2, 0x6f, 0x4d, 0xaa, 0x69, 0x08,
		0x62, 0x62, 0x6f, 0x08, 0xab, 0x7c, 0x24, 0x08,
		0x62, 0xe2, 0x77, 0xcf, 0x52, 0x78, 0x04,
		0x62, 0x72, 0x67, 0x4c, 0x53, 0x54, 0x84, 0x04,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(vaes)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vaesdec(xmm20, xmm30, ptr [rcx + 64]);
			vaesdec(ymm1, ymm2, ptr [rcx + 64]);
			vaesdec(zmm1, zmm2, ptr [rcx + 64]);

			vaesdeclast(xmm20, xmm30, ptr [rax + 64]);
			vaesdeclast(ymm20, ymm30, ptr [rax + 64]);
			vaesdeclast(zmm20, zmm30, ptr [rax + 64]);

			vaesenc(xmm20, xmm30, ptr [rcx + 64]);
			vaesenc(ymm1, ymm2, ptr [rcx + 64]);
			vaesenc(zmm1, zmm2, ptr [rcx + 64]);

			vaesenclast(xmm20, xmm30, ptr [rax + 64]);
			vaesenclast(ymm20, ymm30, ptr [rax + 64]);
			vaesenclast(zmm20, zmm30, ptr [rax + 64]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xE2, 0x0D, 0x00, 0xDE, 0x61, 0x04,
		0xC4, 0xE2, 0x6D, 0xDE, 0x49, 0x40,
		0x62, 0xF2, 0x6D, 0x48, 0xDE, 0x49, 0x01,

		0x62, 0xE2, 0x0D, 0x00, 0xDF, 0x60, 0x04,
		0x62, 0xE2, 0x0D, 0x20, 0xDF, 0x60, 0x02,
		0x62, 0xE2, 0x0D, 0x40, 0xDF, 0x60, 0x01,

		0x62, 0xE2, 0x0D, 0x00, 0xDC, 0x61, 0x04,
		0xC4, 0xE2, 0x6D, 0xDC, 0x49, 0x40,
		0x62, 0xF2, 0x6D, 0x48, 0xDC, 0x49, 0x01,

		0x62, 0xE2, 0x0D, 0x00, 0xDD, 0x60, 0x04,
		0x62, 0xE2, 0x0D, 0x20, 0xDD, 0x60, 0x02,
		0x62, 0xE2, 0x0D, 0x40, 0xDD, 0x60, 0x01,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(vpclmulqdq)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpclmulqdq(xmm2, xmm3, ptr [rax + 64], 3);
			vpclmulqdq(ymm2, ymm3, ptr [rax + 64], 3);
			vpclmulqdq(zmm2, zmm3, ptr [rax + 64], 3);

			vpclmulqdq(xmm20, xmm3, ptr [rax + 64], 3);
			vpclmulqdq(ymm20, ymm3, ptr [rax + 64], 3);
			vpclmulqdq(zmm20, zmm3, ptr [rax + 64], 3);
		}
	} c;
	const uint8_t tbl[] = {
		0xc4, 0xe3, 0x61, 0x44, 0x50, 0x40, 0x03,
		0xc4, 0xe3, 0x65, 0x44, 0x50, 0x40, 0x03,
		0x62, 0xf3, 0x65, 0x48, 0x44, 0x50, 0x01, 0x03,
		0x62, 0xe3, 0x65, 0x08, 0x44, 0x60, 0x04, 0x03,
		0x62, 0xe3, 0x65, 0x28, 0x44, 0x60, 0x02, 0x03,
		0x62, 0xe3, 0x65, 0x48, 0x44, 0x60, 0x01, 0x03,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(vcompressb_w)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vcompressb(ptr[rax + 64], xmm1);
			vcompressb(xmm30 | k5, xmm1);
			vcompressb(ptr[rax + 64], ymm1);
			vcompressb(ymm30 | k3 |T_z, ymm1);
			vcompressb(ptr[rax + 64], zmm1);
			vcompressb(zmm30 | k2 |T_z, zmm1);

			vcompressw(ptr[rax + 64], xmm1);
			vcompressw(xmm30 | k5, xmm1);
			vcompressw(ptr[rax + 64], ymm1);
			vcompressw(ymm30 | k3 |T_z, ymm1);
			vcompressw(ptr[rax + 64], zmm1);
			vcompressw(zmm30 | k2 |T_z, zmm1);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf2, 0x7d, 0x08, 0x63, 0x48, 0x40,
		0x62, 0x92, 0x7d, 0x0d, 0x63, 0xce,
		0x62, 0xf2, 0x7d, 0x28, 0x63, 0x48, 0x40,
		0x62, 0x92, 0x7d, 0xab, 0x63, 0xce,
		0x62, 0xf2, 0x7d, 0x48, 0x63, 0x48, 0x40,
		0x62, 0x92, 0x7d, 0xca, 0x63, 0xce,

		0x62, 0xf2, 0xfd, 0x08, 0x63, 0x48, 0x20,
		0x62, 0x92, 0xfd, 0x0d, 0x63, 0xce,
		0x62, 0xf2, 0xfd, 0x28, 0x63, 0x48, 0x20,
		0x62, 0x92, 0xfd, 0xab, 0x63, 0xce,
		0x62, 0xf2, 0xfd, 0x48, 0x63, 0x48, 0x20,
		0x62, 0x92, 0xfd, 0xca, 0x63, 0xce,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(shld)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpshldw(xmm5|k3|T_z, xmm2, ptr [rax + 0x40], 5);
			vpshldw(ymm5|k3|T_z, ymm2, ptr [rax + 0x40], 5);
			vpshldw(zmm5|k3|T_z, zmm2, ptr [rax + 0x40], 5);

			vpshldd(xmm5|k3|T_z, xmm2, ptr [rax + 0x40], 5);
			vpshldd(ymm5|k3|T_z, ymm2, ptr [rax + 0x40], 5);
			vpshldd(zmm5|k3|T_z, zmm2, ptr [rax + 0x40], 5);

			vpshldq(xmm5|k3|T_z, xmm2, ptr [rax + 0x40], 5);
			vpshldq(ymm5|k3|T_z, ymm2, ptr [rax + 0x40], 5);
			vpshldq(zmm5|k3|T_z, zmm2, ptr [rax + 0x40], 5);

			vpshldvw(xmm5|k3|T_z, xmm2, ptr [rax + 0x40]);
			vpshldvw(ymm5|k3|T_z, ymm2, ptr [rax + 0x40]);
			vpshldvw(zmm5|k3|T_z, zmm2, ptr [rax + 0x40]);

			vpshldvd(xmm5|k3|T_z, xmm2, ptr [rax + 0x40]);
			vpshldvd(ymm5|k3|T_z, ymm2, ptr [rax + 0x40]);
			vpshldvd(zmm5|k3|T_z, zmm2, ptr [rax + 0x40]);

			vpshldvq(xmm5|k3|T_z, xmm2, ptr [rax + 0x40]);
			vpshldvq(ymm5|k3|T_z, ymm2, ptr [rax + 0x40]);
			vpshldvq(zmm5|k3|T_z, zmm2, ptr [rax + 0x40]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf3, 0xed, 0x8b, 0x70, 0x68, 0x04, 0x05,
		0x62, 0xf3, 0xed, 0xab, 0x70, 0x68, 0x02, 0x05,
		0x62, 0xf3, 0xed, 0xcb, 0x70, 0x68, 0x01, 0x05,

		0x62, 0xf3, 0x6d, 0x8b, 0x71, 0x68, 0x04, 0x05,
		0x62, 0xf3, 0x6d, 0xab, 0x71, 0x68, 0x02, 0x05,
		0x62, 0xf3, 0x6d, 0xcb, 0x71, 0x68, 0x01, 0x05,

		0x62, 0xf3, 0xed, 0x8b, 0x71, 0x68, 0x04, 0x05,
		0x62, 0xf3, 0xed, 0xab, 0x71, 0x68, 0x02, 0x05,
		0x62, 0xf3, 0xed, 0xcb, 0x71, 0x68, 0x01, 0x05,

		0x62, 0xf2, 0xed, 0x8b, 0x70, 0x68, 0x04,
		0x62, 0xf2, 0xed, 0xab, 0x70, 0x68, 0x02,
		0x62, 0xf2, 0xed, 0xcb, 0x70, 0x68, 0x01,

		0x62, 0xf2, 0x6d, 0x8b, 0x71, 0x68, 0x04,
		0x62, 0xf2, 0x6d, 0xab, 0x71, 0x68, 0x02,
		0x62, 0xf2, 0x6d, 0xcb, 0x71, 0x68, 0x01,

		0x62, 0xf2, 0xed, 0x8b, 0x71, 0x68, 0x04,
		0x62, 0xf2, 0xed, 0xab, 0x71, 0x68, 0x02,
		0x62, 0xf2, 0xed, 0xcb, 0x71, 0x68, 0x01,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(shrd)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpshrdw(xmm5|k3|T_z, xmm2, ptr [rax + 0x40], 5);
			vpshrdw(ymm5|k3|T_z, ymm2, ptr [rax + 0x40], 5);
			vpshrdw(zmm5|k3|T_z, zmm2, ptr [rax + 0x40], 5);

			vpshrdd(xmm5|k3|T_z, xmm2, ptr [rax + 0x40], 5);
			vpshrdd(ymm5|k3|T_z, ymm2, ptr [rax + 0x40], 5);
			vpshrdd(zmm5|k3|T_z, zmm2, ptr [rax + 0x40], 5);

			vpshrdq(xmm5|k3|T_z, xmm2, ptr [rax + 0x40], 5);
			vpshrdq(ymm5|k3|T_z, ymm2, ptr [rax + 0x40], 5);
			vpshrdq(zmm5|k3|T_z, zmm2, ptr [rax + 0x40], 5);

			vpshrdvw(xmm5|k3|T_z, xmm2, ptr [rax + 0x40]);
			vpshrdvw(ymm5|k3|T_z, ymm2, ptr [rax + 0x40]);
			vpshrdvw(zmm5|k3|T_z, zmm2, ptr [rax + 0x40]);

			vpshrdvd(xmm5|k3|T_z, xmm2, ptr [rax + 0x40]);
			vpshrdvd(ymm5|k3|T_z, ymm2, ptr [rax + 0x40]);
			vpshrdvd(zmm5|k3|T_z, zmm2, ptr [rax + 0x40]);

			vpshrdvq(xmm5|k3|T_z, xmm2, ptr [rax + 0x40]);
			vpshrdvq(ymm5|k3|T_z, ymm2, ptr [rax + 0x40]);
			vpshrdvq(zmm5|k3|T_z, zmm2, ptr [rax + 0x40]);

			vpshrdd(xmm5|k3|T_z, xmm2, ptr_b [rax + 0x40], 5);
			vpshrdd(ymm5|k3|T_z, ymm2, ptr_b [rax + 0x40], 5);
			vpshrdd(zmm5|k3|T_z, zmm2, ptr_b [rax + 0x40], 5);

			vpshrdq(xmm5|k3|T_z, xmm2, ptr_b [rax + 0x40], 5);
			vpshrdq(ymm5|k3|T_z, ymm2, ptr_b [rax + 0x40], 5);
			vpshrdq(zmm5|k3|T_z, zmm2, ptr_b [rax + 0x40], 5);

			vpshrdvd(xmm5|k3|T_z, xmm2, ptr_b [rax + 0x40]);
			vpshrdvd(ymm5|k3|T_z, ymm2, ptr_b [rax + 0x40]);
			vpshrdvd(zmm5|k3|T_z, zmm2, ptr_b [rax + 0x40]);

			vpshrdvq(xmm5|k3|T_z, xmm2, ptr_b [rax + 0x40]);
			vpshrdvq(ymm5|k3|T_z, ymm2, ptr_b [rax + 0x40]);
			vpshrdvq(zmm5|k3|T_z, zmm2, ptr_b [rax + 0x40]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf3, 0xed, 0x8b, 0x72, 0x68, 0x04, 0x05,
		0x62, 0xf3, 0xed, 0xab, 0x72, 0x68, 0x02, 0x05,
		0x62, 0xf3, 0xed, 0xcb, 0x72, 0x68, 0x01, 0x05,

		0x62, 0xf3, 0x6d, 0x8b, 0x73, 0x68, 0x04, 0x05,
		0x62, 0xf3, 0x6d, 0xab, 0x73, 0x68, 0x02, 0x05,
		0x62, 0xf3, 0x6d, 0xcb, 0x73, 0x68, 0x01, 0x05,

		0x62, 0xf3, 0xed, 0x8b, 0x73, 0x68, 0x04, 0x05,
		0x62, 0xf3, 0xed, 0xab, 0x73, 0x68, 0x02, 0x05,
		0x62, 0xf3, 0xed, 0xcb, 0x73, 0x68, 0x01, 0x05,

		0x62, 0xf2, 0xed, 0x8b, 0x72, 0x68, 0x04,
		0x62, 0xf2, 0xed, 0xab, 0x72, 0x68, 0x02,
		0x62, 0xf2, 0xed, 0xcb, 0x72, 0x68, 0x01,

		0x62, 0xf2, 0x6d, 0x8b, 0x73, 0x68, 0x04,
		0x62, 0xf2, 0x6d, 0xab, 0x73, 0x68, 0x02,
		0x62, 0xf2, 0x6d, 0xcb, 0x73, 0x68, 0x01,

		0x62, 0xf2, 0xed, 0x8b, 0x73, 0x68, 0x04,
		0x62, 0xf2, 0xed, 0xab, 0x73, 0x68, 0x02,
		0x62, 0xf2, 0xed, 0xcb, 0x73, 0x68, 0x01,

		0x62, 0xf3, 0x6d, 0x9b, 0x73, 0x68, 0x10, 0x05,
		0x62, 0xf3, 0x6d, 0xbb, 0x73, 0x68, 0x10, 0x05,
		0x62, 0xf3, 0x6d, 0xdb, 0x73, 0x68, 0x10, 0x05,

		0x62, 0xf3, 0xed, 0x9b, 0x73, 0x68, 0x08, 0x05,
		0x62, 0xf3, 0xed, 0xbb, 0x73, 0x68, 0x08, 0x05,
		0x62, 0xf3, 0xed, 0xdb, 0x73, 0x68, 0x08, 0x05,

		0x62, 0xf2, 0x6d, 0x9b, 0x73, 0x68, 0x10,
		0x62, 0xf2, 0x6d, 0xbb, 0x73, 0x68, 0x10,
		0x62, 0xf2, 0x6d, 0xdb, 0x73, 0x68, 0x10,

		0x62, 0xf2, 0xed, 0x9b, 0x73, 0x68, 0x08,
		0x62, 0xf2, 0xed, 0xbb, 0x73, 0x68, 0x08,
		0x62, 0xf2, 0xed, 0xdb, 0x73, 0x68, 0x08,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(vpopcnt)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpopcntb(xmm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntb(ymm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntb(zmm5|k3|T_z, ptr [rax + 0x40]);

			vpopcntw(xmm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntw(ymm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntw(zmm5|k3|T_z, ptr [rax + 0x40]);

			vpopcntd(xmm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntd(ymm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntd(zmm5|k3|T_z, ptr [rax + 0x40]);

			vpopcntd(xmm5|k3|T_z, ptr_b [rax + 0x40]);
			vpopcntd(ymm5|k3|T_z, ptr_b [rax + 0x40]);
			vpopcntd(zmm5|k3|T_z, ptr_b [rax + 0x40]);

			vpopcntq(xmm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntq(ymm5|k3|T_z, ptr [rax + 0x40]);
			vpopcntq(zmm5|k3|T_z, ptr [rax + 0x40]);

			vpopcntq(xmm5|k3|T_z, ptr_b [rax + 0x40]);
			vpopcntq(ymm5|k3|T_z, ptr_b [rax + 0x40]);
			vpopcntq(zmm5|k3|T_z, ptr_b [rax + 0x40]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf2, 0x7d, 0x8b, 0x54, 0x68, 0x04,
		0x62, 0xf2, 0x7d, 0xab, 0x54, 0x68, 0x02,
		0x62, 0xf2, 0x7d, 0xcb, 0x54, 0x68, 0x01,

		0x62, 0xf2, 0xfd, 0x8b, 0x54, 0x68, 0x04,
		0x62, 0xf2, 0xfd, 0xab, 0x54, 0x68, 0x02,
		0x62, 0xf2, 0xfd, 0xcb, 0x54, 0x68, 0x01,

		0x62, 0xf2, 0x7d, 0x8b, 0x55, 0x68, 0x04,
		0x62, 0xf2, 0x7d, 0xab, 0x55, 0x68, 0x02,
		0x62, 0xf2, 0x7d, 0xcb, 0x55, 0x68, 0x01,

		0x62, 0xf2, 0x7d, 0x9b, 0x55, 0x68, 0x10,
		0x62, 0xf2, 0x7d, 0xbb, 0x55, 0x68, 0x10,
		0x62, 0xf2, 0x7d, 0xdb, 0x55, 0x68, 0x10,

		0x62, 0xf2, 0xfd, 0x8b, 0x55, 0x68, 0x04,
		0x62, 0xf2, 0xfd, 0xab, 0x55, 0x68, 0x02,
		0x62, 0xf2, 0xfd, 0xcb, 0x55, 0x68, 0x01,

		0x62, 0xf2, 0xfd, 0x9b, 0x55, 0x68, 0x08,
		0x62, 0xf2, 0xfd, 0xbb, 0x55, 0x68, 0x08,
		0x62, 0xf2, 0xfd, 0xdb, 0x55, 0x68, 0x08,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(vpdpbus)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpdpbusd(xmm5|k3|T_z, xmm20, ptr [rax + 0x40]);
			vpdpbusd(ymm5|k3|T_z, ymm20, ptr [rax + 0x40]);
			vpdpbusd(zmm5|k3|T_z, zmm20, ptr [rax + 0x40]);

			vpdpbusd(xmm5|k3|T_z, xmm20, ptr_b [rax + 0x40]);
			vpdpbusd(ymm5|k3|T_z, ymm20, ptr_b [rax + 0x40]);
			vpdpbusd(zmm5|k3|T_z, zmm20, ptr_b [rax + 0x40]);

			vpdpbusds(xmm5|k3|T_z, xmm20, ptr [rax + 0x40]);
			vpdpbusds(ymm5|k3|T_z, ymm20, ptr [rax + 0x40]);
			vpdpbusds(zmm5|k3|T_z, zmm20, ptr [rax + 0x40]);

			vpdpbusds(xmm5|k3|T_z, xmm20, ptr_b [rax + 0x40]);
			vpdpbusds(ymm5|k3|T_z, ymm20, ptr_b [rax + 0x40]);
			vpdpbusds(zmm5|k3|T_z, zmm20, ptr_b [rax + 0x40]);

			vpdpwssd(xmm5|k3|T_z, xmm20, ptr [rax + 0x40]);
			vpdpwssd(ymm5|k3|T_z, ymm20, ptr [rax + 0x40]);
			vpdpwssd(zmm5|k3|T_z, zmm20, ptr [rax + 0x40]);

			vpdpwssd(xmm5|k3|T_z, xmm20, ptr_b [rax + 0x40]);
			vpdpwssd(ymm5|k3|T_z, ymm20, ptr_b [rax + 0x40]);
			vpdpwssd(zmm5|k3|T_z, zmm20, ptr_b [rax + 0x40]);

			vpdpwssds(xmm5|k3|T_z, xmm20, ptr [rax + 0x40]);
			vpdpwssds(ymm5|k3|T_z, ymm20, ptr [rax + 0x40]);
			vpdpwssds(zmm5|k3|T_z, zmm20, ptr [rax + 0x40]);

			vpdpwssds(xmm5|k3|T_z, xmm20, ptr_b [rax + 0x40]);
			vpdpwssds(ymm5|k3|T_z, ymm20, ptr_b [rax + 0x40]);
			vpdpwssds(zmm5|k3|T_z, zmm20, ptr_b [rax + 0x40]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf2, 0x5d, 0x83, 0x50, 0x68, 0x04,
		0x62, 0xf2, 0x5d, 0xa3, 0x50, 0x68, 0x02,
		0x62, 0xf2, 0x5d, 0xc3, 0x50, 0x68, 0x01,

		0x62, 0xf2, 0x5d, 0x93, 0x50, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xb3, 0x50, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xd3, 0x50, 0x68, 0x10,

		0x62, 0xf2, 0x5d, 0x83, 0x51, 0x68, 0x04,
		0x62, 0xf2, 0x5d, 0xa3, 0x51, 0x68, 0x02,
		0x62, 0xf2, 0x5d, 0xc3, 0x51, 0x68, 0x01,

		0x62, 0xf2, 0x5d, 0x93, 0x51, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xb3, 0x51, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xd3, 0x51, 0x68, 0x10,

		0x62, 0xf2, 0x5d, 0x83, 0x52, 0x68, 0x04,
		0x62, 0xf2, 0x5d, 0xa3, 0x52, 0x68, 0x02,
		0x62, 0xf2, 0x5d, 0xc3, 0x52, 0x68, 0x01,

		0x62, 0xf2, 0x5d, 0x93, 0x52, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xb3, 0x52, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xd3, 0x52, 0x68, 0x10,

		0x62, 0xf2, 0x5d, 0x83, 0x53, 0x68, 0x04,
		0x62, 0xf2, 0x5d, 0xa3, 0x53, 0x68, 0x02,
		0x62, 0xf2, 0x5d, 0xc3, 0x53, 0x68, 0x01,

		0x62, 0xf2, 0x5d, 0x93, 0x53, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xb3, 0x53, 0x68, 0x10,
		0x62, 0xf2, 0x5d, 0xd3, 0x53, 0x68, 0x10,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(vexpand_vpshufbitqmb)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			vpexpandb(xmm5|k3|T_z, xmm30);
			vpexpandb(ymm5|k3|T_z, ymm30);
			vpexpandb(zmm5|k3|T_z, zmm30);
			vpexpandb(xmm5|k3|T_z, ptr [rax + 0x40]);
			vpexpandb(ymm5|k3|T_z, ptr [rax + 0x40]);
			vpexpandb(zmm5|k3|T_z, ptr [rax + 0x40]);

			vpexpandw(xmm5|k3|T_z, xmm30);
			vpexpandw(ymm5|k3|T_z, ymm30);
			vpexpandw(zmm5|k3|T_z, zmm30);
			vpexpandw(xmm5|k3|T_z, ptr [rax + 0x40]);
			vpexpandw(ymm5|k3|T_z, ptr [rax + 0x40]);
			vpexpandw(zmm5|k3|T_z, ptr [rax + 0x40]);

			vpshufbitqmb(k1|k2, xmm2, ptr [rax + 0x40]);
			vpshufbitqmb(k1|k2, ymm2, ptr [rax + 0x40]);
			vpshufbitqmb(k1|k2, zmm2, ptr [rax + 0x40]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0x92, 0x7d, 0x8b, 0x62, 0xee,
		0x62, 0x92, 0x7d, 0xab, 0x62, 0xee,
		0x62, 0x92, 0x7d, 0xcb, 0x62, 0xee,
		0x62, 0xf2, 0x7d, 0x8b, 0x62, 0x68, 0x40,
		0x62, 0xf2, 0x7d, 0xab, 0x62, 0x68, 0x40,
		0x62, 0xf2, 0x7d, 0xcb, 0x62, 0x68, 0x40,

		0x62, 0x92, 0xfd, 0x8b, 0x62, 0xee,
		0x62, 0x92, 0xfd, 0xab, 0x62, 0xee,
		0x62, 0x92, 0xfd, 0xcb, 0x62, 0xee,
		0x62, 0xf2, 0xfd, 0x8b, 0x62, 0x68, 0x20,
		0x62, 0xf2, 0xfd, 0xab, 0x62, 0x68, 0x20,
		0x62, 0xf2, 0xfd, 0xcb, 0x62, 0x68, 0x20,

		0x62, 0xf2, 0x6d, 0x0a, 0x8f, 0x48, 0x04,
		0x62, 0xf2, 0x6d, 0x2a, 0x8f, 0x48, 0x02,
		0x62, 0xf2, 0x6d, 0x4a, 0x8f, 0x48, 0x01,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
CYBOZU_TEST_AUTO(gf2)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			gf2p8affineinvqb(xmm1, xmm2, 3);
			gf2p8affineinvqb(xmm1, ptr [rax + 0x40], 3);

			vgf2p8affineinvqb(xmm1, xmm5, xmm2, 3);
			vgf2p8affineinvqb(ymm1, ymm5, ymm2, 3);
			vgf2p8affineinvqb(xmm1, xmm5, ptr [rax + 0x40], 3);
			vgf2p8affineinvqb(ymm1, ymm5, ptr [rax + 0x40], 3);

			vgf2p8affineinvqb(xmm30, xmm31, xmm4, 5);
			vgf2p8affineinvqb(ymm30, ymm31, ymm4, 5);
			vgf2p8affineinvqb(zmm30, zmm31, zmm4, 5);

			vgf2p8affineinvqb(xmm30|k1|T_z, xmm5, ptr [rax + 0x40], 5);
			vgf2p8affineinvqb(ymm30|k1|T_z, ymm5, ptr [rax + 0x40], 5);
			vgf2p8affineinvqb(zmm30|k1|T_z, zmm5, ptr [rax + 0x40], 5);

			vgf2p8affineinvqb(xmm30|k1|T_z, xmm5, ptr_b [rax + 0x40], 5);
			vgf2p8affineinvqb(ymm30|k1|T_z, ymm5, ptr_b [rax + 0x40], 5);
			vgf2p8affineinvqb(zmm30|k1|T_z, zmm5, ptr_b [rax + 0x40], 5);
		}
	} c;
	const uint8_t tbl[] = {
		0x66, 0x0f, 0x3a, 0xcf, 0xca, 0x03,
		0x66, 0x0f, 0x3a, 0xcf, 0x48, 0x40, 0x03,
		0xc4, 0xe3, 0xd1, 0xcf, 0xca, 0x03,
		0xc4, 0xe3, 0xd5, 0xcf, 0xca, 0x03,
		0xc4, 0xe3, 0xd1, 0xcf, 0x48, 0x40, 0x03,
		0xc4, 0xe3, 0xd5, 0xcf, 0x48, 0x40, 0x03,
		0x62, 0x63, 0x85, 0x00, 0xcf, 0xf4, 0x05,
		0x62, 0x63, 0x85, 0x20, 0xcf, 0xf4, 0x05,
		0x62, 0x63, 0x85, 0x40, 0xcf, 0xf4, 0x05,
		0x62, 0x63, 0xd5, 0x89, 0xcf, 0x70, 0x04, 0x05,
		0x62, 0x63, 0xd5, 0xa9, 0xcf, 0x70, 0x02, 0x05,
		0x62, 0x63, 0xd5, 0xc9, 0xcf, 0x70, 0x01, 0x05,
		0x62, 0x63, 0xd5, 0x99, 0xcf, 0x70, 0x08, 0x05,
		0x62, 0x63, 0xd5, 0xb9, 0xcf, 0x70, 0x08, 0x05,
		0x62, 0x63, 0xd5, 0xd9, 0xcf, 0x70, 0x08, 0x05,
	};
	const size_t n = sizeof(tbl) / sizeof(tbl[0]);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
#endif
