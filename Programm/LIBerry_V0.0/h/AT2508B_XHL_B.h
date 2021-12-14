/*
 * AT2508B-XHL-B.h
 *
 *  Created on: 13 рту. 2020 у.
 *      Author: User356
 */

#ifndef H_AT2508B_XHL_B_H_
#define H_AT2508B_XHL_B_H_

#define sck GPIOA,5
#define SI GPIOC,5
#define SO GPIOA,6
#define CS GPIOA,4
#define WP GPIOC, 4
#define HOLD GPIOA, 7


uint8_t read(uint16_t addr);
uint8_t eeprom_read ();
void eeprom_write (uint8_t dat, uint16_t addr);
void eeprom_test (uint8_t dat);
void eeprom_tst();



#endif /* H_AT2508B_XHL_B_H_ */
