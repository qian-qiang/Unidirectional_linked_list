/*
 * Copyright (c) 2019-2020, redoc
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-05     qq           the first version
 */

#include "error.h"

#define USING_FINSH

#if defined(USING_FINSH) 
    static void error(void);
#endif

void error_lock(void)
{
    //Add locks from your operating system
}

void error_unlock(void)
{
    //Add locks from your operating system
}

static void error_lvl_process(void)
{
    error_lvl_t lvl;
    static uint8_t lvl_re = 0xfe;
    
    lvl = error_lvl_get();
    
    if(lvl_re != lvl)
    {
        switch(lvl)
        {
        case ERROR_LVL_NONE:
            //beep_stop();
            break;
        
        case ERROR_LVL_1:
            //beep_stop();
            break;

        case ERROR_LVL_2:
            //beep_show_err_mid();
            break;
        
        case ERROR_LVL_3:
            //beep_show_err_high();
            break;
        default:
            break;
        }
        printf("error lvl is:%d \r\n",lvl);
        lvl_re = lvl;
		
    }
}

static void thread_error_entry(void)
{
    static uint16_t error_time = 0;
    while(1)
    {
        if(error_time >= 1000)
        {
            error_time = 0;
            
            error_lvl_process();

            #if defined(USING_FINSH) 
                error();
            #endif

        }
        else
        {
            error_time += 100;
        }
    }
}

int main(void)
{
    thread_error_entry();
}


#if defined(USING_FINSH) 

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_CMD 3
#define MAX_INPUT_LENGTH 20

void processInput(char *input) {
    char *token;

    token = strtok(input, " ");
    
    if (!strcmp(token, "print"))
    {
        error_print();
    }
    else if(!strcmp(token, "insert"))
    {
        uint16_t id = strtol(strtok(NULL, " "), NULL, 0);
        error_insert((error_id_t)id);
    }
    else if(!strcmp(token, "delete"))
    {
        uint16_t id = strtol(strtok(NULL, " "), NULL, 0);
        error_delete((error_id_t)id);
    }
    
}

static void error(void)
{
    char input[MAX_INPUT_LENGTH];

    printf("Please input cmd : ");
    fgets(input, sizeof(input), stdin);

    // 移除换行符
    input[strcspn(input, "\n")] = '\0';

    // 处理输入数据
    processInput(input);

    return;
}

#endif
