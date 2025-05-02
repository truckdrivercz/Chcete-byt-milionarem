#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTIONS 15

typedef struct {
    char text[256];
    char options[4][128];
    char correct;
    int prize;
} Question;

void showHelp() {
    printf("\n--- Napoveda ---\n");
    printf("1. Vyberte '1' pro zacatek hry.\n");
    printf("2. Ve hre vybirajte odpovedi pomoci A, B, C, D.\n");
    printf("3. Muzete kdykoliv ukoncit pomoci Q.\n");
    printf("4. Po kazde otazce se muzete rozhodnout, jestli chcete pokracovat.\n");
    printf("5. Vsechny kroky se loguji do log.txt.\n");
    printf("---------------\n\n");
}

void logEvent(const char *event) {
    FILE *log = fopen("log.txt", "a");
    if (log) {
        fprintf(log, "%s\n", event);
        fclose(log);
    }
}

int evaluateAnswer(char userInput, char correct) {
    return userInput == correct;
}

void saveProgress(int money) {
    FILE *save = fopen("save.txt", "w");
    if (save) {
        fprintf(save, "Vyhra: %d Kc\n", money);
        fclose(save);
    }
}

void playGame(Question questions[], int count) {
    int money = 0;
    char input;

    for (int i = 0; i < count; ++i) {
        printf("\nOtazka %d (%d Kc):\n%s\n", i + 1, questions[i].prize, questions[i].text);
        printf("A) %s\nB) %s\nC) %s\nD) %s\nQ) Ukoncit hru\n", 
            questions[i].options[0], questions[i].options[1], 
            questions[i].options[2], questions[i].options[3]);

        scanf(" %c", &input);
        logEvent("Otazka zobrazena");
        char logLine[128];
        sprintf(logLine, "Uzivatel zadal: %c", input);
        logEvent(logLine);

        if (input == 'Q') {
            printf("Ukoncujete hru. Vyhral jste %d Kc.\n", money);
            saveProgress(money);
            return;
        }

        if (evaluateAnswer(input, questions[i].correct)) {
            money = questions[i].prize;
            printf("Spravne! Vyhravate %d Kc\n", money);
        } else {
            printf("Spatne. Koncite s %d Kc.\n", money);
            saveProgress(money);
            return;
        }

        printf("Chcete pokracovat? (Y/N): ");
        scanf(" %c", &input);
        if (input != 'Y') {
            printf("Ukoncujete hru. Vyhral jste %d Kc.\n", money);
            saveProgress(money);
            return;
        }
    }

    printf("Gratuluji! Vyhral jste %d Kc!\n", money);
    saveProgress(money);
}

void mainMenu(Question questions[], int count) {
    int choice;
    while (1) {
        printf("\n--- Hlavni menu ---\n");
        printf("1. Spustit hru\n");
        printf("2. Napoveda\n");
        printf("3. Konec\n");
        printf("Zadejte volbu: ");
        scanf("%d", &choice);
        logEvent("Hlavni menu zobrazeno");

        switch (choice) {
            case 1:
                playGame(questions, count);
                break;
            case 2:
                showHelp();
                break;
            case 3:
                printf("Na shledanou!\n");
                return;
            default:
                printf("Neplatna volba.\n");
        }
    }
}

int main() {
    Question questions[MAX_QUESTIONS] = {
        {"Ktery svetadil je nejmensi rozlohou?", {"Evropa", "Australie", "Jizni Amerika", "Antarktida"}, 'B', 1000},
        {"Kolik minut ma jeden den?", {"1440", "1600", "1200", "2000"}, 'A', 2000},
        {"Ktery rok probehla bitva na Bile hore?", {"1526", "1648", "1620", "1781"}, 'C', 3000},
        {"Ktery cesky prezident byl zvolen jako prvni po roce 1989?", {"Vaclav Klaus", "Milos Zeman", "Ludvik Svoboda", "Vaclav Havel"}, 'D', 5000},
        {"Ktery ocean je nejvetsi na svete?", {"Indicky", "Atlantsky", "Severni ledovy", "Tichy"}, 'D', 10000},
        {"Jake je hlavni mesto Kanady?", {"Toronto", "Montreal", "Ottawa", "Vancouver"}, 'C', 20000},
        {"Kolik je v lidskem tele kosti?", {"206", "208", "204", "210"}, 'A', 40000},
        {"Kdo napsal hru Romeo a Julie?", {"Charles Dickens", "William Shakespeare", "Victor Hugo", "Moliere"}, 'B', 80000},
        {"Ktery prvek je v periodicke tabulce oznacen znackou Fe?", {"Zinek", "Zelezo", "Fluor", "Fosfor"}, 'B', 160000},
        {"Kolik prstenu bylo vytvoreno v pribeh Pan prstenu?", {"5", "7", "9", "20"}, 'D', 320000},
        {"Ktera zeme ma nejvice sousednich statu?", {"Cina", "Rusko", "Brazilie", "Indie"}, 'B', 640000},
        {"Ktery jazyk ma nejvice rodilych mluvci?", {"Anglictina", "Spanelstina", "Hindstina", "Cinstina"}, 'D', 1250000},
        {"Ktery cesky kral byl nazyvan Otec vlasti?", {"Premysl Otakar II.", "Vaclav IV.", "Karel IV.", "Jiri z Podebrad"}, 'C', 2500000},
        {"Ktery rok pristala prvni lidska posadka na Mesici?", {"1967", "1969", "1970", "1972"}, 'B', 5000000},
        {"Jak se jmenuje nejvyssi hora Evropy?", {"Mont Blanc", "Mount Elbrus", "Dufourspitze", "Matterhorn"}, 'B', 10000000},
    };

    mainMenu(questions, 15);
    return 0;
}