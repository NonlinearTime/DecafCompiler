/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 11 "parser.y" /* yacc.c:339  */


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


#line 82 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_Void = 258,
    T_Bool = 259,
    T_Int = 260,
    T_Double = 261,
    T_String = 262,
    T_Class = 263,
    T_LessEqual = 264,
    T_GreaterEqual = 265,
    T_Equal = 266,
    T_NotEqual = 267,
    T_Dims = 268,
    T_PostPlus = 269,
    T_PostMinus = 270,
    T_And = 271,
    T_Or = 272,
    T_Null = 273,
    T_Extends = 274,
    T_This = 275,
    T_Interface = 276,
    T_Implements = 277,
    T_While = 278,
    T_For = 279,
    T_If = 280,
    T_Else = 281,
    T_Return = 282,
    T_Break = 283,
    T_Switch = 284,
    T_Case = 285,
    T_Default = 286,
    T_New = 287,
    T_NewArray = 288,
    T_Print = 289,
    T_ReadInteger = 290,
    T_ReadLine = 291,
    T_Identifier = 292,
    T_StringConstant = 293,
    T_IntConstant = 294,
    T_DoubleConstant = 295,
    T_BoolConstant = 296,
    UMINUS = 297,
    NoElse = 298
  };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_PostPlus 269
#define T_PostMinus 270
#define T_And 271
#define T_Or 272
#define T_Null 273
#define T_Extends 274
#define T_This 275
#define T_Interface 276
#define T_Implements 277
#define T_While 278
#define T_For 279
#define T_If 280
#define T_Else 281
#define T_Return 282
#define T_Break 283
#define T_Switch 284
#define T_Case 285
#define T_Default 286
#define T_New 287
#define T_NewArray 288
#define T_Print 289
#define T_ReadInteger 290
#define T_ReadLine 291
#define T_Identifier 292
#define T_StringConstant 293
#define T_IntConstant 294
#define T_DoubleConstant 295
#define T_BoolConstant 296
#define UMINUS 297
#define NoElse 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "parser.y" /* yacc.c:355  */

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

#line 267 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 298 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  20
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   595

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,     2,     2,    47,     2,     2,
      56,    57,    49,    45,    60,    46,    52,    48,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    61,    55,
      44,    42,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    62,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,     2,    59,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    51,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   184,   184,   196,   197,   200,   201,   202,   203,   206,
     211,   216,   223,   228,   232,   236,   239,   243,   248,   253,
     256,   260,   266,   273,   278,   282,   286,   290,   296,   297,
     298,   299,   300,   304,   308,   309,   311,   317,   324,   328,
     332,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     347,   348,   350,   354,   359,   363,   366,   370,   374,   378,
     381,   385,   388,   393,   397,   402,   406,   410,   414,   418,
     422,   426,   427,   428,   429,   430,   431,   435,   439,   443,
     447,   451,   455,   459,   463,   467,   471,   475,   479,   483,
     487,   491,   492,   493,   498,   502,   506,   511,   517,   521,
     525,   532,   537,   538,   540,   541,   542,   543,   544
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_PostPlus", "T_PostMinus", "T_And", "T_Or",
  "T_Null", "T_Extends", "T_This", "T_Interface", "T_Implements",
  "T_While", "T_For", "T_If", "T_Else", "T_Return", "T_Break", "T_Switch",
  "T_Case", "T_Default", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "'='", "'>'", "'<'", "'+'", "'-'",
  "'%'", "'/'", "'*'", "'!'", "UMINUS", "'.'", "'['", "NoElse", "';'",
  "'('", "')'", "'{'", "'}'", "','", "':'", "']'", "$accept", "Program",
  "DeclList", "Decl", "VariableDecl", "FunctionDecl", "ClassDecl",
  "Fields", "Field", "Extends", "Implement", "Impts", "InterfaceDecl",
  "ProtoTypes", "ProtoType", "Type", "Formals", "ArgList", "StmtBlock",
  "StmtList", "Stmt", "_Expr", "VarDeclList", "IfStmt", "elseStmt",
  "WhileStmt", "ForStmt", "SwitchStmt", "CaseList", "CaseStmt",
  "DefaultStmt", "BreakStmt", "ReturnStmt", "PrintStmt", "Expr",
  "ExprList", "LValue", "Call", "Actuals", "Constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,    61,    62,    60,    43,    45,    37,    47,    42,
      33,   297,    46,    91,   298,    59,    40,    41,   123,   125,
      44,    58,    93
};
# endif

