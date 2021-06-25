#include "FQueue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void QFDel( QFIFO* q );

QFIFO* QFCreate( int nSize )
{
	QFIFO* pQueue = (QFIFO*)calloc( 1, sizeof( QFIFO ) );
	if( !pQueue ) return NULL;
	QINFO** pTab = (QINFO**)calloc( nSize, sizeof( QINFO* ) );
	if( !pTab ) return NULL;
	pQueue->pFQItems = pTab;
	pQueue->nMaxElem = nSize;
	pQueue->nNoElem = 0;
	pQueue->nHead = 0;
	pQueue->nTail = 0;
	return pQueue;
}
int QFEmpty( QFIFO* q )
{
	if( !q->nNoElem )return 1;
	return 0;
}
int QFEnqueue( QFIFO* q, QINFO* pItem )
{
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
	while( !QFEmpty( q ) )
	{
		QINFO* pTemp = QFDequeue( q );
		FreeMem( pTemp );
	}
}
void QFRemove( QFIFO** q, void( *FreeMem )( const void* ) )
{
	QFClear( *q, FreeMem );
	free( ( *q )->pFQItems );
	free( *q );
}
void PrintQueue( QFIFO* q, void( *PrintInfo )( const void* ) )
{
	int n = 1;
	int index = q->nHead;
	printf( "#######Queue: ######\n" );
	for( int i = q->nNoElem; i>0; i = i--, n++, index = ( index+1 )%( q->nMaxElem ))
	{
		printf( "%d. ", n );
		PrintInfo( q->pFQItems[index] );
	}
}

void QFDel( QFIFO* q )
{
	memset( &( q->pFQItems[q->nHead] ), 0, sizeof( QINFO* ) );
	q->nHead = ( q->nHead + 1 )%( q->nMaxElem );
	q->nNoElem--;
}