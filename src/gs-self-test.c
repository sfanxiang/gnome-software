/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2017 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "config.h"

#include "gnome-software-private.h"

#include "gs-common.h"
#include "gs-test.h"

static void
gs_common_func (void)
{
	const gchar *css;
	g_autoptr(GError) error = NULL;
	g_autoptr(GHashTable) hash1 = NULL;
	g_autoptr(GHashTable) hash2 = NULL;

	/* hash, no IDs */
	hash1 = gs_utils_parse_css_ids ("border: 0;", &error);
	g_assert_no_error (error);
	g_assert (hash1 != NULL);
	css = g_hash_table_lookup (hash1, "");
	g_assert_cmpstr (css, ==, "border: 0;");

	/* hash IDs */
	hash2 = gs_utils_parse_css_ids ("#tile{\nborder: 0;}\n#name {color: white;\n}", &error);
	g_assert_no_error (error);
	g_assert (hash2 != NULL);
	css = g_hash_table_lookup (hash2, "");
	g_assert_cmpstr (css, ==, NULL);
	css = g_hash_table_lookup (hash2, "tile");
	g_assert_cmpstr (css, ==, "border: 0;");
	css = g_hash_table_lookup (hash2, "name");
	g_assert_cmpstr (css, ==, "color: white;");
}

int
main (int argc, char **argv)
{
	g_test_init (&argc, &argv, NULL);
	g_setenv ("G_MESSAGES_DEBUG", "all", TRUE);

	/* only critical and error are fatal */
	g_log_set_fatal_mask (NULL, G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL);

	/* tests go here */
	g_test_add_func ("/gnome-software/src/common", gs_common_func);

	return g_test_run ();
}

/* vim: set noexpandtab: */
