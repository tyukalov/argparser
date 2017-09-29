#define MAX_OPTION_SIZE		0x100
#define SPACE			'\n'
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
		char	*value;
		int	flag;
	};
} OPTIONS, *RETOPT;


int argparse(ARGPARSE_ARG, RETOPT, int);
int FindOption(RETOPT, char*, int);
void fprinterror(FILE *fd, errcode err, char **argv);
