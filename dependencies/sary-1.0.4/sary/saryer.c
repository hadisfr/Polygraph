/* 
 * sary - a suffix array library
 *
 * $Id: saryer.c,v 1.4 2001/12/24 14:10:37 satoru Exp $
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
#include <ctype.h>
#include <sary.h>

/* 
 * Saryer stands for Suffix Array Searcher. 
 */

typedef	gboolean	(*SearchFunc)(Saryer *saryer, 
				      const gchar *pattern, 
				      SaryInt len, 
				      SaryInt offset,
				      SaryInt range);
struct _Saryer {
    SaryInt     len;    /* number of index points */
    SaryText    *text;
    SaryMmap    *array;
    SaryInt  	*first;
    SaryInt     *last;
    SaryInt     *cursor;
    SaryInt	*allocated_data;
    gboolean    is_sorted;
    gboolean    is_allocated;
    SaryPattern	pattern;
    SaryCache	*cache;
    SearchFunc  search;
};

typedef gchar* (*SeekFunc)(const gchar *cursor, 
			   const gchar *sentinel,
			   gconstpointer data);
typedef struct {
    SeekFunc		seek_backward;
    SeekFunc		seek_forward;
    gconstpointer	backward_data;
    gconstpointer	forward_data;
} Seeker;

typedef struct {
    const gchar *str;
    SaryInt len;
} Tag;

static void		init_saryer_states	(Saryer *saryer, 
						 gboolean first_time);
static gboolean		search 			(Saryer *saryer, 
						 const gchar *pattern, 
						 SaryInt len, 
						 SaryInt offset,
						 SaryInt range);
static inline gint	bsearchcmp		(gconstpointer saryer_ptr, 
					 	 gconstpointer obj_ptr);
static inline gint	qsortcmp		(gconstpointer ptr1, 
						 gconstpointer ptr2);
static gboolean		cache_search		(Saryer *saryer, 
						 const gchar *pattern, 
						 SaryInt len, 
						 SaryInt offset,
						 SaryInt range);
static GArray*		icase_search		(Saryer *saryer, 
						 gchar *pattern, 
						 SaryInt len,
						 SaryInt step, 
						 GArray *result);
static gint		expand_letter		(gint *cand, gint c);
static void		assign_range		(Saryer *saryer, 
						 SaryInt *occurences, 
						 SaryInt len);
static gchar*		get_next_region		(Saryer *saryer, 
						 Seeker *seeker,
						 SaryInt *len);
static gchar*		join_subsequent_region	(Saryer *saryer, 
						 Seeker *seeker,
						 gchar *tail);
static gchar*		get_region		(const gchar *head, 
						 const gchar *eof, 
						 SaryInt len);
static gchar*		seek_lines_backward	(const gchar *cursor, 
						 const gchar *bof,
						 gconstpointer n_ptr);
static gchar*		seek_lines_forward 	(const gchar *cursor, 
						 const gchar *eof,
						 gconstpointer n_ptr);
static gchar*		seek_tag_backward	(const gchar *cursor, 
						 const gchar *eof,
						 gconstpointer tag_ptr);
static gchar*		seek_tag_forward	(const gchar *cursor, 
						 const gchar *eof,
						 gconstpointer tag_ptr);

/**
 * saryer_new:
 * @file_name: file name that is searched.
 *
 * Create #Saryer for @file_name. It handles search and its results.
 * Saryer stands for Suffix Array Searcher.
 *
 * Returns: a new #Saryer; NULL if there was a failure.
 *
 **/
Saryer *
saryer_new (const gchar *file_name)
{
    Saryer *saryer;
    gchar *array_name = g_strconcat(file_name, ".ary", NULL);

    saryer = saryer_new2(file_name, array_name);
    g_free(array_name);
    return saryer;
}


/**
 * saryer_new2:
 * @file_name: file name that is searched.
 * @array_name: file name of suffix array.
 *
 * This function is identical to saryer_new except the @array_name
 * parameter specifying the file name of the suffix array.
 *
 * Returns: a new #Saryer; NULL if there was a failure.
 *
 **/
Saryer *
saryer_new2 (const gchar *file_name, const gchar *array_name)
{
    Saryer *saryer = g_new(Saryer, 1);

    saryer->text = sary_text_new(file_name);
    if (saryer->text == NULL) {
	return NULL;
    }

    saryer->array = sary_mmap(array_name, "r");
    if (saryer->array == NULL) {
	return NULL;
    }

    saryer->len    = saryer->array->len / sizeof(SaryInt);
    saryer->search = search;
    saryer->cache  = NULL;

    init_saryer_states(saryer, TRUE);

    return saryer;
}

