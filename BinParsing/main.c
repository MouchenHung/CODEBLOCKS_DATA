#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef short int uint16_t;
typedef int uint32_t;


typedef struct PLDM_UPDATE_FW_PACKAGE_HEADER pu_fw_package_header;
typedef struct PLDM_UPDATE_FW_DEVICE_ID_AREA pu_fw_device_id_area;

typedef union u_FW_PACKAGE_HEADER package_header_t;
typedef union u_FW_PACKAGE_DEVICEID package_deviceid_t;

union u_FW_PACKAGE_HEADER{
    uint8_t     value[36];
    pu_fw_package_header   *realp;
};

union u_FW_PACKAGE_DEVICEID{
    uint8_t     value[36];
    pu_fw_device_id_area   *realp;
};

typedef struct PLDM_BINARY_FILE pldm_file_t;

struct PLDM_BINARY_FILE{
    pu_fw_package_header *HEADER;
    pu_fw_device_id_area *DEVICEID;

};

struct __attribute__((__packed__)) PLDM_UPDATE_FW_PACKAGE_HEADER{
    uint8_t     PackageHeaderIdentifier[16];
    uint8_t     PackageHeaderFormatRevision;
    uint16_t    PackageHeaderSize;
    uint8_t     PackageReleaseDateTime[13];
    uint16_t    ComponentBitmapBitLength;
    uint8_t     PackageVersionStringType;
    uint8_t     PackageVersionStringLength;
    uint8_t     *PackageVersionString;
};

typedef struct PLDM_UPDATE_FW_RECORD_DESCRIPTORS pu_fw_device_record_descriptors;
struct __attribute__((__packed__)) PLDM_UPDATE_FW_RECORD_DESCRIPTORS{
    uint16_t    InitialDescriptorType;
    uint16_t    InitialDescriptorLength;
    uint8_t     *InitialDescriptorData;
};

typedef struct PLDM_UPDATE_FW_DEVICE_ID_RECORDS pu_fw_device_id_records;
struct __attribute__((__packed__)) PLDM_UPDATE_FW_DEVICE_ID_RECORDS{
    uint16_t    RecordLength;
    uint8_t     DescriptorCount;
    uint32_t    DeviceUpdateOptionFlags;
    uint8_t     ComponentImageSetVersionStringType;
    uint8_t     ComponentImageSetVersionStringLength;
    uint16_t    FirmwareDevicePackageDataLength;
    uint8_t     ApplicableComponents;
    uint8_t     *ComponentImageSetVersionString;
    pu_fw_device_record_descriptors     *rd;
    uint8_t     *FirmwareDevicePackageData;
};

struct __attribute__((__packed__)) PLDM_UPDATE_FW_DEVICE_ID_AREA{
    uint8_t     DeviceIDRecordCount;
    pu_fw_device_id_records *body;
};

typedef enum {
    SECTION_HEADER,
    SECTION_DEVICEID,
    SECTION_INVALID = 0xFF
}section_t;

static pldm_file_t *PLDM_BIN_FILE;

void FreeVariable(uint8_t *ptr, uint16_t size){
    for (int i=0; i<size; i++){
        free(ptr+i);
    }
}

