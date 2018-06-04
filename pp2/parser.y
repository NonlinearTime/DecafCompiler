/* File: parser.y
 * --------------
 * Bison input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    
    Decl *decl;
    List<Decl*> *declList;
    VarDecl *varDecl;
    ClassDecl *classDecl;
    InterfaceDecl *interfaceDecl;
    FnDecl * fnDecl;
    List<VarDecl*> *varList;

    Type *type;
    NamedType *namedTpye;
    ArrayType *arrayType;
    List<Type*> *typeList;
    List<NamedType*> *namedTpyeList;

    Expr *expr;
    EmptyExpr *emptyExpr;
    NullConstant *nullConstant;
    Operator *op;
    CompoundExpr *compoundExpr;
    ArithmeticExpr *arithmeticExpr;
    RelationalExpr *relationalExpr;
    EqualityExpr *equalityExpr;
    LogicalExpr *logicalExpr;
    AssignExpr *assignExpr;
    LValue *lValue;
    This *_this;
    ArrayAccess *arrayAccess;
    FieldAccess *filedAccess;
    Call *call;
    NewExpr *newExpr;
    NewArrayExpr *newArrayExpr;
    ReadIntegerExpr *readIntegerExpr;
    ReadLineExpr *readLineExpr;
    List<Expr*> *exprList;

    Stmt *stmt;
    StmtBlock *stmtBlock;
    ConditionalStmt *conditionalStmt;
    LoopStmt *loopStmt;
    ForStmt *forStmt;
    WhileStmt *whileStmt;
    IfStmt *ifStmt;
    BreakStmt *breakStmt;
    ReturnStmt *returnStmt;
    PrintStmt *printStmt;
    List<Stmt*> *stmtList;
    SwitchStmt *switchStmt;
    CaseStmt *caseStmt;
    DefaultStmt *defaultStmt;
    List<CaseStmt*> *caseList;
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Bison will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims T_PostPlus T_PostMinus
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break T_Switch T_Case T_Default
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <declList>            DeclList ProtoTypes Fields
%type <decl>                Decl Field
%type <varDecl>             VariableDecl
%type <fnDecl>              FunctionDecl ProtoType
%type <classDecl>           ClassDecl
%type <interfaceDecl>       InterfaceDecl
%type <type>                Type
%type <namedTpye>           Extends
%type <namedTpyeList>       Impts Implement              
%type <varList>             Formals ArgList VarDeclList  /* VarDeclList actually */

%type <stmtBlock>           StmtBlock   
%type <stmtList>            StmtList
%type <stmt>                Stmt elseStmt
%type <ifStmt>              IfStmt
%type <whileStmt>           WhileStmt
%type <breakStmt>           BreakStmt
%type <returnStmt>          ReturnStmt
%type <forStmt>             ForStmt
%type <printStmt>           PrintStmt
%type <switchStmt>          SwitchStmt
%type <caseStmt>            CaseStmt
%type <defaultStmt>         DefaultStmt 
%type <caseList>            CaseList

%type <expr>                Expr _Expr Constant
%type <exprList>            ExprList Actuals
%type <lValue>              LValue
%type <call>                Call



%right                      '='
%left                       T_Or
%left                       T_And
%nonassoc                   T_Equal T_NotEqual
%nonassoc                   T_GreaterEqual T_LessEqual '>' '<'
%left                       '+' '-'
%left                       '%' '/' '*'
%left                       '!' UMINUS T_PostMinus T_PostPlus
%left                       '.' '['

%nonassoc                   NoElse
%nonassoc                   T_Else


%%  
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program         :   DeclList                { 
                    @1; 
                    /* pp2: The @1 is needed to convince 
                    * yacc to set up yylloc. You can remove 
                    * it once you have other uses of @n*/
                    Program *program = new Program($1);
                    // if no errors, advance to next phase
                    if (ReportError::NumErrors() == 0) 
                    program->Print(0);
                }
                ;

DeclList        :   DeclList Decl           { ($$=$1)->Append($2); }
                |   Decl                    { ($$ = new List<Decl*>)->Append($1); }
                ;

Decl            :   VariableDecl            { $$ = $1; } 
                |   FunctionDecl            { $$ = $1; }    
                |   ClassDecl               { $$ = $1; }
                |   InterfaceDecl           { $$ = $1; }
                ;

