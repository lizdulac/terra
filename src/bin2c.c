/*
License: BSD
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
  
  1. Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
  2. Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
  3. The names of the authors may not be used to endorse or promote
     products derived from this software without specific prior
     written permission.
  
THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

static void Abort (char *fmt,...)
{
  va_list args;
  va_start (args, fmt);
  vfprintf (stderr, fmt, args);
  va_end (args);
  exit (1);
}

int main (int argc, char **argv)
{
  FILE  *inFile;
  FILE  *outFile = stdout;
  time_t now     = time (NULL);
  int    ch, i;

  if (argc != 2)
     Abort ("Usage: %s bin-file [> result]", argv[0]);

  if ((inFile = fopen(argv[1],"rb")) == NULL)
     Abort ("Cannot open %s\n", argv[1]);

  fprintf (outFile,
           "/* data statements for file %s at %.24s */\n"
           "/* Generated by BIN2C, G.Vanem 1995 */\n",
           argv[1], ctime(&now));

  i = 0;
  while ((ch = fgetc(inFile)) != EOF)
  {
    if (i++ % 12 == 0)
       fputs ("\n  ", outFile);
    fprintf (outFile, "0x%02X,", ch);
  }
  fputc ('\n', outFile);
  fclose (inFile);
  return (0);
}