#define YYPACT_NINF -106

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-106)))

#define YYTABLE_NINF -52

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-52)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      93,   -28,  -106,  -106,  -106,  -106,     1,    17,  -106,    15,
      93,  -106,  -106,  -106,  -106,  -106,    -7,    19,    71,    36,
    -106,  -106,  -106,   -24,     7,    65,    91,  -106,  -106,     7,
      21,    47,    60,  -106,    80,    63,    18,    67,  -106,    81,
       7,  -106,    73,  -106,   104,  -106,  -106,    82,    81,  -106,
    -106,    94,   106,    75,    88,    92,  -106,   122,  -106,  -106,
    -106,  -106,  -106,  -106,     7,     7,  -106,  -106,    96,   111,
     115,   539,    98,   118,   136,   119,   120,   123,   130,   -10,
    -106,  -106,  -106,  -106,   539,   539,   539,  -106,    95,  -106,
     128,   473,   133,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
     370,    14,  -106,  -106,   134,   135,   539,   539,   539,   141,
     143,  -106,   539,  -106,   539,   539,   142,   145,   539,    57,
      57,   229,   148,  -106,  -106,  -106,   539,   539,   539,   539,
     539,   539,   539,   539,   539,   539,   539,   539,   539,   167,
     539,  -106,  -106,   539,   150,   151,   244,   152,   293,  -106,
     308,   184,   370,    46,  -106,  -106,   149,   153,  -106,    40,
      40,   426,   426,   437,   381,    40,    40,   117,   117,    57,
      57,    57,   155,   173,   370,  -106,  -106,   512,   539,   512,
     154,     7,   158,   539,  -106,   539,  -106,  -106,   357,   182,
     185,    -5,  -106,   370,   157,   539,   512,  -106,    97,   -26,
    -106,  -106,  -106,   166,  -106,   163,   181,  -106,  -106,   175,
     512,   473,   473,  -106,  -106,  -106,  -106
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    30,    28,    29,    31,     0,     0,    32,     0,
       2,     4,     5,     6,     7,     8,     0,     0,    18,     0,
       1,     3,    33,     0,    35,     0,    20,    25,     9,    35,
       0,     0,    34,    17,     0,     0,     0,     0,    37,     0,
       0,    22,    19,    14,     0,    23,    24,     0,     0,    53,
      11,     0,     0,     0,     0,     0,    10,    40,    36,    21,
      12,    15,    16,    13,    35,    35,   108,    73,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,    97,
     107,   104,   106,   105,     0,     0,     0,    52,     0,    48,
       0,    40,     0,    42,    43,    44,    49,    45,    46,    47,
      50,    72,    74,    71,     0,     0,     0,    51,     0,    97,
       0,    65,     0,    93,     0,     0,     0,     0,   103,    81,
      90,     0,     0,    38,    39,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,    70,     0,     0,     0,     0,     0,     0,    66,
       0,     0,    96,     0,    91,    92,   102,     0,    75,    83,
      85,    86,    87,    88,    89,    84,    82,    76,    77,    80,
      79,    78,    98,     0,    68,    27,    26,    51,     0,    51,
       0,     0,     0,     0,   100,   103,    99,    57,     0,    56,
       0,     0,    67,    95,     0,    51,    51,    54,     0,     0,
      62,    94,   101,     0,    55,     0,     0,    60,    61,     0,
      51,    40,    40,    59,    58,    63,    64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,  -106,   233,   -37,   194,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,     0,   -22,  -106,   -13,   -89,
    -105,   -70,  -106,  -106,  -106,  -106,  -106,  -106,  -106,    49,
    -106,  -106,  -106,  -106,   -67,   137,  -106,  -106,    64,    52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    14,    53,    63,    26,
      35,    42,    15,    36,    46,    30,    31,    32,    89,    90,
      91,    92,    57,    93,   197,    94,    95,    96,   199,   200,
     209,    97,    98,    99,   100,   156,   101,   102,   157,   103
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,   110,   124,   -32,   198,   206,    22,    37,    22,    17,
      16,     2,     3,     4,     5,    20,    61,   119,   120,   121,
      87,    44,     2,     3,     4,     5,    50,   -32,   141,   142,
      23,    28,    29,   207,    22,    56,    47,   147,    18,   146,
      51,   148,   104,   105,     8,   150,   118,   151,   152,   -52,
     -52,   152,   201,    16,    19,     8,   143,    88,    38,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   187,   173,   189,    24,   174,    45,     1,     2,
       3,     4,     5,   -52,   -52,   134,   135,   136,   137,   138,
      25,   204,   139,   140,    27,    22,     1,     2,     3,     4,
       5,     6,    33,   182,    39,   214,   183,    22,    22,   139,
     140,   188,     8,    34,     7,    66,   193,    41,   152,    55,
      40,    43,   215,   216,    48,   203,     2,     3,     4,     5,
       8,    58,   122,    52,    60,    80,    81,    82,    83,    49,
      66,    54,    67,    59,    64,    68,    69,    70,    65,    71,
      72,    73,   106,   111,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,   136,   137,   138,   107,    84,   139,
     140,   108,    85,   113,   112,   114,   115,   -51,    86,   116,
      49,   191,   126,   127,   128,   129,   117,   123,   125,   130,
     131,   144,   145,   126,   127,   128,   129,   118,   149,   154,
     130,   131,   155,    28,   172,   175,   176,   178,   196,   183,
     184,   185,   190,   192,   202,   198,   132,   133,   134,   135,
     136,   137,   138,   210,   211,   139,   140,   132,   133,   134,
     135,   136,   137,   138,   213,   186,   139,   140,   126,   127,
     128,   129,   212,    21,   181,   130,   131,    62,   208,   194,
     205,     0,   153,   126,   127,   128,   129,     0,     0,     0,
     130,   131,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,   133,   134,   135,   136,   137,   138,     0,
       0,   139,   140,     0,     0,     0,   158,   132,   133,   134,
     135,   136,   137,   138,     0,     0,   139,   140,     0,     0,
       0,   177,   126,   127,   128,   129,     0,     0,     0,   130,
     131,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,     0,     0,     0,   130,   131,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   132,   133,   134,   135,
     136,   137,   138,     0,     0,   139,   140,     0,     0,     0,
     179,   132,   133,   134,   135,   136,   137,   138,     0,     0,
     139,   140,     0,     0,     0,   180,   126,   127,   128,   129,
       0,     0,     0,   130,   131,     0,     0,     0,     0,   126,
     127,   128,   129,     0,     0,     0,   130,   131,     0,     0,
     126,   127,   128,   129,     0,     0,     0,   130,     0,     0,
     132,   133,   134,   135,   136,   137,   138,     0,     0,   139,
     140,     0,   195,   132,   133,   134,   135,   136,   137,   138,
       0,     0,   139,   140,   132,   133,   134,   135,   136,   137,
     138,     0,     0,   139,   140,   126,   127,   -52,   -52,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   132,
     133,   134,   135,   136,   137,   138,     0,     0,   139,   140,
     132,   133,   134,   135,   136,   137,   138,     0,     0,   139,
     140,    66,     0,    67,     0,     0,    68,    69,    70,     0,
      71,    72,    73,     0,     0,    74,    75,    76,    77,    78,
     109,    80,    81,    82,    83,     0,     0,     0,     0,    84,
       0,     0,     0,    85,     0,     0,     0,     0,   -51,    86,
      66,    49,    67,     0,     0,    68,    69,    70,     0,    71,
      72,    73,     0,     0,    74,    75,    76,    77,    78,   109,
      80,    81,    82,    83,     0,     0,     0,    66,    84,    67,
       0,     0,    85,     0,     0,     0,     0,     0,    86,     0,
      49,    74,    75,     0,    77,    78,   109,    80,    81,    82,
      83,     0,     0,     0,     0,    84,     0,     0,     0,    85,
       0,     0,     0,     0,     0,    86
};

