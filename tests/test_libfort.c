#include <stdio.h>
#include "fort.h"

int main(void)
{
    ft_table_t *table = ft_create_table();
    /* Change border style */
    ft_set_border_style(table, FT_DOUBLE2_STYLE);

    /* Set "header" type for the first row */
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "Movie title", "Director", "Year", "Rating");

    ft_write_ln(table, "The Shawshank Redemption", "Frank Darabont", "1994", "9.5");
    ft_write_ln(table, "The Godfather", "Francis Ford Coppola", "1972", "9.2");
    ft_write_ln(table, "2001: A Space Odyssey", "Stanley Kubrick", "1968", "8.5");

    /* Set center alignment for the 1st and 3rd columns */
    ft_set_cell_prop(table, FT_ANY_ROW, 1, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, FT_ANY_ROW, 3, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);

    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}