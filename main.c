#include <stdio.h>
#include "type.h"

unsigned get_count_countries(void);
void get_countries_data(type_country_data *data);

int main(void) {
    unsigned count_countries = get_count_countries();
    struct _country_data countries_data[count_countries];
    get_countries_data(countries_data);

	return 0;
}