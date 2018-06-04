%{
    typedef enum  {
        LT = 256,
        LE, EQ, NE, GT, WHILE, DO, ID, NUMBER, RELOP
    } TokenType;
%}
    /*regular expression*/

delim           [ \r\n\t]
ws              {delim}+
letter          [A-Za-z]
digit           [0-9]
id              {letter}({letter}|{digit}|[_])*
double          {digit}+("."{digit}+)([Ee][+\-]?{digit}+)?
hex_digit       [0-9A-Fa-f]
hex             (0[Xx]{hex_digit}+)
decimal         [\-]?{digit}+
string          \"[^"\n]*\"
%%
    /*Rules Section*/  
    /*KeyWords*/
"bool"              {printf("bool");}
"break"             {printf("break");}
"class"             {printf("class");}
"else"              {printf("else");}    
"extends"           {printf("extends");}
"for"               {printf("for");}
"if"                {printf("if");}
"int"               {printf("int");}
"new"               {printf("new");}
"null"              {printf("null");}
"return"            {printf("return");}
"string"            {printf("string");}
"this"              {printf("this");}   
"void"              {printf("void");}
"while"             {printf("while");}
"static"            {printf("static");}
"Print"             {printf("Print");}
"ReadInterger"      {printf("ReadInterger");}
"ReadLine"          {printf("ReadLine");}
"instanceof"        {printf("instanceof");}

    /*reserved*/

    /*constant*/
"true"|"false"      {printf("boolVal");}
{hex}|{decimal}     {printf("intconstant");}
{string}            {printf("(string: %s)", "string");}

    /*operators*/
"+"                 {printf("plus");}
"-"                 {printf("minus");}
"*"                 {printf("multiple");}
"/"                 {printf("divide");}
"%"                 {printf("mod");}
"<"                 {printf("less");}
"<="                {printf("lessequal");}
">"                 {printf("larger");}
">="                {printf("largerequal");}
"="                 {printf("equal");}
"=="                {printf("euqalsto");}
"!="                {printf("notequalsto");}
"&&"                {printf("and");}
"||"                {printf("or");}
"!"                 {printf("not");}
";"                 {printf("semicolon");}
","                 {printf("comma");}
"."                 {printf("dot");}
"["                 {printf("leftBracket");}
"]"                 {printf("rightBracket");}
"("                 {printf("leftParen");}
")"                 {printf("rightParen");}
"{"                 {printf("leFtBrace");}
"}"                 {printf("rightBrace");}

    /*identifiers*/
{ws}                {printf(" ");}
    /* {letter}            {printf("letter");}*/
{id}                {printf("Identifier");}
{double}            {printf("double");}
.                   {printf("myserycharactor");}
%%
    /*Additopn Setion*/
