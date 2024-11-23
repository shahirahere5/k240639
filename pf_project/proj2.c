#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h> // For console colors and styling

#define CountryMax 193
#define COLUMNS 3 // Number of columns for table display

typedef struct {
    char name[50];
    char vote[10];
} Country;

const char *countriesList[CountryMax] = {
    "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antigua and Barbuda", "Argentina",
    "Armenia", "Australia", "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados",
    "Belarus", "Belgium", "Belize", "Benin", "Bhutan", "Bolivia", "Bosnia and Herzegovina",
    "Botswana", "Brazil", "Brunei", "Bulgaria", "Burkina Faso", "Burundi", "Cabo Verde", "Cambodia",
    "Cameroon", "Canada", "Central African Republic", "Chad", "Chile", "China", "Colombia", "Comoros",
    "Congo", "Costa Rica", "Croatia", "Cuba", "Cyprus", "Czech Republic", "Denmark", "Djibouti",
    "Dominica", "Dominican Republic", "Ecuador", "Egypt", "El Salvador", "Equatorial Guinea",
    "Eritrea", "Estonia", "Eswatini", "Ethiopia", "Fiji", "Finland", "France", "Gabon", "Gambia",
    "Georgia", "Germany", "Ghana", "Greece", "Grenada", "Guatemala", "Guinea", "Guinea-Bissau",
    "Guyana", "Haiti", "Honduras", "Hungary", "Iceland", "India", "Indonesia", "Iran", "Iraq",
    "Ireland", "Israel", "Italy", "Jamaica", "Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati",
    "Korea (North)", "Korea (South)", "Kuwait", "Kyrgyzstan", "Laos", "Latvia", "Lebanon", "Lesotho",
    "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg", "Madagascar", "Malawi", "Malaysia",
    "Maldives", "Mali", "Malta", "Marshall Islands", "Mauritania", "Mauritius", "Mexico", "Micronesia",
    "Moldova", "Monaco", "Mongolia", "Montenegro", "Morocco", "Mozambique", "Myanmar", "Namibia",
    "Nauru", "Nepal", "Netherlands", "New Zealand", "Nicaragua", "Niger", "Nigeria", "North Macedonia",
    "Norway", "Oman", "Pakistan", "Palau", "Panama", "Papua New Guinea", "Paraguay", "Peru",
    "Philippines", "Poland", "Portugal", "Qatar", "Romania", "Russia", "Rwanda", "Saint Kitts and Nevis",
    "Saint Lucia", "Saint Vincent and the Grenadines", "Samoa", "San Marino", "Sao Tome and Principe",
    "Saudi Arabia", "Senegal", "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovakia",
    "Slovenia", "Solomon Islands", "Somalia", "South Africa", "South Sudan", "Spain", "Sri Lanka",
    "Sudan", "Suriname", "Sweden", "Switzerland", "Syria", "Tajikistan", "Tanzania", "Thailand",
    "Timor-Leste", "Togo", "Tonga", "Trinidad and Tobago", "Tunisia", "Turkey", "Turkmenistan",
    "Tuvalu", "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom", "United States", "Uruguay",
    "Uzbekistan", "Vanuatu", "Vatican City", "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe",""
};

// Function to validate votes
bool valid(const char *vote) {
    return (strcasecmp(vote, "for") == 0 || strcasecmp(vote, "against") == 0 || strcasecmp(vote, "abstain") == 0);
}

// Function to set console text color
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to print table border
void printTableBorder() {
    setConsoleColor(11); // Cyan
    printf("+-------------------------+------------+------------+------------+\n");
    setConsoleColor(15); // Reset
}

int main() {
    Country countries[CountryMax];
    int For = 0, Against = 0, Abstain = 0;

    // File pointer for saving results
    FILE *file = fopen("VotingResults.txt", "w");
    if (file == NULL) {
        printf("Error creating results file.\n");
        return 1;
    }

    // Welcome message
    setConsoleColor(10); // Green
    printf("\nWELCOME TO THE UN VOTING SYSTEM\n");
    setConsoleColor(9); // Reset
    printf("Please cast your vote for the resolution: 'for', 'against', or 'abstain'\n");

    for (int i = 0; i < CountryMax; i++) {
        strcpy(countries[i].name, countriesList[i]);
        while (1) {
			setConsoleColor(9);
            printf("Enter %s's vote (for/against/abstain): ", countries[i].name);
			setConsoleColor(15);
            scanf(" %9s", countries[i].vote);
			

            if (valid(countries[i].vote)) {
                break;
            } else {
                setConsoleColor(12); // Red
                printf("Invalid input! Please enter a valid vote.\n");
                setConsoleColor(15); // Reset
            }
        }

        if (strcasecmp(countries[i].vote, "for") == 0) {
            For++;
        } else if (strcasecmp(countries[i].vote, "against") == 0) {
            Against++;
        } else {
            Abstain++;
        }
    }

    // Display results
    printf("\nFINAL RESULTS:\n");
    fprintf(file, "\nFINAL RESULTS:\n");

    printTableBorder();
    printf("| %-23s | %-10s | %-10s | %-10s |\n", "Country", "Vote", "For", "Against");
    printTableBorder();

    for (int i = 0; i < CountryMax; i++) {
        printf("| %-23s | %-10s |\n", countries[i].name, countries[i].vote);
    }

    fclose(file);
    return 0;
}

