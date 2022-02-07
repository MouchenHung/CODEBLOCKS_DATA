#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef short int uint16_t;
typedef int uint32_t;

typedef signed short int int16_t;


enum{
  Self_IFs = 0x0,
  ME_IPMB_IFs = 0x01,
  BMC_IPMB_IFs = 0x02,
  HOST_KCS_IFs = 0x03,
  SERVER_IPMB_IFs = 0x04,
  EXP1_IPMB_IFs = 0x05,
  EXP2_IPMB_IFs = 0x06,

  BMC_USB_IFs = 0x10,
  Reserve_IFs,
};

enum {
  BMC_IPMB_IDX,
  ME_IPMB_IDX,
  EXP1_IPMB_IDX,
  EXP2_IPMB_IDX,
  MAX_IPMB_IDX,
};

uint8_t IPMB_inf_index_map[MAX_IPMB_IDX + 1]; // map IPMB source/target interface to bus

enum{
  I2C_IF,
  I3C_IF,
  Reserve_IF,
};

typedef struct _IPMB_config_ {
  uint8_t index;
  uint8_t Inf;
  uint8_t Inf_source;
} IPMB_config;

IPMB_config pal_IPMB_config_table[] = {
  //   index             interface         interface_source  bus              Target_addr          EnStatus  slave_addr            Rx_attr_name          Tx_attr_name//
     { BMC_IPMB_IDX,     I2C_IF,           BMC_IPMB_IFs    },
     { ME_IPMB_IDX,      I2C_IF,           ME_IPMB_IFs     },
     { EXP1_IPMB_IDX,    I2C_IF,           EXP1_IPMB_IFs    },
     { EXP2_IPMB_IDX,    I2C_IF,           EXP2_IPMB_IFs   },
     { MAX_IPMB_IDX,     Reserve_IF,       Reserve_IFs      },
};

void map_inf_index(void) {
  uint8_t inf,index_num;

  memset(IPMB_inf_index_map, MAX_IPMB_IDX, sizeof(IPMB_inf_index_map));
  for (inf = 0x01; inf != Reserve_IFs; inf++) { // interface 0x0 reserved for BIC itself
    for (index_num = 0; index_num < MAX_IPMB_IDX; index_num++) {
      if (pal_IPMB_config_table[index_num].Inf_source == inf) {
        IPMB_inf_index_map[inf] = index_num;
        break;
      }
    }
  }
  int i=0;
  while (i<5)
    {
        printf("%d\n", IPMB_inf_index_map[i]);
        i++;
    }

}

int insufficient[5];
int *block = insufficient+7;

void test6(){
    for(int i=0; i<10; i++){
        insufficient[i] = i+1;
    }
    for(int i=0; i<10; i++){
        printf("ele[%d] %d\n", i, insufficient[i]);
    }
}

void test7(){
    static char a[] = "kevin";
    static char b[] = "kevin";
    // let b[0] = a[1]
    *b = *(a+1);
    *b = '5';
    if(a==b){
        printf("kevin == KEVIN, a=%c(%d), b=%c(%d)\n", *a, a, *b, b);
    }
    else{
        printf("kevin != KEVIN, a=%c(%d), b=%c(%d)\n", *a, a, *b, b);
    }

    static char *c = "kevin";
    static char *d = "kevin";
    if(c==d){
        printf("kevin == KEVIN, c=%c(%d), d=%c(%d)\n", *c, c, *d, d);
    }
    else{
        printf("kevin != KEVIN, c=%c(%d), d=%c(%d)\n", *c, c, *d, d);
    }

    //*c = a;
    if(c==d){
        printf("kevin == KEVIN, c=%c(%d), d=%c(%d)\n", *(c+1), c, *d, d);
    }
    else{
        printf("kevin != KEVIN, c=%c(%d), d=%c(%d)\n", *(c+1), c, *d, d);
    }
    static int t = 150;
    static int *q = &t;

    printf("150 After change = %d\n", *q);
}

void _swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void test8(){
    int arr[2] = {3,5};
    int *f1 = arr;
    int *f2 = arr+1;
    printf("f1=%d, f2=%d\n", *f1, *f2);
    _swap(f1, f2);
    printf("swap --> f1=%d, f2=%d\n", *f1, *f2);

}

void test9(){
    double dum = 5.32;
    int *p = &dum, *p1;
    printf("Sizeof int = %d\n", sizeof(int));
    printf("Sizeof unsigned int_8 = %d\n", sizeof(uint8_t));
    printf("Sizeof float = %d\n", sizeof(float));
    printf("Sizeof double = %d\n", sizeof(double));
    printf("Sizeof *p = %d\n", sizeof(*p));
    printf("Address of *p = %p, *p1 = %p\n", p, p1);
    u_int16_t *dynamic_heaper;
    uint8_t numbers = 3;
    dynamic_heaper = (u_int16_t*)malloc(sizeof(u_int16_t) * numbers);
    *dynamic_heaper = 0x1234;
    *(dynamic_heaper+1) = 0x5678;
    printf("First = 0x%x, Second = 0x%x\n", *dynamic_heaper, *(dynamic_heaper+1));
}