VariableDecl    :   Type T_Identifier ';'   { 
                    Identifier *i = new Identifier(@2, $2);
                    $$ = new VarDecl(i, $1);
                }
                ;
FunctionDecl    :   Type T_Identifier '(' Formals ')' StmtBlock {
                    Identifier *i = new Identifier(@2, $2);
                    $$ = new FnDecl(i, $1, $4);
                    $$->SetFunctionBody($6);        
                }
                |   T_Void T_Identifier '(' Formals ')' StmtBlock {
                    Identifier *i = new Identifier(@2, $2);
                    Type *t = new Type("void");
                    $$ = new FnDecl(i, t, $4);
                    $$->SetFunctionBody($6);
                }
                ;
ClassDecl       :   T_Class T_Identifier Extends Implement '{' Fields '}' {
                    Identifier *i = new Identifier(@2, $2);
                    $$ = new ClassDecl(i, $3, $4, $6);
                }
                ;
Fields          :   Fields Field            {
                    $$ = $1;
                    $$->Append($2);
                }
                |                           {
                    $$ = new List<Decl*>();
                }
                ;
Field           :   VariableDecl            {
                    $$ = $1;
                }
                |   FunctionDecl            {
                    $$ = $1;
                }
                ;
Extends         :   T_Extends T_Identifier  {
                    Identifier *i = new Identifier(@2,$2);
                    NamedType *n = new NamedType(i);
                    $$ = n;
                }
                |                           {
                    /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
                    $$ = NULL;
                }
                ;
Implement       :   T_Implements Impts {
                    $$ = $2;
                }
                |                           {
                    $$ = new List<NamedType*>();
                }
                ;
Impts           :   Impts ',' T_Identifier {
                    Identifier *i = new Identifier(@3, $3);
                    NamedType *n = new NamedType(i);
                    $$ = $1;
                    $$->Append(n);
                }
                |   T_Identifier                {
                    Identifier *i = new Identifier(@1, $1);
                    NamedType *n = new NamedType(i);
                    $$ = new List<NamedType*>();
                    $$->Append(n);
                }
                ;
InterfaceDecl   :   T_Interface T_Identifier '{' ProtoTypes '}' {
                    Identifier *i = new Identifier(@2, $2);
                    $$ = new InterfaceDecl(i, $4);
                }
                ;   
ProtoTypes      :   ProtoTypes ProtoType    {
                    $$ = $1;
                    $$->Append($2);
                }
                |                           {
                    $$ = new List<Decl*>();
                }
                ;
ProtoType       :   Type T_Identifier '(' Formals ')' ';'   {
                    Identifier *i = new Identifier(@2, $2);
                    $$ = new FnDecl(i, $1, $4);
                }
                |   T_Void T_Identifier '(' Formals ')' ';'  {
                    Identifier *i = new Identifier(@2, $2);
                    Type *t = new Type("void");
                    $$ = new FnDecl(i, t, $4);
                }
                ;
Type            :   T_Int                   { $$ = new Type("int"); }
                |   T_Double                { $$ = new Type("double"); }
                |   T_Bool                  { $$ = new Type("bool"); }
                |   T_String                { $$ = new Type("string"); }
                |   T_Identifier            { 
                    Identifier *i = new Identifier(@1, $1);
                    $$ = new NamedType(i);
                }
                |   Type T_Dims             {
                    $$ = new ArrayType(Join(@1,@2), $1);
                }
                ;
Formals         :   ArgList                 { $$ = $1; }
                |                           { $$ = new List<VarDecl*>(); }
                ;
ArgList         :   ArgList ',' Type T_Identifier   {
                    Identifier *i = new Identifier(@4, $4);
                    VarDecl *v = new VarDecl(i, $3);
                    $$ = $1;
                    $$->Append(v);
                }
                |   Type T_Identifier       {
                    Identifier *i = new Identifier(@2, $2);
                    VarDecl *v = new VarDecl(i, $1);
                    $$ = new List<VarDecl*>();
                    $$->Append(v);
                }
                ;
StmtBlock       :   '{' VarDeclList StmtList '}'    {
                    $$ = new StmtBlock($2, $3);
                }
                ;
