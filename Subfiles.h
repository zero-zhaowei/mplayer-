#pragma once


#if __cplusplus
extern "C"{
#endif

	typedef struct lrc
	{
		int time;
		char lrc[256];	
		struct lrc *next;
	}LRC;

    extern char *Read(char *str);
	extern int Cutting(char *file,char *lrc[128]);
	extern LRC *Unpacking(char *lrc[],int yes);

#if __cplusplus
}
#endif


