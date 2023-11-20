#include <stdio.h>
#include <string.h>
#include <xbyak/xbyak.h>
#include <xbyak/xbyak_util.h>
#include <cybozu/test.hpp>

#ifndef XBYAK64
	#error "only 64-bit mode"
#endif

using namespace Xbyak;

CYBOZU_TEST_AUTO(reg_rm)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r17, ptr [rax]);
			adc(ptr [r18], rdx);
			adc(r30, rcx);
			add(r17, ptr [rax]);
			add(ptr [r18], rdx);
			add(r30, rcx);
			and_(r17, ptr [rax]);
			and_(ptr [r18], rdx);
			and_(r30, rcx);
			cmp(r17, ptr [rax]);
			cmp(ptr [r18], rdx);
			cmp(r30, rcx);
			or_(r17, ptr [rax]);
			or_(ptr [r18], rdx);
			or_(r30, rcx);
			sbb(r17, ptr [rax]);
			sbb(ptr [r18], rdx);
			sbb(r30, rcx);
			sub(r17, ptr [rax]);
			sub(ptr [r18], rdx);
			sub(r30, rcx);
			xor_(r17, ptr [rax]);
			xor_(ptr [r18], rdx);
			xor_(r30, rcx);

			add(r30, ptr [rbx+rcx*4]);
			add(rax, ptr [r30+rcx*4]);
			add(rax, ptr [rbx+r30*4]);
		}
	}  c;
	const uint8_t tbl[] = {
		0xd5, 0x48, 0x13, 0x08, 0xd5, 0x18, 0x11, 0x12, 0xd5, 0x19, 0x11, 0xce, 0xd5, 0x48, 0x03, 0x08,
		0xd5, 0x18, 0x01, 0x12, 0xd5, 0x19, 0x01, 0xce, 0xd5, 0x48, 0x23, 0x08, 0xd5, 0x18, 0x21, 0x12,
		0xd5, 0x19, 0x21, 0xce, 0xd5, 0x48, 0x3b, 0x08, 0xd5, 0x18, 0x39, 0x12, 0xd5, 0x19, 0x39, 0xce,
		0xd5, 0x48, 0x0b, 0x08, 0xd5, 0x18, 0x09, 0x12, 0xd5, 0x19, 0x09, 0xce, 0xd5, 0x48, 0x1b, 0x08,
		0xd5, 0x18, 0x19, 0x12, 0xd5, 0x19, 0x19, 0xce, 0xd5, 0x48, 0x2b, 0x08, 0xd5, 0x18, 0x29, 0x12,
		0xd5, 0x19, 0x29, 0xce, 0xd5, 0x48, 0x33, 0x08, 0xd5, 0x18, 0x31, 0x12, 0xd5, 0x19, 0x31, 0xce,
		0xd5, 0x4c, 0x03, 0x34, 0x8b, 0xd5, 0x19, 0x03, 0x04, 0x8e, 0xd5, 0x2a, 0x03, 0x04, 0xb3,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(reg64)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r30, rax); adc(r30, rcx); adc(r30, rdx); adc(r30, rbx); adc(r30, rsp); adc(r30, rbp); adc(r30, rsi); adc(r30, rdi);
			adc(r30, r8); adc(r30, r9); adc(r30, r10); adc(r30, r11); adc(r30, r12); adc(r30, r13); adc(r30, r14); adc(r30, r15);
			adc(r30, r16); adc(r30, r17); adc(r30, r18); adc(r30, r19); adc(r30, r20); adc(r30, r21); adc(r30, r22); adc(r30, r23);
			adc(r30, r24); adc(r30, r25); adc(r30, r26); adc(r30, r27); adc(r30, r28); adc(r30, r29); adc(r30, r30); adc(r30, r31);
			adc(rax, r30); adc(rcx, r30); adc(rdx, r30); adc(rbx, r30); adc(rsp, r30); adc(rbp, r30); adc(rsi, r30); adc(rdi, r30);
			adc(r8, r30); adc(r9, r30); adc(r10, r30); adc(r11, r30); adc(r12, r30); adc(r13, r30); adc(r14, r30); adc(r15, r30);
			adc(r16, r30); adc(r17, r30); adc(r18, r30); adc(r19, r30); adc(r20, r30); adc(r21, r30); adc(r22, r30); adc(r23, r30);
			adc(r24, r30); adc(r25, r30); adc(r26, r30); adc(r27, r30); adc(r28, r30); adc(r29, r30); adc(r30, r30); adc(r31, r30);
		}
	}  c;
	const uint8_t tbl[] = {
		0xd5, 0x19, 0x11, 0xc6, 0xd5, 0x19, 0x11, 0xce, 0xd5, 0x19, 0x11, 0xd6, 0xd5, 0x19, 0x11, 0xde,
		0xd5, 0x19, 0x11, 0xe6, 0xd5, 0x19, 0x11, 0xee, 0xd5, 0x19, 0x11, 0xf6, 0xd5, 0x19, 0x11, 0xfe,
		0xd5, 0x1d, 0x11, 0xc6, 0xd5, 0x1d, 0x11, 0xce, 0xd5, 0x1d, 0x11, 0xd6, 0xd5, 0x1d, 0x11, 0xde,
		0xd5, 0x1d, 0x11, 0xe6, 0xd5, 0x1d, 0x11, 0xee, 0xd5, 0x1d, 0x11, 0xf6, 0xd5, 0x1d, 0x11, 0xfe,
		0xd5, 0x59, 0x11, 0xc6, 0xd5, 0x59, 0x11, 0xce, 0xd5, 0x59, 0x11, 0xd6, 0xd5, 0x59, 0x11, 0xde,
		0xd5, 0x59, 0x11, 0xe6, 0xd5, 0x59, 0x11, 0xee, 0xd5, 0x59, 0x11, 0xf6, 0xd5, 0x59, 0x11, 0xfe,
		0xd5, 0x5d, 0x11, 0xc6, 0xd5, 0x5d, 0x11, 0xce, 0xd5, 0x5d, 0x11, 0xd6, 0xd5, 0x5d, 0x11, 0xde,
		0xd5, 0x5d, 0x11, 0xe6, 0xd5, 0x5d, 0x11, 0xee, 0xd5, 0x5d, 0x11, 0xf6, 0xd5, 0x5d, 0x11, 0xfe,
		0xd5, 0x4c, 0x11, 0xf0, 0xd5, 0x4c, 0x11, 0xf1, 0xd5, 0x4c, 0x11, 0xf2, 0xd5, 0x4c, 0x11, 0xf3,
		0xd5, 0x4c, 0x11, 0xf4, 0xd5, 0x4c, 0x11, 0xf5, 0xd5, 0x4c, 0x11, 0xf6, 0xd5, 0x4c, 0x11, 0xf7,
		0xd5, 0x4d, 0x11, 0xf0, 0xd5, 0x4d, 0x11, 0xf1, 0xd5, 0x4d, 0x11, 0xf2, 0xd5, 0x4d, 0x11, 0xf3,
		0xd5, 0x4d, 0x11, 0xf4, 0xd5, 0x4d, 0x11, 0xf5, 0xd5, 0x4d, 0x11, 0xf6, 0xd5, 0x4d, 0x11, 0xf7,
		0xd5, 0x5c, 0x11, 0xf0, 0xd5, 0x5c, 0x11, 0xf1, 0xd5, 0x5c, 0x11, 0xf2, 0xd5, 0x5c, 0x11, 0xf3,
		0xd5, 0x5c, 0x11, 0xf4, 0xd5, 0x5c, 0x11, 0xf5, 0xd5, 0x5c, 0x11, 0xf6, 0xd5, 0x5c, 0x11, 0xf7,
		0xd5, 0x5d, 0x11, 0xf0, 0xd5, 0x5d, 0x11, 0xf1, 0xd5, 0x5d, 0x11, 0xf2, 0xd5, 0x5d, 0x11, 0xf3,
		0xd5, 0x5d, 0x11, 0xf4, 0xd5, 0x5d, 0x11, 0xf5, 0xd5, 0x5d, 0x11, 0xf6, 0xd5, 0x5d, 0x11, 0xf7,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(reg32)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r30d, eax); adc(r30d, ecx); adc(r30d, edx); adc(r30d, ebx); adc(r30d, esp); adc(r30d, ebp); adc(r30d, esi); adc(r30d, edi);
			adc(r30d, r8d); adc(r30d, r9d); adc(r30d, r10d); adc(r30d, r11d); adc(r30d, r12d); adc(r30d, r13d); adc(r30d, r14d); adc(r30d, r15d);
			adc(r30d, r16d); adc(r30d, r17d); adc(r30d, r18d); adc(r30d, r19d); adc(r30d, r20d); adc(r30d, r21d); adc(r30d, r22d); adc(r30d, r23d);
			adc(r30d, r24d); adc(r30d, r25d); adc(r30d, r26d); adc(r30d, r27d); adc(r30d, r28d); adc(r30d, r29d); adc(r30d, r30d); adc(r30d, r31d);
			adc(eax, r29d); adc(ecx, r29d); adc(edx, r29d); adc(ebx, r29d); adc(esp, r29d); adc(ebp, r29d); adc(esi, r29d); adc(edi, r29d);
			adc(r8d, r29d); adc(r9d, r29d); adc(r10d, r29d); adc(r11d, r29d); adc(r12d, r29d); adc(r13d, r29d); adc(r14d, r29d); adc(r15d, r29d);
			adc(r16d, r29d); adc(r17d, r29d); adc(r18d, r29d); adc(r19d, r29d); adc(r20d, r29d); adc(r21d, r29d); adc(r22d, r29d); adc(r23d, r29d);
			adc(r24d, r29d); adc(r25d, r29d); adc(r26d, r29d); adc(r27d, r29d); adc(r28d, r29d); adc(r29d, r29d); adc(r30d, r29d); adc(r31d, r29d);
		}
	}  c;
	const uint8_t tbl[] = {
		0xd5, 0x11, 0x11, 0xc6, 0xd5, 0x11, 0x11, 0xce, 0xd5, 0x11, 0x11, 0xd6, 0xd5, 0x11, 0x11, 0xde,
		0xd5, 0x11, 0x11, 0xe6, 0xd5, 0x11, 0x11, 0xee, 0xd5, 0x11, 0x11, 0xf6, 0xd5, 0x11, 0x11, 0xfe,
		0xd5, 0x15, 0x11, 0xc6, 0xd5, 0x15, 0x11, 0xce, 0xd5, 0x15, 0x11, 0xd6, 0xd5, 0x15, 0x11, 0xde,
		0xd5, 0x15, 0x11, 0xe6, 0xd5, 0x15, 0x11, 0xee, 0xd5, 0x15, 0x11, 0xf6, 0xd5, 0x15, 0x11, 0xfe,
		0xd5, 0x51, 0x11, 0xc6, 0xd5, 0x51, 0x11, 0xce, 0xd5, 0x51, 0x11, 0xd6, 0xd5, 0x51, 0x11, 0xde,
		0xd5, 0x51, 0x11, 0xe6, 0xd5, 0x51, 0x11, 0xee, 0xd5, 0x51, 0x11, 0xf6, 0xd5, 0x51, 0x11, 0xfe,
		0xd5, 0x55, 0x11, 0xc6, 0xd5, 0x55, 0x11, 0xce, 0xd5, 0x55, 0x11, 0xd6, 0xd5, 0x55, 0x11, 0xde,
		0xd5, 0x55, 0x11, 0xe6, 0xd5, 0x55, 0x11, 0xee, 0xd5, 0x55, 0x11, 0xf6, 0xd5, 0x55, 0x11, 0xfe,
		0xd5, 0x44, 0x11, 0xe8, 0xd5, 0x44, 0x11, 0xe9, 0xd5, 0x44, 0x11, 0xea, 0xd5, 0x44, 0x11, 0xeb,
		0xd5, 0x44, 0x11, 0xec, 0xd5, 0x44, 0x11, 0xed, 0xd5, 0x44, 0x11, 0xee, 0xd5, 0x44, 0x11, 0xef,
		0xd5, 0x45, 0x11, 0xe8, 0xd5, 0x45, 0x11, 0xe9, 0xd5, 0x45, 0x11, 0xea, 0xd5, 0x45, 0x11, 0xeb,
		0xd5, 0x45, 0x11, 0xec, 0xd5, 0x45, 0x11, 0xed, 0xd5, 0x45, 0x11, 0xee, 0xd5, 0x45, 0x11, 0xef,
		0xd5, 0x54, 0x11, 0xe8, 0xd5, 0x54, 0x11, 0xe9, 0xd5, 0x54, 0x11, 0xea, 0xd5, 0x54, 0x11, 0xeb,
		0xd5, 0x54, 0x11, 0xec, 0xd5, 0x54, 0x11, 0xed, 0xd5, 0x54, 0x11, 0xee, 0xd5, 0x54, 0x11, 0xef,
		0xd5, 0x55, 0x11, 0xe8, 0xd5, 0x55, 0x11, 0xe9, 0xd5, 0x55, 0x11, 0xea, 0xd5, 0x55, 0x11, 0xeb,
		0xd5, 0x55, 0x11, 0xec, 0xd5, 0x55, 0x11, 0xed, 0xd5, 0x55, 0x11, 0xee, 0xd5, 0x55, 0x11, 0xef,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(reg16)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r30w, ax); adc(r30w, cx); adc(r30w, dx); adc(r30w, bx); adc(r30w, sp); adc(r30w, bp); adc(r30w, si); adc(r30w, di);
			adc(r30w, r8w); adc(r30w, r9w); adc(r30w, r10w); adc(r30w, r11w); adc(r30w, r12w); adc(r30w, r13w); adc(r30w, r14w); adc(r30w, r15w);
			adc(r30w, r16w); adc(r30w, r17w); adc(r30w, r18w); adc(r30w, r19w); adc(r30w, r20w); adc(r30w, r21w); adc(r30w, r22w); adc(r30w, r23w);
			adc(r30w, r24w); adc(r30w, r25w); adc(r30w, r26w); adc(r30w, r27w); adc(r30w, r28w); adc(r30w, r29w); adc(r30w, r30w); adc(r30w, r31w);
			adc(ax, r29w); adc(cx, r29w); adc(dx, r29w); adc(bx, r29w); adc(sp, r29w); adc(bp, r29w); adc(si, r29w); adc(di, r29w);
			adc(r8w, r29w); adc(r9w, r29w); adc(r10w, r29w); adc(r11w, r29w); adc(r12w, r29w); adc(r13w, r29w); adc(r14w, r29w); adc(r15w, r29w);
			adc(r16w, r29w); adc(r17w, r29w); adc(r18w, r29w); adc(r19w, r29w); adc(r20w, r29w); adc(r21w, r29w); adc(r22w, r29w); adc(r23w, r29w);
			adc(r24w, r29w); adc(r25w, r29w); adc(r26w, r29w); adc(r27w, r29w); adc(r28w, r29w); adc(r29w, r29w); adc(r30w, r29w); adc(r31w, r29w);
		}
	}  c;
	const uint8_t tbl[] = {
		0x66, 0xd5, 0x11, 0x11, 0xc6, 0x66, 0xd5, 0x11, 0x11, 0xce, 0x66, 0xd5, 0x11, 0x11, 0xd6, 0x66,
		0xd5, 0x11, 0x11, 0xde, 0x66, 0xd5, 0x11, 0x11, 0xe6, 0x66, 0xd5, 0x11, 0x11, 0xee, 0x66, 0xd5,
		0x11, 0x11, 0xf6, 0x66, 0xd5, 0x11, 0x11, 0xfe, 0x66, 0xd5, 0x15, 0x11, 0xc6, 0x66, 0xd5, 0x15,
		0x11, 0xce, 0x66, 0xd5, 0x15, 0x11, 0xd6, 0x66, 0xd5, 0x15, 0x11, 0xde, 0x66, 0xd5, 0x15, 0x11,
		0xe6, 0x66, 0xd5, 0x15, 0x11, 0xee, 0x66, 0xd5, 0x15, 0x11, 0xf6, 0x66, 0xd5, 0x15, 0x11, 0xfe,
		0x66, 0xd5, 0x51, 0x11, 0xc6, 0x66, 0xd5, 0x51, 0x11, 0xce, 0x66, 0xd5, 0x51, 0x11, 0xd6, 0x66,
		0xd5, 0x51, 0x11, 0xde, 0x66, 0xd5, 0x51, 0x11, 0xe6, 0x66, 0xd5, 0x51, 0x11, 0xee, 0x66, 0xd5,
		0x51, 0x11, 0xf6, 0x66, 0xd5, 0x51, 0x11, 0xfe, 0x66, 0xd5, 0x55, 0x11, 0xc6, 0x66, 0xd5, 0x55,
		0x11, 0xce, 0x66, 0xd5, 0x55, 0x11, 0xd6, 0x66, 0xd5, 0x55, 0x11, 0xde, 0x66, 0xd5, 0x55, 0x11,
		0xe6, 0x66, 0xd5, 0x55, 0x11, 0xee, 0x66, 0xd5, 0x55, 0x11, 0xf6, 0x66, 0xd5, 0x55, 0x11, 0xfe,
		0x66, 0xd5, 0x44, 0x11, 0xe8, 0x66, 0xd5, 0x44, 0x11, 0xe9, 0x66, 0xd5, 0x44, 0x11, 0xea, 0x66,
		0xd5, 0x44, 0x11, 0xeb, 0x66, 0xd5, 0x44, 0x11, 0xec, 0x66, 0xd5, 0x44, 0x11, 0xed, 0x66, 0xd5,
		0x44, 0x11, 0xee, 0x66, 0xd5, 0x44, 0x11, 0xef, 0x66, 0xd5, 0x45, 0x11, 0xe8, 0x66, 0xd5, 0x45,
		0x11, 0xe9, 0x66, 0xd5, 0x45, 0x11, 0xea, 0x66, 0xd5, 0x45, 0x11, 0xeb, 0x66, 0xd5, 0x45, 0x11,
		0xec, 0x66, 0xd5, 0x45, 0x11, 0xed, 0x66, 0xd5, 0x45, 0x11, 0xee, 0x66, 0xd5, 0x45, 0x11, 0xef,
		0x66, 0xd5, 0x54, 0x11, 0xe8, 0x66, 0xd5, 0x54, 0x11, 0xe9, 0x66, 0xd5, 0x54, 0x11, 0xea, 0x66,
		0xd5, 0x54, 0x11, 0xeb, 0x66, 0xd5, 0x54, 0x11, 0xec, 0x66, 0xd5, 0x54, 0x11, 0xed, 0x66, 0xd5,
		0x54, 0x11, 0xee, 0x66, 0xd5, 0x54, 0x11, 0xef, 0x66, 0xd5, 0x55, 0x11, 0xe8, 0x66, 0xd5, 0x55,
		0x11, 0xe9, 0x66, 0xd5, 0x55, 0x11, 0xea, 0x66, 0xd5, 0x55, 0x11, 0xeb, 0x66, 0xd5, 0x55, 0x11,
		0xec, 0x66, 0xd5, 0x55, 0x11, 0xed, 0x66, 0xd5, 0x55, 0x11, 0xee, 0x66, 0xd5, 0x55, 0x11, 0xef,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(reg8)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r17b, al); adc(r17b, cl); adc(r17b, dl); adc(r17b, bl); adc(r17b, spl); adc(r17b, bpl); adc(r17b, sil); adc(r17b, dil);
			adc(r17b, r8b); adc(r17b, r9b); adc(r17b, r10b); adc(r17b, r11b); adc(r17b, r12b); adc(r17b, r13b); adc(r17b, r14b); adc(r17b, r15b);
			adc(r17b, r16b); adc(r17b, r17b); adc(r17b, r18b); adc(r17b, r19b); adc(r17b, r20b); adc(r17b, r21b); adc(r17b, r22b); adc(r17b, r23b);
			adc(r17b, r24b); adc(r17b, r25b); adc(r17b, r26b); adc(r17b, r27b); adc(r17b, r28b); adc(r17b, r29b); adc(r17b, r30b); adc(r17b, r31b);
			adc(al, r20b); adc(cl, r20b); adc(dl, r20b); adc(bl, r20b); adc(spl, r20b); adc(bpl, r20b); adc(sil, r20b); adc(dil, r20b);
			adc(r8b, r20b); adc(r9b, r20b); adc(r10b, r20b); adc(r11b, r20b); adc(r12b, r20b); adc(r13b, r20b); adc(r14b, r20b); adc(r15b, r20b);
			adc(r16b, r20b); adc(r17b, r20b); adc(r18b, r20b); adc(r19b, r20b); adc(r20b, r20b); adc(r21b, r20b); adc(r22b, r20b); adc(r23b, r20b);
			adc(r24b, r20b); adc(r25b, r20b); adc(r26b, r20b); adc(r27b, r20b); adc(r28b, r20b); adc(r29b, r20b); adc(r30b, r20b); adc(r31b, r20b);
		}
	}  c;
	const uint8_t tbl[] = {
		0xd5, 0x10, 0x10, 0xc1, 0xd5, 0x10, 0x10, 0xc9, 0xd5, 0x10, 0x10, 0xd1, 0xd5, 0x10, 0x10, 0xd9,
		0xd5, 0x10, 0x10, 0xe1, 0xd5, 0x10, 0x10, 0xe9, 0xd5, 0x10, 0x10, 0xf1, 0xd5, 0x10, 0x10, 0xf9,
		0xd5, 0x14, 0x10, 0xc1, 0xd5, 0x14, 0x10, 0xc9, 0xd5, 0x14, 0x10, 0xd1, 0xd5, 0x14, 0x10, 0xd9,
		0xd5, 0x14, 0x10, 0xe1, 0xd5, 0x14, 0x10, 0xe9, 0xd5, 0x14, 0x10, 0xf1, 0xd5, 0x14, 0x10, 0xf9,
		0xd5, 0x50, 0x10, 0xc1, 0xd5, 0x50, 0x10, 0xc9, 0xd5, 0x50, 0x10, 0xd1, 0xd5, 0x50, 0x10, 0xd9,
		0xd5, 0x50, 0x10, 0xe1, 0xd5, 0x50, 0x10, 0xe9, 0xd5, 0x50, 0x10, 0xf1, 0xd5, 0x50, 0x10, 0xf9,
		0xd5, 0x54, 0x10, 0xc1, 0xd5, 0x54, 0x10, 0xc9, 0xd5, 0x54, 0x10, 0xd1, 0xd5, 0x54, 0x10, 0xd9,
		0xd5, 0x54, 0x10, 0xe1, 0xd5, 0x54, 0x10, 0xe9, 0xd5, 0x54, 0x10, 0xf1, 0xd5, 0x54, 0x10, 0xf9,
		0xd5, 0x40, 0x10, 0xe0, 0xd5, 0x40, 0x10, 0xe1, 0xd5, 0x40, 0x10, 0xe2, 0xd5, 0x40, 0x10, 0xe3,
		0xd5, 0x40, 0x10, 0xe4, 0xd5, 0x40, 0x10, 0xe5, 0xd5, 0x40, 0x10, 0xe6, 0xd5, 0x40, 0x10, 0xe7,
		0xd5, 0x41, 0x10, 0xe0, 0xd5, 0x41, 0x10, 0xe1, 0xd5, 0x41, 0x10, 0xe2, 0xd5, 0x41, 0x10, 0xe3,
		0xd5, 0x41, 0x10, 0xe4, 0xd5, 0x41, 0x10, 0xe5, 0xd5, 0x41, 0x10, 0xe6, 0xd5, 0x41, 0x10, 0xe7,
		0xd5, 0x50, 0x10, 0xe0, 0xd5, 0x50, 0x10, 0xe1, 0xd5, 0x50, 0x10, 0xe2, 0xd5, 0x50, 0x10, 0xe3,
		0xd5, 0x50, 0x10, 0xe4, 0xd5, 0x50, 0x10, 0xe5, 0xd5, 0x50, 0x10, 0xe6, 0xd5, 0x50, 0x10, 0xe7,
		0xd5, 0x51, 0x10, 0xe0, 0xd5, 0x51, 0x10, 0xe1, 0xd5, 0x51, 0x10, 0xe2, 0xd5, 0x51, 0x10, 0xe3,
		0xd5, 0x51, 0x10, 0xe4, 0xd5, 0x51, 0x10, 0xe5, 0xd5, 0x51, 0x10, 0xe6, 0xd5, 0x51, 0x10, 0xe7,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(rm)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r16, ptr [r17+0x40]);
			adc(ptr [r17+0x40], r16);
			adc(r16d, ptr [r17+0x40]);
			adc(ptr [r17+0x40], r16d);
			adc(r16w, ptr [r17+0x40]);
			adc(ptr [r17+0x40], r16w);
			adc(r16b, ptr [r17+0x40]);
			adc(ptr [r17+0x40], r16b);
			adc(r16, ptr [r18*4+0x40]);
			adc(ptr [r18*4+0x40], r16);
			adc(r16d, ptr [r18*4+0x40]);
			adc(ptr [r18*4+0x40], r16d);
			adc(r16w, ptr [r18*4+0x40]);
			adc(ptr [r18*4+0x40], r16w);
			adc(r16b, ptr [r18*4+0x40]);
			adc(ptr [r18*4+0x40], r16b);
			adc(r16, ptr [r17+r18*4+0x40]);
			adc(ptr [r17+r18*4+0x40], r16);
			adc(r16d, ptr [r17+r18*4+0x40]);
			adc(ptr [r17+r18*4+0x40], r16d);
			adc(r16w, ptr [r17+r18*4+0x40]);
			adc(ptr [r17+r18*4+0x40], r16w);
			adc(r16b, ptr [r17+r18*4+0x40]);
			adc(ptr [r17+r18*4+0x40], r16b);
		}
	}  c;
	const uint8_t tbl[] = {
		0xd5, 0x58, 0x13, 0x41, 0x40, 0xd5, 0x58, 0x11, 0x41, 0x40, 0xd5, 0x50, 0x13, 0x41, 0x40, 0xd5,
		0x50, 0x11, 0x41, 0x40, 0x66, 0xd5, 0x50, 0x13, 0x41, 0x40, 0x66, 0xd5, 0x50, 0x11, 0x41, 0x40,
		0xd5, 0x50, 0x12, 0x41, 0x40, 0xd5, 0x50, 0x10, 0x41, 0x40, 0xd5, 0x68, 0x13, 0x04, 0x95, 0x40,
		0x00, 0x00, 0x00, 0xd5, 0x68, 0x11, 0x04, 0x95, 0x40, 0x00, 0x00, 0x00, 0xd5, 0x60, 0x13, 0x04,
		0x95, 0x40, 0x00, 0x00, 0x00, 0xd5, 0x60, 0x11, 0x04, 0x95, 0x40, 0x00, 0x00, 0x00, 0x66, 0xd5,
		0x60, 0x13, 0x04, 0x95, 0x40, 0x00, 0x00, 0x00, 0x66, 0xd5, 0x60, 0x11, 0x04, 0x95, 0x40, 0x00,
		0x00, 0x00, 0xd5, 0x60, 0x12, 0x04, 0x95, 0x40, 0x00, 0x00, 0x00, 0xd5, 0x60, 0x10, 0x04, 0x95,
		0x40, 0x00, 0x00, 0x00, 0xd5, 0x78, 0x13, 0x44, 0x91, 0x40, 0xd5, 0x78, 0x11, 0x44, 0x91, 0x40,
		0xd5, 0x70, 0x13, 0x44, 0x91, 0x40, 0xd5, 0x70, 0x11, 0x44, 0x91, 0x40, 0x66, 0xd5, 0x70, 0x13,
		0x44, 0x91, 0x40, 0x66, 0xd5, 0x70, 0x11, 0x44, 0x91, 0x40, 0xd5, 0x70, 0x12, 0x44, 0x91, 0x40,
		0xd5, 0x70, 0x10, 0x44, 0x91, 0x40,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(r3)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r20b, r21b, r23b);
			adc(r20w, r21w, r23w);
			adc(r20d, r21d, r23d);
			adc(r20, r21, r23);
	}
	}  c;
	const uint8_t tbl[] = {
		0x62, 0xec, 0x5c, 0x10, 0x10, 0xfd, 0x62, 0xec, 0x5d, 0x10, 0x11, 0xfd, 0x62, 0xec, 0x5c, 0x10,
		0x11, 0xfd, 0x62, 0xec, 0xdc, 0x10, 0x11, 0xfd,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(rm3)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(rax, r18, ptr [rbx+rcx*4+0x123]);
			adc(rax, ptr [rbx+rcx*4+0x123], r20);
			adc(rax, ptr [r30], r29);
			adc(r11, r13, ptr [r10]);
			adc(r11, r13, ptr [r10*4]);
			adc(r11, ptr [r10*8], r9);
		}
	}  c;
	const uint8_t tbl[] = {
		0x62, 0xe4, 0xfc, 0x18, 0x13, 0x94, 0x8b, 0x23, 0x01, 0x00, 0x00, 0x62, 0xe4, 0xfc, 0x18, 0x11,
		0xa4, 0x8b, 0x23, 0x01, 0x00, 0x00, 0x62, 0x4c, 0xfc, 0x18, 0x11, 0x2e, 0x62, 0x54, 0xa4, 0x18,
		0x13, 0x2a, 0x62, 0x34, 0xa4, 0x18, 0x13, 0x2c, 0x95, 0x00, 0x00, 0x00, 0x00, 0x62, 0x34, 0xa4,
		0x18, 0x11, 0x0c, 0xd5, 0x00, 0x00, 0x00, 0x00,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(rm3_2)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adc(r20b, r21b, r23b);
			adc(r20w, r21w, r23w);
			adc(r20d, r21d, r23d);
			adc(r20, r21, r23);
			adc(r20b, ptr [rax+rcx*4+0x7fffffff], 0x12);
			adc(r20w, ptr [rax+rcx*4+0x7fffffff], 0x1234);
			adc(r20d, ptr [rax+rcx*4+0x7fffffff], 0x12345678);
			adc(r20, ptr [rax+rcx*4+0x7fffffff], 0x12345678);
			adc(r20b, al, 0x12);
			adc(r20w, ax, 0x1234);
			adc(r20d, eax, 0x12345678);
			adc(r20, rax, 0x12345678);
		}
	}  c;
	const uint8_t tbl[] = {
		0x62, 0xec, 0x5c, 0x10, 0x10, 0xfd, 0x62, 0xec, 0x5d, 0x10, 0x11, 0xfd, 0x62, 0xec, 0x5c, 0x10,
		0x11, 0xfd, 0x62, 0xec, 0xdc, 0x10, 0x11, 0xfd, 0x62, 0xf4, 0x5c, 0x10, 0x80, 0x94, 0x88, 0xff,
		0xff, 0xff, 0x7f, 0x12, 0x62, 0xf4, 0x5d, 0x10, 0x81, 0x94, 0x88, 0xff, 0xff, 0xff, 0x7f, 0x34,
		0x12, 0x62, 0xf4, 0x5c, 0x10, 0x81, 0x94, 0x88, 0xff, 0xff, 0xff, 0x7f, 0x78, 0x56, 0x34, 0x12,
		0x62, 0xf4, 0xdc, 0x10, 0x81, 0x94, 0x88, 0xff, 0xff, 0xff, 0x7f, 0x78, 0x56, 0x34, 0x12, 0x62,
		0xf4, 0x5c, 0x10, 0x80, 0xd0, 0x12, 0x62, 0xf4, 0x5d, 0x10, 0x81, 0xd0, 0x34, 0x12, 0x62, 0xf4,
		0x5c, 0x10, 0x81, 0xd0, 0x78, 0x56, 0x34, 0x12, 0x62, 0xf4, 0xdc, 0x10, 0x81, 0xd0, 0x78, 0x56,
		0x34, 0x12,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(adcx_adox)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			adcx(rax, r30);
			adcx(ecx, r20d);
			adcx(ecx, ptr [r31+r29*4]);
			adcx(r20d, ptr [rax]);
			adcx(r16, ptr [r31+r29*4]);
			adcx(r17, ptr [rax]);
			adcx(rax, rcx, rdx);

			adox(rax, r30);
			adox(ecx, r20d);
			adox(ecx, ptr [r31+r29*4]);
			adox(r20d, ptr [rax]);
			adox(r16, ptr [r31+r29*4]);
			adox(r17, ptr [rax]);
			adox(rax, rcx, rdx);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xdc, 0xfd, 0x08, 0x66, 0xc6, 0x62, 0xfc, 0x7d, 0x08, 0x66, 0xcc, 0x62, 0x9c, 0x79, 0x08,
		0x66, 0x0c, 0xaf, 0x62, 0xe4, 0x7d, 0x08, 0x66, 0x20, 0x62, 0x8c, 0xf9, 0x08, 0x66, 0x04, 0xaf,
		0x62, 0xe4, 0xfd, 0x08, 0x66, 0x08, 0x62, 0xf4, 0xfd, 0x18, 0x66, 0xca,

		0x62, 0xdc, 0xfe, 0x08, 0x66, 0xc6, 0x62, 0xfc, 0x7e, 0x08, 0x66, 0xcc, 0x62, 0x9c, 0x7a, 0x08,
		0x66, 0x0c, 0xaf, 0x62, 0xe4, 0x7e, 0x08, 0x66, 0x20, 0x62, 0x8c, 0xfa, 0x08, 0x66, 0x04, 0xaf,
		0x62, 0xe4, 0xfe, 0x08, 0x66, 0x08, 0x62, 0xf4, 0xfe, 0x18, 0x66, 0xca,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(r3_2)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			add(rax, rcx, rdx);
			adc(rax, rcx, rdx);
			and_(rax, rcx, rdx);
			or_(rax, rcx, rdx);
			sbb(rax, rcx, rdx);
			sub(rax, rcx, rdx);
			xor_(rax, rcx, rdx);
			add(r30, ptr [r20], r9);
			adc(r30, ptr [r20], r9);
			and_(r30, ptr [r20], r9);
			or_(r30, ptr [r20], r9);
			sbb(r30, ptr [r20], r9);
			sub(r30, ptr [r20], r9);
			xor_(r30, ptr [r20], r9);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf4, 0xfc, 0x18, 0x01, 0xd1, 0x62, 0xf4, 0xfc, 0x18, 0x11, 0xd1, 0x62, 0xf4, 0xfc, 0x18,
		0x21, 0xd1, 0x62, 0xf4, 0xfc, 0x18, 0x09, 0xd1, 0x62, 0xf4, 0xfc, 0x18, 0x19, 0xd1, 0x62, 0xf4,
		0xfc, 0x18, 0x29, 0xd1, 0x62, 0xf4, 0xfc, 0x18, 0x31, 0xd1, 0x62, 0x7c, 0x8c, 0x10, 0x01, 0x0c,
		0x24, 0x62, 0x7c, 0x8c, 0x10, 0x11, 0x0c, 0x24, 0x62, 0x7c, 0x8c, 0x10, 0x21, 0x0c, 0x24, 0x62,
		0x7c, 0x8c, 0x10, 0x09, 0x0c, 0x24, 0x62, 0x7c, 0x8c, 0x10, 0x19, 0x0c, 0x24, 0x62, 0x7c, 0x8c,
		0x10, 0x29, 0x0c, 0x24, 0x62, 0x7c, 0x8c, 0x10, 0x31, 0x0c, 0x24,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(NF)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			add(rax, rcx, rdx);
			add(rax|T_nf, rcx, rdx);
			and_(rax, rcx, rdx);
			and_(rax|T_nf, rcx, rdx);
			or_(rax, rcx, rdx);
			or_(rax|T_nf, rcx, rdx);
			sub(rax, rcx, rdx);
			sub(rax|T_nf, rcx, rdx);
			xor_(rax, rcx, rdx);
			xor_(rax|T_nf, rcx, rdx);

			add(rax, rcx, 3);
			add(rax|T_nf, rcx, 3);
			and_(rax, rcx, 3);
			and_(rax|T_nf, rcx, 3);
			or_(rax, rcx, 3);
			or_(rax|T_nf, rcx, 3);
			sub(rax, rcx, 3);
			sub(rax|T_nf, rcx, 3);
			xor_(rax, rcx, 3);
			xor_(rax|T_nf, rcx, 3);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf4, 0xfc, 0x18, 0x01, 0xd1,
		0x62, 0xf4, 0xfc, 0x1c, 0x01, 0xd1,

		0x62, 0xf4, 0xfc, 0x18, 0x21, 0xd1,
		0x62, 0xf4, 0xfc, 0x1c, 0x21, 0xd1,

		0x62, 0xf4, 0xfc, 0x18, 0x09, 0xd1,
		0x62, 0xf4, 0xfc, 0x1c, 0x09, 0xd1,

		0x62, 0xf4, 0xfc, 0x18, 0x29, 0xd1,
		0x62, 0xf4, 0xfc, 0x1c, 0x29, 0xd1,

		0x62, 0xf4, 0xfc, 0x18, 0x31, 0xd1,
		0x62, 0xf4, 0xfc, 0x1c, 0x31, 0xd1,

		0x62, 0xf4, 0xfc, 0x18, 0x83, 0xc1, 0x03,
		0x62, 0xf4, 0xfc, 0x1c, 0x83, 0xc1, 0x03,

		0x62, 0xf4, 0xfc, 0x18, 0x83, 0xe1, 0x03,
		0x62, 0xf4, 0xfc, 0x1c, 0x83, 0xe1, 0x03,

		0x62, 0xf4, 0xfc, 0x18, 0x83, 0xc9, 0x03,
		0x62, 0xf4, 0xfc, 0x1c, 0x83, 0xc9, 0x03,

		0x62, 0xf4, 0xfc, 0x18, 0x83, 0xe9, 0x03,
		0x62, 0xf4, 0xfc, 0x1c, 0x83, 0xe9, 0x03,

		0x62, 0xf4, 0xfc, 0x18, 0x83, 0xf1, 0x03,
		0x62, 0xf4, 0xfc, 0x1c, 0x83, 0xf1, 0x03,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(andn_etc)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			andn(r29, r30, r31);
			andn(r29|T_nf, r30, r31);
			andn(eax, ecx, r17d); // 32bit
			andn(r29, r30, ptr [r31+r20*4]);

			mulx(eax, ecx, r17d);
			mulx(r29, r30, r31);
			mulx(r29, r30, ptr [r31+r20*4]);
			pdep(eax, ecx, r17d);
			pdep(r29, r30, r31);
			pdep(r29, r30, ptr [r31+r20*4]);
			pext(eax, ecx, r17d);
			pext(r29, r30, r31);
			pext(r29, r30, ptr [r31+r20*4]);

		}
	} c;
	const uint8_t tbl[] = {
		// andn
		0x62, 0x4a, 0x8c, 0x00, 0xf2, 0xef,
		0x62, 0x4a, 0x8c, 0x04, 0xf2, 0xef,
		0x62, 0xfa, 0x74, 0x08, 0xf2, 0xc1,
		0x62, 0x4a, 0x88, 0x00, 0xf2, 0x2c, 0xa7,

		// mulx, pdep, pext
		0x62, 0xfa, 0x77, 0x08, 0xf6, 0xc1, 0x62, 0x4a, 0x8f, 0x00, 0xf6, 0xef, 0x62, 0x4a, 0x8b, 0x00, 0xf6, 0x2c, 0xa7,
		0x62, 0xfa, 0x77, 0x08, 0xf5, 0xc1, 0x62, 0x4a, 0x8f, 0x00, 0xf5, 0xef, 0x62, 0x4a, 0x8b, 0x00, 0xf5, 0x2c, 0xa7,
		0x62, 0xfa, 0x76, 0x08, 0xf5, 0xc1, 0x62, 0x4a, 0x8e, 0x00, 0xf5, 0xef, 0x62, 0x4a, 0x8a, 0x00, 0xf5, 0x2c, 0xa7,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(bextr_etc)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			bextr(r29, r30, r31);
			bextr(r29|T_nf, r30, r31);
			bextr(eax, ecx, r17d);
			bextr(r29, ptr [r31+r20*4], r30);

			bzhi(r29, r30, r31);
			bzhi(r29|T_nf, r30, r31);
			bzhi(eax, ecx, r17d);
			bzhi(r29, ptr [r31+r20*4], r30);

			sarx(r29, r30, r31);
			sarx(eax, ecx, r17d);
			sarx(r29, ptr [r31+r20*4], r30);

			shlx(r29, r30, r31);
			shlx(eax, ecx, r17d);
			shlx(r29, ptr [r31+r20*4], r30);

			shrx(r29, r30, r31);
			shrx(eax, ecx, r17d);
			shrx(r29, ptr [r31+r20*4], r30);

			blsi(r30, r31);
			blsi(r30|T_nf, r31);
			blsi(ecx, r17d);
			blsi(r30, ptr [r31+r20*4]);

			blsmsk(r30, r31);
			blsmsk(r30|T_nf, r31);
			blsmsk(ecx, r17d);
			blsmsk(r30, ptr [r31+r20*4]);

			blsr(r30, r31);
			blsr(r30|T_nf, r31);
			blsr(ecx, r17d);
			blsr(r30, ptr [r31+r20*4]);

			rorx(r30, r31, 3);
			rorx(ecx, r17d, 5);
			rorx(r30, ptr [r31+r20*4], 4);
		}
	} c;
	const uint8_t tbl[] = {
		// bextr
		0x62, 0x4a, 0x84, 0x00, 0xf7, 0xee,
		0x62, 0x4a, 0x84, 0x04, 0xf7, 0xee,
		0x62, 0xf2, 0x74, 0x00, 0xf7, 0xc1,
		0x62, 0x4a, 0x88, 0x00, 0xf7, 0x2c, 0xa7,

		// bzhi
		0x62, 0x4a, 0x84, 0x00, 0xf5, 0xee,
		0x62, 0x4a, 0x84, 0x04, 0xf5, 0xee,
		0x62, 0xf2, 0x74, 0x00, 0xf5, 0xc1,
		0x62, 0x4a, 0x88, 0x00, 0xf5, 0x2c, 0xa7,

		// sarx
		0x62, 0x4a, 0x86, 0x00, 0xf7, 0xee,
		0x62, 0xf2, 0x76, 0x00, 0xf7, 0xc1,
		0x62, 0x4a, 0x8a, 0x00, 0xf7, 0x2c, 0xa7,

		// shlx
		0x62, 0x4a, 0x85, 0x00, 0xf7, 0xee,
		0x62, 0xf2, 0x75, 0x00, 0xf7, 0xc1,
		0x62, 0x4a, 0x89, 0x00, 0xf7, 0x2c, 0xa7,

		// shrx
		0x62, 0x4a, 0x87, 0x00, 0xf7, 0xee,
		0x62, 0xf2, 0x77, 0x00, 0xf7, 0xc1,
		0x62, 0x4a, 0x8b, 0x00, 0xf7, 0x2c, 0xa7,

		// blsi
		0x62, 0xda, 0x8c, 0x00, 0xf3, 0xdf,
		0x62, 0xda, 0x8c, 0x04, 0xf3, 0xdf,
		0x62, 0xfa, 0x74, 0x08, 0xf3, 0xd9,
		0x62, 0xda, 0x88, 0x00, 0xf3, 0x1c, 0xa7,

		// blsmsk
		0x62, 0xda, 0x8c, 0x00, 0xf3, 0xd7,
		0x62, 0xda, 0x8c, 0x04, 0xf3, 0xd7,
		0x62, 0xfa, 0x74, 0x08, 0xf3, 0xd1,
		0x62, 0xda, 0x88, 0x00, 0xf3, 0x14, 0xa7,

		// blsr
		0x62, 0xda, 0x8c, 0x00, 0xf3, 0xcf,
		0x62, 0xda, 0x8c, 0x04, 0xf3, 0xcf,
		0x62, 0xfa, 0x74, 0x08, 0xf3, 0xc9,
		0x62, 0xda, 0x88, 0x00, 0xf3, 0x0c, 0xa7,

		// rorx
		0x62, 0x4b, 0xff, 0x08, 0xf0, 0xf7, 0x03,
		0x62, 0xfb, 0x7f, 0x08, 0xf0, 0xc9, 0x05,
		0x62, 0x4b, 0xfb, 0x08, 0xf0, 0x34, 0xa7, 0x04,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(bit)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			// adc
			adc(r20b, r21b, r22b);
			adc(r20w, r21w, r22w);
			adc(r20d, r21d, r22d);
			adc(r20, r21, r22);

			adc(r20b, r21b);
			adc(r20w, r21w);
			adc(r20d, r21d);
			adc(r20, r21);

			adc(r20b, r21b, 0x3);
			adc(r20w, r21w, 0x3);
			adc(r20d, r21d, 0x3);
			adc(r20, r21, 0x3);

			adc(r20b, 0x3);
			adc(r20w, 0x3);
			adc(r20d, 0x3);
			adc(r20, 0x3);

			// add
			add(r20b, r21b, r22b);
			add(r20w, r21w, r22w);
			add(r20d, r21d, r22d);
			add(r20, r21, r22);
			add(r20b, r21b);
			add(r20w, r21w);
			add(r20d, r21d);
			add(r20, r21);
			add(r20b, r21b, 0x3);
			add(r20w, r21w, 0x3);
			add(r20d, r21d, 0x3);
			add(r20, r21, 0x3);
			add(r20b, 0x3);
			add(r20w, 0x3);
			add(r20d, 0x3);
			add(r20, 0x3);
		}
	} c;
	const uint8_t tbl[] = {
		// adc
		0x62, 0xec, 0x5c, 0x10, 0x10, 0xf5, 0x62, 0xec, 0x5d, 0x10, 0x11, 0xf5, 0x62, 0xec, 0x5c, 0x10,
		0x11, 0xf5, 0x62, 0xec, 0xdc, 0x10, 0x11, 0xf5, 0xd5, 0x50, 0x10, 0xec, 0x66, 0xd5, 0x50, 0x11,
		0xec, 0xd5, 0x50, 0x11, 0xec, 0xd5, 0x58, 0x11, 0xec, 0x62, 0xfc, 0x5c, 0x10, 0x80, 0xd5, 0x03,
		0x62, 0xfc, 0x5d, 0x10, 0x83, 0xd5, 0x03, 0x62, 0xfc, 0x5c, 0x10, 0x83, 0xd5, 0x03, 0x62, 0xfc,
		0xdc, 0x10, 0x83, 0xd5, 0x03, 0xd5, 0x10, 0x80, 0xd4, 0x03, 0x66, 0xd5, 0x10, 0x83, 0xd4, 0x03,
		0xd5, 0x10, 0x83, 0xd4, 0x03, 0xd5, 0x18, 0x83, 0xd4, 0x03,

		// add
		0x62, 0xec, 0x5c, 0x10, 0x00, 0xf5, 0x62, 0xec, 0x5d, 0x10, 0x01, 0xf5, 0x62, 0xec, 0x5c, 0x10,
		0x01, 0xf5, 0x62, 0xec, 0xdc, 0x10, 0x01, 0xf5, 0xd5, 0x50, 0x00, 0xec, 0x66, 0xd5, 0x50, 0x01,
		0xec, 0xd5, 0x50, 0x01, 0xec, 0xd5, 0x58, 0x01, 0xec, 0x62, 0xfc, 0x5c, 0x10, 0x80, 0xc5, 0x03,
		0x62, 0xfc, 0x5d, 0x10, 0x83, 0xc5, 0x03, 0x62, 0xfc, 0x5c, 0x10, 0x83, 0xc5, 0x03, 0x62, 0xfc,
		0xdc, 0x10, 0x83, 0xc5, 0x03, 0xd5, 0x10, 0x80, 0xc4, 0x03, 0x66, 0xd5, 0x10, 0x83, 0xc4, 0x03,
		0xd5, 0x10, 0x83, 0xc4, 0x03, 0xd5, 0x18, 0x83, 0xc4, 0x03,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(inc_dec)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			inc(r30b);
			inc(r30w);
			inc(r30d);
			inc(r30);
			inc(r30b, r31b);
			inc(r30w, r31w);
			inc(r30w|T_nf, r31w);
			inc(r30d, r31d);
			inc(r30, r31);
			inc(r30, ptr [r31]);

			dec(r30b);
			dec(r30w);
			dec(r30d);
			dec(r30);
			dec(r30b, r31b);
			dec(r30w, r31w);
			dec(r30w|T_nf, r31w);
			dec(r30d, r31d);
			dec(r30, r31);
			dec(r30, ptr [r31]);
		}
	} c;
	const uint8_t tbl[] = {
		// inc
		0xd5, 0x11, 0xfe, 0xc6, 0x66, 0xd5, 0x11, 0xff, 0xc6, 0xd5, 0x11, 0xff, 0xc6, 0xd5, 0x19, 0xff,
		0xc6, 0x62, 0xdc, 0x0c, 0x10, 0xfe, 0xc7,
		0x62, 0xdc, 0x0d, 0x10, 0xff, 0xc7,
		0x62, 0xdc, 0x0d, 0x14, 0xff, 0xc7, // T_nf
		0x62, 0xdc, 0x0c, 0x10, 0xff, 0xc7, 0x62, 0xdc, 0x8c, 0x10, 0xff, 0xc7, 0x62,
		0xdc, 0x8c, 0x10, 0xff, 0x07,
		// decA
		0xd5, 0x11, 0xfe, 0xce, 0x66, 0xd5, 0x11, 0xff, 0xce, 0xd5, 0x11, 0xff, 0xce, 0xd5, 0x19, 0xff,
		0xce, 0x62, 0xdc, 0x0c, 0x10, 0xfe, 0xcf,
		0x62, 0xdc, 0x0d, 0x10, 0xff, 0xcf,
		0x62, 0xdc, 0x0d, 0x14, 0xff, 0xcf, // T_nf
		0x62, 0xdc, 0x0c, 0x10, 0xff, 0xcf, 0x62, 0xdc, 0x8c, 0x10, 0xff, 0xcf, 0x62,
		0xdc, 0x8c, 0x10, 0xff, 0x0f,

	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(div_op1)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			div(r20b);
			div(r20d);
			div(r20w);
			div(r20);
			div(r20|T_nf);
			div(eax|T_nf);
			div(byte [r20+r30*1]);
			div(word [r20+r30*1]);
			div(dword [r20+r30*1]);
			div(qword [r20+r30*1]);

			idiv(r20b);
			idiv(r20d);
			idiv(r20w);
			idiv(r20);
			idiv(r20|T_nf);
			idiv(eax|T_nf);
			idiv(byte [r20+r30*1]);
			idiv(word [r20+r30*1]);
			idiv(dword [r20+r30*1]);
			idiv(qword [r20+r30*1]);

			imul(r20b);
			imul(r20d);
			imul(r20w);
			imul(r20);
			imul(r20|T_nf);
			imul(eax|T_nf);
			imul(byte [r20+r30*1]);
			imul(word [r20+r30*1]);
			imul(dword [r20+r30*1]);
			imul(qword [r20+r30*1]);

			mul(r20b);
			mul(r20d);
			mul(r20w);
			mul(r20);
			mul(r20|T_nf);
			mul(eax|T_nf);
			mul(byte [r20+r30*1]);
			mul(word [r20+r30*1]);
			mul(dword [r20+r30*1]);
			mul(qword [r20+r30*1]);

			neg(r20b);
			neg(r20d);
			neg(r20w);
			neg(r20);
			neg(r20|T_nf);
			neg(eax|T_nf);
			neg(byte [r20+r30*1]);
			neg(word [r20+r30*1]);
			neg(dword [r20+r30*1]);
			neg(qword [r20+r30*1]);

			// not_ does not have NF=1
			not_(r20b);
			not_(r20d);
			not_(r20w);
			not_(r20);
			not_(byte [r20+r30*1]);
			not_(word [r20+r30*1]);
			not_(dword [r20+r30*1]);
			not_(qword [r20+r30*1]);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xfc, 0x7c, 0x08, 0xf6, 0xf4,
		0x62, 0xfc, 0x7c, 0x08, 0xf7, 0xf4,
		0x62, 0xfc, 0x7d, 0x08, 0xf7, 0xf4,
		0x62, 0xfc, 0xfc, 0x08, 0xf7, 0xf4,
		0x62, 0xfc, 0xfc, 0x0c, 0xf7, 0xf4, // r20|T_nf
		0x62, 0xf4, 0x7c, 0x0c, 0xf7, 0xf0, // eax|T_nf
		0x62, 0xbc, 0x78, 0x08, 0xf6, 0x34, 0x34,
		0x62, 0xbc, 0x79, 0x08, 0xf7, 0x34, 0x34,
		0x62, 0xbc, 0x78, 0x08, 0xf7, 0x34, 0x34,
		0x62, 0xbc, 0xf8, 0x08, 0xf7, 0x34, 0x34,

		0x62, 0xfc, 0x7c, 0x08, 0xf6, 0xfc, 0x62, 0xfc, 0x7c, 0x08, 0xf7, 0xfc, 0x62, 0xfc, 0x7d, 0x08,
		0xf7, 0xfc, 0x62, 0xfc, 0xfc, 0x08, 0xf7, 0xfc, 0x62, 0xfc, 0xfc, 0x0c, 0xf7, 0xfc, 0x62, 0xf4,
		0x7c, 0x0c, 0xf7, 0xf8, 0x62, 0xbc, 0x78, 0x08, 0xf6, 0x3c, 0x34, 0x62, 0xbc, 0x79, 0x08, 0xf7,
		0x3c, 0x34, 0x62, 0xbc, 0x78, 0x08, 0xf7, 0x3c, 0x34, 0x62, 0xbc, 0xf8, 0x08, 0xf7, 0x3c, 0x34,

		0x62, 0xfc, 0x7c, 0x08, 0xf6, 0xec, 0x62, 0xfc, 0x7c, 0x08, 0xf7, 0xec, 0x62, 0xfc, 0x7d, 0x08,
		0xf7, 0xec, 0x62, 0xfc, 0xfc, 0x08, 0xf7, 0xec, 0x62, 0xfc, 0xfc, 0x0c, 0xf7, 0xec, 0x62, 0xf4,
		0x7c, 0x0c, 0xf7, 0xe8, 0x62, 0xbc, 0x78, 0x08, 0xf6, 0x2c, 0x34, 0x62, 0xbc, 0x79, 0x08, 0xf7,
		0x2c, 0x34, 0x62, 0xbc, 0x78, 0x08, 0xf7, 0x2c, 0x34, 0x62, 0xbc, 0xf8, 0x08, 0xf7, 0x2c, 0x34,
		0x62, 0xfc, 0x7c, 0x08, 0xf6, 0xe4, 0x62, 0xfc, 0x7c, 0x08, 0xf7, 0xe4, 0x62, 0xfc, 0x7d, 0x08,
		0xf7, 0xe4, 0x62, 0xfc, 0xfc, 0x08, 0xf7, 0xe4, 0x62, 0xfc, 0xfc, 0x0c, 0xf7, 0xe4, 0x62, 0xf4,
		0x7c, 0x0c, 0xf7, 0xe0, 0x62, 0xbc, 0x78, 0x08, 0xf6, 0x24, 0x34, 0x62, 0xbc, 0x79, 0x08, 0xf7,
		0x24, 0x34, 0x62, 0xbc, 0x78, 0x08, 0xf7, 0x24, 0x34, 0x62, 0xbc, 0xf8, 0x08, 0xf7, 0x24, 0x34,
		0x62, 0xfc, 0x7c, 0x08, 0xf6, 0xdc, 0x62, 0xfc, 0x7c, 0x08, 0xf7, 0xdc, 0x62, 0xfc, 0x7d, 0x08,
		0xf7, 0xdc, 0x62, 0xfc, 0xfc, 0x08, 0xf7, 0xdc, 0x62, 0xfc, 0xfc, 0x0c, 0xf7, 0xdc, 0x62, 0xf4,
		0x7c, 0x0c, 0xf7, 0xd8, 0x62, 0xbc, 0x78, 0x08, 0xf6, 0x1c, 0x34, 0x62, 0xbc, 0x79, 0x08, 0xf7,
		0x1c, 0x34, 0x62, 0xbc, 0x78, 0x08, 0xf7, 0x1c, 0x34, 0x62, 0xbc, 0xf8, 0x08, 0xf7, 0x1c, 0x34,
		0x62, 0xfc, 0x7c, 0x08, 0xf6, 0xd4, 0x62, 0xfc, 0x7c, 0x08, 0xf7, 0xd4, 0x62, 0xfc, 0x7d, 0x08,
		0xf7, 0xd4, 0x62, 0xfc, 0xfc, 0x08, 0xf7, 0xd4, 0x62, 0xbc, 0x78, 0x08, 0xf6, 0x14, 0x34, 0x62,
		0xbc, 0x79, 0x08, 0xf7, 0x14, 0x34, 0x62, 0xbc, 0x78, 0x08, 0xf7, 0x14, 0x34, 0x62, 0xbc, 0xf8,
		0x08, 0xf7, 0x14, 0x34,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(imul_2op)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			// imul(r30b, al); // QQQ : not supported?
			imul(r30w, ax);
			imul(r30d, eax);
			imul(r30, rax);
			imul(r30|T_nf, rax);
			imul(rcx|T_nf, rax);
			imul(rcx, ptr [r30]);

			neg(r30b, al);
			neg(r30w, ax);
			neg(r30d, eax);
			neg(r30, rax);
			neg(r30|T_nf, rax);
			neg(rcx|T_nf, rax);
			neg(rcx, ptr [r30]);

			not_(r30b, al);
			not_(r30w, ax);
			not_(r30d, eax);
			not_(r30, rax);
			not_(rcx, ptr [r30]);
		}
	} c;
	const uint8_t tbl[] = {
		// imul
		0x62, 0x64, 0x7d, 0x08, 0xaf, 0xf0,
		0x62, 0x64, 0x7c, 0x08, 0xaf, 0xf0,
		0x62, 0x64, 0xfc, 0x08, 0xaf, 0xf0,
		0x62, 0x64, 0xfc, 0x0c, 0xaf, 0xf0,
		0x62, 0xf4, 0xfc, 0x0c, 0xaf, 0xc8,
		0x62, 0xdc, 0xfc, 0x08, 0xaf, 0x0e,

		// neg
		0x62, 0xf4, 0x0c, 0x10, 0xf6, 0xd8, 0x62, 0xf4, 0x0d, 0x10, 0xf7, 0xd8, 0x62, 0xf4, 0x0c, 0x10,
		0xf7, 0xd8, 0x62, 0xf4, 0x8c, 0x10, 0xf7, 0xd8, 0x62, 0xf4, 0x8c, 0x14, 0xf7, 0xd8, 0x62, 0xf4,
		0xf4, 0x1c, 0xf7, 0xd8, 0x62, 0xdc, 0xf4, 0x18, 0xf7, 0x1e,

		// not
		0x62, 0xf4, 0x0c, 0x10, 0xf6, 0xd0, 0x62, 0xf4, 0x0d, 0x10, 0xf7, 0xd0, 0x62, 0xf4, 0x0c, 0x10,
		0xf7, 0xd0, 0x62, 0xf4, 0x8c, 0x10, 0xf7, 0xd0, 0x62, 0xdc, 0xf4, 0x18, 0xf7, 0x16,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(imul_zu)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			imul(ax|T_zu, cx, 0x1234);
			imul(ax|T_nf, cx, 0x1234);
			imul(ax|T_zu|T_nf, cx, 0x1234);
			imul(r30w, ax, 0x1234);
			imul(r30d, eax, 0x12345678);
			imul(r30, rax, 0x12345678);
			imul(r30|T_zu, rax, 0x12345678);
			imul(r30|T_nf, rax, 0x12345678);
			imul(r30|T_nf|T_zu, rax, 0x12345678);
			imul(rcx, ptr [r30], 0x12345678);
		}
	} c;
	const uint8_t tbl[] = {
		0x62, 0xf4, 0x7d, 0x18, 0x69, 0xc1, 0x34, 0x12, // T_zu
		0x62, 0xf4, 0x7d, 0x0c, 0x69, 0xc1, 0x34, 0x12, // T_nf
		0x62, 0xf4, 0x7d, 0x1c, 0x69, 0xc1, 0x34, 0x12, // T_zu|T_nf
		0x62, 0x64, 0x7d, 0x08, 0x69, 0xf0, 0x34, 0x12, // w
		0x62, 0x64, 0x7c, 0x08, 0x69, 0xf0, 0x78, 0x56, 0x34, 0x12, // d
		0x62, 0x64, 0xfc, 0x08, 0x69, 0xf0, 0x78, 0x56, 0x34, 0x12,
		0x62, 0x64, 0xfc, 0x18, 0x69, 0xf0, 0x78, 0x56, 0x34, 0x12, // T_zu
		0x62, 0x64, 0xfc, 0x0c, 0x69, 0xf0, 0x78, 0x56, 0x34, 0x12, // T_nf
		0x62, 0x64, 0xfc, 0x1c, 0x69, 0xf0, 0x78, 0x56, 0x34, 0x12, // T_nf|T_zu
		0x62, 0xdc, 0xfc, 0x08, 0x69, 0x0e, 0x78, 0x56, 0x34, 0x12,

	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(lzcnt)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			lzcnt(r16w, r17w);
			lzcnt(r16d, r17d);
			lzcnt(r16, r17);
			lzcnt(r16|T_nf, r17);
			lzcnt(rax|T_nf, rcx);
			lzcnt(rax, ptr [r18]);

			tzcnt(r16w, r17w);
			tzcnt(r16d, r17d);
			tzcnt(r16, r17);
			tzcnt(r16|T_nf, r17);
			tzcnt(rax|T_nf, rcx);
			tzcnt(rax, ptr [r18]);
		}
	} c;
	const uint8_t tbl[] = {
		// lzcnt
		0x62, 0xec, 0x7d, 0x08, 0xf5, 0xc1, 0x62, 0xec, 0x7c, 0x08, 0xf5, 0xc1, 0x62, 0xec, 0xfc, 0x08,
		0xf5, 0xc1, 0x62, 0xec, 0xfc, 0x0c, 0xf5, 0xc1, 0x62, 0xf4, 0xfc, 0x0c, 0xf5, 0xc1, 0x62, 0xfc,
		0xfc, 0x08, 0xf5, 0x02,
		// tzcnt
		0x62, 0xec, 0x7d, 0x08, 0xf4, 0xc1, 0x62, 0xec, 0x7c, 0x08, 0xf4, 0xc1, 0x62, 0xec, 0xfc, 0x08,
		0xf4, 0xc1, 0x62, 0xec, 0xfc, 0x0c, 0xf4, 0xc1, 0x62, 0xf4, 0xfc, 0x0c, 0xf4, 0xc1, 0x62, 0xfc,
		0xfc, 0x08, 0xf4, 0x02,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(shld)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			shld(rax|T_nf, rcx, cl);
			shld(r16, rcx, cl);
			shld(r16, rcx, 0x9);
			shld(r16|T_nf, rcx, 0x9);
			shld(r20, r16, rcx, cl);
			shld(r20|T_nf, r16, rcx, cl);
			shld(r20, r16, rcx, 0x9);
			shld(r20|T_nf, r16, rcx, 0x9);
			shld(r20, ptr [r21], rcx, 0x9);

			shrd(rax|T_nf, rcx, cl);
			shrd(r16, rcx, cl);
			shrd(r16, rcx, 0x9);
			shrd(r16|T_nf, rcx, 0x9);
			shrd(r20, r16, rcx, cl);
			shrd(r20|T_nf, r16, rcx, cl);
			shrd(r20, r16, rcx, 0x9);
			shrd(r20|T_nf, r16, rcx, 0x9);
			shrd(r20, ptr [r21], rcx, 0x9);
		}
	} c;
	const uint8_t tbl[] = {
		// shld
		0x62, 0xf4, 0xfc, 0x0c, 0xa5, 0xc8, 0x62, 0xfc, 0xfc, 0x08, 0xa5, 0xc8, 0x62, 0xfc, 0xfc, 0x08,
		0x24, 0xc8, 0x09, 0x62, 0xfc, 0xfc, 0x0c, 0x24, 0xc8, 0x09, 0x62, 0xfc, 0xdc, 0x10, 0xa5, 0xc8,
		0x62, 0xfc, 0xdc, 0x14, 0xa5, 0xc8, 0x62, 0xfc, 0xdc, 0x10, 0x24, 0xc8, 0x09, 0x62, 0xfc, 0xdc,
		0x14, 0x24, 0xc8, 0x09, 0x62, 0xfc, 0xdc, 0x10, 0x24, 0x4d, 0x00, 0x09,
		// shrd
		0x62, 0xf4, 0xfc, 0x0c, 0xad, 0xc8, 0x62, 0xfc, 0xfc, 0x08, 0xad, 0xc8, 0x62, 0xfc, 0xfc, 0x08,
		0x2c, 0xc8, 0x09, 0x62, 0xfc, 0xfc, 0x0c, 0x2c, 0xc8, 0x09, 0x62, 0xfc, 0xdc, 0x10, 0xad, 0xc8,
		0x62, 0xfc, 0xdc, 0x14, 0xad, 0xc8, 0x62, 0xfc, 0xdc, 0x10, 0x2c, 0xc8, 0x09, 0x62, 0xfc, 0xdc,
		0x14, 0x2c, 0xc8, 0x09, 0x62, 0xfc, 0xdc, 0x10, 0x2c, 0x4d, 0x00, 0x09,

	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(base)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			lea(r30, ptr[r20+r21]);
			add(r30, r20);
			add(r30, ptr[r20]);
			cmp(r30, ptr[r20]);
		}
	} c;
	const uint8_t tbl[] = {
		// lea
		0xd5, 0x7c, 0x8d, 0x34, 0x2c,
		// add
		0xd5, 0x59, 0x01, 0xe6,
		0xd5, 0x5c, 0x03, 0x34, 0x24,
		// cmp
		0xd5, 0x5c, 0x3b, 0x34, 0x24,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}

