#include <stdlib.h>
#include <stdio.h>

#include "link.h"
#include "Subfiles.h"

//链表的有序插入
LRC *insert_link(LRC *head, LRC tmp)
{
    //1、为插入的节点 申请 堆区空间
    LRC *pi = (LRC *)calloc(1, sizeof(LRC));
    //2、将tmp的数据 赋值到 *pi中
    *pi = tmp;
    //将pi->next赋值为NULL；
    pi->next = NULL;

    if (head == NULL)
    {
        head = pi;
        return head;
    }
    else
    {
        LRC *pf = head, *pb = head;
        while ((pb->time < pi->time) && (pb->next != NULL))
        {
            pf = pb;

            pb = pb->next;
        }

        if (pb->time >= pi->time)
        {
            if (pb == head)
            {
                pi->next = head;
                head = pi;
            }
            else
            {
                pf->next = pi;
                pi->next = pb;
            }
        }
        else if (pb->next == NULL)
        {
            pb->next = pi;
        }

        
    }
    return head;
}



void print_link(LRC *head)
{
    if (head == NULL) //链表不存在
    {
        printf("链表不存在\n");
        return;
    }
    else //存在
    {
        LRC *pb = head;
        while (pb != NULL)
        {
            printf("num=%d,name=%s\n", pb->time, pb->lrc);
            pb = pb->next;
        }
    }
}
