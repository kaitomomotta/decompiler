#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void IntermodifyString(char* str) {
    int i;
    for (i = 0; i < 4; i++) {
        str[i] = str[i + 1];
    }
    str[4] = '\0';
}

void InteradjustHexString(char* hex)
{
    unsigned int value = strtol(hex, NULL, 16);

    if (value > 0x127)
    {
        value -= 0x100;
        sprintf(hex, "%04x", value);
    }
}

void InterconvertHexToSignedHex(char* hex)
{
    // Convert the hexadecimal string to an unsigned long integer
    unsigned long value = strtoul(hex + 1, NULL, 16); // Skip the '+' character

    // If the most significant bit (bit 7) is set, interpret the value as negative
    if (value & 0x80)
    {
        // Perform two's complement conversion
        value = (~value + 1) & 0xFF;
        
        // Modify the first character in the string to '-'
        hex[0] = '-';
        // Store the resulting signed value back in the string starting from the second character
        sprintf(hex + 1, "%02lx", value);
    }
    else
    {
        // Keep the '+' character
        // Store the resulting signed value back in the string starting from the second character
        sprintf(hex + 1, "%02lx", value);
    }
}

char* InterRegTable(char* regstr,char w)
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

char* InterRegTableSegment(char* regstr)
{
    if (strcmp(regstr,"00")==0)
    {
        return "es";
    }
    if (strcmp(regstr,"01")==0)
    {
        return "cs";
    }
    if (strcmp(regstr,"10")==0)
    {
        return "ss";
    }
    if (strcmp(regstr,"11")==0)
    {
        return "ds";
    }
}

char* InterRMTable(char* rm)
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

char* InterInterModDisp(char* mod)
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

void InterMOV_Immediate_Register(char* sub_str,int* index, int* bin_index,char* hex_string){
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char regstr[4];
    strncpy(regstr,sub_str+5,3);
    //strcat(regstr,'\0');
    if (sub_str[4]=='1')
    {
        //w = 1
        
        reg=InterRegTable(regstr,1);
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

void InterINT_Specified(char* sub_str,int* index, int* bin_index,char* hex_string)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char regstr[4];
    //strncpy(regstr,sub_str+5,3);
    //reg=InterRegTable(regstr,1);
    strncpy(printstr,hex_string+*index,4);
    printf("%s",printstr);
    printf("int %c%c\n",hex_string[*index+2],hex_string[*index+3]);
    *index+=4;
    *bin_index+=16;
}

void InterGeneric_Fixed_Port(char* sub_str,int* index, int* bin_index,char* hex_string, char* left)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char regstr[4];
    //strncpy(regstr,sub_str+5,3);
    //reg=InterRegTable(regstr,1);
    strncpy(printstr,hex_string+*index,4);
    printf("%s",printstr);
    if (sub_str[7]=='1')
    {
        printf("%s%s%c%c\n",left,"ax, ", hex_string[*index+2],hex_string[*index+3]);
    }
    else printf("%s%s%c%c\n",left,"al, ",hex_string[*index+2],hex_string[*index+3]);
    *index+=4;
    *bin_index+=16;
}

void InterGeneric_Fixed_PortVAR(char* sub_str,int* index, int* bin_index,char* hex_string, char* left)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char regstr[4];
    //strncpy(regstr,sub_str+5,3);
    //reg=InterRegTable(regstr,1);
    strncpy(printstr,hex_string+*index,4);
    printf("%s",printstr);
    if (sub_str[7]=='1')
    {
        printf("%s%s\n",left,"ax, dl");
    }
    else printf("%s%s\n",left,"al, dx");
    *index+=2;
    *bin_index+=8;
}

