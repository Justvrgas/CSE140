#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "computer.h"
#undef mips			/* gcc already has a def for mips */

unsigned int endianSwap(unsigned int);

void PrintInfo (int changedReg, int changedMem);
unsigned int Fetch (int);
void Decode (unsigned int, DecodedInstr*, RegVals*);
int Execute (DecodedInstr*, RegVals*);
int Mem(DecodedInstr*, int, int *);
void RegWrite(DecodedInstr*, int, int *);
void UpdatePC(DecodedInstr*, int);
void PrintInstruction (DecodedInstr*);

/*Globally accessible Computer variable*/
Computer mips;
RegVals rVals;

/*
 *  Return an initialized computer with the stack pointer set to the
 *  address of the end of data memory, the remaining registers initialized
 *  to zero, and the instructions read from the given file.
 *  The other arguments govern how the program interacts with the user.
 */
void InitComputer (FILE* filein, int printingRegisters, int printingMemory,
  int debugging, int interactive) {
    int k;
    unsigned int instr;

    /* Initialize registers and memory */

    for (k=0; k<32; k++) {
        mips.registers[k] = 0;
    }

    /* stack pointer - Initialize to highest address of data segment */
    mips.registers[29] = 0x00400000 + (MAXNUMINSTRS+MAXNUMDATA)*4;

    for (k=0; k<MAXNUMINSTRS+MAXNUMDATA; k++) {
        mips.memory[k] = 0;
    }

    k = 0;
    while (fread(&instr, 4, 1, filein)) {
	/*swap to big endian, convert to host byte order. Ignore this.*/
        mips.memory[k] = ntohl(endianSwap(instr));
        k++;
        if (k>MAXNUMINSTRS) {
            fprintf (stderr, "Program too big.\n");
            exit (1);
        }
    }

    mips.printingRegisters = printingRegisters;
    mips.printingMemory = printingMemory;
    mips.interactive = interactive;
    mips.debugging = debugging;
}

unsigned int endianSwap(unsigned int i) {
    return (i>>24)|(i>>8&0x0000ff00)|(i<<8&0x00ff0000)|(i<<24);
}

/*
 *  Run the simulation.
 */
void Simulate () {
    char s[40];  /* used for handling interactive input */
    unsigned int instr;
    int changedReg=-1, changedMem=-1, val;
    DecodedInstr d;
    
    /* Initialize the PC to the start of the code section */
    mips.pc = 0x00400000;
    while (1) {
        if (mips.interactive) {
            printf ("> ");
            fgets (s,sizeof(s),stdin);
            if (s[0] == 'q') {
                return;
            }
        }

        /* Fetch instr at mips.pc, returning it in instr */
        instr = Fetch (mips.pc);

        printf ("Executing instruction at %8.8x: %8.8x\n", mips.pc, instr);

        /* 
	 * Decode instr, putting decoded instr in d
	 * Note that we reuse the d struct for each instruction.
	 */
        Decode (instr, &d, &rVals);
        /*Print decoded instruction*/
        PrintInstruction(&d);

        /* 
	 * Perform computation needed to execute d, returning computed value 
	 * in val 
	 */
        val = Execute(&d, &rVals);

	UpdatePC(&d,val);

        /* 
	 * Perform memory load or store. Place the
	 * address of any updated memory in *changedMem, 
	 * otherwise put -1 in *changedMem. 
	 * Return any memory value that is read, otherwise return -1.
         */
        val = Mem(&d, val, &changedMem);

        /* 
	 * Write back to register. If the instruction modified a register--
	 * (including jal, which modifies $ra) --
         * put the index of the modified register in *changedReg,
         * otherwise put -1 in *changedReg.
         */
        RegWrite(&d, val, &changedReg);

        PrintInfo (changedReg, changedMem);
    }
}

/*
 *  Print relevant information about the state of the computer.
 *  changedReg is the index of the register changed by the instruction
 *  being simulated, otherwise -1.
 *  changedMem is the address of the memory location changed by the
 *  simulated instruction, otherwise -1.
 *  Previously initialized flags indicate whether to print all the
 *  registers or just the one that changed, and whether to print
 *  all the nonzero memory or just the memory location that changed.
 */
