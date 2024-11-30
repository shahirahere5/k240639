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

void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
