#ifndef UPNPFILEINFO_H
#define UPNPFILEINFO_H

/*!
 * \file
 *
 * \brief Header file for UpnpFileInfo methods.
 *
 * Do not edit this file, it is automatically generated. Please look at
 * generator.c.
 *
 * \author Marcelo Roberto Jimenez
 */
#include <stdlib.h> /* for size_t */

#include "UpnpGlobal.h" /* for UPNP_EXPORT_SPEC */

#include "UpnpInet.h"
#include "UpnpString.h"
#include "ixml.h"
#include "list.h"
#include <sys/types.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*!
 * UpnpFileInfo
 */
typedef struct s_UpnpFileInfo UpnpFileInfo;

/*! Constructor */
UPNP_EXPORT_SPEC UpnpFileInfo *UpnpFileInfo_new();
/*! Destructor */
UPNP_EXPORT_SPEC void UpnpFileInfo_delete(UpnpFileInfo *p);
/*! Copy Constructor */
UPNP_EXPORT_SPEC UpnpFileInfo *UpnpFileInfo_dup(const UpnpFileInfo *p);
/*! Assignment operator */
UPNP_EXPORT_SPEC int UpnpFileInfo_assign(
	UpnpFileInfo *p, const UpnpFileInfo *q);

/*! UpnpFileInfo_get_FileLength */
UPNP_EXPORT_SPEC off_t UpnpFileInfo_get_FileLength(const UpnpFileInfo *p);
/*! UpnpFileInfo_set_FileLength */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_FileLength(UpnpFileInfo *p, off_t n);

/*! UpnpFileInfo_get_LastModified */
UPNP_EXPORT_SPEC time_t UpnpFileInfo_get_LastModified(const UpnpFileInfo *p);
/*! UpnpFileInfo_set_LastModified */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_LastModified(UpnpFileInfo *p, time_t n);

/*! UpnpFileInfo_get_IsDirectory */
UPNP_EXPORT_SPEC int UpnpFileInfo_get_IsDirectory(const UpnpFileInfo *p);
/*! UpnpFileInfo_set_IsDirectory */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_IsDirectory(UpnpFileInfo *p, int n);

/*! UpnpFileInfo_get_IsReadable */
UPNP_EXPORT_SPEC int UpnpFileInfo_get_IsReadable(const UpnpFileInfo *p);
/*! UpnpFileInfo_set_IsReadable */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_IsReadable(UpnpFileInfo *p, int n);

/*! UpnpFileInfo_get_ContentType */
UPNP_EXPORT_SPEC const DOMString UpnpFileInfo_get_ContentType(
	const UpnpFileInfo *p);
/*! UpnpFileInfo_set_ContentType */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_ContentType(
	UpnpFileInfo *p, const DOMString s);
/*! UpnpFileInfo_get_ContentType_cstr */
UPNP_EXPORT_SPEC const char *UpnpFileInfo_get_ContentType_cstr(
	const UpnpFileInfo *p);

/*! UpnpFileInfo_get_ExtraHeadersList */
UPNP_EXPORT_SPEC const UpnpListHead *UpnpFileInfo_get_ExtraHeadersList(
	const UpnpFileInfo *p);
/*! UpnpFileInfo_set_ExtraHeadersList */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_ExtraHeadersList(
	UpnpFileInfo *p, const UpnpListHead *q);
/*! UpnpFileInfo_add_to_list_ExtraHeadersList */
UPNP_EXPORT_SPEC void UpnpFileInfo_add_to_list_ExtraHeadersList(
	UpnpFileInfo *p, UpnpListHead *head);

/*! UpnpFileInfo_get_CtrlPtIPAddr */
UPNP_EXPORT_SPEC const struct sockaddr_storage *UpnpFileInfo_get_CtrlPtIPAddr(
	const UpnpFileInfo *p);
/*! UpnpFileInfo_get_CtrlPtIPAddr */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_CtrlPtIPAddr(
	UpnpFileInfo *p, const struct sockaddr_storage *buf);
/*! UpnpFileInfo_get_CtrlPtIPAddr */
UPNP_EXPORT_SPEC void UpnpFileInfo_clear_CtrlPtIPAddr(UpnpFileInfo *p);

/*! UpnpFileInfo_get_Os */
UPNP_EXPORT_SPEC const UpnpString *UpnpFileInfo_get_Os(const UpnpFileInfo *p);
/*! UpnpFileInfo_set_Os */
UPNP_EXPORT_SPEC int UpnpFileInfo_set_Os(UpnpFileInfo *p, const UpnpString *s);
/*! UpnpFileInfo_get_Os_Length */
UPNP_EXPORT_SPEC size_t UpnpFileInfo_get_Os_Length(const UpnpFileInfo *p);
/*! UpnpFileInfo_get_Os_cstr */
UPNP_EXPORT_SPEC const char *UpnpFileInfo_get_Os_cstr(const UpnpFileInfo *p);
/*! UpnpFileInfo_strcpy_Os */
UPNP_EXPORT_SPEC int UpnpFileInfo_strcpy_Os(UpnpFileInfo *p, const char *s);
/*! UpnpFileInfo_strncpy_Os */
UPNP_EXPORT_SPEC int UpnpFileInfo_strncpy_Os(
	UpnpFileInfo *p, const char *s, size_t n);
/*! UpnpFileInfo_clear_Os */
UPNP_EXPORT_SPEC void UpnpFileInfo_clear_Os(UpnpFileInfo *p);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UPNPFILEINFO_H */
