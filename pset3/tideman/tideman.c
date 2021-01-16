#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if the name is match for valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // The name is valid
        if (strcmp(name, candidates[i]) == 0)
        {
            // update the ranks array to indicate that the voter has the candidate as their rank preference
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the global preferences array  to add the current voter’s preferences.
    //Recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j

    // Only check past the current rank
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = (i+1); j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Define the global pair_count variable
    pair_count = 0;

    // The function should add all pairs of candidates where one candidate is preferred --> to the pairs array.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = (i+1); j < candidate_count; j++)
        {
            if (i != j) // Don't compare the candidate to itself
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    // Add this to pairs array
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;

                    pair_count+=1;
                }
                else if (preferences[i][j] < preferences[j][i] && preferences[i][j] > 0)
                {
                    // Add this to pairs array
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;

                    pair_count+=1;
                }
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Length of pairs is pair_count
    // Sort from LARGEST to SMALLEST

    for (int i = 0; i < pair_count; i++)
    {
        pair this_pair = pairs[i];

        for (int a = 0; a < pair_count; a++)
        {
            if (i < (pair_count))
            {
                int this_pair_margin =  preferences[pairs[a].winner][pairs[a].loser] - preferences[pairs[a].loser][pairs[a].winner];
                int next_pair_margin =  preferences[pairs[a+1].winner][pairs[a+1].loser] - preferences[pairs[a+1].loser][pairs[a+1].winner];

                if (this_pair_margin < next_pair_margin)
                {
                    // Swipe the smaller number to the right
                    pairs[i] = pairs[i+1];
                    pairs[i+1] = this_pair;
                }
            }
         }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // // // Is the last pair going to create a cycle?
        // // if (i == pair_count-1)
        // // {
        // //     if (pairs[i].loser == pairs[0].winner)
        // //     {
        // //         return;
        // //     }
        // // }

        // // True count
        // int trues_found = 0;

        // for (int c = 0; c < candidate_count; c++)
        // {
        //     for (int r = 0; r < candidate_count; r++)
        //     {
        //       if (locked[r][c] == true)
        //       {
        //           trues_found += 1;

        //             if (trues_found > 1)
        //             {
        //                 // There were multiple in this row
        //                 return;
        //             }
        //       }
        //     }

        //     trues_found = 0;
        // }

        // for (int r = 0; r < candidate_count; r++)
        // {
        //     for (int c = 0; c < candidate_count; c++)
        //     {
        //       if (locked[r][c] == true)
        //       {
        //           trues_found += 1;

        //             if (trues_found > 1)
        //             {
        //                 // There were multiple in this row
        //                 return;
        //             }
        //       }
        //     }

        //     trues_found = 0;
        // }

        bool true_in_row = false;
        for (int c = 0; c < candidate_count; c++)
        {
            // Row to check = pairs[i].loser
            if (locked[pairs[i].winner][c] == true)
            {
                true_in_row = true;
            }
        }

        bool true_in_col = false;
        for (int r = 0; r < candidate_count; r++)
        {
            // Col to check = pairs[i].winner
            if (locked[r][pairs[i].loser] == true)
            {
                true_in_col = true;
            }
        }

        if (true_in_row && true_in_col)
        {
            return;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        // for (int b = 0; b < pair_count; b++)
        // {
        //     if ((i == pair_count-1) && (locked[pairs[i].loser][b] == true))
        //     {
        //         return;
        //     }
        // }


    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    //Closest to top left
    return;
}

