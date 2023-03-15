.global _start

_start:
/* 1.使能全部时钟 */
ldr r0, =0X020C4068
ldr r1, =0XFFFFFFFF 
str r1, [r0]

ldr r1, =0X020C406C
str r1, [r0]

ldr r1, =0X020C4070
str r1, [r0]

ldr r1, =0X020C4074
str r1, [r0]

ldr r1, =0X020C4078
str r1, [r0]

ldr r1, =0X020C407C
str r1, [r0]

ldr r1, =0X020C4080
str r1, [r0]

/* 2.设置GPIO1_IO03复用为GPIO1_IO3 */
ldr r0, =0X020E0068
ldr r1, =0X5
str r1, [r0]

/* 3.配置GPIO1_IO3的IO属性 */
ldr r0, =0X020E02F4
ldr r1, =0X10B0
str r1, [r0]

/* 4.设置GPIO1_IO3为输出 */
ldr r0, =0X0209C004
ldr r1, =0X0000008
str r1, [r0]

/* 5.打开LED0 设置GPIO1_IO3输出低电平 */
ldr r0, =0X0209C000
ldr r1, =0
str r1, [r0]

loop:
    b loop
    