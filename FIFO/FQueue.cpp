#include "FQueue.h"
#include <stdlib.h>
#include <stdio.h>

void QFDel( QFIFO* q );

QFIFO* QFCreate( )
{
	return (QFIFO*)calloc( 1, sizeof( QFIFO ) );
}
int QFEmpty( QFIFO* q )
{
	return  !q || !q->pHead;
}
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
	if( !q ) return 0;
	FQItem* pAdded = (FQItem*)calloc( 1, sizeof( FQItem ) );
	if( !pAdded ) return 0;
	pAdded->pInfo = pItem;
	if( QFEmpty( q ) )
	{
		q->pHead = pAdded;
	}
	else q->pTail->pNext = pAdded;
	q->pTail = pAdded;
	return 1;
}
QINFO* QFDequeue( QFIFO* q )
{
	if( QFEmpty( q ) ) return NULL;
	QINFO* pInfo = q->pHead->pInfo;
	QFDel( q );
	return pInfo;
}
void QFClear( QFIFO* q, void( *FreeMem )( const void* ) )
{
	if( !q )
	{
		printf( "(F) Error1: Queue does not exist (3)\n" );
		return;
	}
	while( !QFEmpty(q) )
		FreeMem( QFDequeue( q ) );
}
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) )
{
	if( !(q && *q ) )
	{
		printf( "(F) Error1: Queue does not exist (1)\n" );
		return;
	}
	QFClear( *q, FreeMem );
	free( *q );
	*q = NULL;
}
void QFDel( QFIFO* q )
{
	if( QFEmpty( q ) )
	{
		printf( "(F) Error2: Queue is empty or does not exist item cannot be deleted (1)\n" );
		return;
	}
	FQItem* pDeleted = q->pHead;
	q->pHead = pDeleted->pNext;
	if( QFEmpty(q) ) q->pTail = NULL;
	free( pDeleted );
}
void PrintQueue( QFIFO* q, void( *PrintInfo )( const void* ) )
{
	if( !q )
	{
		printf( "(F) Error1: Queue does not exist (2)\n" );
		return;
	}
	FQItem* pTemp = q->pHead;
	int i = 1;
	printf( "#####Queue: ######\n" );
	while( pTemp )
	{
		printf( "%d. ",i );
		if(PrintInfo) PrintInfo( pTemp->pInfo );
		i++;
		pTemp = pTemp->pNext;
	}
	printf( "##################\n" );
}