static const yytype_int16 yycheck[] =
{
       0,    71,    91,    13,    30,    31,    13,    29,    13,    37,
      10,     4,     5,     6,     7,     0,    53,    84,    85,    86,
      57,     3,     4,     5,     6,     7,    39,    37,    14,    15,
      37,    55,    56,    59,    13,    48,    36,   107,    37,   106,
      40,   108,    64,    65,    37,   112,    56,   114,   115,     9,
      10,   118,    57,    53,    37,    37,    42,    57,    37,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   177,   140,   179,    56,   143,    59,     3,     4,
       5,     6,     7,    43,    44,    45,    46,    47,    48,    49,
      19,   196,    52,    53,    58,    13,     3,     4,     5,     6,
       7,     8,    37,    57,    57,   210,    60,    13,    13,    52,
      53,   178,    37,    22,    21,    18,   183,    37,   185,    37,
      60,    58,   211,   212,    57,   195,     4,     5,     6,     7,
      37,    37,    37,    60,    59,    38,    39,    40,    41,    58,
      18,    37,    20,    37,    56,    23,    24,    25,    56,    27,
      28,    29,    56,    55,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    47,    48,    49,    56,    46,    52,
      53,    56,    50,    37,    56,    56,    56,    55,    56,    56,
      58,   181,     9,    10,    11,    12,    56,    59,    55,    16,
      17,    57,    57,     9,    10,    11,    12,    56,    55,    57,
      16,    17,    57,    55,    37,    55,    55,    55,    26,    60,
      57,    56,    58,    55,    57,    30,    43,    44,    45,    46,
      47,    48,    49,    57,    61,    52,    53,    43,    44,    45,
      46,    47,    48,    49,    59,    62,    52,    53,     9,    10,
      11,    12,    61,    10,    60,    16,    17,    53,   199,   185,
     198,    -1,   115,     9,    10,    11,    12,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    52,    53,    -1,    -1,    -1,    57,    43,    44,    45,
      46,    47,    48,    49,    -1,    -1,    52,    53,    -1,    -1,
      -1,    57,     9,    10,    11,    12,    -1,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    44,    45,    46,
      47,    48,    49,    -1,    -1,    52,    53,    -1,    -1,    -1,
      57,    43,    44,    45,    46,    47,    48,    49,    -1,    -1,
      52,    53,    -1,    -1,    -1,    57,     9,    10,    11,    12,
      -1,    -1,    -1,    16,    17,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    -1,    -1,    16,    17,    -1,    -1,
       9,    10,    11,    12,    -1,    -1,    -1,    16,    -1,    -1,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    52,
      53,    -1,    55,    43,    44,    45,    46,    47,    48,    49,
      -1,    -1,    52,    53,    43,    44,    45,    46,    47,    48,
      49,    -1,    -1,    52,    53,     9,    10,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    45,    46,    47,    48,    49,    -1,    -1,    52,    53,
      43,    44,    45,    46,    47,    48,    49,    -1,    -1,    52,
      53,    18,    -1,    20,    -1,    -1,    23,    24,    25,    -1,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    55,    56,
      18,    58,    20,    -1,    -1,    23,    24,    25,    -1,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    18,    46,    20,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      58,    32,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    21,    37,    64,
      65,    66,    67,    68,    69,    75,    78,    37,    37,    37,
       0,    66,    13,    37,    56,    19,    72,    58,    55,    56,
      78,    79,    80,    37,    22,    73,    76,    79,    37,    57,
      60,    37,    74,    58,     3,    59,    77,    78,    57,    58,
      81,    78,    60,    70,    37,    37,    81,    85,    37,    37,
      59,    67,    68,    71,    56,    56,    18,    20,    23,    24,
      25,    27,    28,    29,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    46,    50,    56,    67,    78,    81,
      82,    83,    84,    86,    88,    89,    90,    94,    95,    96,
      97,    99,   100,   102,    79,    79,    56,    56,    56,    37,
      84,    55,    56,    37,    56,    56,    56,    56,    56,    97,
      97,    97,    37,    59,    82,    55,     9,    10,    11,    12,
      16,    17,    43,    44,    45,    46,    47,    48,    49,    52,
      53,    14,    15,    42,    57,    57,    97,    84,    97,    55,
      97,    97,    97,    98,    57,    57,    98,   101,    57,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    37,    97,    97,    55,    55,    57,    55,    57,
      57,    60,    57,    60,    57,    56,    62,    83,    97,    83,
      58,    78,    55,    97,   101,    55,    26,    87,    30,    91,
      92,    57,    57,    84,    83,   102,    31,    59,    92,    93,
      57,    61,    61,    59,    83,    82,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    66,    66,    66,    66,    67,
      68,    68,    69,    70,    70,    71,    71,    72,    72,    73,
      73,    74,    74,    75,    76,    76,    77,    77,    78,    78,
      78,    78,    78,    78,    79,    79,    80,    80,    81,    82,
      82,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      84,    84,    85,    85,    86,    87,    87,    88,    89,    90,
      90,    91,    91,    92,    93,    94,    95,    96,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    98,    98,    99,    99,    99,
     100,   100,   101,   101,   102,   102,   102,   102,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     3,
       6,     6,     7,     2,     0,     1,     1,     2,     0,     2,
       0,     3,     1,     5,     2,     0,     6,     6,     1,     1,
       1,     1,     1,     2,     1,     0,     4,     2,     4,     2,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     2,     0,     6,     2,     0,     5,     9,     8,
       7,     2,     1,     4,     3,     2,     3,     5,     3,     2,
       2,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     2,     6,     3,     1,     1,     3,     4,
       4,     6,     1,     0,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 184 "parser.y" /* yacc.c:1646  */
    { 
                    (yylsp[0]); 
                    /* pp2: The @1 is needed to convince 
                    * yacc to set up yylloc. You can remove 
                    * it once you have other uses of @n*/
                    Program *program = new Program((yyvsp[0].declList));
                    // if no errors, advance to next phase
                    if (ReportError::NumErrors() == 0) 
                    program->Print(0);
                }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 196 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList)=(yyvsp[-1].declList))->Append((yyvsp[0].decl)); }
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 197 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[0].decl)); }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].varDecl); }
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].fnDecl); }
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 202 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].classDecl); }
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 203 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].interfaceDecl); }
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 206 "parser.y" /* yacc.c:1646  */
    { 
                    Identifier *i = new Identifier((yylsp[-1]), (yyvsp[-1].identifier));
                    (yyval.varDecl) = new VarDecl(i, (yyvsp[-2].type));
                }
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 211 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
                    (yyval.fnDecl) = new FnDecl(i, (yyvsp[-5].type), (yyvsp[-2].varList));
                    (yyval.fnDecl)->SetFunctionBody((yyvsp[0].stmtBlock));        
                }
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 216 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
                    Type *t = new Type("void");
                    (yyval.fnDecl) = new FnDecl(i, t, (yyvsp[-2].varList));
                    (yyval.fnDecl)->SetFunctionBody((yyvsp[0].stmtBlock));
                }
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 223 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-5]), (yyvsp[-5].identifier));
                    (yyval.classDecl) = new ClassDecl(i, (yyvsp[-4].namedTpye), (yyvsp[-3].namedTpyeList), (yyvsp[-1].declList));
                }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 228 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.declList) = (yyvsp[-1].declList);
                    (yyval.declList)->Append((yyvsp[0].decl));
                }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 232 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.declList) = new List<Decl*>();
                }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 236 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.decl) = (yyvsp[0].varDecl);
                }
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 239 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.decl) = (yyvsp[0].fnDecl);
                }
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 243 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]),(yyvsp[0].identifier));
                    NamedType *n = new NamedType(i);
                    (yyval.namedTpye) = n;
                }
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 248 "parser.y" /* yacc.c:1646  */
    {
                    /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
                    (yyval.namedTpye) = NULL;
                }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 253 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.namedTpyeList) = (yyvsp[0].namedTpyeList);
                }
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 256 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.namedTpyeList) = new List<NamedType*>();
                }
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 260 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                    NamedType *n = new NamedType(i);
                    (yyval.namedTpyeList) = (yyvsp[-2].namedTpyeList);
                    (yyval.namedTpyeList)->Append(n);
                }