/**
 * saryer_destroy:
 * @saryer: a #Saryer to be destructed.
 *
 * Destructs the @saryer.
 *
 **/
void
saryer_destroy (Saryer *saryer)
{
    sary_text_destroy(saryer->text);
    sary_cache_destroy(saryer->cache);
    sary_munmap(saryer->array);

    g_free(saryer->allocated_data);
    g_free(saryer);
}

/**
 * saryer_search:
 * @saryer: a #Saryer.
 * @pattern: pattern.
 *
 * Search for @pattern.
 *
 * Returns: %FALSE if an error occurred, %TRUE on success.
 *
 **/
gboolean
saryer_search (Saryer *saryer, const gchar *pattern)
{
    return saryer_search2(saryer, pattern, strlen(pattern));
}

/**
 * saryer_search2:
 * @saryer: a #Saryer.
 * @pattern: pattern.
 * @len: length.
 *
 * Search for @pattern whose length is specified with @len.
 *
 * Returns: %FALSE if an error occurred, %TRUE on success.
 *
 **/
gboolean
saryer_search2 (Saryer *saryer, const gchar *pattern, SaryInt len)
{
    g_assert(saryer != NULL);
    init_saryer_states(saryer, FALSE);

    /*
     * Search the full range of the suffix array.
     */
    return saryer->search(saryer, pattern, len, 0, saryer->len);
}

/**
 * saryer_isearch:
 * @saryer: a #Saryer.
 * @pattern: pattern.
 * @len: length.
 *
 * Similar to saryer_search2 but this function does efficient incremental
 * searchs (isearch stands for `incremental search'). Each search is performed
 * for the range of the previous search results (the first time is identical
 * to saryer_search2). Call the function continuously with the same pattern and
 * increase @len incrementally to the length of @pattern to do incremental
 * searchs. saryer_sort_occurrences MUST not be used together.
 *
 * Returns: %FALSE if an error occurred, %TRUE on success.
 *
 **/
gboolean
saryer_isearch (Saryer *saryer, const gchar *pattern, SaryInt len)
{
    SaryInt offset, range;
    gboolean result;

    g_assert(saryer->pattern.skip <= len && 
	     saryer->is_sorted == FALSE);

    if (saryer->pattern.skip == 0) { /* the first time */
	init_saryer_states(saryer, FALSE);
	offset = 0;
	range  = saryer->len;
    } else {
	offset = (gconstpointer)saryer->first - saryer->array->map;
	range  = saryer_count_occurrences(saryer);
    }

    /*
     * Search the range of the previous search results.
     * Don't use saryer_sort_occurrences together.
     */
    result = saryer->search(saryer, pattern, len, offset, range);
    saryer->pattern.skip = len;
    return result;
}

/**
 * saryer_icase_search:
 * @saryer: a #Saryer.
 * @pattern: pattern.
 *
 * Do case-insensitive search for @pattern.
 *
 * Returns: %FALSE if an error occurred, %TRUE on success.
 *
 **/
gboolean
saryer_icase_search (Saryer *saryer, const gchar *pattern)
{
    return saryer_icase_search2(saryer, pattern, strlen(pattern));
}

/**
 * saryer_icase_search2:
 * @saryer: a #Saryer.
 * @pattern: pattern.
 * @len: length.
 *
 * Do case-insensitive search for @pattern whose length is specified with
 * @len.
 *
 * Returns: %FALSE if an error occurred, %TRUE on success.
 *
 **/
gboolean
saryer_icase_search2 (Saryer *saryer, const gchar *pattern, SaryInt len)
{
    gboolean result;
    GArray *occurences;
    gchar *tmppat;

    g_assert(len >= 0);
    init_saryer_states(saryer, FALSE);

    if (len == 0) { /* match all occurrences */
	return saryer_isearch(saryer, pattern, len);
    }

    tmppat = g_new(gchar, len);  /* for modifications in icase_search. */
    g_memmove(tmppat, pattern, len);

    occurences = g_array_new(FALSE, FALSE, sizeof(SaryInt));
    occurences = icase_search(saryer, tmppat, len, 0, occurences);

    if (occurences->len == 0) { /* not found */
	result = FALSE;
    } else {
	saryer->is_allocated   = TRUE;
	saryer->allocated_data = (SaryInt *)occurences->data;
	assign_range(saryer, saryer->allocated_data, occurences->len);
	result = TRUE;
    }

    g_free(tmppat);
    g_array_free(occurences, FALSE); /* don't free the data */

    return result;
}

