/* 
 * sary - a suffix array library
 *
 * $Id: text.c,v 1.3 2000/12/14 08:55:00 rug Exp $
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
 * Class for `mmap'ed text files.
 */

#include "config.h"
#include <string.h>
#include <glib.h>
#include <sary.h>

/**
 * sary_text_new:
 * @file_name: file name.
 *
 * Create #SaryText for the @file_name.
 *
 * Returns: a new #SaryText; NULL if there was a failure.
 *
 **/
SaryText *
sary_text_new (const gchar *file_name)
{
    SaryText *text;
    SaryMmap *mobj;

    g_assert(file_name != NULL);

    mobj = sary_mmap(file_name, "r");
    if (mobj == NULL) {
	return NULL;
    }

    /*
     * zero-length (empty) text file can be handled. In that
     * case, text->{bol,eof,cursor} are NULL. Be careful!
     */
    text = g_new(SaryText, 1);
    text->mobj      = mobj;
    text->bof       = (gchar *)mobj->map;
    text->eof       = (gchar *)mobj->map + mobj->len;  /* sentinel */
    text->cursor    = (gchar *)mobj->map;
    text->lineno    = 1;  /* 1-origin */
    text->file_name = g_strdup(file_name);

    return text;
}

/**
 * sary_text_destroy:
 * @text: a #SaryText to be destructed.
 *
 * Destructs @text.
 *
 **/
void
sary_text_destroy (SaryText *text)
{
    sary_munmap(text->mobj);
    g_free(text->file_name);
    g_free(text);
}

SaryInt
sary_text_get_size (SaryText *text)
{
    return text->eof - text->bof;
}


/**
 * sary_text_get_lineno:
 * @text: a #SaryText.
 *
 * Get the line number of the cursor position. (No useful for libsary).
 *
 * Returns: the line number of the cursor position.
 *
 **/
SaryInt
sary_text_get_lineno (SaryText *text)
{
    return text->lineno;
}

/**
 * sary_text_set_lineno:
 * @text: a #SaryText.
 * @lineno: the line number of the cursor position.
 *
 * Set @lineno. (No useful for libsary)
 *
 **/
void
sary_text_set_lineno (SaryText *text, SaryInt lineno)
{
    text->lineno = lineno;
}

/**
 * sary_text_get_linelen:
 * @text: a #SaryText.
 *
 * Returns: the line length of the cursor position; 0 (if the cursor is
 * on the end of file). The length includes the line feed character '\n'.
 *
 **/
SaryInt
sary_text_get_linelen (SaryText *text)
{
    return sary_str_get_linelen(text->cursor, text->bof, text->eof);
}

/**
 * sary_text_get_line:
 * @text: a #SaryText.
 *
 * Returns: the newly creatd string of the line of the cursor position;
 * NULL (if cursor is on the end of file). The string includes the line
 * feed character '\n'. The returned value MUST be `g_free'ed by caller.
 *
 **/
gchar *
sary_text_get_line (SaryText *text)
{
    return sary_str_get_line(text->cursor, text->bof, text->eof);
}

/**
 * sary_text_get_region:
 * @cursor: a #SaryText.
 * @len: length.
 *
 * Get the newly creatd string of the region starting at the the cursor,
 * position through @len.
 *
 * Returns: the newly creatd string of the region. The returned value MUST
 * be `g_free'ed by caller.
 *
 **/
gchar *
sary_text_get_region (SaryText *text, SaryInt len)
{
    return sary_str_get_region(text->cursor, text->eof, len);
}


/**
 * sary_text_is_eof:
 * @text: a #SaryText.
 *
 * Returns: %TRUE if the cursor is on the end of file, %FALSE otherwise.
 *
 **/
gboolean
sary_text_is_eof (SaryText *text)
{
    if (text->cursor == text->eof) {
	return TRUE;
    } else {
	return FALSE;
    }
}

/**
 * sary_text_get_cursor:
 * @text: a #SaryText.
 *
 * Returns: the cursor position.
 *
 **/
gchar *
sary_text_get_cursor (SaryText *text)
{
    return text->cursor;
}

/**
 * sary_text_set_cursor:
 * @text: a #SaryText.
 * @cursor: cursor.
 *
 * Set the cursor position.
 *
 **/
void
sary_text_set_cursor (SaryText *text, gchar *cursor)
{
    text->cursor = cursor;
}

/**
 * sary_text_goto_bol:
 * @text: a #SaryText.
 *
 * Forward the cursor position to the beginning of line.
 *
 * Returns: the moved cursor position.
 *
 **/
gchar *
sary_text_goto_bol (SaryText *text)
{
    text->cursor = sary_str_seek_bol(text->cursor, text->bof);
    return text->cursor;
}

/**
 * sary_text_goto_eol:
 * @text: a #SaryText.
 *
 * Forward the cursor position to the end of line.
 *
 * Returns: the moved cursor position.
 *
 **/
gchar *
sary_text_goto_eol (SaryText *text)
{
    text->cursor = sary_str_seek_eol(text->cursor, text->eof);
    return text->cursor;
}

/**
 * sary_text_goto_next_line:
 * @text: a #SaryText.
 *
 * Forward the cursor position to the next line.
 *
 * Returns: the moved cursor position.
 *
 **/
gchar *
sary_text_goto_next_line (SaryText *text)
{
    text->cursor = sary_str_seek_eol(text->cursor, text->eof);
    g_assert(text->cursor <= text->eof);
    text->lineno++;
    return text->cursor;
}

/**
 * sary_text_goto_next_word:
 * @text: a #SaryText.
 *
 * Forward the cursor position to the next word. The word is a string
 * delimited by whitespaces.
 *
 * Returns: the moved cursor position.
 *
 **/
gchar *
sary_text_goto_next_word (SaryText *text)
{
    text->cursor = sary_str_seek_forward(text->cursor, 
					 text->eof, 
					 sary_str_get_whitespaces());
    text->cursor = sary_str_skip_forward(text->cursor, 
					 text->eof,
					 sary_str_get_whitespaces());
    return text->cursor;
}

/**
 * sary_text_forward_cursor:
 * @text: a #SaryText.
 * @len: length.
 *
 * Forward the cursor position step bytes.
 *
 * Returns: the moved cursor position.
 *
 **/
gchar *
sary_text_forward_cursor (SaryText *text, SaryInt len)
{
    g_assert(len >= 0);

    text->cursor += len;
    if (text->cursor > text->eof) { /* overrun */
	text->cursor = text->eof;
    }
    return text->cursor;
}

/**
 * sary_text_backward_cursor:
 * @text: a #SaryText.
 * @len: length.
 *
 * Back the cursor position step bytes.
 *
 * Returns: the moved cursor position.
 *
 **/
gchar *
sary_text_backward_cursor (SaryText *text, SaryInt len)
{
    g_assert(len >= 0);

    text->cursor -= len;
    if (text->cursor < text->bof) { /* overrun */
	text->cursor = text->bof;
    }
    return text->cursor;
}

