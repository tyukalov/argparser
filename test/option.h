/* Initialization */
#define OPT_LEN  5
OPTIONS arr[5] ={
  {"p", FALSE},
  {"t", FALSE},
  {"-ten", TRUE},
  {"v", FALSE},
  {"b", TRUE}
};
ARGPARSE_ARG marg = {
  '-',
  ' ',
  argc,
  arg,
  5,
  arr
};
