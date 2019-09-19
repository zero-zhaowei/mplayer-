#pragma once
#include "Subfiles.h"

#if __cplusplus
extern "C"{
#endif

	extern LRC *insert_link(LRC *head, LRC tmp);
	extern void print_link(LRC *head);

#if __cplusplus
}
#endif