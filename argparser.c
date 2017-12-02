/* argparser - a small library for parsing command-line arguments
   
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

#include <stdio.h>
#include <stdlib.h>
#include "argparser.h"
#include <string.h>


static int
FindOption(const ARGPARSE_ARG args, const char *opt)
{
	int  result = 0;
	OPTIONS var;
	for(; result < args.len; result++)
	{
		var = args.opts[result];
		if(!strcmp(var.options, opt)) return result;
	}
	return -1;
}


OPTARG
argparse(const ARGPARSE_ARG args)
{
  int count, numcopts, gonumber, valflag = TRUE, beginoptflag = TRUE, beginargflag = TRUE;
  char  *popt, *varval, *varvalex, buf[MAX_OPTION_SIZE];
  OPTARG RESULT;
  POPTION varopt;
  PARGUMENTS vararg;
  RESULT.result = AP_NORMAL;
  RESULT.opt = (POPTION)NULL;
  RESULT.arg = (PARGUMENTS)NULL;
  /*
  popt - pointer to current option;
  varval, varvalex - pointers to option parameter;
  buf - temporary buffer;
  gonumber - option number in array args.opts;
  numcopts - number of combined options;
  beginoptflag, beginargflag - flags indicating whether to create the appropriate linked lists or they already exist
  valflag - a flag that indicates whether an element is a parameter
   */
  for(count=1; count < args.argc; count++)
    {
      if(*(args.argv[count]) == args.prefix)
	{
	  popt = args.argv[count] + 1;
	  if(args.separator == AP_SPACE)
	    {
	      varval = args.argv[count+1];
	    }
	  if((varvalex=strchr(popt, (int)args.separator)) || (varvalex=strchr(popt, (int)ALT_SEPARATOR)))
	    {
	      strncpy(buf, popt, (varvalex - popt));
	      buf[varvalex-popt] = 0;			/* trailing zero */
	      varval = ++varvalex;				/*cut out the symbol of the separator  */
	    }
	  else
	    {
	      strcpy(buf, popt);
	    }
	  gonumber = FindOption(args, buf);
	  if(gonumber >= 0)
	    {
	      INIT(beginoptflag, RESULT, varopt);
	      if(args.opts[gonumber].flag == AP_REQUIRED || args.opts[gonumber].flag == AP_OPTIONAL)
		{
		  if((!varval || (*varval == args.prefix)) && args.opts[gonumber].flag == AP_REQUIRED)
		    {
		      RESULT.result = AP_MISSING_VALUE;
		      return RESULT;
		    }
		  else if(varval && *varval == args.prefix && args.opts[gonumber].flag == AP_OPTIONAL)
		    {
		      varval = NULL;
		    }
		  varopt->value = varval;
		  if(args.separator == AP_SPACE && args.opts[gonumber].flag == AP_REQUIRED) valflag = FALSE;
		}
	      varopt->option = args.opts[gonumber].options;
	    }
	  else
	    {
	      numcopts = strlen(buf) - 1;
	      for(; numcopts>=0; numcopts--)
		/*When passing an optional parameter, the option must be seperate! */ 
		{
		  gonumber = FindOption(args, buf + numcopts);
		  if(gonumber >= 0)
		    {
		      if(args.opts[gonumber].flag == AP_REQUIRED) /* The option with the required parameter must stand alone */
			{
			  RESULT.result = AP_ILLEGAL_USE_OPTIONS;
			  return RESULT;
			}
		      *(buf + numcopts) = 0;
		      INIT(beginoptflag, RESULT, varopt);
		      varopt->option = args.opts[gonumber].options;
		    }
		  else
		    {
		      RESULT.erropt = count;
		      RESULT.result = AP_UNKNOWN_OPTION;
		      return RESULT;
		    }
		}
	    }
	}
      else
	{
	  if (valflag)
	    {
	      if(beginargflag)
		{
		  vararg = RESULT.arg = INITARG;
		  beginargflag = FALSE;
		}
	      else
		{
		  vararg = vararg->next = INITARG;
		}
	      VALIDATOR(vararg, RESULT);
	      vararg->argument = args.argv[count];
	    }
	  else
	    {
	      valflag = TRUE;
	    }
	}
    }
  return RESULT;
}

void
argclean(OPTARG optarg)
{
  POPTION p, popt = optarg.opt;
  PARGUMENTS a, parg = optarg.arg;
  while(popt)
    {
      p = popt -> next;
      free(popt);
      popt = p;
    };
  while(parg)
    {
      a = parg -> next;
      free(parg);
      parg = a;
    };
}

/* Find option */
int
findopt(OPTARG a, const char *o,  char **value)
{
  POPTION opts = a.opt;
  while(opts)
    {
      if(!strcmp(opts->option, o))
	{
	  *value = opts->value;
	  return 0;
	}
      opts = opts->next;
    }
  return -1;
}
