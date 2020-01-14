#pragma once

/* Copyright © 2018-2019 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include "node/Node.h"

typedef struct
{
    size_t count;
    IOStreamDirentry entries[];
} DirectoryListing;

typedef struct
{
    char name[PATH_ELEMENT_LENGHT];
    FsNode *node;
} FsDirectoryEntry;

typedef struct
{
    FsNode node;
    List *childs;
} FsDirectory;

FsNode *directory_create(void);