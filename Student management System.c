#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char diagnosis[100];
    char treatment[100];
};

// Function prototypes
void admitPatient();
void dischargePatient();
void viewAllPatients();
void searchPatientByID();

const char *filename = "patients.dat";

int main() {
    int choice;
    printf("Hospital Patient Management System\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Admit Patient\n");
        printf("2. Discharge Patient\n");
        printf("3. View All Patients\n");
        printf("4. Search Patient by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                admitPatient();
                break;
            case 2:
                dischargePatient();
                break;
            case 3:
                viewAllPatients();
                break;
            case 4:
                searchPatientByID();
                break;
            case 5:
                printf("Exiting system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to admit a new patient
void admitPatient() {
    struct Patient patient;
    FILE *file = fopen(filename, "ab");

    printf("Enter Patient ID: ");
    scanf("%d", &patient.id);
    printf("Enter Patient Name: ");
    getchar(); // Clear newline character
    fgets(patient.name, 50, stdin);
    patient.name[strcspn(patient.name, "\n")] = 0; // Remove newline
    printf("Enter Age: ");
    scanf("%d", &patient.age);
    printf("Enter Diagnosis: ");
    getchar();
    fgets(patient.diagnosis, 100, stdin);
    patient.diagnosis[strcspn(patient.diagnosis, "\n")] = 0;
    printf("Enter Treatment: ");
    fgets(patient.treatment, 100, stdin);
    patient.treatment[strcspn(patient.treatment, "\n")] = 0;

    fwrite(&patient, sizeof(struct Patient), 1, file);
    fclose(file);
    printf("Patient admitted successfully.\n");
}

// Function to discharge a patient by ID
void dischargePatient() {
    int id;
    struct Patient patient;
    FILE *file = fopen(filename, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int found = 0;

    printf("Enter Patient ID to discharge: ");
    scanf("%d", &id);

    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        if (patient.id == id) {
            found = 1;
            printf("Patient with ID %d discharged.\n", id);
        } else {
            fwrite(&patient, sizeof(struct Patient), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);
    remove(filename);
    rename("temp.dat", filename);

    if (!found) {
        printf("Patient ID not found.\n");
    }
}

// Function to view all patients
void viewAllPatients() {
    struct Patient patient;
    FILE *file = fopen(filename, "rb");

    printf("Patient Records:\n");
    printf("ID\tName\t\tAge\tDiagnosis\t\tTreatment\n");
    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        printf("%d\t%s\t\t%d\t%s\t\t%s\n", patient.id, patient.name, patient.age, patient.diagnosis, patient.treatment);
    }

    fclose(file);
}

// Function to search for a patient by ID
void searchPatientByID() {
    int id;
    struct Patient patient;
    FILE *file = fopen(filename, "rb");
    int found = 0;

    printf("Enter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        if (patient.id == id) {
            printf("Patient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDiagnosis: %s\nTreatment: %s\n",
                   patient.id, patient.name, patient.age, patient.diagnosis, patient.treatment);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Patient ID not found.\n");
    }
}
