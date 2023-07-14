#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void append_str(char str[] , char c){
     auto char arr[2] = {c , '\0'};
     strcat(str , arr);
}

void Parse2Args(char *msg, char *arg1, char *arg2)
{
    int k = 0;
    while (msg[k] != 0)
    {
        if (msg[k]==' ')
        {
            k++;
            while(msg[k]!=',')
            {
                append_str(arg1 , msg[k]);
                k++;
            }
        }
        if (msg[k]==',')
        {
            k+=2;
            while(msg[k]!=0)
            {
                append_str(arg2 , msg[k]);
                k++;
            }
        }
        
        k++;
    }
    
}

void PushRegister(short chars, const char* regName, short* AX, short* BX, short* CX, short* DX, short* SP, short* BP, short* SI, short* DI)
{
    while (chars>32767)
    {
        chars-=65536;
    }
    
    if (strcmp(regName, "ax") == 0)
    {
        *AX = chars;
    }
    if (strcmp(regName, "bx") == 0)
    {
        *BX = chars;
    }
    if (strcmp(regName, "cx") == 0)
    {
        *CX = chars;
    }
    if (strcmp(regName, "dx") == 0)
    {
        *DX = chars;
    }
    if (strcmp(regName, "sp") == 0)
    {
        *SP = chars;
    }
    if (strcmp(regName, "bp") == 0)
    {
        *BP = chars;
    }
    if (strcmp(regName, "si") == 0)
    {
        *SI = chars;
    }
    if (strcmp(regName, "di") == 0)
    {
        *DI = chars;
    }
}

short GetRegister(const char* regName, short AX, short BX, short CX, short DX, short SP, short BP, short SI, short DI)
{
    if (strcmp(regName, "ax") == 0)
    {
        return AX;
    }
    if (strcmp(regName, "bx") == 0)
    {
        return BX;
    }
    if (strcmp(regName, "cx") == 0)
    {
        return CX;
    }
    if (strcmp(regName, "dx") == 0)
    {
        return DX;
    }
    if (strcmp(regName, "sp") == 0)
    {
        return SP;
    }
    if (strcmp(regName, "bp") == 0)
    {
        return BP;
    }
    if (strcmp(regName, "si") == 0)
    {
        return SI;
    }
    if (strcmp(regName, "di") == 0)
    {
        return DI;
    }
}

char* get_adress(char*data, char*adress)
{
    char* result = malloc(10*sizeof(char));
    int adressint = strtol(adress, NULL, 16);
    result[0] = data[adressint*2];
    result[1]=data[adressint*2+1];
    result[2]=data[adressint*2+2];
    result[3]=data[adressint*2+3];
    return result;
}
