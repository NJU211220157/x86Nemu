#include "cpu/instr.h"

void load_sreg(uint8_t sreg);

static void instr_execute_2op() 
{
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)


make_instr_func(mov_c2r_l){
    int len = 1;
    
    OPERAND r,rm;
    
    r.data_size = 32;
    rm.data_size = 32;
    
    len += modrm_r_rm(eip + 1, &r, &rm);
    
    rm.type = OPR_CREG;//没有这个语句，段错误
    operand_read(&rm);
    r.val = rm.val;
    operand_write(&r);
    
    print_asm_2("mov", "", len, &rm, &r);
    
    return len;
}

make_instr_func(mov_r2c_l){
    int len = 1;
    
    OPERAND r,rm;

    r.data_size = 32;
    rm.data_size = 32;
    
    len += modrm_r_rm(eip + 1, &r, &rm);
    
    r.type = OPR_CREG;
    operand_read(&rm);
    r.val = rm.val;
    operand_write(&r);
    
    print_asm_2("mov", "", len, &rm, &r);
    
    return len;
}

make_instr_func(mov_rm2s_w){
    int len = 1;
    
    OPERAND r,rm;
    r.sreg = SREG_CS;
    rm.sreg = SREG_CS;
    
    r.data_size = 16;
    rm.data_size = data_size;
    len += modrm_r_rm(eip + 1, &r, &rm);
    
    operand_read(&rm);
    r.val = rm.val&0xffff;
    operand_write(&r);
    load_sreg(1);
    
    print_asm_2("mov", "", len, &rm, &r);
    
    return len;
}

make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
        return len;
}
