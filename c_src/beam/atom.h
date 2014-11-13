/*
 * %CopyrightBegin%
 *
 * Copyright Ericsson AB 1996-2013. All Rights Reserved.
 *
 * The contents of this file are subject to the Erlang Public License,
 * Version 1.1, (the "License"); you may not use this file except in
 * compliance with the License. You should have received a copy of the
 * Erlang Public License along with this software. If not, it can be
 * retrieved online at http://www.erlang.org/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * %CopyrightEnd%
 */

#ifndef __ATOM_H__
#define __ATOM_H__

#ifndef __INDEX_H__
#include "index.h"
#endif

#include <stdint.h>

#define MAX_ATOM_CHARACTERS 255
#define MAX_ATOM_SZ_FROM_LATIN1 (2*MAX_ATOM_CHARACTERS)
#define MAX_ATOM_SZ_LIMIT (4*MAX_ATOM_CHARACTERS) /* theoretical byte limit */
#define ATOM_LIMIT (1024*1024)
#define MIN_ATOM_TABLE_SIZE 8192

/*
 * Atom entry.
 */
typedef struct atom {
    IndexSlot slot;  /* MUST BE LOCATED AT TOP OF STRUCT!!! */
    int16_t len;      /* length of atom name (UTF-8 encoded) */
    int16_t latin1_chars; /* 0-255 if atom can be encoded in latin1; otherwise, -1 */
    int ord0;        /* ordinal value of first 3 bytes + 7 bits */
    char* name;      /* name of atom */
} Atom;

extern IndexTable erts_atom_table;

#endif
