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

extern arc_entry_t *entries;

/*
    reads the given file and its entries
*/
void A_ReadFile(const char *path);

#endif // __ARC_H__
