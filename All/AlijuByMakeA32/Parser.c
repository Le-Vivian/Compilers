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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

ali_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
ali_void matchToken(ali_int tokenCode, ali_int tokenAttribute) {
	ali_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
		if (tokenAttribute == NO_ATTR) {
			matchFlag = 1;
		}
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
ali_void syncErrorHandler(ali_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
ali_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("***** ERROR  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
	//	printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
			printf("KW_T: %d\n", t.attribute.codeType);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	case INT_T:
		printf("INT_T\n");
		break;
	case FLT_T:
		printf("FLT_T\n");
		break;
	case STRV_T:
		printf("STRV_T\n");
		break;
	case INIV_T:
		printf("INIV_T\n");
		break;
	case FLTV_T:
		printf("FLTV_T\n");
		break;
	case COM_T:
		printf("COM_T\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
ali_void program() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			dataSession();
			codeSession();
			matchToken(RBR_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
ali_void dataSession() {
	//matchToken(KW_T, KW_data);
//	matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
//	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
}
ali_int dataType(ali_int type) {
	switch (type) {
	case 0:
	case 1:
	case 2:
		printf("data type \n");
		return 1;
		
	default:
		printf(" not data type \n");
		return 0;

	}
}

ali_void floatVariableList() {

	switch (lookahead.code) {
		case FLTV_T:
		matchToken(FLTV_T, NO_ATTR);
		switch (lookahead.code) {
		case COM_T:
			matchToken(COM_T, NO_ATTR);
			floatVariableList();
			break;
		default:
			break;
		}
		break;
	default:
	//	printf("ERROR\n");

		; // Empty
	}

	

}
ali_void intVariableList() {

	switch (lookahead.code) {
		case INIV_T:
		matchToken(INIV_T, NO_ATTR);
			switch (lookahead.code) {
		case COM_T:
				matchToken(COM_T, NO_ATTR);
			intVariableList();
		
			break;
		default:
			break;
		}
		break;
	default:
	//	printf("ERROR\n");

		; // Empty
		}

	

}
ali_void stringVariableList() {

	switch (lookahead.code) {
		case STRV_T:
		matchToken(STRV_T, NO_ATTR);
		switch (lookahead.code) {
		case COM_T:
			matchToken(COM_T, NO_ATTR);
			stringVariableList();
			break;
		default:
			break;
		}
		break;
	default:
	//	printf("ERROR\n");

		; // Empty
	}

	

}



/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
ali_void optVarListDeclarations() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case REAL_N:
			matchToken(KW_T, NO_ATTR);
			floatVariableList();
			matchToken(EOS_T, NO_ATTR);
			optVarListDeclarations();
			break;
		case INT_N:
			matchToken(KW_T, NO_ATTR);
			intVariableList();
			matchToken(EOS_T, NO_ATTR);
			optVarListDeclarations();
			break;
		case STR_N:
			matchToken(KW_T, NO_ATTR);
			stringVariableList();
			matchToken(EOS_T, NO_ATTR);
			optVarListDeclarations();
			break;
		}
		break;
	default:
	//	printf("ERROR\n");

		; // Empty
	}

	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
ali_void codeSession() {
//	matchToken(KW_T, KW_code);
//	matchToken(LBR_T, NO_ATTR);
	optionalStatements();
//	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
ali_void optionalStatements() {

			statements();
/*	switch (lookahead.code) {
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
		break;
	case FLTV_T:

		break;

	default:
		; // Empty
		break;
	}*/
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ali_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ali_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
//		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
//		}
	case FLTV_T:
		statements();
		break;
	case INIV_T:
		statements();
		break;
	case STRV_T:
		statements();
		break;
	case KW_T:
		statements();
		break;
	default:
		; //empty string
	}
}


ali_void floatB() {
	ali_boln math = ALI_FALSE;
	switch (lookahead.code) {
	case FLT_T:
		matchToken(FLT_T, NO_ATTR);
		break;
	case FLTV_T:
		matchToken(FLTV_T, NO_ATTR);
		break;
	case INT_T:
		matchToken(INT_T, NO_ATTR);
		break;
	case INIV_T:
		matchToken(INIV_T, NO_ATTR);
		break;

	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		floatB();
		matchToken(RPR_T, NO_ATTR);

		break;

	}

	switch (lookahead.code) {
	case PLU_T:
		matchToken(PLU_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case ADD_T:

		matchToken(ADD_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case MIN_T:

		matchToken(MIN_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case DIV_T:
		
		matchToken(DIV_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case EQU_T:
		matchToken(EQU_T, NO_ATTR);
		math = ALI_TRUE;
		break;

	case KW_T:
		if (lookahead.attribute.codeType == AND_N) {
			matchToken(KW_T, NO_ATTR);
		//	math = ALI_TRUE;
			logicalArg();
		}
	if (lookahead.attribute.codeType == OR_N) {
			matchToken(KW_T, NO_ATTR);
		//	math = ALI_TRUE;
		logicalArg();
		}



	}

	if (math == ALI_TRUE) {
		floatB();
	}
}
ali_void floatA() {
	matchToken(FLTV_T, NO_ATTR);
	matchToken(EQU_T, NO_ATTR);

	floatB();
//	matchToken(EOS_T,NO_ATTR);
//	matchToken(EOS_T, NO_ATTR);
}
ali_void intB() {
	ali_boln math = ALI_FALSE;
	switch (lookahead.code) {
	case INT_T:
		matchToken(INT_T, NO_ATTR);
		break;
	case INIV_T:
		matchToken(INIV_T, NO_ATTR);
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		intB();
		matchToken(RPR_T, NO_ATTR);
		break;

	}

	switch (lookahead.code) {
	case PLU_T:
		matchToken(PLU_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case ADD_T:
		matchToken(ADD_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case MIN_T:
		matchToken(MIN_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case DIV_T:
		matchToken(DIV_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case SMT_T:
		matchToken(SMT_T, NO_ATTR);
		math = ALI_TRUE;
		break;
	case LAT_T:
		matchToken(LAT_T, NO_ATTR);
		math = ALI_TRUE;
		break;
	case EQU_T:
		matchToken(EQU_T, NO_ATTR);
		math = ALI_TRUE;
		break;

	case KW_T:
		if (lookahead.attribute.codeType == AND_N) {
			matchToken(KW_T, NO_ATTR);

			logicalArg();
		}
		if (lookahead.attribute.codeType == OR_N) {
			matchToken(KW_T, NO_ATTR);

			logicalArg();
		}

		break;

	}

	if (math == ALI_TRUE) {
		intB();
	}
}

ali_void intA() {
	matchToken(INIV_T, NO_ATTR);
	matchToken(EQU_T, NO_ATTR);

	intB();
//	matchToken(EOS_T,NO_ATTR);
//	matchToken(EOS_T, NO_ATTR);
}

ali_void stringB() {
	ali_boln math = ALI_FALSE;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case STRV_T:
		matchToken(STRV_T, NO_ATTR);
		break;
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		stringB();
		matchToken(RPR_T, NO_ATTR);
		break;

	}

	switch (lookahead.code) {
	case PLU_T:
		matchToken(PLU_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case ADD_T:
		matchToken(ADD_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case MIN_T:
		matchToken(MIN_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case DIV_T:
		matchToken(DIV_T,NO_ATTR);
		math = ALI_TRUE;
		break;
	case EQU_T:
		matchToken(EQU_T, NO_ATTR);
		math = ALI_TRUE;
		break;
	case SMT_T:
		matchToken(SMT_T, NO_ATTR);
		math = ALI_TRUE;
		break;
	case LAT_T:
		matchToken(LAT_T, NO_ATTR);
		math = ALI_TRUE;
		break;
	case KW_T:
		if (lookahead.attribute.codeType == AND_N) {
			matchToken(KW_T, NO_ATTR);

			logicalArg();
		}
		if (lookahead.attribute.codeType == OR_N) {
			matchToken(KW_T, NO_ATTR);

			logicalArg();
		}




	}

	if (math == ALI_TRUE) {
		stringB();
	}
}

ali_void stringA() {
	matchToken(STRV_T, NO_ATTR);
	matchToken(EQU_T, NO_ATTR);

	stringB();
//	matchToken(EOS_T,NO_ATTR);
//	matchToken(EOS_T, NO_ATTR);
}


/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
ali_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case WHILE_N:
			matchToken(KW_T, NO_ATTR);
			matchToken(LPR_T, NO_ATTR);
			intB();
			matchToken(RPR_T, NO_ATTR);
			if (lookahead.code == KW_T && lookahead.attribute.codeType == DO_N) {
				matchToken(KW_T, NO_ATTR);
				matchToken(LBR_T, NO_ATTR);
				statements();
				matchToken(RBR_T, NO_ATTR);
				matchToken(EOS_T, NO_ATTR);
			}
			break;

		case IF_N:
			matchToken(KW_T, NO_ATTR);
			matchToken(LPR_T, NO_ATTR);
			stringB();
			matchToken(RPR_T,NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			statements();
			matchToken(RBR_T, NO_ATTR);
			if (lookahead.code == KW_T && lookahead.attribute.codeType == ELSE_N) {
				matchToken(KW_T, NO_ATTR);
				matchToken(LBR_T,NO_ATTR);
				statements();
				matchToken(RBR_T,NO_ATTR);
				matchToken(EOS_T, NO_ATTR);

			}
			break;
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			inputStatement();
		}
		break;
	case FLTV_T:
		floatA();
		matchToken(EOS_T, NO_ATTR);
		break;
	case INIV_T:
		intA();
		matchToken(EOS_T, NO_ATTR);
		break;
	case STRV_T:
		stringA();
		matchToken(EOS_T, NO_ATTR);
		break;


	default:
		;
		}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
ali_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}
ali_void inputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": input statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
ali_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T,NO_ATTR);
		break;
	case INT_T:
		matchToken(INT_T,NO_ATTR);
		break;
	case FLT_T:
		matchToken(FLT_T,NO_ATTR);
		break;

	case STRV_T:
		matchToken(STRV_T, NO_ATTR);
		break;
	case FLTV_T:
		matchToken(FLTV_T, NO_ATTR);
		break;
	case INIV_T:
		matchToken(INIV_T, NO_ATTR);
		break;

	default:
		;

	}
	if (lookahead.code == COM_T) {
		matchToken(COM_T, NO_ATTR);
		outputVariableList();
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

ali_void logicalArg() {
	switch (lookahead.code) {
	case INT_T:
		intB();
		break;
	case INIV_T:
		intB();
		break;

	case FLT_T:
		floatB();
		break;
	case FLTV_T:
		floatB();
		break;
	case STR_T:
		stringB();
		break;
	case STRV_T:
		stringB();
		break;

	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		logicalArg();
		matchToken(RPR_T, NO_ATTR);
		break;

	}

}
