#include "cpu/instr.h"
/*
Put the implementations of `lgdt' instructions here.
*/

make_instr_func(lgdt)
{
    OPERAND rm;
    rm.data_size = 16;
    int len = 1;
    
    len += modrm(eip + 1,&rm);
    operand_read(&rm);
    cpu.gdtr.limit = rm.val;
    
    rm.addr += 2;
    rm.data_size = 32;
    operand_read(&rm);
    cpu.gdtr.base = rm.val;
    
    return len;
}
