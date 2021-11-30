OUTPUT_ARCH(riscv)
ENTRY(_start)
MEMORY
{
	ram  : org = 0x80000000, len = 10M
}

SECTIONS
{
	.text :
	{
		*(.init)
		*(.text*)
	} > ram

	.data ALIGN(4) :
	{
		*(.data*)
    	*(.rodata*)
		. = ALIGN(4);
	} > ram

	PROVIDE(__bss_start = .);
	.bss ALIGN(4) :
	{
		*(.bss*)
		. = ALIGN(4);
	} > ram
	PROVIDE(__bss_end = .);

  PROVIDE(__stack_end = 0x80000000+1M);
}
