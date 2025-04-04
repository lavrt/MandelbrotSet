	.file	"defaultRender.cpp"
# GNU C++17 (Ubuntu 13.3.0-6ubuntu2~24.04) version 13.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 13.3.0, GMP version 6.3.0, MPFR version 4.2.1, MPC version 1.3.1, isl version isl-0.26-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed: -mtune=generic -march=x86-64 -O2 -fasynchronous-unwind-tables -fstack-protector-strong -fstack-clash-protection -fcf-protection
	.text
	.p2align 4
	.globl	_Z13DefaultRenderPh10tParametrs
	.type	_Z13DefaultRenderPh10tParametrs, @function
_Z13DefaultRenderPh10tParametrs:
.LFB3356:
	.cfi_startproc
	endbr64	
# ./src/defaultRender.cpp:11: void DefaultRender(sf::Uint8* pixels, tParametrs position) {
	movq	%xmm0, -16(%rsp)	# tmp131, position
# ./src/defaultRender.cpp:12:     float pX = INIT_X + position.offsetX;
	movss	-12(%rsp), %xmm0	# position.offsetX, position.offsetX
	subss	.LC1(%rip), %xmm0	#, position.offsetX
# ./src/defaultRender.cpp:16:     float stepY = (4. / HEIGHT) / position.zoom;
	movl	$1080, %ecx	#, ivtmp_55
# ./src/defaultRender.cpp:13:     float pY = INIT_Y + position.offsetY;
	subss	.LC2(%rip), %xmm1	#, pY
	movss	.LC5(%rip), %xmm7	#, tmp127
# ./src/defaultRender.cpp:15:     float stepX = (4. / WIDTH * ASPECT) / position.zoom;
	movsd	.LC3(%rip), %xmm8	#, tmp115
# ./src/defaultRender.cpp:16:     float stepY = (4. / HEIGHT) / position.zoom;
	movsd	.LC4(%rip), %xmm9	#, tmp117
# ./src/defaultRender.cpp:12:     float pX = INIT_X + position.offsetX;
	movaps	%xmm0, %xmm10	# position.offsetX, pX
# ./src/defaultRender.cpp:15:     float stepX = (4. / WIDTH * ASPECT) / position.zoom;
	pxor	%xmm0, %xmm0	# _2
	cvtss2sd	-16(%rsp), %xmm0	# position.zoom, _2
# ./src/defaultRender.cpp:15:     float stepX = (4. / WIDTH * ASPECT) / position.zoom;
	divsd	%xmm0, %xmm8	# _2, tmp114
# ./src/defaultRender.cpp:16:     float stepY = (4. / HEIGHT) / position.zoom;
	divsd	%xmm0, %xmm9	# _2, tmp116
# ./src/defaultRender.cpp:15:     float stepX = (4. / WIDTH * ASPECT) / position.zoom;
	cvtsd2ss	%xmm8, %xmm8	# tmp114, stepX
# ./src/defaultRender.cpp:16:     float stepY = (4. / HEIGHT) / position.zoom;
	cvtsd2ss	%xmm9, %xmm9	# tmp116, stepY
.L5:
# ./src/defaultRender.cpp:19:         pY += stepY;
	addss	%xmm9, %xmm1	# stepY, pY
	movaps	%xmm10, %xmm6	# pX, pX
	movl	$1920, %edx	#, ivtmp_67
	.p2align 4,,10
	.p2align 3
.L4:
# ./src/defaultRender.cpp:26:             float sY2 = 0;
	pxor	%xmm4, %xmm4	# sY2
# ./src/defaultRender.cpp:21:             pX += stepX;
	addss	%xmm8, %xmm6	# stepX, pX
# ./src/defaultRender.cpp:28:             size_t iter = 0;
	xorl	%eax, %eax	# iter
# ./src/defaultRender.cpp:25:             float sX2 = 0;
	movaps	%xmm4, %xmm3	#, sX2
# ./src/defaultRender.cpp:24:             float sY = 0;
	movaps	%xmm4, %xmm2	# tmp23, sY
# ./src/defaultRender.cpp:23:             float sX = 0;
	movaps	%xmm4, %xmm0	# tmp22, sX
	jmp	.L2	#
	.p2align 4,,10
	.p2align 3
.L14:
# ./src/defaultRender.cpp:29:             for (; sX2 + sY2 < MAX_RADIUS * MAX_RADIUS && iter < MAX_ITER; iter++) {
	cmpq	$256, %rax	#, iter
	je	.L6	#,
.L2:
# ./src/defaultRender.cpp:30:                 sY = 2 * sX * sY + pY;
	addss	%xmm0, %xmm0	# sX, tmp118
# ./src/defaultRender.cpp:31:                 sX = sX2 - sY2 + pX;
	subss	%xmm4, %xmm3	# sY2, tmp119
# ./src/defaultRender.cpp:29:             for (; sX2 + sY2 < MAX_RADIUS * MAX_RADIUS && iter < MAX_ITER; iter++) {
	addq	$1, %rax	#, iter
# ./src/defaultRender.cpp:35:                 dummy = 1;
	movl	$1, dummy(%rip)	#, dummy
# ./src/defaultRender.cpp:30:                 sY = 2 * sX * sY + pY;
	mulss	%xmm0, %xmm2	# tmp118, _6
# ./src/defaultRender.cpp:31:                 sX = sX2 - sY2 + pX;
	addss	%xmm6, %xmm3	# pX, tmp119
	movaps	%xmm3, %xmm0	# tmp119, sX
# ./src/defaultRender.cpp:33:                 sX2 = sX * sX;
	mulss	%xmm3, %xmm3	# sX, sX2
# ./src/defaultRender.cpp:30:                 sY = 2 * sX * sY + pY;
	addss	%xmm1, %xmm2	# pY, sY
# ./src/defaultRender.cpp:34:                 sY2 = sY * sY; 
	movaps	%xmm2, %xmm4	# sY, sY2
	mulss	%xmm2, %xmm4	# sY, sY2
# ./src/defaultRender.cpp:29:             for (; sX2 + sY2 < MAX_RADIUS * MAX_RADIUS && iter < MAX_ITER; iter++) {
	movaps	%xmm3, %xmm5	# sX2, tmp120
	addss	%xmm4, %xmm5	# sY2, tmp120
# ./src/defaultRender.cpp:29:             for (; sX2 + sY2 < MAX_RADIUS * MAX_RADIUS && iter < MAX_ITER; iter++) {
	comiss	%xmm5, %xmm7	# tmp120, tmp127
	ja	.L14	#,
.L6:
# ./src/defaultRender.cpp:20:         for (size_t x = 0; x < WIDTH; x++) {
	subq	$1, %rdx	#, ivtmp_67
	jne	.L4	#,
# ./src/defaultRender.cpp:18:     for (size_t y = 0; y < HEIGHT; y++) {
	subq	$1, %rcx	#, ivtmp_55
	jne	.L5	#,
# ./src/defaultRender.cpp:43: }
	ret	
	.cfi_endproc
.LFE3356:
	.size	_Z13DefaultRenderPh10tParametrs, .-_Z13DefaultRenderPh10tParametrs
	.globl	dummy
	.bss
	.align 4
	.type	dummy, @object
	.size	dummy, 4
dummy:
	.zero	4
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC1:
	.long	1075419546
	.align 4
.LC2:
	.long	1067030938
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC3:
	.long	-858993459
	.long	1064195898
	.align 8
.LC4:
	.long	-922622604
	.long	1064195898
	.section	.rodata.cst4
	.align 4
.LC5:
	.long	1082130432
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