/**
 * saryer_isearch_reset:
 * @saryer: a #Saryer.
 *
 * Reset internal states stored for saryer_isearch. To use saryer_isearch
 * with another pattern again, you should call this function beforehand.
 *
 **/
void
saryer_isearch_reset (Saryer *saryer)
{
    saryer->pattern.skip = 0;
}


/**
 * saryer_get_text:
 * @saryer: a #Saryer.
 *
 * Returns: #SaryText of the #Saryer.
 *
 **/
SaryText *
saryer_get_text (Saryer *saryer)
{
    return saryer->text;
}

/**
 * saryer_get_array:
 * @saryer: a #Saryer.
 *
 * Returns: #SaryMMap of the #Saryer.
 *
 **/
SaryMmap *
saryer_get_array (Saryer *saryer)
{
    return saryer->array;
}

/**
 * saryer_get_next_offset:
 * @saryer: a #Saryer.
 *
 * Get the next search result as #SaryText. The function is useful for low-level
 * text processing. The all results can be retrieved by calling the functions
 * continuously.
 *
 * Returns: the next search result as #SaryText; NULL if no more results.
 *
 **/
SaryInt
saryer_get_next_offset (Saryer *saryer)
{
    SaryInt offset;

    if (saryer->cursor > saryer->last) {
	return -1;
    }

    offset = GINT_FROM_BE(*(saryer->cursor));
    saryer->cursor++;

    return offset;
}

/**
 * saryer_get_next_line:
 * @saryer: a #Saryer.
 *
 * Get the next search result line by line as newly created string. The
 * all results can be retrieved by calling the functions continuously.
 *
 * Returns: the next search result line by line as newly created string;
 * NULL if no more results. The returned value MUST be `g_free'ed by caller.
 *
 **/
gchar *
saryer_get_next_line (Saryer *saryer)
{
    /*
     * This function is only a special case of
     * saryer_get_next_context_lines().  If
     * saryer_sort_occurrences() is used and the patttern
     * occurs more than once in the same line, duplicated
     * lines will never returned because of the work of
     * join_subsequent_lines().
     */
    return saryer_get_next_context_lines(saryer, 0, 0);
}

/**
 * saryer_get_next_line2:
 * @saryer: a #Saryer.
 * @len: length.
 *
 * Get the next search result line by line as a pointer. Store the length
 * of the string into @len. The all results can be retrieved by calling
 * the functions continuously.
 *
 * Returns: the next search result line by line as a pointer; NULL if
 * no more results.
 *
 **/
gchar *
saryer_get_next_line2 (Saryer *saryer, SaryInt *len)
{
    return saryer_get_next_context_lines2(saryer, 0, 0, len);
}

/*
 * Act like GNU grep -A -B -C. Subsequent lines are joined
 * not to print duplicated lines if occurrences are sorted. 
 */

/**
 * saryer_get_next_context_lines:
 * @saryer: a #Saryer.
 * @backward: backward.
 * @forward: forward.
 *
 * Get the next search result as context lines as newly created string. The
 * string includes the line feed character '\n' at the end. The all results
 * can be retrieved by calling the functions continuously.
 *
 * Returns: the next search result as context lines as newly created string;
 * NULL if no more results. The returned value MUST be `g_free'ed by caller.
 *
 **/
gchar *
saryer_get_next_context_lines (Saryer *saryer, 
			       SaryInt backward, 
			       SaryInt forward)
{
    gchar *head, *eof;
    SaryInt len;

    eof  = sary_text_get_eof(saryer->text);
    head = saryer_get_next_context_lines2(saryer, backward, forward, &len);

    return get_region(head, eof, len);
}

/*
 * Act like GNU grep -A -B -C. Subsequent lines are joined
 * not to print duplicated lines if occurrences are sorted. 
 */

/**
 * saryer_get_next_context_lines2:
 * @saryer: a #Saryer.
 * @backward: backward.
 * @forward: forward.
 * @len: length.
 *
 * Get the next search result as context lines as a pointer. Store the length
 * of the string into @len. The string includes the line feed character '\n'
 * at the end. The all results can be retrieved by calling the functions
 * continuously.
 *
 * Returns: the next search result as context lines as a pointer; NULL if
 * no more results.
 *
 **/
