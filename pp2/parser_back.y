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
    VarDecl *varDecl;
    ClassDecl *classDecl;
    InterfaceDecl *interfaceDecl;
    FnDecl *fnDecl;
    List<Decl*> *declList;
    Type *type;
    List<VarDecl*> *varList;
    NamedType *namedType;
    List<NamedType*> *namedTypeList;
    Stmt *stmt;
    List<Stmt *> *stmtList;
    ConditionalStmt *condStmt;
    LoopStmt *loopStmt;
    ForStmt  *forStmt;
    WhileStmt *whileStmt;
    IfStmt *ifStmt;
    BreakStmt *breakStmt;
    ReturnStmt *returnStmt;
    PrintStmt *printStmt;
    Expr *expr;
    List<Expr *> *exprList;
    LValue *lValue;
    Call *call;
	/*     List<CaseStmt *> *caseList;
		CaseStmt *caseStmt;
		SwitchStmt *switchStmt;
		DefaultStmt *defaultStmt; */
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Bison will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_POSTPLUSPLUS T_POSTMINUSMINUS
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break 
%token   T_Switch T_Case T_Default
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
%type <declList>	DeclList Fields Prototypes
%type <decl>      	Decl Field
%type <varDecl>     	VariableDecl 
%type <fnDecl>          FunctionDecl Prototype
%type <classDecl>	ClassDecl
%type <interfaceDecl>	InterfaceDecl
%type <type>        	Type
%type <varList>         Formals ArgList VariableDeclP
%type <namedTypeList>	IdentifierList Implement
%type <namedType>       Extend
%type <stmt>            Stmt StmtBlock ElseZ
%type <stmtList>        StmtP
%type <expr>            Expr ExprZ Constant
%type <ifStmt>          IfStmt
%type <whileStmt>       WhileStmt
%type <forStmt>         ForStmt
%type <returnStmt>      ReturnStmt
%type <breakStmt>       BreakStmt
%type <printStmt>       PrintStmt
%type <exprList>        ExprList Actuals
%type <lValue>          LValue
%type <call>            Call
	/* %type <switchStmt>      SwitchStmt
	%type <caseStmt>        CaseStmt
	%type <caseList>        CaseList
	%type <defaultStmt>     DefaultStmt DefaultZ */

%right 		      '='
%left  		      T_Or
%left  		      T_And
%nonassoc  	      T_NotEqual T_Equal
%nonassoc  	      T_GreaterEqual '>' T_LessEqual '<'
%left  		      '-' '+'
%left  		      '%' '/' '*' 
%left 		      '!' UMINUS POSTFIX
%left  		      '.'
%left  		      '['

%nonassoc              NoElse
%nonassoc              T_Else


