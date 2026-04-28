#include <stdio.h>

// Global balance
float balance = 0;

// Function prototypes
void showMenu();
void checkBalance();
void recharge();
void payFare();

int main() {
    int choice;

    while (1) {
        showMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                recharge();
                break;
            case 3:
                payFare();
                break;
            case 4:
                printf("Exiting system... Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

// Show menu
void showMenu() {
    printf("\n=============================\n");
    printf("   BUS CARD SYSTEM\n");
    printf("=============================\n");
    printf("1. Check Balance\n");
    printf("2. Recharge Card\n");
    printf("3. Pay Fare\n");
    printf("4. Exit\n");
}

// Check balance
void checkBalance() {
    printf("\nYour current balance is: %.2f\n", balance);
}

// Recharge card
void recharge() {
    float amount;
    printf("\nEnter amount to recharge: ");
    scanf("%f", &amount);

    if (amount > 0) {
        balance += amount;
        printf("Recharge successful! New balance: %.2f\n", balance);
    } else {
        printf("Invalid amount!\n");
    }
}

// Pay fare
void payFare() {
    float fare = 2.5; // fixed bus fare

    if (balance >= fare) {
        balance -= fare;
        printf("\nFare paid successfully: %.2f deducted\n", fare);
        printf("Remaining balance: %.2f\n", balance);
    } else {
        printf("\nInsufficient balance! Please recharge.\n");
    }
}