#line 1863 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 266 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                    NamedType *n = new NamedType(i);
                    (yyval.namedTpyeList) = new List<NamedType*>();
                    (yyval.namedTpyeList)->Append(n);
                }
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 273 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-3]), (yyvsp[-3].identifier));
                    (yyval.interfaceDecl) = new InterfaceDecl(i, (yyvsp[-1].declList));
                }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 278 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.declList) = (yyvsp[-1].declList);
                    (yyval.declList)->Append((yyvsp[0].fnDecl));
                }
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 282 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.declList) = new List<Decl*>();
                }
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 286 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
                    (yyval.fnDecl) = new FnDecl(i, (yyvsp[-5].type), (yyvsp[-2].varList));
                }
#line 1909 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 290 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-4]), (yyvsp[-4].identifier));
                    Type *t = new Type("void");
                    (yyval.fnDecl) = new FnDecl(i, t, (yyvsp[-2].varList));
                }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 296 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type("int"); }
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 297 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type("double"); }
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 298 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type("bool"); }
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 299 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new Type("string"); }
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 300 "parser.y" /* yacc.c:1646  */
    { 
                    Identifier *i = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                    (yyval.type) = new NamedType(i);
                }
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 304 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.type) = new ArrayType(Join((yylsp[-1]),(yylsp[0])), (yyvsp[-1].type));
                }
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 308 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = (yyvsp[0].varList); }
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 309 "parser.y" /* yacc.c:1646  */
    { (yyval.varList) = new List<VarDecl*>(); }
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 311 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                    VarDecl *v = new VarDecl(i, (yyvsp[-1].type));
                    (yyval.varList) = (yyvsp[-3].varList);
                    (yyval.varList)->Append(v);
                }