gchar *
saryer_get_next_context_lines2 (Saryer *saryer, 
				SaryInt backward, 
				SaryInt forward,
				SaryInt *len)
{
    Seeker seeker;
    g_assert(backward >= 0 && forward >=0);

    seeker.seek_backward = seek_lines_backward;
    seeker.seek_forward  = seek_lines_forward;
    seeker.backward_data = &backward;
    seeker.forward_data  = &forward;

    return get_next_region(saryer, &seeker, len);
}


/**
 * saryer_get_next_tagged_region:
 * @saryer: a #Saryer.
 * @start_tag: start tag.
 * @end_tag: end tag.
 *
 * Get the next search result as tagged regions between @start_tag and @end_tag
 * (including @start_tag and @end_tag) as newly created string. The all results
 * can be retrieved by calling the functions continuously.
 *
 * Returns: the next search result as tagged regions as newly created string;
 * NULL if no more results. The returned value MUST be `g_free'ed by caller.
 *
 **/
gchar *
saryer_get_next_tagged_region (Saryer *saryer,
			       const gchar *start_tag,
			       const gchar *end_tag)
{
    gchar *head, *eof;
    SaryInt len;
    SaryInt start_tag_len, end_tag_len;

    start_tag_len = strlen(start_tag);
    end_tag_len   = strlen(end_tag);

    eof  = sary_text_get_eof(saryer->text);
    head = saryer_get_next_tagged_region2(saryer, start_tag, start_tag_len,
					  end_tag, end_tag_len, &len);
    return get_region(head, eof, len);
}

/**
 * saryer_get_next_tagged_region2:
 * @saryer: a #Saryer.
 * @start_tag: start tag.
 * @start_tag_len: length of start tag.
 * @end_tag: end tag.
 * @end_tag_len: length of end tag.
 * @len: length.
 *
 * Get the next search result as tagged regions between @start_tag and @end_tag
 * (including @start_tag and @end_tag) as a pointer. Store the length of the
 * string into @len. The all results can be retrieved by calling the functions
 * continuously.
 *
 * Returns: the next search result as tagged regions as a pointer; NULL if
 * no more results.
 *
 **/
gchar *
saryer_get_next_tagged_region2 (Saryer *saryer,
				const gchar *start_tag,
				SaryInt start_tag_len,
				const gchar *end_tag,
				SaryInt end_tag_len,
				SaryInt *len)
{
    Seeker seeker;
    Tag start, end;

    g_assert(start_tag != NULL && end_tag != NULL);
    g_assert(start_tag_len >= 0 && end_tag_len >= 0);

    start.str = start_tag;
    start.len = start_tag_len;
    end.str   = end_tag;
    end.len   = end_tag_len;

    seeker.seek_backward = seek_tag_backward;
    seeker.seek_forward  = seek_tag_forward;
    seeker.backward_data = &start;
    seeker.forward_data  = &end;

    return get_next_region(saryer, &seeker, len);
}

/*
 * Return the text object whose cursor points to the
 * position of the occurrence in the text. This function is
 * useful for low-level text processing with sary_text_*
 * functions.
 */

/**
 * saryer_get_next_occurrence:
 * @saryer: a #Saryer.
 *
 * Get the next search result as #SaryText. The function is useful for low-level
 * text processing. The all results can be retrieved by calling the functions
 * continuously.
 *
 * Returns: the next search result as #SaryText; NULL if no more results.
 *
 **/
SaryText *
saryer_get_next_occurrence (Saryer *saryer)
{
    gchar *occurrence;

    if (saryer->cursor > saryer->last) {
	return NULL;
    }

    occurrence = sary_i_text(saryer->text, saryer->cursor);
    sary_text_set_cursor(saryer->text, occurrence);
    saryer->cursor++;

    return saryer->text;
}

/**
 * saryer_peek_next_position:
 * @saryer: a #Saryer.
 *
 * Peek the next search results as a position.
 *
 * Returns: the next search results as a position; NULL if no more results.
 *
 **/
gchar *
saryer_peek_next_position (Saryer *saryer)
{
    gchar *occurrence;

    if (saryer->cursor > saryer->last) {
	return NULL;
    }

    occurrence = sary_i_text(saryer->text, saryer->cursor);
    return occurrence;
}

/**
 * saryer_count_occurrences:
 * @saryer: a #Saryer.
 *
 * Get the number of hits of the search.
 *
 * Returns: the number of hits of the search. 
 *
 **/