void Print_parsing(section_t part){
    if(part == SECTION_HEADER){
        printf("Parsing result in section [HEADER]:\n");
        printf("* PackageHeaderIdentifier: ");
        for(int i=0; i<sizeof(PLDM_BIN_FILE->HEADER->PackageHeaderIdentifier)/sizeof(uint8_t); i++){
            printf("0x%x ", *(PLDM_BIN_FILE->HEADER->PackageHeaderIdentifier+i));
        }
        printf("\n");
        printf("* PackageHeaderFormatRevision: 0x%x\n", PLDM_BIN_FILE->HEADER->PackageHeaderFormatRevision);
        printf("* PackageHeaderSize: 0x%x\n", PLDM_BIN_FILE->HEADER->PackageHeaderSize);
        printf("* PackageReleaseDateTime: ");
        for(int i=0; i<sizeof(PLDM_BIN_FILE->HEADER->PackageReleaseDateTime)/sizeof(uint8_t); i++){
            printf("0x%x ", *(PLDM_BIN_FILE->HEADER->PackageReleaseDateTime+i));
        }
        printf("\n");
        printf("* ComponentBitmapBitLength: 0x%x\n", PLDM_BIN_FILE->HEADER->ComponentBitmapBitLength);
        printf("* PackageVersionStringType: 0x%x\n", PLDM_BIN_FILE->HEADER->PackageVersionStringType);
        printf("* PackageVersionStringLength: 0x%x\n", PLDM_BIN_FILE->HEADER->PackageVersionStringLength);
        uint8_t *tmp = malloc(PLDM_BIN_FILE->HEADER->PackageVersionStringLength * sizeof(uint8_t));
        tmp = &PLDM_BIN_FILE->HEADER->PackageVersionString;
        printf("* PackageVersionString: ");
        for(int i=0; i<PLDM_BIN_FILE->HEADER->PackageVersionStringLength; i++){
            printf("0x%x ", *(tmp+i));
        }
        printf("\n");
        //free(tmp);
        //FreeVariable(tmp, PLDM_BIN_FILE->HEADER->PackageVersionStringLength);
    }
    else if(part == SECTION_DEVICEID){
        printf("Parsing result in section [RECORD]:\n");
        printf("* DeviceIDRecordCount: 0x%x\n", PLDM_BIN_FILE->DEVICEID->DeviceIDRecordCount);
        uint8_t *tmp1 = malloc(sizeof(pu_fw_device_id_area));
        tmp1 = &PLDM_BIN_FILE->DEVICEID->body;
        printf("* RecordLength: 0x%x\n", *tmp1);
    }
    else{
        printf("Warning, please check again input arguments!\n\n");
    }
}

int main()
{
    printf("Parsing PLDM fw...\n");
    uint16_t a = 0x1234;
    printf("0x%x\n", a);
    unsigned char buffer[10], buffer1[30];
    FILE *fp;

    fp = fopen("./PLX4_iSSW_GA_145220_20210219_PLDM.fw","rb");  // r for read, b for binary

    /*
    fread(buffer,sizeof(buffer),1,fp); // read 10 bytes to our buffer
    for(int i=0; i<10; i++){
        printf("0x%x ", buffer[i]);
    }

    fread(buffer1,sizeof(buffer1),1,fp); // read 10 bytes to our buffer
    for(int i=0; i<30; i++){
        printf("0x%x ", buffer1[i]);
    }
    */

    package_header_t *fw_header_u;
    fw_header_u = malloc(sizeof(uint8_t)*44);
    //fw_header_u->realp = malloc(sizeof(uint8_t)*36);

    pu_fw_package_header *fw_header;
    fw_header = (pu_fw_package_header*)malloc(sizeof(uint8_t)*36);
    fw_header = &fw_header_u->realp;

    fread(fw_header_u->value, sizeof(pu_fw_package_header), 1, fp); // for SECTION_HEADER


    package_deviceid_t *fw_deviceid_u;
    fw_deviceid_u = malloc(sizeof(uint8_t)*36);
    fread(fw_deviceid_u->value, sizeof(pu_fw_device_id_area), 1, fp); // for SECTION_DEVICEID
    printf("..........checking 0x%x - 0x%x 0x%x, 0x%x\n", fw_deviceid_u->value, *(fw_deviceid_u->value+1), fw_deviceid_u->value[2]);

    /* Add every part into one structure */
    PLDM_BIN_FILE = (pldm_file_t*) malloc(sizeof(pldm_file_t));
    PLDM_BIN_FILE->HEADER = &fw_header_u->realp;
    PLDM_BIN_FILE->DEVICEID = &fw_deviceid_u->realp;

    /* debug use */
    printf(">> %u - %u - 0x%x - 0x%x - 0x%x\n", fw_header_u->value, &fw_header_u->realp, *(fw_header->PackageHeaderIdentifier), *(PLDM_BIN_FILE->HEADER->PackageHeaderIdentifier), PLDM_BIN_FILE->HEADER->PackageHeaderFormatRevision);

    Print_parsing(SECTION_HEADER);
    Print_parsing(SECTION_DEVICEID);

    return 0;
}
