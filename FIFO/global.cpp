#include "global.h"
#include <stdlib.h>
#include <stdio.h>


QINFO* AllocateUserType( )
{
	QINFO* pInfo = (QINFO*)calloc(1, sizeof( QINFO ) );
	if( !pInfo ) return NULL;
	char* str = (char*)calloc( NAME_LENGTH, sizeof( char ) );
	if( !str ) return NULL;
	pInfo->sName = str;
	return pInfo;
}
void FreeUserType( const void* pInfo )
{
	QINFO* pInfo2 = (QINFO*)pInfo;
	free( pInfo2 );
}
void PrintUserType( const void* pInfo )
{
	QINFO* pInfo2 = (QINFO*)pInfo;
	if( !pInfo2 )
	{
		printf( "NULL\n" );
		return;
	}
	printf( "Key: %d   Name: %s\n", pInfo2->nKey, pInfo2->sName );
}