%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   :    DeclList            { 
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

DeclList  :    DeclList Decl        { 
					($$=$1)->Append($2); 
				    }

          |    Decl                 { 
	  	       			($$ = new List<Decl*>)->Append($1);
	       			      	
				    }
          ;

Decl    :      VariableDecl         {
					$$ = $1;
				    }
 
        |      FunctionDecl         {
					$$ = $1;
				    }

	|	ClassDecl           {
					$$ = $1;
				    }

	|	InterfaceDecl       {
					$$ = $1;
				    }
        ;

VariableDecl  :   Type T_Identifier ';'  {
						Identifier *i = new Identifier(@2,$2);
						$$ = new VarDecl(i, $1);
					 }
	      ;

FunctionDecl  :		Type T_Identifier '(' Formals ')' StmtBlock    {
			
				Identifier *i = new Identifier(@2, $2);
				$$ = new FnDecl(i, $1, $4);
				$$->SetFunctionBody($6);
			
			}
	      |   	T_Void T_Identifier '(' Formals ')' StmtBlock  {
			       fflush(stdout);
	      		       Identifier *i = new Identifier(@2,$2);
	      		       Type *v = new Type("void");
			       $$ = new FnDecl(i, v, $4);
			       $$->SetFunctionBody($6);
	      		}
	      ;

ClassDecl     :		T_Class T_Identifier Extend Implement '{' Fields '}' {
	      			Identifier *i= new Identifier(@2,$2);
	      			$$ = new ClassDecl(i, $3, $4, $6);	
	      		}
	      ;

Fields	      :		Fields Field {
	      		($$ = $1)->Append($2);
	      }
	      |		{
	      		$$ = new List<Decl*>();
	      }
	      ;
Field	       :	VariableDecl		{
	       			$$ = $1;
	       		
	       		}
	       |	FunctionDecl		{
	       			$$ = $1;
	       		}
	       ;

Extend        :         T_Extends T_Identifier   {
	      			Identifier *i = new Identifier(@2,$2);
	      			$$ = new NamedType(i);
	      		}
	      |					 {
	      			/* according to the definition of class
				 * this could be NULL 
				 */
	      			$$ = NULL;
			}
	      ;

Implement     :		T_Implements IdentifierList     {
	      		$$ = $2;
	      }
	      |						{
	      		$$ = new List<NamedType *>();
	      }
	      ;

IdentifierList :	IdentifierList ',' T_Identifier  {
	       		Identifier *i = new Identifier(@3,$3);
	       		NamedType *nt = new NamedType(i);
			($$ = $1)->Append(nt);
	       }
	       |	T_Identifier		      {
	       		Identifier *i = new Identifier(@1,$1);
	       		NamedType *nt = new NamedType(i);
			($$ = new List<NamedType *>())->Append(nt);
	       }
	       ;


InterfaceDecl  :	T_Interface T_Identifier '{' Prototypes '}' {
	       			    Identifier *i = new Identifier(@2, $2);
				    $$ = new InterfaceDecl(i, $4);				    
	       		}
               ;

Prototypes     :	Prototypes Prototype	{
	       			   ($$ = $1)->Append($2);
	       		}
	       |		   		{
	       			   $$ = new List<Decl *>();
	       		}
	       ;

Prototype      :	Type T_Identifier '(' Formals ')' ';'      {
	       		     Identifier *i = new Identifier(@2, $2);
			     $$ = new FnDecl(i, $1, $4);
	       		}
	       | 	T_Void T_Identifier '(' Formals ')' ';'	   {
	       		     Identifier *i = new Identifier(@2, $2);
			     Type *t = new Type("void");
			     $$ = new FnDecl(i, t, $4);
	       		}
	       ;

Type          :   T_Int             {
					$$ = new Type("int");
	      	  		    }
              |	  T_Double          {	
	      	  		    	$$ = new Type("double");
				    }
	      |	  T_Bool            {
					$$ = new Type("bool");
				    }
	      |	  T_String          {
					$$ = new Type("string");
				    }
	      |	  T_Identifier      {				
	      	  		    	Identifier *i = new Identifier(@1,$1);	
					$$ = new NamedType(i);
	      	  		    }
	      |	  Type T_Dims       {
					$$ = new ArrayType(@1, $1);
	      	       		    }
              ; 

Formals	      :		ArgList		{
						$$ = $1;
	      				}
	      |				{
						$$ = new List<VarDecl *>();;
					}
	      ;

ArgList	      :		ArgList ',' Type T_Identifier	{
	      			Identifier *i = new Identifier(@4,$4);
	      			VarDecl *v = new VarDecl(i, $3);
				($$ = $1)->Append(v);
	      		}
	      |		Type T_Identifier  		{
	      		        Identifier *i = new Identifier(@2,$2);
	      		     	VarDecl *v = new VarDecl(i, $1);
	      		     	($$ = new List<VarDecl *>)->
				    Append(v);
	      		}
	      ;

StmtBlock      :	'{' VariableDeclP StmtP '}'	{
	       		    $$ = new StmtBlock($2, $3);
	       		}
	       |	'{' VariableDeclP '}'		{
	       		    List<Stmt *> *stmt = new List<Stmt *>();
	       		    $$ = new StmtBlock($2, stmt);
	       		}
	       | 	'{' StmtP '}'	  		{
	       		    List<VarDecl *> *vl = new List<VarDecl *>();
	       		    $$ = new StmtBlock(vl, $2);
	       		}
	       |	'{' '}'	  			{
	       		    List<VarDecl *> *vl = new List<VarDecl *>();
			    List<Stmt *> *sl = new List<Stmt *>();
			    $$ = new StmtBlock(vl, sl);
	       		}
	       ;

VariableDeclP  :	VariableDeclP VariableDecl		{
	       		    ($$=$1)->Append($2);
	       		}
	       |      	VariableDecl	 	  		{
	       		    ($$ = new List<VarDecl *>())->Append($1);
	       		}
	       ;

StmtP	       :	StmtP Stmt		{
	       		    ($$=$1)->Append($2);
	       		}
	       |	Stmt	 		{
	       		    ($$ = new List<Stmt *>())->Append($1);
	       		}
	       ;

Stmt		 :	ExprZ ';'		{
		 	    $$ = $1;
		 	}
		 |	IfStmt			{
		 	    $$ = $1;
		 	}
		 |	WhileStmt		{
		 	    $$ = $1;
		 	}
		 |	ForStmt			{
		 	    $$ = $1;
		 	}
	/* 		 |      SwitchStmt              {
					$$ = $1;
				} */
		 |	BreakStmt		{
		 	    $$ = $1;
		 	}
		 |	ReturnStmt		{
		 	    $$ = $1;
		 	}
		 |	PrintStmt		{
		 	    $$ = $1;
		 	}
		 |	StmtBlock		{
		 	    $$ = $1;
		 	}
		 ;

ExprZ		 :	Expr			{
		 	    $$ = $1;
		 	}
		 |				{
		 	    $$ = new EmptyExpr();
		 	}
		 ;

IfStmt		 :	T_If '(' Expr ')' Stmt ElseZ	{
		 	    $$ = new IfStmt($3, $5, $6);
		 	}
		 ;

ElseZ		 :	T_Else Stmt  %prec T_Else		{
		 	    $$ = $2;
		 	}
		 |	       	     %prec NoElse		{
		  	    $$ = NULL;
		 	}
		 ;

	/* SwitchStmt       :      T_Switch '(' Expr ')' '{' CaseList DefaultZ '}' {
					$$ = new SwitchStmt($3, $6, $7);
				} 
			;

	CaseList         :      CaseList CaseStmt {
					($$ = $1)->Append($2);
				}
			|	CaseStmt {
					($$ = new List<CaseStmt *>())->Append($1);
				}
			;			

	CaseStmt         :      T_Case Constant ':' StmtP {
					$$ = new CaseStmt($2,$4);
				}
			|      T_Case Constant ':' {
					$$ = new CaseStmt($2, NULL);
				}
			;

	DefaultStmt      :      T_Default ':' StmtP {
					$$ = new DefaultStmt($3);
				}
			|      T_Default ':' {
					$$ = new DefaultStmt(NULL);
				}
			; */

	/* DefaultZ         :      DefaultStmt {
					$$ = $1;
				}
			|      {
					$$ = NULL;
				} */
 
WhileStmt	 :	T_While	'(' Expr ')' Stmt	{
		 	    $$ = new WhileStmt($3, $5);
		 	}
		 ;

ForStmt		 :	T_For '(' ExprZ ';' Expr ';' ExprZ ')' Stmt  {
		 	    $$ = new ForStmt($3, $5, $7, $9);
		 	}
		 ;

ReturnStmt	 :	T_Return ExprZ ';'		{
		 	    $$ = new ReturnStmt(@1, $2);
		 	}
		 ;

BreakStmt	 :	T_Break ';'			{
		 	    $$ = new BreakStmt(@1);
		 	}
		 ;

PrintStmt	 :	T_Print	'(' ExprList ')' ';'	{
		 	    $$ = new PrintStmt($3);
		 	}
		 ;

Expr		 :	LValue '=' Expr	                {
		 	    Operator *op = new Operator(@2, "=");
		 	    $$ = new AssignExpr($1, op, $3);
		 	}
		 /* |      LValue T_POSTPLUSPLUS %prec POSTFIX          {
		 	    Operator *op = new Operator(@2, "++");
			    $$ = new PostfixExpr($1, op);
		 	} */
		 /* |      LValue T_POSTMINUSMINUS  %prec POSTFIX       {
		 	    Operator *op = new Operator(@2, "--");
			    $$ = new PostfixExpr($1, op);
		 	} */
		 	
		 | 	Constant   			{
			    $$ = $1;    
		 	}
		 | 	LValue				{
		 	    $$ = $1;
		 	}
		 |	T_This				{
		 	    $$ = new This(@1);
		 	}
		 |	Call				{
		 	    $$ = $1;
		 	}
		 |	'(' Expr ')'			{
		 	    $$ = $2;
		 	}	
		 |	Expr '+' Expr			{
		 	    Operator *op = new Operator(@2, "+");
		 	    $$ = new ArithmeticExpr($1, op, $3);
		 	}
		 |	Expr '-' Expr			{
		 	    Operator *op = new Operator(@2, "-");
			    $$ = new ArithmeticExpr($1, op, $3);
		 	}
		 |	Expr '/' Expr			{
		 	    Operator *op = new Operator(@2, "/");
			    $$ = new ArithmeticExpr($1, op, $3);
		 	}
		 |      Expr '*' Expr                   {
		  	    Operator *op = new Operator(@2, "*");
			    $$ = new ArithmeticExpr($1, op, $3);
		 	}
		 |	Expr '%' Expr			{
 	    		Operator *op = new Operator(@2, "%");
			    $$ = new ArithmeticExpr($1, op, $3);

		 	}
		 |	'-' Expr %prec UMINUS		{
		 	    Operator *op = new Operator(@1, "-");
			    $$ = new ArithmeticExpr(op, $2);
		 	}
		 |	Expr '<' Expr			{
		 	    Operator *op = new Operator(@2, "<");
			    $$ = new RelationalExpr($1, op, $3);
		 	}
		 |	Expr T_LessEqual Expr		{
		 	    Operator *op = new Operator(@2, "<=");
			    $$ = new RelationalExpr($1, op, $3);
		 	}
		 |	Expr '>' Expr	 		{
		 	    Operator *op = new Operator(@2, ">");
			    $$ = new RelationalExpr($1, op, $3);
		 	}
		 |	Expr T_GreaterEqual Expr	{
		 	    Operator *op = new Operator(@2, ">=");
			    $$ = new RelationalExpr($1, op, $3);
		 	}
		 |	Expr T_Equal Expr   		{
		 	    Operator *op = new Operator(@2, "==");	
			    $$ = new EqualityExpr($1, op, $3);
			}
		 |	Expr T_NotEqual Expr		{
		 	    Operator *op = new Operator(@2, "!=");
			    $$ = new EqualityExpr($1, op, $3);
		 	}
		 |	Expr T_And Expr			{
		 	    Operator *op = new Operator(@2, "&&");
			    $$ = new LogicalExpr($1, op, $3);
		 	}
		 |	Expr T_Or Expr			{
		 	    Operator *op = new Operator(@2, "||");
			    $$ = new LogicalExpr($1, op, $3);
		 	}
		 |	'!' Expr  			{
		 	    Operator *op = new Operator(@2, "!");
			    $$ = new LogicalExpr(op, $2);
		 	}
		 |	T_ReadInteger '(' ')'		{
  		 	    $$ = new ReadIntegerExpr(@1);
		 	}
		 |	T_ReadLine '(' ')'		{
		  	    $$ = new ReadLineExpr(@1);
		 	}
		 |	T_New T_Identifier		{
		 	    Identifier *i = new Identifier(@2, $2);
			    NamedType *nt = new NamedType(i);
			    $$ = new NewExpr(@1, nt);
		 	}
		 |	T_NewArray '(' Expr ',' Type ')' {
		 	    $$ = new NewArrayExpr(@1, $3, $5);
		 	}
		 ;

LValue		 :	T_Identifier		{
		 	    Identifier *i = new Identifier(@1, $1);
			    $$ = new FieldAccess(NULL, i);
			    
		 	}
		 |	Expr '.' T_Identifier	{
		 	    Identifier *i = new Identifier(@3, $3);
			    $$ = new FieldAccess($1, i);
		 	}
		 | 	Expr '[' Expr ']'	{
		 	    $$ = new ArrayAccess(@1, $1, $3);
		 	}
		 ;
		 
Call		 :	T_Identifier '(' Actuals ')'	{
		 	    Identifier *i = new Identifier(@1, $1);
			    $$ = new Call(@1, NULL, i, $3);
		 	}
		 |	Expr '.' T_Identifier '(' Actuals ')'	{
		 	    Identifier *i = new Identifier(@3, $3);
			    $$ = new Call(@1, $1, i, $5);
		 	}
		 ;

Actuals		 :	ExprList	{
		 	    $$ = $1;
		 	}
		 |			{
		 	    $$ = new List<Expr *>();
		 	}
		 ;
ExprList	 :	ExprList ',' Expr	{
		 	    ($$ = $1)->Append($3);
		 	}
		 | 	Expr			{
		 	    ($$ = new List<Expr *>())->Append($1);
		 	}
		 ;

Constant	 :	T_IntConstant		{
		 	    $$ = new IntConstant(@1, $1);
		 	}
		 |	T_DoubleConstant	{
		 	    $$ = new DoubleConstant(@1, $1);
		 	}
		 |	T_BoolConstant		{
		 	    $$ = new BoolConstant(@1, $1);
		 	}
		 |	T_StringConstant	{
		 	    $$ = new StringConstant(@1, $1);
		 	}
		 |	T_Null			{
		 	    $$ = new NullConstant(@1);
		 	}
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
