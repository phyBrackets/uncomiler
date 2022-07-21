#include "defs.h"
#include "data.h"
#include "decl.h"

// list of available registers
static int freereg[4];
static const char *reglist[4] = {"%r8", "%r9", "%r10", "%r11"};

// set all register as available
void freeall_registers(void) {
    freereg[0] = freereg[1] = freereg[2] = freereg[3] = 1;
}

// allocate free register
static int alloc_register(void) {
    for(int i=0; i<4; i++) {
        if(freereg[i]) {
            freereg[i] = 0;
            return i;
        } 
    }
    std::cerr<<"out of registers\n";
    exit(1);
}

// return a regsiter to the list of available register 
static void free_register(int reg) {
    if(freereg[reg] !=0){
        std::cerr<< "error trying to free register" << reg << "\n";
        exit(1);
    }
    freereg[reg] = 1;
}

// Print out the assembly preamble
void cgpreamble()
{
  freeall_registers();
  fputs(
	"\t.text\n"
	".LC0:\n"
	"\t.string\t\"%d\\n\"\n"
	"printint:\n"
	"\tpushq\t%rbp\n"
	"\tmovq\t%rsp, %rbp\n"
	"\tsubq\t$16, %rsp\n"
	"\tmovl\t%edi, -4(%rbp)\n"
	"\tmovl\t-4(%rbp), %eax\n"
	"\tmovl\t%eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n"
	"\t.globl\tmain\n"
	"\t.type\tmain, @function\n"
	"main:\n"
	"\tpushq\t%rbp\n"
	"\tmovq	%rsp, %rbp\n",
  Outfile);
}

// Print out the assembly postamble
void cgpostamble()
{
  fputs(
	"\tmovl	$0, %eax\n"
	"\tpopq	%rbp\n"
	"\tret\n",
  Outfile);
}

// load an int lit value to register 
// return the no. of register
int cgload(int value) {
    // get a new register 
    int r = alloc_register();

    // print out the code to initialize it 
    fprintf(Outfile, "\tmovq\t$%d, %s\n",value, reglist[r]);
    return r;
}

// add two register and return 
// the no. of register with result 
int cgadd(int r1, int r2) {
    fprintf(Outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);
    return r2;
}

//multiply two registers together and return 
// the no. of the register with result 
int cgmul(int r1, int r2) {
    fprintf(Outfile, "timulq\t%s, %s\n", reglist[r1], reglist[r2]);
    free_register(r1);
    return r2;
}

// subtract two regs
int cgsub(int r1, int r2) {
  fprintf(Outfile, "\tsubq\t%s, %s\n", reglist[r2], reglist[r1]);
  free_register(r2);
  return r1;
}

// divide the first register by the second 
// return the number of the register with the result 
int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tmovq\t%s,%%rax\n", reglist[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidivq\t%s\n", reglist[r2]);
    fprintf(Outfile, "\tmovq\t%%rax,%s\n", reglist[r1]);
    free_register(r2);
    return r1;
}

// call printint() with the given register 
void cgprintint(int r) {
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", reglist[r]);
    fprintf(Outfile, "\tcall\tprintint\n");
    free_register(r);
}