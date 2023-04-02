#pragma once

#define PROC_LOG_CALL 437
#define PROC_OVERRIDE 0
#define PROC_ALERT 1
#define PROC_CRITICAL 2
#define PROC_ERROR 3
#define PROC_WARNING 4
#define PROC_NOTICE 5
#define PROC_INFO 6
#define PROC_DEBUG 7

int get_proc_log_level();

int set_proc_log_level(int new_level);

int proc_log_message(int level, char* message);

int* retrieve_set_level_params(int new_level);

int* retrieve_get_level_params();

int interpret_set_level_result(int ret_value);

int interpret_get_level_result(int ret_value);

int interpret_log_message_result(int ret_value);
