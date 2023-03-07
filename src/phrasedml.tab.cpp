/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         PHRASED_YYSTYPE
/* Substitute the variable and function names.  */
#define yyparse         phrased_yyparse
#define yylex           phrased_yylex
#define yyerror         phrased_yyerror
#define yydebug         phrased_yydebug
#define yynerrs         phrased_yynerrs
#define yylval          phrased_yylval
#define yychar          phrased_yychar

/* First part of user prologue.  */
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
#include "stringx.h"
#include "modelChange.h"

  using namespace std;
  using namespace phrasedml;
  int phrased_yylex(void);
  void phrased_yyerror(char const *);
  Registry g_registry;
  int phrased_yylloc_last_line = 1;

#line 107 "phrasedml.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef PHRASED_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define PHRASED_YYDEBUG 1
#  else
#   define PHRASED_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define PHRASED_YYDEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined PHRASED_YYDEBUG */
#if PHRASED_YYDEBUG
extern int phrased_yydebug;
#endif

/* Token kinds.  */
#ifndef PHRASED_YYTOKENTYPE
# define PHRASED_YYTOKENTYPE
  enum phrased_yytokentype
  {
    PHRASED_YYEMPTY = -2,
    PHRASED_YYEOF = 0,             /* "end of file"  */
    PHRASED_YYerror = 256,         /* error  */
    PHRASED_YYUNDEF = 257,         /* "invalid token"  */
    NUM = 259,                     /* "number"  */
    PHRASEWORD = 260,              /* "element name"  */
    TEXTSTRING = 261,              /* "text string in quotes"  */
    ERROR = 262                    /* "an error"  */
  };
  typedef enum phrased_yytokentype phrased_yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined PHRASED_YYSTYPE && ! defined PHRASED_YYSTYPE_IS_DECLARED
union PHRASED_YYSTYPE
{
#line 55 "phrasedml.ypp"

  char character;
  const string* word;
  vector<const string*>* words;
  vector<string>* wordstr;
  vector<vector<string>*>* wordstrvec;
  vector<vector<const string*>* >* nameslist;
  double number;
  vector<double>* nums;
  vector<ModelChange>* changelist;

#line 180 "phrasedml.tab.cpp"

};
typedef union PHRASED_YYSTYPE PHRASED_YYSTYPE;
# define PHRASED_YYSTYPE_IS_TRIVIAL 1
# define PHRASED_YYSTYPE_IS_DECLARED 1
#endif


extern PHRASED_YYSTYPE phrased_yylval;


