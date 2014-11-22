#include <stdio.h>
#include "file.h"

char* readFile(FILE** arquivo){
  char* token=NULL;

  fscanf(*arquivo,"%ms",&token);
  return token;
}
