/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 /* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 7: FUL = Full */
#define SETFULLBIT 0x80
#define RSTFULLBIT 0x7F
#define CHKFULLBIT SETFULLBIT

/* TO_DO: BIT 6: EMP: Empty */
#define SETEMPBIT 0x40
#define RSTEMPLBIT 0xBF
#define CHKEMPBIT SETEMPBIT

/* TO_DO: BIT 5: REL = Relocation */
#define SETRELBIT 0x20
#define RSTRELBIT 0xDF
#define CHKRELBIT SETRELBIT

/* TO_DO: BIT 4: END = EndOfBuffer */
#define SETENDBIT 0x10
#define RSTENDBIT 0xEF
#define CHKENDBIT SETENDBIT

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	ali_int mark;			/* the offset to the mark position (in chars) */
	ali_int read;			/* the offset to the get a char position (in chars) */
	ali_int wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	ali_char*	content;			/* pointer to the beginning of character array (character buffer) */
	ali_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	ali_int		increment;			/* character array increment factor */
	ali_int		mode;				/* operational mode indicator */
	ali_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;			/* Offset / position field */
	ali_int		histogram[NCHAR];	/* Statistics of chars */
	ali_int		numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(ali_int, ali_int, ali_int);
ReaderPointer	readerAddChar		(ReaderPointer const, ali_char);
ali_boln		readerClear		    (ReaderPointer const);
ali_boln		readerFree		    (ReaderPointer const);
ali_boln		readerIsFull		(ReaderPointer const);
ali_boln		readerIsEmpty		(ReaderPointer const);
ali_boln		readerSetMark		(ReaderPointer const, ali_int);
ali_int		readerPrint		    (ReaderPointer const);
ali_int		readerLoad			(ReaderPointer const, FILE* const);
ali_boln		readerRecover		(ReaderPointer const);
ali_boln		readerRetract		(ReaderPointer const);
ali_boln		readerRestore		(ReaderPointer const);
/* Getters */
ali_char		readerGetChar		(ReaderPointer const);
ali_char*	readerGetContent	(ReaderPointer const, ali_int);
ali_int		readerGetPosRead	(ReaderPointer const);
ali_int		readerGetPosWrte	(ReaderPointer const);
ali_int		readerGetPosMark	(ReaderPointer const);
ali_int		readerGetSize		(ReaderPointer const);
ali_int		readerGetInc		(ReaderPointer const);
ali_int		readerGetMode		(ReaderPointer const);
ali_byte	readerGetFlags		(ReaderPointer const);
ali_int		readerShowStat		(ReaderPointer const);
ali_int		readerNumErrors		(ReaderPointer const);

#endif