void InterGeneric_Process(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
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
    //create data
    char data[5];
    memset(data,'\0', sizeof(data));
    reg=InterRegTable(regstr,sub_str[w_index]);
    if (strcmp(mod,"11")==0)
    {
        rm=InterRegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod != "11"
        rm=InterRMTable(rmstr);
    }

    char* dispstr[6]={'+','\0','\0','\0','\0','\0'};
    //find disp
    if (strcmp(mod,"01")==0)
    {
        //disp = disp-low sign-extended to 16 bits
        strncat(dispstr,hex_string+*index+4,2);
        InterconvertHexToSignedHex(dispstr);
        //strcat(dispstr,'\0');
        hex_length+=2;
    }
    else if (strcmp(mod,"10")==0)
    {
        //disp = disp-high;disp-low
        strncat(dispstr,hex_string+*index+6,2);
        //strcat(dispstr,'\0');
        strncat(dispstr,hex_string+*index+4,2);
        //strcat(dispstr,'\0');
        hex_length+=4;
    }
    

    if (strcmp(mod,"00")==0&&strcmp(rmstr,"110")==0)
    {
        // EA = disp-high;disp-low
        
        if (bin_string[*bin_index+w_index]=='1')
        {
            data[0]=hex_string[*index+hex_length+2];
            data[1]=hex_string[*index+hex_length+3];
            data[2]=hex_string[*index+hex_length];
            data[3]=hex_string[*index+hex_length+1];
            hex_length+=4;
        }
        else
        {
            data[0]=hex_string[*index+hex_length];
            data[1]=hex_string[*index+hex_length+1];
            hex_length+=2;
        }
        rm=data;
    }
    
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (strcmp(dispstr,"+")==0)
        {
            if (sub_str[d_index]=='0')
            {
                //d==0
                if (data[0]==0) printf("%s[%s]%s%s%s\n",left, rm, middle, reg, right);
                else printf("%s[%s]%s%s%s\n",left, data, middle, reg, right);
            }
            else
            {
                //d==1
                if (data[0]==0) printf("%s%s%s[%s]%s\n",left, reg, middle,rm, right);
                else printf("%s%s%s[%s]%s\n",left, reg, middle,data, right);
            }
        }
        else
        {
            if (sub_str[d_index]=='0')
            {
                //d==0
                if (data[0]==0) printf("%s[%s%s]%s%s%s\n",left, rm,dispstr, middle, reg, right);
                else printf("%s[%s%s]%s%s%s\n",left, data,dispstr, middle, reg, right);
            }
            else
            {
                //d==1
                if (data[0]==0) printf("%s%s%s[%s%s]%s\n",left, reg, middle,rm,dispstr, right);
                else printf("%s%s%s[%s%s]%s\n",left, reg, middle,data,dispstr, right);
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

void InterGeneric_Process_NODW(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index,int reg_index,int rm_index, int hex_length,
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
    //create data
    char data[5];
    memset(data,'\0', sizeof(data));
    reg=InterRegTable(regstr,'1');
    if (strcmp(mod,"11")==0)
    {
        rm=InterRegTable(rmstr,'1');
    }
    else
    {
        //mod != "11"
        rm=InterRMTable(rmstr);
    }

    char* dispstr[6]={'+','\0','\0','\0','\0','\0'};
    //find disp
    if (strcmp(mod,"01")==0)
    {
        //disp = disp-low sign-extended to 16 bits
        strncat(dispstr,hex_string+*index+4,2);
        InterconvertHexToSignedHex(dispstr);
        //strcat(dispstr,'\0');
        hex_length+=2;
    }
    else if (strcmp(mod,"10")==0)
    {
        //disp = disp-high;disp-low
        strncat(dispstr,hex_string+*index+6,2);
        //strcat(dispstr,'\0');
        strncat(dispstr,hex_string+*index+4,2);
        //strcat(dispstr,'\0');
        hex_length+=4;
    }
    

    if (strcmp(mod,"00")==0&&strcmp(rmstr,"110")==0)
    {
        // EA = disp-high;disp-low

        data[0]=hex_string[*index+hex_length+2];
        data[1]=hex_string[*index+hex_length+3];
        data[2]=hex_string[*index+hex_length];
        data[3]=hex_string[*index+hex_length+1];
        hex_length+=4;
        rm=data;
    }
    
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (strcmp(dispstr,"+")==0)
        {
            if (data[0]==0) printf("%s%s%s[%s]%s\n",left, reg, middle,rm, right);
            else printf("%s%s%s[%s]%s\n",left, reg, middle,data, right);
        }
        else
        {
            if (data[0]==0) printf("%s%s%s[%s%s]%s\n",left, reg, middle,rm,dispstr, right);
            else printf("%s%s%s[%s%s]%s\n",left, reg, middle,data,dispstr, right);
        }
    }
    else
    {
        printf("%s%s%s%s%s\n",left, rm, middle, reg, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void InterGeneric_Process_NODW_Segment(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index,int reg_index,int rm_index, int hex_length,
    char* left, char* middle, char* right,int disp,int pos) //pos = 0 --> reg rm, pos = 1 --> rm reg
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    char* rm;
    //find reg
    char regstr[3];
    regstr[2]=0;
    strncpy(regstr,bin_string+*bin_index+reg_index,2);
    //find rm
    char rmstr[4];
    strncpy(rmstr,bin_string+*bin_index+rm_index,3);
    rmstr[3]=0;
    //find mod
    char mod[3];
    strncpy(mod,bin_string+*bin_index+mod_index,2);
    mod[2]=0;
    //create data
    char data[5];
    memset(data,'\0', sizeof(data));
    reg=InterRegTableSegment(regstr);
    if (strcmp(mod,"11")==0)
    {
        rm=InterRegTableSegment(rmstr);
        rm[2]=0;
    }
    else
    {
        //mod != "11"
        rm=InterRMTable(rmstr);
    }

    char* dispstr[6]={'+','\0','\0','\0','\0','\0'};
    //find disp
    if (strcmp(mod,"01")==0)
    {
        //disp = disp-low sign-extended to 16 bits
        strncat(dispstr,hex_string+*index+4,2);
        InterconvertHexToSignedHex(dispstr);
        //strcat(dispstr,'\0');
        hex_length+=2;
    }
    else if (strcmp(mod,"10")==0)
    {
        //disp = disp-high;disp-low
        strncat(dispstr,hex_string+*index+6,2);
        //strcat(dispstr,'\0');
        strncat(dispstr,hex_string+*index+4,2);
        //strcat(dispstr,'\0');
        hex_length+=4;
    }
    

    if (strcmp(mod,"00")==0&&strcmp(rmstr,"110")==0)
    {
        // EA = disp-high;disp-low

        data[0]=hex_string[*index+hex_length+2];
        data[1]=hex_string[*index+hex_length+3];
        data[2]=hex_string[*index+hex_length];
        data[3]=hex_string[*index+hex_length+1];
        hex_length+=4;
        rm=data;
    }
    
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
        {
            if (strcmp(dispstr,"+")==0)
            {
                if (pos==0)
                {
                    //d==0
                    if (data[0]==0) printf("%s[%s]%s%s%s\n",left, rm, middle, reg, right);
                    else printf("%s[%s]%s%s%s\n",left, data, middle, reg, right);
                }
                else
                {
                    //d==1
                    if (data[0]==0) printf("%s%s%s[%s]%s\n",left, reg, middle,rm, right);
                    else printf("%s%s%s[%s]%s\n",left, reg, middle,data, right);
                }
            }
            else
            {
                if (pos==0)
                {
                    //d==0
                    if (data[0]==0) printf("%s[%s%s]%s%s%s\n",left, rm,dispstr, middle, reg, right);
                    else printf("%s[%s%s]%s%s%s\n",left, data,dispstr, middle, reg, right);
                }
                else
                {
                    //d==1
                    if (data[0]==0) printf("%s%s%s[%s%s]%s\n",left, reg, middle,rm,dispstr, right);
                    else printf("%s%s%s[%s%s]%s\n",left, reg, middle,data,dispstr, right);
                }
            }
        }
        else
        {
            if (pos==0)
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

void InterGeneric_Process_NODWREG(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index,int rm_index, int hex_length,
    char* left, char* right,int disp)
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
    //create data
    char data[5];
    memset(data,'\0', sizeof(data));
    if (strcmp(mod,"11")==0)
    {
        rm=InterRegTable(rmstr,'1');
    }
    else
    {
        //mod != "11"
        rm=InterRMTable(rmstr);
    }

    char* dispstr[6]={'+','\0','\0','\0','\0','\0'};
    //find disp
    if (strcmp(mod,"01")==0)
    {
        //disp = disp-low sign-extended to 16 bits
        strncat(dispstr,hex_string+*index+4,2);
        InterconvertHexToSignedHex(dispstr);
        //strcat(dispstr,'\0');
        hex_length+=2;
    }
    else if (strcmp(mod,"10")==0)
    {
        //disp = disp-high;disp-low
        strncat(dispstr,hex_string+*index+6,2);
        //strcat(dispstr,'\0');
        strncat(dispstr,hex_string+*index+4,2);
        //strcat(dispstr,'\0');
        hex_length+=4;
    }
    

    if (strcmp(mod,"00")==0&&strcmp(rmstr,"110")==0)
    {
        // EA = disp-high;disp-low

        data[0]=hex_string[*index+hex_length+2];
        data[1]=hex_string[*index+hex_length+3];
        data[2]=hex_string[*index+hex_length];
        data[3]=hex_string[*index+hex_length+1];
        hex_length+=4;
        rm=data;
    }
    
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (strcmp(dispstr,"+")==0)
        {
            printf("%s[%s]%s\n",left, rm, right);
        }
        else
        {
            if (data[0]==0) printf("%s[%s%s]%s\n",left, rm,dispstr, right);
            else printf("%s[%s%s]%s\n",left, data,dispstr, right);
        }
    }
    else
    {
        printf("%s%s%s\n",left, rm, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void InterGeneric_Process_NODREG(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int w_index,int mod_index,int rm_index, int hex_length,
    char* left, char* right,int disp)
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
    //create data
    char data[5];
    memset(data,'\0', sizeof(data));
    if (strcmp(mod,"11")==0)
    {
        rm=InterRegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod != "11"
        rm=InterRMTable(rmstr);
    }

    char* dispstr[6]={'+','\0','\0','\0','\0','\0'};
    //find disp
    if (strcmp(mod,"01")==0)
    {
        //disp = disp-low sign-extended to 16 bits
        strncat(dispstr,hex_string+*index+4,2);
        InterconvertHexToSignedHex(dispstr);
        //strcat(dispstr,'\0');
        hex_length+=2;
    }
    else if (strcmp(mod,"10")==0)
    {
        //disp = disp-high;disp-low
        strncat(dispstr,hex_string+*index+6,2);
        //strcat(dispstr,'\0');
        strncat(dispstr,hex_string+*index+4,2);
        //strcat(dispstr,'\0');
        hex_length+=4;
    }
    

    if (strcmp(mod,"00")==0&&strcmp(rmstr,"110")==0)
    {
        // EA = disp-high;disp-low

        data[0]=hex_string[*index+hex_length+2];
        data[1]=hex_string[*index+hex_length+3];
        data[2]=hex_string[*index+hex_length];
        data[3]=hex_string[*index+hex_length+1];
        hex_length+=4;
        rm=data;
    }
    
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (strcmp(dispstr,"+")==0)
        {
            printf("%s[%s]%s\n",left, rm, right);
        }
        else
        {
            if (data[0]==0) printf("%s[%s%s]%s\n",left, rm,dispstr, right);
            else printf("%s[%s%s]%s\n",left, data,dispstr, right);
        }
    }
    else
    {
        printf("%s%s%s\n",left, rm, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}


void InterGeneric_Process_VW(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int mod_index, int v_index,int w_index,int rm_index, int hex_length,
    char* left, char* middle, char* right,int disp)
{
    *bin_index=*index*4;
    
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
    //create data
    char data[5];
    memset(data,'\0', sizeof(data));

    rm=InterRMTable(rmstr);

    char* dispstr[6]={'+','\0','\0','\0','\0','\0'};
    //find disp
    if (strcmp(mod,"01")==0)
    {
        //disp = disp-low sign-extended to 16 bits
        strncat(dispstr,hex_string+*index+4,2);
        InterconvertHexToSignedHex(dispstr);
        //strcat(dispstr,'\0');
        hex_length+=2;
    }
    else if (strcmp(mod,"10")==0)
    {
        //disp = disp-high;disp-low
        strncat(dispstr,hex_string+*index+6,2);
        //strcat(dispstr,'\0');
        strncat(dispstr,hex_string+*index+4,2);
        //strcat(dispstr,'\0');
        hex_length+=4;
    }
    

    if (strcmp(mod,"00")==0&&strcmp(rmstr,"110")==0)
    {
        // EA = disp-high;disp-low
        
        if (bin_string[*bin_index+w_index]=='1')
        {
            data[0]=hex_string[*index+hex_length+2];
            data[1]=hex_string[*index+hex_length+3];
            data[2]=hex_string[*index+hex_length];
            data[3]=hex_string[*index+hex_length+1];
            hex_length+=4;
        }
        else
        {
            data[0]=hex_string[*index+hex_length];
            data[1]=hex_string[*index+hex_length+1];
            hex_length+=2;
        }
        rm=data;
    }
    
    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    if (strcmp(mod,"01")==0||strcmp(mod,"10")==0||strcmp(mod,"00")==0)
    {
        if (strcmp(dispstr,"+")==0)
        {
            if (sub_str[v_index]=='0')
            {
                //v==0
                if (data[0]==0) printf("%s[%s]%s%s%s\n",left, rm, middle, "1", right);
                else printf("%s[%s]%s%s%s\n",left, data, middle, "1", right);
            }
            else
            {
                //v==1
                if (data[0]==0) printf("%s%s%s[%s]%s\n",left, "cl", middle,rm, right);
                else printf("%s%s%s[%s]%s\n",left, "cl", middle,data, right);
            }
        }
        else
        {
            if (sub_str[v_index]=='0')
            {
                //v==0
                if (data[0]==0) printf("%s[%s%s]%s%s%s\n",left, rm,dispstr, middle, "1", right);
                else printf("%s[%s%s]%s%s%s\n",left, data,dispstr, middle, "1", right);
            }
            else
            {
                //v==1
                if (data[0]==0) printf("%s%s%s[%s%s]%s\n",left, "cl", middle,rm,dispstr, right);
                else printf("%s%s%s[%s%s]%s\n",left, "cl", middle,data,dispstr, right);
            }
        }
    }
    else
    {
        if (sub_str[v_index]=='0')
        {
            //v==0
            printf("%s%s%s%s%s\n",left, rm, middle, "1", right);
        }
        else
        {
            //v==1
            printf("%s%s%s%s%s\n",left, "cl", middle,rm, right);
        }
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}


void InterGeneric_Process_One(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
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

    reg=InterRegTable(regstr,sub_str[w_index]);
    if (strcmp(mod,"11")==0)
    {
        rm=InterRegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod == "00"
        rm=InterRMTable(rmstr);
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

void InterGeneric_Process_NOREG_S(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
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
        rm=InterRegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        //mod == "00"
        rm=InterRMTable(rmstr);
    }
    char data[5];
    memset(data,'\0', sizeof(data));
    if (bin_string[*bin_index+s_index]=='1'&&bin_string[*bin_index+7]=='1')
    {
        hex_length+=4;
    }
    
    if (bin_string[*bin_index+s_index]=='0'&&bin_string[*bin_index+7]=='1')
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

void InterGeneric_Process_ACCU(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int w_index, int hex_length,
    char* left, char* middle, char* right,int disp, int data_index)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char data[5];
    memset(data,'\0', sizeof(data));
    if (bin_string[*bin_index+7]=='1')
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
    if (bin_string[*bin_index+7]=='1')
    {
        printf("%s%s%s%s%s\n",left, "ax", middle, data, right);
    }
    else
    {
        printf("%s%s%s%s%s\n",left, "al", middle, data, right);
    }
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}


void Interadd_hex_strings(char *hex1, char *hex2, char *result) {
    int num1 = (int)strtol(hex1, NULL, 16);
    int num2 = (int)strtol(hex2, NULL, 16);
    int sum = num1 + num2;
    sprintf(result, "%04x", sum);
}

void Interswap_chars(char *arr) {
    char temp;

    temp = arr[0];
    arr[0] = arr[2];
    arr[2] = temp;

    temp = arr[1];
    arr[1] = arr[3];
    arr[3] = temp;
}

void InterGeneric_Process_JUMP(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int hex_length,char* left, char* right, int data_index,int data_length)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    //find data
    char data1[data_length+1];
    strncpy(data1,hex_string+*index+data_index,data_length);
    data1[data_length]=0;
    
    if (data_length==4)
    {
        Interswap_chars(data1);
    }

    int num = ((*index-32*2)/2)+2;
    if (data_length==4) num = ((*index-32*2)/2)+3;
    
    char str[5];
    sprintf(str, "%04x", num);
    str[5]=0;

    char data[5];
    add_hex_strings(data1,str,data);
    data[5]=0;

    if(data_length==2) InteradjustHexString(data);

    if(data[4]!='\0') IntermodifyString(data);

    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);

    printf("%s%s\n",left,data);
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}

void InterGeneric_Process_IMMEDIATE(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
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
        rm=InterRegTable(rmstr,sub_str[w_index]);
    }
    else
    {
        rm=InterRMTable(rmstr);
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

void InterGeneric_Process_REGISTER(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int reg_index, int hex_length,
    char* left, char* right)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    //find reg
    char regstr[4];
    regstr[3]=0;
    strncpy(regstr,bin_string+*bin_index+reg_index,3);
    reg=InterRegTable(regstr,'1');

    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    printf("%s%s%s\n",left, reg, right);
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;
}

void InterGeneric_Process_Segment_REGISTER(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int reg_index, int hex_length,
    char* left, char* right)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
    char* reg;
    //find reg
    char regstr[3];
    regstr[2]=0;
    strncpy(regstr,bin_string+*bin_index+reg_index,2);
    reg=InterRegTableSegment(regstr);

    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);
    printf("%s%s%s\n",left, reg, right);
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;
}

void InterGeneric_Process_NOTHING(char* sub_str,int* index, int* bin_index,char* hex_string,char* bin_string,
    int hex_length,char* left, char* right)
{
    char printstr[]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};

    strncpy(printstr,hex_string+*index,hex_length);
    printf("%s",printstr);

    printf("%s%s\n",left,right);
    
    *index+=hex_length;
    *bin_index+=hex_length*4;
    return;

}