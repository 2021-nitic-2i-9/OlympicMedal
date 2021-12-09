#ifndef INCLUDED_TYPE
#define INCLUDED_TYPE

struct _country_data {
    char name[256];
    int gold;
    int silver;
    int bronze;
};

typedef struct _country_data type_country_data;

#endif