struct i2c_ipmb_slave_config {
	char *controller_dev_name;
	uint8_t address;
	uint32_t ipmb_msg_length;
};

/* I2C slave table */
struct i2c_ipmb_slave_config I2C_SLAVE_CFG_TABLE[] = {
  {"I2C_0", 0x20, 0xA},
  {"I2C_1", 0xFF, 0xA},
  {"I2C_2", 0xFF, 0xA},
  {"I2C_3", 0xFF, 0xA},
  {"I2C_4", 0xFF, 0xA},
  {"I2C_5", 0xFF, 0xA},
  {"I2C_6", 0xFF, 0xA},
  {"I2C_7", 0xFF, 0xA},
  {"I2C_8", 0xFF, 0xA},
  {"I2C_9", 0xFF, 0xA},
  {"I2C_10", 0xFF, 0xA},
  {"I2C_11", 0xFF, 0xA},
  {"I2C_12", 0xFF, 0xA},
  {"I2C_13", 0xFF, 0xA},
  {"I2C_14", 0xFF, 0xA},
  {"I2C_15", 0xFF, 0xA}
};

/*
#define I2C_SLAVE_DEV_SET(inst)  static struct i2c_ipmb_slave_config		 \
		i2c_ipmb_slave_##inst##_cfg = {			 \
		.controller_dev_name = I2C_SLAVE_CFG_TABLE[inst].controller_dev_name,	 \
		.address = I2C_SLAVE_CFG_TABLE[inst].address,		 \
		.ipmb_msg_length = I2C_SLAVE_CFG_TABLE[inst].ipmb_msg_length,	 \
	};
*/
/*
static struct i2c_ipmb_slave_config aaaaa = {
    .controller_dev_name = &I2C_SLAVE_CFG_TABLE[0].controller_dev_name,
    .address = I2C_SLAVE_CFG_TABLE[0].address,
    .ipmb_msg_length = I2C_SLAVE_CFG_TABLE[0].ipmb_msg_length
};
*/

void transName(char *name, char *ref_name){
    printf("get name: %s\n", name);
    if(!strcmp(name, ref_name)){
        printf("find!\n");
    }
    else
        printf("bad!\n");
}

void test10(){
    static struct i2c_ipmb_slave_config tmp_s;
    tmp_s.controller_dev_name = I2C_SLAVE_CFG_TABLE[0].controller_dev_name;
    printf("Name: %s - %s\n", I2C_SLAVE_CFG_TABLE[0].controller_dev_name, tmp_s.controller_dev_name);

    transName("I2C_0", tmp_s.controller_dev_name);
    //I2C_SLAVE_DEV_SET(0);
    //printf("Name: %s\n", i2c_ipmb_slave_0_cfg.controller_dev_name);

    char tmp_name[] = "123456789";
    printf("char 0 = %c\n", tmp_name[0]);
    printf("char 1 = %c\n", tmp_name[1]);
}

void test11(){
    uint8_t inputdata[] = {0x00, 0x08, 0x05, 0x07};

}

void test12(){
    uint8_t bus_num = 0;
    char ControlerName[] = "I2C_";
	char num[4];
	sprintf(num, "%d", (int)bus_num);
	strcat(ControlerName, num);
	printf("Concat name: %s\n", ControlerName);
}

#define I2C_DEVICE_PREFIX "I2C_"
/*
void test13(uint8_t bus_num, char *controllerName){
	char num[4];
	printf("size of input = %d\n", sizeof(controllerName));
    strcpy(controllerName, I2C_DEVICE_PREFIX);
    printf("Concat name: %s\n", controllerName);
	sprintf(num, "%d", (int)bus_num);
	strcat(controllerName, num);
    printf("Concat name: %s\n", controllerName);
}*/

char* test13(uint8_t bus_num){
	char num[4];
	char *controllerName = (char*)malloc(10);
	static char fixed_mem[10];
	printf("size of input = %d\n", sizeof(controllerName));
    strcpy(controllerName, I2C_DEVICE_PREFIX);
    printf("Concat name: %s\n", controllerName);
	sprintf(num, "%d", (int)bus_num);
	strcat(controllerName, num);
    printf("Concat name: %s\n", controllerName);
    memcpy(fixed_mem, controllerName, 10);
    free(controllerName);

    return fixed_mem;
}

void test14(){
    char a[10] = "";
    memset(a, 0, 10);
    if (a)
        printf("Not empty!\n");
    else
        printf("empty!\n");
}

#define STR(x) #x
#define I2C_CONTROLLER_NAME_GET(inst) I2C_DEVICE_PREFIX #inst
#define plus(a,b) "inst" #b
#define DO_CONCAT(x, y) x ## y
void test15(){
    char num = '9';
    printf("name = %s %s\n", I2C_CONTROLLER_NAME_GET(num));
}

