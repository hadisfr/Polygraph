#ifndef __SARY_SARYER_H__
#define __SARY_SARYER_H__

#include <glib.h>
#include <sary/mmap.h>
#include <sary/text.h>
#include <sary/i.h>
#include <sary/saryconfig.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _Saryer 		Saryer;

typedef struct {
    const gchar *str;
    SaryInt len;   /* length of pattern */
    SaryInt skip;  /* length of bytes which can be skipped */
} SaryPattern;

typedef struct {
    SaryInt  *first;
    SaryInt  *last;
} SaryResult;


Saryer*		saryer_new			(const gchar 
						 *file_name);
Saryer*		saryer_new2			(const gchar *file_name, 
						 const gchar *array_name);
void		saryer_destroy			(Saryer *saryer);
gboolean	saryer_search			(Saryer *saryer, 
						 const gchar *pattern);
gboolean	saryer_search2			(Saryer *saryer, 
						 const gchar *pattern, 
						 SaryInt len);
gboolean	saryer_isearch			(Saryer *saryer, 
						 const gchar *pattern, 
						 SaryInt len);
void		saryer_isearch_reset		(Saryer *saryer);
gboolean	saryer_icase_search		(Saryer *saryer, 
						 const gchar *pattern);
gboolean	saryer_icase_search2		(Saryer *saryer, 
						 const gchar *pattern, 
						 SaryInt len);
SaryText*	saryer_get_text			(Saryer *saryer);
SaryMmap*	saryer_get_array		(Saryer *saryer);
SaryInt         saryer_get_next_offset          (Saryer *saryer);
gchar*		saryer_get_next_line		(Saryer *saryer);
gchar*		saryer_get_next_line2		(Saryer *saryer, 
						 SaryInt *len);
gchar*		saryer_get_next_context_lines	(Saryer *saryer, 
						 SaryInt backward, 
						 SaryInt forward);
gchar*		saryer_get_next_context_lines2	(Saryer *saryer, 
						 SaryInt backward, 
						 SaryInt forward,
						 SaryInt *len);
gchar*		saryer_get_next_tagged_region	(Saryer *saryer, 
						 const gchar *start_tag,
						 const gchar *end_tag);
gchar*		saryer_get_next_tagged_region2	(Saryer *saryer,
						 const gchar *start_tag,
						 SaryInt start_tag_len,
						 const gchar *end_tag,
						 SaryInt end_tag_len,
						 SaryInt *len);
SaryText*	saryer_get_next_occurrence	(Saryer *saryer);
gchar*		saryer_peek_next_position	(Saryer *saryer);
SaryInt		saryer_count_occurrences	(Saryer *saryer);
void		saryer_sort_occurrences		(Saryer *saryer);
void		saryer_enable_cache		(Saryer *saryer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SARY_SARYER_H__ */
