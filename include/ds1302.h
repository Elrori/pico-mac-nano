/*
 * DS1302 Real Time Clock Driver
 * 
 * Support for DS1302 RTC with I2C interface
 * Provides time reading and writing functionality
 *
 * Copyright 2024
 * MIT License
 */

#ifndef DS1302_H
#define DS1302_H

#include <stdint.h>
#include <time.h>

/* DS1302 Register Addresses */
#define DS1302_SECONDS      0x80
#define DS1302_MINUTES      0x82
#define DS1302_HOURS        0x84
#define DS1302_DATE         0x86
#define DS1302_MONTH        0x88
#define DS1302_DAY          0x8A
#define DS1302_YEAR         0x8C
#define DS1302_CONTROL      0x8E
#define DS1302_RAM_START    0xC0

/* DS1302 Control Register Bits */
#define DS1302_CONTROL_WP   0x80  /* Write Protect */
#define DS1302_CONTROL_OUT  0x80  /* Output enable */

/* GPIO Pins for DS1302 */
#define DS1302_CLK_PIN      16    /* I2C Clock */
#define DS1302_DATA_PIN     17    /* I2C Data */
#define DS1302_CE_PIN       18    /* Chip Enable */

/* DS1302 I2C Address */
#define DS1302_I2C_ADDR     0xD0  /* 0x68 */
#define DS1302_I2C_BUS      i2c0

/* Time structure */
typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;      /* 0-99 (20xx assumed) */
    uint8_t weekday;   /* 1-7 */
} ds1302_time_t;

/* Initialize DS1302 RTC */
void ds1302_init(void);

/* Read time from DS1302 */
int ds1302_read_time(ds1302_time_t *time);

/* Write time to DS1302 */
int ds1302_write_time(const ds1302_time_t *time);

/* Get current time as Unix timestamp */
time_t ds1302_get_timestamp(void);

/* Set time from Unix timestamp */
int ds1302_set_timestamp(time_t timestamp);

/* Convert DS1302 time to tm struct */
void ds1302_to_tm(const ds1302_time_t *ds_time, struct tm *tm_time);

/* Convert tm struct to DS1302 time */
void tm_to_ds1302(const struct tm *tm_time, ds1302_time_t *ds_time);

/* BCD encode/decode utilities */
uint8_t bcd_encode(uint8_t value);
uint8_t bcd_decode(uint8_t value);

#endif /* DS1302_H */