int phrased_yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_mathematical_symbol_ = 3,     /* "mathematical symbol"  */
  YYSYMBOL_4_ = 4,                         /* '&'  */
  YYSYMBOL_5_ = 5,                         /* '|'  */
  YYSYMBOL_6_ = 6,                         /* '-'  */
  YYSYMBOL_7_ = 7,                         /* '+'  */
  YYSYMBOL_8_ = 8,                         /* '*'  */
  YYSYMBOL_9_ = 9,                         /* '/'  */
  YYSYMBOL_10_ = 10,                       /* '%'  */
  YYSYMBOL_11_ = 11,                       /* '^'  */
  YYSYMBOL_NUM = 12,                       /* "number"  */
  YYSYMBOL_PHRASEWORD = 13,                /* "element name"  */
  YYSYMBOL_TEXTSTRING = 14,                /* "text string in quotes"  */
  YYSYMBOL_ERROR = 15,                     /* "an error"  */
  YYSYMBOL_16_ = 16,                       /* '.'  */
  YYSYMBOL_17_ = 17,                       /* '='  */
  YYSYMBOL_18_ = 18,                       /* ','  */
  YYSYMBOL_19_ = 19,                       /* '['  */
  YYSYMBOL_20_ = 20,                       /* ']'  */
  YYSYMBOL_21_ = 21,                       /* '('  */
  YYSYMBOL_22_ = 22,                       /* ')'  */
  YYSYMBOL_23_ = 23,                       /* '>'  */
  YYSYMBOL_24_ = 24,                       /* ':'  */
  YYSYMBOL_25_ = 25,                       /* '!'  */
  YYSYMBOL_26_ = 26,                       /* '<'  */
  YYSYMBOL_27_ = 27,                       /* ';'  */
  YYSYMBOL_28_n_ = 28,                     /* '\n'  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_input = 30,                     /* input  */
  YYSYMBOL_varOrKeyword = 31,              /* varOrKeyword  */
  YYSYMBOL_equals = 32,                    /* equals  */
  YYSYMBOL_changelist = 33,                /* changelist  */
  YYSYMBOL_numlist = 34,                   /* numlist  */
  YYSYMBOL_plot = 35,                      /* plot  */
  YYSYMBOL_name = 36,                      /* name  */
  YYSYMBOL_number = 37,                    /* number  */
  YYSYMBOL_taskslist = 38,                 /* taskslist  */
  YYSYMBOL_vslist = 39,                    /* vslist  */
  YYSYMBOL_formula = 40,                   /* formula  */
  YYSYMBOL_commaformula = 41,              /* commaformula  */
  YYSYMBOL_mathThing = 42,                 /* mathThing  */
  YYSYMBOL_lineend = 43                    /* lineend  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined PHRASED_YYSTYPE_IS_TRIVIAL && PHRASED_YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   262


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      28,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,     2,     2,    10,     4,     2,
      21,    22,     8,     7,    18,     6,    16,     9,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    24,    27,
      26,    17,    23,     2,     2,     2,     2,     2,     2,     2,
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

#if PHRASED_YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    92,    92,    93,    94,    95,    96,    97,    98,   101,
     102,   103,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   140,   141,   142,   145,   146,   149,   152,   153,
     156,   157,   160,   162,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   182,   183,   184,   185,   197,   198,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   213,
     214
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"",
  "\"mathematical symbol\"", "'&'", "'|'", "'-'", "'+'", "'*'", "'/'",
  "'%'", "'^'", "\"number\"", "\"element name\"",
  "\"text string in quotes\"", "\"an error\"", "'.'", "'='", "','", "'['",
  "']'", "'('", "')'", "'>'", "':'", "'!'", "'<'", "';'", "'\\n'",
  "$accept", "input", "varOrKeyword", "equals", "changelist", "numlist",
  "plot", "name", "number", "taskslist", "vslist", "formula",
  "commaformula", "mathThing", "lineend", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-69)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -69,    10,   -69,   -69,   -69,   -69,   -69,   -69,   239,   -22,
     -22,   -22,   -69,   -69,   -69,    37,    55,   128,    37,   -69,
      65,    -3,   223,   -69,   -69,   -69,    11,    -3,    62,   -69,
     -69,   -69,    99,   -69,   139,   -69,    37,    79,    94,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,    12,     7,   -69,
     -69,   -69,    11,   -69,   -69,   110,   110,    32,   -69,   223,
     -69,   -69,    69,   -69,   -69,   223,   -14,   101,    11,   149,
      12,   101,    12,   -69,    37,   -69,    88,   120,   110,   110,
      41,    88,   120,   -69,   223,    37,    23,   110,    11,   101,
     -69,   111,   223,    37,   110,    12,    37,    90,   241,    88,
     120,   110,   223,   120,   152,   177,    12,    12,    35,    37,
     158,   246,   120,   -69,   -69,   -69,    47,    12,     6,   223,
      37,    12,    37,   253,   -69,   -69,   134,    37,   223,   173,
     200,    12,    12,   137,    37,   223,   -69,   -69,   -69,    54,
      12,   223,   -69,   -69
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     7,     9,     8,    79,    80,     0,     0,
       0,     0,     6,    57,    55,     0,     0,     0,     0,    58,
      54,    45,    52,     3,     4,     5,    54,    46,     0,    48,
      10,    11,    23,    24,     0,    47,     0,     0,     0,    70,
      69,    71,    72,    77,    73,    60,    78,    42,     0,    74,
      76,    75,    59,    63,    49,    12,     0,    16,    56,    53,
      64,    65,     0,    43,    61,    67,     0,     0,    50,     0,
      42,     0,     0,    66,     0,    62,     0,    13,     0,     0,
       0,    18,    17,    44,    68,     0,    14,     0,    51,     0,
      22,    19,    25,     0,     0,    42,     0,     0,     0,     0,
      21,     0,    26,    15,     0,     0,     0,    42,     0,     0,
      32,     0,    20,    30,    31,    27,     0,     0,    54,    34,
       0,    42,     0,     0,    29,    28,     0,     0,    36,     0,
       0,     0,    42,     0,     0,    35,    40,    41,    37,     0,
       0,    33,    39,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,    -1,   -69,   -68,   -61,   -69,   -69,   -15,   -69,
     144,    46,   -69,   -69,   126
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    52,     9,    77,    62,    10,    11,    63,    69,
      21,    22,    66,    53,    12
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
       8,    31,    33,    82,    74,     6,     7,    20,    75,    80,
       2,     3,   126,    13,    26,    36,    32,    26,    28,    14,
       4,   100,    16,     4,    29,     5,   103,    16,    18,    64,
     127,    57,    19,   112,   104,    26,     4,     6,     7,    16,
      93,    94,    95,    13,    96,     4,   116,    26,    16,    14,
       4,    16,   117,    70,    67,    68,    71,    83,    18,    72,
     129,    28,    19,    90,    34,    72,    76,    29,    30,   124,
      81,   139,    72,    26,    54,    86,   142,    88,    89,    35,
      91,    16,    59,    60,    26,    97,    98,    72,    99,    73,
      97,   115,    26,    99,    65,    26,   108,   110,   111,    61,
      99,     4,   125,     4,    16,    85,    16,   106,   118,   123,
      97,   107,     4,    55,     4,    16,   138,    16,    56,    26,
      84,    26,   133,     4,     4,   143,    26,    16,    93,   101,
      95,    92,    96,    26,    28,    23,    24,    25,    87,   102,
      29,     4,   105,    37,    38,    39,    40,    41,    42,    43,
      44,    45,     4,    16,   140,   119,    46,   134,    47,    27,
      48,    58,    49,     0,    50,    51,   128,    78,   130,    79,
      72,     4,   113,   135,    16,   120,     0,   121,     0,   122,
     141,    37,    38,    39,    40,    41,    42,    43,    44,    45,
       4,    72,     0,   136,    46,     0,    47,     0,    48,   114,
      49,     0,    50,    51,    37,    38,    39,    40,    41,    42,
      43,    44,    45,     4,     0,     0,     0,    46,     0,    47,
       0,    48,   137,    49,     0,    50,    51,    37,    38,    39,
      40,    41,    42,    43,    44,    45,     4,     0,     0,     0,
      46,     0,    47,     0,    48,    13,    49,     0,    50,    51,
       0,    14,     4,    15,     4,    16,    17,    16,   109,     4,
      18,     0,    16,    93,    19,    95,     4,    96,     0,    16,
     131,     0,     0,     0,   132
};

static const yytype_int16 yycheck[] =
{
       1,    16,    17,    71,    18,    27,    28,     8,    22,    70,
       0,     1,     6,     6,    15,    18,    17,    18,     6,    12,
      13,    89,    16,    13,    12,    15,    94,    16,    21,    22,
      24,    32,    25,   101,    95,    36,    13,    27,    28,    16,
      17,    18,    19,     6,    21,    13,   107,    48,    16,    12,
      13,    16,    17,    21,    55,    56,    57,    72,    21,    18,
     121,     6,    25,    22,    18,    18,    67,    12,    13,    22,
      71,   132,    18,    74,    12,    76,    22,    78,    79,    14,
      81,    16,    36,     4,    85,    86,    87,    18,    89,    20,
      91,   106,    93,    94,    48,    96,    97,    98,    99,     5,
     101,    13,   117,    13,    16,    17,    16,    17,   109,   110,
     111,    21,    13,    14,    13,    16,   131,    16,    19,   120,
      74,   122,   123,    13,    13,   140,   127,    16,    17,    18,
      19,    85,    21,   134,     6,     9,    10,    11,    18,    93,
      12,    13,    96,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    16,    17,   109,    17,    23,    19,    15,
      21,    22,    23,    -1,    25,    26,   120,    18,   122,    20,
      18,    13,    20,   127,    16,    17,    -1,    19,    -1,    21,
     134,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    18,    -1,    20,    17,    -1,    19,    -1,    21,    22,
      23,    -1,    25,    26,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    -1,    17,    -1,    19,
      -1,    21,    22,    23,    -1,    25,    26,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    -1,    -1,
      17,    -1,    19,    -1,    21,     6,    23,    -1,    25,    26,
      -1,    12,    13,    14,    13,    16,    17,    16,    17,    13,
      21,    -1,    16,    17,    25,    19,    13,    21,    -1,    16,
      17,    -1,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    30,     0,     1,    13,    15,    27,    28,    31,    32,
      35,    36,    43,     6,    12,    14,    16,    17,    21,    25,
      31,    39,    40,    43,    43,    43,    31,    39,     6,    12,
      13,    37,    31,    37,    40,    14,    18,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    17,    19,    21,    23,
      25,    26,    31,    42,    12,    14,    19,    31,    22,    40,
       4,     5,    34,    37,    22,    40,    41,    31,    31,    38,
      21,    31,    18,    20,    18,    22,    31,    33,    18,    20,
      34,    31,    33,    37,    40,    17,    31,    18,    31,    31,
      22,    31,    40,    17,    18,    19,    21,    31,    31,    31,
      33,    18,    40,    33,    34,    40,    17,    21,    31,    17,
      31,    31,    33,    20,    22,    37,    34,    17,    31,    40,
      17,    19,    21,    31,    22,    37,     6,    24,    40,    34,
      40,    17,    21,    31,    23,    40,    20,    22,    37,    34,
      17,    40,    22,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    30,    30,    30,    30,    30,    30,    31,
      31,    31,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    34,    34,    34,    35,    35,    36,    37,    37,
      38,    38,    39,    39,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    41,    41,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    43,
      43
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     3,     3,     2,     2,     2,     1,
       3,     3,     4,     6,     7,     9,     4,     6,     6,     7,
       9,     8,     7,     3,     3,     3,     4,     5,     6,     6,
       5,     5,     4,     8,     5,     7,     6,     7,     8,     8,
       7,     7,     0,     1,     3,     2,     3,     3,     1,     2,
       1,     3,     1,     3,     1,     1,     3,     1,     1,     2,
       2,     3,     4,     2,     3,     3,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = PHRASED_YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == PHRASED_YYEMPTY)                                        \
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

/* Backward compatibility with an undocumented macro.
   Use PHRASED_YYerror or PHRASED_YYUNDEF. */
