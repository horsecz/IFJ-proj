/**
 * @file parser.h
 * @author Roman Janiczek (xjanic25@vutbr.cz)
 * @brief Header for parser
 * @version 0.1
 * @date 2020-11-14
 */
#ifndef IFJ_PROJECT_PARSER_H
#define IFJ_PROJECT_PARSER_H
// General 
#include <stdio.h>
#include <stdlib.h>
// Project specific
#include "scanner.h"
#include "symtable.h"
#include "returns.h"

/**
 * @brief Main parser logic \n
 *        Contains mainly enviroment preparation before parsing and then calls @see program() to initiate
 *        parsing. After this it checks return value and acts upon that
 * @param tk Pointer to token //TODO: Not sure why this is needed
 * @return eRC @see returnCodes
 */
eRC parser(Token *tk);

/** ----------------------------------------------------------- **
 *  List of functions generated according to LL1-grammar         *
 ** ----------------------------------------------------------- **/

/*** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***
 *                                                               *
 *               BASIC PROGRAM STRUCTURE CHECKS                  *
 *                                                               * 
 *** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***/

/**
 * @brief Program parse \n
 *        Goes through EOLs at the beggining of the program,
 *        does basic rule check and then calls appropriate parse functions.
 * @note <program> -> <prolog> <eol_m> <functions>
 * @return eRC @see returnCodes
 * @pre Global and shared variables are initialized and setup for parsing
 * @post Parsing should be complete and prepared for code generation or code should already be generated
 */
eRC program();

/**
 * @brief Prolog parse \n
 *        Checks if program starts with 'package main'.
 * @note <prolog> -> package main
 * @return eRC @see returnCodes
 * @pre Expects token to be at the TYPE_KEYWORD
 * @post Leaves token at the TYPE_IDENTIFIER for 'main' -> next function has to call getToken!
 */
eRC prolog();

/**
 * @brief EOL after 'package main' parse \n
 *        Require EOL after 'package main'
 * @note <eol_m> -> EOL <eol_r>
 * @return eRC @see returnCodes
 * @post Next function has to call getToken
 */
eRC eolM();

/**
 * @brief EOL indefinite parse \n
 *        Go through indefinite number of EOLs after @see eolM
 * @note <eol_r> -> EOL <eol_r>
 * @note <eol_r> -> eps
 * @return eRC @see returnCodes
 * @post Token will be ready for processing (do not call getToken in function following this function)
 */
eRC eolR();

/*** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***
 *                                                               *
 *                   FUNCTION RELATED CHECKS                     *
 *                                                               * 
 *** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***
 *   GENERAL FUNCTION CHECKS                                     *
 *** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***/

/**
 * @brief Parse block of functions \n
 *        According to roles this block has to contain at least one function (and at least one function
 *        with identifier 'main')
 * @note <functions> -> <func> <function_n>
 * @return eRC @see returnCodes
 * @pre Token should be prepared before calling this function @see eolR()
 * @post
 */
eRC functionsBlock();

/**
 * @brief Parse function \n
 *        Check function and its <cmd_block>. Save information about functions and its inside structure.
 *        Information about function (params, return values, ID) will be saved to GST (global symtable),
 *        additional symtables will be created for variables of different scopes
 * @note <func> -> func ID ( <arguments> ) <func_return> <cmd_block> 
 * @return eRC @see returnCodes
 * @pre Token should be prepared in functions preceding this function
 * @post Token will be prepared for other step -> @see commandBlock()
 */
eRC function();

/**
 * @brief Parse next function \n
 *        Try to parse another functions that may be in the source code
 * @note <function_n> -> <func> <function_n> 
 * @note <function_n> -> eps
 * @return eRC @see returnCodes
 * @pre Token should be prepared (skipped EOLs, etc..) -> @see commandBlock()
 * @post
 */
eRC functionNext();

/*** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***
 *   TYPE FUNCTION CHECKS                                        *
 *** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***/

/**
 * @brief Parse function arguments \n
 *        Gets the first identifier of the function argument and then call type() for type parse
 * @note <arguments> -> ID <type> <arguments_n>
 * @note <arguments> -> eps
 * @return eRC @see returnCodes
 * @post Token may be ready for parsing if the <arguments> -> eps rule was applied (everytime?), check for safety
 */
eRC arguments();

/**
 * @brief Parse next argument of the function \n
 *        Tries to get the token with comma, if comma is not found then it's accepted as an eps state
 * @note <arguments_n> -> , ID <type> <arguments_n>
 * @note <arguments_n> -> eps
 * @return eRC @see returnCodes
 * @post Token may be ready for parsing if the <arguments_n> -> eps rule was applied (everytime?), check for safety
 */
eRC argumentNext();

/**
 * @brief Parse type \n
 *        Parse type of the variable (in function arguments and return types)
 * @note <type> -> int
 * @note <type> -> float64
 * @note <type> -> string
 * @note <type> -> bool
 * @return eRC @see returnCodes
 * @pre Token has to be prepared before calling this function (no getToken call in this function)
 * @post Leaves token as it was -> next function has to call getToken!
 */
eRC type();

/**
 * @brief Parse function return setting \n
 *        Can be empty, () or contain (<types>) -> where <types> can be one type or more
 * @note <func_return> -> ( <f_type> <r_type_n> )
 * @note <func_return> -> eps
 * @return eRC @see returnCodes
 * @pre Expects token to be pre-prepared before calling this function
 * @post This function doesn't prepare token for the next function that will be called
 */
eRC functionReturn();

/**
 * @brief Parse function return type \n
 *        Checking inside of the brackets
 * @note <f_type> -> <type>
 * @note <f_type> -> eps
 * @return eRC @see returnCodes
 * @pre Expects token to be pre-prepared before calling this function
 * @post This function doesn't prepare token for the next function that will be called
 */
eRC functionReturnType();

/**
 * @brief Parse next function return type \n
 *        Check if there is more return types
 * @note <r_type_n> -> <type>
 * @note <r_type_n> -> eps
 * @return eRC @see returnCodes
 * @pre Expects token to be pre-prepared (call of getToken() done before calling this function)
 * @post This function doesn't prepare token for the next function that will be called
 */
eRC functionReturnTypeNext();

/*** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***
 *   COMMANDS FUNCTION CHECK                                     *
 *** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * ***/

/**
 * @brief Parse command block of the function \n
 *        Command block is composed of commands where every command is on the new line (one instruction per line)
 * @note <cmd_block> -> { EOL <commands> } EOL
 * @return eRC @see returnCodes
 * @post Token will be prepared for other processing
 */
eRC commandBlock();

/**
 * @brief Parse one line of commands
 * @note <commands> -> <cmd> EOL <commands>
 * @note <commands> -> eps
 * @return eRC @see returnCodes
 * @post Token will be prepared for other processing
 */
eRC commands();

/**
 * @brief Parse command \n
 *        See notes for acceptable commands
 * @note <cmd> -> ID <statement>
 * @note <cmd> -> if <expression> <cmd_block> else <cmd_block>
 * @note <cmd> -> for <for_definition> ; <expression> ; <for_assignment> <cmd_block>
 * @note <cmd> -> <return_cmd>
 * @return eRC @see returnCodes
 * @pre Expecting token to be pre-prepared
 * @post
 */
eRC command();
// STATEMENTS
eRC statement();
eRC statementMul();
eRC assignment();
eRC unary();
eRC variableIdNext();
// IF
eRC ifElse();
eRC ifElseExpanded();
// FOR
eRC forDefine();
eRC forAssign();
// RETURNS
eRC returnCommand();
eRC returnStatement();

#endif