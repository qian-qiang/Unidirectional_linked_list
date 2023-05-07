/*
 * Copyright (c) 2019-2020, redoc
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-05     qq        the first version
 */

#include "error.h"


/*  Add the error level correctly to the list */
error_id_t error_buf[] = ERROR_BUF;
error_id_t error_lvl_1_buf[] = ERROR_BUF_LVL_1;
error_id_t error_lvl_2_buf[] = ERROR_BUF_LVL_2;
error_id_t error_lvl_3_buf[] = ERROR_BUF_LVL_3;


/* The query pair ID error is listed in lvl 3 */
error_exist_t is_error_in_lvl_3_buf(error_id_t id)
{
	error_exist_t exist = ERROR_EXIST_NO;
	uint16_t error_lvl_buf_len = sizeof(error_lvl_3_buf)/sizeof(error_id_t);
    
	for(uint16_t i = 0; i < error_lvl_buf_len; i++)
	{
		if(id == error_lvl_3_buf[i])
		{
			exist = ERROR_EXIST_YES;
			return exist;
		}
	}
	
	return exist;
}

/* The query pair ID error is listed in lvl 2 */
error_exist_t is_error_in_lvl_2_buf(error_id_t id)
{
	error_exist_t exist = ERROR_EXIST_NO;
	uint16_t error_lvl_buf_len = sizeof(error_lvl_2_buf)/sizeof(error_id_t);
    
	for(uint16_t i = 0; i < error_lvl_buf_len; i++)
	{
		if(id == error_lvl_2_buf[i])
		{
			exist = ERROR_EXIST_YES;
			return exist;
		}
	}
	
	return exist;
}

/* The query pair ID error is listed in lvl 1 */
error_exist_t is_error_in_lvl_1_buf(error_id_t id)
{
	error_exist_t exist = ERROR_EXIST_NO;
	uint16_t error_lvl_buf_len = sizeof(error_lvl_1_buf)/sizeof(error_id_t);
    
	for(uint16_t i = 0; i < error_lvl_buf_len; i++)
	{
		if(id == error_lvl_1_buf[i])
		{
			exist = ERROR_EXIST_YES;
			return exist;
		}
	}
	
	return exist;
}

/* The query pair ID error is listed in error buf */
error_exist_t is_error_in_buf(error_id_t id)
{
	error_exist_t exist = ERROR_EXIST_NO;
	uint16_t error_lvl_buf_len = sizeof(error_buf)/sizeof(error_id_t);
    
	for(uint16_t i = 0; i < error_lvl_buf_len; i++)
	{
		if(id == error_buf[i])
		{
			exist = ERROR_EXIST_YES;
			return exist;
		}
	}
	
	return exist;
}