#define YYERRCODE PHRASED_YYUNDEF


/* Enable debugging if requested.  */
#if PHRASED_YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !PHRASED_YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !PHRASED_YYDEBUG */


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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = PHRASED_YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == PHRASED_YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= PHRASED_YYEOF)
    {
      yychar = PHRASED_YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == PHRASED_YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = PHRASED_YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = PHRASED_YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* input: input equals lineend  */
#line 93 "phrasedml.ypp"
                                     {}
#line 1587 "phrasedml.tab.cpp"
    break;

  case 4: /* input: input plot lineend  */
#line 94 "phrasedml.ypp"
                                   {}
#line 1593 "phrasedml.tab.cpp"
    break;

  case 5: /* input: input name lineend  */
#line 95 "phrasedml.ypp"
                                   {}
#line 1599 "phrasedml.tab.cpp"
    break;

  case 6: /* input: input lineend  */
#line 96 "phrasedml.ypp"
                              {}
#line 1605 "phrasedml.tab.cpp"
    break;

  case 7: /* input: input error  */
#line 97 "phrasedml.ypp"
                            {YYABORT;}
#line 1611 "phrasedml.tab.cpp"
    break;

  case 8: /* input: input "an error"  */
#line 98 "phrasedml.ypp"
                            {YYABORT;}
#line 1617 "phrasedml.tab.cpp"
    break;

  case 9: /* varOrKeyword: "element name"  */
#line 101 "phrasedml.ypp"
                           {(yyval.words) = new vector<const string*>; (yyval.words)->push_back((yyvsp[0].word));}
#line 1623 "phrasedml.tab.cpp"
    break;

  case 10: /* varOrKeyword: varOrKeyword '.' "element name"  */
#line 102 "phrasedml.ypp"
                                            {(yyval.words) = (yyvsp[-2].words); (yyval.words)->push_back((yyvsp[0].word));}
#line 1629 "phrasedml.tab.cpp"
    break;

  case 11: /* varOrKeyword: varOrKeyword '.' number  */
#line 103 "phrasedml.ypp"
                                        {(yyval.words) = (yyvsp[-2].words); (yyval.words)->push_back(g_registry.addWord(DoubleToString((yyvsp[0].number))));}
#line 1635 "phrasedml.tab.cpp"
    break;

  case 12: /* equals: varOrKeyword '=' varOrKeyword "text string in quotes"  */
#line 106 "phrasedml.ypp"
                                                         {if (g_registry.addModelDef((yyvsp[-3].words), (yyvsp[-1].words), (yyvsp[0].word))) YYABORT;}
#line 1641 "phrasedml.tab.cpp"
    break;

  case 13: /* equals: varOrKeyword '=' varOrKeyword "text string in quotes" varOrKeyword changelist  */
#line 107 "phrasedml.ypp"
                                                                                 {if (g_registry.addModelDef((yyvsp[-5].words), (yyvsp[-3].words), (yyvsp[-2].word), (yyvsp[-1].words), (yyvsp[0].changelist))) YYABORT;}
#line 1647 "phrasedml.tab.cpp"
    break;

  case 14: /* equals: varOrKeyword '=' varOrKeyword "text string in quotes" varOrKeyword varOrKeyword varOrKeyword  */
#line 108 "phrasedml.ypp"
                                                                                                {if (g_registry.addModelDef((yyvsp[-6].words), (yyvsp[-4].words), (yyvsp[-3].word), (yyvsp[-2].words), (yyvsp[-1].words), (yyvsp[0].words))) YYABORT;}
#line 1653 "phrasedml.tab.cpp"
    break;

  case 15: /* equals: varOrKeyword '=' varOrKeyword "text string in quotes" varOrKeyword varOrKeyword varOrKeyword ',' changelist  */
#line 109 "phrasedml.ypp"
                                                                                                               {if (g_registry.addModelDef((yyvsp[-8].words), (yyvsp[-6].words), (yyvsp[-5].word), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].changelist))) YYABORT;}
