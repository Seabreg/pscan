/**********************************************************************
 * pscan: http://deployingradius.com/pscan/
 *
 * Copyright (C) 2000,2007 Alan DeKok <aland@deployingradius.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 *
 **********************************************************************/
#error Do not compile this file!

/*
 *  This file consists of a number of sample snippets of C code.
 *  Run it through the scanner by doing:
 *
 *    ./pscan ./test.c
 *
 *  You should see a number of problems reported.
 */


/*
 *  This may be a problem.
 */
fprintf(stderr, variable);	/* problematic */

/*
 *  This MIGHT be a problem, depending on where the 'format'
 *  string comes from, and what it's value is.
 */
fprintf(stderr, format, variable1, variable2);

/*
 *  This is safer.
 */
fprintf(stderr, "%s", variable); /* OK */

/*
 *  Constant strings can't be modified externally, so they're OK.
 */
sprintf(buffer, "string");	/* OK */

/*
 *  If you're a dumb enough programmer to put something like this
 *  in the source, you get what you deserve.  But it isn't an
 *  externally exploitable security hole.
 */
sprintf(buffer, "%s");	/* OK */

/*
 *  The variable may contain formatting commands!
 */
sprintf(buffer, variable);	/* problematic */

/*
 *  This is the safe way of doing it.
 */
sprintf(buffer, "%s", variable); /* OK */

/*
 *  The first sprintf is OK, but the second one has a problem.
 *  This is a check for nested security problems.
 */
sprintf(buffer, "%d", sprintf(buffer1, variable)); /* problematic! */

/*
 *  strerror(errno) isn't a problem function, and snprintf has lots
 *  of arguments after the format string, so this is OK.
 */
snprintf(buffer, sizeof(buffer), "test: Error opening %s: %s\n", filename, strerror(errno)); /* OK */

/*
 *  Multi-line sequences get checked, too.  This one should be OK.
 */
snprintf(buffer, sizeof(buffer), "test: Error opening %s: %s\n",
	 filename,
	 strerror(errno)); /* also OK */

/*
 *  This multi-line sequence shouldn't be OK.
 */
sprintf(buffer,
	variable);	/* problematic */

/*
 *  Lots of arguments after the format string.  It's up to your C
 *  compiler to see if you're using the right number of arguments for
 *  the format string.
 */
sprintf(buffer, "%s %s %s", one, two, three); /* OK */

/*
 *  Nested braces should be OK.
 */
printf((variable ? "%4" : "%3s"), string); /* OK */

/*
 *  User-supplied format strings are OK, I guess...
 */
printf((variable ? fmt1 : fmt2), string3); /* OK */

/*
 *  There's still only one argument for printf, that's a problem.
 */
printf((variable ? string1 : string2));	/* problematic */

// sprintf(buffer, variable);	C++ comments get ignored, for good or for bad.

/* sprintf(buffer, variable);	these comments get ignored, too */

/*
 *  This next bit of code is from the wu-ftp source.  It's OK, but it
 *  gets flagged because the parser isn't smart enough to check for
 *  previous, safe, uses of strings.
  */
sprintf(s, "PASV port %i assigned to %s", i, remoteident);
syslog(LOG_DEBUG, s);

/*
 *  The following are references to the functions, but not actual
 *  function calls, so they're OK.
 */
void *foo[] = {snprintf, fprintf}; /* OK */

/*
 *  Your program may define a problem function in one file,
 *  and use a variable of the same name in another file.  We don't
 *  want to complain about uses of those variables.
 *
 *  I know this won't work in a real C program, but it's a way of faking
 *  such a variable reference, to ensure that pscan ignores it.
 */
fprintf[1] = 1;			/* OK */

/*
 *  NetBSD allows err(1,NULL).  We should, too.
 */
err(1, NULL);
