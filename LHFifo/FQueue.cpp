#include "FQueue.h"
#include <stdlib.h>
#include <stdio.h>

void QFDel( QFIFO* q );

QFIFO* QFCreate( )
{
	QFIFO* pQueue = (QFIFO*)calloc( 1, sizeof( QFIFO ) );
	if( !pQueue ) return NULL;
	FQItem* pFirst = (FQItem*)calloc( 1, sizeof( FQItem ) );
	if( !pFirst ) return NULL;
	pQueue->pHead = pFirst;
	pQueue->pTail = pFirst;
	return pQueue;
}
int QFEmpty( QFIFO* q )
{
	return !( q&&q->pHead->pNext );
}
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
	if( !q ) return 0;
	FQItem* pAdded = (FQItem*)calloc( 1, sizeof( FQItem ) );
	if( !pAdded ) return 0;
	pAdded->pInfo = pItem;
	q->pTail->pNext = pAdded;
	q->pTail = pAdded;
	return 1;
}
QINFO* QFDequeue( QFIFO* q )
{
	if( QFEmpty( q ) ) return NULL;
	QINFO* pInfo = q->pHead->pNext->pInfo;
	QFDel( q );
	return pInfo;
}
void QFClear( QFIFO* q, void( *FreeMem )( const void* ) )
{
	while( !QFEmpty(q) )
	{
		QINFO* pTemp = q->pHead->pNext->pInfo;
		QFDel( q );
		FreeMem( pTemp );
	}
}
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) )
{
	if( !q )
	{
		printf( "(LH) Error1: Queue does not exist (1)\n" );
		return;
	}
	QFClear( *q, FreeMem );
	free( ( *q )->pHead ); //pHead i pTail wskazuja na ten sam obiekt
	free( *q );
}
void QFDel( QFIFO* q )
{
	if( QFEmpty( q ) )
	{
		printf( "(LH) Error2: Queue is empty or does not exist item cannot be deleted (1)\n" );
		return;
	}
	FQItem* pDeleted = q->pHead->pNext;
	q->pHead->pNext = q->pHead->pNext->pNext;
	if( !( q->pHead->pNext ) ) q->pTail = q->pHead;
	free( pDeleted );
}
void PrintQueue( QFIFO* q, void( *PrintInfo )( const void* ) )
{
	FQItem* pTemp = q->pHead->pNext;
	int i = 1;
	printf( "#####Queue: ######\n" );
	while( pTemp )
	{
		printf( "%d. ", i );
		PrintInfo( pTemp->pInfo );
		i++;
		pTemp = pTemp->pNext;
	}
	printf( "####################\n" );
}