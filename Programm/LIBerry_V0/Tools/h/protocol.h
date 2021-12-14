/*
 * protocol.h
 *
 *  Created on: 11 дек. 2020 г.
 *      Author: HP
 */

#ifndef H_PROTOCOL_H_
#define H_PROTOCOL_H_
/*
//////////////////////////////////////////////////////////protocol read
	 //-1// 03h - read register      - Team read
	 ///////////////////////////////////
  	  	  //-2// 01h - read_programming status  //-3// 00 - no programming 01 - programming
    	  //-2// 02h - read_version program	    //-3// 00 - version 1....n
   	  	  //-2// 03h - read_test status	connect
  	  	  	  //-3// 00 - error_off
  	  	  	  //-3// 01 - error send
  	  	  	  //-3// 02 - error write
  	  	  	  //-3// 03 - error controller
  	  	  //-2// 03h - data_test
  	  	  	  //3-//  data
  	  	  	  //4-//  month
  	  	  	  //5-//  year
  	  	  //-2// 04h - ID_controller - 00 18h
  	  	  	  //-3//  00- namber product
     	 	  //-3//  18 - stm32f103vet
     	 	  //-3//  14 - stm32f407vet
     	 	  //-3//  1D - stm32 nucleo
   	  	 //-2//   05  - device_test_prog
  	  	  	  //-3//  00- no test device program
  	          //-3//  01- device program fleche
  	  	  	  //-3//  02- ADC
         	  //-3//  03- DAC
  	     //-2//   06  - number_test_device
	  	  	  //-3//  00...n
 /////////////////////////////////////////////////////////protocol write
	 //-1// 08h - write   command


 	 //-2// 01h - command help
	 //-2// 02h - command test controller.Availability
	 //-2// 03h - command test device. Availability

     //-2// 14h - command programming
     //-2// 15h - command list device programming

  	 //-2// 04h - command test #1
	 //-2// 05h - command test #2
	 //-2// 06h - command test #3
	 //-2// 07h - command test #4
	 //-2// 08h - command test #5

	 //-2// 0Dh - data request test. data send, data read
	 //-2// 0Ah - Log On
	 //-2// 0Bh - Log OFF

	 //-2// 0Dh - OFF Command
//////////////////////////////////////////////////////////
*/
///////////////////////////////////////////////////////////////////////
 typedef enum  //read-> controller
 {
/////////////////////////0 bit
readd	= 0x03,
	/////1 bit
	received_readd          = 0x1A,
	no_received_writt       = 0x2A,
	/////2 bit
	read_programming  		= 0x01,
	read_version  	   		= 0x02,
	read_test          		= 0x03,
		/////////////////////////3 read_test
		error_off  			= 0x00,
		error_send			= 0x01,
		error_write         = 0x02,
		error_controller    = 0x03,
		/////////////////////////3 read_test
	read_data_test     		= 0x02,
		/////////////////////////3,4,5 read_data_test
		test_data           = 00, //0...31  0...1Fh
		test_month			= 00, //0...12  0...Ch
		test_year 			= 00, //20      14h
		/////////////////////////3,4,5 read_data_test
	read_ID_controller 		= 0x04,
		/////////////////////////3 ID_controller
		ID_stm32f103vet     = 0x18,
		ID_stm32f407vet     = 0x14,
		ID_stm32_nucleo     = 0x1D,
		/////////////////////////3 ID_controller
	read_device_test_prog   = 0x05,
		/////////////////////////3 device_test_prog
		no_device           = 0x00,
		device_flash        = 0x01,
		device_ADC          = 0x02,
		device_DAC          = 0x03,
		/////////////////////////3 device_test_prog
	read_number_test_device = 0x06,
	    /////////////////////////3 number_test_device
		number_device       = 0x00,   //  00...n
		/////////////////////////3 number_test_device
    read_number_list_device = 0x07,
		/////////////////////////3 device_test_prog
		quantity_device     = 0x00,   //  00...n
}f_read;

typedef enum   // write -> conntroller
{
/////////////////////////0 bit
writt	= 0x08,
    /////1 bit
	received_writt           = 0x1B,  // status command read
	no_received_readd        = 0x2B,  // status command read
	////2 bit
	write_help          	 = 0x01,  // issue a list of commands
	write_test_controlle     = 0x02,
	write_test_device        = 0x03,
	write_programming        = 0x14,  // programming controller
	write_device_programming = 0x15,  // list device programming
////////////////////////////////////////
	write_test1              = 0x04,
	write_test2              = 0x05,
	write_test3              = 0x06,
	write_test4              = 0x07,
	write_test5              = 0x08,
	write_request            = 0x0D,  //data send, data read
	write_log_OFF            = 0x0A,
	write_log_ON 			 = 0x0B,
	write_OFF 				 = 0x0D,

}f_write;

typedef struct
{
uint8_t data[10];
}protocol_mas;

typedef struct
{
	uint8_t WR;            // read / write
	uint8_t status;        // status read / write
	uint8_t comand;	       // command read/ write
	uint8_t r_3;	       // command read
	uint8_t r_4;	       // command read
	uint8_t r_5;	 	   // command read
	uint8_t CRC_Cmd;       // rd_0+rd_1+rd_2+r_3
	uint8_t byte;          // 8..64 byte send
	uint8_t CRC_data;      // rd_0+rd_1+rd_2+r_
	uint8_t mas_data[10];
//	protocol_mas data;
}protocol;


extern  protocol pt;
//struct
#endif /* H_PROTOCOL_H_ */
