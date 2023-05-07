/*
 * Copyright (c) 2019-2020, redoc
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-05     qq           the first version
 */
 
#ifndef __ERROR_ID_H
#define __ERROR_ID_H

/* Error code id */
typedef enum
{
    ERROR_ID_NONE  = 0x00000000,
    /*    Error level one     */
	ERROR_ID_LVL_1_1,
    ERROR_ID_LVL_1_2,                       
    ERROR_ID_LVL_1_3,

    /*    Error level two     */
	ERROR_ID_LVL_2_1 = 0x50,
    ERROR_ID_LVL_2_2,                       
    ERROR_ID_LVL_2_3,

    /*    Error level three     */
	ERROR_ID_LVL_3_1 = 0xA0,
    ERROR_ID_LVL_3_2,                       
    ERROR_ID_LVL_3_3,
	
    /*    Error level     */
    ERROR_ID_LVL_1 = 0xFD,
    ERROR_ID_LVL_2,
    ERROR_ID_LVL_3,
}error_id_t;


/* Error list */
#define ERROR_BUF       \
{                       \
    ERROR_ID_LVL_1_1,   \
    ERROR_ID_LVL_1_2,   \
    ERROR_ID_LVL_1_3,   \
    ERROR_ID_LVL_2_1,   \
    ERROR_ID_LVL_2_2,   \
    ERROR_ID_LVL_2_3,   \
    ERROR_ID_LVL_3_1,   \
    ERROR_ID_LVL_3_2,   \
    ERROR_ID_LVL_3_3,   \
    ERROR_ID_LVL_1,     \
    ERROR_ID_LVL_2,     \
    ERROR_ID_LVL_3,     \
};

/* Error list of one */
#define ERROR_BUF_LVL_1     \
{                           \
    ERROR_ID_LVL_1_1,       \
    ERROR_ID_LVL_1_2,       \
    ERROR_ID_LVL_1_3,       \
    ERROR_ID_LVL_1,         \
};

/* Error list of two */
#define ERROR_BUF_LVL_2     \
{                           \
    ERROR_ID_LVL_2_1,       \
    ERROR_ID_LVL_2_2,       \
    ERROR_ID_LVL_2_3,       \
    ERROR_ID_LVL_2,         \
};                                                    
          
/* Error list of three */
#define ERROR_BUF_LVL_3     \
{                           \
    ERROR_ID_LVL_3_1,       \
    ERROR_ID_LVL_3_2,       \
    ERROR_ID_LVL_3_3,       \
    ERROR_ID_LVL_3,         \
};                                                         

#endif
