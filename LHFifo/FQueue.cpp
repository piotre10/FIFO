#include "FQueue.h"
#include <stdlib.h>
#include <stdio.h>

void QFDel( QFIFO* q );
FQItem* AllocateFQItem( );

QFIFO* QFCreate( )
{
	QFIFO* pQueue = (QFIFO*)calloc( 1, sizeof( QFIFO ) );
	if( !pQueue ) return NULL;
	FQItem* pFirst = AllocateFQItem( );
	if( !pFirst ) return NULL;
	pQueue->pHead = pFirst;
	pQueue->pTail = pFirst;
	return pQueue;
}
int QFEmpty( QFIFO* q )
{
	if( q->pHead->pNext==NULL ) return 1;
	return 0;
}
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
	FQItem* pAdded = AllocateFQItem( );
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
	while( q->pHead->pNext )
	{
		QINFO* pTemp = q->pHead->pNext->pInfo;
		QFDel( q );
		FreeMem( pTemp );
	}
}
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) )
{
	QFClear( *q, FreeMem );
	free( ( *q )->pHead );
	( *q )->pTail = NULL;
	free( ( *q )->pTail );
	free( *q );
}
void QFDel( QFIFO* q )
{
	if( QFEmpty( q ) ) return;
	FQItem* pDeleted = q->pHead->pNext;
	q->pHead->pNext = q->pHead->pNext->pNext;
	if( !( q->pHead->pNext ) ) q->pTail = q->pHead;
	free( pDeleted );
}
FQItem* AllocateFQItem( )
{
	FQItem* pItem = (FQItem*)calloc( 1, sizeof( FQItem ) );
	if( !pItem ) return NULL;
	pItem->pInfo = NULL;
	pItem->pNext = NULL;
	return pItem;
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
}