#line 1983 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 317 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                    VarDecl *v = new VarDecl(i, (yyvsp[-1].type));
                    (yyval.varList) = new List<VarDecl*>();
                    (yyval.varList)->Append(v);
                }
#line 1994 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 324 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtBlock) = new StmtBlock((yyvsp[-2].varList), (yyvsp[-1].stmtList));
                }
#line 2002 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 328 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtList) = (yyvsp[0].stmtList);
                    (yyval.stmtList)->InsertAt((yyvsp[-1].stmt),0);
                }
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 332 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtList) = new List<Stmt*>();
                    /* $$->Append($1); */
                }
#line 2020 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 337 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[-1].expr); }
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 338 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].ifStmt); }
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 339 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].whileStmt); }
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 340 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].forStmt); }
#line 2044 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 341 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].breakStmt); }
#line 2050 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 342 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].returnStmt); }
#line 2056 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 343 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].printStmt); }
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 344 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmtBlock); }
#line 2068 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 345 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].switchStmt); }
#line 2074 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 347 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2080 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 348 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new EmptyExpr(); }
#line 2086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 350 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.varList) = (yyvsp[-1].varList);
                    (yyval.varList)->Append((yyvsp[0].varDecl));
                }
#line 2095 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 354 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.varList) = new List<VarDecl*>();
                    /* $$->Append($1); */
                }
