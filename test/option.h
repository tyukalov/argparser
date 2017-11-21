/* Initialization */
#define OPT_LEN  5
OPTIONS arr[5] ={
  {"p", NONE},
  {"t", OPTIONAL},
  {"-ten", REQUIRED},
  {"v", NONE},
  {"b", REQUIRED}
};
ARGPARSE_ARG marg = {
  '-',
  ' ',
  argc,
  arg,
  5,
  arr
};
