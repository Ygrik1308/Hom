//Function declaration for ADuC832.lib file for Keil tools.
extern char AdcCfg(char);
extern char AdcGo(char, char);
extern int AdcRd(void);
extern char AdcBsy(void);
extern int AdcGet(char);
extern char AdcCal(char);
extern char DacCfg(char);
extern char DacOut(char, int);
extern char PllDly(int);
extern char PllWcd(char);
extern char PllRcd(void);
extern char PwmCfg(char);
extern char PwmW16(char,int);
extern char PwmW8(char,char,char);
extern char TicCfg(char);
extern char TicHr(void);
extern char TicMin(void);
extern char TicSec(void);
extern char TicHth(void);
extern char TicVal(char,char);
extern char TicGo(char,char,char,char);
extern char UrtCfg(char, unsigned int);
extern char UrtBsy(void);

//Variable declaration for ADuC832.lib file.
//char datar	cUrtVar;

//Declaration End====================================================Declaration End


/*REV.  0.1    11th February 2002
  ADuC832  Apps, Analog Devices Inc.*/

/*  BYTE Register  */
#define   P0        = 0x80;
#define   SP        = 0x81;
#define   DPL       = 0x82;
#define   DPH       = 0x83;
#define   DPP       = 0x84;
#define   PCON      = 0x87;
#define   TCON      = 0x88;
#define   TMOD      = 0x89;
#define   TL0       = 0x8A;
#define   TL1       = 0x8B;
#define   TH0       = 0x8C;
#define   TH1       = 0x8D;
#define   P1        = 0x90;
#define   SCON      = 0x98;
#define   SBUF      = 0x99;
#define   T3FD      = 0x9D;
#define   T3CON     = 0x9E;
#define   P2        = 0xA0;
#define   TIMECON   = 0xA1;
#define   HTHSEC    = 0xA2;
#define   SEC       = 0xA3;
#define   MIN       = 0xA4;
#define   HOUR      = 0xA5;
#define   INTVAL    = 0xA6;
#define   DPCON     = 0xA7;
#define   IE        = 0xA8;
#define   IEIP2     = 0xA9;
#define   PWMCON    = 0xAE;
#define   CFG831    = 0xAF;
#define   P3        = 0xB0;
#define   PWM0L     = 0xB1;
#define   PWM0H     = 0xB2;
#define   PWM1L     = 0xB3;
#define   PWM1H     = 0xB4;
#define   SPH       = 0xB7;
#define   IP        = 0xB8;
#define   ECON      = 0xB9;
#define   EDATA1    = 0xBC;
#define   EDATA2    = 0xBD;
#define   EDATA3    = 0xBE;
#define   EDATA4    = 0xBF;
#define   WDCON     = 0xC0;
#define   CHIPID    = 0xC2;
#define   EADRL     = 0xC6;
#define   EADRH     = 0xC7;
#define   T2CON     = 0xC8;
#define   RCAP2L    = 0xCA;
#define   RCAP2H    = 0xCB;
#define   TL2       = 0xCC;
#define   TH2       = 0xCD;
#define   PSW       = 0xD0;
#define   DMAL      = 0xD2;
#define   DMAH      = 0xD3;
#define   DMAP      = 0xD4;
#define   PLLCON    = 0xD7;
#define   ADCCON2   = 0xD8;
#define   ADCDATAL  = 0xD9;
#define   ADCDATAH  = 0xDA;
#define   PSMCON    = 0xDF;
#define   ACC       = 0xE0;
#define   I2CCON    = 0xE8;
#define   DCON      = 0xE8;
#define   ADCCON1   = 0xEF;
#define   B         = 0xF0;
#define   ADCOFSL   = 0xF1;
#define   ADCOFSH   = 0xF2;
#define   ADCGAINL  = 0xF3;
#define   ADCGAINH  = 0xF4;
#define   ADCCON3   = 0xF5;
#define   SPIDAT    = 0xF7;
#define   SPICON    = 0xF8;
#define   DAC0L     = 0xF9;
#define   DAC0H     = 0xFA;
#define   DAC1L     = 0xFB;
#define   DAC1H     = 0xFC;
#define   DACCON    = 0xFD;

