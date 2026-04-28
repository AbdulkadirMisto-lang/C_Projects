#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_MOVIE 50
#define FILE_NAME "tickets.dat"

typedef struct {
    int ticketId;
    char customerName[MAX_NAME];
    char movieName[MAX_MOVIE];
    int seats;
    int popcorn;
    int juice;
    float totalPrice;
    char paymentMethod[20];
    int paymentConfirmed; // 0 = not confirmed, 1 = confirmed
} Ticket;

const float PRICE_PER_SEAT = 50.0;
const float PRICE_POPCORN  = 20.0;
const float PRICE_JUICE    = 15.0;

void bookTicket();
void displayTickets();
void deleteTicket();

int main() {
    int choice;
    while (1) {
        printf("\n===== Cinema Ticket System =====\n");
        printf("1. Book Ticket\n");
        printf("2. Display All Tickets\n");
        printf("3. Delete Ticket\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: displayTickets(); break;
            case 3: deleteTicket(); break;
            case 4: exit(0); break;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void bookTicket() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) { printf("Error opening file!\n"); return; }

    Ticket t;
    printf("Enter Ticket ID: ");
    scanf("%d", &t.ticketId);
    printf("Enter Customer Name: ");
    getchar();
    fgets(t.customerName, MAX_NAME, stdin);
    t.customerName[strcspn(t.customerName, "\n")] = 0;
    printf("Enter Movie Name: ");
    fgets(t.movieName, MAX_MOVIE, stdin);
    t.movieName[strcspn(t.movieName, "\n")] = 0;
    printf("Enter Number of Seats: ");
    scanf("%d", &t.seats);

    printf("Popcorn (0=no, 1=yes): ");
    scanf("%d", &t.popcorn);
    printf("Juice (0=no, 1=yes): ");
    scanf("%d", &t.juice);

    // Calculate total price
    t.totalPrice = (t.seats * PRICE_PER_SEAT) +
                   (t.popcorn ? PRICE_POPCORN : 0) +
                   (t.juice ? PRICE_JUICE : 0);

    // Payment method
    int payChoice;
    printf("\nChoose Payment Method:\n");
    printf("1. Cash\n");
    printf("2. Credit Card\n");
    printf("3. Mobile Payment\n");
    printf("Enter choice: ");
    scanf("%d", &payChoice);

    switch (payChoice) {
        case 1: strcpy(t.paymentMethod, "Cash"); break;
        case 2: strcpy(t.paymentMethod, "Credit Card"); break;
        case 3: strcpy(t.paymentMethod, "Mobile Payment"); break;
        default: strcpy(t.paymentMethod, "Unknown");
    }

    // Confirm payment
    char confirm;
    printf("Total Price: %.2f$\n", t.totalPrice);
    printf("Confirm payment (y/n): ");
    getchar();
    scanf("%c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        t.paymentConfirmed = 1;
        printf("Payment successful! Booking completed.\n");
        fwrite(&t, sizeof(Ticket), 1, fp);
    } else {
        t.paymentConfirmed = 0;
        printf("Payment not confirmed. Booking cancelled.\n");
    }

    fclose(fp);
}

void displayTickets() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No tickets found!\n"); return; }

    Ticket t;
    printf("\n--- Ticket Records ---\n");
    while (fread(&t, sizeof(Ticket), 1, fp)) {
        printf("ID: %d | Name: %s | Movie: %s | Seats: %d | Popcorn: %s | Juice: %s | Total: %.2f$ | Payment: %s | Status: %s\n",
               t.ticketId, t.customerName, t.movieName, t.seats,
               t.popcorn ? "Yes" : "No",
               t.juice ? "Yes" : "No",
               t.totalPrice,
               t.paymentMethod,
               t.paymentConfirmed ? "Confirmed" : "Not Confirmed");
    }
    fclose(fp);
}

void deleteTicket() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) { printf("No tickets found!\n"); return; }

    FILE *temp = fopen("temp.dat", "wb");
    int id, found = 0;
    printf("Enter Ticket ID to delete: ");
    scanf("%d", &id);

    Ticket t;
    while (fread(&t, sizeof(Ticket), 1, fp)) {
        if (t.ticketId == id) { found = 1; continue; }
        fwrite(&t, sizeof(Ticket), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) printf("Ticket deleted successfully!\n");
    else printf("No ticket found with ID %d\n", id);
}