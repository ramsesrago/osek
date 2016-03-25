/*
 * File:        stdlib.h
 * Purpose:     Function prototypes for standard library functions
 *
 * Notes:
 */

#ifndef _STDLIB_H
#define _STDLIB_H

/********************************************************************
 * Standard library functions
 ********************************************************************/

int
isspace (int) __attribute__((weak));

int
isalnum (int) __attribute__((weak));

int
isdigit (int) __attribute__((weak));

int
isupper (int) __attribute__((weak));

int
strcasecmp (const char *, const char *) __attribute__((weak));

int
strncasecmp (const char *, const char *, int) __attribute__((weak));

char *
strcat (char *, const char *) __attribute__((weak));



char *
strcpy (char *, const char *) __attribute__((weak));



int
strcmp (const char *, const char *) __attribute__((weak));




void
free (void *) __attribute__((weak));

uint32
strtoul (char *str, char **ptr, int base) __attribute__((weak));

int
strlen (const char *str) __attribute__((weak));

/********************************************************************/

#endif
