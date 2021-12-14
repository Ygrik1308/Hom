#include "main.h"
//////////////////////////////////////
#ifdef I2C//HAL_I2C_MODULE_ENABLED
//////////////////////////////////////
#include "I2C.h"

 /////////////////////////////////////////////////////////////////////
    volatile uint8_t i2c_frame_error = 0;

//----------------------- ++
//------------------------------------
void Delay_us( uint32_t tickCount )
{
    for( uint32_t i = 0; i < tickCount; i++ ) {asm( "nop" );}
}
//----------------------- ++
//------------------------------------
     void SCL_in( I2C_mine I2C_P)    // SCL = 1 SCL-> IN
{

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin  = ( 1 <<  I2C_P.SCL_PIN ) ;   //  ( 1 << I2C_P );//I2C( 1 << I2C_SCL );  I2C_P   I2C_P.PORT
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   // GPIO_InitStruct.Pin  = ( 1 << I2C_SCL );
    GPIO_InitStruct.Pull  =   GPIO_PULLUP;  //+
    HAL_GPIO_Init( I2C_P.PORT, &GPIO_InitStruct ); //I2C_PORT
}
//-----------------------
//------------------------------------
void SCL_out( I2C_mine I2C_P )     // SCL = 0 SCL-> OUT
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin   = ( 1 << I2C_P.SCL_PIN );
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( I2C_P.PORT, &GPIO_InitStruct );
    SCL_O;
}
//----------------------- ++
//------------------------------------
void SDA_in( I2C_mine I2C_P )  //SDA = 1 SCL-> IN
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin  = ( 1 << I2C_P.SDA_PIN  ); //I2C_SDA
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init( I2C_P.PORT, &GPIO_InitStruct );
}
//----------------------- ++ 0
//------------------------------------
void SDA_out( I2C_mine I2C_P)  //SDA = 0 SCL-> OUT
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin   = ( 1 << I2C_P.SDA_PIN );
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init( I2C_P.PORT, &GPIO_InitStruct );
    SDA_O;
}

//------------------------------------
void i2c_st_test( I2C_mine I2C_P )  //start / stop test line
{
    uint16_t SCL, SDA;
    SCL_out(I2C_P);
    	Delay_us( 10 );  //
    	SDA_out(I2C_P);
    	Delay_us( 10 );  //  SDA
    SCL_in(I2C_P);
    	Delay_us( 10 );  //  SCL
    	SDA_in(I2C_P);
    	Delay_us( 10 );  //  SDA
    //
    i2c_frame_error = 0;  //
    SCL = SCL_I;
    SDA = SDA_I;
    	if( SCL == 0 )
    		i2c_frame_error++;  //�
    	if( SDA == 0 )
   		i2c_frame_error++;      //
//    SCL_out();      //?
//        Delay_us( 10 );
//    SCL_in();      // ?

    Delay_us( 40 );
}

//-----------------------
//------------------------------------
void i2c_start( I2C_mine I2C_P )
{
    SDA_out(I2C_P);
    Delay_us( 10 );  //
    SCL_out(I2C_P);
    Delay_us( 10 );  //
}
//----------------------- �
//------------------------------------
void i2c_init( I2C_mine I2C_P )
{
	i2c_st_test(I2C_P);  //
	i2c_st_test(I2C_P);  //
}

//-----------------------
//------------------------------------
void i2c_restart_cond( I2C_mine I2C_P)
{
    SDA_in(I2C_P);
    Delay_us( 10 );  //
    SCL_in(I2C_P);
    Delay_us( 10 );  //
    SDA_out(I2C_P);
    Delay_us( 10 );  //
    SCL_out(I2C_P);
    Delay_us( 10 );  //
}
//-----------------------

