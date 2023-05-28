#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instructions.c"


char* hexadd(int number){
    char str[]={'0','0','0','0','\0'};
    int number2 = number;
    str[3]=number;
}

char* hexxx(int number) {
    int num = number;
    char str[5];
    sprintf(str, "%04x", num);
    printf("%s: ", str);
    return 0;
}

//the function that does everything
int process(char* hex_string, char* bin_string,unsigned int lenght_of_buffer){
    unsigned int end_index = 32*2 + lenght_of_buffer*2;
    unsigned int index = 32*2;
    unsigned int bin_index=32*2*4;
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    while (index<end_index)
    {
        hexxx((index-32*2)/2);
        for (size_t i = 0; i < 14; i++)
        {
            printstr[i]=' ';
        }
        char sub_str[9];
        strncpy(sub_str, bin_string + bin_index, 8);
        sub_str[8] = '\0';


        //MOV immediate to Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1')
        {
            Generic_Process_One(sub_str,&index,&bin_index,hex_string,bin_string,0,5,0,4,0,0,6,"mov ",", ","",2);
            continue;
        }
        
        //INT Specified
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            INT_Specified(sub_str,&index,&bin_index,hex_string);
            continue;
        }

        //MOV Register/Memory to Segment Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='0'&&bin_string[bin_index+10]=='0')
        {
            Generic_Process_NODW_Segment(sub_str,&index,&bin_index,hex_string,bin_string,8,11,13,4,"mov ", ", ","",0,0);
            continue;
        }

        //MOV Register/Memory to Segment Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0'&&bin_string[bin_index+10]=='0')
        {
            Generic_Process_NODW_Segment(sub_str,&index,&bin_index,hex_string,bin_string,8,11,13,4,"mov ", ", ","",0,1);
            continue;
        }

        //ADD Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"add ", ", ","",0);
            continue;
        }

        //ADC Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"adc ", ", ","",0);
            continue;
        }

        //SUB Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"sub ", ", ","",0);
            continue;
        }

        //SSB Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"ssb ", ", ","",0);
            continue;
        }

        //CMP Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"cmp ", ", ","",0);
            continue;
        }

        //AND Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"and ", ", ","",0);
            continue;
        }

        //OR Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"or ", ", ","",0);
            continue;
        }
        
        //XOR Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"xor ", ", ", "",0);
            continue;
        }

        //MOV Register/Memory to/from Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"mov ", ", ", "",0);
            continue;
        }

        //SHL/SAL Shift Logical/Arithmetic Left
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='0')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"shl ", ", ", "",0);
            continue;
        }

        //SHR shift logical right
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='1')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"shr ", ", ", "",0);
            continue;
        }

        //SAR shift arithmetic right
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='1')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"sar ", ", ", "",0);
            continue;
        }

        //ROL rotate left
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='0')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"rol ", ", ", "",0);
            continue;
        }

        //ROR rotate right
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='1')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"ror ", ", ", "",0);
            continue;
        }

        //RCL rotate through carry flag left
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='0')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"rcl ", ", ", "",0);
            continue;
        }

        //RCL rotate through carry right
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='1')
        {
            Generic_Process_VW(sub_str,&index,&bin_index,hex_string,bin_string,8,6,7,14,4,"rcr ", ", ", "",0);
            continue;
        }

        //LEA  Load EA to Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NODW(sub_str,&index,&bin_index,hex_string,bin_string,8,10,13,4,"lea ", ", ","",0);
            continue;
        }

        //LDS load pointer to DS
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NODW(sub_str,&index,&bin_index,hex_string,bin_string,8,10,13,4,"lds ", ", ","",0);
            continue;
        }

        //LES load pointer to ES
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NODW(sub_str,&index,&bin_index,hex_string,bin_string,8,10,13,4,"les ", ", ","",0);
            continue;
        }

        //ADD Immediate to Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='0')
        {
            if (bin_string[bin_index+6]=='0'&&bin_string[bin_index+7]=='1')
            {
                Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,8,"add ", ", ", "",0,4);
            }
            else Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,6,"add ", ", ", "",0,4);

            continue;
        }

        //ADC Immediate to Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='0')
        {
            if (bin_string[bin_index+6]=='0'&&bin_string[bin_index+7]=='1')
            {
                Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,8,"adc ", ", ", "",0,4);
            }
            else Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,6,"adc ", ", ", "",0,4);

            continue;
        }

        //SUB Immediate from Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='1')
        {
            if (bin_string[bin_index+6]=='0'&&bin_string[bin_index+7]=='1')
            {
                Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,8,"sub ", ", ", "",0,4);
            }
            else Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,6,"sub ", ", ", "",0,4);

            continue;
        }

        //SSB Immediate from Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='1')
        {
            if (bin_string[bin_index+6]=='0'&&bin_string[bin_index+7]=='1')
            {
                Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,8,"ssb ", ", ", "",0,4);
            }
            else Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,6,"ssb ", ", ", "",0,4);

            continue;
        }

        //CMP Immediate with Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='1')
        {
            if (bin_string[bin_index+6]=='0'&&bin_string[bin_index+7]=='1')
            {
                Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,8,"cmp ", ", ", "",0,4);
            }
            else Generic_Process_NOREG_S(sub_str,&index,&bin_index,hex_string,bin_string,8,0,7,13,6,6,"cmp ", ", ", "",0,4);

            continue;
        }
        
        //JNB immediate to Register
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jnb ","",2,2);
            continue;
        }

        //TEST Immediate Data and Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='0')
        {
            if (bin_string[bin_index+7]=='1')
            {
                Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,8,4,"test ",",","",2);
            }
            Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,6,4,"test ",", ","",2);
            continue;
        }

        //AND Immediate Data and Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='0')
        {
            if (bin_string[bin_index+7]=='1')
            {
                Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,8,4,"and ",",","",2);
            }
            Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,6,4,"and ",", ","",2);
            continue;
        }

        //MOV Immediate Data and Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='0')
        {
            if (bin_string[bin_index+7]=='1')
            {
                Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,8,4,"mov ",",","",2);
            }
            Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,6,4,"mov ",", ","",2);
            continue;
        }

        //OR Immediate Data and Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='1')
        {
            if (bin_string[bin_index+7]=='1')
            {
                Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,8,4,"or ",",","",2);
            }
            Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,6,4,"or ",", ","",2);
            continue;
        }

        //OR Immediate Data and Register/Memory
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&bin_string[bin_index+10]=='1'&&bin_string[bin_index+11]=='1'&&bin_string[bin_index+12]=='0')
        {
            if (bin_string[bin_index+7]=='1')
            {
                Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,8,4,"xor ",",","",2);
            }
            Generic_Process_IMMEDIATE(sub_str,&index,&bin_index,hex_string,bin_string,8,7,13,6,4,"xor ",", ","",2);
            continue;
        }

        //JNE Jump on Not Equal/Not Zero
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jne ","",2,2);
            continue;
        }

        //JE/JZ Jump on Equal/Zero
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"je ","",2,2);
            continue;
        }

        //JL/JNGE Jump on Less/Not Greater or Equal
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jl ","",2,2);
            continue;
        }

        //JLE/JNG Jump on Less or Equal/ Not Greater
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jle ","",2,2);
            continue;
        }

        //JB/JNAE Jump on Below/Not Above or Equal
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jb ","",2,2);
            continue;
        }

        //JBE/JNA Jump on Below or Equal/Not Above
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jbe ","",2,2);
            continue;
        }

        //JP/JPE Jump on Parity/Parity Even
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jp ","",2,2);
            continue;
        }

        //JO Jump on Overflow
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jo ","",2,2);
            continue;
        }

        //JS Jump on Sign
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"js ","",2,2);
            continue;
        }

        //JNL/JGE Jump on not less/greater or equal
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jnl ","",2,2);
            continue;
        }

        //JNLE/JG Jump on Not less or equal/greater
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jnle ","",2,2);
            continue;
        }

        //JNBE/JA Jump on Not below or equal/above
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jnbe ","",2,2);
            continue;
        }

        //JNP/JPO Jump on Not below or equal/above
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jnp ","",2,2);
            continue;
        }

        //JNO Jump on not overflow
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jno ","",2,2);
            continue;
        }

        //JNS jump on not sign
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jns ","",2,2);
            continue;
        }

        //LOOP Loop CX times
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"loop ","",2,2);
            continue;
        }

        //LOOPZ/LOOPE loop while zero/equal
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"loopz ","",2,2);
            continue;
        }

        //LOOPNZ/LOOPNE loop while not zero/equal
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"loopnz ","",2,2);
            continue;
        }

        //JCXZ jump on CX zero
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jcxz ","",2,2);
            continue;
        }

        //PUSH Register
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0')
        {
            Generic_Process_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,5,2,"push ","");
            continue;
        }

        //DEC Register
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1')
        {
            Generic_Process_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,5,2,"dec ","");
            continue;
        }

        //POP Register
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1')
        {
            Generic_Process_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,5,2,"pop ","");
            continue;
        }

        //XCHG Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0')
        {
            Generic_Process_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,5,2,"xchg ","");
            continue;
        }

        //INC Register
        if (sub_str[0]=='0'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0')
        {
            Generic_Process_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,5,2,"inc ","");
            continue;
        }

        //PUSH Segment Register
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_Segment_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,3,2,"push ","");
            continue;
        }

        //POP Segment Register
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_Segment_REGISTER(sub_str,&index,&bin_index,hex_string,bin_string,3,2,"pop ","");
            continue;
        }

        //CALL Direct Within Segment
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,6,"call ","",2,4);
            continue;
        }

        //JMP Direct within segment
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,6,"jmp ","",2,4);
            continue;
        }

        //JMP Direct within segment-short
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jmp short ","",2,2);
            continue;
        }

        //INT Type 3
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"int","");
            continue;
        }

        //INTO
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"into","");
            continue;
        }

        //IRET
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"iret","");
            continue;
        }

        //CLC
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"clc","");
            continue;
        }

        //CMC
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"cmc","");
            continue;
        }

        //STC
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"stc","");
            continue;
        }

        //CLD
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"cld","");
            continue;
        }

        //STD
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"std","");
            continue;
        }

        //CLI
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"cli","");
            continue;
        }

        //STI
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"sti","");
            continue;
        }

        //HLT
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"hlt","");
            continue;
        }

        //WAIT
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"wait","");
            continue;
        }

        //LOCK
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"lock","");
            continue;
        }

        //AAA
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"aaa","");
            continue;
        }

        //BAA
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"baa","");
            continue;
        }

        //AAS
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"aas","");
            continue;
        }

        //AAS
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"das","");
            continue;
        }

        //AAM
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0'&&bin_string[bin_index+8]=='0'&&bin_string[bin_index+9]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='1'&&bin_string[bin_index+13]=='0'&&bin_string[bin_index+14]=='1'&&bin_string[bin_index+15]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,4,"aam","");
            continue;
        }

        //AAD
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1'&&bin_string[bin_index+8]=='0'&&bin_string[bin_index+9]=='0'&&bin_string[bin_index+10]=='0'&&bin_string[bin_index+11]=='0'&&bin_string[bin_index+12]=='1'&&bin_string[bin_index+13]=='0'&&bin_string[bin_index+14]=='1'&&bin_string[bin_index+15]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,4,"aad","");
            continue;
        }

        //CBW
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"cbw","");
            continue;
        }

        //CWD
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='1'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"cwd","");
            continue;
        }

        //RET Within Segment
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"ret","");
            continue;
        }

        //RET Intersegment
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='0'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"ret","");
            continue;
        }

        //XLAT 
        if (sub_str[0]=='1'&&sub_str[1]=='1'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='0'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"xlat","");
            continue;
        }

        //LAHF 
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"lahf","");
            continue;
        }

        //SAHF 
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='1'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"sahf","");
            continue;
        }

        //PUSHF 
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='0')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"pushf","");
            continue;
        }

        //POPF 
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='1'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            Generic_Process_NOTHING(sub_str,&index,&bin_index,hex_string,bin_string,2,"popf","");
            continue;
        }

        else
        {
            printstr[0]=hex_string[index];
            printstr[1]=hex_string[index+1];
            printf("%s",printstr);
            printf("(undefined)\n");
            index+=2;
            bin_index+=8;
            continue;
        }
        
    }
    printf("\n");
}

