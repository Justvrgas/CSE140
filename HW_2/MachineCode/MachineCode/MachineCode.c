//  MachineCode.c
//  MachineCode
//
//  Collaborated with Byron Garcia
//  Copyright © 2019 Justin Vargas and Byron Garcia. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct instruction{
    char name[7];
    char opcode[7];
    char funct[3];
    char functToBinary[7];
    
};

struct registers{
    char binary[6];
    char decimal[4];
    char name[5];
};




int main(int argc, char const *argv[])
{
    char machineCode[32];
    
    struct instruction instructArr[12];
    
    struct instruction add;
    strcpy(add.name, "add");
    strcpy(add.opcode, "000000");
    strcpy(add.funct, "20");
    strcpy(add.functToBinary, "100000");
    instructArr[0] = add;
    
    struct instruction addu;
    strcpy(addu.name, "addu");
    strcpy(addu.opcode, "000000");
    strcpy(addu.funct, "21");
    strcpy(addu.functToBinary, "100001");
    instructArr[1] = addu;
    
    struct instruction and;
    strcpy(and.name, "and");
    strcpy(and.opcode, "000000");
    strcpy(and.funct, "24");
    strcpy(and.functToBinary, "100100");
    instructArr[2] = and;
    
    struct instruction jr;
    strcpy(jr.name, "jr");
    strcpy(jr.opcode, "000000");
    strcpy(jr.funct, "08");
    strcpy(jr.functToBinary, "001000");
    instructArr[3] = jr;
    
    struct instruction nor;
    strcpy(nor.name, "nor");
    strcpy(nor.opcode, "000000");
    strcpy(nor.funct, "27");
    strcpy(nor.functToBinary, "100111");
    instructArr[4] = nor;
    
    struct instruction or;
    strcpy(or.name, "or");
    strcpy(or.opcode, "000000");
    strcpy(or.funct, "25");
    strcpy(or.functToBinary, "100101");
    instructArr[5] = or;
    
    struct instruction slt;
    strcpy(slt.name, "slt");
    strcpy(slt.opcode, "000000");
    strcpy(slt.funct, "2a");
    strcpy(slt.functToBinary, "101010");
    instructArr[6] = slt;
    
    
    struct instruction sltu;
    strcpy(sltu.name, "sltu");
    strcpy(sltu.opcode, "000000");
    strcpy(sltu.funct, "2b");
    strcpy(sltu.functToBinary, "101011");
    instructArr[7] = sltu;
    
    struct instruction sll;
    strcpy(sll.name, "sll");
    strcpy(sll.opcode, "000000");
    strcpy(sll.funct, "00");
    strcpy(sll.functToBinary, "000000");
    instructArr[8] = sll;
    
    struct instruction srl;
    strcpy(srl.name, "srl");
    strcpy(srl.opcode, "000000");
    strcpy(srl.funct, "02");
    strcpy(srl.functToBinary, "000010");
    instructArr[9] = srl;
    
    struct instruction sub;
    strcpy(sub.name, "sub");
    strcpy(sub.opcode, "000000");
    strcpy(sub.funct, "22");
    strcpy(sub.functToBinary, "100010");
    instructArr[10] = sub;
    
    struct instruction subu;
    strcpy(subu.name, "subu");
    strcpy(subu.opcode, "000000");
    strcpy(subu.funct, "23");
    strcpy(subu.functToBinary, "100011");
    instructArr[11] = subu;
   

    struct registers regArr[32];

    struct registers zero;
    strcpy(zero.name, "zero");
    strcpy(zero.decimal, "R0");
    strcpy(zero.binary, "00000");
    regArr[0] = zero;

    struct registers at;
    strcpy(at.name, "at");
    strcpy(at.decimal, "R1");
    strcpy(at.binary, "00001");
    regArr[1] = at;

    struct registers v0;
    strcpy(v0.name, "v0");
    strcpy(v0.decimal, "R2");
    strcpy(v0.binary, "00010");
    regArr[2] = v0;

    struct registers v1;
    strcpy(v1.name, "v1");
    strcpy(v1.decimal, "R3");
    strcpy(v1.binary, "00011");
    regArr[3] = v1;

    struct registers a0;
    strcpy(a0.name, "a0");
    strcpy(a0.decimal, "R4");
    strcpy(a0.binary, "00100");
    regArr[4] = a0;

    struct registers a1;
    strcpy(a1.name, "a1");
    strcpy(a1.decimal, "R5");
    strcpy(a1.binary, "00101");
    regArr[5] = a1;

    struct registers a2;
    strcpy(a2.name, "a2");
    strcpy(a2.decimal, "R6");
    strcpy(a2.binary, "00110");
    regArr[6] = a2;

    struct registers a3;
    strcpy(a3.name, "a3");
    strcpy(a3.decimal, "R7");
    strcpy(a3.binary, "00111");
    regArr[7] = a3;

    struct registers t0;
    strcpy(t0.name, "t0");
    strcpy(t0.decimal, "R8");
    strcpy(t0.binary, "01000");
    regArr[8] = t0;

    struct registers t1;
    strcpy(t1.name, "t1");
    strcpy(t1.decimal, "R9");
    strcpy(t1.binary, "01001");
    regArr[9] = t1;

    struct registers t2;
    strcpy(t2.name, "t2");
    strcpy(t2.decimal, "R10");
    strcpy(t2.binary, "01010");
    regArr[10] = t2;

    struct registers t3;
    strcpy(t3.name, "t3");
    strcpy(t3.decimal, "R11");
    strcpy(t3.binary, "01011");
    regArr[11] = t3;

    struct registers t4;
    strcpy(t4.name, "t4");
    strcpy(t4.decimal, "R12");
    strcpy(t4.binary, "01100");
    regArr[12] = t4;

    struct registers t5;
    strcpy(t5.name, "t5");
    strcpy(t5.decimal, "R13");
    strcpy(t5.binary, "01101");
    regArr[13] = t5;

    struct registers t6;
    strcpy(t6.name, "t6");
    strcpy(t6.decimal, "R14");
    strcpy(t6.binary, "01110");
    regArr[14] = t6;

    struct registers t7;
    strcpy(t7.name, "t7");
    strcpy(t7.decimal, "R15");
    strcpy(t7.binary, "01111");
    regArr[15] = t7;

    struct registers s0;
    strcpy(s0.name, "s0");
    strcpy(s0.decimal, "R16");
    strcpy(s0.binary, "10000");
    regArr[16] = s0;

    struct registers s1;
    strcpy(s1.name, "s1");
    strcpy(s1.decimal, "R17");
    strcpy(s1.binary, "10001");
    regArr[17] = s1;

    struct registers s2;
    strcpy(s2.name, "s2");
    strcpy(s2.decimal, "R18");
    strcpy(s2.binary, "10010");
    regArr[18] = s2;

    struct registers s3;
    strcpy(s3.name, "s3");
    strcpy(s3.decimal, "R19");
    strcpy(s3.binary, "10011");
    regArr[19] = s3;

    struct registers s4;
    strcpy(s4.name, "s4");
    strcpy(s4.decimal, "R20");
    strcpy(s4.binary, "10100");
    regArr[20] = s4;

    struct registers s5;
    strcpy(s5.name, "s5");
    strcpy(s5.decimal, "R21");
    strcpy(s5.binary, "10101");
    regArr[21] = s5;

    struct registers s6;
    strcpy(s6.name, "s6");
    strcpy(s6.decimal, "R22");
    strcpy(s6.binary, "10110");
    regArr[22] = s6;

    struct registers s7;
    strcpy(s7.name, "s7");
    strcpy(s7.decimal, "R23");
    strcpy(s7.binary, "10111");
    regArr[23] = s7;

    struct registers t8;
    strcpy(t8.name, "t8");
    strcpy(t8.decimal, "R24");
    strcpy(t8.binary, "11000");
    regArr[24] = t8;

    struct registers t9;
    strcpy(t9.name, "t9");
    strcpy(t9.decimal, "R25");
    strcpy(t9.binary, "11001");
    regArr[25] = t9;

    struct registers k0;
    strcpy(k0.name, "k0");
    strcpy(k0.decimal, "R26");
    strcpy(k0.binary, "11010");
    regArr[26] = k0;

    struct registers k1;
    strcpy(k1.name, "k1");
    strcpy(k1.decimal, "R27");
    strcpy(k1.binary, "11011");
    regArr[27] = k1;

    struct registers gp;
    strcpy(gp.name, "gp");
    strcpy(gp.decimal, "R28");
    strcpy(gp.binary, "11100");
    regArr[28] = gp;

    struct registers sp;
    strcpy(sp.name, "sp");
    strcpy(sp.decimal, "R29");
    strcpy(sp.binary, "11101");
    regArr[29] = sp;

    struct registers fp;
    strcpy(fp.name, "fp");
    strcpy(fp.decimal, "R30");
    strcpy(fp.binary, "11110");
    regArr[30] = fp;

    struct registers ra;
    strcpy(ra.name, "ra");
    strcpy(ra.decimal, "R31");
    strcpy(ra.binary, "11111");
    regArr[31] = ra;
    
    

    fgets(machineCode, 32, stdin);  //gets whole instruction line (sample: add s0 s2 s4)
    
    const char s[2] = " ,";
    char *token;
    char *operation;
    char *Rs = NULL;
    char *Rd = NULL;
    char *Rt = NULL;
    char binaryCode[33];
    int binaryShamt[4];
    int count = 0;
    int intShamt = 0;

     /* get the first token */
    token = strtok(machineCode, s);
    operation = token;
    printf("Operation: %s\n", operation);
    strcat(binaryCode, "000000"); //opcode is always "000000" for R-Instruction
    
    //if operation is "srl"
    if (*operation == 's' && *(operation+1) == 'r' && *(operation+2) == 'l') {
        while( token != NULL ) {     // first iteration in the while loop but the second token 's0'
            token = strtok(NULL, s);
            if(count == 0){
                Rd = token;
            }
            else if (count == 1) {
                Rt = token;
            }
            else if (count == 2) {
                Rs = token;
                Rs[2] = ' ';
            }
            count++;
        }
        
        // converting char shamt input to binary
        
        intShamt = atoi(Rs); // Make string an integer to convert into a binary value

        for (int i = 0; i <= 4; i++) {
            binaryShamt[i] = intShamt % 2;
            intShamt = (intShamt - binaryShamt[i]) / 2;
        }
        
        intShamt = atoi(Rs); // Make string an integer to convert into a binary value

//        for (int i = 4; i >= 0; i--) {
//            printf("%d", binaryShamt[i]);
//        }
//
//        printf("\n");
       
        printf("Rs: 0(R0)\n");
        strcat(binaryCode, "00000");
        
        for(int i = 0; i < sizeof(regArr); i++){
            if (*Rt == *regArr[i].name && *(Rt+1) == *(regArr[i].name+1)) {
                printf("Rt: %s", Rt);
                printf("(%s)\n", regArr[i].decimal);
                strcat(binaryCode, regArr[i].binary);
                break;
            }
        }
        
        for(int i = 0; i < sizeof(regArr); i++){
            if (*Rd == *regArr[i].name && *(Rd+1) == *(regArr[i].name+1)) {
                printf("Rd: %s", Rd);
                printf("(%s)\n", regArr[i].decimal);
                strcat(binaryCode, regArr[i].binary);
                break;
            }
        }
        
        printf("Shamt: %d\n", intShamt);
        printf("Funct: 2\n");
        
        printf("Machine Code: %s", binaryCode);
        for (int i = 0; i <= 4; i++) {
            binaryShamt[i] = intShamt % 2;
            intShamt = (intShamt - binaryShamt[i]) / 2;
        }
        for (int i = 4; i >= 0; i--) {
            printf("%d", binaryShamt[i]);
        }
        printf("00010\n");
      
    }

    /* if operation is sll*/
    else if (*operation == 's' && *(operation+1) == 'l' && *(operation+2) == 'l'){
        while( token != NULL ) {     // first iteration in the while loop but the second token 's0'
                token = strtok(NULL, s);
                if(count == 0){
                    Rd = token;
                }
                else if (count == 1) {
                    Rt = token;
                }
                else if (count == 2) {
                    Rs = token;
                    Rs[2] = ' ';
                }
                count++;
            }
            
            // converting char shamt input to binary
            
            intShamt = atoi(Rs); // Make string an integer to convert into a binary value

            for (int i = 0; i <= 4; i++) {
                binaryShamt[i] = intShamt % 2;
                intShamt = (intShamt - binaryShamt[i]) / 2;
            }
            
            intShamt = atoi(Rs); // Make string an integer to convert into a binary value

    //        for (int i = 4; i >= 0; i--) {
    //            printf("%d", binaryShamt[i]);
    //        }
    //
    //        printf("\n");
           
            printf("Rs: 0(R0)\n");
            strcat(binaryCode, "00000");
            
            for(int i = 0; i < sizeof(regArr); i++){
                if (*Rt == *regArr[i].name && *(Rt+1) == *(regArr[i].name+1)) {
                    printf("Rt: %s", Rt);
                    printf("(%s)\n", regArr[i].decimal);
                    strcat(binaryCode, regArr[i].binary);
                    break;
                }
            }
            
            for(int i = 0; i < sizeof(regArr); i++){
                if (*Rd == *regArr[i].name && *(Rd+1) == *(regArr[i].name+1)) {
                    printf("Rd: %s", Rd);
                    printf("(%s)\n", regArr[i].decimal);
                    strcat(binaryCode, regArr[i].binary);
                    break;
                }
            }
            
            printf("Shamt: %d\n", intShamt);
            printf("Funct: 0\n");
            
            printf("Machine Code: %s", binaryCode);
            for (int i = 0; i <= 4; i++) {
                binaryShamt[i] = intShamt % 2;
                intShamt = (intShamt - binaryShamt[i]) / 2;
            }
            for (int i = 4; i >= 0; i--) {
                printf("%d", binaryShamt[i]);
            }
            printf("00000\n");
    }

    /* if operation is jr */
    else if (*operation == 'j' && *(operation+1) == 'r' ){
        token = strtok(NULL, s);
        Rs = token;
        Rs[2] = ' ';
        
        for(int i = 0; i < sizeof(regArr); i++){
            if (*Rs == *regArr[i].name && *(Rs+1) == *(regArr[i].name+1)) {
                printf("Rs: %s", Rs);
                printf(" (%s)\n", regArr[i].decimal);
                strcat(binaryCode, regArr[i].binary);
                break;
            }
        }
        
        printf("Rt: 0 (R0)\n");
        strcat(binaryCode, "00000");
        printf("Rd: 0 (R0)\n");
        strcat(binaryCode, "00000");
        printf("Shamt: 0\n");
        strcat(binaryCode, "00000");
        printf("Funct: 8\n");
        strcat(binaryCode, instructArr[3].functToBinary);
        
        printf("Machine Code: %s\n", binaryCode);
    }
    
    
    /* if operation is any arithmetic operation */
    else{
        //printf("other stuff");
        while( token != NULL ) {     // first iteration in the while loop but the second token 's0'
            token = strtok(NULL, s);
            if(count == 0){
                Rd = token;
            }
            else if (count == 1) {
                Rs = token;
            }
            else if (count == 2) {
                Rt = token;
                Rt[2] = ' ';
            }
            count++;
        }
        
        
        for(int i = 0; i < sizeof(regArr); i++){
            if (*Rs == *regArr[i].name && *(Rs+1) == *(regArr[i].name+1)) {
                printf("Rs: %s", Rs);
                printf(" (%s)\n", regArr[i].decimal);
                strcat(binaryCode, regArr[i].binary);
                break;
            }
        }
        
        for(int i = 0; i < sizeof(regArr); i++){
            if (*Rt == *regArr[i].name && *(Rt+1) == *(regArr[i].name+1)) {
                printf("Rt: %s", Rt);
                printf("(%s)\n", regArr[i].decimal);
                strcat(binaryCode, regArr[i].binary);
                break;
            }
        }
        
        for(int i = 0; i < sizeof(regArr); i++){
            if (*Rd == *regArr[i].name && *(Rd+1) == *(regArr[i].name+1)) {
                printf("Rd: %s", Rd);
                printf(" (%s)\n", regArr[i].decimal);
                strcat(binaryCode, regArr[i].binary);
                break;
            }
        }
        
        printf("Shamt: %s\n", "00000");
        strcat(binaryCode, "00000");
        
        for(int i = 0; i < sizeof(instructArr); i++){
            if (*operation == *instructArr[i].name && *(operation+1) == *(instructArr[i].name+1) && *(operation+2) == *(instructArr[i].name+2) && *(operation+3) == *(instructArr[i].name+3)) {
                printf("Funct: %s\n", instructArr[i].funct);
                strcat(binaryCode, instructArr[i].functToBinary);
                break;
            }
        }
        
        printf("Machine Code: %s\n", binaryCode);
    }
    
    

    return 0;
}

