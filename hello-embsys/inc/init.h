#ifndef __INIT_H__
#define __INIT_H__

void handlerDummy(void);
void initHardware(void);
void initUART0(uint16_t baud, uint8_t mode, uint8_t fmode);
void pinConfigurator(void);



#endif /* __INIT_H__ */
