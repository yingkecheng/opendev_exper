#include "bsp_int.h"

static unsigned int irqNesting;

static sys_irq_handle_t irqTable[NUMBER_OF_INT_VECTORS]

void int_init(void) {
	GIC_Init(void);
	system_irqtable_init();
	__set_VBAR((uint32_t)0x87800000);	/* 中断向量表偏移 */
}

void system_irqtable_init(void) {
	unsigned int i = 0;
	irqNesting = 0;
	
	for (i = 0; i < NUMBER_OF_INT_VECTORS; i++) {
		system_register_irqhandler((IRQn_Type)i, default_irqhandler, NULL);
	}
}

void system_register_irqhandler(IRQn_Type irq, 
								system_irq_handler_t handler,
								void *userParam) {
	irqTable[irq].irqHandler = handler;
	irqTable[irq].userParam = userParam;
}

void system_irqhandler(unsigned int giccIar) {
	uint32_t intNum = giccIar & 0x3FFUL;
	
	if ((intNum == 1020) || (intNum >= NUMBER_OF_INT_VECTORS)) {
		return;
	}

	isqNesting++;

	irqTable[intNum].irqHandler(intNum, irqTable[intNum].userParam);

	irqNesting--;
}

void default_irqhandler(unsigned int giccIarm, void *userParam) {
	while (1);
}

