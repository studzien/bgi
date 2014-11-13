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

/*
** General hash and index functions
** The idea behind this file was to capture the
** way Atom,Export and Module table was implemented
*/
#ifndef __INDEX_H__
#define __INDEX_H__

#ifndef __HASH_H__
#include "hash.h"
#endif

#include "types.h"

typedef struct index_slot 
{
    HashBucket bucket;
    int index;
} IndexSlot;


typedef struct index_table
{
    Hash htable;		/* Mapping obj -> index */
    ErtsAlcType_t type;
    int size;			/* Allocated size */
    int limit;			/* Max size */
    int entries;		/* Number of entries */
    IndexSlot*** seg_table;	/* Mapping index -> obj */
} IndexTable;

#define INDEX_PAGE_SHIFT 10
#define INDEX_PAGE_SIZE (1 << INDEX_PAGE_SHIFT)
#define INDEX_PAGE_MASK ((1 << INDEX_PAGE_SHIFT)-1)

static inline IndexSlot* erts_index_lookup(IndexTable* t, unsigned int ix)
{
    return t->seg_table[ix>>INDEX_PAGE_SHIFT][ix&INDEX_PAGE_MASK];
}

#endif