#line 1659 "phrasedml.tab.cpp"
    break;

  case 16: /* equals: varOrKeyword '=' varOrKeyword varOrKeyword  */
#line 110 "phrasedml.ypp"
                                                           {if (g_registry.addEquals((yyvsp[-3].words), (yyvsp[-1].words), (yyvsp[0].words))) YYABORT;}
#line 1665 "phrasedml.tab.cpp"
    break;

  case 17: /* equals: varOrKeyword '=' varOrKeyword varOrKeyword varOrKeyword changelist  */
#line 111 "phrasedml.ypp"
                                                                                   {if (g_registry.addEquals((yyvsp[-5].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[-1].words), (yyvsp[0].changelist))) YYABORT;}
#line 1671 "phrasedml.tab.cpp"
    break;

  case 18: /* equals: varOrKeyword '=' varOrKeyword varOrKeyword varOrKeyword varOrKeyword  */
#line 112 "phrasedml.ypp"
                                                                                     {if (g_registry.addEquals((yyvsp[-5].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[-1].words), (yyvsp[0].words))) YYABORT;}
#line 1677 "phrasedml.tab.cpp"
    break;

  case 19: /* equals: varOrKeyword '=' varOrKeyword varOrKeyword varOrKeyword varOrKeyword varOrKeyword  */
#line 113 "phrasedml.ypp"
                                                                                                  {if (g_registry.addEquals((yyvsp[-6].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[-1].words), (yyvsp[0].words))) YYABORT;}
#line 1683 "phrasedml.tab.cpp"
    break;

  case 20: /* equals: varOrKeyword '=' varOrKeyword varOrKeyword varOrKeyword varOrKeyword varOrKeyword ',' changelist  */
