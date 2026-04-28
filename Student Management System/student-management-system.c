#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_DEPT 30
#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char name[MAX_NAME];
    int age;
    char department[MAX_DEPT];
} Student;

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    getchar(); // clear newline
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0; // remove newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Department: ");
    getchar();
    fgets(s.department, MAX_DEPT, stdin);
    s.department[strcspn(s.department, "\n")] = 0;

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    Student s;
    printf("\n--- Student Records ---\n");
    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("ID: %d | Name: %s | Age: %d | Dept: %s\n",
               s.id, s.name, s.age, s.department);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int id, found = 0;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("Record Found: ID: %d | Name: %s | Age: %d | Dept: %s\n",
                   s.id, s.name, s.age, s.department);
            found = 1;
            break;
        }
    }
    if (!found) printf("No student found with ID %d\n", id);
    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("Enter new Name: ");
            getchar();
            fgets(s.name, MAX_NAME, stdin);
            s.name[strcspn(s.name, "\n")] = 0;
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Department: ");
            getchar();
            fgets(s.department, MAX_DEPT, stdin);
            s.department[strcspn(s.department, "\n")] = 0;

            fseek(fp, sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("No student found with ID %d\n", id);
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    Student s;
    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }
    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) printf("Record deleted successfully!\n");
    else printf("No student found with ID %d\n", id);
}