SaryInt
saryer_count_occurrences (Saryer *saryer)
{
    return saryer->last - saryer->first + 1;
}

/**
 * saryer_sort_occurrences:
 * @saryer: a #Saryer.
 *
 * Sort the occurrences (search results) in occurrence order.
 *
 **/
void
saryer_sort_occurrences (Saryer *saryer)
{
    SaryInt len;

    len = saryer_count_occurrences(saryer);

    if (saryer->is_allocated == FALSE) {
	saryer->allocated_data = g_new(SaryInt, len);
	g_memmove(saryer->allocated_data, 
		  saryer->first, len * sizeof(SaryInt));
	saryer->is_allocated = TRUE;
    }

    qsort(saryer->allocated_data, len, sizeof(SaryInt), qsortcmp);
    assign_range(saryer, saryer->allocated_data, len);
    saryer->is_sorted = TRUE;
}

/**
 * saryer_enable_cache:
 * @saryer: a #Saryer.
 *
 * Enable the cache engine. Cache the search results and reuse them for
 * the same pattern later.
 *
 **/
void
saryer_enable_cache (Saryer *saryer)
{
    saryer->cache  = sary_cache_new();
    saryer->search = cache_search;
}

static void
init_saryer_states(Saryer *saryer, gboolean first_time)
{
    if (!first_time) {
	g_free(saryer->allocated_data);
    }
    saryer->allocated_data = NULL;
    saryer->is_allocated   = FALSE;
    saryer->is_sorted      = FALSE;
    saryer->first     = NULL;
    saryer->last      = NULL;
    saryer->cursor    = NULL;
    saryer->pattern.skip = 0;
}

static gboolean
search (Saryer *saryer, 
	const gchar *pattern, 
	SaryInt len, 
	SaryInt offset,
	SaryInt range)
{
    SaryInt *first, *last;
    SaryInt next_low, next_high;

    g_assert(len >= 0);

    if (saryer->array->map == NULL) {  /* 0-length (empty) file */
	return FALSE;
    }

    saryer->pattern.str = (gchar *)pattern;
    saryer->pattern.len = len;

    first = (SaryInt *)sary_bsearch_first(saryer, 
					  saryer->array->map + offset,
					  range, sizeof(SaryInt), 
					  &next_low, &next_high,
					  bsearchcmp);
    if (first == NULL) {
	return FALSE;
    }

    last  = (SaryInt *)sary_bsearch_last(saryer, 
					 saryer->array->map + offset, 
					 range, sizeof(SaryInt),
					 next_low, next_high,
					 bsearchcmp);
    g_assert(last != NULL);

    saryer->first   = first;
    saryer->last    = last;
    saryer->cursor  = first;

    return TRUE;
}

static inline gint 
bsearchcmp (gconstpointer saryer_ptr, gconstpointer obj_ptr)
{
    gint len1, len2, skip;
    Saryer *saryer  = (Saryer *)saryer_ptr;
    gchar *eof  = sary_text_get_eof(saryer->text);
    gchar *pos = sary_i_text(saryer->text, obj_ptr);

    skip = saryer->pattern.skip;
    len1 = saryer->pattern.len - skip;
    len2 = eof - pos - skip;
    if (len2 < 0) {
	len2 = 0;
    }

    return memcmp(saryer->pattern.str + skip, pos + skip, MIN(len1, len2));
}

static inline gint 
qsortcmp (gconstpointer ptr1, gconstpointer ptr2)
{
    SaryInt occurrence1 = GINT_FROM_BE(*(SaryInt *)ptr1);
    SaryInt occurrence2 = GINT_FROM_BE(*(SaryInt *)ptr2);

    if (occurrence1 < occurrence2) {
	return -1;
    } else if (occurrence1 == occurrence2) {
	return 0;
    } else {
	return 1;
    }
}

static gboolean
cache_search (Saryer *saryer, 
	      const gchar *pattern, 
	      SaryInt len, 
	      SaryInt offset,
	      SaryInt range)
{
    SaryResult *cache;

    if ((cache = sary_cache_get(saryer->cache, pattern, len)) != NULL) {
	saryer->first   = cache->first;
	saryer->last    = cache->last;
	saryer->cursor  = cache->first;
	return TRUE;
    } else {
	gboolean result = search(saryer, pattern, len, offset, range);
	if (result == TRUE) {
	    sary_cache_add(saryer->cache, 
			   sary_i_text(saryer->text, saryer->first), len, 
			   saryer->first, saryer->last);
	}
	return result;
    }
    g_assert_not_reached();
}