#line 114 "phrasedml.ypp"
                                                                                                                 {if (g_registry.addEquals((yyvsp[-8].words), (yyvsp[-6].words), (yyvsp[-5].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words))) YYABORT;}
#line 1689 "phrasedml.tab.cpp"
    break;

  case 21: /* equals: varOrKeyword '=' varOrKeyword '[' taskslist ']' varOrKeyword changelist  */
#line 115 "phrasedml.ypp"
                                                                                        {if (g_registry.addRepeatedTask((yyvsp[-7].words), (yyvsp[-5].words), (yyvsp[-3].nameslist), (yyvsp[-1].words), (yyvsp[0].changelist))) YYABORT;}
#line 1695 "phrasedml.tab.cpp"
    break;

  case 22: /* equals: varOrKeyword '=' varOrKeyword varOrKeyword '(' numlist ')'  */
#line 116 "phrasedml.ypp"
                                                                           {if (g_registry.addEquals((yyvsp[-6].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].nums))) YYABORT;}
#line 1701 "phrasedml.tab.cpp"
    break;

  case 23: /* equals: varOrKeyword '=' varOrKeyword  */
#line 117 "phrasedml.ypp"
                                              {if (g_registry.addEquals((yyvsp[-2].words), (yyvsp[0].words))) YYABORT;}
#line 1707 "phrasedml.tab.cpp"
    break;

  case 24: /* equals: varOrKeyword '=' number  */
#line 118 "phrasedml.ypp"
                                              {if (g_registry.addEquals((yyvsp[-2].words), (yyvsp[0].number))) YYABORT;}
#line 1713 "phrasedml.tab.cpp"
    break;

  case 25: /* changelist: varOrKeyword '=' formula  */
#line 121 "phrasedml.ypp"
                                         {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-2].words), (yyvsp[0].wordstr))) YYABORT;}
#line 1719 "phrasedml.tab.cpp"
    break;

  case 26: /* changelist: varOrKeyword varOrKeyword '=' formula  */
#line 122 "phrasedml.ypp"
                                                      {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].wordstr), true)) YYABORT;}
#line 1725 "phrasedml.tab.cpp"
    break;

  case 27: /* changelist: varOrKeyword varOrKeyword varOrKeyword '=' number  */
#line 123 "phrasedml.ypp"
                                                                  {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].number))) YYABORT;}
#line 1731 "phrasedml.tab.cpp"
    break;

  case 28: /* changelist: varOrKeyword varOrKeyword varOrKeyword varOrKeyword '=' number  */
#line 124 "phrasedml.ypp"
                                                                               {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-5].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].number))) YYABORT;}
#line 1737 "phrasedml.tab.cpp"
    break;

  case 29: /* changelist: varOrKeyword varOrKeyword varOrKeyword '(' numlist ')'  */
#line 125 "phrasedml.ypp"
                                                                       {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-5].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].nums))) YYABORT;}
#line 1743 "phrasedml.tab.cpp"
    break;

  case 30: /* changelist: varOrKeyword varOrKeyword '[' numlist ']'  */
#line 126 "phrasedml.ypp"
                                                          {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].nums))) YYABORT;}
#line 1749 "phrasedml.tab.cpp"
    break;

  case 31: /* changelist: varOrKeyword varOrKeyword '(' formula ')'  */
#line 127 "phrasedml.ypp"
                                                          {(yyval.changelist) = new vector<ModelChange>; if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].wordstr), false)) YYABORT;}
#line 1755 "phrasedml.tab.cpp"
    break;

  case 32: /* changelist: changelist ',' varOrKeyword varOrKeyword  */
#line 128 "phrasedml.ypp"
                                                         {(yyval.changelist) = (yyvsp[-3].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-1].words), (yyvsp[0].words))) YYABORT;}
#line 1761 "phrasedml.tab.cpp"
    break;

  case 33: /* changelist: changelist ',' varOrKeyword '=' varOrKeyword '-' '>' formula  */
#line 129 "phrasedml.ypp"
                                                                             {(yyval.changelist) = (yyvsp[-7].changelist); if (g_registry.addMapToChangeList((yyval.changelist), (yyvsp[-5].words), (yyvsp[-3].words), (yyvsp[0].wordstr))) YYABORT;}
#line 1767 "phrasedml.tab.cpp"
    break;

  case 34: /* changelist: changelist ',' varOrKeyword '=' formula  */
#line 130 "phrasedml.ypp"
                                                        {(yyval.changelist) = (yyvsp[-4].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-2].words), (yyvsp[0].wordstr))) YYABORT;}
#line 1773 "phrasedml.tab.cpp"
    break;

  case 35: /* changelist: changelist ',' varOrKeyword '=' varOrKeyword ':' formula  */
#line 131 "phrasedml.ypp"
                                                                         {(yyval.changelist) = (yyvsp[-6].changelist); if (g_registry.addToChangeListFromRange((yyval.changelist), (yyvsp[-4].words), (yyvsp[-2].words), (yyvsp[0].wordstr))) YYABORT;}
#line 1779 "phrasedml.tab.cpp"
    break;

  case 36: /* changelist: changelist ',' varOrKeyword varOrKeyword '=' formula  */
