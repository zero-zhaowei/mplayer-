#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Subfiles.h"
#include "link.h"
char *Read(char *str)
{

    FILE *fp = fopen(str,"r");

    //将文件流指针定位到文件尾部
    fseek(fp,0,2);

    //通过ftell获取文件的总大小
    long len = ftell(fp);

	//申请空间   
    char *file = (char *)calloc(1,len+1);
    
	//复位文件流指针  
    rewind(fp);  
    //读取文件数据  
    fread(file,len,1,fp);  
    
    fclose(fp);
    return file;
}

int Cutting(char *file,char *lrc[128])
{
    
    int i = 0;
    
    
    lrc[i] = strtok(file,"\r\n");
   
    while (lrc[i] != NULL)
    {
        i++;
        lrc[i] = strtok(NULL,"\r\n");
    }
    //打印屏幕
    /*
    i=0;
    while (lrc[i] != NULL)
    {
        printf("%s\n",lrc[i]);
        i++;
    }   
    */
   return i;
    
}


LRC *Unpacking(char *lrc[128],int yes)
{
   
    
    LRC *head = NULL;
   
    
    for (int i = 4; i < yes; i++)
    {
        
        char *p_lrc = lrc[i];
        while (*p_lrc == '[')
        {
            p_lrc +=10;
             
        }
       
        char *ps = lrc[i];
       
        while (*ps == '[')
        {
            int m = 0, s = 0, ms=0;
            sscanf(ps,"[%d:%d.%d",&m,&s,&ms);

            LRC tmp;
            tmp.time = m*60+s+(ms/50);
            strcpy(tmp.lrc,p_lrc);
            head = insert_link(head,tmp);

            ps +=10;
        }
        
    }
    
    return head;
}