void get_name(char *name){
    printf("get name: %s\n", name);
}

#define EQUALSTR(x,y) (strcmp(x,y) == 0?1:0)

#define test5(x,y)   (EQUALSTR(x,y) ? printf("yes\n") : printf("no\n"))

#define CAL_SUM(x,y)  x+y

#define test0(x, y)                                     \
({                                                      \
    float answer;                                       \
    if (EQUALSTR((x),(y))) {                         \
        printf("--> yes\n");                                     \
    } else {                                            \
        printf("--> no\n");    \
    }                                                   \
})

#define test(x, y)                                     \
({                                                      \
    (x) == (y) ? printf("--> yes\n"):printf("--> no\n");                                                  \
})

/*Can't use function in front of '?'*/
/*
#define test1(x, y)                                     \
({                                                      \
    strcmp((x),(y)) == (0) ? printf("--> yes\n"):printf("--> no\n");                                                  \
})
*/

#define test2(x, y)                                     \
({                                                      \
    int flag;\
    flag = CAL_SUM(x,y);\
    flag ? printf("--> yes\n"):printf("--> no\n");                                                  \
})

//#define test(x,y) EQUALSTR(x,y) ? 1: 0

#define STRCMP(a, R, b) (strcmp(a, b) R 0)

#define strcmp_print(x, y)                                     \
({                                                      \
    float answer;                                       \
    if ((x) == (y)) {                         \
        printf("--> yes\n");                                     \
    } else {                                            \
        printf("--> no\n");    \
    }                                                   \
})



#if ABC == 1
#define CBA 10
#else
#define CBA 5
#endif // ABC

#define ABC 0

#define MAX_EXC_LOG 10

#define bbb "1234"

int main()
{
    printf("TEST0.\n");
    int a = 0x15;
    int b = 0xff;
    int sum = a+b;

    printf("sum = 0x%x\n", sum);
    printf("hb,lb = 0x%x 0x%x\n", sum>>8&0xff, sum&0xff);

    printf("TEST1.\n");
    strcmp_print("bbb","aaa");
    printf("TEST2.\n");
    test0("2","2");
    printf("TEST3.\n");
    char p1[] = "123";
    test(p1, p1);
    printf("TEST4.\n");
    printf("--> %d\n", EQUALSTR("abc","abc"));

    if(EQUALSTR("abc","abc") == 1){
        printf("yes\n");
    }
    else
        printf("no\n");


    if (strcmp(("2"),("2"))) {
        printf("-----> yes\n");
    } else {
        printf("-----> no\n");
    }
    printf("TEST5.\n");
    test5("1", "5");
    printf("TEST6.\n");
    printf("%d\n", test5("5", "5"));

    printf("TEST6.\n");
    test6();
    //map_inf_index();

    printf("TEST7.\n");
    test7();

    printf("TEST8.\n");
    test8();

    printf("TEST9.\n");
    test9();

    printf("TEST10.\n");
    test10();

    printf("TEST12.\n");
    test12();

    printf("TEST13.\n");
    //char name[10];
    //test13(3, &name);
    char *name = test13(3);
    printf("device name = %s %p\n", name, name);

    name = test13(10);
    printf("device name = %s %p\n", name, name);

    printf("define test: %d\n", CBA);

    printf("TEST14.\n");
    test14();

    printf("TEST15.\n");
    test15();


    printf("answer = %d\n", 10 / 2 * 3);


    char string[50] = "Hello world";
    /*
    // Extract the first token
    char * token = strtok(string, " ");
    printf( " %s\n", token ); //printing the token
    */

    static char exc_log[MAX_EXC_LOG][15] = {
        "ipmb",
    };
    for (int i=0; i<MAX_EXC_LOG; i++){
        if (exc_log[i][0] != '\0')
            get_name(exc_log[i]);
        else
            printf("noting..\n");
    }

    uint8_t C = -40;
    printf("--> 0x%x\n", C);

    unsigned char D = 252;
    unsigned char *DD;
    DD = malloc(sizeof(unsigned char) * 2);
    memset(DD, 0, sizeof(unsigned char) * 2);
    memcpy(DD, &D, 1);

    printf("--> %d %d\n", D, *DD);

    char AC = 'A';
    printf("--> %d\n", 'B');

    int i=2;
    printf("%d %d %d \n", i, ++i, ++i);

    int ddf[3] = {1,2,3};
    int *n = ddf;
    printf("%d %d %d\n", *n, *++n, *++n);


    unsigned char aaa[5] = "1234";
    if (!memcmp(aaa, bbb, sizeof(aaa)/sizeof(unsigned char)))
        printf("same!\n");
    else
        printf("diff\n");

    struct S1{
        char a[4];
        char *b;
    };
    struct S1 s1 = {"abc", "def"};

    printf("%c %c\n", s1.a[0], *s1.b);

    int acx = 100;
    int16_t integer = acx/3 ;
    int16_t frag =
    printf("%d.%d\n", integer, frag);

    return 0;
}
