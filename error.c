/*
 * Copyright (c) 2019-2020, redoc
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-05     qq           the first version
 */

#define LOG_TAG   "error"  
#define LOG_LVL   LOG_LVL_DBG 

#include "error.h"

static error_node_t* error_handle = NULL;

static error_node_t *error_exist(error_id_t id);
static error_exist_t error_find(void);
static error_exist_t is_error_lvl_3_exist(void);
static error_exist_t is_error_lvl_2_exist(void);
static error_exist_t is_error_lvl_1_exist(void);
extern error_exist_t is_error_in_buf(error_id_t id);
extern error_exist_t is_error_in_lvl_3_buf(error_id_t id);
extern error_exist_t is_error_in_lvl_2_buf(error_id_t id);
extern error_exist_t is_error_in_lvl_1_buf(error_id_t id);

/* Query whether there are errors in the lvl3 list */
static error_exist_t is_error_lvl_3_exist(void)
{
	error_exist_t exist = ERROR_EXIST_NO;
	
	struct error_node_t** curr;
    
	for(curr = &error_handle; *curr; ) 
	{
		struct error_node_t* entry = *curr;
		if (is_error_in_lvl_3_buf(entry->id)) 
		{
			exist = ERROR_EXIST_YES;
			return exist;
		} 
		else
		{
			curr = &entry->next;
		}	
	}
	
	return exist; 
}

/* Query whether there are errors in the lvl2 list */
static error_exist_t is_error_lvl_2_exist(void)
{
	error_exist_t exist = ERROR_EXIST_NO;
	
	struct error_node_t** curr;
    
	for(curr = &error_handle; *curr; ) 
	{
		struct error_node_t* entry = *curr;
		if (is_error_in_lvl_2_buf(entry->id)) 
		{
			exist = ERROR_EXIST_YES;
			return exist;
		} 
		else
		{
			curr = &entry->next;
		}	
	}
	
	return exist; 
}

/* Query whether there are errors in the lvl1 list */
static error_exist_t is_error_lvl_1_exist(void)
{
	error_exist_t exist = ERROR_EXIST_NO;
	
	struct error_node_t** curr;
    
	for(curr = &error_handle; *curr; ) 
	{
		struct error_node_t* entry = *curr;
		if (is_error_in_lvl_1_buf(entry->id)) 
		{
			exist = ERROR_EXIST_YES;
			return exist;
		} 
		else
		{
			curr = &entry->next;
		}	
	}
	
	return exist; 
}

/* The node address is returned successfully. Otherwise, nothing is returned */
static error_node_t *error_exist(error_id_t id)
{
	struct error_node_t** curr;
    
    for(curr = &error_handle; *curr; ) 
    {
        struct error_node_t* entry = *curr;
        if (entry->id == id) 
        {
            return entry;
        } 
        else
        {
            curr = &entry->next;
        }   
    }
    
    return NULL;
}

/* Query whether any errors are in the list */
static error_exist_t error_find(void)
{
	error_exist_t exist = ERROR_EXIST_NO;
	
	struct error_node_t** curr;
    
	for(curr = &error_handle; *curr; ) 
	{
		struct error_node_t* entry = *curr;
		if (entry) 
		{
			exist = ERROR_EXIST_YES;
			return exist;
		} 
		else
		{
			curr = &entry->next;
		}	
	}
	
	return exist; 
}

/* Insert a node. if the node does exist return ERROR_EXIST_NO else renturn ERROR_EXIST_YES */
error_exist_t error_insert(error_id_t id)
{
	error_node_t *error_node_ptr = NULL;
	error_exist_t result = ERROR_EXIST_YES;
	
	error_lock();
	
	error_node_ptr = error_exist(id);
	
    if(NULL != error_node_ptr)
    {
        result = ERROR_EXIST_YES;
		printf("error insert invalid, error id in error_node");
		goto __exit;
    }
	else
	{
		error_node_ptr = malloc(sizeof(error_node_t));
		
		if(NULL == error_node_ptr)
		{
			printf("malloc error.");
			result = ERROR_EXIST_NO;
			goto __exit;
		}
		
		error_node_ptr->id = id;
		error_node_ptr->next = error_handle;
		error_handle = error_node_ptr;
		
		printf("error insert %d \r\n",id);
		
		result = ERROR_EXIST_NO;
		goto __exit;
	} 

__exit:	
	
	error_unlock();
	
	return result;	
}

/* Delete a node if the node does no exist return ERROR_EXIST_NO else renturn ERROR_EXIST_YES */
error_exist_t error_delete(error_id_t id)
{
	error_node_t *error_node_ptr = NULL;
	error_exist_t result = ERROR_EXIST_YES;
	
	error_lock();
	
	error_node_ptr = error_exist(id);
	
    if(NULL == error_node_ptr)
    {
        result = ERROR_EXIST_NO;
		goto __exit;
    }
	else
	{
		struct error_node_t** curr;
    
		for(curr = &error_handle; *curr; ) 
		{
			struct error_node_t* entry = *curr;
			if (entry == error_node_ptr) 
			{
				*curr = entry->next;
			} 
			else
			{
				curr = &entry->next;
			}
		}
		
        printf("error delete %d \r\n",id);
        
		free(error_node_ptr);
		
		result = ERROR_EXIST_YES;
		goto __exit;
	}

__exit:	
	error_unlock();
	
	return result;
}

/* Traversing the node returns an error one at a time */
error_id_t error_code_get(void)
{
	error_id_t id = ERROR_ID_NONE;
    static error_node_t* target_tr = NULL;
    
    error_lock();
    
    if(target_tr == NULL)
    {
        target_tr = error_handle;
    }
    
    if(target_tr)
    {
        id = target_tr->id;
        
        target_tr = target_tr->next;
    }
    
    if(ERROR_EXIST_NO == is_error_in_buf(id))
    {
        id = ERROR_ID_NONE;
    }
    
    error_unlock();
    
	return id;
}

/*  Query error level  */
error_lvl_t error_lvl_get(void)
{
	error_lvl_t lvl = ERROR_LVL_NONE;
	
    error_lock();
    
	if(ERROR_EXIST_NO == error_find())
	{
		lvl = ERROR_LVL_NONE;
	}
    else if(ERROR_EXIST_YES == is_error_lvl_3_exist())
	{
		lvl = ERROR_LVL_3;
	}
	else if(ERROR_EXIST_YES == is_error_lvl_2_exist())
	{
		lvl = ERROR_LVL_2;
	}
	else if(ERROR_EXIST_YES == is_error_lvl_1_exist())
	{
		lvl = ERROR_LVL_1;
	}
    else
    {
        printf("have some error id is not in the list_lvl. \r\n");
    }
    
    error_unlock();
	
	return lvl;
}

void error_print(void)
{
	error_node_t* target = NULL;
	
	target = error_handle;
	
    printf("error lvl: %d\r\n", error_lvl_get());
    
    error_lock();
	if(target == NULL)
	{
		printf("no error!\r\n");
	}
	else
	{
		printf("error id : ");
		for(; target != NULL; target = target->next)
		{
			printf(" %d ", target->id);
		}
		printf("\r\n");
	}
    error_unlock();
}


