#include <assert.h>
#include <errno.h>
#include <sary.h>

static gint 
search (Saryer *saryer, gchar* pattern, gchar *start, gchar *end)
{
    gint freq = 0;

    if (saryer_search(saryer, pattern)) {
        gchar *line;
        saryer_sort_occurrences(saryer);
        while((line = saryer_get_next_tagged_region(saryer, start, end))) {
	    freq++;
            g_free(line);
        }
    }
    return freq;
}

int
main (int argc, char **argv)
{
    Saryer *saryer;
    gchar *file  = argv[1];

    saryer = saryer_new(file);
    if(saryer == NULL){
        g_print("error: %s(.ary): %s\n", file, g_strerror(errno));
        return 1;
    }

    {
	/*
	 * They differ Sary 1.0.3 or older.
	 */
	gint x, y;
	x = search(saryer, "mmm",  "<p", "</p>");
	y = search(saryer, "mmm",  "<p", "</p");
	assert(x == y);
    }

    saryer_destroy(saryer);
    return 0;
}