//////////////////////////////////////////////////////////////////////test
uint8_t i2c_writeByte( uint16_t dat, uint8_t byte ,I2C_mine I2C_P)  //send I2C 1byte write
{

	uint8_t error=0;
    _Bool   SDA=1;
    ////////////////////////////////////////////////////////////////////////////////
    for(uint8_t i = 0; i < byte+1; i++ )
    {
       (dat & 0x80 )  ? SDA_in(I2C_P) :  SDA_out(I2C_P);

        Delay_us( 10 );
       	SCL_in(I2C_P);
       	Delay_us( 10 );
        SCL_out(I2C_P);   				//
        dat <<= 1;
    }

//    /////////////////////////////////////////////////////////////////
//    i2c_stop_cond();
    SCL_in(I2C_P);

    Delay_us( 10 );

    SDA = READ_PIN(I2C_PORT,I2C_SDA); //printf("Error\n"); !=0){error=error+1;}

  //  SDA_in(I2C_P);  // Return SDA

	return SDA;  //

//   i2c_stop_cond();
}
////////////////////////////////////////////////////////////////////////////////////working +
uint8_t i2c_send_byte( uint8_t data, uint8_t byte ,uint8_t type, I2C_mine I2C_P ) //+  ID Sendb + type -(write/read) 1 byte
{
	uint8_t error=0;
    _Bool   SDA=1;
    _Bool   SCL=1;
    ////////////////////////////////////////////////////////////////////////////////
    for(uint8_t i = 0; i < byte; i++ )
    {
       (data & 0x80 )  ? SDA_in(I2C_P) :  SDA_out(I2C_P);

        Delay_us( 10 );
       	SCL_in(I2C_P);
       	Delay_us( 10 );
        SCL_out(I2C_P);   				//
        data <<= 1;
    }
    /////////////////////////////////////////////////////////////////read / WRITE
     (type ) ? SDA_in(I2C_P) :  SDA_out(I2C_P);  // SDA_in();

    SCL_in(I2C_P);  // Delay_us(10);
    ///////////////////////////////////////////////////////////////// i2c_stop_cond
 //    i2c_stop_cond();
 ///////////////////////////////////////////////////////////////////////  Stop
    SCL_out(I2C_P);
    	Delay_us( 10 );  //
      SDA_out(I2C_P);
    	Delay_us( 10 );  //  SDA
    SCL_in(I2C_P);
    	Delay_us( 10 );  //  SCL
        SDA_in(I2C_P);
 //   	Delay_us( 10 );  //  SDA
////////////////////////////////////////////////////////////////////////
    	Delay_us( 30 );  //40
/////////////////////////////////////////////////////////////////////////////
    SCL_in(I2C_P);  //in
    	Delay_us( 10 );
    if(SDA = READ_PIN(I2C_PORT,I2C_SDA)!=0){error=error+1;}// printf("Error\n");

    SCL_out(I2C_P);
       SDA_in(I2C_P);            //
    SCL_in(I2C_P);  //in


    return SDA;  //
}
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
uint8_t i2c_send_2byte( uint8_t ID, uint8_t byte ,uint8_t type ,uint8_t Address , I2C_mine I2C_P)  //ID + Address send
{
	uint8_t error=0;
	//data=(data<<1);

    _Bool   SDA=1;
    _Bool   SDA2=1;
    ////////////////////////////////////////////////////////////////////////////////
    for(uint8_t i = 0; i < byte; i++ )
    {
       (ID & 0x80 )  ? SDA_in(I2C_P) :  SDA_out(I2C_P);

        Delay_us( 10 );
       	SCL_in(I2C_P);
       	Delay_us( 10 );
        SCL_out(I2C_P);   				//
        ID <<= 1;
    }
    /////////////////////////////////////////////////////////////////read/ write
     (type ) ? SDA_in(I2C_P) :  SDA_out(I2C_P);  // SDA_in(); //  ??
     SCL_in(I2C_P);  // Delay_us(10);
    /////////////////////////////////////////////////////////////////
//    i2c_stop_cond();
     SCL_out(I2C_P);
     	Delay_us( 10 );  //
       SDA_out(I2C_P);
     	Delay_us( 10 );  //  SDA
     SCL_in(I2C_P);
     	Delay_us( 10 );  //  SCL
         SDA_in(I2C_P);
     	Delay_us( 30 );  //  SDA
 //////////////////////////////////////////////////


    SCL_in(I2C_P);
//    Delay_us( 10 );

    if(SDA = READ_PIN(I2C_PORT,I2C_SDA)!=0)    //////////??
       {
     	  return SDA;  //
       }
      else
      {
    	  SDA2 = i2c_writeByte(Address,byte,I2C_P);
      }

    return SDA;  //
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////working
uint8_t i2c_send_3byte( uint8_t ID, uint8_t byte ,uint8_t type ,uint8_t Config, uint8_t data , I2C_mine I2C_P)  //ID + Address send
{
	uint8_t error=0;
	//data=(data<<1);

    _Bool   SDA=1;
    _Bool   SDA2=1;
    _Bool   SDA3=1;

    ////////////////////////////////////////////////////////////////////////////////
    for(uint8_t i = 0; i < byte; i++ )
    {
       (ID & 0x80 )  ? SDA_in(I2C_P) :  SDA_out(I2C_P);

        Delay_us( 10 );
       	SCL_in(I2C_P);
       	Delay_us( 10 );
        SCL_out(I2C_P);   				//
        ID <<= 1;
    }
    /////////////////////////////////////////////////////////////////read/ write
     (type) ? SDA_in(I2C_P) :  SDA_out(I2C_P);  // SDA_in(); //
     SCL_in(I2C_P);  // Delay_us(10);
    /////////////////////////////////////////////////////////////////
//    i2c_stop_cond();
     SCL_out(I2C_P);
     	Delay_us( 10 );  //
       SDA_out(I2C_P);
     	Delay_us( 10 );  //  SDA
     SCL_in(I2C_P);
     	Delay_us( 10 );  //  SCL
         SDA_in(I2C_P);
     	Delay_us( 30 );  //  SDA
 //////////////////////////////////////////////////


    SCL_in(I2C_P);
//    Delay_us( 10 );

    if(SDA = READ_PIN(I2C_PORT,I2C_SDA)!=0)    //////////??
       {
     	  return SDA;  //
       }
      else
      {
    	  SDA2 = i2c_writeByte(Config,8,I2C_P);
       	  SDA3 = i2c_writeByte(data,8,I2C_P);
    //	  i2c_st_test(I2C_P);
      }

    if( (SDA2 && SDA3) !=0)
    {
     printf("Error_Onsver:%u:%u\n",SDA2,SDA3);
    }
    return SDA;  //
}



//----------------------- �
//------------------------------------
uint8_t i2c_get_byte( uint8_t last_byte ,I2C_mine I2C_P)
{
    uint8_t  i, res = 0;
    uint16_t SDA;
    SDA_in(I2C_P);  //

    for( i = 0; i < 8; i++ )
    {
        res <<= 1;
        SCL_in(I2C_P);  //
        Delay_us( 10 );
        SDA_in(I2C_P);
        SDA = SDA_I;
        if( SDA == 1 )
           res = res |0x01;   //
        SCL_out(I2C_P);       //
        Delay_us( 10 );
    }

    if( last_byte == 0 )
        SDA_out(I2C_P);  //
    else
        SDA_in(I2C_P);   //
                         //
    Delay_us( 10 );
    	SCL_in(I2C_P);
    Delay_us( 10 );     //
    	SCL_out(I2C_P);
    Delay_us( 10 );     //
    	SDA_in(I2C_P);        //
    return res;         //
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------Function-----------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////test
uint8_t i2c_Read_regist_1b_addres(uint8_t ID,uint8_t byte,uint8_t Adrres,I2C_mine I2C_P)  //send ID + address  read data 1 byte
{
    _Bool result = 1;
    i2c_start_cond(I2C_P);
    uint8_t a = i2c_send_2byte(ID,byte,write_i2c,Adrres,I2C_P);
    uint8_t b = i2c_get_byte(0,I2C_P);
    Delay_us( 10 );

    return (b);

}
///////////////////////////////////////////////////////////////////////////////Working +
uint8_t i2c_ID( uint8_t I2C_IDD , I2C_mine I2C_P)  //////////////////////////// send 1 byte => ID TEST
{
    _Bool result = 1;
    i2c_init(I2C_P);
    uint8_t b=0;
    i2c_start(I2C_P);

    for(uint8_t i=0;i<128;i++) //128
    {
    	result = i2c_send_byte(i,8,read_i2c, I2C_P);

            if(result==0)
    	{
            	I2C_IDD = i;
    		b++;
    	}
            Delay_us( 500 ); //250
            Delay_us( 500 ); //250
            Delay_us( 500 ); //250
    }

    return I2C_IDD;
}
////////////////////////////////////////////////////////////////////////////////test
uint8_t i2c_readByte( I2C_mine I2C_P, uint8_t ID )	////////////////////////////////////////send ID read 1byte
{
    _Bool result = 1;
    uint8_t data = 0;

    ID=(ID<<1);
    i2c_start(I2C_P);

    result =  i2c_send_byte( ID, 7 ,read_i2c, I2C_P );
    printf("answer:%u  ",result);

    data = i2c_get_byte( 8 , I2C_P);
    i2c_st_test(I2C_P);

    return data;
}
////////////////////////////////////////////////////////////////////////////////Working +
uint8_t i2c_SendByteConfData( uint8_t ID,uint8_t config ,uint8_t data_w,I2C_mine I2C_P)////Send ID + data_config + data ADC
{

  //  i2c_init(I2C_P);

    _Bool result = 1;
    uint8_t data = 0;

    ID=(ID<<1);
    i2c_start(I2C_P);

    result =  i2c_send_3byte( ID, 7 ,write_i2c, config,data_w, I2C_P );
    printf("answer_config:%u  \n",result);

    //i2c_st_test(I2C_P);

    return data;
}
/*-
extern LCD1602 scr;

void I2C_Scan(LCD1602 *scr )
{
while( i < 128 )
{
    b = HAL_I2C_IsDeviceReady( &hi2c1, ( i << 1 ), 1, 1000 );
    if( b == HAL_OK )
    {
  	  printf( "ID=%.2X\n", i );

    }
    i=i+1;
    if(i==128)
    {
  	  printf( "No i2C\n");

    }
}
}
-*/
////////////////////////////////////////////////////////////////////////////////test
//uint8_t i2c_SendByteConf( uint8_t ID,uint8_t data_W ,I2C_mine I2C_P)          //Send ID + data_config
//{
//
//  //  i2c_init(I2C_P);
//
//    _Bool result = 1;
//    uint8_t data = 0;
//
//    ID=(ID<<1);
//    i2c_start(I2C_P);
//
//    result =  i2c_send_2byte( ID, 7 ,write_i2c, data_W , I2C_P );
//    printf("answer_config:%u  ",result);
//    i2c_st_test(I2C_P);
//
//    return data;
//}


//////////////////////////////////////////////////////////////////////////////// �������
///////////////////////////////////////////////////////////////////////////////
/*uint8_t i2c_SendID_Data( uint8_t devId, uint8_t data, uint8_t byte1,uint8_t byte2 )
{
    _Bool result = 0;
    i2c_init();


    i2c_start_cond();

    result = i2c_send_byte( devId, 8,read_i2c);
    if( result == 1 ) { printf( "NO_answers\n" ); };

    /*	result=i2c_send_byte(data,byte1);  //17
            if(result==1){printf("NO_answers\n");};

            result=i2c_send_byte(data,byte2);  //28
            if(result==1){printf("NO_answers\n");};
    */
/*
    i2c_stop_cond();
    SCL_in();
    Delay_us( 10 );  // ÃƒÂ¯ÃƒÂ°ÃƒÂ¨ÃƒÂ²ÃƒÂ¿ÃƒÂ­ÃƒÂ³ÃƒÂ²ÃƒÂ¼ SCL (ÃƒÂ«ÃƒÂ®ÃƒÂ£.0)
    return result;
}
*/

////////////////////////////////////////////////////////////////////////////////error


#endif /* HAL_I2C_MODULE_ENABLED */


/*
void init_I2C(I2C_mine I2C)
{
	PINS_HIGH(I2C.SCL);
	PINS_HIGH(I2C.SDA);

	PINS_OUT(I2C.SCL);
	PINS_OUT(I2C.SDA);


}
void srart_stop(I2C_mine I2C)
{
	PINS_LOW(I2C.SDA);
	delay_nop( 5 );
	PINS_LOW(I2C.SCL);

 //   delay_nop( 5 );
}


void clk_I2C(I2C_mine I2C)
{
    delay_nop( 10 );
    PINS_HIGH(I2C.SCL);	//SCL_in();
    delay_nop( 10 );
    PINS_LOW(I2C.SCL); // SCL_out();
}



uint8_t I2C_ID_test(I2C_mine I2C, uint8_t data, uint8_t byte,_Bool type)   //type write_i2c= 0  read_i2c= 1 // не работает время много
{
     uint8_t i;
    _Bool   test;
    init_I2C(I2C);
   // delay_nop( 200 );


    srart_stop(I2C);
    ////////////////////////////////////////////////////////////////////////////////
    for( i = 0; i < byte-1; i++ )
    {
        (data  & 0x80 )  ? PINS_HIGH(I2C.SDA) : PINS_LOW(I2C.SDA);  //0x80
        clk_I2C(I2C);		//
        data <<= 1;  											    //
    }
       (type )  ? PINS_HIGH(I2C.SDA) : PINS_LOW(I2C.SDA);  			//write/read
       clk_I2C(I2C);
       PINS_IN(I2C.SDA);

       clk_I2C(I2C);


       clk_I2C(I2C);
       delay_nop( 12 );
   	   PINS_HIGH(I2C.SCL); // SCL_out();


   	 test = READS_PIN(I2C.SDA);


   return test;  										 			  //
}

 *
*/
/*
void I2C_Scan(I2C *scr )
{
    uint16_t b = 0xFF;

    for( uint16_t i = 0; i < 128; i++ )
    {
        b = HAL_I2C_IsDeviceReady( scr->hi2c, ( i << 1 ), 1, 1000 );
        if( b == HAL_OK ) { printf( "ID=%.2X\n", i ); }
    }
    //	HAL_I2C_Mem_Read(scr2->hi2c,i,0,1,0,1,10);
    //	HAL_I2C_Mem_Read(scr2->hi2c,i,0,1,0,1,10);
    HAL_Delay( 5 );

    printf( "ID\n" );
}

*/





//	scr2.hi2c_2= &hi2c2;
//	scr2.DevAddress_2 = 0xAA;   // 0x27  // //LED1
/*
//////////////////////////////////////////////////////////////////I2C CUBE
void sendData_I2C( I2C* scr2, uint8_t* pData )
{
    // *pData |= (1<<2);// ÃƒÂ³ÃƒÂ±ÃƒÂ²ÃƒÂ ÃƒÂ­ÃƒÂ ÃƒÂ¢ÃƒÂ«ÃƒÂ¨ÃƒÂ¢ÃƒÂ ÃƒÂ¥ÃƒÂ¬ ÃƒÂ±ÃƒÂ²ÃƒÂ°ÃƒÂ®ÃƒÂ¡ÃƒÂ¨ÃƒÂ°ÃƒÂ³ÃƒÂ¾ÃƒÂ¹ÃƒÂ¨ÃƒÂ© ÃƒÂ±ÃƒÂ¨ÃƒÂ£ÃƒÂ­ÃƒÂ ÃƒÂ« E ÃƒÂ¢ 1
    while( HAL_I2C_Master_Transmit( scr2->hi2c, scr2->DevAddress_2, pData, 1,
                                    1000 ) != HAL_OK ) {}
    HAL_Delay( 5 );
}

void readdData_I2C( I2C* scr2, uint8_t* pData )
// Read 2 bytes from the temperature register
{
    uint8_t buf[12] = { 0 };
    int16_t val;
    *pData =
        HAL_I2C_Master_Receive( scr2->hi2c, scr2->DevAddress_2, 0, 0, 1000 );
    if( pData != HAL_OK ) {
        strcpy( (char*)buf, "Error Rx\r\n" );
    } else {
        // Combine the bytes
        val = ( (int16_t)buf[0] << 4 ) | ( buf[1] >> 4 );
    }
}


*/
