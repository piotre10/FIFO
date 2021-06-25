#pragma once

#include "global.h"


typedef struct tagFQItem
{
   QINFO* pInfo;
   tagFQItem* pNext;
}FQItem;

typedef struct
{
   FQItem* pHead;
   FQItem* pTail;
} QFIFO;


QFIFO* QFCreate( );
int QFEmpty( QFIFO* q );
int QFEnqueue( QFIFO* q, QINFO* pItem );
QINFO* QFDequeue( QFIFO* q );
void QFClear( QFIFO* q, void( *FreeMem )( const void* ) );
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) );
void PrintQueue( QFIFO* q, void( *PrintInfo )( const void* ) );