#line 132 "phrasedml.ypp"
                                                                     {(yyval.changelist) = (yyvsp[-5].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].wordstr), true)) YYABORT;}
#line 1785 "phrasedml.tab.cpp"
    break;

  case 37: /* changelist: changelist ',' varOrKeyword varOrKeyword varOrKeyword '=' number  */
#line 133 "phrasedml.ypp"
                                                                                 {(yyval.changelist) = (yyvsp[-6].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].number))) YYABORT;}
#line 1791 "phrasedml.tab.cpp"
    break;

  case 38: /* changelist: changelist ',' varOrKeyword varOrKeyword varOrKeyword varOrKeyword '=' number  */
#line 134 "phrasedml.ypp"
                                                                                              {(yyval.changelist) = (yyvsp[-7].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-5].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-2].words), (yyvsp[0].number))) YYABORT;}
#line 1797 "phrasedml.tab.cpp"
    break;

  case 39: /* changelist: changelist ',' varOrKeyword varOrKeyword varOrKeyword '(' numlist ')'  */
#line 135 "phrasedml.ypp"
                                                                                      {(yyval.changelist) = (yyvsp[-7].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-5].words), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].nums))) YYABORT;}
#line 1803 "phrasedml.tab.cpp"
    break;

  case 40: /* changelist: changelist ',' varOrKeyword varOrKeyword '[' numlist ']'  */
#line 136 "phrasedml.ypp"
                                                                         {(yyval.changelist) = (yyvsp[-6].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].nums))) YYABORT;}
#line 1809 "phrasedml.tab.cpp"
    break;

  case 41: /* changelist: changelist ',' varOrKeyword varOrKeyword '(' formula ')'  */
#line 137 "phrasedml.ypp"
                                                                         {(yyval.changelist) = (yyvsp[-6].changelist); if (g_registry.addToChangeList((yyval.changelist), (yyvsp[-4].words), (yyvsp[-3].words), (yyvsp[-1].wordstr), false)) YYABORT;}
#line 1815 "phrasedml.tab.cpp"
    break;

  case 42: /* numlist: %empty  */
#line 140 "phrasedml.ypp"
                            {(yyval.nums) = new vector<double>;}
#line 1821 "phrasedml.tab.cpp"
    break;

  case 43: /* numlist: number  */
#line 141 "phrasedml.ypp"
                       {(yyval.nums) = new vector<double>; (yyval.nums)->push_back((yyvsp[0].number));}
#line 1827 "phrasedml.tab.cpp"
    break;

  case 44: /* numlist: numlist ',' number  */
#line 142 "phrasedml.ypp"
                                   {(yyval.nums) = (yyvsp[-2].nums); (yyval.nums)->push_back((yyvsp[0].number));}
#line 1833 "phrasedml.tab.cpp"
    break;

  case 45: /* plot: varOrKeyword vslist  */
#line 145 "phrasedml.ypp"
                                    {if (g_registry.addOutput((yyvsp[-1].words), (yyvsp[0].wordstrvec))) YYABORT;}
#line 1839 "phrasedml.tab.cpp"
    break;

  case 46: /* plot: varOrKeyword "text string in quotes" vslist  */
#line 146 "phrasedml.ypp"
                                               {if (g_registry.addOutput((yyvsp[-2].words), (yyvsp[0].wordstrvec), (yyvsp[-1].word))) YYABORT;}
#line 1845 "phrasedml.tab.cpp"
    break;

  case 47: /* name: varOrKeyword varOrKeyword "text string in quotes"  */
#line 149 "phrasedml.ypp"
                                                     {if (g_registry.setName((yyvsp[-2].words), (yyvsp[-1].words), (yyvsp[0].word))) YYABORT;}
#line 1851 "phrasedml.tab.cpp"
    break;

  case 48: /* number: "number"  */
#line 152 "phrasedml.ypp"
                    {(yyval.number) = (yyvsp[0].number);}
#line 1857 "phrasedml.tab.cpp"
    break;

  case 49: /* number: '-' "number"  */
#line 153 "phrasedml.ypp"
                        {(yyval.number) = -(yyvsp[0].number);}
#line 1863 "phrasedml.tab.cpp"
    break;

  case 50: /* taskslist: varOrKeyword  */
#line 156 "phrasedml.ypp"
                             {(yyval.nameslist) = new vector<vector<const string*>*>; (yyval.nameslist)->push_back((yyvsp[0].words));}
#line 1869 "phrasedml.tab.cpp"
    break;

  case 51: /* taskslist: taskslist ',' varOrKeyword  */
#line 157 "phrasedml.ypp"
                                           {(yyval.nameslist) = (yyvsp[-2].nameslist); (yyval.nameslist)->push_back((yyvsp[0].words));}
#line 1875 "phrasedml.tab.cpp"
    break;

  case 52: /* vslist: formula  */
#line 160 "phrasedml.ypp"
                        {(yyval.wordstrvec) = new vector<vector<string>* >; (yyval.wordstrvec)->push_back((yyvsp[0].wordstr));}
#line 1881 "phrasedml.tab.cpp"
    break;

  case 53: /* vslist: vslist ',' formula  */
