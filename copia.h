//Archivo .h generado 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List5.h"
extern DigitList *list_New();
extern int list_Add( DigitList *pList, Digit digit );
	extern Digit list_Nth( DigitList list, short n );
extern void list_Dispose( DigitList **ppList );
static short RandomNumberInRange( short min, short max );
int main( int argc, char *argv[] );
