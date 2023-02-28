#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    //iterate through the candidates list
    for (int i = 0; i < candidate_count; i++)
    {
        // check if voted candidate exists, if yes add him to the preferences for voter i, if not return error.
        if (strcmp(candidates[i].name, name))
        {
            continue;
        }
        preferences[voter][rank] = i;
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------
// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // iterate through the number of voters
    for (int i = 0; i < voter_count; i++)
    {
        //iterate through voters ballot for candidates
        for (int j = 0; j < 3; j++)
        {
            // check if the candidate has been eliminated, if not increment his vote number
            if (!(candidates[preferences[i][j]].eliminated))
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}
//---------------------------------------------------------------------------------------------------------------------
// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int winnerVote = 0, winnerIndex;
    //iterate through the candidates list
    for (int i = 0; i < candidate_count; i++)
    {
        // check if the votes are enough to win the election, meaning more than half of total
        if (candidates[i].votes > (voter_count / 2))
        {
            // check if candidate has more votes than the privous candidate with the higher value
            if (candidates[i].votes > winnerVote)
            {
                winnerVote = candidates[i].votes;
                winnerIndex = i;
            }
        }
    }
    //print winner if there's one
    if (winnerVote)
    {
        printf("%s\n", candidates[winnerIndex].name);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------------------------------------------------
// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int minVotes = 0;
    //iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //check if current candidate has less votes than the current one with less votes
        if (candidates[i].votes > minVotes)
        {
            //check if candiadte has been elimnated yet, if not then make his votes the new lowest number
            if (!(candidates[i].eliminated))
            {
                minVotes = candidates[i].votes;
            }
        }
    }
    // if there's someone with less votes then return it's votes number
    if (minVotes)
    {
        return minVotes;
    }
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!(candidates[i].eliminated))
        {
            if (candidates[i].votes != min)
            {
                return false;
            }
        }
    }
    return true;
}
//---------------------------------------------------------------------------------------------------------------------
// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}