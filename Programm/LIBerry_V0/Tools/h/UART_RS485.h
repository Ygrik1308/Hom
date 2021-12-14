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
	reeadd	= 0x22,
	writ	= 0x23,
	state	= 0x24,
	sleping	= 0x25,
	test    = 0x26
  }function_485;


  int UART_Reed(uint8_t d2);  
  void UART_Write(uint8_t d1);

  
//  void send__read_UART(uint8_t d, void (*f)() );
//  void send_UART_485();
// int UART_Writ_Reed_255(int err,USART_TypeDef * USARTX);
// void read_write_UART();

  #endif /* LED_H */



  /* C++ style
   .h
  */
  // class Data
  // {
  //   public:
  //     int data[7];
  //     Data() : data { 0, 1, 2, 3, 4, 5, 6 }
  //     {
  //     	 // new
  //     }
  //     ~Data()
  //     {
  //     	 // delete
  //     }
  //     void SendData( int d );
  //     int GetData();
  //};
  //
  //void Data::SendData( int d ){
  //	//
  //}
  //int Data::GetData(){
  //	//
  //}
  ////
