#include "../def.h"

arc_header_t header;
arc_entry_t *entries;

// cached entry data
void **entry_data;

// path to the currently loaded archive
const char *archive;

void A_ReadFile(const char *path)
{
    FILE *handle = fopen(path, "rb");

    if (handle == NULL)
    {
        I_Error("A_ReadFile(): failed to open file");
    }

    fread(&header, sizeof(arc_header_t), 1, handle);

    if (strncmp(header.id, "ARCH", 4))
    {
        I_Error("A_ReadFile(): invalid file format");
    }

    fseek(handle, header.directory, SEEK_SET);

    entries = malloc(header.entry_count * sizeof(arc_entry_t));

    for (int i = 0; i < header.entry_count; i++)
    {
        fread(&entries[i], sizeof(arc_entry_t), 1, handle);
    }

    fclose(handle);

    archive = path;

    A_CacheEntries();
}

void A_ReadEntry(int entry, void *destination)
{
    if (entry < 0 || entry > header.entry_count)
    {
        I_Error("A_ReadEntry(): invalid entry index");
    }

    FILE *handle = fopen(archive, "rb");

    if (handle == NULL)
    {
        I_Error("A_ReadEntry(): failed to open file");
    }

    arc_entry_t *entry_info = &entries[entry];

    fseek(handle, entry_info->offset, SEEK_SET);
    fread(destination, 1, entry_info->size, handle);

    fclose(handle);
}

int A_FindEntry(const char *name)
{
    for (int i = 0; i < header.entry_count; i++)
    {
        if (!strncmp(entries[i].name, name, 8))
        {
            return i;
        }
    }

    I_Warning("A_FindEntry(): entry '%s' not found", name);

    return -1;
}

void *A_GetEntry(const char *name)
{
    return entry_data[A_FindEntry(name)];
}

void *A_GetEntryByIndex(int entry)
{
    if (entry < 0 || entry >= header.entry_count)
    {
        I_Error("A_GetEntryByIndex(): invalid entry index");
    }

    return entry_data[entry];
}

void A_CacheEntries()
{
    entry_data = calloc(header.entry_count, sizeof(void *));

    for (int i = 0; i < header.entry_count; i++)
    {
        entry_data[i] = malloc(entries[i].size);
    }

    A_ReadEntry(A_FindEntry("PALETTE"), entry_data[0]);

    A_ReadEntry(A_FindEntry("TILEMAP"), entry_data[1]);
    A_ReadEntry(A_FindEntry("TEXTMAP"), entry_data[2]);

    // "T_START" and "T_END" entries serve as texture data delimiters
    int first_texture = A_FindEntry("T_START") + 1;
    int last_texture = A_FindEntry("T_END") - 1;

    for (int i = first_texture; i <= last_texture; i++)
    {
        A_ReadEntry(i, entry_data[i]);
    }
}