#line 162 "phrasedml.ypp"
                                   {(yyval.wordstrvec) = (yyvsp[-2].wordstrvec); (yyval.wordstrvec)->push_back((yyvsp[0].wordstr));}
#line 1887 "phrasedml.tab.cpp"
    break;

  case 54: /* formula: varOrKeyword  */
#line 166 "phrasedml.ypp"
                             {(yyval.wordstr) = new vector<string>(); (yyval.wordstr)->push_back(getStringFrom((yyvsp[0].words), g_registry.getSeparator())); }
#line 1893 "phrasedml.tab.cpp"
    break;

  case 55: /* formula: "number"  */
#line 167 "phrasedml.ypp"
                    {(yyval.wordstr) = new vector<string>(); (yyval.wordstr)->push_back(g_registry.ftoa((yyvsp[0].number))); }
#line 1899 "phrasedml.tab.cpp"
    break;

  case 56: /* formula: '(' formula ')'  */
#line 168 "phrasedml.ypp"
                                {(yyval.wordstr) = (yyvsp[-1].wordstr); (yyval.wordstr)->insert((yyval.wordstr)->begin(), "("); (yyval.wordstr)->push_back(")"); }
#line 1905 "phrasedml.tab.cpp"
    break;

  case 57: /* formula: '-'  */
#line 169 "phrasedml.ypp"
                    {(yyval.wordstr) = new vector<string>(); (yyval.wordstr)->push_back("-"); }
#line 1911 "phrasedml.tab.cpp"
    break;

  case 58: /* formula: '!'  */
#line 170 "phrasedml.ypp"
                    {(yyval.wordstr) = new vector<string>(); (yyval.wordstr)->push_back("!"); }
#line 1917 "phrasedml.tab.cpp"
    break;

  case 59: /* formula: formula varOrKeyword  */
#line 171 "phrasedml.ypp"
                                     {(yyval.wordstr) = (yyvsp[-1].wordstr); (yyval.wordstr)->push_back(getStringFrom((yyvsp[0].words), g_registry.getSeparator())); }
#line 1923 "phrasedml.tab.cpp"
    break;

  case 60: /* formula: formula "number"  */
#line 172 "phrasedml.ypp"
                             {(yyval.wordstr) = (yyvsp[-1].wordstr); (yyvsp[-1].wordstr)->push_back(g_registry.ftoa((yyvsp[0].number))); }
#line 1929 "phrasedml.tab.cpp"
    break;

  case 61: /* formula: formula '(' ')'  */
#line 173 "phrasedml.ypp"
                                {(yyval.wordstr) = (yyvsp[-2].wordstr); (yyval.wordstr)->push_back("()");}
#line 1935 "phrasedml.tab.cpp"
    break;

  case 62: /* formula: formula '(' commaformula ')'  */
#line 175 "phrasedml.ypp"
                {
                  (yyval.wordstr) = (yyvsp[-3].wordstr);
                  (yyval.wordstr)->push_back("(");
                  (yyval.wordstr)->insert((yyval.wordstr)->end(), (yyvsp[-1].wordstr)->begin(), (yyvsp[-1].wordstr)->end());
                  (yyval.wordstr)->push_back(")");
                  delete (yyvsp[-1].wordstr);
                }
#line 1947 "phrasedml.tab.cpp"
    break;

  case 63: /* formula: formula mathThing  */
#line 182 "phrasedml.ypp"
                                  {(yyval.wordstr) = (yyvsp[-1].wordstr); string mt; mt.push_back((yyvsp[0].character)); (yyvsp[-1].wordstr)->push_back(mt); }
#line 1953 "phrasedml.tab.cpp"
    break;

  case 64: /* formula: formula '&' '&'  */
#line 183 "phrasedml.ypp"
                                {(yyval.wordstr) = (yyvsp[-2].wordstr); (yyvsp[-2].wordstr)->push_back("&&"); }
#line 1959 "phrasedml.tab.cpp"
    break;

  case 65: /* formula: formula '|' '|'  */
#line 184 "phrasedml.ypp"
                                {(yyval.wordstr) = (yyvsp[-2].wordstr); (yyvsp[-2].wordstr)->push_back("||"); }
#line 1965 "phrasedml.tab.cpp"
    break;

  case 66: /* formula: formula '[' numlist ']'  */
#line 186 "phrasedml.ypp"
                {
                  (yyval.wordstr) = (yyvsp[-3].wordstr);
                  (yyval.wordstr)->push_back("[");
                  for (size_t d=0; d<(yyvsp[-1].nums)->size(); d++) {
                    (yyval.wordstr)->push_back(g_registry.ftoa((*(yyvsp[-1].nums))[d]));
                  }
                  (yyval.wordstr)->push_back("]");
                  delete (yyvsp[-1].nums);
                }
#line 1979 "phrasedml.tab.cpp"
    break;

  case 67: /* commaformula: formula  */
#line 197 "phrasedml.ypp"
                        {(yyval.wordstr) = (yyvsp[0].wordstr);}
#line 1985 "phrasedml.tab.cpp"
    break;

  case 68: /* commaformula: commaformula ',' formula  */
