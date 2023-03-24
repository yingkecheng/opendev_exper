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
	bic r0, r0, #(0x1 << 12)
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
	bic r0, r0, #0x1F
	orr r0, r0, #0x12
	msr cpsr, r0
	ldr sp, =0x80600000
	
	/* 进入SYS模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1F
	orr r0, r0, #0x1F
	msr cpsr, r0
	ldr sp, =0x80400000
	
	/* 进入SVC模式 */
	mrs r0, cpsr
	bic r0, r0, #0x1F
	orr r0, r0, #0x13
	msr cpsr, r0
	ldr sp, =0x80200000

	cpsie i				/* 打开全局中断 */

#if 0
	/* 使能IRQ中断 */
	mrs r0, cpsr
	bic r0, r0, #0x80
	msr cpsr, r0
#endif

	b main

/* 未定义中断 */
Undefined_Handler:
	ldr r0, =Undefined_Handler
	bx r0

/* SVC中断 */
SVC_Handler:
	ldr r0, =SVC_Handler
	bx r0

/* 预取终止中断 */
PrefAbort_Handler:
	ldr r0, =PrefAbort_Handler
	bx r0

/* 数据终止中断 */
DataAbort_Handler:
	ldr r0, =DataAbort_Handler
	bx r0

/* 未使用的中断 */
NotUsed_Handler:
	ldr r0, =NotUsed_Handler
	bx r0

/* IRQ中断 */
IRQ_Handler:
	push {lr}					/* 保存lr地址 */
	push {r0-r3, r12}	
	
	mrs r0, spsr
	push {r0}					/* 保存spsr */
	
	mrc p15, 4, r1, c15, c0, 0	/* 读GIC基地址 */
	add r1, r1, #0x2000
	ldr r0, [r1, #0xC]			/* 读当前发生的中断号 */

	push {r0, r1}				/* 保存r0，r1 */
	cps #0x13					/* 进入SVC模式，允许其他中断进入 */
	
	push {lr}					/* 保存SVC模式的lr寄存器 */
	ldr r2, =system_irqhandler	/* 加载C语言中断函数到r2寄存器 */
	blx r2						/* 运行C语言中断函数，带有一个参数 */

	pop {lr}					/* 执行完C语言中断函数，lr出栈 */
	cps #0x12					/* 进入IRQ模式 */
	pop {r0, r1}
	str r0, [r1, #0x10]			/* 中断完成，写EOIR */

	pop {r0}
	msr spsr_cxsf, r0			/* 恢复spsr */

	pop {r0-r3, r12}
	pop {lr}
	subs pc, lr, #4
	
/* FIQ中断 */
FIQ_Handler:
	ldr r0, =FIQ_Handler
	bx r0

