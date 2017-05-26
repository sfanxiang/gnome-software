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

#include "config.h"

#include <glib/gi18n.h>

#include "gs-permission.h"

struct _GsPermission
{
	GObject			 parent_instance;

	gchar			*label;
	gboolean		 enabled;
	GHashTable		*metadata;	/* utf8: utf8 */
};

G_DEFINE_TYPE (GsPermission, gs_permission, G_TYPE_OBJECT)

/**
 * gs_permission_get_metadata_item:
 * @auth: a #GsPermission
 * @key: a string
 *
 * Gets some metadata from a permission object.
 * It is left for the the plugin to use this method as required, but a
 * typical use would be to retrieve an ID for this permission.
 *
 * Returns: A string value, or %NULL for not found
 */
const gchar *
gs_permission_get_metadata_item (GsPermission *auth, const gchar *key)
{
	g_return_val_if_fail (GS_IS_PERMISSION (auth), NULL);
	g_return_val_if_fail (key != NULL, NULL);
	return g_hash_table_lookup (auth->metadata, key);
}

/**
 * gs_permission_add_metadata:
 * @auth: a #GsPermission
 * @key: a string
 * @value: a string
 *
 * Adds metadata to the permission object.
 * It is left for the the plugin to use this method as required, but a
 * typical use would be to store an ID for this permission.
 */
void
gs_permission_add_metadata (GsPermission *auth, const gchar *key, const gchar *value)
{
	g_return_if_fail (GS_IS_PERMISSION (auth));
	g_hash_table_insert (auth->metadata, g_strdup (key), g_strdup (value));
}

/**
 * gs_permission_get_label:
 * @permission: a #GsPermission
 *
 * Get the label for this permission.
 *
 * Returns: a label string.
 */
const gchar *
gs_permission_get_label (GsPermission *permission)
{
	g_return_val_if_fail (GS_IS_PERMISSION (permission), NULL);
	return permission->label;
}

/**
 * gs_permission_get_enabled:
 * @permission: a #GsPermission
 *
 * Get if this permission is enabled.
 *
 * Returns: %TRUE if enabled
 */
gboolean
gs_permission_get_enabled (GsPermission *permission)
{
	g_return_val_if_fail (GS_IS_PERMISSION (permission), 0);
	return permission->enabled;
}

/**
 * gs_permission_set_enabled:
 * @permission: a #GsPermission
 * @enabled: %TRUE if this permission is enabled.
 *
 * Set if this permission is enabled.
 */
void
gs_permission_set_enabled (GsPermission *permission, gboolean enabled)
{
	g_return_if_fail (GS_IS_PERMISSION (permission));
	permission->enabled = enabled;
}

static void
gs_permission_finalize (GObject *object)
{
	GsPermission *permission = GS_PERMISSION (object);

	g_free (permission->label);
	g_hash_table_unref (permission->metadata);

	G_OBJECT_CLASS (gs_permission_parent_class)->finalize (object);
}

static void
gs_permission_class_init (GsPermissionClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->finalize = gs_permission_finalize;
}

static void
gs_permission_init (GsPermission *permission)
{
	permission->metadata = g_hash_table_new_full (g_str_hash, g_str_equal,
						      g_free, g_free);
}

static GsPermission *
gs_permission_new (const gchar *label, gboolean enabled)
{
	GsPermission *permission;
	permission = g_object_new (GS_TYPE_PERMISSION, NULL);
	permission->label = g_strdup (label);
	permission->enabled = enabled;
	return GS_PERMISSION (permission);
}

/**
 * gs_permission_new_camera:
 * @enabled: %TRUE if camera access is enabled.
 *
 * Creates a new permission object for camera access.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_camera (gboolean enabled)
{
	return gs_permission_new (_("Can acquire photos / video from cameras"), enabled);
}

/**
 * gs_permission_new_bluetooth:
 * @enabled: %TRUE if Bluetooth access is enabled.
 *
 * Creates a new permission object for Bluetooth access.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_bluetooth (gboolean enabled)
{
	return gs_permission_new (_("Can access Bluetooth devices"), enabled);
}

/**
 * gs_permission_new_network:
 * @enabled: %TRUE if network access is enabled.
 *
 * Creates a new permission object for network access.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_network (gboolean enabled)
{
	return gs_permission_new (_("Can access the network"), enabled);
}

/**
 * gs_permission_new_media:
 * @enabled: %TRUE if removable media is enabled.
 *
 * Creates a new permission object for removable media.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_media (gboolean enabled)
{
	return gs_permission_new (_("Can access removable media (USB drives etc)"), enabled);
}

/**
 * gs_permission_new_optical_drive:
 * @enabled: %TRUE if optical drive access is enabled.
 *
 * Creates a new permission object for optical drive access.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_optical_drive (gboolean enabled)
{
	return gs_permission_new (_("Can access optical drives (CD, DVD etc)"), enabled);
}

/**
 * gs_permission_new_printing:
 * @enabled: %TRUE if printing access is enabled.
 *
 * Creates a new permission object for printing access.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_printing (gboolean enabled)
{
	return gs_permission_new (_("Can print documents"), enabled);
}

/**
 * gs_permission_new_shutdown:
 * @enabled: %TRUE if shutdown / restart is allowed.
 *
 * Creates a new permission object for shutdown / restart of this machine.
 *
 * Return value: a new #GsPermission object.
 **/
GsPermission *
gs_permission_new_shutdown (gboolean enabled)
{
	return gs_permission_new (_("Can shutdown / restart this computer"), enabled);
}

/* vim: set noexpandtab: */
