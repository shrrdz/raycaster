#pragma once

#ifndef __ARC_H__
#define __ARC_H__

/*
    ┌-------------------------------------------------------------------------┐
    |  .arc file                                                              |
    |-------------------------------------------------------------------------|
    |                                                                         |
    |  file header                                                            |
    |  ┌-------------------------------------------------------------------┐  |
    |  |  header                                                           |  |
    |  |-------------------------------------------------------------------|  |
    |  |  offset: 0x00 | size: 4 bytes | desc: ASCII id ("ARCH")           |  |
    |  |-------------------------------------------------------------------|  |
    |  |  offset: 0x04 | size: 4 bytes | desc: number of entries           |  |
    |  |-------------------------------------------------------------------|  |
    |  |  offset: 0x08 | size: 4 bytes | desc: offset of the directory     |  |
    |  └-------------------------------------------------------------------┘  |
    |                                                                         |
    |  data of all entries + zero-byte delimiters                             |
    |  ┌-------------------------------------------------------------------┐  |
    |  |  uncompressed entry data                                          |  |
    |  └-------------------------------------------------------------------┘  |
    |                                                                         |
    |  directory                                                              |
    |  ┌-------------------------------------------------------------------┐  |
    |  |  entry                                                            |  |
    |  |-------------------------------------------------------------------|  |
    |  |  offset: 0x00 | size: 4 bytes | desc: position in the file        |  |
    |  |-------------------------------------------------------------------|  |
    |  |  offset: 0x04 | size: 4 bytes | desc: size of the entry in bytes  |  |
    |  |-------------------------------------------------------------------|  |
    |  |  offset: 0x08 | size: 8 bytes | desc: name of the entry           |  |
    |  └-------------------------------------------------------------------┘  |
    └-------------------------------------------------------------------------┘
*/

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
