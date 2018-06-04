 /* File:  scanner.l
  * ----------------
  * Lex input file to generate the scanner for the compiler.
  */

%{

/* The text within this first region delimited by %{ and %} is assumed to
 * be C/C++ code and will be copied verbatim to the lex.yy.c file ahead
 * of the definitions of the yylex() function. Add other header file inclusions
 * or C++ variable declarations/prototypes that are needed by your code here.
 */

#include <string.h>
#include "scanner.h"
#include "utility.h" // for PrintDebug()
#include "errors.h"
#include "parser.h"
#include <vector>

/* Macro: YY_USER_ACTION 
 * ---------------------
 * This flex built-in macro can be defined to provide an action which is
 * always executed prior to any matched rule's action. Basically, it is
 * a way of having a piece of code common to all actions factored out to
 * this routine.  We already defined it for you and left the empty
 * function DoBeforeEachAction ready for your use as needed. It will
 * be called once for each pattern scanned from the file, before
 * executing its action.
 */
static void DoBeforeEachAction(); 
#define YY_USER_ACTION DoBeforeEachAction();

int rowNum = 1;
int colNum = 1;
vector<const char*> savedLines;

%}
                /* define some states */
%x CMT
%x CPY 
%option stack

 /* The section before the first %% is the Definitions section of the lex
  * input file. Here is where you set options for the scanner, define lex
  * states, and can set up definitions to give names to regular expressions
  * as a simple substitution mechanism that allows for more readable
  * entries in the Rules section later. 
  */

delim               [ \r]
ws                  {delim}+
letter              [A-Za-z]
digit               [0-9]
id                  {letter}({letter}|{digit}|"_")*
double              {digit}+("."{digit}*)([Ee][+\-]?{digit}+)?
hex_digit           [0-9A-Fa-f]
hex                 (0[Xx]{hex_digit}+)
decimal             {digit}+
string              \"[^"\n]*\"
wrg_str             \"[^"\n]*
com_sin             "//"[^\n\r]*
com_beg             "/*"
com_end             "*/"
com_multi           "/*[^]**/"
wrg_cmt             "/*"[^\n\r]*


%%             /* BEGIN RULES SECTION */
 /* All patterns and actions should be placed between the start and stop
  * %% markers which delimit the Rules section. 
  */ 
                  /*Rules Section*/ 
<CPY>.*             {/* char curLine[512]; */
                    savedLines.push_back(strdup(yytext));
                    colNum = 1;
                    yy_pop_state();/* once a line to copy */
                    yyless(0);}
<CPY><<EOF>>        {yy_pop_state();}
    /* <*>\n        {rowNum++; */
                    /* colNum = 1；
                    if（YYSTATE == CPY} savedLines.push_back("");
                    else yy_push_state(CPY);} */
 
{com_beg}           {BEGIN(CMT);}                /* enter state CMT */
<CMT>{com_end}      {BEGIN(INITIAL);}            /* quit state CMT */
<CMT>.              {/* skip any charactor */}   
<CMT><<EOF>>        {/*printf("wrong_comment");*/
                        ReportError::UntermComment();}
<*>[\n]             {/*printf("nextline");*/
                    rowNum++;colNum=1;
                    if(YYSTATE == CPY) savedLines.push_back("");
                    else yy_push_state(CPY);}     /* increase the row num anytime */
<*>[\t]             {colNum += 8 - colNum%8 + 1;}                  
                  /*KeyWords*/
"double"            { return T_Double; }
"interface"         { return T_Interface; }
"implements"        { return T_Implements;  }

"bool"              {/*printf("bool");*/return T_Bool;}
"break"             {/* printf("break"); */return T_Break;}
"class"             {/* printf("class"); */return T_Class;}
"else"              {/* printf("else"); */return T_Else;}    
"extends"           {/* printf("extends"); */return T_Extends;}
"for"               {/* printf("for"); */return T_For;}
"if"                {/* printf("if"); */return T_If;}
"int"               {/* printf("int"); */return T_Int;}
"new"               {/* printf("new"); */return T_New;}
"null"              {/* printf("null"); */return T_Null;}
"return"            {/* printf("return"); */return T_Return;}
"string"            {/* printf("string"); */return T_String;}
"this"              {/* printf("this"); */return T_This;}   
"void"              {/* printf("void"); */return T_Void;}
"while"             {/* printf("while"); */return T_While;}
"switch"            { return T_Switch; }
"case"              { return T_Case; }
"default"           { return T_Default; }
    /*"static"            {printf("static");return T_Static;}*/
"NewArray"          { return T_NewArray;    }
"Print"             {/* printf("Print"); */return T_Print;}
"ReadInteger"       {/* printf("ReadInterger"); */return T_ReadInteger;}
"ReadLine"          {/* printf("ReadLine"); */return T_ReadLine;}



                  /*reserved*/

                  /*constant*/
