/* File: utiliy.cc
 * ---------------
 * Implementation of simple printing functions to report failures or
 * debugging information triggered by keys.
 */

#include "utility.h"
#include <stdarg.h>
#include <string.h>
#include <vector>
using std::vector;

static vector<const char*> Keys[10];
static const int BufferSize = 2048;

void Failure(const char *format, ...) {
  va_list args;
  char errbuf[BufferSize];
  
  va_start(args, format);
  vsprintf(errbuf, format, args);
  va_end(args);
  fflush(stdout);
  fprintf(stderr,"\n*** Failure: %s\n\n", errbuf);
  abort();
}

int IndexOf(const char *key, CmdParam cmdparam) {
  for (unsigned int i = 0; i < Keys[cmdparam].size(); i++)
    if (!strcmp(Keys[cmdparam][i], key)) 
      return i;

  return -1;
}

bool IsDebugOn(const char *key) {
  return (IndexOf(key, debug) != -1);
}

bool IsTypeOn(const char *key) {
  return (IndexOf(key, type) != -1);
}

void SetKey(const char *key, bool value, CmdParam cmdparam) {
  int k = IndexOf(key, cmdparam);
  if (!value && k != -1)
    Keys[cmdparam].erase(Keys[cmdparam].begin() + k);
  else if (value && k == -1)
    Keys[cmdparam].push_back(key);
}

void PrintDebug(const char *key, const char *format, ...) {
  va_list args;
  char buf[BufferSize];

  if (!IsDebugOn(key))
     return;
  
  va_start(args, format);
  vsprintf(buf, format, args);
  va_end(args);
  printf("+++ (%s): %s%s", key, buf, buf[strlen(buf)-1] != '\n'? "\n" : "");
}

void ParseCommandLine(int argc, char *argv[]) {
  if (argc == 1)
    return;
  
  CmdParam c;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
        if (strcmp(argv[i], "-d") == 0) {
          c = debug;
          continue;
        }
        if (strcmp(argv[i], "-t") == 0) {
          c = type;
          continue;
        }
        printf("Incorrect Use:   ");
        for (int i = 1; i < argc; i++) printf("%s ", argv[i]);
        printf("\n");
        printf("Correct Usage:   -d <tac> ... \n");
        printf("                 -t <mars> ... \n");
        exit(2);
    }
    SetKey(argv[i],true, c);
  }
}

