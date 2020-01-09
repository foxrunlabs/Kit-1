/*******************************************************************************
 *  Copyright 2019 Ryan Clarke
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  License for the specific language governing permissions and limitations
 *  under the License.
 ******************************************************************************/

/*******************************************************************************
 *  Program   : bin2c
 *  File Name : bin2c.c
 *  Project   : Kit-1 8-bit Computer
 *  Author    : Ryan Clarke
 *  E-mail    : kj6msg@icloud.com
 *  ----------------------------------------------------------------------------
 *  Purpose : Converts the KitBIOS .bin file to C source code for implementation
 *            in the KitDMA module.
 ******************************************************************************/
 

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>


#define FILEHEADER "\
/*******************************************************************************\n\
 *  Copyright 2019 Ryan Clarke\n\
 *\n\
 *  Licensed under the Apache License, Version 2.0 (the \"License\"); you may not\n\
 *  use this file except in compliance with the License. You may obtain a copy\n\
 *  of the License at\n\
 *\n\
 *      http://www.apache.org/licenses/LICENSE-2.0\n\
 *\n\
 *  Unless required by applicable law or agreed to in writing, software\n\
 *  distributed under the License is distributed on an \"AS IS\" BASIS, WITHOUT\n\
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the\n\
 *  License for the specific language governing permissions and limitations\n\
 *  under the License.\n\
 ******************************************************************************/\n\
 \n\
/*******************************************************************************\n\
 *  Program   : KitBIOS\n\
 *  File Name : kitbios.c\n\
 *  Project   : Kit-1 8-bit Computer\n\
 *  Device    : PIC18F47K40\n\
 *  Author    : Ryan Clarke\n\
 *  E-mail    : kj6msg@icloud.com\n\
 *  ----------------------------------------------------------------------------\n\
 *  Purpose : KitBIOS image for the Kit-1 8-bit computer.\n\
 ******************************************************************************/\n\
 \n\
 \n\
#include <stdint.h>\n\
\n\
\n\
const uint16_t bios_start = 0x%04X;\n\
\n\
const uint8_t bios[%u] = {\n"


int main(int argc, char *argv[])
{
    uint8_t  *buf;
    uint16_t start;
    int      i;
    int      j;
    FILE     *file_in;
    FILE     *file_out;
    struct   stat st;
    
    /* must supply two arguments */
    if((argc == 1) || (argc > 3))
    {
        fprintf(stderr, "usage: %s infile outfile\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    /* open input file */
    if((file_in = fopen(argv[1], "rb")) == NULL)
    {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[1]);
        return EXIT_FAILURE;
    }
    
    /* get input file stats */
    if(stat(argv[1], &st) != 0)
    {
        fprintf(stderr, "%s: %s: error %d\n", argv[0], argv[1], errno);
        fclose(file_in);
        return EXIT_FAILURE;
    }
    
    /* input file must be greater than 256 bytes and less than 64768 bytes */
    if((st.st_size < 256) || (st.st_size > 64768))
    {
        fprintf(stderr, "%s: %s: size must be between 256 and 64768 bytes\n", argv[0], argv[1]);
        fclose(file_in);
        return EXIT_FAILURE;
    }
    
    /* input file must be a multiple of 256 bytes */
    if(st.st_size % 256)
    {
        fprintf(stderr, "%s: %s: size must be a multiple of 256\n", argv[0], argv[1]);
        fclose(file_in);
        return EXIT_FAILURE;
    }
    
    /* create output file */
    if((file_out = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "%s: %s: unable to create file\n", argv[0], argv[2]);
        fclose(file_in);
        return EXIT_FAILURE;
    }
    
    /* allocate buffer for input file data */
    if((buf = malloc((size_t)st.st_size * sizeof(uint8_t))) == NULL)
    {
        fprintf(stderr, "%s: insufficent memory\n", argv[0]);
        fclose(file_in);
        fclose(file_out);
        return EXIT_FAILURE;
    }
    
    fread(buf, sizeof(uint8_t), (size_t)st.st_size, file_in);
    
    /* compute starting address of BIOS in Kit-1 RAM space */
    start = (uint16_t)(0x10000 - st.st_size);
    fprintf(file_out, FILEHEADER, start, (uint16_t)st.st_size);
    
    /* convert individual bytes to hexadecimal format */
    j = 0;
    for(i = 0; i < st.st_size; i++)
    {
        fprintf(file_out, "0x%02X", buf[i]);
        
        if(i < st.st_size - 1)
            fputc(',', file_out);
        
        if(j < 7)
        {
            fputc(' ', file_out);
            j++;
        }
        else
        {
            fputc('\n', file_out);
            j = 0;
        }
    }
    
    fputs("};\n", file_out);
    
    free(buf);
    fclose(file_in);
    fclose(file_out);
    
    return EXIT_SUCCESS;
}
