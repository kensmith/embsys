/*
 * MODULE:
 *
 *  lpc2378.h
 * 
 * DESCRIPTION:
 *
 *  LPC2378 standard definitions file
 * 
 * OS:
 *
 *  N/A
 *
 * PLATFORM:
 *
 *  Olimex LPC2378-STK
 *
 * ORIGINATOR:
 *
 *  Andrew N. Sloss
 *
 * HISTORY:
 *
 *  - started creating the header file  
 *
 * NOTES:
 *
 *  n/a
 *
 */
 
#ifndef LPC2378_STANDARD_DEFINITIONS
#define LPC2378_STANDARD_DEFINITIONS

/*
 * STANDARD DEFINITIONS 
 */

#define BIT(a)  (1<<a)

#define VOLATILE32(addr) (*(volatile uint32_t *)(addr)) 
#define VOLATILE16(addr) (*(volatile uint16_t *)(addr)) 
#define VOLATILE8(addr)  (*(volatile uint8_t *)(addr))  

/*
 * REGISTER MAPPINGS
 */ 

/* 
 * Fast GPIO Registers 
 */

#define FIO0DIR        0x3FFFC000
#define FIO0MASK       0x3FFFC010
#define FIO0PIN        0x3FFFC014
#define FIO0SET        0x3FFFC018
#define FIO0CLR        0x3FFFC01C

/*
 * UART0
 */ 

#define U0RBR          0xE000C000
#define U0THR          0xE000C000
#define U0DLL          0xE000C000
#define U0DLM          0xE000C004
#define U0IER          0xE000C004
#define U0IIR          0xE000C008
#define U0FCR          0xE000C008
#define U0LCR          0xE000C00C
#define U0LSR          0xE000C014
#define U0SCR          0xE000C01C
#define U0ACR          0xE000C020
#define U0ICR          0xE000C024
#define U0FDR          0xE000C028
#define U0TER          0xE000C030

#define PINSEL0        0xE002C000
#define PINSEL1        0xE002C004
#define PINSEL2        0xE002C008
#define PINSEL3        0xE002C00C
#define PINSEL4        0xE002C010
#define PINSEL5        0xE002C014
#define PINSEL6        0xE002C018
#define PINSEL7        0xE002C01C
#define PINSEL8        0xE002C020
#define PINSEL9        0xE002C024
#define PINSEL10       0xE002C028
#define PINSEL10_MASK  0x00000008	/* mask reserved bits */

/* PIN SELECT - Chapter 8 of the LPC2378 User Manual */
#define PINMODE0       0xE002C040
#define PINMODE1       0xE002C044
#define PINMODE2       0xE002C048
#define PINMODE3       0xE002C04C
#define PINMODE4       0xE002C050
#define PINMODE5       0xE002C054
#define PINMODE6       0xE002C058
#define PINMODE7       0xE002C05C
#define PINMODE8       0xE002C060
#define PINMODE9       0xE002C064

#define MAMCR          0xE01FC000
#define MAMTIM         0xE01FC004
#define MEMMAP         0xE01FC040
#define PLLCON         0xE01FC080
#define PLLCFG         0xE01FC084
#define PLLSTAT        0xE01FC088
#define PLLFEED        0xE01FC08C

#define PCON           0xE01FC0C0
#define PCONP          0xE01FC0C4
	
#define SCS            0xE01FC1A0	
#define CCLKCFG        0xE01FC104
#define USBCLKCFG      0xE01FC108
#define CLKSRCSEL      0xE01FC10C
#define PCLKSEL0       0xE01FC1A8
#define PCLKSEL1       0xE01FC1AC

/*
 * Timer0
 */ 

#define T0IR            0xE0004000
#define T0TCR           0xE0004004
#define T0TC            0xE0004008
#define T0PR            0xE000400C
#define T0PC            0xE0004010
#define T0MCR           0xE0004014
#define T0MR0           0xE0004018
#define T0MR1           0xE000401C
#define T0MR2           0xE0004020
#define T0MR3           0xE0004024
#define T0CCR           0xE0004028
#define T0CR0           0xE000402C
#define T0CR1           0xE0004030
#define T0CR2           0xE0004034
#define T0CR3           0xE0004038
#define T0EMR           0xE000403C
#define T0CTCR          0xE0004070


/*
 * REGISTER DEFINITIONS
 */ 


/* 
 * MEMMAP 
 */

