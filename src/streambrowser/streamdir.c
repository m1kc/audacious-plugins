
#include <string.h>
#include <glib.h>

#include "streambrowser.h"
#include "streamdir.h"


streamdir_t* streamdir_new(gchar *name)
{
	streamdir_t *streamdir = (streamdir_t*) g_malloc(sizeof(streamdir_t));
	strncpy(streamdir->name, name, DEF_STRING_LEN);
	streamdir->category_list = NULL;
	
	return streamdir;
}

void streamdir_delete(streamdir_t *streamdir)
{
	GList *iterator;
	category_t *category;

	for (iterator = g_list_first(streamdir->category_list); iterator != NULL; iterator = g_list_next(iterator)) {
		category = iterator->data;		
		category_delete(category);
	}

	g_list_free(streamdir->category_list);
	g_free(streamdir);
}


category_t* category_new(gchar *name)
{
	category_t *category = (category_t*) g_malloc(sizeof(category_t));
	strncpy(category->name, name, DEF_STRING_LEN);
	category->streaminfo_list = NULL;
	
	return category;
}

void category_delete(category_t *category)
{
	GList *iterator;
	streaminfo_t *streaminfo;
	
	for (iterator = g_list_first(category->streaminfo_list); iterator != NULL; iterator = g_list_next(iterator)) {
		streaminfo = iterator->data;
		streaminfo_delete(streaminfo);
	}

	g_list_free(category->streaminfo_list);
	g_free(category);
}

void category_add(streamdir_t *streamdir, category_t *category)
{
	streamdir->category_list = g_list_append(streamdir->category_list, category);
}

void category_remove(streamdir_t *streamdir, category_t *category)
{
	streamdir->category_list = g_list_remove(streamdir->category_list, category);
}

category_t* category_get_by_index(streamdir_t *streamdir, gint index)
{
	return (category_t*) g_list_nth_data(streamdir->category_list, index);
}

category_t* category_get_by_name(streamdir_t *streamdir, gchar *name)
{
	GList *iterator;
	category_t *category;
	
	for (iterator = g_list_first(streamdir->category_list); iterator != NULL; iterator = g_list_next(iterator)) {
		category = iterator->data;
		if (strncasecmp(category->name, name, DEF_STRING_LEN) == 0)
			return category;
	}
	
	return NULL;
}

gint category_get_count(streamdir_t *streamdir)
{
	return g_list_length(streamdir->category_list);
}

gint category_get_index(streamdir_t *streamdir, category_t *category)
{
	return g_list_index(streamdir->category_list, category);
}


streaminfo_t* streaminfo_new(gchar *name, gchar *playlist_url, gchar *current_track)
{
	streaminfo_t *streaminfo = (streaminfo_t*) g_malloc(sizeof(streaminfo_t));
	strncpy(streaminfo->name, name, DEF_STRING_LEN);
	strncpy(streaminfo->playlist_url, playlist_url, DEF_STRING_LEN);
	strncpy(streaminfo->current_track, current_track, DEF_STRING_LEN);

	return streaminfo;
}

void streaminfo_delete(streaminfo_t *streaminfo)
{
	g_free(streaminfo);
}

void streaminfo_add(category_t *category, streaminfo_t *streaminfo)
{
	category->streaminfo_list = g_list_append(category->streaminfo_list, streaminfo);
}

void streaminfo_remove(category_t *category, streaminfo_t *streaminfo)
{
	category->streaminfo_list = g_list_remove(category->streaminfo_list, streaminfo);
}

streaminfo_t* streaminfo_get_by_index(category_t *category, gint index)
{
	return (streaminfo_t*) g_list_nth_data(category->streaminfo_list, index);
}

streaminfo_t* streaminfo_get_by_name(category_t *category, gchar *name)
{
	GList *iterator;
	streaminfo_t *streaminfo;
	
	for (iterator = g_list_first(category->streaminfo_list); iterator != NULL; iterator = g_list_next(iterator)) {
		streaminfo = iterator->data;
		if (strncasecmp(streaminfo->name, name, DEF_STRING_LEN) == 0)
			return streaminfo;
	}
	
	return NULL;
}

gint streaminfo_get_count(category_t *category)
{
	return g_list_length(category->streaminfo_list);
}

gint streaminfo_get_index(category_t *category, streaminfo_t *streaminfo)
{
	return g_list_index(category->streaminfo_list, streaminfo);
}

