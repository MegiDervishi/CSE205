#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cachelab.h"

// Megi Dervishi megi.dervishi
/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/* Globals set by command line args */
  int verbosity; /* print trace if set */
  int s;         /* set index bits */
  int b;         /* block offset bits */
  int E;         /* associativity */
  int hits;
  int miss;
  int evict;


/*
 * Create Cache which is a 2D array == [sets [lines [v, tag, block]]]
 */
typedef struct scache_lines { 
  int v; //validity
  long long int tag; //64 bit memory address
  char *block;
}cache_lines;

typedef struct scache_sets {cache_lines *lines;} cache_sets;
typedef struct scache { cache_sets *sets;} cache;


cache new_cache(long long sets, int lines, long long block){ //2^s, E, 2^b
  cache_lines clines;
  cache_sets csets;
  cache C;

  C.sets =  (cache_sets *) calloc(sets , (lines));

  for (int i=0; i< sets; i++) {
    C.sets->lines = (cache_lines*) calloc(lines , sizeof(cache_lines));
    C.sets[i] = csets;

    for(int j=0; j < lines; j++) {
      clines.v = 0;
      clines.tag = 0;
      csets.lines[j] = clines;
    }
  }
  return C;
}

/*
 *How does the cache work?
 */



void clear_cache(cache C, long long sets, int lines, long long block){
  if (C.sets != NULL) {
    free(C.sets);
  }
  for (int i = 0; i< sets; i++){
    if (C.sets[i].lines != NULL){
      free(C.sets[i].lines); // function to delete memory
    }
  }
}

/*
 * main - Main routine 
 */
int main(int argc, char* argv[])
{

  new_cache(pow(2,s), E, pow(2,b));
  char c;
  char* trace_file;//dont initialize 
  
  while( (c=getopt(argc,argv,"s:E:b:t:vh")) != -1){
    switch(c){
    case 's':
      s = atoi(optarg);
      break;
    case 'E':
      E = atoi(optarg);
      break;
    case 'b':
      b = atoi(optarg);
      break;
    case 't':
      trace_file = optarg; //parameter used by getopt
      break;
    case 'v':
      verbosity = 1;
      break;
    case 'h':
      printUsage(argv);
      exit(0);
    default:
      printUsage(argv);
      exit(1);
    }
  }

  /* Make sure that all required command line args were specified */
  if (s == 0 || E == 0 || b == 0 || trace_file == NULL) {
    printf("%s: Missing required command line argument\n", argv[0]);
    printUsage(argv);
    exit(1);
  }

  //get the values of e,b,s and assign to create a cache
  /*long long B = pow(2,b);
  long long S = pow(2,s);
  cache C = new_cache(S,E, B);
  miss = 0;
  hits = 0;
  evict = 0; */

  /*FILE *rfile;
  rfile = fopen(trace_file,"r"); //open file

  char operation;
  char address;
  char size;

  while(fscanf(rfile, " %c %x,%d", &operation, &address, &size) == 3){
    // for each case to run replacement thingie and count how many hits and misses there are
  }
  //clear the cache
  clear_cache(C, S, E, B);
  fclose(rfile); //close file*/

  printSummary(hits, miss, evict);
  return 0;
}
