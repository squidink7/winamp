		/*
	dct64_3dnow.s: Replacement of dct64() with AMD's 3DNow! SIMD operations support
		
	copyright ?-2006 by the mpg123 project - free software under the terms of the LGPL 2.1
	see COPYING and AUTHORS files in distribution or http://mpg123.org
	initially written by Syuuhei Kashiyama
		
	Original "license" statement:
	The author of this program disclaim whole expressed or implied
	warranties with regard to this program, and in no event shall the
	author of this program liable to whatever resulted from the use of
	this program. Use it at your own risk.
		*/
		
		#include "mangle.h"
		
	.globl ASM_NAME(dct64_3dnow)
		/*	.type	 ASM_NAME(dct64_3dnow),@function */
		ASM_NAME(dct64_3dnow):
	subl $256,%esp
	pushl %ebp
	pushl %edi
	pushl %esi
	pushl %ebx
		
	#undef _EBX_
	#define _EBX_ %ecx
	GET_GOT
		
	leal 16(%esp),%ebx
	movl 284(%esp),%edi
	movl 276(%esp),%ebp
	movl 280(%esp),%edx
	leal 128(%ebx),%esi
		
	/* femms */
		
	/* 1 */
		#if defined(PIC) && defined(__APPLE__)
	movl GLOBAL_VAR_PTR(pnts),%eax
	movl (%eax),%eax
		#else
	movl GLOBAL_VAR(pnts),%eax
		#endif
	movq 0(%edi),%mm0
