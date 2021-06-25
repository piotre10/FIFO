#pragma once
#include "global.h"

typedef struct tagQFIFO
{
	QINFO** pFQItems;
	int nHead;
	int nTail;
	int nNoElem;
	int nMaxElem;
}QFIFO;

QFIFO* QFCreate( int nSize );
int QFEmpty( QFIFO* q );
int QFEnqueue( QFIFO* q, QINFO* pItem );
QINFO* QFDequeue( QFIFO* q );
void QFClear( QFIFO* q, void( *FreeMem )( const void* ) );
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) );
void PrintQueue( QFIFO* q, void( *PrintInfo )( const void* ) );