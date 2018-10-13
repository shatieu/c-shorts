//
// Created by Ondřej on 27. 4. 2018.
//
//#include <mem.h>
#include <malloc.h>
#include "hash_helper.h"
#include "stdio.h"
#include "string.h"

// ---------------------------- reverse --------------------------------

// Reverses (reflects) bits in a 32-bit word.
unsigned reverse(unsigned x) {
    x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
    x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
    x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
    x = (x << 24) | ((x & 0xFF00) << 8) |
        ((x >> 8) & 0xFF00) | (x >> 24);
    return x;
}

// ----------------------------- crc32a --------------------------------




int decideHashes(const char* param, int* hashesToDO){
    if (hashesToDO == NULL || param == NULL){
        return -1;
    }
    if (!strcmp(param, "-xor")){
        hashesToDO[0] = 1;
        return 0;
    }
    if (!strcmp(param, "-c16")){
        hashesToDO[1] = 1;
        return 0;
    }
    if (!strcmp(param, "-md5")){
        hashesToDO[3] = 1;
        return 0;
    }
    if (!strcmp(param, "-c32")){
        hashesToDO[2] = 1;
        return 0;
    }
    if (!strcmp(param, "-hex")){
        return 16;
    }
    //case file
    if (strlen(param) >= 2 ){
        if(param[0] == '-' && param[1] == 'f'){
            return 2;
        }
    }
    return -1;
}

void ToHex(const unsigned char digest[16], char *output, int LowerCase)
{
    char *outputEnd;
    const unsigned char *s = digest;


    for (outputEnd = output + 32; output < outputEnd; output += 2) {
        sprintf(output, "%02x", *(s++));
    }
}


int main(int argc, char *argv[])
{
    if (argc < 2){
        fprintf(stderr,"inssuficient args \n");
        return 1;
    }
    int hashesToDo [4] = {0,0,0,0};
    char* filename = NULL;
    int hexFlag = 0;
    int fromStdin = 1;

    for (int i = 1; i < argc; i++) {
        int decided = decideHashes(argv[i], hashesToDo);
        if(decided == -1){
            fprintf(stderr,"error while reading args \n");
            return 1;
        }
        if(decided == 16){
            hexFlag = 1;
        }
        if(decided == 2){
            if(filename != NULL){
                fprintf(stderr, "conflicting file args \n");
                return 1;
            }
            i++;
            if(i >= argc){
                fprintf(stderr, "no file specified \n");
                return 1;
            }
            filename = argv[i];
            fromStdin = 0;
            if(filename == NULL){
                fprintf(stderr,"wrong file argument \n");
                return 1;
            }
        }
    }
    if(hashesToDo[0] == 0 && hashesToDo[1] == 0 && hashesToDo[2] == 0 && hashesToDo[3] == 0){
        fprintf(stderr,"no valid hash chosen");
        return 1;
    }

    FILE *toHash = NULL;

    if(fromStdin == 0){
        toHash = fopen(filename, "rb");
        if(toHash == NULL){
            fprintf(stderr, "cannot open file");
            if (filename != NULL) {
                free(filename);
            }
            return 1;
        }
    }else{
        toHash = stdin;
    }
    unsigned char res = 0;
    long int byteCount = 1;
    if(fread(&res,1,1,toHash) == 0){
        byteCount = 0;
    }
    unsigned char forXor = res;

    crc16_context cr16ctx;
    crc16_init(&cr16ctx);


    MD5_CTX ctxmd5;
    MD5_Init(&ctxmd5);
    size_t blocksize = 1;
    unsigned char result [16];

    int i, j;
    unsigned int byte, crc, mask;
    i = 0;
    crc = 0xFFFFFFFF;

    if(byteCount == 1) {
        crc16_update(&cr16ctx,res);
        MD5_Update(&ctxmd5, &res, blocksize);
        byte = res;            // Get next byte.
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {    // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }
    unsigned char add = 0;
    while(fread(&add, sizeof(unsigned char), 1, toHash) == 1){
        byteCount++;
        //---------------------
        if(hashesToDo[0] == 1){
            forXor = forXor ^ add;
        }

        // CRC-16 ----------------------------------------

        if(hashesToDo[1] == 1){
            crc16_update(&cr16ctx, add);
        }
        //-----------
        if(hashesToDo[3] == 1){
            MD5_Update(&ctxmd5, &add, blocksize);
        }
        if(hashesToDo[2] == 1){
            byte = add;            // Get next byte.
            crc = crc ^ byte;
            for (j = 7; j >= 0; j--) {    // Do eight times.
                mask = -(crc & 1);
                crc = (crc >> 1) ^ (0xEDB88320 & mask);
            }
            i = i + 1;
        }

    }
    //------------------------

    //-------------------------------------prints

    printf("Length: %ld bytes\n", byteCount);

    if(hashesToDo[0] == 1){
        if(hexFlag == 1) {
            printf("XOR: 0x%02x\n", forXor);
        } else{
            printf("XOR: %d\n", forXor);
        }
    }

    // CRC-16 ----------------------------------------

    if(hashesToDo[1] == 1){
        if(hexFlag == 1){
            printf("CRC-16: 0x%04x\n", cr16ctx.crc);
        } else{
            printf("CRC-16: %d\n", cr16ctx.crc);
        }
    }
    if(hashesToDo[2] == 1){
        reverse(~crc);
        if(hexFlag == 1){
            printf("CRC-32: 0x%08x\n", ~crc);
        } else{
            printf("CRC-32: %d\n", ~crc);
        }
    }
    //-----------
    if(hashesToDo[3] == 1){
        MD5_Final(result,&ctxmd5);
        char output [32];
        ToHex(result, output, 1);
        printf("MD5: %s\n",output);
    }

    fclose(toHash);
    return 0;
}
