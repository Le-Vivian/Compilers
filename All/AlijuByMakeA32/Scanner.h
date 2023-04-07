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
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 50   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,	//0	/*  0: Error token */
	MNID_T,	//1/*  1: Method name identifier token (start: &) */
	STR_T,	//2	/*  2: String literal token */
	INT_T,  //3
	FLT_T,  //4
	STRV_T, //5
	INIV_T, //6
	FLTV_T, //7
	LPR_T,  //8		/*  3: Left parenthesis token */
	RPR_T,  //9		/*  4: Right parenthesis token */
	LBR_T,	//10	/*  5: Left brace token */
	RBR_T,	//11	/*  6: Right brace token */
	KW_T,	//12	/*  7: Keyword token */
	EOS_T,	//13	/*  8: End of statement (semicolon) */
	RTE_T,	//14	/*  9: Run-time error token */
	SEOF_T,	//15	/* 11: Source end-of-file token */
	COM_T,  //16 
	LAT_T,  //17 //>
	SMT_T,  //18 //<
	PLU_T,  //19 //*
	ADD_T,  //20 //=
	MIN_T,  //21 //-
    DIV_T,  //22
	EQU_T,  //23  // /
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	ali_int codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	ali_int intValue;						/* integer literal attribute (value) */
	ali_int keywordIndex;					/* keyword index in the keyword table */
	ali_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	ali_float floatValue;					/* floating-point literal attribute (value) */
	ali_char floatTempl[VID_LEN + 1];
	ali_char intTempl[VID_LEN + 1];
	ali_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	ali_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	ali_byte flags;			/* Flags information */
	union {
		ali_int intValue;				/* Integer value */
		ali_float floatValue;			/* Float value */
		ali_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	ali_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '%'		// method
#define CHRCOL3 '\''	// quote
#define CHRCOL4 '.'		// period	
#define CHRCOL5 '$'		// int var
#define CHRCOL6 '@'		// string var id
#define CHRCOL7 '^'		// float var id
#define CHRCOL8 '#'		// comment


/* These constants will be used on VID / MID function */
#define MNIDPREFIX '%'


/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	21		/* Error state with no retract */
#define ESWR	22		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 11

/* TO_DO: Transition table - type of states defined in separate table */
//static ali_int transitionTable[][TABLE_COLUMNS] = {
//	/*[A-z], [0-9],    _,    &,    ', SEOF, other
//	   L(0),  D(1), U(2), M(3), Q(4), E(5),  O(6) */
//	{     1,  ESNR, ESNR, ESNR,    4, ESWR, ESNR}, // S0: NOAS
//	{     1,     1,    1,    2, ESWR, ESWR,    3}, // S1: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S2: ASNR (MVID)
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S3: ASWR (KEY)
//	{     4,     4,    4,    4,    5, ESWR,    4}, // S4: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S5: ASNR (SL)
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}, // S6: ASNR (ES)
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS}  // S7: ASWR (ER)
//};

