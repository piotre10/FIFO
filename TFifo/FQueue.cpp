#include "FQueue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void QFDel( QFIFO* q );

QFIFO* QFCreate( int nSize )
{
	QFIFO* pQueue = (QFIFO*)calloc( 1, sizeof( QFIFO ) );
	if( !pQueue ) return NULL;
	pQueue->pFQItems = (QINFO**)calloc( nSize, sizeof( QINFO* ) );
	if( !pQueue->pFQItems ) return NULL;
	pQueue->nMaxElem = nSize;
	return pQueue;
}
int QFEmpty( QFIFO* q )
{
	return !( q&&q->nNoElem );
}
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
	if( !q ) return 0;
	if( q->nNoElem >= q->nMaxElem ) return 0;
	q->pFQItems[q->nTail] = pItem;
	q->nTail = ( q->nTail + 1 )%( q->nMaxElem );
	q->nNoElem++;
	return 1;
}
QINFO* QFDequeue( QFIFO* q )
{
	if( QFEmpty( q ) ) return NULL;
	QINFO* pRes = q->pFQItems[q->nHead];
	QFDel( q );
	return pRes;
}
void QFClear( QFIFO* q, void( *FreeMem )( const void* ) )
{
	if( !q )
	{
		printf( "(TF) Error1: Queue does not exist (3)\n" );
		return;
	}
	while( !QFEmpty( q ) )
		FreeMem( QFDequeue( q ) );
	q->nHead = q->nTail = 0;
}
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) )
{
	if( !( q && *q ) )
	{
		printf( "(TF) Error1: Queue does not exist (1)" );
	}
	QFClear( *q, FreeMem );
	free( ( *q )->pFQItems );
	free( *q );
	*q = NULL;
}
void PrintQueue( QFIFO* q, void( *PrintInfo )( const void* ) )
{
	if( !q )
	{
		printf( "(TF) Error1: Queue does not exist (2)" );
		return;
	}
	int index = q->nHead;
	printf( "#######Queue: ######\n" );
	for( int i =1 ; i<=q->nNoElem; i++, index = ( index+1 )%( q->nMaxElem ))
	{
		printf( "%d. ", i );
		PrintInfo( q->pFQItems[index] );
	}
	printf( "####################\n" );
}

void QFDel( QFIFO* q )
{
	if( QFEmpty( q ) )
	{
		printf( "(TF) Error2: Queue is empty or does not exist item cannot be deleted (1)\n" );
		return;
	}
	q->pFQItems[q->nHead] = NULL;
	q->nHead = ( q->nHead+1 )%( q->nMaxElem );
	q->nNoElem--;
}