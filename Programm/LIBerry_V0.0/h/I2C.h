#include "main.h"
#ifndef H_I2C_H_
#define H_I2C_H_
//#ifdef HAL_I2C_MODULE_ENABLED

#if defined arm3    // Controller

//typedef struct __I2C_HandleTypeDef
//{
//  I2C_TypeDef                *Instance;      /*!< I2C registers base address               */
//
// // I2C_InitTypeDef            Init;           /*!< I2C communication parameters             */
//
//  uint8_t                    *pBuffPtr;      /*!< Pointer to I2C transfer buffer           */
//
//  uint16_t                   XferSize;       /*!< I2C transfer size                        */
//
//  __IO uint16_t              XferCount;      /*!< I2C transfer counter                     */
//
//  __IO uint32_t              XferOptions;    /*!< I2C transfer options                     */
//
//  __IO uint32_t              PreviousState;  /*!< I2C communication Previous state and mode
//                                                  context for internal usage               */
//
//  DMA_HandleTypeDef          *hdmatx;        /*!< I2C Tx DMA handle parameters             */
//
//  DMA_HandleTypeDef          *hdmarx;        /*!< I2C Rx DMA handle parameters             */
//
//  HAL_LockTypeDef            Lock;           /*!< I2C locking object                       */
//
////  __IO HAL_I2C_StateTypeDef  State;          /*!< I2C communication state                  */
//
////  __IO HAL_I2C_ModeTypeDef   Mode;           /*!< I2C communication mode                   */
//
//  __IO uint32_t              ErrorCode;      /*!< I2C Error code                           */
//
//  __IO uint32_t              Devaddress;     /*!< I2C Target device address                */
//
//  __IO uint32_t              Memaddress;     /*!< I2C Target memory address                */
//
//  __IO uint32_t              MemaddSize;     /*!< I2C Target memory address  size          */
//
//  __IO uint32_t              EventCount;     /*!< I2C Event counter                        */
//
//} I2C_HandleTypeDef;
#endif  //Arm3




//typedef struct
//{
//   I2C_HandleTypeDef *hi2c; //*hi2c
//   uint16_t DevAddress_2;
//}I2C;



typedef struct
{
   GPIO SDA; //*hi2c
   GPIO SCL; //*hi2c
   uint8_t SDA_PIN;
   uint8_t SCL_PIN;
   GPIO_TypeDef *PORT;
  }I2C_mine;

typedef enum
{
	write_i2c=0,
	read_i2c=1
};





//#define DEV_ADDR_WR 0x70	// 0x40 - pcf8574, 0x70 - pcf8574a
//#define DEV_ADDR_RD 0x71	// 0x41 - pcf8574, 0x71 - pcf8574a

#define TIMEOUT 10

#define I2C_PORT	GPIOB
#define I2C_SCL		0       //6
#define I2C_SDA		1       //7


//#define SDA_		GPIOC,7       //7
//#define SCL_		GPIOC,6       //7



//extern I2C scr2;


//void I2C_Scan(I2C *scr);


//void sendData_I2C(I2C *scr2 , uint8_t *pData);

//I2C_HandleTypeDef *pcf8574hi2c;




void byte_write(uint16_t address, uint8_t val2write);
uint8_t read_current_addr_data(uint16_t address);


// В CUBE MX порты I2C настроить на выход (либо в main.c вручну подать тактирование на нужны GPIO)

#define SCL_I HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
#define SDA_I HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
#define SCL_O HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
#define SDA_O HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
//--------------------------------------------------------------------------------
void i2c_init (I2C_mine I2C_P);               		// Инициализация шины
void i2c_start (I2C_mine I2C_P);        			// Генерация условия старт
void i2c_restart_cond ( I2C_mine I2C_P);      			// Генерация условия рестарт
void i2c_st_test (I2C_mine I2C_P) ;       			// Генерация условия стоп

uint8_t i2c_send_byte( uint8_t data, uint8_t byte ,uint8_t type ,I2C_mine I2C_P);     // Передать байт ID (вх. аргумент передаваемый байт) (возвращает 0 - АСК, 1 - NACK)
uint8_t i2c_ID(uint8_t I2C_IDD, I2C_mine I2C_P ); // Чтение ID

uint8_t i2c_writeByte( uint16_t dat, uint8_t byte, I2C_mine I2C_P  ); // посылка только 8-ми данных
uint8_t i2c_get_byte( uint8_t last_byte ,I2C_mine I2C_P);   // получить 8-мь байт


uint8_t i2c_readByte(I2C_mine I2C_P,uint8_t ID);
uint8_t i2c_readByteID(uint8_t devId);
uint8_t i2c_SendID_Data_read(uint8_t devId,uint8_t data,uint8_t byte1,uint8_t byte2);

uint8_t i2c_send_2byte( uint8_t data, uint8_t byte ,uint8_t type ,uint8_t Address,I2C_mine I2C_P);
uint8_t i2c_SendByteConfData( uint8_t ID,uint8_t config ,uint8_t data_w,I2C_mine I2C_P);

void clk_I2C(I2C_mine I2C_P);
void init_I2C(I2C_mine I2C_P);
uint8_t I2C_ID_test(I2C_mine I2C_P, uint8_t data, uint8_t byte,_Bool type);
uint8_t i2c_send_3byte( uint8_t ID, uint8_t byte ,uint8_t type ,uint8_t Config,uint8_t data , I2C_mine I2C_P);
void SCL_in( I2C_mine I2C_P );    // void


void I2C_Scan(I2C_mine *scr );

#endif /* H_I2C_H_ */
//#endif /* H_I2C_H_ */
