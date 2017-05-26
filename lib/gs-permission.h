/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2017 Canonical Ltd.
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

#ifndef __GS_PERMISSION_H
#define __GS_PERMISSION_H

#include <glib-object.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

#define GS_TYPE_PERMISSION (gs_permission_get_type ())

G_DECLARE_FINAL_TYPE (GsPermission, gs_permission, GS, PERMISSION, GObject)

GsPermission	*gs_permission_new_bluetooth		(gboolean	 enabled);
GsPermission	*gs_permission_new_camera		(gboolean	 enabled);
GsPermission	*gs_permission_new_network		(gboolean	 enabled);
GsPermission	*gs_permission_new_media		(gboolean	 enabled);
GsPermission	*gs_permission_new_optical_drive	(gboolean	 enabled);
GsPermission	*gs_permission_new_printing		(gboolean	 enabled);
GsPermission	*gs_permission_new_shutdown		(gboolean	 enabled);

const gchar	*gs_permission_get_metadata_item	(GsPermission	*permission,
							 const gchar	*key);
void		 gs_permission_add_metadata		(GsPermission	*permission,
							 const gchar	*key,
							 const gchar	*value);

const gchar	*gs_permission_get_label		(GsPermission	*permission);
gboolean	 gs_permission_get_enabled		(GsPermission	*permission);
void		 gs_permission_set_enabled		(GsPermission	*permission,
							 gboolean	 enabled);

G_END_DECLS

#endif /* __GS_PERMISSION_H */

/* vim: set noexpandtab: */
