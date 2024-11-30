#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define CountryMax 20

typedef struct {
    char name[50];
    char vote[10];
} Country;

const char *countriesList[CountryMax] = {
    "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antigua and Barbuda", "Argentina", 
    "Armenia", "Australia", "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados", 
    "Belarus", "Belgium", "Belize", "Benin", "Bhutan"
};

bool valid(const char *vote) {
    return (strcasecmp(vote, "for") == 0 || strcasecmp(vote, "against") == 0 || strcasecmp(vote, "abstain") == 0);
}

void saveToFile(const Country countries[], int For, int Against, int Abstain) {
    FILE *file = fopen("voting_results.txt", "w");
    if (!file) {
        setConsoleColor(4); // Red for errors
        printf("Error: Unable to open file for saving results.\n");
        setConsoleColor(7);
        return;
    }

    fprintf(file, "Voting Results:\n");
    fprintf(file, "-------------------------------------------------------------\n");
    fprintf(file, "| %-25s | %-10s |\n", "Country", "Vote");
    fprintf(file, "-------------------------------------------------------------\n");
    for (int i = 0; i < CountryMax; i++) {
        fprintf(file, "| %-25s | %-10s |\n", countries[i].name, countries[i].vote);
    }
    fprintf(file, "-------------------------------------------------------------\n");
    fprintf(file, "\nTotal Votes:\n");
    fprintf(file, "For: %d\n", For);
    fprintf(file, "Against: %d\n", Against);
    fprintf(file, "Abstain: %d\n", Abstain);
    fprintf(file, "\nResolution Status: ");
    fprintf(file, (For > 12) ? "Passed\n" : "Failed\n");

    fclose(file);
    setConsoleColor(2); // Green for success
    printf("Results saved to 'voting_results.txt'.\n");
    setConsoleColor(7);
}

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
int main() {
    Country countries[CountryMax];
    int For = 0, Against = 0, Abstain = 0;

    setConsoleColor(3); // Cyan for heading
    printf("UN Voting System\n");
    printf("Enter votes for the Resolution (for, against, abstain)\n");
    setConsoleColor(7); // Reset to default




setConsoleColor(3); // Cyan for results
    printf("\nVoting Results:\n");
    printf("-------------------------------------------------------------\n");
    printf("| %-25s | %-10s |\n", "Country", "Vote");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < CountryMax; i++) {
        printf("| %-25s | %-10s |\n", countries[i].name, countries[i].vote);
    }
    printf("-------------------------------------------------------------\n");

    setConsoleColor(7); // Reset color
    printf("\nTotal Votes:\n");
    setConsoleColor(2); // Green for positive results
    printf("For: %d\n", For);
    setConsoleColor(4); // Red for negative results
    printf("Against: %d\n", Against);
    setConsoleColor(6); // Yellow for neutral results
    printf("Abstain: %d\n", Abstain);
    setConsoleColor(7);

    printf("\nResolution Status: ");
    if (For > 12) {
        setConsoleColor(2); // Green for passed
        printf("Passed\n");
    } else {
        setConsoleColor(4); // Red for failed
        printf("Failed\n");
    }
    setConsoleColor(7);

    saveToFile(countries, For, Against, Abstain);

    return 0;
}
