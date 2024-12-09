#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_COUNTRIES 20
#define FILENAME "voting_results.txt"

typedef struct {
    char name[50];
    char vote[10];
} Country;

typedef struct {
    int For;
    int Against;
    int Abstain;
    int totalVotes;
    bool resolutionPassed;  // To track whether the resolution passed or failed( true or false)
} VotingResult;

const char *countryList[MAX_COUNTRIES] = {
    "Afghanistan", "Albania", "Algeria", "Andorra", "Angola",
    "Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria",
    "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados",
    "Belarus", "Belgium", "Belize", "Benin", "Bhutan"
};

// category for voting
const char *categoryList[] = {
    "Climate Change", "Human Rights", "Economic Policy", "Global Health", "Technology Development"
};

//  set console text color
void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void conductVoting(Country countries[], VotingResult *result, int categoryChoice);
void filingofvotingresults(VotingResult *result, Country countries[], int categoryChoice);
void displayPastResults();
void compareTurnaround(VotingResult *newResult);
void clearVotingResultsFile();
bool isValidVote(const char *vote);
void displayMenu();
void clearInputBuffer();

int main() {
    Country countries[MAX_COUNTRIES];
    VotingResult currentResult = {0, 0, 0, 0, false};
    int choice, categoryChoice;

    for (int i = 0; i < MAX_COUNTRIES; i++) {
        strcpy(countries[i].name, countryList[i]);
    }

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            setConsoleColor(12); // Red
            printf("Invalid input. Please enter a valid number.\n");
            setConsoleColor(7); // Reset to default color
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                
                printf("\nSelect a voting category:\n");
                for (int i = 0; i < 5; i++) {
                    printf("%d. %s\n", i + 1, categoryList[i]);
                }
                printf("Enter your choice (1-5): ");
                if (scanf("%d", &categoryChoice) != 1 || categoryChoice < 1 || categoryChoice > 5) {
                    setConsoleColor(12); // Red
                    printf("Invalid category choice.\n");
                    setConsoleColor(7); // Reset to default color
                    continue;
                }
                conductVoting(countries, &currentResult, categoryChoice);
                filingofvotingresults(&currentResult, countries, categoryChoice);
                break;
            case 2:
                displayPastResults();
                break;
            case 3:
                compareTurnaround(&currentResult);
                break;
            case 4:
                clearVotingResultsFile();
                break;
            case 5:
                setConsoleColor(10); // Green
                printf("Exiting program. Goodbye!\n");
                setConsoleColor(7); // Reset to default color
                return 0;
            default:
                setConsoleColor(12); // Red
                printf("Invalid choice! Please try again.\n");
                setConsoleColor(7); // Reset to default color
        }
    }
    return 0;
}

void displayMenu() {
    setConsoleColor(9); // Blue
    printf("\n--- UN Voting System ---\n");
    setConsoleColor(7); // Reset to default color
    printf("1. Conduct Voting\n");
    printf("2. View Past Results\n");
    printf("3. Compare Turnaround\n");
    printf("4. Clear Past Results\n");
    printf("5. Exit\n");
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

bool isValidVote(const char *vote) {
    return (strcasecmp(vote, "for") == 0 || strcasecmp(vote, "against") == 0 || strcasecmp(vote, "abstain") == 0);
}

void conductVoting(Country countries[], VotingResult *result, int categoryChoice) {
    result->For = 0;
    result->Against = 0;
    result->Abstain = 0;

    printf("\n--- Conducting Voting Session ---\n");
    for (int i = 0; i < MAX_COUNTRIES; i++) {
        while (1) {
            printf("Enter vote for %s (for/against/abstain): ", countries[i].name);
            scanf(" %9s", countries[i].vote);

            if (isValidVote(countries[i].vote)) {
                break;
            } else {
                setConsoleColor(12); // Red
                printf("Invalid vote. Please enter 'for', 'against', or 'abstain'.\n");
                setConsoleColor(7); // Reset to default color
            }
        }

        if (strcasecmp(countries[i].vote, "for") == 0) {
            result->For++;
        } else if (strcasecmp(countries[i].vote, "against") == 0) {
            result->Against++;
        } else if (strcasecmp(countries[i].vote, "abstain") == 0) {
            result->Abstain++;
        }
    }

    result->totalVotes = result->For + result->Against + result->Abstain;
    result->resolutionPassed = (result->For > 12);  //checking if for more then 12 resolution is passed

    printf("\nVoting Completed:\n");
    if (result->resolutionPassed) {
        setConsoleColor(10); // Green
        printf("Resolution Passed!\n");
    } else {
        setConsoleColor(12); // Red
        printf("Resolution Failed.\n");
    }
    setConsoleColor(7); // Reset to default color
    printf("For: %d, Against: %d, Abstain: %d\n", result->For, result->Against, result->Abstain);
}

void filingofvotingresults(VotingResult *result, Country countries[], int categoryChoice) {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "--- Voting Session Results ---\n");
    fprintf(file, "Category: %s\n", categoryList[categoryChoice - 1]);
    for (int i = 0; i < MAX_COUNTRIES; i++) {
        fprintf(file, "%s: %s\n", countries[i].name, countries[i].vote);
    }
    fprintf(file, "Summary: For: %d, Against: %d, Abstain: %d, Total Votes: %d\n",
            result->For, result->Against, result->Abstain, result->totalVotes);
    if (result->resolutionPassed) {
        fprintf(file, "Resolution Passed.\n");
    } else {
        fprintf(file, "Resolution Failed.\n");
    }
    fprintf(file, "--------------------------------\n");

    fclose(file);
    setConsoleColor(9); // Blue
    printf("Results saved to '%s'.\n", FILENAME);
    setConsoleColor(7); // Reset to default color
}

void displayPastResults() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256];
    printf("\n--- Past Voting Results ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void compareTurnaround(VotingResult *newResult) {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int For, Against, Abstain, totalVotes;
    int effectivePastVotes = 0, sessionCount = 0;

    char line[256];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "Summary: For: %d, Against: %d, Abstain: %d, Total Votes: %d", 
            &For, &Against, &Abstain, &totalVotes) == 4) {
            effectivePastVotes += (totalVotes - Abstain);
            sessionCount++;
        }
    }

    fclose(file);

    if (sessionCount == 0) {
        setConsoleColor(12); // Red
        printf("No past voting sessions available for comparison.\n");
        setConsoleColor(7); // Reset to default color
        return;
    }

    int averageEffectiveVotes = effectivePastVotes / sessionCount;
    int currentEffectiveVotes = newResult->totalVotes - newResult->Abstain;

    printf("\n--- Turnaround Comparison ---\n");
    printf("Average Past Effective Votes (Excluding Abstentions): %d\n", averageEffectiveVotes);
    printf("Current Session Effective Votes (Excluding Abstentions): %d\n", currentEffectiveVotes);

    if (currentEffectiveVotes > averageEffectiveVotes) {
        setConsoleColor(10); // Green
        printf("Current session had a higher effective turnout.\n");
    } else if (currentEffectiveVotes < averageEffectiveVotes) {
        setConsoleColor(12); // Red
        printf("Current session had a lower effective turnout.\n");
    } else {
        setConsoleColor(9); // Blue
        printf("Current session had the same effective turnout as the average.\n");
    }
    setConsoleColor(7); // Reset to default color
}

void clearVotingResultsFile() {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        perror("Error clearing file");
        return;
    }
    fclose(file);
    setConsoleColor(9); // Blue
    printf("File contents cleared successfully.\n");
    setConsoleColor(7); // Reset to default color
}
