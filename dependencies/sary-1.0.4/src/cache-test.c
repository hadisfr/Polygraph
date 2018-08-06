/* 
 * sary - a suffix array library
 *
 * $Id: cache-test.c,v 1.2 2000/12/04 13:03:36 satoru Exp $
 *
 * Copyright (C) 2000  Satoru Takabayashi <satoru@namazu.org>
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Test for the cache mechanism. Effect of the cache can be
 * measured with search-benchmark.
 *
 *  % cp /usr/dict/words .
 *  % mksary -l words
 *  % ./cache-test words
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <errno.h>
#include <sary.h>

static void 	cache_test		(const gchar *file_name);
static Saryer *	new			(const gchar *file_name);
static void 	show_usage		(void);

int 
main (int argc, char **argv)
{
    gchar *file_name;

    if (argc != 2) {
	show_usage();
	exit(EXIT_FAILURE);
    }

    file_name = argv[1];
    cache_test(file_name);

    return 0;
}

static void
cache_test (const gchar *file_name)
{
    Saryer *saryer1;
    Saryer *saryer2;
    gint i;
    gchar  pattern[BUFSIZ];
    FILE *fp = fopen(file_name, "r");
    g_assert(fp != NULL);

    saryer1 = new(file_name);
    saryer2 = new(file_name);
    saryer_enable_cache(saryer2);

    for (i = 0; i < 10; i++) {
	while (fgets(pattern, BUFSIZ, fp) != NULL) {
	    gchar *line1, *line2;

	    saryer_search(saryer1, pattern);
	    saryer_search(saryer2, pattern);

	    line1 = saryer_get_next_line(saryer1);
	    line2 = saryer_get_next_line(saryer2);
	    g_assert(line1 != NULL && line2 != NULL);
	    g_assert(strcmp(line1, line2) == 0);

	    line1 = saryer_get_next_line(saryer1);
	    line2 = saryer_get_next_line(saryer2);
	    g_assert(line1 == NULL && line2 == NULL);
	}
	rewind(fp);
    }
    saryer_destroy(saryer1);
    saryer_destroy(saryer2);
}

static Saryer *
new (const gchar *file_name)
{
    Saryer *saryer = saryer_new(file_name);

    if (saryer == NULL) {
	g_printerr("cache-test: %s(.ary): %s\n", 
		   file_name, g_strerror(errno));
	exit(EXIT_FAILURE);
    }
    return saryer;
}

static void
show_usage (void)
{
    g_print("Usage: cache-test <file>\n");
}

