#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __int32_t int32_t;


#define SDR_SENSOR_L_LINEAR     0x00
#define SDR_SENSOR_L_LN         0x01
#define SDR_SENSOR_L_LOG10      0x02
#define SDR_SENSOR_L_LOG2       0x03
#define SDR_SENSOR_L_E          0x04
#define SDR_SENSOR_L_EXP10      0x05
#define SDR_SENSOR_L_EXP2       0x06
#define SDR_SENSOR_L_1_X        0x07
#define SDR_SENSOR_L_SQR        0x08
#define SDR_SENSOR_L_CUBE       0x09
#define SDR_SENSOR_L_SQRT       0x0a
#define SDR_SENSOR_L_CUBERT     0x0b
#define SDR_SENSOR_L_NONLINEAR  0x70


#define BSWAP_16(x) ((((x) & 0xff00) >> 8) | (((x) & 0x00ff) << 8))
#define BSWAP_32(x) ((((x) & 0xff000000) >> 24) | (((x) & 0x00ff0000) >> 8) | (((x) & 0x0000ff00) << 8) | (((x) & 0x000000ff) << 24))

#define tos32(val, bits)    ((val & ((1<<((bits)-1)))) ? (-((val) & (1<<((bits)-1))) | (val)) : (val))

# define __TO_TOL(mtol)     (uint16_t)(BSWAP_16(mtol) & 0x3f)
# define __TO_M(mtol)       (int16_t)(tos32((((BSWAP_16(mtol) & 0xff00) >> 8) | ((BSWAP_16(mtol) & 0xc0) << 2)), 10))
# define __TO_B(bacc)       (int32_t)(tos32((((BSWAP_32(bacc) & 0xff000000) >> 24) | ((BSWAP_32(bacc) & 0xc00000) >> 14)), 10))
# define __TO_ACC(bacc)     (uint32_t)(((BSWAP_32(bacc) & 0x3f0000) >> 16) | ((BSWAP_32(bacc) & 0xf000) >> 6))
# define __TO_ACC_EXP(bacc) (uint32_t)((BSWAP_32(bacc) & 0xc00) >> 10)
# define __TO_R_EXP(bacc)   (int32_t)(tos32(((BSWAP_32(bacc) & 0xf0) >> 4), 4))
# define __TO_B_EXP(bacc)   (int32_t)(tos32((BSWAP_32(bacc) & 0xf), 4))

long long convertDecimalToBinary(int);

int main()
{

    printf("%u\n", 0xfffffff8); //unsigned int
    printf("%d\n", 0xfffffff8); //signed int
    printf("%d\n", -(0x0d & (1<<3)) | 0x0d);

    int mode;
    int byte_l, byte_h;

    while(1)
     {
         int MODE;
         char mode[1024];
         printf("Choose MODE([0]:RowtoX, [1]:MBR): ");
         fgets (mode, sizeof (mode), stdin);
         if (strcmp (mode, "\n") == 0)
             break;
         MODE = atoi(mode);

         switch(MODE){
            case 0:
                {
                    printf("--> Please enter LOW byte: ");
                    scanf("%x", &byte_l);
                    printf("--> Please enter HIGH byte: ");
                    scanf("%x", &byte_h);
                    ROW2toX(byte_l, byte_h);
                    getchar();
                    break;
                }

            case 1:
                {
                    uint8_t val = 0x99;
                    uint16_t mtol = 0x004e;		    /* M, tolerance (from low to high) */
                    uint32_t bacc = 0xd0000000;		/* accuracy, B, Bexp, Rexp */
                    uint8_t unit_analog = 0x00;
                    uint8_t linearization = 0x00;

                    sdr_convert_sensor_reading(val, mtol, bacc, unit_analog, linearization);
                    break;
                }

            default:
                {
                    printf("No such command!\n\n");
                    break;
                }

        }

     }


    return 0;
}

void ROW2toX(int raw_byte_l, int raw_byte_h){
    int Y = ((0x07 & raw_byte_h)<<8) | raw_byte_l;
    int N = (raw_byte_h & 0x80)? -(((~raw_byte_h & 0xF8) >> 3) + 1) : (0xF8 & raw_byte_h)>>3;
    int X = (N>=0)? Y<<N : Y>>(-N);
    //printf("Y = %x\nN = %x\n", Y, N);
    printf("Y = %d\nN = %d\n", Y, N);
    printf("%x --> %d\n", X, X);
    //long long h = convertDecimalToBinary(raw_byte_h);
    //printf("%d\n", h);
    printf("\n");
}

long long convertDecimalToBinary(int n)
{
    long long binaryNumber = 0;
    int remainder, i = 1, step = 1;

    while (n!=0)
    {
        remainder = n%2;
        printf("Step %d: %d/2, 余数 = %d, 商 = %d\n", step++, n, remainder, n/2);
        n /= 2;
        binaryNumber += remainder*i;
        i *= 10;
    }
    return binaryNumber;
}

void sdr_convert_sensor_reading(uint8_t val, uint16_t mtol, uint32_t bacc, uint8_t unit_analog, uint8_t linearization){
    double result;
    int m, b, k1, k2;

    m = __TO_M(mtol);
    b = __TO_B(bacc);
    k1 = __TO_B_EXP(bacc);
    k2 = __TO_R_EXP(bacc);
    double k=0;
    switch (unit_analog) {
    case 0:
        //double Bexp = pow(10, )
        result = (double) (((m * val) + (b * pow(10,k1))) * pow(10,k2));
        break;
    case 1:
        if(val & 0x80)
            val++;
        /* Deliberately fall through to case 2. */
    case 2:
        result = (double) (((m * (int8_t)val) + (b * pow(10,k1))) * pow(10,k2));

        break;
    default:
        /* Oops! This isn't an analog sensor. */
        printf("no result!\n");
    }



    switch (linearization & 0x7f) {
	case SDR_SENSOR_L_LN:
		result = log(result);
		break;
	case SDR_SENSOR_L_LOG10:
		result = log10(result);
		break;
	case SDR_SENSOR_L_LOG2:
		result = (double) (log(result) / log(2.0));
		break;
	case SDR_SENSOR_L_E:
		result = exp(result);
		break;
	case SDR_SENSOR_L_EXP10:
		result = pow(10.0, result);
		break;
	case SDR_SENSOR_L_EXP2:
		result = pow(2.0, result);
		break;
	case SDR_SENSOR_L_1_X:
		result = pow(result, -1.0);	/*1/x w/o exception */
		break;
	case SDR_SENSOR_L_SQR:
		result = pow(result, 2.0);
		break;
	case SDR_SENSOR_L_CUBE:
		result = pow(result, 3.0);
		break;
	case SDR_SENSOR_L_SQRT:
		result = sqrt(result);
		break;
	case SDR_SENSOR_L_CUBERT:
		result = cbrt(result);
		break;
	case SDR_SENSOR_L_LINEAR:
	default:
		break;
	}
	printf("parameter: m=%d, b=%d, k1=%d, k2=%d\n", m, b, k1, k2);
	printf("SDR Real value = %f\n\n", result);
}
