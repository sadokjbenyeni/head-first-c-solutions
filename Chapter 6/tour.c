#include <stdio.h>

typedef struct island
{
    char *name;
    char *opens;
    char *closes;
    struct island *next;
} island;


island* create(char *name)
{
    island *i = malloc(sizeof(island));
    i->name = strdup(name);
    i->opens = "09:00";
    i->closes = "17:00";
    i->next = NULL;
    return i;
}

void display(island *start)
{
    island *i = start;
    for (; i != NULL; i = i->next)
    {
        printf("Name: %s \nopen: %s-%s\n", i->name, i->opens, i->closes);
    }
}

void release(island *start)
{
    island *i = start;
    island *next = NULL;
    for(;i !=NULL; i=next){
        next = i->next;
        free(i->name);
        free(i);
    }
}

int main()
{
    island amity = {"Amity", "09:00", "17:00", NULL};
    island craggy = {"Craggy", "09:00", "17:00", NULL};
    island isla_nublar = {"Isla Nublar", "09:00", "17:00", NULL};
    island shutter = {"Shutter", "09:00", "17:00", NULL};
    amity.next = &craggy;
    craggy.next = &isla_nublar;
    isla_nublar.next = &shutter;
    island skull = {"Skull", "09:00", "17:00", NULL};
    isla_nublar.next = &skull;
    skull.next = &shutter;
    display(&amity);
}