void PrintInfo ( int changedReg, int changedMem) {
    int k, addr;
    printf ("New pc = %8.8x\n", mips.pc);
    if (!mips.printingRegisters && changedReg == -1) {
        printf ("No register was updated.\n");
    } else if (!mips.printingRegisters) {
        printf ("Updated r%2.2d to %8.8x\n",
        changedReg, mips.registers[changedReg]);
    } else {
        for (k=0; k<32; k++) {
            printf ("r%2.2d: %8.8x  ", k, mips.registers[k]);
            if ((k+1)%4 == 0) {
                printf ("\n");
            }
        }
    }
    if (!mips.printingMemory && changedMem == -1) {
        printf ("No memory location was updated.\n");
    } else if (!mips.printingMemory) {
        printf ("Updated memory at address %8.8x to %8.8x\n",
        changedMem, Fetch (changedMem));
    } else {
        printf ("Nonzero memory\n");
        printf ("ADDR	  CONTENTS\n");
        for (addr = 0x00400000+4*MAXNUMINSTRS;
             addr < 0x00400000+4*(MAXNUMINSTRS+MAXNUMDATA);
             addr = addr+4) {
            if (Fetch (addr) != 0) {
                printf ("%8.8x  %8.8x\n", addr, Fetch (addr));
            }
        }
    }
    
}
    
/*
 *  Return the contents of memory at the given address. Simulates
 *  instruction fetch. 
 */
unsigned int Fetch ( int addr) {
    return mips.memory[(addr-0x00400000)/4];
}

/* Decode instr, returning decoded instruction. */
//DONE
void Decode ( unsigned int instr, DecodedInstr* d, RegVals* rVals) {
    
    /*
        R-Format instruction Decode
     */
    if(instr >> 26 == 0){
        //OPCODE
        d->op = instr >> 26;
        printf("OPCODE: %d\n", d->op);
        //setting the type of instruction
        d->type = R;
        //RS
        d->regs.r.rs = instr << 6;
        d->regs.r.rs = d->regs.r.rs >> 27;
        printf("RS: %d\n", d->regs.r.rs);
        //RT
        d->regs.r.rt = instr << 11;
        d->regs.r.rt = d->regs.r.rt >> 27;
        printf("RT: %d\n", d->regs.r.rt);
        //RD
        d->regs.r.rd = instr << 16;
        d->regs.r.rd = d->regs.r.rd >> 27;
        printf("RD: %d\n", d->regs.r.rd);
        //SHAMT
        d->regs.r.shamt = instr << 21;
        d->regs.r.shamt = d->regs.r.shamt >> 27;
        printf("SHAMT: %d\n", d->regs.r.shamt);
        //FUNCT
        unsigned int temp = instr << 26;
        d->regs.r.funct = temp >> 26;
        printf("FUNCT: %d\n", d->regs.r.funct);
        //setting register values
        rVals->R_rs = mips.registers[d->regs.r.rs];
        rVals->R_rt = mips.registers[d->regs.r.rt];
        rVals->R_rd = mips.registers[d->regs.r.rd];
        // abort();
    }
    /*
        J-Format instruction Deocode
     */
    else if(instr >> 26 == 2 || instr >> 26 == 3){
        d->type = J;
        d->op = instr >> 26;
        printf("OP: %d\n", d->op);
        d->regs.j.target = instr << 6;
        d->regs.j.target = d->regs.j.target >> 4;
        printf("TARGET: %d\n", d->regs.j.target);
      
        // abort();
    }
    /*
        I-Format instruction Decode
     */
    else{
        d->type = I;

        d->op = instr >> 26;
        printf("OP: %d\n", d->op);
        d->regs.i.rs = instr << 6;
        d->regs.i.rs = d->regs.i.rs >> 27;
        printf("RS: %d\n", d->regs.i.rs);
        d->regs.i.rt = instr << 11;
        d->regs.i.rt = d->regs.i.rt >> 27;
        printf("RT: %d\n", d->regs.i.rt);

        /*
            addiu instruction
            test dump file : I_instruction_1.dump
            addiu $t1, $t2, -150
         */
        if (d->op == 9){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed);
        }
        /*
            andi instruction
            test dump file : I_instruction_2.dump
            andi $t1, $t2, 100
         */
        else if (d->op == 12){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed);
        }
        /*
            ori instruction
            test dump file : I_instruction_3.dump
            ori $t1, $t2, 100
         */
        else if (d->op == 13){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed);
        }
        /*
            lui instruction
            test dump file : I_instruction_4.dump
            lui $t1, 100
         */
        else if (d->op == 15){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed); 
        }
        /*
            beq instruction
            test dump file : I_instruction_5.dump
            beq $t1, $t2, label
            label:
         */
        else if (d->op == 4){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed); 
        }
        /*
            bne instruction
            test dump file : I_instruction_5.dump
            bne $t1, $t2, label
            label:
         */
        else if (d->op == 5){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed); 
        }
        /*
            lw instruction
            test dump file : I_instruction_7.dump
            lw $t1, ($t2)
         */
        else if (d->op == 35){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed);
        }
        /*
            sw instruction
            test dump file : I_instruction_8.dump
            sw $t1, ($t2)
         */
        else if(d->op == 43){
           d->regs.i.addr_or_immed = instr << 16;
           d->regs.i.addr_or_immed = d->regs.i.addr_or_immed >> 16;
           printf("IMMEDIATE: %d\n", d->regs.i.addr_or_immed);            
        }

        rVals->R_rs = mips.registers[d->regs.i.rs];
        rVals->R_rt = mips.registers[d->regs.i.rt];
        // abort();
    }

}

