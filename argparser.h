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
#define ILLEGAL_USE_OPTIONS	-0x1000
#define MISSING_VALUE		-0x2000
typedef int errcode;
typedef struct {
	char		prefix;
	char		separator;
	int		argc;
	char		**argv;
}ARGPARSE_ARG;

typedef struct {
	char		*options;
	union{
		int	flag;
		char	*value;
	};
} OPTIONS, *RETOPT;


int argparse(ARGPARSE_ARG, RETOPT, int);
int FindOption(RETOPT, char*, int);
void fprinterror(FILE *fd, errcode err, char **argv);
