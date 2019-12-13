#include "../def.h"

arc_header_t header;
arc_entry_t *entries;

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