StmtList        :   Stmt StmtList           {
                    $$ = $2;
                    $$->InsertAt($1,0);
                }
                |   /* Stmt */                    {
                    $$ = new List<Stmt*>();
                    /* $$->Append($1); */
                }
                ;
Stmt            :   _Expr ';'               { $$ = $1; }
                |   IfStmt                  { $$ = $1; }
                |   WhileStmt               { $$ = $1; }
                |   ForStmt                 { $$ = $1; }
                |   BreakStmt               { $$ = $1; }
                |   ReturnStmt              { $$ = $1; }
                |   PrintStmt               { $$ = $1; }
                |   StmtBlock               { $$ = $1; }
                |   SwitchStmt              { $$ = $1; }
                ;
_Expr           :   Expr                    { $$ = $1; }
                |                           { $$ = new EmptyExpr(); }
                ;
VarDeclList     :   VarDeclList VariableDecl {
                    $$ = $1;
                    $$->Append($2);
                }
                |   /* VariableDecl */             {
                    $$ = new List<VarDecl*>();
                    /* $$->Append($1); */
                }
                ;
IfStmt          :   T_If '(' Expr ')' Stmt elseStmt     {
                    $$ = new IfStmt($3, $5, $6);
                }
                ;
elseStmt        :   T_Else Stmt %prec T_Else {
                    $$ = $2;
                }
                |   %prec NoElse             {
                    $$ = NULL;
                }
                ;
WhileStmt       :   T_While '(' Expr ')' Stmt {
                    $$ = new WhileStmt($3,$5);
                }
                ;
ForStmt         :   T_For '(' _Expr ';' Expr ';' _Expr ')' Stmt {
                    $$ = new ForStmt($3,$5,$7,$9);
                }
                ;
SwitchStmt      :   T_Switch '(' Expr ')' '{' CaseList DefaultStmt '}' {
                    $$ = new SwitchStmt($3, $6, $7);
                }
                |   T_Switch '(' Expr ')' '{' CaseList '}' {
                    $$ = new SwitchStmt($3, $6, NULL);
                }
                ;
CaseList        :   CaseList CaseStmt {
                    ($$ = $1)->Append($2);
                }
                |   CaseStmt {
                    $$ = new List<CaseStmt*> ();
                    $$ -> Append($1);
                }
                ;
CaseStmt        :   T_Case  Constant ':' StmtList {
                    $$ = new CaseStmt($2, $4);
                }
                ;
DefaultStmt     :   T_Default ':' StmtList  { 
                    $$ = new DefaultStmt($3);
                }
                ;

BreakStmt       :   T_Break ';'             {
                    $$ = new BreakStmt(@1);
                }
                ;
ReturnStmt      :   T_Return _Expr ';'      {
                    $$ = new ReturnStmt(@1, $2);
                }
                ;
PrintStmt       :   T_Print '(' ExprList ')' ';' {
                    $$ = new PrintStmt($3);
                }
                ;