/*
 *  Print the disassembled version of the given instruction
 *  followed by a newline.
 */

//DONE
void PrintInstruction ( DecodedInstr* d) {
    /*
        seperate the prints based off of their type
     */
    
    //R format prints
    if(d->type == 0){
        if(d->regs.r.funct == 33){
            printf("addu $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }
        else if(d->regs.r.funct == 36){
            printf("and $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }
        else if(d->regs.r.funct == 8){
            printf("jr $%d\n", d->regs.r.rs);
        }
        else if(d->regs.r.funct == 37){
            printf("or $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }
        else if(d->regs.r.funct == 42){
            printf("slt $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }
        else if(d->regs.r.funct == 0){
            printf("sll $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.shamt);
        }
        else if(d->regs.r.funct == 2){
            printf("srl $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.shamt);
        }
        else if(d->regs.r.funct == 35){
            printf("subu $%d, $%d, $%d\n", d->regs.r.rd, d->regs.r.rs, d->regs.r.rt);
        }

        // abort();
        
    }
    
    //I format prints
    else if(d->type == I){
        if(d->op == 9){
            printf("addiu $%d, $%d, %d\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
        }
        else if(d->op == 12){
            printf("andi $%d, $%d, %d\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
        }
        else if(d->op == 13){
            printf("ori $%d, $%d, %d\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
        }
        else if(d->op == 15){
            printf("lui $%d, %d\n", d->regs.i.rt, d->regs.i.addr_or_immed);
        }
        else if(d->op == 4){
            printf("beq $%d, $%d, %d\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
        }
        else if(d->op == 5){
            printf("bne $%d, $%d, %d\n", d->regs.i.rs, d->regs.i.rt, d->regs.i.addr_or_immed);
        }
        else if(d->op == 35){
            printf("lw $%d, %d($%d)\n", d->regs.i.rs, d->regs.i.addr_or_immed, d->regs.i.rt);
        }
        else if(d->op == 43){
            printf("sw $%d, %d($%d)\n", d->regs.i.rs, d->regs.i.addr_or_immed, d->regs.i.rt);
        }
        // abort();
    }

    //j format prints
    else{
        if(d->op == 2){
            printf("j 0x%08x\n", d->regs.j.target);
        }
        else if(d->op == 3){
            printf("jal 0x%08x\n", d->regs.j.target);
        }
    }
    // abort();
}

/* Perform computation needed to execute d, returning computed value */
int Execute ( DecodedInstr* d, RegVals* rVals) {
     int val = 0;

     if(d->type == 0){
        //addu
        if(d->regs.r.funct == 33){
            //rd = rs + rt
            rVals->R_rd = rVals->R_rs + rVals->R_rt;
            val = rVals->R_rd;
        }
        // and
        else if(d->regs.r.funct == 36){
            //rd = rs & rt
            rVals->R_rd = rVals->R_rs & rVals->R_rt;
            val = rVals->R_rd;
        }
        // jr
        else if(d->regs.r.funct == 8){
            /**
             * FINISH
             */
        }
        // or
        else if(d->regs.r.funct == 37){
            //rd = rs | rt
            rVals->R_rd = rVals->R_rs | rVals->R_rt;
            val = rVals->R_rd;
        }
        // slt
        else if(d->regs.r.funct == 42){
            //rd = 1 if rs < rt else rd = 0
            if(rVals->R_rs < rVals->R_rt){
                rVals->R_rd = 1;
                val = rVals->R_rd;
            }
            else{
                rVals->R_rd = 0;
                val = rVals->R_rd;
            }
        }
        // sll
        else if(d->regs.r.funct == 0){
            //rd = rt << shamt
            rVals->R_rd = rVals->R_rt << d->regs.r.shamt;
            val = rVals->R_rd;
        }
        // srl
        else if(d->regs.r.funct == 2){
            //rd = rt >> shamt
            rVals->R_rd = rVals->R_rt >> d->regs.r.shamt;
            val = rVals->R_rd;
        }
        // subu
        else if(d->regs.r.funct == 35){
            //rd = rs - rt
            rVals->R_rd = rVals->R_rs - rVals->R_rt;
            val = rVals->R_rd;
        }

        return val;
        // abort();
        
    }

    //i-format
    else if(d->type == I){
        //addiu
        if(d->op == 9){
            //rt = rs + imm
            rVals->R_rt = rVals->R_rs + d->regs.i.addr_or_immed;
        }
        //andi
        else if(d->op == 12){
            //
            rVals->R_rt = rVals->R_rs & d->regs.i.addr_or_immed;
        }
        //ori
        else if(d->op == 13){
            rVals->R_rt = rVals->R_rs | d->regs.i.addr_or_immed;
        }
        //lui
        else if(d->op == 15){
            rVals->R_rt = d->regs.i.addr_or_immed << 16;
        }
        //beq
        else if(d->op == 4){
            /**
             * FINISH
             */
        }
        //bne
        else if(d->op == 5){
            /**
             * FINISH
             */
        }
        //lw
        else if(d->op == 35){
            /**
             * FINISH
             */
        }
        //sw
        else if(d->op == 43){
            /**
             * FINISH
             */
        }
        // abort();
    }

    //j-format
    else{
        //j
        if(d->op == 2){
            /**
             * FINISH
             */
        }
        //jal
        else if(d->op == 3){
            /**
             * FINISH
             */
        }
    }



  return 0;
}

/* 
 * Update the program counter based on the current instruction. For
 * instructions other than branches and jumps, for example, the PC
 * increments by 4 (which we have provided).
 */
void UpdatePC ( DecodedInstr* d, int val) {
    
    if(d->type == R){
        printf("R FORMAT MEM\n");
        if(d->op != 8)
        {
            mips.pc += 4;
        }
    }

    else if(d->type == J){
        printf("J FORMAT MEM\n");
    }

    else{
        printf("I FORMAT MEM\n");
    }

    mips.pc+=4;
}

/*
 * Perform memory load or store. Place the address of any updated memory 
 * in *changedMem, otherwise put -1 in *changedMem. Return any memory value 
 * that is read, otherwise return -1. 
 *
 * Remember that we're mapping MIPS addresses to indices in the mips.memory 
 * array. mips.memory[0] corresponds with address 0x00400000, mips.memory[1] 
 * with address 0x00400004, and so forth.
 *
 */
int Mem( DecodedInstr* d, int val, int *changedMem) {
    /* Your code goes here */

    if(d->type == I){
        printf("R FORMAT MEM\n");
    }

    else if(d->type == J){
        printf("J FORMAT MEM\n");
    }

    else{
        printf("I FORMAT MEM\n");
    }

    return 0;
}

/* 
 * Write back to register. If the instruction modified a register--
 * (including jal, which modifies $ra) --
 * put the index of the modified register in *changedReg,
 * otherwise put -1 in *changedReg.
 */
void RegWrite( DecodedInstr* d, int val, int *changedReg) {
    /* Your code goes here */
}
