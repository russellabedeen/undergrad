#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int get_proc_log_level() {
	syscall(435);
}

int set_proc_log_level(int new_level) {
	if (new_level < 8 && new_level > -1) {
		int ret = syscall(436, new_level);
		return ret;
	}
	else {
		return -1;
	}
}

int proc_log_message(int level, char* message) {
	if (level < 8 && level > -1) {
		int ret = syscall(437, message, level);
		return ret;
	}
	else {
		return -1;
	}
}

int* retrieve_set_level_params(int new_level) {
	int size = 3;
	int* params = malloc(sizeof(size));
	params[0] = 436;
	params[1] = 2;
	params[2] = new_level;
	return params;
}

int* retrieve_get_level_params() {
	int size = 2;
	int* params = malloc(sizeof(size));
	params[0] = 435;
	params[1] = 1;
	return params;
}

int interpret_set_level_result(int ret_value) {
	if (ret_value > -1) {
		return ret_value;
	}
	else {
		return -1;
	}
}

int interpret_get_level_result(int ret_value) {
	if (ret_value > -1) {
		return ret_value;
	}
	else {
		return -1;
	}
}

int interpret_log_message_result(int ret_value) {
	if (ret_value > -1) {
		return ret_value;
	}
	else {
		return -1;
	}
}