Expr            :   LValue '=' Expr         {
                    Operator *op = new Operator(@2, "=");
                    $$ = new AssignExpr($1, op, $3);
                }
                |   LValue T_PostPlus       {
                    Operator *op = new Operator(@2, "++");
                    $$ = new PostfixExpr($1,op);               
                }   
                |   LValue T_PostMinus      {
                    Operator *op = new Operator(@2, "--");
                    $$ = new PostfixExpr($1,op);    
                }
                |   Constant                { $$ = $1; }
                |   LValue                  { $$ = $1; }
                |   T_This                  { $$ = new This(@1); }
                |   Call                    { $$ = $1; }
                |   '(' Expr ')'            { $$ = $2; }
                |   Expr '+' Expr           {
                    Operator *op = new Operator(@2, "+");
                    $$ = new ArithmeticExpr($1, op, $3);
                }
                |   Expr '-' Expr           {
                    Operator *op = new Operator(@2, "-");
                    $$ = new ArithmeticExpr($1, op, $3);
                }
                |   Expr '*' Expr           {
                    Operator *op = new Operator(@2, "*");
                    $$ = new ArithmeticExpr($1, op, $3);
                }
                |   Expr '/' Expr           {
                    Operator *op = new Operator(@2, "/");
                    $$ = new ArithmeticExpr($1, op, $3);
                }
                |   Expr '%' Expr           {
                    Operator *op = new Operator(@2, "%");
                    $$ = new ArithmeticExpr($1, op, $3);
                }
                |   '-' Expr %prec UMINUS   {
                    Operator *op = new Operator(@1, "-");
                    $$ = new ArithmeticExpr(op, $2);
                }
                |   Expr '<' Expr           {
                    Operator *op = new Operator(@2, "<");
                    $$ = new RelationalExpr($1, op, $3);
                }
                |   Expr T_LessEqual Expr   {
                    Operator *op = new Operator(@2, "<=");
                    $$ = new RelationalExpr($1, op, $3);
                }
                |   Expr '>' Expr           {
                    Operator *op = new Operator(@2, ">");
                    $$ = new RelationalExpr($1, op, $3);
                }
                |   Expr T_GreaterEqual Expr    {
                    Operator *op = new Operator(@2, ">=");
                    $$ = new RelationalExpr($1, op, $3);
                }
                |   Expr T_Equal Expr       {
                    Operator *op = new Operator(@2, "==");
                    $$ = new EqualityExpr($1, op, $3);
                }
                |   Expr T_NotEqual Expr    {
                    Operator *op = new Operator(@2, "!=");
                    $$ = new EqualityExpr($1, op, $3);
                }
                |   Expr T_And  Expr        {
                    Operator *op = new Operator(@2, "&&");
                    $$ = new LogicalExpr($1, op, $3);
                }
                |   Expr T_Or   Expr        {
                    Operator *op = new Operator(@2, "||");
                    $$ = new LogicalExpr($1, op, $3);
                }
                |   '!' Expr                {
                    Operator *op = new Operator(Join(@1,@2), "!");
                    $$ = new LogicalExpr(op, $2);
                }
                |   T_ReadInteger '(' ')'   { $$ = new ReadIntegerExpr(Join(@1,@3)); }
                |   T_ReadLine '(' ')'      { $$ = new ReadLineExpr(Join(@1,@3)); }
                |   T_New T_Identifier      {
                    Identifier *i = new Identifier(@2, $2);
                    NamedType *n = new NamedType(i);
                    $$ = new NewExpr(Join(@1,@2), n);
                }
                |   T_NewArray '(' Expr ',' Type ')'    {
                    $$ = new NewArrayExpr(Join(@1,@5), $3, $5);
                }
                ;
ExprList        :   ExprList ',' Expr       {
                    $$ = $1;
                    $$->Append($3);
                }
                |   Expr                    {
                    $$ = new List<Expr*>();
                    $$->Append($1);
                }
                ;
LValue          :   T_Identifier            {
                    /* FieldAccess::FieldAccess(Expr *b, Identifier *f)  */
                    /* b can be be NULL (just means no explicit base) */
                    Identifier *i = new Identifier(@1,$1);
                    $$ = new FieldAccess(NULL,i);
                }
                |   Expr '.' T_Identifier   {
                    Identifier *i = new Identifier(@3,$3);
                    $$ = new FieldAccess($1, i);
                }
                |   Expr '[' Expr ']'       {
                    $$ = new ArrayAccess(Join(@1,@4), $1, $3);
                }
                ;
Call            :   T_Identifier '(' Actuals ')'    {
                    /* Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  */
                    /* b can be be NULL (just means no explicit base) */
                    Identifier *i = new Identifier(@1,$1);
                    $$ = new Call(Join(@1,@4), NULL , i, $3);

                }
                |   Expr '.' T_Identifier '(' Actuals ')'  {
                    Identifier *i = new Identifier(@3, $3);
                    $$ = new Call(Join(@1,@6), $1, i, $5);
                }
                ;
Actuals         :   ExprList                { $$ = $1; }
                |                           { $$ = new List<Expr *>(); }
                ;   
Constant        :   T_IntConstant           { $$ = new IntConstant(@1, $1); }
                |   T_BoolConstant          { $$ = new BoolConstant(@1, $1); }
                |   T_DoubleConstant        { $$ = new DoubleConstant(@1, $1); }
                |   T_StringConstant        { $$ = new StringConstant(@1, $1); }
                |   T_Null                  { $$ = new NullConstant(@1); }
                ;
%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