"true"|"false"      {/* printf("boolVal"); */
                        yylval.boolConstant = yytext[0] == 't';
                        return T_BoolConstant;}
{hex}               {/* printf("hex"); */
                        yylval.integerConstant = strtol(yytext,NULL,16);
                        return T_IntConstant;}
{decimal}           {/* printf("intconstant"); */
                        yylval.integerConstant = strtol(yytext,NULL,10);
                        return T_IntConstant;}
{string}            {/* printf("(string: %s)", "string"); */
                        yylval.stringConstant = strdup(yytext);
                        return T_StringConstant;}
{wrg_str}           {/* printf("wrong_string"); */ReportError::UntermString(&yylloc, yytext);}
{double}            {/* printf("double"); */
                        yylval.doubleConstant = strtod(yytext,NULL);
                        return T_DoubleConstant;}

                  /*operators*/
"+"                 {/* printf("plus"); */return yytext[0];}
"-"                 {/* printf("minus"); */return yytext[0];}
"*"                 {/* printf("multiple"); */return yytext[0];}
"/"                 {/* printf("divide"); */return yytext[0];}
"%"                 {/* printf("mod"); */return yytext[0];}
"<"                 {/* printf("less"); */return yytext[0];}
"<="                {/* printf("lessequal"); */return T_LessEqual;}
">"                 {/* printf("larger"); */return yytext[0];}
">="                {/* printf("largerequal"); */return T_GreaterEqual;}
"="                 {/* printf("equal"); */return yytext[0];}
"=="                {/* printf("euqalsto"); */return T_Equal;}
"!="                {/* printf("notequalsto"); */return T_NotEqual;}
"&&"                {/* printf("and"); */return T_And;}
"||"                {/* printf("or"); */return T_Or;}
"!"                 {/* printf("not"); */return yytext[0];}
";"                 {/* printf("semicolon"); */return yytext[0];}
":"                 { return yytext[0]; }
","                 {/* printf("comma"); */return yytext[0];}
"."                 {/* printf("dot"); */return yytext[0];}
"["                 {/* printf("leftBracket"); */return yytext[0];}
"]"                 {/* printf("rightBracket"); */return yytext[0];}
"("                 {/* printf("leftParen"); */return yytext[0];}
")"                 {/* printf("rightParen"); */return yytext[0];}
"{"                 {/* printf("leFtBrace"); */return yytext[0];}
"}"                 {/* printf("rightBrace"); */return yytext[0];}
"[]"                {/* printf("index"); */return T_Dims;}
"--"                { return T_PostMinus; }
"++"                { return T_PostPlus; }
 
    /*identifiers*/
{ws}                {/*skip white space*/}
    /* {letter}            {printf("letter");}*/
{id}                {/* printf("Identifier"); */
                        if (yyleng > MaxIdentLen) {
                            ReportError::LongIdentifier(&yylloc, yytext);
                        }
                            strncpy(yylval.identifier, yytext, MaxIdentLen);
                            return T_Identifier;
                        
                    }
{com_sin}           {/* printf("single comment"); */}
    /* {com_multi}         { printf("multiple comment"); } */
    /* {wrg_cmt}           {printf("wrong_comment"); ReportError::UntermComment();} */
.                   { /*printf("myserycharactor");*/ ReportError::UnrecogChar(&yylloc, yytext[0]);}



%%
  /* The closing %% above marks the end of the Rules section and the beginning
  * of the User Subroutines section. All text from here to the end of the
  * file is copied verbatim to the end of the generated lex.yy.c file.
  * This section is where you put definitions of helper functions.
  */


  /* Function: InitScanner
  * ---------------------
  * This function will be called before any calls to yylex().  It is designed
  * to give you an opportunity to do anything that must be done to initialize
  * the scanner (set global variables, configure starting state, etc.). One
  * thing it already does for you is assign the value of the global variable
  * yy_flex_debug that controls whether flex prints debugging information
  * about each token and what rule was matched. If set to false, no information
  * is printed. Setting it to true will give you a running trail that might
  * be helpful when debugging your scanner. Please be sure the variable is
  * set to false when submitting your final version.
  */
  void InitScanner()
  {
      PrintDebug("lex", "Initializing scanner");
      yy_flex_debug = false;
      BEGIN(INITIAL);
      yy_push_state(CPY);
      rowNum = 1;
      colNum = 1;
  }


  /* Function: DoBeforeEachAction()
  * ------------------------------
  * This function is installed as the YY_USER_ACTION. This is a place
  * to group code common to all actions.
  */
  static void DoBeforeEachAction()
  {
      yylloc.first_line = rowNum;
      yylloc.first_column = colNum;
      yylloc.last_column = colNum + yyleng - 1;
      colNum += yyleng;
  }

  /* Function: GetLineNumbered()
  * ---------------------------
  * Returns string with contents of line numbered n or NULL if the
  * contents of that line are not available.  The scanner that we will
  * release later on will have this implemented for you; for now, feel
  * free to use this stub implementation.
  */
  const char *GetLineNumbered(int num) {
    if (num <= 0 || num > savedLines.size()) return NULL;
    return savedLines[num-1]; 
  }
