#include "FQueue.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 4

int main()
{
   QFIFO* pQueue = QFCreate( SIZE );
   for( int i = 0; i<5; i++ )
   {
      QINFO* pTemp = AllocateUserType( );
      if( !pTemp )
      {
         printf( "ERROR%d: Usertype cannot be allocated", i+1 );
         return -2;
      }
      pTemp->nKey = i+1;
      itoa( i+1, pTemp->sName,10 );
      if( !QFEnqueue( pQueue, pTemp ) )
      {
         printf( "Error%d: Queue is full item has not been added\n", i );
      }
   }
   PrintQueue( pQueue, PrintUserType );
   QINFO* pTemp = NULL;
   for( int j = 0; j<3; j++ )
   {
      PrintUserType( pTemp = QFDequeue( pQueue ) );
      if( !pTemp ) continue;
      FreeUserType( pTemp );
   }
   PrintQueue( pQueue, PrintUserType );
   for( int i = 5; i<8; i++ )
   {
      QINFO* pTemp = AllocateUserType( );
      if( !pTemp )
      {
         printf( "ERROR%d: Usertype cannot be allocated", i+1 );
         return -2;
      }
      pTemp->nKey = i+1;
      itoa( i+1, pTemp->sName, 10 );
      if( !QFEnqueue( pQueue, pTemp ) )
      {
         printf( "Error%d: Queue is full item has not been added", i );
      }
   }
   QFClear( pQueue, FreeUserType );
   for( int i = 8; i<12; i++ )
   {
      QINFO* pTemp = AllocateUserType( );
      if( !pTemp )
      {
         printf( "ERROR%d: Usertype cannot be allocated", i+1 );
         return -2;
      }
      pTemp->nKey = i+1;
      itoa( i+1, pTemp->sName, 10 );
      if( !QFEnqueue( pQueue, pTemp ) )
      {
         printf( "Error%d: Queue is full item has not been added", i );
      }
   }
   PrintUserType( pTemp = QFDequeue( pQueue ) );
   if( pTemp ) FreeUserType( pTemp );
   PrintQueue( pQueue, PrintUserType );
   QFRemove( &pQueue, FreeUserType );



   return 0;
}

