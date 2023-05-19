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

        //ADD Reg Memory with register to either
        if (sub_str[0]=='0'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='0'&&sub_str[5]=='0')
        {
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,6,7,13,0,4,"add ", ", ","",0);
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

        //LEA  Load EA to Register
        if (sub_str[0]=='1'&&sub_str[1]=='0'&&sub_str[2]=='0'&&sub_str[3]=='0'&&sub_str[4]=='1'&&sub_str[5]=='1'&&sub_str[6]=='0'&&sub_str[7]=='1')
        {
            char sub[3];
            strncpy(sub,hex_string+index+4,2);
            sub[2]=0;
            int disp = (int)strtol(sub,NULL,16);
            Generic_Process(sub_str,&index,&bin_index,hex_string,bin_string,8,10,0,0,13,0,6,"lea ", ", ", "",disp);
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
            Generic_Process_JUMP(sub_str,&index,&bin_index,hex_string,bin_string,4,"jnb ","",2);
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
