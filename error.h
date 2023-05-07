/*
 * Copyright (c) 2019-2020, redoc
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-05     qq           the first version
 */

#ifndef __ERROR_H
#define __ERROR_H

#include "error_id.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	ERROR_EXIST_NO = 0,
	ERROR_EXIST_YES,
	
}error_exist_t;

typedef enum
{
	ERROR_LVL_NONE = 0,
	ERROR_LVL_1,
	ERROR_LVL_2,
    ERROR_LVL_3,
	
}error_lvl_t;

/* unidirectional error list structure */
typedef struct error_node_t
{
    error_id_t id;                        /*  error id                */
    struct error_node_t *next;            /*  next struct node point  */
    
}error_node_t;

void error_lock(void);
void error_unlock(void);
error_exist_t error_insert(error_id_t id);
error_exist_t error_delete(error_id_t id);
error_id_t error_code_get(void);
error_lvl_t error_lvl_get(void);
void error_print(void);

#endif
