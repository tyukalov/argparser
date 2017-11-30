/* Initialization */
#define OPT_LEN  5
OPTIONS arr[5] ={
  {"p", AP_NONE},
  {"t", AP_OPTIONAL},
  {"-ten", AP_REQUIRED},
  {"v", AP_NONE},
  {"b", AP_REQUIRED}
};
ARGPARSE_ARG marg = {
  '-',
  ' ',
  argc,
  arg,
  5,
  arr
};