#line 2104 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 359 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.ifStmt) = new IfStmt((yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].stmt));
                }
#line 2112 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 363 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmt) = (yyvsp[0].stmt);
                }
#line 2120 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 366 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmt) = NULL;
                }
#line 2128 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 370 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.whileStmt) = new WhileStmt((yyvsp[-2].expr),(yyvsp[0].stmt));
                }
#line 2136 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 374 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forStmt) = new ForStmt((yyvsp[-6].expr),(yyvsp[-4].expr),(yyvsp[-2].expr),(yyvsp[0].stmt));
                }
#line 2144 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 378 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.switchStmt) = new SwitchStmt((yyvsp[-5].expr), (yyvsp[-2].caseList), (yyvsp[-1].defaultStmt));
                }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 381 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.switchStmt) = new SwitchStmt((yyvsp[-4].expr), (yyvsp[-1].caseList), NULL);
                }
#line 2160 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 385 "parser.y" /* yacc.c:1646  */
    {
                    ((yyval.caseList) = (yyvsp[-1].caseList))->Append((yyvsp[0].caseStmt));
                }
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 388 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.caseList) = new List<CaseStmt*> ();
                    (yyval.caseList) -> Append((yyvsp[0].caseStmt));
                }
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 393 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.caseStmt) = new CaseStmt((yyvsp[-2].expr), (yyvsp[0].stmtList));
                }
#line 2185 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 397 "parser.y" /* yacc.c:1646  */
    { 
                    (yyval.defaultStmt) = new DefaultStmt((yyvsp[0].stmtList));
                }
#line 2193 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 402 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.breakStmt) = new BreakStmt((yylsp[-1]));
                }
#line 2201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 406 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.returnStmt) = new ReturnStmt((yylsp[-2]), (yyvsp[-1].expr));
                }
#line 2209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 410 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.printStmt) = new PrintStmt((yyvsp[-2].exprList));
                }
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 414 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "=");
                    (yyval.expr) = new AssignExpr((yyvsp[-2].lValue), op, (yyvsp[0].expr));
                }
#line 2226 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 418 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[0]), "++");
                    (yyval.expr) = new PostfixExpr((yyvsp[-1].lValue),op);               
                }
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 422 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[0]), "--");
                    (yyval.expr) = new PostfixExpr((yyvsp[-1].lValue),op);    
                }
