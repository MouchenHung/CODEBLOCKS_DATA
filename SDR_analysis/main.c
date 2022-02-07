#include <stdio.h>
#include <stdlib.h>

typedef  unsigned char   INT8U;

const INT8U DefaultSdrr[] = {

		/*******/
		/* BMC */
		/*******/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_MC_DEV_LOCATOR, /* Record Type */
			IPMI_SDR_MC_SENSOR_MIN_LEN + 3, /* Record Length, base length + ID string length */

			/* key */
			0x20, /* device slave address */
			0x00, /* channel number */

			/* body */
			0x00, /* Power State Notification Global Initialization */
			0x1F, /* Device Capabilities */
			0x00, 0x00, 0x00, /* reserved */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_MGT_MOD,
			0x00,
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 3, /* ID string type/length, length should be between 0 to 16 */
			'B', 'M', 'C', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/***********/
		/* PDB FRU */
		/***********/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FRU_DEV_LOCATOR, /* Record Type */
			IPMI_SDR_FRU_SENSOR_MIN_LEN + 3, /* Record Length, base length + ID string length */

			/* keys */
			0x68, /* slave address */
			PDB_FRU_ID, /* FRU device ID */
			0x80, /* LUN/ Bus ID */
			0x00, /* channel number */

			/* body */
			0x00, /* reserved */
			/* device type and modifier */
			IPMI_DEV_TYPE_FRU_BEDHIND_MC,
			IPMI_DEV_TYPE_MOD_IPMI_FRU,
			/* entity ID and instance */
			IPMI_ENTITY_ID_PDB,
			0x00,
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 3,
			'P', 'D', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#if 0
		/**************/
		/* HDD BP FRU */
		/**************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FRU_DEV_LOCATOR, /* Record Type */
			IPMI_SDR_FRU_SENSOR_MIN_LEN + 6, /* Record Length, base length + ID string length */

			/* keys */
			0x68, /* slave address */
			HDD_FRU_ID, /* FRU device ID */
			0x80, /* LUN/ Bus ID */
			0x00, /* channel number */

			/* body */
			0x00, /* reserved */
			/* device type and modifier */
			IPMI_DEV_TYPE_FRU_BEDHIND_MC,
			IPMI_DEV_TYPE_MOD_IPMI_FRU,
			/* entity ID and instance */
			IPMI_ENTITY_ID_BACKPLANE,
			0x00,
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 6,
			'H', 'D', 'D', ' ', 'B', 'P', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif

		///////////////////////////////////////////////////////////////////////////////////
		//  FULL SENSOR RECORD REGION BEGIN
		///////////////////////////////////////////////////////////////////////////////////

		/*************************************************************************************************/
		/************************************** temperature **********************************************/
		/*************************************************************************************************/

		/******************************************/
		/* temperature of back panel1, TMP75      */
		/******************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 12, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_HDD_AMBIENT1, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_BACKPLANE,
			0x01,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_TEMPERATURE, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x80, /* sensor unit */
			IPMI_SENSOR_UNIT_DEGREE_C, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x01, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x23, /* normal reading */
			0x00, /* normal maximum */
			0x00, /* normal minimum */
			0x7F, /* sensor maximum reading */
			0x80, /* sensor minimum reading */
			0x00, /* UNRT */
			0x32, /* UCT */
			0x2D, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 12, /* ID string type/length, length should be between 0 to 16 */
			'H', 'D', 'D', '_', 'A', 'm', 'b', 'i', 'e', 'n', 't', '1', 0x00, 0x00, 0x00, 0x00,

		/******************************************/
		/* temperature of back panel2, TMP75      */
		/******************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 12, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_HDD_AMBIENT2, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_BACKPLANE,
			0x02,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_TEMPERATURE, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x80, /* sensor unit */
			IPMI_SENSOR_UNIT_DEGREE_C, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x01, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x23, /* normal reading */
			0x00, /* normal maximum */
			0x00, /* normal minimum */
			0x7F, /* sensor maximum reading */
			0x80, /* sensor minimum reading */
			0x00, /* UNRT */
			0x32, /* UCT */
			0x2D, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 12, /* ID string type/length, length should be between 0 to 16 */
			'H', 'D', 'D', '_', 'A', 'm', 'b', 'i', 'e', 'n', 't', '2', 0x00, 0x00, 0x00, 0x00,

		/******************************************/
		/* temperature of front panel, TMP75   */
		/******************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 10, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_FP_AMBIENT, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_BACKPLANE,
			0x02,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_TEMPERATURE, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x80, /* sensor unit */
			IPMI_SENSOR_UNIT_DEGREE_C, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x01, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x23, /* normal reading */
			0x00, /* normal maximum */
			0x00, /* normal minimum */
			0x7F, /* sensor maximum reading */
			0x80, /* sensor minimum reading */
			0x00, /* UNRT */
			0x32, /* UCT */
			0x2D, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 10, /* ID string type/length, length should be between 0 to 16 */
			'F', 'P', '_', 'A', 'm', 'b', 'i', 'e', 'n', 't', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/******************************************/
		/* temperature of front panel2, TMP75  */
		/******************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 11, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_FP2_AMBIENT, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_BACKPLANE,
			0x02,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_TEMPERATURE, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x80, /* sensor unit */
			IPMI_SENSOR_UNIT_DEGREE_C, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x01, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x23, /* normal reading */
			0x00, /* normal maximum */
			0x00, /* normal minimum */
			0x7F, /* sensor maximum reading */
			0x80, /* sensor minimum reading */
			0x00, /* UNRT */
			0x32, /* UCT */
			0x2D, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 11, /* ID string type/length, length should be between 0 to 16 */
			'F', 'P', '2', '_', 'A', 'm', 'b', 'i', 'e', 'n', 't', 0x00, 0x00, 0x00, 0x00, 0x00,


		/*************************************************************************************************/
		/************************************** voltage **************************************************/
		/*************************************************************************************************/

		/***************************/
		/* Voltage of 12V*/
		/***************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 4, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_12V, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_BOARD,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_CURRENT, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			0x00,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_VOL, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x4E, /* M bits[7:0] */   //0x47  //jerry modify
			0x00, /* M bits[9:8], tolerance[7:0] */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[5:0] */
			0x00, /* accuracy[9:6], accuracy exp[1:0], sensor direction[1:0] */
			0xD0, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 4, /* ID string type/length, length should be between 0 to 16 */
			'P', '1', '2', 'V', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/***************************/
		/* Voltage of 12V_STB*/
		/***************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 8, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_12V_STB, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_BOARD,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_CURRENT, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			0x00,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_VOL, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x4E, /* M bits[7:0] */  //0x47   //jerry modify
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0xD0, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 8, /* ID string type/length, length should be between 0 to 16 */
			'P', '1', '2', 'V', '_', 'S', 'T', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/***************************/
		/* Voltage of 5V*/
		/***************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 3, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_5V, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_BOARD,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_CURRENT, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			0x00,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_VOL, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x20, /* M bits[7:0] */  // 0x1D //jerry modify
 			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0xD0, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 3, /* ID string type/length, length should be between 0 to 16 */
			'P', '5', 'V', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/***************************/
		/* Voltage of 3V_STB*/
		/***************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 7, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_3V3_STB, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_BOARD,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_CURRENT, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			0x00,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_VOL, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0xD2, /* M bits[7:0] */  //0xBE  //jerry modify
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0xC0, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 7, /* ID string type/length, length should be between 0 to 16 */
			'P', '3', 'V', '_', 'S', 'T', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#if 0
		/***************************/
		/* Voltage of 3V*/
		/***************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 3, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_3V3, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_BOARD,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_CURRENT, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			0x00,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_VOL, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0xD2, /* M bits[7:0] */ // 0xBE //jerry modify
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0xC0, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 3, /* ID string type/length, length should be between 0 to 16 */
			'P', '3', 'V', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
#endif

		/*************************************************************************************************/
		/************************************** Current **************************************************/
		/*************************************************************************************************/

		/***************************/
		/* Current of FAN 12V, Ina219 */
		/***************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 10, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_FAN_PS_12V, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_SYS_BOARD,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_CURRENT, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			0x00,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_WATT, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x02, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 10, /* ID string type/length, length should be between 0 to 16 */
			'F', 'A', 'N', '_', 'P', 'S', '_', '1', '2', 'V', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/*************************************************************************************************/
		/************************************** PSU ******************************************************/
		/*************************************************************************************************/

		/*************************************/
		/* PSU Input */
		/*************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 13, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_TOP_PSU_INPUT, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_POWER_SUPPLY,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_POWER_SUPPLY, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_WATT, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x0D, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 13, /* ID string type/length, length should be between 0 to 16 */
			'T', 'O', 'P', '_', 'P', 'S', 'U', ' ', 'I', 'n', 'p', 'u', 't', 0x00, 0x00, 0x00,

		/*************************************/
		/* PSU Input */
		/*************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 13, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_BOT_PSU_INPUT, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_POWER_SUPPLY,
			0x00,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_POWER_SUPPLY, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_WATT, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x0D, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 13, /* ID string type/length, length should be between 0 to 16 */
			'B', 'O', 'T', '_', 'P', 'S', 'U', ' ', 'I', 'n', 'p', 'u', 't', 0x00, 0x00, 0x00,

		/*************************************/
		/* PSU Output */
		/*************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 14, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_TOP_PSU_OUTPUT, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_POWER_SUPPLY,
			0x01,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_POWER_SUPPLY, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_WATT, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x0D, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 14, /* ID string type/length, length should be between 0 to 16 */
			'T', 'O', 'P', '_', 'P', 'S', 'U', ' ', 'O', 'u', 't', 'p', 'u', 't', 0x00, 0x00,

		/*************************************/
		/* PSU Output */
		/*************************************/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 14, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_BOT_PSU_OUTPUT, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_POWER_SUPPLY,
			0x01,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_POWER_SUPPLY, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_UCT_READABLE | IPMI_UNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_WATT, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x0D, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x83, /* normal reading */
			0xA8, /* normal maximum */
			0x00, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0xFF, /* UNRT */
			0xFF, /* UCT */
			0xFF, /* UNCT */
			0x00, /* LNRT */
			0x00, /* LCT */
			0x00, /* LNCT */
			0x00, /* positive-going hysteresis */
			0x00, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 14, /* ID string type/length, length should be between 0 to 16 */
			'B', 'O', 'T', '_', 'P', 'S', 'U', ' ', 'O', 'u', 't', 'p', 'u', 't', 0x00, 0x00,


		/*************************************************************************************************/
		/************************************** fan ******************************************************/
		/*************************************************************************************************/

		/********************************************/
		/* FAN1A */
		/********************************************/
			/* Full Sensor Record -- System Fan 1A */
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN1A, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x01,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '1', 'A', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN1B */
		/********************************************/
			/* Full Sensor Record -- System Fan 1B  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN1B, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x02,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '1', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN2A */
		/********************************************/
			/* Full Sensor Record -- System Fan 2A  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN2A, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x03,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
		    0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '2', 'A', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN2B */
		/********************************************/
			/* Full Sensor Record -- System Fan 2B  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN2B, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x04,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
		    0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '2', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN3A */
		/********************************************/
			/* Full Sensor Record -- System Fan 3A  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN3A, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x05,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '3', 'A', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN3B */
		/********************************************/
			/* Full Sensor Record -- System Fan 3B  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN3B, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x06,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '3', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN4A */
		/********************************************/
			/* Full Sensor Record -- System Fan 4A  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN4A, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x07,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '4', 'A', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN4B */
		/********************************************/
			/* Full Sensor Record -- System Fan 4B  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN4B, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x08,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '4', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN5A */
		/********************************************/
			/* Full Sensor Record -- System Fan 4A  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN5A, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x09,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '5', 'A', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		/********************************************/
		/* FAN5B */
		/********************************************/
			/* Full Sensor Record -- System Fan 4B  ADT7490*/
			/* header */
			0xa5, 0x5a, /* record ID */
			IPMI_SDR_VER_15, /* SDR version */
			IPMI_SDR_TYPE_FULL_SENSOR, /* Record Type */
			IPMI_SDR_FULL_SENSOR_MIN_LEN + 9, /* Record Length, base length + ID string length */

			/* key */
			0x68, /* sensor owner ID */
			0x00, /* sensor owner LUN */
			SENSOR_NUM_SYS_FAN5B, /* sensor number */

			/* body */
			/* entity ID and instance, identify the entity that the sensor is monitoring */
			IPMI_ENTITY_ID_FAN,
			0x0A,
			/* sensor initialization */
			IPMI_SDR_SENSOR_INIT_SCAN | IPMI_SDR_SENSOR_INIT_EVENT |
			IPMI_SDR_SENSOR_INIT_THRESHOLD | IPMI_SDR_SENSOR_INIT_HYSTERESIS |
			IPMI_SDR_SENSOR_INIT_DEF_EVENT | IPMI_SDR_SENSOR_INIT_DEF_SCAN,
			/* sensor capabilities */
			IPMI_SDR_SENSOR_CAP_AUTO_RE_ARM | IPMI_SDR_SENSOR_CAP_HYSTERESIS_RO |
			IPMI_SDR_SENSOR_CAP_THRESHOLD_RW | IPMI_SDR_SENSOR_CAP_EVENT_CTRL_BIT,
			IPMI_SENSOR_TYPE_FAN, /* sensor type */
			IPMI_EVENT_TYPE_THRESHOLD, /* event/reading type */
			/* assertion event/lower threshold reading mask, LSB first */
			0x00,
			0x00,
			/* deassertion event/upper threshold reading mask, LSB first */
			0x00,
			0x00,
			/* Discrete Reading / Settable & Readable Threshold Mask, LSB first */
			IPMI_LCT_READABLE | IPMI_LNCT_READABLE,
			0x00,
			/* sensor units */
			0x00, /* sensor unit */
			IPMI_SENSOR_UNIT_RPM, /* base unit */
			0x00, /* modifier unit */
			IPMI_LINEAR_LINEAR, /* linearization */
			0x64, /* M bits[7:0] */
			0x00, /* M bits[9:8], tolerance */
			0x00, /* B bits[7:0] */
			0x00, /* B bits[9:8], accuracy[3:0] */
			0x00, /* accuracy[7:4], accuracy exp, sensor direction */
			0x00, /* R exp[3:0], B exp[3:0] */
			0x00, /* analog characteristic flags */
			0x74, /* normal reading */
			0xF4, /* normal maximum */
			0x29, /* normal minimum */
			0xFF, /* sensor maximum reading */
			0x00, /* sensor minimum reading */
			0x00, /* UNRT */
			0x00, /* UCT */
			0x00, /* UNCT */
			0x00, /* LNRT */
			0x05, /* LCT */
			0x00, /* LNCT */
			0x02, /* positive-going hysteresis */
			0x02, /* negative-going hysteresis */
			0x00, 0x00,  /* reserved */
			0x00, /* OEM */
			IPMI_STRING_TYPE_ASCII_8 | 9, /* ID string type/length, length should be between 0 to 16 */
			'P', 'D', 'B', '_', 'F', 'A', 'N', '5', 'B', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		///////////////////////////////////////////////////////////////////////////////////
		//  FULL SENSOR RECORD REGION END
		///////////////////////////////////////////////////////////////////////////////////

};


int main()
{
    printf("%s\n", );
    return 0;
}
