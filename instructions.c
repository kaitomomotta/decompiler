#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* RegTable(char* regstr,char w)
{
    if (w=='1')
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

char* ModDisp(char* mod)
{
    if (strcmp(mod,"01")==0)
    {
        return "+2";
    }
    if (strcmp(mod,"10")==0)
    {
        return "+4";
    }
    return "";
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



void Generic_Process(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index,int reg_index, int d_index,int w_index,int rm_index,int s_index, int hex_length,
    char* left, char* middle, char* right,int disp)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char* rm;
    //find reg
    char regstr[4];
    regstr[3]=0;
    strncpy(regstr,bin_string+*bin_index+reg_index,3);
    //find rm
    char rmstr[4];
    strncpy(rmstr,bin_string+*bin_index+rm_index,3);
    rmstr[3]=0;
    //find mod
    char mod[3];
    strncpy(mod,bin_string+*bin_index+mod_index,2);
    mod[2]=0;

    reg=RegTable(regstr,sub_str[w_index]);
    if (strcmp(mod,"11")==0)
    {
        rm=RegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod == "00"
        rm=RMTable(rmstr);
    }
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (disp==0)
        {
            if (sub_str[d_index]=='0')
            {
                //d==0
                printf("%s[%s]%s%s%s\n",left, rm, middle, reg, right);
            }
            else
            {
                //d==1
                printf("%s%s%s[%s]%s\n",left, reg, middle,rm, right);
            }
        }
        else
        {
            if (sub_str[d_index]=='0')
            {
                //d==0
                printf("%s[%s+%i]%s%s%s\n",left, rm,disp, middle, reg, right);
            }
            else
            {
                //d==1
                printf("%s%s%s[%s+%i]%s\n",left, reg, middle,rm,disp, right);
            }
        }
    }
    else
    {
        if (sub_str[d_index]=='0')
        {
            //d==0
            printf("%s%s%s%s%s\n",left, rm, middle, reg, right);
        }
        else
        {
            //d==1
            printf("%s%s%s%s%s\n",left, reg, middle,rm, right);
        }
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void Generic_Process_One(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index,int reg_index, int d_index,int w_index,int rm_index,int s_index, int hex_length,
    char* left, char* middle, char* right, int data_index)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char* rm;
    //find reg
    char regstr[4];
    regstr[3]=0;
    strncpy(regstr,bin_string+*bin_index+reg_index,3);
    //find rm
    char rmstr[4];
    strncpy(rmstr,bin_string+*bin_index+rm_index,3);
    rmstr[3]=0;
    //find mod
    char mod[3];
    strncpy(mod,bin_string+*bin_index+mod_index,2);
    //find data
    char data[5]={0,0,0,0,'\0'};
    if (sub_str[w_index]=='1')
    {
        strncat(data,hex_string+*index+data_index,4);
        char temp = data[0];
        data[0] = data[2];
        data[2] = temp;

        temp = data[1];
        data[1] = data[3];
        data[3] = temp;
    }
    else strncat(data,hex_string+*index+data_index, 2);
    
    mod[2]=0;

    reg=RegTable(regstr,sub_str[w_index]);
    if (strcmp(mod,"11")==0)
    {
        rm=RegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod == "00"
        rm=RMTable(rmstr);
    }
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    
    if (sub_str[d_index]=='0')
    {
        //d==0
        printf("%s%s%s%s%s\n",left, data, middle, reg, right);
    }
    else
    {
        //d==1
        printf("%s%s%s%s%s\n",left, reg, middle,data, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void Generic_Process_NOREG_S(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index, int d_index,int w_index,int rm_index,int s_index, int hex_length,
    char* left, char* middle, char* right,int disp, int data_index)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* rm;
    //find rm
    char rmstr[4];
    strncpy(rmstr,bin_string+*bin_index+rm_index,3);
    rmstr[3]=0;
    //find mod
    char mod[3];
    strncpy(mod,bin_string+*bin_index+mod_index,2);
    mod[2]=0;
    if (strcmp(mod,"11")==0)
    {
        rm=RegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod == "00"
        rm=RMTable(rmstr);
    }
    char data[5];
    memset(data,'\0', sizeof(data));
    if (bin_string[*bin_index+s_index]=='0')
    {
        data[0]=hex_string[*index+data_index+2];
        data[1]=hex_string[*index+data_index+3];
        data[2]=hex_string[*index+data_index];
        data[3]=hex_string[*index+data_index+1];
    }
    else
    {
        data[0]=hex_string[*index+data_index];
        data[1]=hex_string[*index+data_index+1];
    }
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (disp==0)
        {
            printf("%s[%s]%s%s%s\n",left, rm, middle, data, right);
        }
        else
        {
            printf("%s[%s+%i]%s%s%s\n",left, rm,disp, middle, data, right);
        }
    }
    else
    {
        printf("%s%s%s%s%s\n",left, rm, middle, data, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void add_hex_strings(char *hex1, char *hex2, char *result) {
    int num1 = (int)strtol(hex1, NULL, 16);
    int num2 = (int)strtol(hex2, NULL, 16);
    int sum = num1 + num2;
    sprintf(result, "%04x", sum);
}

void Generic_Process_JUMP(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int hex_length,char* left, char* right, int data_index)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    //find data
    char data1[3];
    strncpy(data1,hex_string+*index+data_index,2);
    data1[2]=0;

    int num = ((*index-32*2)/2)+2;
    char str[5];
    sprintf(str, "%04x", num);
    str[5]=0;

    char data[5];
    add_hex_strings(data1,str,data);
    data[5]=0;

    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);

    printf("%s%s\n",left,data);
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void Generic_Process_IMMEDIATE(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index,int w_index,int rm_index, int hex_length, int data_index,
    char* left, char* middle, char* right,int disp)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* rm;
    //find rm
    char rmstr[4];
    strncpy(rmstr,bin_string+*bin_index+rm_index,3);
    rmstr[3]=0;
    //find mod
    char mod[3];
    strncpy(mod,bin_string+*bin_index+mod_index,2);
    mod[2]=0;

    char data[5];
    memset(data,'\0', sizeof(data));
    if (bin_string[*bin_index+w_index]=='1')
    {
        data[0]=hex_string[*index+data_index+2];
        data[1]=hex_string[*index+data_index+3];
        data[2]=hex_string[*index+data_index];
        data[3]=hex_string[*index+data_index+1];
    }
    else
    {
        data[0]=hex_string[*index+data_index];
        data[1]=hex_string[*index+data_index+1];
    }
    if (strcmp(mod,"11")==0)
    {
        rm=RegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        rm=RMTable(rmstr);
    }
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (disp==0)
        {
            printf("%s[%s]%s%s%s\n",left, rm, middle, data, right);
            
        }
        else
        {
            printf("%s[%s+%i]%s%s%s\n",left, rm,disp, middle, data, right);
        }
    }
    else
    {
        printf("%s%s%s%s%s\n",left, rm, middle, data, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}