/* BIT Register..... */
/* TCON */
#define  TF1       = 0x8F;
#define  TR1       = 0x8E;
#define  TF0       = 0x8D;
#define  TR0       = 0x8C;
#define  IE1       = 0x8B;
#define  IT1       = 0x8A;
#define  IE0       = 0x89;
#define  IT0       = 0x88;
/* P1 */
#define  T2EX      = 0x91;
#define  T2        = 0x90;
/* SCON */
#define  SM0       = 0x9F;
#define  SM1       = 0x9E;
#define  SM2       = 0x9D;
#define  REN       = 0x9C;
#define  TB8       = 0x9B;
#define  RB8       = 0x9A;
#define  TI        = 0x99;
#define  RI        = 0x98;
/* IE */
#define  EA        = 0xAF;
#define  EADC      = 0xAE;
#define  ET2       = 0xAD;
#define  ES        = 0xAC;
#define  ET1       = 0xAB;
#define  EX1       = 0xAA;
#define  ET0       = 0xA9;
#define  EX0       = 0xA8;
/* P3 */
#define  RD        = 0xB7;
#define  WR        = 0xB6;
#define  T1        = 0xB5;
#define  T0        = 0xB4;
#define  INT1      = 0xB3;
#define  INT0      = 0xB2;
#define  TXD       = 0xB1;
#define  RXD       = 0xB0;
/* IP */
#define  PSI       = 0xBF;
#define  PADC      = 0xBE;
#define  PT2       = 0xBD;
#define  PS        = 0xBC;
#define  PT1       = 0xBB;
#define  PX1       = 0xBA;
#define  PT0       = 0xB9;
#define  PX0       = 0xB8;
/* WDCON */
#define  PRE3      = 0xC7;
#define  PRE2      = 0xC6;
#define  PRE1      = 0xC5;
#define  PRE0      = 0xC4;
#define  WDIR      = 0xC3;
#define  WDS       = 0xC2;
#define  WDE       = 0xC1;
#define  WDWR      = 0xC0;
/* T2CON */
#define  TF2       = 0xCF;
#define  EXF2      = 0xCE;
#define  RCLK      = 0xCD;
#define  TCLK      = 0xCC;
#define  EXEN2     = 0xCB;
#define  TR2       = 0xCA;
#define  CNT2      = 0xC9;
#define  CAP2      = 0xC8;
/* PSW */
#define  CY        = 0xD7;
#define  AC        = 0xD6;
#define  F0        = 0xD5;
#define  RS1       = 0xD4;
#define  RS0       = 0xD3;
#define  OV        = 0xD2;
#define  F1        = 0xD1;
#define  P         = 0xD0;
/* ADCCON2 */
#define  ADCI      = 0xDF;
#define  DMA       = 0xDE;
#define  CCONV     = 0xDD;
#define  SCONV     = 0xDC;
#define  CS3       = 0xDB;
#define  CS2       = 0xDA;
#define  CS1       = 0xD9;
#define  CS0       = 0xD8;
/*  I2CCON  */
#define  MDO       = I2CCON^7;
#define  MDE       = I2CCON^6;
#define  MCO       = I2CCON^5;
#define  MDI       = I2CCON^4;
#define  I2CM      = I2CCON^3;
#define  I2CRS     = I2CCON^2;
#define  I2CTX     = I2CCON^1;
#define  I2CI      = I2CCON^0;
/*  DCON  */
#define  D1        = DCON^7;
#define  D1EN      = DCON^6;
#define  D0        = DCON^5;
#define  D0EN      = DCON^3;
/* SPICON */
#define  ISPI      = 0xFF;
#define  WCOL      = 0xFE;
#define  SPE       = 0xFD;
#define  SPIM      = 0xFC;
#define  CPOL      = 0xFB;
#define  CPHA      = 0xFA;
#define  SPR1      = 0xF9;
#define  SPR0      = 0xF8;
