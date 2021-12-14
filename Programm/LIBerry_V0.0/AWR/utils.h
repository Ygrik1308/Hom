#ifndef INCLUDE_UTILS_H
#define INCLUDE_UTILS_H

#if defined (__AVR_ATmega2560__)
#define GPIOA    _SFR_IO8(0X01)     //DDR
#define GPIOB    _SFR_IO8(0x04)     //DDR
#define GPIOC    _SFR_IO8(0x07)     //DDR
#define GPIOD    _SFR_IO8(0x0A)     //DDR
#define GPIOD    _SFR_IO8(0x0A)     //DDR
#define GPIOE    _SFR_IO8(0x0D)     //DDR
#define GPIOF    _SFR_IO8(0x10)     //DDR
#define GPIOG    _SFR_IO8(0x13)     //DDR
#define GPIOK    _SFR_MEM8(0x107)   //DDR
#define GPIOL    _SFR_MEM8(0x10A)   //DDR
#define GPIOJ    _SFR_MEM8(0x104)   //DDR
#define GPIOH    _SFR_MEM8(0x101)   //DDR
#endif


#if defined (__AVR_ATmega1281__)
#define GPIOA    _SFR_IO8(0X01)     //DDR   _SFR_IO8(0X01)
#define GPIOB    _SFR_IO8(0x04)     //DDR   _SFR_IO8(0x04) 
#define GPIOC    _SFR_IO8(0x07)     //DDR   _SFR_IO8(0x07)
#define GPIOD    _SFR_IO8(0x0A)     //DDR   _SFR_IO8(0x0A)
#define GPIOE    _SFR_IO8(0x0D)     //DDR   _SFR_IO8(0x0D) E
#define GPIOF    _SFR_IO8(0x10)     //DDR   _SFR_IO8(0x10)
#define GPIOG    _SFR_IO8(0x13)     //DDR   _SFR_IO8(0x13)
#endif


bool READ_PIN(uint8_t volatile  *pReg,uint16_t Pin)  // 
{
    bool dat = *(pReg-1) & (1<<Pin);
    return dat;
}


//#define PINN_HIGH( register, bit ) register |= (1<<bit)
//#define PINN_LOW( register, bit ) register &= ~(1<<bit)


//////////////////////////////////////////////////////////////////////////PIN
void PIN_HIGH(uint8_t volatile  *pReg,uint8_t PIN) //volatile -
{
  //    *(pReg-1)&= ~(1<<PIN);  //                
      *(pReg+1)|=(1<<PIN) ;
      
  // *((pReg-1))&= ~~(1<<PIN);  //
}

void PIN_LOW(uint8_t volatile  *pReg,uint8_t PIN) //volatile  +
{
    //  *(pReg-1)&= ~(0<<PIN);  //                
      *(pReg+1)&= ~(1<<PIN) ;
}

void PIN_IN(uint8_t volatile  *pReg,uint8_t PIN) //volatile  +
{
    *(pReg) &= ~(1<<PIN);  //
}

void PIN_OUT(uint8_t volatile  *pReg,uint8_t PIN) //volatile  +
{
    *(pReg) |= (1<<PIN);  //
}

//////////////////////////////////////////////////////////////////////////PORT
void PORT_OUT(uint8_t volatile  *pReg) //volatile 
{
    *(pReg) = 0xFF;  //
}

void PORT_IN(uint8_t volatile  *pReg) //volatile
{
    *(pReg) = 0x00;  //
}

void PORT_HIGH(uint8_t volatile  *pReg) //volatile
{
    *(pReg-1) = 0xFF;  //
}
void PORT_LOW(uint8_t volatile  *pReg) //volatile
{
    *(pReg-1) = 0x00;  //
}

void PORT_DATA(uint8_t volatile  *pReg,uint8_t data) //volatile 
{
    *(pReg) = data;  //
}

void fail_signal(uint8_t volatile  *pReg,uint8_t PIN)
{
          PIN_HIGH (&(*(pReg)),PIN); //--  
         _delay_ms( 300 );

         PIN_LOW  (&(*(pReg)),PIN); //--
         _delay_ms( 300 );
}


void delay_nop(int Delay)
{
	for( uint8_t i=0; i<Delay; ++i) asm ( "nop" );
}


// 	GPIO_TypeDef *A;
// 	uint16_t      P;
typedef struct
{
    uint8_t volatile *A;      /*!< GPIO port mode register,                 Address offset: 0x00      // DDR*/
    uint16_t P;               /*!< GPIO port output speed register,         Address offset: 0x08    */
} GPIO;
/////////////////////////////////////////////////////////////////////////////////////////////////////

void PINS_HIGH(GPIO Port) //volatile -
{
//    *((Port.A)-1)&= ~(1<<Port.P);  //
    *((Port.A)+1)|=  (1<<Port.P) ;
    
    // *((pReg-1))&= ~~(1<<PIN);  //
}

void PINS_LOW(GPIO Port) //volatile  +
{
    *((Port.A)+1)&= ~(1<<Port.P);  //0
//    *((Port.A)-1)|=  (0<<Port.P) ;
}
//////////////////////////////////////////////////////////////////////////
void PINS_IN(GPIO Port) //volatile  +
{
    *(Port.A) &= ~(1<<Port.P);  //
}

