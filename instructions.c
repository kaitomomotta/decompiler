#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* RegTable(char* regstr,int w)
{
    if (w==1)
    {
        if (strcmp(regstr,"000")==0)
        {
            return "ax";
        }
        if (strcmp(regstr,"001")==0)
        {
            return "cx";
        }
        if (strcmp(regstr,"010")==0)
        {
            return "dx";
        }
        if (strcmp(regstr,"011")==0)
        {
            return "bx";
        }
        if (strcmp(regstr,"100")==0)
        {
            return "sp";
        }
        if (strcmp(regstr,"101")==0)
        {
            return "bp";
        }
        if (strcmp(regstr,"110")==0)
        {
            return "si";
        }
        else
        {
            return "di";
        }
    }
    else
    {
        if (strcmp(regstr,"000")==0)
        {
            return("al");
        }
        if (strcmp(regstr,"001")==0)
        {
            return("cl");
        }
        if (strcmp(regstr,"010")==0)
        {
            return("dl");
        }
        if (strcmp(regstr,"011")==0)
        {
            return("bl");
        }
        if (strcmp(regstr,"100")==0)
        {
            return("ah");
        }
        if (strcmp(regstr,"101")==0)
        {
            return("ch");
        }
        if (strcmp(regstr,"110")==0)
        {
            return("dh");
        }
        if (strcmp(regstr,"111")==0)
        {
            return("bh");
        }
    }
}

char* RMTable(char* rm)
{
    if (strcmp(rm,"000")==0)
    {
        return("bx+si");
    }
    if (strcmp(rm,"001")==0)
    {
        return("bx+di");
    }
    if (strcmp(rm,"010")==0)
    {
        return("bp+si");
    }
    if (strcmp(rm,"011")==0)
    {
        return("bp+di");
    }
    if (strcmp(rm,"100")==0)
    {
        return("si");
    }
    if (strcmp(rm,"101")==0)
    {
        return("di");
    }
    if (strcmp(rm,"110")==0)
    {
        return("bp");
    }
    if (strcmp(rm,"111")==0)
    {
        return("bx");
    }
}

void MOV_Immediate_Register(char* sub_str,int* index, int* bin_index,char* hex_string){
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char regstr[4];
    strncpy(regstr,sub_str+5,3);
    //strcat(regstr,'\0');
    if (sub_str[4]=='1')
    {
        //w = 1
        
        reg=RegTable(regstr,1);
        strncpy(printstr,hex_string+*index,6);
        printf("%s",printstr);
        printf("mov %s, %c%c%c%c\n",reg,hex_string[*index+4],hex_string[*index+5],hex_string[*index+2],hex_string[*index+3]);
        *index+=6;
        *bin_index+=24;
    }
    else
    {
        //w=0
        //NOT DONE
        strncpy(printstr,hex_string+*index,4);
        printf("%s",printstr);
        *index+=4;
        *bin_index+=16;
    }
}

void INT_Specified(char* sub_str,int* index, int* bin_index,char* hex_string)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char regstr[4];
    //strncpy(regstr,sub_str+5,3);
    //reg=RegTable(regstr,1);
    strncpy(printstr,hex_string+*index,4);
    printf("%s",printstr);
    printf("int %c%c\n",hex_string[*index+2],hex_string[*index+3]);
    *index+=4;
    *bin_index+=16;
}

void ADD_Register(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char* rm;
    //find reg
    char regstr[4];
    strncpy(regstr,bin_string+*bin_index+10,3);
    //find rm
    char rmstr[4];
    strncpy(rmstr,bin_string+*bin_index+12,3);
    rmstr[3]=0;
    //find mod
    char* mod[4];
    strncpy(mod,bin_string+8,2);
    if (sub_str[7]=='1')
    {
        //w=1
        reg=RegTable(regstr,1);
        if (strcmp(mod,"11")==0)
        {
            rm=RegTable(rmstr,1);
        }
        else
        {
            //mod == "00"
            rm=RMTable(rmstr);
        }
        strncpy(printstr,hex_string+*index,4);
        printf("%s",printstr);
        if (sub_str[6]=='0')
        {
            //d==0
            printf("add [%s], %s\n", rm,reg);
        }
        else
        {
            //d==1
            printf("add [%s], %s\n", reg,rm);
        }
        *index+=4;
        *bin_index+=16;
        return;
    }
    else
    {
        //w=0
        reg=RegTable(regstr,0);
        if (strcmp(mod,"11")==0)
        {
            rm=RegTable(rmstr,0);
        }
        else
        {
            //mod == "00"
            rm=RMTable(rmstr);
        }
        strncpy(printstr,hex_string+*index,4);
        printf("%s",printstr);
        if (sub_str[6]=='0')
        {
            //d==0
            printf("add [%s], %s\n", rm,reg);
        }
        else
        {
            //d==1
            printf("add [%s], %s\n", reg,rm);
        }
        *index+=4;
        *bin_index+=16;
        return;
    }
}