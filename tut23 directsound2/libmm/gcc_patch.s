// 2023/05/18 reject libgcc.
// patched -> _call_via_r7, _call_via_r1, malloc


	.align 0
	.global _call_via_r7
	.thumb_func

_call_via_r7:
	bx r7


	.align 0
	.global _call_via_r1
	.thumb_func

_call_via_r1:
	bx r1

