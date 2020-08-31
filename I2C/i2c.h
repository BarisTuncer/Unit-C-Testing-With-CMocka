#ifndef __I2C_H_
#define __I2C_H_

#include <stdint.h>

#define I2C_SLAVE_FORCE 0x0706

int open_i2c(uint8_t i2c_addr);
int do_something();

#endif /* __I2C_H_ */
