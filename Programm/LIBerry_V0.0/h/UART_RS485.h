
 #ifndef UART_485_H
 #define UART_485_H


  typedef struct
  {
    uint8_t ID_address;
    uint8_t function_uart;
	int data_send[7];  //  doubleuint16_t timing;  //
    uint16_t CRC_UART;
    uint16_t time;
   }Uart_485;

	typedef enum
  {
	request = 0x21,
	readd	= 0x22,
	writ	= 0x23,
	state	= 0x24,
	sleping	= 0x25,
	test    = 0x26
  }function_485;

/* C++ style
 .h
 class Data {
   public:
     int data[7];
     Data() : data { 0, 1, 2, 3, 4, 5, 6 } {
     	 // new
     }
     ~Data(){
     	 // delete
     }
     void SendData( int d );
     int GetData();
};
.cpp
void Data::SendData( int d ){
	//
}
int Data::GetData(){
	//
}
 */
  void send__read_UART(uint8_t d, void (*f)() );
  void send_UART_485();
//  void send_UART_485(Uart_485 *huart2); //data -> comp
//  void read_UART_485(Uart_485 *huart2); //data -> comp
  int UART_Writ_Reed_255(int err); 
  int UART_Reed(uint8_t d2);  
  
  void read_write_UART();
  uint8_t read_UART(uint8_t d);
  void UART_Write(uint16_t d1);
  uint16_t block_erase(uint16_t adress_3,uint16_t adress_4,uint16_t adress_5);

  #endif /* LED_H */
