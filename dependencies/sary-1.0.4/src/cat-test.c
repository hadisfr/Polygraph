/* 
 * sary - a suffix array library
 *
 * $Id: cat-test.c,v 1.2 2000/12/04 13:03:36 satoru Exp $
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


#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <errno.h>
#include <sary.h>

static void 	cat			(const gchar *file_name);
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
    cat(file_name);

    return 0;
}

/*
 * Very devious way to `cat' a file. This is a test for
 * saryer_get_next_occurrence().
 */
static void
cat (const gchar *file_name)
{
    Saryer *saryer;
    SaryText *text;

    saryer = saryer_new(file_name);
    if (saryer == NULL) {
	g_printerr("cat-test: %s(.ary): %s\n", file_name, g_strerror(errno));
	exit(EXIT_FAILURE);
    }

    if (saryer_search(saryer, "") == TRUE) {
	saryer_sort_occurrences(saryer);
	while ((text = saryer_get_next_occurrence(saryer))) {
	    gchar *occurence = sary_text_get_cursor(text);
	    g_print("%c", *occurence);
	}
    }
    saryer_destroy(saryer);
}

static void
show_usage (void)
{
    g_print("Usage: cat-test <file>\n");
}

