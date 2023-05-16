#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        
        if (hex_string[index]=='b'&&hex_string[index+1]=='b')
        {
            printstr[0]='b';
            printstr[1]='b';
            printstr[2]=hex_string[index+2];
            printstr[3]=hex_string[index+3];
            printstr[4]=hex_string[index+4];
            printstr[5]=hex_string[index+5];
            
            printf("%s",printstr);
            printf("mov bx, %c%c%c%c\n",hex_string[index+4],hex_string[index+5],hex_string[index+2],hex_string[index+3]);

            index+=6;
            bin_index+=36;
            continue;
        }
        if (hex_string[index]=='c'&&hex_string[index+1]=='d')
        {
            printstr[0]='c';
            printstr[1]='d';
            printstr[2]=hex_string[index+2];
            printstr[3]=hex_string[index+3];
            printf("%s",printstr);
            printf("int %c%c\n",hex_string[index+2],hex_string[index+3]);
            index+=4;
            bin_index+=16;
            continue;
        }
        else
        {
            printstr[0]=hex_string[index];
            printstr[1]=hex_string[index+1];
            printstr[2]=hex_string[index+2];
            printstr[3]=hex_string[index+3];
            printf("%s",printstr);
            printf("add [bx+si], al\n");
            index+=4;
            continue;
        }
        
        index+=2;
        
    }
    printf("\n");
}

int main() {
    FILE *file;
    char *buffer;
    long file_length;
    char hex_string[1024] = ""; // Initialize an empty string
    char bin_string[8192]="";
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

    // Add the hex and binary bytes to their respective strings
    for (int i = 0; i < file_length; i++) {
        // Add the hex byte to the hex string
        sprintf(hex_string + strlen(hex_string), "%02x", (unsigned char)buffer[i]);

        // Add the binary byte to the binary string
        for (int j = 7; j >= 0; j--) {
            if ((unsigned char)buffer[i] & (1 << j)) {
                strcat(bin_string, "1");
            } else {
                strcat(bin_string, "0");
            }
        }
        strcat(bin_string, "");
    }

    // Display the hex and binary strings
    printf("Hex string: %s\n", hex_string);
    printf("Binary string: %s\n", bin_string);

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

    process(hex_string,bin_string,lenght_of_buffer);

    // Display the hex string
    //printf("full buffer: %s\n", hex_string);

    // Clean up
    free(buffer);
    fclose(file);

    return 0;
}
