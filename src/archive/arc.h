#pragma once

#ifndef __ARC_H__
#define __ARC_H__

typedef struct arc_header_t
{
    char id[4];
    int entry_count;
    int directory;
} arc_header_t;

typedef struct arc_entry_t
{
    int offset;
    int size;
    char name[8];
} arc_entry_t;

/*
    reads the given file and caches all its entries
*/
void A_ReadFile(const char *path);

/*
    reads the data of the entry with the given index
*/
void A_ReadEntry(int entry, void *destination);

/*
    returns the index of the desired entry (returns -1 if not found)
*/
int A_FindEntry(const char *name);

/*
    returns the data of the desired entry from the cache
*/
void *A_GetEntry(const char *name);

/*
    reads the data of each entry and puts them all into an array of pointers pointing to that data
*/
void A_CacheEntries();

#endif // __ARC_H__
