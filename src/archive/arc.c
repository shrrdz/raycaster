#include "../def.h"

arc_header_t header;
arc_entry_t *entries;

void A_ReadFile(const char *path)
{
    FILE *handle = fopen(path, "rb");

    fread(&header, sizeof(arc_header_t), 1, handle);

    fseek(handle, header.directory, SEEK_SET);

    entries = malloc(header.entry_count * sizeof(arc_entry_t));

    for (int i = 0; i < header.entry_count; i++)
    {
        fread(&entries[i], sizeof(arc_entry_t), 1, handle);
    }

    fclose(handle);
}