movq %mm0,%mm1
	movd 124(%edi),%mm2
	punpckldq 120(%edi),%mm2
	movq 0(%eax),%mm3
	pfadd %mm2,%mm0
	movq %mm0,0(%ebx)
	pfsub %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,124(%ebx)
	psrlq $32,%mm1
	movd %mm1,120(%ebx)
	movq 8(%edi),%mm4
	movq %mm4,%mm5
	movd 116(%edi),%mm6
	punpckldq 112(%edi),%mm6
	movq 8(%eax),%mm7
	pfadd %mm6,%mm4
	movq %mm4,8(%ebx)
	pfsub %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,116(%ebx)
	psrlq $32,%mm5
	movd %mm5,112(%ebx)
	movq 16(%edi),%mm0
	movq %mm0,%mm1
	movd 108(%edi),%mm2
	punpckldq 104(%edi),%mm2
	movq 16(%eax),%mm3
	pfadd %mm2,%mm0
	movq %mm0,16(%ebx)
	pfsub %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,108(%ebx)
	psrlq $32,%mm1
	movd %mm1,104(%ebx)
	movq 24(%edi),%mm4
	movq %mm4,%mm5
	movd 100(%edi),%mm6
	punpckldq 96(%edi),%mm6
	movq 24(%eax),%mm7
	pfadd %mm6,%mm4
	movq %mm4,24(%ebx)
	pfsub %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,100(%ebx)
	psrlq $32,%mm5
	movd %mm5,96(%ebx)
	movq 32(%edi),%mm0
	movq %mm0,%mm1
	movd 92(%edi),%mm2
	punpckldq 88(%edi),%mm2
	movq 32(%eax),%mm3
	pfadd %mm2,%mm0
	movq %mm0,32(%ebx)
	pfsub %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,92(%ebx)
	psrlq $32,%mm1
	movd %mm1,88(%ebx)
	movq 40(%edi),%mm4
	movq %mm4,%mm5
	movd 84(%edi),%mm6
	punpckldq 80(%edi),%mm6
	movq 40(%eax),%mm7
	pfadd %mm6,%mm4
	movq %mm4,40(%ebx)
	pfsub %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,84(%ebx)
	psrlq $32,%mm5
	movd %mm5,80(%ebx)
	movq 48(%edi),%mm0
	movq %mm0,%mm1
	movd 76(%edi),%mm2
	punpckldq 72(%edi),%mm2
	movq 48(%eax),%mm3
	pfadd %mm2,%mm0
	movq %mm0,48(%ebx)
	pfsub %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,76(%ebx)
	psrlq $32,%mm1
	movd %mm1,72(%ebx)
	movq 56(%edi),%mm4
	movq %mm4,%mm5
	movd 68(%edi),%mm6
	punpckldq 64(%edi),%mm6
	movq 56(%eax),%mm7
	pfadd %mm6,%mm4
	movq %mm4,56(%ebx)
	pfsub %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,68(%ebx)
	psrlq $32,%mm5
	movd %mm5,64(%ebx)
	
	/* 2 */
		#if defined(PIC) && defined(__APPLE__)
	movl GLOBAL_VAR_PTR(pnts),%eax
	movl 4(%eax),%eax
		#else
	movl 4+GLOBAL_VAR(pnts),%eax
		#endif
	/* 0,14 */
	movq 0(%ebx),%mm0
	movq %mm0,%mm1
	movd 60(%ebx),%mm2
	punpckldq 56(%ebx),%mm2
	movq 0(%eax),%mm3
	pfadd %mm2,%mm0
	movq %mm0,0(%esi)
	pfsub %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,60(%esi)
	psrlq $32,%mm1
	movd %mm1,56(%esi)
	/* 16,30 */
	movq 64(%ebx),%mm0
	movq %mm0,%mm1
	movd 124(%ebx),%mm2
	punpckldq 120(%ebx),%mm2
	pfadd %mm2,%mm0
	movq %mm0,64(%esi)
	pfsubr %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,124(%esi)
	psrlq $32,%mm1
	movd %mm1,120(%esi)
	/* 2,12 */
	movq 8(%ebx),%mm4
	movq %mm4,%mm5
	movd 52(%ebx),%mm6
	punpckldq 48(%ebx),%mm6
	movq 8(%eax),%mm7
	pfadd %mm6,%mm4
	movq %mm4,8(%esi)
	pfsub %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,52(%esi)
	psrlq $32,%mm5
	movd %mm5,48(%esi)
	/* 18,28 */
	movq 72(%ebx),%mm4
	movq %mm4,%mm5
	movd 116(%ebx),%mm6
	punpckldq 112(%ebx),%mm6
	pfadd %mm6,%mm4
	movq %mm4,72(%esi)
	pfsubr %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,116(%esi)
	psrlq $32,%mm5
	movd %mm5,112(%esi)
	/* 4,10 */
	movq 16(%ebx),%mm0
	movq %mm0,%mm1
	movd 44(%ebx),%mm2
	punpckldq 40(%ebx),%mm2
	movq 16(%eax),%mm3
	pfadd %mm2,%mm0
	movq %mm0,16(%esi)
	pfsub %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,44(%esi)
	psrlq $32,%mm1
	movd %mm1,40(%esi)
	/* 20,26 */
	movq 80(%ebx),%mm0
	movq %mm0,%mm1
	movd 108(%ebx),%mm2
	punpckldq 104(%ebx),%mm2
	pfadd %mm2,%mm0
	movq %mm0,80(%esi)
	pfsubr %mm2,%mm1
	pfmul %mm3,%mm1
	movd %mm1,108(%esi)
	psrlq $32,%mm1
	movd %mm1,104(%esi)
	/* 6,8 */
	movq 24(%ebx),%mm4
	movq %mm4,%mm5
	movd 36(%ebx),%mm6
	punpckldq 32(%ebx),%mm6
	movq 24(%eax),%mm7
	pfadd %mm6,%mm4
	movq %mm4,24(%esi)
	pfsub %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,36(%esi)
	psrlq $32,%mm5
	movd %mm5,32(%esi)
	/* 22,24 */
	movq 88(%ebx),%mm4
	movq %mm4,%mm5
	movd 100(%ebx),%mm6
	punpckldq 96(%ebx),%mm6
	pfadd %mm6,%mm4
	movq %mm4,88(%esi)
	pfsubr %mm6,%mm5
	pfmul %mm7,%mm5
	movd %mm5,100(%esi)
	psrlq $32,%mm5
	movd %mm5,96(%esi)
		
	/* 3 */
		#if defined(PIC) && defined(__APPLE__)
	movl GLOBAL_VAR_PTR(pnts),%eax
	movl 8(%eax),%eax
		#else
	movl 8+GLOBAL_VAR(pnts),%eax
		#endif
	movq 0(%eax),%mm0
	movq 8(%eax),%mm1
	/* 0,6 */
	movq 0(%esi),%mm2
	movq %mm2,%mm3
	movd 28(%esi),%mm4
	punpckldq 24(%esi),%mm4
	pfadd %mm4,%mm2
	pfsub %mm4,%mm3
	pfmul %mm0,%mm3
	movq %mm2,0(%ebx)
	movd %mm3,28(%ebx)
	psrlq $32,%mm3
	movd %mm3,24(%ebx)
	/* 2,4 */
	movq 8(%esi),%mm5
	movq %mm5,%mm6
	movd 20(%esi),%mm7
	punpckldq 16(%esi),%mm7
	pfadd %mm7,%mm5
	pfsub %mm7,%mm6
	pfmul %mm1,%mm6
	movq %mm5,8(%ebx)
	movd %mm6,20(%ebx)
	psrlq $32,%mm6
	movd %mm6,16(%ebx)
	/* 8,14 */
	movq 32(%esi),%mm2
	movq %mm2,%mm3
	movd 60(%esi),%mm4
	punpckldq 56(%esi),%mm4
	pfadd %mm4,%mm2
	pfsubr %mm4,%mm3
	pfmul %mm0,%mm3
	movq %mm2,32(%ebx)
	movd %mm3,60(%ebx)
	psrlq $32,%mm3
	movd %mm3,56(%ebx)
	/* 10,12 */
	movq 40(%esi),%mm5
	movq %mm5,%mm6
	movd 52(%esi),%mm7
	punpckldq 48(%esi),%mm7
	pfadd %mm7,%mm5
	pfsubr %mm7,%mm6
	pfmul %mm1,%mm6
	movq %mm5,40(%ebx)
	movd %mm6,52(%ebx)
	psrlq $32,%mm6
	movd %mm6,48(%ebx)
	/* 16,22 */
	movq 64(%esi),%mm2
	movq %mm2,%mm3
	movd 92(%esi),%mm4
	punpckldq 88(%esi),%mm4
	pfadd %mm4,%mm2
	pfsub %mm4,%mm3
	pfmul %mm0,%mm3
	movq %mm2,64(%ebx)
	movd %mm3,92(%ebx)
	psrlq $32,%mm3
	movd %mm3,88(%ebx)
	/*  18,20 */
	movq 72(%esi),%mm5
	movq %mm5,%mm6
	movd 84(%esi),%mm7
	punpckldq 80(%esi),%mm7
	pfadd %mm7,%mm5
	pfsub %mm7,%mm6
	pfmul %mm1,%mm6
	movq %mm5,72(%ebx)
	movd %mm6,84(%ebx)
	psrlq $32,%mm6
	movd %mm6,80(%ebx)
	/*  24,30 */
	movq 96(%esi),%mm2
	movq %mm2,%mm3
	movd 124(%esi),%mm4
	punpckldq 120(%esi),%mm4
	pfadd %mm4,%mm2
	pfsubr %mm4,%mm3
	pfmul %mm0,%mm3
	movq %mm2,96(%ebx)
	movd %mm3,124(%ebx)
	psrlq $32,%mm3
	movd %mm3,120(%ebx)
	/*  26,28 */
	movq 104(%esi),%mm5
	movq %mm5,%mm6
	movd 116(%esi),%mm7
	punpckldq 112(%esi),%mm7
	pfadd %mm7,%mm5
	pfsubr %mm7,%mm6
	pfmul %mm1,%mm6
	movq %mm5,104(%ebx)
	movd %mm6,116(%ebx)
	psrlq $32,%mm6
	movd %mm6,112(%ebx)
	
	/*  4 */
		#if defined(PIC) && defined(__APPLE__)
	movl GLOBAL_VAR_PTR(pnts),%eax
	movl 12(%eax),%eax
		#else
	movl 12+GLOBAL_VAR(pnts),%eax
		#endif
	movq 0(%eax),%mm0
	/*  0 */
	movq 0(%ebx),%mm1
	movq %mm1,%mm2
	movd 12(%ebx),%mm3
	punpckldq 8(%ebx),%mm3
	pfadd %mm3,%mm1
	pfsub %mm3,%mm2
	pfmul %mm0,%mm2
	movq %mm1,0(%esi)
	movd %mm2,12(%esi)
	psrlq $32,%mm2
	movd %mm2,8(%esi)
	/*  4 */
	movq 16(%ebx),%mm4
	movq %mm4,%mm5
	movd 28(%ebx),%mm6
	punpckldq 24(%ebx),%mm6
	pfadd %mm6,%mm4
	pfsubr %mm6,%mm5
	pfmul %mm0,%mm5
	movq %mm4,16(%esi)
	movd %mm5,28(%esi)
	psrlq $32,%mm5
	movd %mm5,24(%esi)
	/*  8 */
	movq 32(%ebx),%mm1
	movq %mm1,%mm2
	movd 44(%ebx),%mm3
	punpckldq 40(%ebx),%mm3
	pfadd %mm3,%mm1
	pfsub %mm3,%mm2
	pfmul %mm0,%mm2
	movq %mm1,32(%esi)
	movd %mm2,44(%esi)
	psrlq $32,%mm2
	movd %mm2,40(%esi)
	/*  12 */
	movq 48(%ebx),%mm4
	movq %mm4,%mm5
	movd 60(%ebx),%mm6
	punpckldq 56(%ebx),%mm6
	pfadd %mm6,%mm4
	pfsubr %mm6,%mm5
	pfmul %mm0,%mm5
	movq %mm4,48(%esi)
	movd %mm5,60(%esi)
	psrlq $32,%mm5
	movd %mm5,56(%esi)
	/*  16 */
	movq 64(%ebx),%mm1
	movq %mm1,%mm2
	movd 76(%ebx),%mm3
	punpckldq 72(%ebx),%mm3
	pfadd %mm3,%mm1
	pfsub %mm3,%mm2
	pfmul %mm0,%mm2
	movq %mm1,64(%esi)
	movd %mm2,76(%esi)
	psrlq $32,%mm2
	movd %mm2,72(%esi)
	/*  20 */
	movq 80(%ebx),%mm4
	movq %mm4,%mm5
	movd 92(%ebx),%mm6
	punpckldq 88(%ebx),%mm6
	pfadd %mm6,%mm4
	pfsubr %mm6,%mm5
	pfmul %mm0,%mm5
	movq %mm4,80(%esi)
	movd %mm5,92(%esi)
	psrlq $32,%mm5
	movd %mm5,88(%esi)
	/*  24 */
	movq 96(%ebx),%mm1
	movq %mm1,%mm2
	movd 108(%ebx),%mm3
	punpckldq 104(%ebx),%mm3
	pfadd %mm3,%mm1
	pfsub %mm3,%mm2
	pfmul %mm0,%mm2
	movq %mm1,96(%esi)
	movd %mm2,108(%esi)
	psrlq $32,%mm2
	movd %mm2,104(%esi)
	/*  28 */
	movq 112(%ebx),%mm4
	movq %mm4,%mm5
	movd 124(%ebx),%mm6
	punpckldq 120(%ebx),%mm6
	pfadd %mm6,%mm4
	pfsubr %mm6,%mm5
	pfmul %mm0,%mm5
	movq %mm4,112(%esi)
	movd %mm5,124(%esi)
	psrlq $32,%mm5
	movd %mm5,120(%esi)
		
	/*  5 */
	movl $-1,%eax
	movd %eax,%mm1
	movl $1,%eax
	/*  L | H */
	movd %eax,%mm0	
	punpckldq %mm1,%mm0
	/*  1.0 | -1.0 */
	pi2fd %mm0,%mm0	
	movd %eax,%mm1
	pi2fd %mm1,%mm1
		#if defined(PIC) && defined(__APPLE__)
	movl GLOBAL_VAR_PTR(pnts),%eax
	movl 16(%eax),%eax
		#else
	movl 16+GLOBAL_VAR(pnts),%eax
		#endif
	movd 0(%eax),%mm2
	/*  1.0 | cos0 */
	punpckldq %mm2,%mm1
	/*  0 */
	movq 0(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2
	pfmul %mm1,%mm2
	movq %mm2,0(%ebx)
	movq 8(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm4,8(%ebx)
	/*  4 */
	movq 16(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2 
	pfmul %mm1,%mm2
	movq 24(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm2,%mm3
	psrlq $32,%mm3
	pfadd %mm4,%mm2
	pfadd %mm3,%mm4
	movq %mm2,16(%ebx)
	movq %mm4,24(%ebx)
	/*  8 */
	movq 32(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2
	pfmul %mm1,%mm2
	movq %mm2,32(%ebx)
	movq 40(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm4,40(%ebx)
	/*  12 */
	movq 48(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2 
	pfmul %mm1,%mm2
	movq 56(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm2,%mm3
	psrlq $32,%mm3
	pfadd %mm4,%mm2
	pfadd %mm3,%mm4
	movq %mm2,48(%ebx)
	movq %mm4,56(%ebx)
	/*  16 */
	movq 64(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2
	pfmul %mm1,%mm2
	movq %mm2,64(%ebx)
	movq 72(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm4,72(%ebx)
	/*  20 */
	movq 80(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2 
	pfmul %mm1,%mm2
	movq 88(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm2,%mm3
	psrlq $32,%mm3
	pfadd %mm4,%mm2
	pfadd %mm3,%mm4
	movq %mm2,80(%ebx)
	movq %mm4,88(%ebx)
	/*  24 */
	movq 96(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2
	pfmul %mm1,%mm2
	movq %mm2,96(%ebx)
	movq 104(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm4,104(%ebx)
	/*  28 */
	movq 112(%esi),%mm2
	movq %mm2,%mm3
	pfmul %mm0,%mm3
	pfacc %mm3,%mm2 
	pfmul %mm1,%mm2
	movq 120(%esi),%mm4
	movq %mm4,%mm5
	pfmul %mm0,%mm5
	pfacc %mm5,%mm4
	pfmul %mm0,%mm4
	pfmul %mm1,%mm4
	movq %mm4,%mm5
	psrlq $32,%mm5
	pfacc %mm5,%mm4
	movq %mm2,%mm3
	psrlq $32,%mm3
	pfadd %mm4,%mm2
	pfadd %mm3,%mm4
	movq %mm2,112(%ebx)
	movq %mm4,120(%ebx)
		
	/*  Phase6 */
	movl 0(%ebx),%eax
	movl %eax,1024(%ebp)
	movl 4(%ebx),%eax
	movl %eax,0(%ebp)
	movl %eax,0(%edx)
	movl 8(%ebx),%eax
	movl %eax,512(%ebp)
	movl 12(%ebx),%eax
	movl %eax,512(%edx)
		
	movl 16(%ebx),%eax
	movl %eax,768(%ebp)
	movl 20(%ebx),%eax
	movl %eax,256(%edx)
		
	movl 24(%ebx),%eax
	movl %eax,256(%ebp)
	movl 28(%ebx),%eax
	movl %eax,768(%edx)
		
	movq 32(%ebx),%mm0
	movq 48(%ebx),%mm1
	pfadd %mm1,%mm0
	movd %mm0,896(%ebp)
	psrlq $32,%mm0
	movd %mm0,128(%edx)
	movq 40(%ebx),%mm2
	pfadd %mm2,%mm1
	movd %mm1,640(%ebp)
	psrlq $32,%mm1
	movd %mm1,384(%edx)
		
	movq 56(%ebx),%mm3
	pfadd %mm3,%mm2
	movd %mm2,384(%ebp)
psrlq $32,%mm2
	movd %mm2,640(%edx)
		
	movd 36(%ebx),%mm4
	pfadd %mm4,%mm3
	movd %mm3,128(%ebp)
	psrlq $32,%mm3
	movd %mm3,896(%edx)
	movq 96(%ebx),%mm0
	movq 64(%ebx),%mm1
		
	movq 112(%ebx),%mm2
pfadd %mm2,%mm0
	movq %mm0,%mm3
	pfadd %mm1,%mm3
	movd %mm3,960(%ebp)
	psrlq $32,%mm3
	movd %mm3,64(%edx)
	movq 80(%ebx),%mm1
	pfadd %mm1,%mm0
	movd %mm0,832(%ebp)
psrlq $32,%mm0
	movd %mm0,192(%edx)
	movq 104(%ebx),%mm3
	pfadd %mm3,%mm2
	movq %mm2,%mm4
	pfadd %mm1,%mm4
	movd %mm4,704(%ebp)
	psrlq $32,%mm4
	movd %mm4,320(%edx)
	movq 72(%ebx),%mm1
	pfadd %mm1,%mm2
	movd %mm2,576(%ebp)
	psrlq $32,%mm2
	movd %mm2,448(%edx)
		
	movq 120(%ebx),%mm4
	pfadd %mm4,%mm3
	movq %mm3,%mm5
	pfadd %mm1,%mm5
	movd %mm5,448(%ebp)
	psrlq $32,%mm5
	movd %mm5,576(%edx)
	movq 88(%ebx),%mm1
	pfadd %mm1,%mm3
	movd %mm3,320(%ebp)
	psrlq $32,%mm3
	movd %mm3,704(%edx)
		
	movd 100(%ebx),%mm5
	pfadd %mm5,%mm4
	movq %mm4,%mm6
	pfadd %mm1,%mm6
	movd %mm6,192(%ebp)
	psrlq $32,%mm6
	movd %mm6,832(%edx)	
	movd 68(%ebx),%mm1
	pfadd %mm1,%mm4
	movd %mm4,64(%ebp)
	psrlq $32,%mm4
	movd %mm4,960(%edx)
		
	/*  femms */
		
popl %ebx
	popl %esi
	popl %edi
popl %ebp
	addl $256,%esp
	
ret
		
		#if defined(PIC) && defined(__APPLE__)
	.section	__IMPORT,__pointers,non_lazy_symbol_pointers
		L_pnts:
	.indirect_symbol	ASM_NAME(pnts)
	.long	0
		#endif
		
		NONEXEC_STACK
		