// Convert a single hexadecimal character to its binary representation
char* hexCharToBin(char c)
{
    switch (c)
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a':
        case 'A': return "1010";
        case 'b':
        case 'B': return "1011";
        case 'c':
        case 'C': return "1100";
        case 'd':
        case 'D': return "1101";
        case 'e':
        case 'E': return "1110";
        case 'f':
        case 'F': return "1111";
        default: return ""; // Invalid character
    }
}

// Convert a hexadecimal string to its binary representation
void hexToBin(const char* hexStr, char* binStr)
{
    size_t hexLen = strlen(hexStr);
    size_t binIndex = 0;
    for (size_t i = 0; i < hexLen; i++)
    {
        char* bin = hexCharToBin(hexStr[i]);
        if (strlen(bin) == 0)
        {
            // Invalid character, return empty string
            binStr[0] = '\0';
            return;
        }
        size_t binLen = strlen(bin);
        strncpy(binStr + binIndex, bin, binLen);
        binIndex += binLen;
    }
    binStr[binIndex] = '\0';
}

int main() {
    FILE *file;
    char *buffer;
    long file_length;
    char hex_string[1025] = ""; // Initialize an empty string
    char bin_string[4097]={0};

    // Open the file
    file = fopen("a.out", "rb");
    if (!file) {
        printf("Error: file not found\n");
        return 1;
    }

    // Get the file length
    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    rewind(file);
    
    // Allocate memory for the buffer
    buffer = (char *)malloc(file_length);

    // Read the file into the buffer
    fread(buffer, file_length, 1, file);


    unsigned int little_endian_value = 0;
    unsigned int lenght_of_buffer = 0;

    
    // Extract the little endian lenght_of_buffer from addresses 0x08 to 0x0B
    little_endian_value = ((unsigned int)buffer[0x0B] << 24) | 
                          ((unsigned int)buffer[0x0A] << 16) | 
                          ((unsigned int)buffer[0x09] << 8) | 
                          (unsigned int)buffer[0x08];

    lenght_of_buffer = (unsigned int)little_endian_value;
    // Display the little endian value
    //printf("Little endian value: 0x%08x\n", little_endian_value);
    //printf("int lenght_of_buffer: %u\n",lenght_of_buffer);

    // Add the hex and binary bytes to their respective strings
    for (int i = 0; i < 32*2+lenght_of_buffer; i++) {
        // Add the hex byte to the hex string
        sprintf(hex_string + strlen(hex_string), "%02x", (unsigned char)buffer[i]);

    }
    hexToBin(hex_string,bin_string);
    // Display the hex and binary strings
    //printf("Hex string: %s\n", hex_string);
    //printf("Binary string: %s\n", bin_string);



    process(hex_string,bin_string,lenght_of_buffer);

    // Display the hex string
    //printf("full buffer: %s\n", hex_string);

    // Clean up
    free(buffer);
    fclose(file);

    return 0;
}