#line 2244 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 426 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2250 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 427 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].lValue); }
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 428 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new This((yylsp[0])); }
#line 2262 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 429 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].call); }
#line 2268 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 430 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2274 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 431 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "+");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 435 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "-");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2292 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 439 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "*");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2301 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 443 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "/");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2310 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 447 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "%");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 451 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "-");
                    (yyval.expr) = new ArithmeticExpr(op, (yyvsp[0].expr));
                }
#line 2328 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 455 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "<");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2337 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 459 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "<=");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 463 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), ">");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2355 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 467 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), ">=");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2364 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 471 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "==");
                    (yyval.expr) = new EqualityExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2373 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 475 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "!=");
                    (yyval.expr) = new EqualityExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 479 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "&&");
                    (yyval.expr) = new LogicalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 483 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator((yylsp[-1]), "||");
                    (yyval.expr) = new LogicalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                }
#line 2400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 487 "parser.y" /* yacc.c:1646  */
    {
                    Operator *op = new Operator(Join((yylsp[-1]),(yylsp[0])), "!");
                    (yyval.expr) = new LogicalExpr(op, (yyvsp[0].expr));
                }
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 491 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ReadIntegerExpr(Join((yylsp[-2]),(yylsp[0]))); }
#line 2415 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 492 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ReadLineExpr(Join((yylsp[-2]),(yylsp[0]))); }
#line 2421 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 493 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]), (yyvsp[0].identifier));
                    NamedType *n = new NamedType(i);
                    (yyval.expr) = new NewExpr(Join((yylsp[-1]),(yylsp[0])), n);
                }
#line 2431 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 498 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.expr) = new NewArrayExpr(Join((yylsp[-5]),(yylsp[-1])), (yyvsp[-3].expr), (yyvsp[-1].type));
                }
#line 2439 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 502 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprList) = (yyvsp[-2].exprList);
                    (yyval.exprList)->Append((yyvsp[0].expr));
                }
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 506 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.exprList) = new List<Expr*>();
                    (yyval.exprList)->Append((yyvsp[0].expr));
                }
#line 2457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 511 "parser.y" /* yacc.c:1646  */
    {
                    /* FieldAccess::FieldAccess(Expr *b, Identifier *f)  */
                    /* b can be be NULL (just means no explicit base) */
                    Identifier *i = new Identifier((yylsp[0]),(yyvsp[0].identifier));
                    (yyval.lValue) = new FieldAccess(NULL,i);
                }
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 517 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[0]),(yyvsp[0].identifier));
                    (yyval.lValue) = new FieldAccess((yyvsp[-2].expr), i);
                }
#line 2477 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 521 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.lValue) = new ArrayAccess(Join((yylsp[-3]),(yylsp[0])), (yyvsp[-3].expr), (yyvsp[-1].expr));
                }
#line 2485 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 525 "parser.y" /* yacc.c:1646  */
    {
                    /* Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  */
                    /* b can be be NULL (just means no explicit base) */
                    Identifier *i = new Identifier((yylsp[-3]),(yyvsp[-3].identifier));
                    (yyval.call) = new Call(Join((yylsp[-3]),(yylsp[0])), NULL , i, (yyvsp[-1].exprList));

                }
#line 2497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 532 "parser.y" /* yacc.c:1646  */
    {
                    Identifier *i = new Identifier((yylsp[-3]), (yyvsp[-3].identifier));
                    (yyval.call) = new Call(Join((yylsp[-5]),(yylsp[0])), (yyvsp[-5].expr), i, (yyvsp[-1].exprList));
                }
#line 2506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 537 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = (yyvsp[0].exprList); }
#line 2512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 538 "parser.y" /* yacc.c:1646  */
    { (yyval.exprList) = new List<Expr *>(); }
#line 2518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 540 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new IntConstant((yylsp[0]), (yyvsp[0].integerConstant)); }
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 541 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BoolConstant((yylsp[0]), (yyvsp[0].boolConstant)); }
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 542 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new DoubleConstant((yylsp[0]), (yyvsp[0].doubleConstant)); }
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 543 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new StringConstant((yylsp[0]), (yyvsp[0].stringConstant)); }
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 544 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new NullConstant((yylsp[0])); }
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2552 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 546 "parser.y" /* yacc.c:1906  */


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
