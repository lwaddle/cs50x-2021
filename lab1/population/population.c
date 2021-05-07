#include <cs50.h>
#include <stdio.h>

int get_llama_population_years_required(long starting_population, long ending_population);

int main(void)
{
    const long minimum_population_size = 9;
    long       starting_population;
    long       ending_population;
    
    // Prompt for start size
    do
    {
        starting_population = get_long("Starting population: ");
    }
    while (starting_population < minimum_population_size);
    
    // Prompt for end size
    do
    {
        ending_population = get_long("Ending population: ");
    }
    while (ending_population < starting_population);
     
    // Calculate number of years until we reach threshold
    int total_years = get_llama_population_years_required(starting_population, ending_population);

    // Print number of years
    printf("Years: %i\n", total_years);
}


int get_llama_population_years_required(long starting_population, long ending_population)
{
    /**
     * Say we have a population of n llamas. Each year, n / 3 new llamas are
     * born, and n / 4 llamas pass away.
     * For example, if we were to start with n = 1200 llamas, then in the
     * first year, 1200 / 3 = 400 new llamas would be born and
     * 1200 / 4 = 300 llamas would pass away. At the end of that year,
     * we would have 1200 + 400 - 300 = 1300 llamas.
     */
    
    long total_llamas = starting_population;
    int total_years = 0;
    
    while (total_llamas < ending_population)
    {
        long born =         total_llamas / 3;
        long passed_away =  total_llamas / 4;
        long net_gain =     born - passed_away;
        
        total_llamas += net_gain;
        total_years++;
    }
    
    return total_years;
}