//static ali_int transitionTable[][TABLE_COLUMNS] = {
//	/*[A-z], [0-9],    _,    &,    ', SEOF, other 
//	   L(0),  D(1), U(2), M(3),    S    I    Q(4),     O       P   */
//	{     1,     6, ESNR, ESNR,   13,  10,    4,    ESNR,  ESNR}, // S0: NOAS
//	{     1,     1,    1,    2,    3,    3,    3,    3,     3}, // S1: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // S2: ASNR (MVID)
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // S3: ASWR (KEY)
//	{     4,     4,    4,    4,    4,    4,    5,     4,    4}, // S4: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // S5: ASNR (SL)
//	{     7,     6,    7,    7,    7,    7,    7,     7,    8}, // S6: NOAS (ES)
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // S7: ASWR (ER)
//	{     9,     8,    9,    9,    9,    9,    9,     9,    9}, // S8: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // s9: ASWR(float)
//	{    11,  ESNR, ESNR, ESNR, ESNR, ESNR, ESNR,  ESNR, ESNR}, // s10: NOAS
//	{    11,    11, ESNR, ESNR, ESNR,   12, ESNR,  ESNR, ESNR}, // s11: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // s12: ASNR(sl)
//	{    14,  ESNR, ESNR, ESNR, ESNR, ESNR, ESNR,  ESNR, ESNR}, // s13: NOAS
//	{    14,    14, ESNR, ESNR,   15, ESNR, ESNR,  ESNR, ESNR}, // s14: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // s15: ASNR(sl)
//	{     4,     4,    4,    4,    4,    4,    5,     4,    4}, // S4: NOAS
//	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,    FS,   FS}, // S5: ASNR (SL)
//
//};
//static ali_int transitionTable[][TABLE_COLUMNS] = {
//	/*[A-z], [0-9],    %,    ',	     .,	intVar,	stringVar, floatVar,	comments,	SEOF, other
//	   L(0),  D(1), M(2), Q(3),   P(4),	  I(5), 	S(6),	   F(7),	C(8)		E(9),  O(10) k  */
//	{     1,     6, ESNR,    4,   ESNR,		10,		  13,		16,		19,			ESWR, ESNR,  ESNR}, // S0: NOAS
//	{     1,     1,    2, ESWR,   ESWR,   ESWR,		ESWR,	   	ESWR,	ESWR,		ESWR,    ESNR,   3}, // S1: NOAS
//	{    FS,    FS,   FS,   FS,     FS,	   	FS,	  	  FS,	  	FS,		FS,			FS,   FS,     FS}, // S2: ASNR (MVID)
//	{    FS,    FS,   FS,   FS,     FS,	   	FS,	  	  FS,	  	FS,		FS,			FS,   FS, FS}, // S3: ASWR (KEY)
//	{     4,     4,    4,    5,      4,	  	 4,	   	   4,		 4,		4,			ESWR,   4, ESWR}, // S4: NOAS ?ESWR
//	{    FS,    FS,   FS,   FS,     FS,		FS,	  	  FS,		FS,		FS,			FS,   FS, FS}, // S5: ASNR (SL)
//	{	  7,	 6,	   7,    7,      8,	   	 7,        7,   	 7,		7,			ESWR,    7, ESWR}, // S6: NOAS ?ESWR
//	{    FS,    FS,   FS,   FS,     FS,	 	FS,	  	  FS,		FS,		FS,			FS,   FS, FS}, // S7: ASNR (IL)
//	{     9,     8,    9,    9,   ESWR,	  	 9,	       9,		9,		9,			ESWR,    9, ESWR}, // S8: NOAS
//	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS, FS}, // S9: ASNR (FL)
//	{	  11,  ESWR, ESWR, ESWR,  ESWR,   ESWR,	    ESWR,		ESWR,	ESWR,		ESWR, ESNR, ESWR}, // S10: NOAS, ?ESNR not so sure
//	{	  11,	 11, ESNR, ESNR,  ESWR,	 	12,	    ESNR,		ESWR,	ESWR,		ESNR, ESNR, ESWR}, // S11: NOAS
//	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS, FS}, // S12: IVID (integer variable)
//	{	 14,  ESWR,	ESWR, ESWR,   ESNR,   ESWR,	    ESWR,		ESWR,	ESWR,		ESNR, ESNR, ESNR}, // S13: NOAS
//	{	 14,    14,	ESNR, ESNR,   ESNR,   ESNR,	      15,		ESWR,	ESWR,		ESNR, ESNR, ESNR}, // S14: NOAS
//	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS, FS}, // S15: SVID (string variable)
//	{	 17,  ESNR,	ESNR, ESNR,   ESNR,	  ESNR,	    ESNR,		ESNR,	ESNR,		ESNR, ESNR, ESNR}, // S16: NOAS
//	{	 17,    17,	ESNR, ESNR,   ESNR,	  ESNR,	    ESNR,		18,		ESNR,		ESNR, ESNR, ESNR}, // S17: NOAS
//	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS, FS}, // S18: FVID (float variable)
//	{	 19,	19,	  19,   19,		19,		19,		  19,		19,		20,			19,	 19, 19}, // S19: NOAS
//	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS,FS}, // S20: C comment
//	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS, FS}, // S21: ASNR (ES)
//	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS, FS}  // S22: ASWR (ER)
//};


