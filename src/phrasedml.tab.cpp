/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         phrased_yyparse
#define yylex           phrased_yylex
#define yyerror         phrased_yyerror
#define yylval          phrased_yylval
#define yychar          phrased_yychar
#define yydebug         phrased_yydebug
#define yynerrs         phrased_yynerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 26 "phrasedml.ypp"

  //#define YYSTYPE double
#include <cassert>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>
#ifndef NSBML
#include <sbml/SBMLTypes.h>
#endif
#include "registry.h"
//#include "module.h"
//#include "unitdef.h"
//#include "stringx.h"

  class ModelChange;

  using namespace std;
  int phrased_yylex(void);
  void phrased_yyerror(char const *);
  Registry g_registry;
  int phrased_yylloc_last_line = 1;

/* Line 371 of yacc.c  */
#line 103 "phrasedml.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int phrased_yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     YYEOF = 0,
     NUM = 259,
     PHRASEWORD = 260,
     TEXTSTRING = 261,
     ERROR = 262
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 55 "phrasedml.ypp"

  char character;
  const string* word;
  vector<const string*>* words;
  vector<string>* wordstr;
  vector<vector<const string*>* >* nameslist;
  double number;
  vector<double>* nums;
  vector<ModelChange>* changelist;


/* Line 387 of yacc.c  */
#line 162 "phrasedml.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE phrased_yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int phrased_yyparse (void *YYPARSE_PARAM);
#else
int phrased_yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int phrased_yyparse (void);
#else
int phrased_yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 190 "phrasedml.tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   200

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   262

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,     2,     2,    10,     4,     2,
      21,    22,     8,     7,    18,     6,    16,     9,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    26,
      24,    17,    23,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    19,     2,    20,    11,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     5,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,    12,
      13,    14,    15
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     8,    12,    16,    19,    22,    25,
      27,    31,    36,    43,    51,    61,    66,    73,    80,    88,
      98,   107,   115,   119,   124,   130,   137,   144,   150,   156,
     161,   167,   174,   182,   191,   200,   208,   216,   217,   219,
     223,   228,   232,   234,   237,   238,   241,   245,   247,   251,
     252,   255,   258,   263,   266,   270,   274,   277,   282,   284,
     288,   290,   292,   294,   296,   298,   300,   302,   304,   306,
     308,   310
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      29,     0,    -1,    -1,    29,    31,    42,    -1,    29,    34,
      42,    -1,    29,    35,    42,    -1,    29,    42,    -1,    29,
       1,    -1,    29,    15,    -1,    13,    -1,    30,    16,    13,
      -1,    30,    17,    30,    14,    -1,    30,    17,    30,    14,
      30,    32,    -1,    30,    17,    30,    14,    30,    30,    30,
      -1,    30,    17,    30,    14,    30,    30,    30,    18,    32,
      -1,    30,    17,    30,    30,    -1,    30,    17,    30,    30,
      30,    32,    -1,    30,    17,    30,    30,    30,    30,    -1,
      30,    17,    30,    30,    30,    30,    30,    -1,    30,    17,
      30,    30,    30,    30,    30,    18,    32,    -1,    30,    17,
      30,    19,    38,    20,    30,    32,    -1,    30,    17,    30,
      30,    21,    33,    22,    -1,    30,    17,    39,    -1,    30,
      30,    17,    39,    -1,    30,    30,    30,    17,    36,    -1,
      30,    30,    30,    30,    17,    36,    -1,    30,    30,    30,
      21,    33,    22,    -1,    30,    30,    19,    33,    20,    -1,
      30,    30,    21,    39,    22,    -1,    32,    18,    30,    30,
      -1,    32,    18,    30,    17,    39,    -1,    32,    18,    30,
      30,    17,    39,    -1,    32,    18,    30,    30,    30,    17,
      36,    -1,    32,    18,    30,    30,    30,    30,    17,    36,
      -1,    32,    18,    30,    30,    30,    21,    33,    22,    -1,
      32,    18,    30,    30,    19,    33,    20,    -1,    32,    18,
      30,    30,    21,    39,    22,    -1,    -1,    36,    -1,    33,
      18,    36,    -1,    30,    30,    30,    37,    -1,    30,    30,
      14,    -1,    12,    -1,     6,    12,    -1,    -1,    37,    30,
      -1,    37,    18,    30,    -1,    30,    -1,    38,    18,    30,
      -1,    -1,    39,    13,    -1,    39,    12,    -1,    39,    21,
      40,    22,    -1,    39,    41,    -1,    39,     4,     4,    -1,
      39,     5,     5,    -1,    39,    16,    -1,    39,    19,    33,
      20,    -1,    39,    -1,    40,    18,    39,    -1,     7,    -1,
       6,    -1,     8,    -1,     9,    -1,    11,    -1,    23,    -1,
      24,    -1,    25,    -1,    10,    -1,    17,    -1,    26,    -1,
      27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    91,    91,    92,    93,    94,    95,    96,    97,   100,
     101,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   134,   135,   136,
     139,   142,   145,   146,   149,   150,   151,   154,   155,   158,
     159,   160,   161,   169,   170,   171,   172,   173,   185,   186,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     201,   202
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"mathematical symbol\"",
  "'&'", "'|'", "'-'", "'+'", "'*'", "'/'", "'%'", "'^'", "\"number\"",
  "\"element name\"", "\"text string in quotes\"", "\"an error\"", "'.'",
  "'='", "','", "'['", "']'", "'('", "')'", "'>'", "'<'", "'!'", "';'",
  "'\\n'", "$accept", "input", "varOrKeyword", "equals", "changelist",
  "numlist", "plot", "name", "number", "plotlist", "taskslist", "formula",
  "commaformula", "mathThing", "lineend", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,    38,   124,    45,    43,    42,    47,
      37,    94,   259,   260,   261,   262,    46,    61,    44,    91,
      93,    40,    41,    62,    60,    33,    59,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    29,    29,    29,    29,    29,    29,    30,
      30,    31,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    33,    33,    33,
      34,    35,    36,    36,    37,    37,    37,    38,    38,    39,
      39,    39,    39,    39,    39,    39,    39,    39,    40,    40,
      41,    41,    41,    41,    41,    41,    41,    41,    41,    41,
      42,    42
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     2,     2,     2,     1,
       3,     4,     6,     7,     9,     4,     6,     6,     7,     9,
       8,     7,     3,     4,     5,     6,     6,     5,     5,     4,
       5,     6,     7,     8,     8,     7,     7,     0,     1,     3,
       4,     3,     1,     2,     0,     2,     3,     1,     3,     0,
       2,     2,     4,     2,     3,     3,     2,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     7,     9,     8,    70,    71,     0,     0,
       0,     0,     6,     0,     0,     0,     3,     4,     5,    10,
       0,    41,    44,    11,     0,    15,    40,     0,    47,     0,
      37,     0,     0,    45,     0,    12,     0,     0,     0,    42,
       0,    38,    17,    16,    46,    49,    13,     0,    48,     0,
      43,     0,    21,    18,    22,    49,     0,    37,    49,     0,
       0,     0,    20,    39,     0,     0,     0,    61,    60,    62,
      63,    68,    64,    51,    50,    56,    69,    37,    49,    65,
      66,    67,    53,    23,    14,     0,     0,     0,    37,     0,
      49,    29,     0,    19,    54,    55,     0,    58,     0,    27,
      28,    24,     0,     0,    30,    49,    37,    49,     0,    57,
      49,    52,    26,    25,    31,     0,     0,     0,    37,     0,
      59,    35,    36,    32,     0,     0,    34,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    59,     9,    35,    40,    10,    11,    41,    26,
      29,    54,    98,    82,    12
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -51
static const yytype_int16 yypact[] =
{
     -51,    61,   -51,   -51,   -51,   -51,   -51,   -51,    34,   -23,
     -23,   -23,   -51,     7,    70,    64,   -51,   -51,   -51,   -51,
       2,   -51,    -4,    70,    70,    52,    25,   111,    -4,    36,
       5,   111,    70,    -4,    69,    71,    70,    70,    90,   -51,
      22,   -51,    69,    71,    -4,   -51,   144,    70,    -4,   111,
     -51,     5,   -51,   151,   131,   -51,    70,     5,   -51,   -11,
     174,    69,    71,   -51,    70,   119,   124,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,   -51,   -51,     5,   -51,   -51,
     -51,   -51,   -51,   131,    71,   133,    87,     5,     5,    55,
     -51,   158,   165,    71,   -51,   -51,   179,   131,    27,   -51,
     -51,   -51,    48,     5,   131,   -51,     5,   -51,   172,   -51,
     -51,   -51,   -51,   -51,   131,   180,   109,     5,     5,   129,
     131,   -51,   -51,   -51,    83,     5,   -51,   -51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,    -1,   -51,   -22,   -49,   -51,   -51,   -50,   -51,
     -51,   -26,   -51,   -51,   185
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
       8,    63,     4,     6,     7,    13,    87,    15,    85,    43,
      88,    38,    13,    20,    22,     4,    23,    39,    13,    25,
      19,    24,    27,    28,    31,    33,    34,    62,    96,    83,
      42,    44,    86,    46,    84,    48,    49,   101,     4,   102,
      51,    53,    93,    32,    52,   110,    60,     4,    61,   111,
      13,    14,    97,   113,    36,    61,    37,   115,    89,    91,
      92,     2,     3,    61,   104,     4,    51,   123,    13,   124,
     112,    13,   103,    30,     4,   127,     5,     4,    21,   114,
      13,   116,     4,     4,   120,    13,    45,     6,     7,    47,
     108,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    51,    50,    75,    76,   126,    77,   119,    78,   100,
      79,    80,    81,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    94,     4,    75,    76,    13,    77,    95,
      78,   122,    79,    80,    81,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    13,   125,    75,    76,     0,
      77,    51,    78,    99,    79,    80,    81,     4,     0,     0,
      13,    55,    56,    57,     4,    58,     0,    13,    55,    64,
      57,     4,    58,     0,    13,   105,     0,   106,     4,   107,
       0,    13,    55,     0,    57,     4,    58,     4,    13,   117,
      13,    90,     0,   118,    16,    17,    18,    51,    51,   109,
     121
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-51)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
       1,    51,    13,    26,    27,    16,    17,     8,    57,    31,
      21,     6,    16,    14,    15,    13,    14,    12,    16,    20,
      13,    19,    23,    24,    25,    26,    27,    49,    77,    55,
      31,    32,    58,    34,    56,    36,    37,    87,    13,    88,
      18,    42,    64,    18,    22,    18,    47,    13,    49,    22,
      16,    17,    78,   103,    18,    56,    20,   106,    59,    60,
      61,     0,     1,    64,    90,    13,    18,   117,    16,   118,
      22,    16,    17,    21,    13,   125,    15,    13,    14,   105,
      16,   107,    13,    13,   110,    16,    17,    26,    27,    18,
      91,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    18,    12,    16,    17,    22,    19,   108,    21,    22,
      23,    24,    25,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     4,    13,    16,    17,    16,    19,     5,
      21,    22,    23,    24,    25,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    16,    17,    16,    17,    -1,
      19,    18,    21,    20,    23,    24,    25,    13,    -1,    -1,
      16,    17,    18,    19,    13,    21,    -1,    16,    17,    18,
      19,    13,    21,    -1,    16,    17,    -1,    19,    13,    21,
      -1,    16,    17,    -1,    19,    13,    21,    13,    16,    17,
      16,    17,    -1,    21,     9,    10,    11,    18,    18,    20,
      20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,     0,     1,    13,    15,    26,    27,    30,    31,
      34,    35,    42,    16,    17,    30,    42,    42,    42,    13,
      30,    14,    30,    14,    19,    30,    37,    30,    30,    38,
      21,    30,    18,    30,    30,    32,    18,    20,     6,    12,
      33,    36,    30,    32,    30,    17,    30,    18,    30,    30,
      12,    18,    22,    30,    39,    17,    18,    19,    21,    30,
      30,    30,    32,    36,    18,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    16,    17,    19,    21,    23,
      24,    25,    41,    39,    32,    33,    39,    17,    21,    30,
      17,    30,    30,    32,     4,     5,    33,    39,    40,    20,
      22,    36,    33,    17,    39,    17,    19,    21,    30,    20,
      18,    22,    22,    36,    39,    33,    39,    17,    21,    30,
      39,    20,    22,    36,    33,    17,    22,    36
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = YYLEX;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
/* Line 1787 of yacc.c  */
#line 92 "phrasedml.ypp"
    {}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 93 "phrasedml.ypp"
    {}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 94 "phrasedml.ypp"
    {}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 95 "phrasedml.ypp"
    {}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 96 "phrasedml.ypp"
    {YYABORT;}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 97 "phrasedml.ypp"
    {YYABORT;}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 100 "phrasedml.ypp"
    {(yyval.words) = new vector<const string*>; (yyval.words)->push_back((yyvsp[(1) - (1)].word));}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 101 "phrasedml.ypp"
    {(yyval.words) = (yyvsp[(1) - (3)].words); (yyval.words)->push_back((yyvsp[(3) - (3)].word));}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 104 "phrasedml.ypp"
    {if (g_registry.addModelDef((yyvsp[(1) - (4)].words), (yyvsp[(3) - (4)].words), (yyvsp[(4) - (4)].word))) YYABORT;}
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 105 "phrasedml.ypp"
    {if (g_registry.addModelDef((yyvsp[(1) - (6)].words), (yyvsp[(3) - (6)].words), (yyvsp[(4) - (6)].word), (yyvsp[(5) - (6)].words), (yyvsp[(6) - (6)].changelist))) YYABORT;}
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 106 "phrasedml.ypp"
    {if (g_registry.addModelDef((yyvsp[(1) - (7)].words), (yyvsp[(3) - (7)].words), (yyvsp[(4) - (7)].word), (yyvsp[(5) - (7)].words), (yyvsp[(6) - (7)].words), (yyvsp[(7) - (7)].words))) YYABORT;}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 107 "phrasedml.ypp"
    {if (g_registry.addModelDef((yyvsp[(1) - (9)].words), (yyvsp[(3) - (9)].words), (yyvsp[(4) - (9)].word), (yyvsp[(5) - (9)].words), (yyvsp[(6) - (9)].words), (yyvsp[(7) - (9)].words), (yyvsp[(9) - (9)].changelist))) YYABORT;}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 108 "phrasedml.ypp"
    {if (g_registry.addEquals((yyvsp[(1) - (4)].words), (yyvsp[(3) - (4)].words), (yyvsp[(4) - (4)].words))) YYABORT;}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 109 "phrasedml.ypp"
    {if (g_registry.addEquals((yyvsp[(1) - (6)].words), (yyvsp[(3) - (6)].words), (yyvsp[(4) - (6)].words), (yyvsp[(5) - (6)].words), (yyvsp[(6) - (6)].changelist))) YYABORT;}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 110 "phrasedml.ypp"
    {if (g_registry.addEquals((yyvsp[(1) - (6)].words), (yyvsp[(3) - (6)].words), (yyvsp[(4) - (6)].words), (yyvsp[(5) - (6)].words), (yyvsp[(6) - (6)].words))) YYABORT;}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 111 "phrasedml.ypp"
    {if (g_registry.addEquals((yyvsp[(1) - (7)].words), (yyvsp[(3) - (7)].words), (yyvsp[(4) - (7)].words), (yyvsp[(5) - (7)].words), (yyvsp[(6) - (7)].words), (yyvsp[(7) - (7)].words))) YYABORT;}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 112 "phrasedml.ypp"
    {if (g_registry.addEquals((yyvsp[(1) - (9)].words), (yyvsp[(3) - (9)].words), (yyvsp[(4) - (9)].words), (yyvsp[(5) - (9)].words), (yyvsp[(6) - (9)].words), (yyvsp[(7) - (9)].words))) YYABORT;}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 113 "phrasedml.ypp"
    {if (g_registry.addRepeatedTask((yyvsp[(1) - (8)].words), (yyvsp[(3) - (8)].words), (yyvsp[(5) - (8)].nameslist), (yyvsp[(7) - (8)].words), (yyvsp[(8) - (8)].changelist))) YYABORT;}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 114 "phrasedml.ypp"
    {if (g_registry.addEquals((yyvsp[(1) - (7)].words), (yyvsp[(3) - (7)].words), (yyvsp[(4) - (7)].words), (yyvsp[(6) - (7)].nums))) YYABORT;}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 117 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (3)].words), (yyvsp[(3) - (3)].wordstr))) YYABORT;}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 118 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (4)].words), (yyvsp[(2) - (4)].words), (yyvsp[(4) - (4)].wordstr), true)) YYABORT;}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 119 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (5)].words), (yyvsp[(2) - (5)].words), (yyvsp[(3) - (5)].words), (yyvsp[(5) - (5)].number))) YYABORT;}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 120 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (6)].words), (yyvsp[(2) - (6)].words), (yyvsp[(3) - (6)].words), (yyvsp[(4) - (6)].words), (yyvsp[(6) - (6)].number))) YYABORT;}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 121 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (6)].words), (yyvsp[(2) - (6)].words), (yyvsp[(3) - (6)].words), (yyvsp[(5) - (6)].nums))) YYABORT;}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 122 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (5)].words), (yyvsp[(2) - (5)].words), (yyvsp[(4) - (5)].nums))) YYABORT;}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 123 "phrasedml.ypp"
    {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(1) - (5)].words), (yyvsp[(2) - (5)].words), (yyvsp[(4) - (5)].wordstr), false)) YYABORT;}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 124 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (4)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (4)].words), (yyvsp[(4) - (4)].words))) YYABORT;}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 125 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (5)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (5)].words), (yyvsp[(5) - (5)].wordstr))) YYABORT;}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 126 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (6)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (6)].words), (yyvsp[(4) - (6)].words), (yyvsp[(6) - (6)].wordstr), true)) YYABORT;}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 127 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (7)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (7)].words), (yyvsp[(4) - (7)].words), (yyvsp[(5) - (7)].words), (yyvsp[(7) - (7)].number))) YYABORT;}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 128 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (8)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (8)].words), (yyvsp[(4) - (8)].words), (yyvsp[(5) - (8)].words), (yyvsp[(6) - (8)].words), (yyvsp[(8) - (8)].number))) YYABORT;}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 129 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (8)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (8)].words), (yyvsp[(4) - (8)].words), (yyvsp[(5) - (8)].words), (yyvsp[(7) - (8)].nums))) YYABORT;}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 130 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (7)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (7)].words), (yyvsp[(4) - (7)].words), (yyvsp[(6) - (7)].nums))) YYABORT;}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 131 "phrasedml.ypp"
    {(yyval.changelist) = (yyvsp[(1) - (7)].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[(3) - (7)].words), (yyvsp[(4) - (7)].words), (yyvsp[(6) - (7)].wordstr), false)) YYABORT;}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 134 "phrasedml.ypp"
    {(yyval.nums) = new vector<double>;}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 135 "phrasedml.ypp"
    {(yyval.nums) = new vector<double>; (yyval.nums)->push_back((yyvsp[(1) - (1)].number));}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 136 "phrasedml.ypp"
    {(yyval.nums) = (yyvsp[(1) - (3)].nums); (yyval.nums)->push_back((yyvsp[(3) - (3)].number));}
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 139 "phrasedml.ypp"
    {if (g_registry.addPlot((yyvsp[(1) - (4)].words), (yyvsp[(2) - (4)].words), (yyvsp[(3) - (4)].words), (yyvsp[(4) - (4)].nameslist))) YYABORT;}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 142 "phrasedml.ypp"
    {if (g_registry.setName((yyvsp[(1) - (3)].words), (yyvsp[(2) - (3)].words), (yyvsp[(3) - (3)].word))) YYABORT;}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 145 "phrasedml.ypp"
    {(yyval.number) = (yyvsp[(1) - (1)].number);}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 146 "phrasedml.ypp"
    {(yyval.number) = -(yyvsp[(2) - (2)].number);}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 149 "phrasedml.ypp"
    {(yyval.nameslist) = new vector<vector<const string*>*>;}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 150 "phrasedml.ypp"
    {(yyval.nameslist) = (yyvsp[(1) - (2)].nameslist); (yyval.nameslist)->push_back((yyvsp[(2) - (2)].words));}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 151 "phrasedml.ypp"
    {(yyval.nameslist) = (yyvsp[(1) - (3)].nameslist); (yyval.nameslist)->push_back((yyvsp[(3) - (3)].words));}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 154 "phrasedml.ypp"
    {(yyval.nameslist) = new vector<vector<const string*>*>; (yyval.nameslist)->push_back((yyvsp[(1) - (1)].words));}
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 155 "phrasedml.ypp"
    {(yyval.nameslist) = (yyvsp[(1) - (3)].nameslist); (yyval.nameslist)->push_back((yyvsp[(3) - (3)].words));}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 158 "phrasedml.ypp"
    {(yyval.wordstr) = new vector<string>(); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 159 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (2)].wordstr); (yyvsp[(1) - (2)].wordstr)->push_back(*(yyvsp[(2) - (2)].word)); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 160 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (2)].wordstr); (yyvsp[(1) - (2)].wordstr)->push_back(g_registry.ftoa((yyvsp[(2) - (2)].number))); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 162 "phrasedml.ypp"
    {
                  (yyval.wordstr) = (yyvsp[(1) - (4)].wordstr);
                  (yyval.wordstr)->push_back("(");
                  (yyval.wordstr)->insert((yyval.wordstr)->end(), (yyvsp[(3) - (4)].wordstr)->begin(), (yyvsp[(3) - (4)].wordstr)->end());
                  (yyval.wordstr)->push_back(")");
                  delete (yyvsp[(3) - (4)].wordstr);
                }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 169 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (2)].wordstr); string mt; mt.push_back((yyvsp[(2) - (2)].character)); (yyvsp[(1) - (2)].wordstr)->push_back(mt); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 170 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (3)].wordstr); (yyvsp[(1) - (3)].wordstr)->push_back("&&"); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 171 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (3)].wordstr); (yyvsp[(1) - (3)].wordstr)->push_back("||"); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 172 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (2)].wordstr); (yyvsp[(1) - (2)].wordstr)->push_back("."); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 174 "phrasedml.ypp"
    {
                  (yyval.wordstr) = (yyvsp[(1) - (4)].wordstr);
                  (yyval.wordstr)->push_back("[");
                  for (size_t d=0; d<(yyvsp[(3) - (4)].nums)->size(); d++) {
                    (yyval.wordstr)->push_back(g_registry.ftoa((*(yyvsp[(3) - (4)].nums))[d]));
                  }
                  (yyval.wordstr)->push_back("]");
                  delete (yyvsp[(3) - (4)].nums);
                }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 185 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (1)].wordstr);}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 186 "phrasedml.ypp"
    {(yyval.wordstr) = (yyvsp[(1) - (3)].wordstr); (yyval.wordstr)->push_back(","); (yyval.wordstr)->insert((yyval.wordstr)->end(), (yyvsp[(3) - (3)].wordstr)->begin(), (yyvsp[(3) - (3)].wordstr)->end()); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 189 "phrasedml.ypp"
    {(yyval.character) = '+';}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 190 "phrasedml.ypp"
    {(yyval.character) = '-';}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 191 "phrasedml.ypp"
    {(yyval.character) = '*';}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 192 "phrasedml.ypp"
    {(yyval.character) = '/';}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 193 "phrasedml.ypp"
    {(yyval.character) = '^';}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 194 "phrasedml.ypp"
    {(yyval.character) = '>';}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 195 "phrasedml.ypp"
    {(yyval.character) = '<';}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 196 "phrasedml.ypp"
    {(yyval.character) = '!';}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 197 "phrasedml.ypp"
    {(yyval.character) = '%';}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 198 "phrasedml.ypp"
    {(yyval.character) = '=';}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 201 "phrasedml.ypp"
    {}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 202 "phrasedml.ypp"
    {}
    break;


/* Line 1787 of yacc.c  */
#line 1938 "phrasedml.tab.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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
		      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 205 "phrasedml.ypp"



void phrased_yyerror(char const *s)
{
  if (g_registry.getError()=="") {
    g_registry.setError(s, phrased_yylloc_last_line);
  }
}

int phrased_yylex(void)
{
  char cc = 0;
  g_registry.input->get(cc);

  //If we're done with the file:
  if (g_registry.input->eof()) {
    if (g_registry.finalize()) {
      return ERROR;
    }
    return 0;
  }
  if (!g_registry.input->good()) {
    //Something else went wrong!
    g_registry.setError("Unparseable content in line " + g_registry.ftoa(phrased_yylloc_last_line) + ".", phrased_yylloc_last_line);
    return ERROR;
  }

  // Skip white space.
  while ((cc == ' ' ||
         cc == '\t') &&
         !g_registry.input->eof()) {
    g_registry.input->get(cc);
  }
  if (g_registry.input->eof()) return phrased_yylex();
  // Skip carriage returns after '\':
  if (cc == '\\') {
    g_registry.input->get(cc);
    if (cc == '\r' || cc == '\n' || cc == ' ') {
      while ((cc == '\r' || cc == '\n' || cc == ' ') && !g_registry.input->eof()) {
        g_registry.input->get(cc);
      }
      ++phrased_yylloc_last_line;
      g_registry.input->unget();
      return phrased_yylex();
    }
    else {
      g_registry.input->unget();
      cc = '\\';
    }
 }

  // Parse words
  if (cc > 0 && cc < 256 && (isalpha(cc) || cc == '_')) {
    string word;
    while (cc > 0 && cc < 256 && (isalpha(cc) || isdigit(cc) || cc == '_') && !g_registry.input->eof()) {
      word += cc;
      g_registry.input->get(cc);
    }
    if (!g_registry.input->eof()) {
      g_registry.input->unget();
    }
    //Otherwise, it's a user-defined variable:
    phrased_yylval.word = g_registry.addWord(word);
    //cout << "\tRead word '" << word << "'." << endl;
    return PHRASEWORD;
  }

  // Parse numbers
  if (cc > 0 && cc < 256 && (isdigit(cc) || (cc=='.' && isdigit(g_registry.input->peek())))) {
    double number;
    g_registry.input->unget();
    streampos numbegin = g_registry.input->tellg();
    *g_registry.input >> number;
    streampos numend = g_registry.input->tellg();
    if (g_registry.input->fail()) {
      //The gcc 4.4.3 parser fails if there's an 'e' after a number with no exponent.
      g_registry.input->clear();
      g_registry.input->seekg(numbegin);
      int numint;
      *g_registry.input >> numint;
      phrased_yylval.number = numint;
      if (g_registry.input->peek() == '.') {
        g_registry.input->get();
        *g_registry.input >> numint;
        double fraction = numint;
        while (fraction >= 1.0) {
          fraction = fraction/10;
        }
        phrased_yylval.number += fraction;
      }
      return NUM;
    }
    assert(g_registry.input->good());
    phrased_yylval.number = number;
    //However, pre-4.4.3 parsers would read the 'e' anyway, and we don't want it to, so unget the 'e'.
    g_registry.input->unget();
    if (!g_registry.input->good()) {
      //Sometimes you can't do this?  For some reason?  If this happens we'll assume there was no 'e'.
      g_registry.input->clear();
    }
    else {
      g_registry.input->get(cc);
      if (cc == 'e' || cc == 'E') {
        g_registry.input->unget();
      }
    }
    return NUM;
  }

  //Skip comments:
  if (cc == '/') {
    g_registry.input->get(cc);
    if (cc == '/') {
      while (cc != '\n' && cc != '\r' && !g_registry.input->eof()) {
        g_registry.input->get(cc);
      }
      if (!g_registry.input->eof()) {
        g_registry.input->unget();
      }
      return phrased_yylex();
    }
    else if (cc == '*') {
      bool nextstar = false;
      g_registry.input->get(cc);
      while ((!g_registry.input->eof()) && !(nextstar && cc == '/')) {
        if (cc == '*') {
          nextstar = true;
        }
        else {
          nextstar = false;
        }
        g_registry.input->get(cc);
      }
      return phrased_yylex();
    }
    else {
      g_registry.input->unget();
      cc = '/';
    }
  }
  else if (cc == '#') {
      while (cc != '\n' && cc != '\r' && !g_registry.input->eof()) {
        g_registry.input->get(cc);
      }
      if (!g_registry.input->eof()) {
        g_registry.input->unget();
      }
      return phrased_yylex();
  }

  //Parse text strings
  if (cc == '"') {
    string textstring;
    long ccount = 0;
    g_registry.input->get(cc);
    while (cc != '"' && cc != '\r' && cc != '\n' && !g_registry.input->eof()) {
      textstring += cc;
      ccount++;
      g_registry.input->get(cc);
    }
    if (cc == '\r' || cc == '\n' || g_registry.input->eof()) {
      for (; ccount > 0; ccount--) {
        g_registry.input->unget();
      }
      cc = '"';
    }
    else {
      phrased_yylval.word = g_registry.addWord(textstring);
      return TEXTSTRING;
    }
  }

  //This converts PC and Mac end-of-line characters to \n:
  if (cc == '\r') {
    g_registry.input->get(cc);
    if (cc != '\n') {
      g_registry.input->unget();
    }
    cc = '\n';
  }
  if (cc == '\n') {
    ++phrased_yylloc_last_line;
  }
  return cc;
}
