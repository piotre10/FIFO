#pragma once

typedef struct
{
	char* sName;
	int   nKey;
} QInfo;

#define QINFO QInfo
#define NAME_LENGTH 50

QINFO* AllocateUserType( );
void FreeUserType( const void* pInfo );
void PrintUserType( const void* pInfo );