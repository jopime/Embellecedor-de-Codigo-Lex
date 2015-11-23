/*
 *   List5.c
 *   Almost OO Example for SEng265
 *   Written by Glen Darling.
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "List5.h"


#define kCheckDigitList         "DigitList"
#define kCheckDigitListNode  "DigitListNode"


/* List functions */

extern DigitList *list_New() {
    DigitList *pList;
    pList = (DigitList *) malloc( sizeof( DigitList ) );
    if( pList != NULL ) {
        ( pList->Check ) = kCheckDigitList;
        ( pList->List ) = NULL;
    }
    return( pList );
}

extern int list_Add( DigitList *pList, Digit digit ) {
    DigitListNodePtr out;
    assert( pList != NULL );
    assert( digit >=0 && digit <= 9 );
    assert( !strcmp( pList->Check, kCheckDigitList ) );
    out = (DigitListNodePtr) malloc( sizeof( DigitListNode ) );
    if( out != NULL ) {
        out->Check = kCheckDigitListNode;
        out->Data = digit;
        out->Next = pList->List;
        pList->List = out;
        return( 1 );
	/*
 *   List5.c
 *   Almost OO Example for SEng265
 *   Written by Glen Darling.
 */
    }
    return( 0 );
}

    short result;
    DigitListNodePtr p;
    assert( !strcmp( list.Check, kCheckDigitList ) );
    p = ( list.List );
    result = 0;
    while( p != NULL ) {
        assert( !strcmp( p->Check, kCheckDigitListNode ) );
        assert( p->Data >=0 && p->Data <= 9 );
        p = ( p->Next );
        result++;
    }
    return( result );
}

extern Digit list_Nth( DigitList list, short n ) {
    DigitListNodePtr p;
    assert( !strcmp( list.Check, kCheckDigitList ) );
    p = ( list.List );
    while( p != NULL ) {
        assert( !strcmp( p->Check, kCheckDigitListNode ) );
        assert( p->Data >=0 && p->Data <= 9 );
        n--;
        if( !n )
            return( p->Data );
        p = ( p->Next );
    }
    assert( 0 );
    return( -1 );  /* This statement is not reached */
}
// hola
extern void list_Dispose( DigitList **ppList ) {
    DigitListNodePtr p;
    assert( ppList != NULL );
    assert( (*ppList) != NULL );
    assert( !strcmp( (*ppList)->Check, kCheckDigitList ) );
    p = ( (*ppList)->List );
    while( p != NULL ) {
        assert( !strcmp( p->Check, kCheckDigitListNode ) );
        assert( p->Data >=0 && p->Data <= 9 );
        ( (*ppList)->List ) = p->Next;
        p->Check = NULL;
        p->Data = -1;
        p->Next = NULL;
        free( p );
        p = ( (*ppList)->List );
    }
    (*ppList)->Check = NULL;
    (*ppList)->List = NULL;
    free(*ppList);
    (*ppList) = NULL;
}

/* List testing functions */

static short RandomNumberInRange( short min, short max ) {
    return( min +
        (short)(((double)(1+max-min))*((double)rand())/
        (1.0+((double)RAND_MAX))) );
}


/* Main function */

int main( int argc, char *argv[] ) {

    short i, n[10];
    Digit r;
    DigitList *p;

    srand( (unsigned int) getpid() );

    p = list_New();

    /* Zero the frequency array */
    for( i=0; i<10; i++ )
        n[i] = 0;

    /* Insert digits, counting frequency as we go */
    for( i=0; i<1000; i++ ) {
        r = RandomNumberInRange( 0, 9 );
        n[r]++;
        if( ! list_Add( p, r ) ) {
            printf( "Out of memory adding element number %d.\n", i );
            exit( 1 );
        }
    }

    /* Display frequencies */
    for( i=0; i<10; i++ )
        printf( "%d: %d\n", i, n[i] );

#if kDEBUG
    /* Display raw data if we are debugging */
    for( i=1; i<=list_Size( *p ); i++ )
        printf( "%u ", list_Nth( *p, i ) );
    printf( "\n" );
#endif

    /* Zero the frequency array */
    for( i=0; i<10; i++ )
        n[i] = 0;

    /* Recompute the frequencies by traversing the list */
    for( i=1; i<=list_Size( *p ); i++ )
        n[ list_Nth( *p, i ) ]++;

    /* Display frequencies again */
    for( i=0; i<10; i++ )
        printf( "%d: %d\n", i, n[i] );

    printf( "\n" );
    list_Dispose( &p );

    return( 0 );
}

 