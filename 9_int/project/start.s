.global _start

_start:
	ldr pc, =Reset_Handler
	ldr pc, =Undefined_Handler
	ldr pc, =SVC_Handler
	ldr pc, =PrefAbort_Handler
	ldr pc, =DataAbort_Handler
	ldr pc, =NotUsed_Handler
	ldr pc, =IRQ_Handler
	ldr pc, =FIQ_Handler

Reset_Handler:
	
	cpsid i
    mrc p15, 0, r0, c1, c0, 0
	bic	r0, r0, #(0x1 << 12)
	bic r0, r0, #(0x1 << 2)
	bic r0, r0, #0x2
	bic r0, r0, #(0x1 << 11)
	bic r0, r0, #0x1
	mcr p15, 0, r0, c1, c0, 0

#if 0
	ldr r0, =0x87800000
	dsb
	isb
	mcr p15, 0, r0, c12, c0, 0
	dsb
	isb
#endif

	/* 进入IRQ模式 */
	mrs r0, cpsr
	bic r0, r0, 0x1F
	orr r0, r0, 0x12
	msr cpsr, r0
	ldr sp, 0x80600000
	
	/* 进入SYS模式 */
	mrs r0, cpsr
    bic r0, r0, 0x1F
    orr r0, r0, 0x1F
    msr cpsr, r0
    ldr sp, 0x80400000
	
	/* 进入SVC模式 */
	mrs r0, cpsr
    bic r0, r0, 0x1F
    orr r0, r0, 0x13
    msr cpsr, r0
    ldr sp, 0x80200000

	cpsie i	