CYBOZU_TEST_AUTO(mov_misc)
{
	struct Code : Xbyak::CodeGenerator {
		Code()
		{
			movdir64b(r16, ptr [r20+r21*8+0x4]);
			movdiri(ptr [r20+r21*8+0x4], r16);

			movbe(ptr [r16], r30w);
			movbe(ptr [r16], r30d);
			movbe(ptr [r16], r30);
			movbe(r30w, ptr [r16]);
			movbe(r30d, ptr [r16]);
			movbe(r30, ptr [r16]);

			crc32(r30d, r8b);
			crc32(r30d, r8w);
			crc32(r30d, r8d);
			crc32(r30, r8b);
			crc32(r30, r8);
		}
	} c;
	const uint8_t tbl[] = {
		// movdir64b
		0x62, 0xec, 0x79, 0x08, 0xf8, 0x44, 0xec, 0x04,
		// movdiri
		0x62, 0xec, 0xf8, 0x08, 0xf9, 0x44, 0xec, 0x04,
		// movbe
		0x62, 0x6c, 0x7d, 0x08, 0x61, 0x30, 0x62, 0x6c, 0x7c, 0x08, 0x61, 0x30, 0x62, 0x6c, 0xfc, 0x08,
		0x61, 0x30, 0x62, 0x6c, 0x7d, 0x08, 0x60, 0x30, 0x62, 0x6c, 0x7c, 0x08, 0x60, 0x30, 0x62, 0x6c,
		0xfc, 0x08, 0x60, 0x30,
		// crc32
		0x62, 0x44, 0x7c, 0x08, 0xf0, 0xf0, 0x62, 0x44, 0x7d, 0x08, 0xf1, 0xf0, 0x62, 0x44, 0x7c, 0x08,
		0xf1, 0xf0, 0x62, 0x44, 0xfc, 0x08, 0xf0, 0xf0, 0x62, 0x44, 0xfc, 0x08, 0xf1, 0xf0,
	};
	const size_t n = sizeof(tbl);
	CYBOZU_TEST_EQUAL(c.getSize(), n);
	CYBOZU_TEST_EQUAL_ARRAY(c.getCode(), tbl, n);
}