#line 198 "phrasedml.ypp"
                                         {(yyval.wordstr) = (yyvsp[-2].wordstr); (yyval.wordstr)->push_back(","); (yyval.wordstr)->insert((yyval.wordstr)->end(), (yyvsp[0].wordstr)->begin(), (yyvsp[0].wordstr)->end()); }
#line 1991 "phrasedml.tab.cpp"
    break;

  case 69: /* mathThing: '+'  */
#line 201 "phrasedml.ypp"
                    {(yyval.character) = '+';}
#line 1997 "phrasedml.tab.cpp"
    break;

  case 70: /* mathThing: '-'  */
#line 202 "phrasedml.ypp"
                    {(yyval.character) = '-';}
#line 2003 "phrasedml.tab.cpp"
    break;

  case 71: /* mathThing: '*'  */
#line 203 "phrasedml.ypp"
                    {(yyval.character) = '*';}
#line 2009 "phrasedml.tab.cpp"
    break;

  case 72: /* mathThing: '/'  */
#line 204 "phrasedml.ypp"
                    {(yyval.character) = '/';}
#line 2015 "phrasedml.tab.cpp"
    break;

  case 73: /* mathThing: '^'  */
#line 205 "phrasedml.ypp"
                    {(yyval.character) = '^';}
#line 2021 "phrasedml.tab.cpp"
    break;

  case 74: /* mathThing: '>'  */
#line 206 "phrasedml.ypp"
                    {(yyval.character) = '>';}
#line 2027 "phrasedml.tab.cpp"
    break;

  case 75: /* mathThing: '<'  */
#line 207 "phrasedml.ypp"
                    {(yyval.character) = '<';}
#line 2033 "phrasedml.tab.cpp"
    break;

  case 76: /* mathThing: '!'  */
#line 208 "phrasedml.ypp"
                    {(yyval.character) = '!';}
#line 2039 "phrasedml.tab.cpp"
    break;

  case 77: /* mathThing: '%'  */
#line 209 "phrasedml.ypp"
                    {(yyval.character) = '%';}
#line 2045 "phrasedml.tab.cpp"
    break;

  case 78: /* mathThing: '='  */
#line 210 "phrasedml.ypp"
                    {(yyval.character) = '=';}
#line 2051 "phrasedml.tab.cpp"
    break;

  case 79: /* lineend: ';'  */
#line 213 "phrasedml.ypp"
                    {}
#line 2057 "phrasedml.tab.cpp"
    break;

  case 80: /* lineend: '\n'  */
#line 214 "phrasedml.ypp"
                     {}
#line 2063 "phrasedml.tab.cpp"
    break;


#line 2067 "phrasedml.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == PHRASED_YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= PHRASED_YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == PHRASED_YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = PHRASED_YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != PHRASED_YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 217 "phrasedml.ypp"



void phrased_yyerror(char const *s)
{
  stringstream err;
  err << "Error in line " << phrased_yylloc_last_line << ": " << s;
  if (g_registry.getError()=="") {
    g_registry.setError(err.str(), phrased_yylloc_last_line);
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
      g_registry.input->putback(cc);
      return phrased_yylex();
    }
    else {
      g_registry.input->putback(cc);
      cc = '\\';
    }
 }

  // Parse words
  if (cc > 0 && (isalpha(cc) || cc == '_')) {
    string word;
    while (cc > 0 && (isalpha(cc) || isdigit(cc) || cc == '_') && !g_registry.input->eof()) {
      word += cc;
      g_registry.input->get(cc);
    }
    if (!g_registry.input->eof()) {
      g_registry.input->putback(cc);
    }
    //Otherwise, it's a user-defined variable:
    phrased_yylval.word = g_registry.addWord(word);
    //cout << "\tRead word '" << word << "'." << endl;
    if (word == "vs" && g_registry.input->peek() == '.') {
      g_registry.input->get(cc);
    }
    return PHRASEWORD;
  }

  // The trick here is to distinguish 'kisao.433' from '5+.433'.  Have to do that with the parser, though.
  if (cc=='.') {
    return cc;
  }

  // Parse numbers
  if (cc > 0 && (isdigit(cc))) {
    double number;
    g_registry.input->putback(cc);
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
        g_registry.input->putback(cc);
      }
      if (cc == '.') {
        //We might be in a 'kisao.43.c' situation.  Which is wrong, but at least clear what was meant.
        char next = g_registry.input->peek();
        if (('a' <= next && next <= 'z') || ('A' <= next && next <= 'Z')) {
          g_registry.input->putback(cc);
        }
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
        g_registry.input->putback(cc);
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
      g_registry.input->putback(cc);
      cc = '/';
    }
  }
  else if (cc == '#') {
      while (cc != '\n' && cc != '\r' && !g_registry.input->eof()) {
        g_registry.input->get(cc);
      }
      if (!g_registry.input->eof()) {
        g_registry.input->putback(cc);
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
        g_registry.input->putback(cc);
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
      g_registry.input->putback(cc);
    }
    cc = '\n';
  }
  if (cc == '\n') {
    ++phrased_yylloc_last_line;
  }
  return cc;
}
