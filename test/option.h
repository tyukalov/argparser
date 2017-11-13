/* Initialization */
#define OPT_LEN  5
ARGPARSE_ARG marg = {
  '-',
  SPACE,
  argc,
  arg
};
OPTIONS ptrn[] = {
  {"p", FALSE},
  {"t", FALSE},
  {"-ten", TRUE},
  {"v", FALSE},
  {"b", TRUE}
};