void PINS_OUT(GPIO Port) //volatile  +
{
    *(Port.A) |= (1<<Port.P);  //
}
//////////////////////////////////////////////////////////////////////////
void PINS_data_clok (GPIO *Port,GPIO CL,uint32_t ddata,uint16_t bytes)  // set addres
{
    //GPIO send[]={};
    //bytes=bytes+1;

    for(uint16_t i = 0; i < bytes; ++i)
    {
        PINS_HIGH(CL);

        (ddata  & 1 )  ? PINS_HIGH(Port[i]) : PINS_LOW(Port[i]);
        ddata >>= 1;
        delay_nop(1);

        PINS_LOW(CL);

    }
}

void PINS_data(GPIO *Port,uint32_t ddata,uint16_t bytes)  // set addres
{
    for(uint16_t i = 0; i < bytes; ++i)
    {
       (ddata  & 1 )  ? PINS_HIGH(Port[i]) : PINS_LOW(Port[i]);
        ddata >>= 1;
        delay_nop(1);
    }
}



uint16_t reverse(uint32_t data,uint16_t byte)  //
{
	uint16_t reversed_data=0x0000;
   for(uint8_t i=0; i<byte; i++)
   {
	   reversed_data <<= 1;
	   reversed_data |= data & 1;
	   data >>= 1;
    }
return reversed_data;
}

 // PINS_data_clok(addres,CLK,row,byt_Address); //put row to bank






/*
#define PINA     _SFR_IO8(0X00) //PIN
#define PORTA    _SFR_IO8(0X02) //PORT
#define PINB     _SFR_IO8(0X03) //PIN
#define PORTB    _SFR_IO8(0x05) //PORT

*/
/*/
#define GPIOA_BASE          (_SFR_IO8(0x2A)
#define GPIOB_BASE          (_SFR_IO8(0x04))
#define GPIOC_BASE          (_SFR_IO8(0x07))
#define GPIOD_BASE          (_SFR_IO8(0x0A))
#define GPIOE_BASE          (_SFR_IO8(0x0D))
#define GPIOF_BASE          (_SFR_IO8(0x10))
#define GPIOG_BASE          (_SFR_IO8(0x13))
#define GPIOH_BASE          (_SFR_MEM8(0x101))
#define GPIOI_BASE          (_SFR_MEM8(0x104))


#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH               ((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI               ((GPIO_TypeDef *) GPIOI_BASE)

*/
/*
template <typename T>
constexpr T reverse( T data ) 
{
    T reversed_data = 0x00;
    for( uint8_t i=0; i<sizeof(T)*8; ++i )
    {
        reversed_data <<= 1;
        reversed_data |= data & 1;
        data >>= 1;
    }
    return reversed_data;
}
*/
/*
////////////////////////////////////////////////////////////////////////// set_bit PORT, bit=1 !!
template <typename D, typename T>                      \
constexpr void PIN_OUT( D& ddr, T bit )              \
{                                                      \
     port |= ( 1 << bit );                              \
}                                                \

////////////////////////////////////////////////////////////////////////// set_bit PORT, bit=1 !!
template <typename P, typename T>                      \ 
constexpr void PIN_HIGH( P& port, T bit )              \
{                                                      \                                           
    port |= ( 1 << bit );                              \
}                                                      \   


//////////////////////////////////////////////////////////////////////////  clear_bit PORT, bit=0 !!
template <typename P, typename T>                     \
constexpr void PIN_LOW( P& port, T bit )              \
{                                                     \
    port &= ~( 1 << bit );                            \
}                                                     \
*/
//////////////////////////////////////////////////////////////////////////toggle_bits edited
template <typename P, typename T>                       \
constexpr void toggle_bits( P& port, T bit )            \
{                                                       \
    port ^= ( 1 << bit );                               \
}                                                       \
//////////////////////////////////////////////////////////////////////////&&&
//template <typename P, typename T>                       

//#define pin_OUT( register, ...)                          
//#define set_bits(port,t,...)                            \          
//{                                                        \
 //   port |=  (1 << t);
//
//}                                                        \
//////////////////////////////////////////////////////////////////////////SET_BITS  DDR=1-> OUT
/*
#define PINS_OUT( register, ...)                        \  
{                                                       \
    uint8_t mask_bits[] = { __VA_ARGS__ };              \
    uint8_t mask = 0x00;                                \
    for( auto& bit : mask_bits ) mask |= (1<<bit);      \
    register |= mask;                                   \
}
//////////////////////////////////////////////////////////////////////////CLEAR_BITS  DDR=0-> IN
#define PINS_IN( register, ... )                        \
{                                                       \
    uint8_t mask_bits[] = { __VA_ARGS__ };              \
    uint8_t mask = 0x00;                                \
    for( auto& bit : mask_bits ) mask |= (1<<bit);      \
    register &= ~mask;                                  \
}

*/




template <typename P, typename T>
class Pin 
{
    public:
    P* const t_port;
    const T  pin;
    Pin( P& port, T pin_num ) : t_port( &port ), pin( pin_num ) {}
    void set() { set_bit( *t_port, pin ); }                              //set_bit
    void clear() { clear_bit( *t_port, pin ); }
    void toggle() { toggle_bit( *t_port, pin ); }
    bool is_low() const { return ( ( *( t_port - 2 ) ) & ( 1 << pin ) ) == 0; }
    bool is_high() const { return ( ( *( t_port - 2 ) ) & ( 1 << pin ) ) != 0; }
    operator T() { return pin; }
};

auto set    = []( auto& p ) { p.set(); };

//#define READ( pin_name )    ( ( ( *( pin_name.t_port - 2 ) ) & ( 1 << pin_name.pin ) ) >> pin_name.pin ) 

/*    
            
*/                                             \ 
#endif