#define BOOTLOADERMODE     0x0               
#define USERFLASHMODE      0x1           
#define USERRAMMODE        0x2   
#define EXTERNALMEMORYMODE 0x3                           
#define MAMCR_OFF          0
#define MAMCR_PART         1
#define MAMCR_FULL         2
#define MAMTIM_CYCLES      (((CCLK)+19999999)/20000000)


#define CLKSRC_INT_RC      (0x00)
#define CLKSRC_MAIN_OSC    (0x01)
#define CLKSRC_MIN_RTC     (0x02)

#define SCS_GPIOM          (1<<0)
#define SCS_EMC_RST_DIS    (1<<1)
#define SCS_MCIPWR         (1<<3)
#define SCS_OSCRANGE       (1<<4)
#define SCS_OSCEN          (1<<5)
#define SCS_OSCSTAT        (1<<6)

#define FCCO               (FOSC*PLL_MUL*2/PLL_DIV) 
#define PLLCON_PLLE        (1<<0)         
#define PLLCON_PLLC        (1<<1)  


#define LED1_SET           FIO0SET
#define LED1_DIR           FIO0DIR
#define LED1_CLR           FIO0CLR
#define LED1_PIN           FIO0PIN
#define LED1_BIT           BIT(21)                                         

#define U0_TX_PINSEL_REG   PINSEL0
#define U0_TX_PINSEL       (1UL<<4)              
#define U0_TX_PINMASK      (3UL<<4)              
#define U0_RX_PINSEL_REG   PINSEL0
#define U0_RX_PINSEL       (1UL<<6)              
#define U0_RX_PINMASK      (3UL<<6)              

#define PDIV_1             0x1
#define PDIV_2             0x2
#define PDIV_4             0x0
#define PDIV_6             0x3
#define PDIV_8             0x3

#define SET_PCLK(per,div) ((div) << (per))

#define PCLK_WDT           0
#define PCLK_TIMER0        2
#define PCLK_TIMER1        4
#define PCLK_UART0         6
#define PCLK_UART1         8
#define PCLK_PWM1          12
#define PCLK_I2C0          14
#define PCLK_SPI           16
#define PCLK_RTC           18         
#define PCLK_SSP1          20
#define PCLK_DAC           22
#define PCLK_ADC           24
#define PCLK_CAN1          26
#define PCLK_CAN2          28
#define PCLK_ACF           30

#define PCLK_BAT_RAM       0
#define PCLK_GPIO          2
#define PCLK_PCB           4
#define PCLK_I2C1          6
#define PCLK_SSP0          10
#define PCLK_TIMER2        12
#define PCLK_TIMER3        14
#define PCLK_UART2         16
#define PCLK_UART3         18
#define PCLK_I2C2          20
#define PCLK_I2S           22
#define PCLK_MCI           24
#define PCLK_SYSCON        28

#define PLLCFG_N           1
#define PLLCFG_M           12
#define PLLCFG_VALUE       (((PLLCFG_N - 1) << 16) + ((PLLCFG_M - 1) << 0))
#define MAMTIM_3_CLK       3
#define PLLSTAT_PLOCK      (1<<26)
#define PLLSTAT_PLLE       (1<<24)
#define PLLSTAT_PLLC       (1<<25)

/*
 * OLD CODE:
 * 
 * #define PINSEL0_TX0        PINSEL_MASK (PINSEL_FUNC_ALT_1, 4)
 * #define PINSEL0_RX0        PINSEL_MASK (PINSEL_FUNC_ALT_1, 6)
 * #define PINSEL0_TX1        PINSEL_MASK (PINSEL_FUNC_ALT_1, 30)
 * #define PINSEL1_RX1        PINSEL_MASK (PINSEL_FUNC_ALT_1, 0)
 *
 */

#define ULCR_DLAB_ENABLE   (1<<7)   
#define ULSR_THRE          (1<<5)   
#define UIER_THRE          (1<<1)
#define UART_BAUD(baud)    (uint16_t)((PCLK/((baud)*16.0))+0.5)
#define HOST_BAUD_U0       (38400)
#define UART_8N1           (uint8_t)(3<<0)        
#define UART_FIFO_OFF      (0x00)       
#define PUTC(c)              while(!(VOLATILE32(U0LSR) & ULSR_THRE)) continue; \
	                       VOLATILE32(U0THR) = (uint8_t) c

#define FOSC               (12000000)          
#define PLL_MUL            (12)              
#define PLL_DIV            (1)         	     
#define CCLK_DIV           (6)        		 
#define CCLK               (FCCO/CCLK_DIV)   
#define CCLKCFG_VALUE      (CCLK_DIV-1)
#define PBSD               1                 
#define PCLK               (CCLK / PBSD)     

#endif
