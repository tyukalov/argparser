/* definition for argparser
   
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Igor 'sp_r00t' Tyukalov <tyukalov@bk.ru> */

#define MAX_OPTION_SIZE		0x100
#define SPACE			' '
#define TRUE			0x1
#define FALSE			0x0

#define VALIDATOR(A, R)				\
  if((A) == NULL){\
    R.result = MEMORY_ERROR;\
    return R;\
  }
#define INITOPT (POPTION)calloc(1,sizeof(OPTION))
#define INITARG (PARGUMENTS)calloc(1,sizeof(ARGUMENTS))

#define INIT(F, R, V)\
  if((F)){\
    (V) = R.opt = INITOPT;			\
    F = FALSE;				\
  }\
  else\
    {\
      (V) = V->next = INITOPT;		\
    };\
  VALIDATOR (V, R)

/* ------------------------------------------- Interface -------------------------------------------- */
/* Strunctures and enums */
typedef enum {
  NORMAL  = 0,
  ILLEGAL_USE_OPTIONS ,
  MISSING_VALUE,
  UNKNOWN_OPTION,
  MEMORY_ERROR,
} errcode;

typedef enum {
  NONE,
  REQUIRED,
  OPTIONAL,
} optflag;

typedef struct {
  char		*options;
  optflag	          flag;
} OPTIONS, *RETOPT;


typedef struct {
  const char		   prefix;
  const char		   separator;
  int		           argc;
  char		   **argv;
  int                    len;
  RETOPT      opts;
}ARGPARSE_ARG;

typedef struct OPTION{
  char   *option;
  char   *value;
  struct OPTION *next;
} OPTION, *POPTION;

typedef struct ARGUMENTS{
  char   *argument;
  struct ARGUMENTS *next;
} ARGUMENTS, *PARGUMENTS;

typedef struct{
  errcode   result;
  int erropt;
  POPTION   opt;
  PARGUMENTS   arg;
} OPTARG;

/* Functions */
OPTARG argparse(const ARGPARSE_ARG);
void argclean(OPTARG);
