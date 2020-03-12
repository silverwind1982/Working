#include <stdio.h>

char b_char[33] = {'\0'};

char* convertInt2Binary(int c, int length)
{
    int i;
    for (i = 0; i < length; ++i) {
        if (c & (0x1 << (length - 1 - i))) {
            b_char[i] = '1';
        } else {
            b_char[i] = '0';
        }
    }

    b_char[length] = '\0';

    //printf("%d: b_char: %s\n", c, b_char);
    return b_char;
}

static unsigned int calculate_crc4(void *buf, unsigned int len)
{
    unsigned int i, j;
    unsigned int byte_length = 8;       /*length of unit (i.e. byte) */
    int msb = 0;
    int polynomial = 0x9;    /* IEEE 32bit polynomial */
    unsigned int regs = 0x0; /* init to all ones */
    int regs_mask = 0xF;     /* ensure only 32 bit answer */
    int regs_msb = 0;
    char tmp;

    printf("regs = %s, ", convertInt2Binary(regs, 4));
    printf("polynomial = %s\n", convertInt2Binary(polynomial, 4));
    printf("buffer = ");
    for (i = 0; i < len; ++i) {
        tmp = ((char)((char*)buf)[i] >> 4) & 0xf;
        printf("%s ", convertInt2Binary(tmp, 4));
        tmp = (char)((char*)buf)[i] & 0xf;
        printf("%s ", convertInt2Binary(tmp, 4));
    }
    printf("\n\n\n");
    for (i = 0; i < len; i++) {
        int data_byte = *((char *)buf + i);
        for (j = 0; j < byte_length; j++) {
            msb = data_byte >> (byte_length - 1); /* get MSB */
            msb &= 1;                             /* ensure just 1 bit */
            regs_msb = (regs >> 3) & 1;          /* MSB of regs */
            printf("j = %d, regs = %s, regs_msb = %d, msb = %d\n",
                    j, convertInt2Binary(regs, 4), regs_msb, msb);
            if (regs_msb ^ msb) {                 /* MSB is a 1 */
                printf("%s ", convertInt2Binary(regs, 4));
                regs = regs ^ polynomial;         /* XOR with generator poly */
                printf("^ %s = ", convertInt2Binary(polynomial, 4));
                printf("%s\n", convertInt2Binary(regs, 4));
            }
            regs = regs << 1;                     /* shift regs for CRC-CCITT */
            regs = regs & regs_mask;              /* Mask off excess upper bits */
            data_byte <<= 1;                      /* get to next bit */
        }
        printf("regs = %s\n\n", convertInt2Binary(regs, 4));
    }

    regs = regs >> 1;
    printf("\nregs = %s\n", convertInt2Binary(regs, 3));
    regs = regs & regs_mask;

    return regs;
}

int main(int argc, char* argv[]) {

    unsigned int crc4 = 0;
	//char buffer[] = "abcdefghijklmnopqqrstuvwxyz";
	char buffer[] = "a";

    crc4 = calculate_crc4(buffer, 1);
	printf("\ncrc4 = %s\n\n", convertInt2Binary(crc4, 3));

	return 0;
}


#if 0
// original CRC32

/*
 * A8h reflected is 15h, i.e. 10101000 <--> 00010101
 */
static int reflect(int data, int len)
{
    int ref = 0;
    int i;
    for (i = 0; i < len; i++) {
        if (data & 0x1) {
            ref |= (1 << ((len - 1) - i));
        }
        data = (data >> 1);
    }
    return ref;
}

static uint32_t calculate_crc32(void *buf, uint32_t len)
{
    uint32_t i, j;
    uint32_t byte_length = 8;       /*length of unit (i.e. byte) */
    int msb = 0;
    int polynomial = 0x04C11DB7;    /* IEEE 32bit polynomial */
    unsigned int regs = 0xFFFFFFFF; /* init to all ones */
    int regs_mask = 0xFFFFFFFF;     /* ensure only 32 bit answer */
    int regs_msb = 0;
    unsigned int reflected_regs;
    for (i = 0; i < len; i++) {
        int data_byte = *((uint8_t *)buf + i);
        data_byte = reflect(data_byte, 8);
        for (j = 0; j < byte_length; j++) {
            msb = data_byte >> (byte_length - 1); /* get MSB */
            msb &= 1;                             /* ensure just 1 bit */
            regs_msb = (regs >> 31) & 1;          /* MSB of regs */
            regs = regs << 1;                     /* shift regs for CRC-CCITT */
            if (regs_msb ^ msb) {                 /* MSB is a 1 */
                regs = regs ^ polynomial;         /* XOR with generator poly */
            }
            regs = regs & regs_mask;              /* Mask off excess upper bits */
            data_byte <<= 1;                      /* get to next bit */
        }
    }
    regs = regs & regs_mask;
    reflected_regs = reflect(regs, 32) ^ 0xFFFFFFFF;
    return reflected_regs;
}
#endif