static ali_int transitionTable[][TABLE_COLUMNS] = {
	/*[A-z], [0-9],    %,    ',	     .,	intVar,	stringVar, floatVar,	comments,	SEOF, other
	   L(0),  D(1), M(2), Q(3),   P(4),	  I(5), 	S(6),	   F(7),	C(8)		E(9),  O(10) */
	{     1,     6, ESNR,    4,   ESNR,		10,		  13,		16,		19,			ESWR, ESNR}, // S0: NOAS
	{     1,     3,    2,    3,      3,      3,		   3,	   	 3,	     3,		    ESWR,    3},       // S1: NOAS
	{    FS,    FS,   FS,   FS,     FS,	   	FS,	  	  FS,	  	FS,		FS,			FS,   FS}, // S2: ASNR (MVID)
	{    FS,    FS,   FS,   FS,     FS,	   	FS,	  	  FS,	  	FS,		FS,			FS,   FS}, // S3: ASWR (KEY)
	{     4,     4,    4,    5,      4,	  	 4,	   	   4,		 4,		4,			ESWR,   4}, // S4: NOAS ?ESWR
	{    FS,    FS,   FS,   FS,     FS,		FS,	  	  FS,		FS,		FS,			FS,   FS}, // S5: ASNR (SL)
	{	  7,	 6,	   7,    7,      8,	   	 7,        7,   	 7,		7,			ESWR,    7}, // S6: NOAS ?ESWR
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	  	  FS,		FS,		FS,			FS,   FS}, // S7: ASNR (IL)
	{     9,     8,    9,    9,   ESWR,	  	 9,	       9,		9,		9,			ESWR,    9}, // S8: NOAS
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS}, // S9: ASNR (FL)
	{	  11,  ESWR, ESWR, ESWR,  ESWR,   ESWR,	    ESWR,		ESWR,	ESWR,		ESWR, ESNR}, // S10: NOAS, ?ESNR not so sure
	{	  11,	 11, ESNR, ESNR,  ESWR,	 	12,	    ESNR,		ESWR,	ESWR,		ESNR, ESNR}, // S11: NOAS
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS}, // S12: IVID (integer variable)
	{	 14,  ESWR,	ESWR, ESWR,   ESNR,   ESWR,	    ESWR,		ESWR,	ESWR,		ESNR, ESNR}, // S13: NOAS
	{	 14,    14,	ESNR, ESNR,   ESNR,   ESNR,	      15,		ESWR,	ESWR,		ESNR, ESNR}, // S14: NOAS
	{    FS,    FS,   FS,   FS,     FS,	 	FS,	      FS,		FS,		FS,			FS,   FS}, // S15: SVID (string variable)
	{	 17,  ESNR,	ESNR, ESNR,   ESNR,	  ESNR,	    ESNR,		ESNR,	ESNR,		ESNR, ESNR}, // S16: NOAS
	{	 17,    17,	ESNR, ESNR,   ESNR,	  ESNR,	    ESNR,		18,		ESNR,		ESNR, ESNR}, // S17: NOAS
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}, // S18: FVID (float variable)
	{	 19,	19,	  19,   19,		19,		19,		  19,		19,		20,			19,	 19}, // S19: NOAS
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}, // S20: C comment
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}, // S21: ASNR (ES)
	{    FS,    FS,   FS,   FS,     FS,	    FS,	      FS,		FS,		FS,			FS,   FS}  // S22: ASWR (ER)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static ali_int stateType[] = {
	NOFS, //S0 
	NOFS, //S1
	FSNR, //S2: MVID
	FSWR, //S3: KEY
	NOFS, //S4
	FSNR, //S5: SL
	NOFS, //S6
	FSWR, //S7: IL
	NOFS, //S8
	FSWR, //S9: FL
	NOFS, //S10
	NOFS, //S11
	FSNR, //S12: int variable
	NOFS, //S13
	NOFS, //S14
	FSNR, //S15: string varibale
	NOFS, //S16
	NOFS, //S17
	FSNR, //S18: float varibale
	NOFS, //S19
	FSNR, //S20: comment
	FSNR, //S21 ESNR
	FSWR //S22 ESWR

};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
ali_int startScanner(ReaderPointer psc_buf);
Token tokenizer(ali_void);
static ali_int nextClass(ali_char c);				/* character class function */
static ali_int nextState(ali_int, ali_char);		/* state machine function */
ali_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(ali_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(ali_char lexeme[]);
Token funcID	(ali_char lexeme[]);
Token funcKEY	(ali_char lexeme[]);
Token funcErr	(ali_char lexeme[]);
Token funcIL	(ali_char lexeme[]);
Token funcFL    (ali_char lexeme[]);
Token funcIDV   (ali_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] - Methods */
	funcKEY,	/* KEY  [03] - Keywords */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] - String Literal */
	NULL,       //6
	funcIL,     //7  int var 
	NULL,       //8
	funcFL,     //9  float var
	NULL,       //10
	NULL,       //11
	funcIDV,    //12 int id
	NULL,       //13
	NULL,       //14
	funcIDV,    //15 string id 
	NULL,       //16
	NULL,       //17
	funcIDV,    //18 float id 
	NULL,       //19
	NULL,       //20
	funcErr,	/* ERR1 [06] - No retract */
	funcErr		/* ERR2 [07] - Retract */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 12
#define INT_N 0 
#define REAL_N 1
#define STR_N 2
#define IF_N 3
#define ELSE_N 4
#define ELSEIF_N 5
#define WHILE_N 6
#define DO_N 7
#define END_N 8
#define FOR_N 9
#define AND_N 10
#define OR_N 11
/* TO_DO: Define the list of keywords */
static ali_char* keywordTable[KWT_SIZE] = {
	"int", //0
	"real", //1
	"string", //2
	"if", //3
	"else", //4
	"elseif", //5
	"while", //6
	"do", //7
	"end", //8
	"for", //9
	"and", //10
	"or" //11

};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	ali_char indentationCharType;
	ali_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
ali_int numScannerErrors;

#endif