static GArray *
icase_search (Saryer *saryer, 
	      gchar *pattern,
	      SaryInt len,
	      SaryInt step, 
	      GArray *result)
{
    gint cand[2], ncand; /* candidates and the number of candidates */
    gint i;

    ncand = expand_letter(cand, (guchar)pattern[step]);
    for (i = 0; i < ncand; i++) {
	SaryInt *orig_first = saryer->first;
	SaryInt *orig_last  = saryer->last;

	pattern[step] = cand[i];
	if (saryer_isearch(saryer, pattern, step + 1)) {
	    if (step + 1 < len) {
		result = icase_search(saryer, pattern, len, step + 1, result);
	    } else if (step + 1 == len) {
		g_array_append_vals(result, saryer->first, 
				    saryer_count_occurrences(saryer));
	    } else {
		g_assert_not_reached();
	    }
	}
	saryer->first = orig_first;
	saryer->last  = orig_last;
	saryer->pattern.skip--;
    }

    return result;
}

static gint
expand_letter (gint *cand, gint c)
{
    if (isalpha(c)) {
	/* 
	 * To preserve lexicographical order, do toupper first.
	 * Assume 'A' < 'a'.
	 */
	cand[0] = toupper(c); 
	cand[1] = tolower(c);
	return 2;
    } else {
	cand[0] = c;
	return 1;
    }
}

static void
assign_range (Saryer *saryer, SaryInt *occurences, SaryInt len)
{
    saryer->first  = occurences;
    saryer->cursor = occurences;
    saryer->last   = occurences + len - 1;
}

static gchar *
get_next_region (Saryer *saryer, Seeker *seeker, SaryInt *len)
{
    gchar *bof, *eof, *cursor;
    gchar *head, *tail;

    if (saryer->cursor > saryer->last) {
	return NULL;
    }

    bof    = sary_text_get_bof(saryer->text);
    eof    = sary_text_get_eof(saryer->text);
    cursor = sary_i_text(saryer->text, saryer->cursor);

    head   = seeker->seek_backward(cursor, bof, seeker->backward_data);
    tail   = seeker->seek_forward(cursor, eof, seeker->forward_data);

    saryer->cursor++; /* Must be called before join_subsequent_region. */
    if (saryer->is_sorted == TRUE) {
	tail = join_subsequent_region(saryer, seeker, tail);
    }

    *len = tail - head;
    return head;
}

static gchar *
join_subsequent_region (Saryer *saryer, Seeker *seeker, gchar *tail)
{
    gchar *bof = sary_text_get_bof(saryer->text);
    gchar *eof = sary_text_get_eof(saryer->text);

    do {
	gchar *next, *next_head;

	next = saryer_peek_next_position(saryer);
	if (next == NULL) {
	    break;
	}
	next_head = seeker->seek_backward(next, bof, seeker->backward_data);
	if (next_head < tail) {
	    saryer_get_next_occurrence(saryer);  /* skip */
	    tail = seeker->seek_forward(next, eof, seeker->forward_data);
	} else {
	    break;
	}
    } while (1);


    return tail;
}

static gchar *
get_region (const gchar *head, const gchar *eof, SaryInt len)
{
    if (head == NULL) {
	return NULL;
    } else {
	return sary_str_get_region(head, eof, len);
    }
}

static gchar *
seek_lines_backward (const gchar *cursor, 
		     const gchar *bof,
		     gconstpointer n_ptr)
{
    SaryInt n = *(gint *)n_ptr;
    return sary_str_seek_lines_backward(cursor, bof, n);
}

static gchar *
seek_lines_forward (const gchar *cursor, 
		    const gchar *eof,
		    gconstpointer n_ptr)
{
    SaryInt n = *(gint *)n_ptr;
    return sary_str_seek_lines_forward(cursor, eof, n);
}

static gchar *
seek_tag_backward (const gchar *cursor, 
		   const gchar *bof,
		   gconstpointer tag_ptr)
{
    Tag *tag = (Tag *)tag_ptr;
    return sary_str_seek_pattern_backward2(cursor, bof, tag->str, tag->len);
}

static gchar *
seek_tag_forward (const gchar *cursor, 
		  const gchar *eof,
		  gconstpointer tag_ptr)
{
    Tag *tag = (Tag *)tag_ptr;
    return sary_str_seek_pattern_forward2(cursor, eof, tag->str, tag->len);
}

