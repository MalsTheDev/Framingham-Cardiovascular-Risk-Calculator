#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

double calculateRiskMen(double age, double totalChol, double hdlChol, double sysBP, int smoker);
double calculateRiskWomen(double age, double totalChol, double hdlChol, double sysBP, int smoker);
int searchPatient(char *insuranceNumber, double *riskScores);
int countPatients();
double calculateAverage();
int addPatient();
int menu();

int main() {
    menu();

    return 1;
}

// Menu
int menu() {
    char insuranceNum[64];
    int option;
    printf("========================================\n");
    printf("           Framingham Risk Score        \n");
    printf("========================================\n");

    printf("Please select an option:\n1. Calculate your risk\n2. Search patient\n3. Close Program\n");
    
    printf("Option: ");
    scanf("%d", &option);

    // Calculate risk and add the patient to file
    if(option == 1) {
        addPatient();
    } else if(option == 2) {  //Search patient
        printf("Insurance Number (Type 'exit' to close the program): ");
        scanf("%s", insuranceNum);

        double riskScores[256];
        int numScores = searchPatient(insuranceNum, riskScores);

        while (numScores == 0)
        {
            if(strcmp(insuranceNum, "exit") == 0) {
                return 1;
            }
            printf("Patient with insurance number %s not found!\n", insuranceNum);
            printf("Insurance Number (Type 'exit' to close the program): ");
            scanf("%s", insuranceNum);
            numScores = searchPatient(insuranceNum, riskScores);
        }
        
        printf("Previous scores:\n");
        for (int i = 0; i < numScores; i++) {
            printf("Risk score: %.2lf\n", riskScores[i]);
        }

        system("pause");
    } else if(option == 3) { // Terminate program
        return 1;
    } else {
        printf("Wrong option!\n");
        main();
    }
}
// Fucntion to calculate the risk for men using Framingham Risk Score algorithm 
double calculateRiskMen(double age, double totalChol, double hdlChol, double sysBP, int smoker) {
    double LMen = 52.00961 * log(age) + 20.014077 * log(totalChol) + (-0.905964) * log(hdlChol)
                   + 1.305784 * log(sysBP) + 12.096316 * smoker
                   + (-4.605038) * log(age) * log(totalChol) - 2.84367 * log(age) * smoker
                   + (-2.93323) * log(age) * log(age) - 172.300168;

    return 1 - pow(0.9402, exp(LMen));
}

// Function to calculate the risk for women using Framingham Risk Score algorithm
double calculateRiskWomen(double age, double totalChol, double hdlChol, double sysBP, int smoker) {
    double LWomen = 31.764001 * log(age) + 22.465206 * log(totalChol) + (-1.187731) * log(hdlChol)
                     + 2.552905 * log(sysBP) + 13.07543 * smoker
                     + (-5.060998) * log(age) * log(totalChol) - 2.996945 * log(age) * smoker
                     - 146.5933061;

    return 1 - pow(0.98767, exp(LWomen));
}

// Function to search patient
int searchPatient(char *insuranceNumber, double *riskScores) {
    FILE *patients = fopen("patients.txt", "r");

    int numScores = 0;
    char line[256];

    while (fgets(line, sizeof(line), patients) != NULL) {
        char currentInsuranceNumber[64];
        double currentRiskScore;

        // Use sscanf to extract the information from the line
        if (sscanf(line, "Insurance number: %63[^| ] || Risk score: %lf", currentInsuranceNumber, &currentRiskScore) == 2) {
            if (strcmp(insuranceNumber, currentInsuranceNumber) == 0) {
                riskScores[numScores++] = currentRiskScore;
            }
        }
    }

    fclose(patients);

    return numScores;
}

// Function to count patients from the file
int countPatients() {
    FILE *patients = fopen("patients.txt", "r");

    int patientCount = 0;
    char line[256];

    while(fgets(line, sizeof(line), patients) != NULL) {
        char insuranceNumber[64];
        double riskScore;

        if(sscanf(line, "Insurance number: %63[^| ] || Risk score: %lf", insuranceNumber, &riskScore) == 2) {
            patientCount++;
        }
    }

    fclose(patients);

    return patientCount;
}

// Function to calculate the average score of the patients from the file
double calculateAverage() {
    FILE *patients = fopen("patients.txt", "r");

    double totalRisk = 0.0;
    int userCount = 0;
    char line[256];

    while (fgets(line, sizeof(line), patients) != NULL) {
        char insuranceNumber[64];
        double riskScore;

        // Use sscanf to extract the information from the line
        if (sscanf(line, "Insurance number: %63[^| ] || Risk score: %lf", insuranceNumber, &riskScore) == 2) {
            totalRisk += riskScore;
            userCount++;
        }
    }

    fclose(patients);

    return totalRisk / userCount;
}

// Function to calculate risk and add patient to file
int addPatient() {
    double age, totalChol, hdlChol, sysBP, riskMen, riskWomen;
    int smoker;
    char insuranceNumber[64], gender;

    // Get insurance number
    printf("Enter insurance number: ");
    scanf("%s", &insuranceNumber);

    if(strlen(insuranceNumber) != 11) {
        printf("Insurance number must have 11 characters, please try again!\n");

        printf("Enter insurance number: ");
        scanf("%s", &insuranceNumber);
    }

    // Get user input
    printf("Enter age: ");
    scanf("%lf", &age);

    while(age < 0) {
        printf("Age must be greater than 0, please try again!\n");
        
        printf("Enter age: ");
        scanf("%lf", &age);
    }

    while(age < 30 || age > 79) {
        printf("This tool is deticated for ages between 30 to 70, please try again!\n");

        printf("Enter age: ");
        scanf("%lf", &age);
    }

    printf("Enter total cholesterol(100-300): ");
    scanf("%lf", &totalChol);

    while(totalChol < 100 || totalChol > 300) {
        printf("Total cholesterol must be greater than 10 and less than 300, please try again!\n");
        
        printf("Enter total cholesterol(100-300): ");
        scanf("%lf", &totalChol);
    }

    printf("Enter HDL cholesterol(10-100): ");
    scanf("%lf", &hdlChol);

    while(hdlChol < 10 ||hdlChol > 100) {
        printf("HDL cholesterol must be greater than 0 and less than 100, please try again!\n");
        
        printf("Enter HDL cholesterol(10-100): ");
        scanf("%lf", &hdlChol);
    }

    printf("Enter systolic BP(80-200): ");
    scanf("%lf", &sysBP);

    while(sysBP < 80 || sysBP > 200) {
        printf("Systolic Blood Pressure must be greater than 80 and less than 200, please try again!\n");

        printf("Enter systolic BP(80-200): ");
        scanf("%lf", &sysBP);
    }

    printf("Smoker? (1 for Yes, 0 for No): ");
    scanf("%d", &smoker);

    while(smoker != 0 && smoker != 1) {
        printf("Smoker must 1 or 0, please try again!\n");

        printf("Smoker? (1 for Yes, 0 for No): ");
        scanf("%d", &smoker);
    }

    printf("Gender [Male -> M, Female -> F]: ");
    scanf(" %c", &gender);

    while(gender != 'M' && gender != 'F') {
        printf("Gender must be M or F, please try again!\n");
        printf("Gender [Male -> M, Female -> F]: ");
        scanf(" %c", &gender);
    }

    // Display risk
    if (gender == 'M') {
        double riskMen = calculateRiskMen(age, totalChol, hdlChol, sysBP, smoker) * 100;
        printf("\nYour risk score is %.2lf%% - ", riskMen);
        if (riskMen < 5.0) {
            printf("Low Risk\n");
        } else if (riskMen < 10.0) {
            printf("Moderate Risk\n");
        } else if (riskMen < 20.0) {
            printf("Strong Risk\n");
        } else {
            printf("High Risk\n");
        }

        int patientsLen = countPatients();

        if(patientsLen >= 100) {
            printf("The average risk of our patients is %.2lf%%\n", calculateAverage());
        }

        double riskScores[256];
        int numScores = searchPatient(insuranceNumber, riskScores);
        
        if(numScores > 0) {
            printf("\nPrevious scores:\n");
            for (int i = 0; i < numScores; i++) {
                printf("%d.Risk score: %.2lf%%\n", i+1, riskScores[i]);
            }
        }
        
        FILE *patients = fopen("patients.txt", "a");

        fprintf(patients, "Insurance number: %s || Risk score: %lf\n", insuranceNumber, riskMen);

        fclose(patients);

        system("pause");
    } else {
        double riskWomen = calculateRiskWomen(age, totalChol, hdlChol, sysBP, smoker) * 100;
        printf("\nYour risk score is %.2lf%% - ", riskWomen);

        if (riskWomen < 5.0) {
            printf("Low Risk\n");
        } else if (riskWomen < 10.0) {
            printf("Moderate Risk\n");
        } else if (riskWomen < 20.0) {
            printf("Strong Risk\n");
        } else {
            printf("High Risk\n");
        }

        int patientsLen = countPatients();

        if(patientsLen >= 100) {
            printf("The average risk of our patients is %.2lf%%\n", calculateAverage());
        }

        double riskScores[256];
        int numScores = searchPatient(insuranceNumber, riskScores);
        
        if(numScores > 0) {
            printf("\nPrevious scores:\n");
            for (int i = 0; i < numScores; i++) {
                printf("%d.Risk score: %.2lf%%\n", i+1, riskScores[i]);
            }
        }
        
        FILE *patients = fopen("patients.txt", "a");

        fprintf(patients, "Insurance number: %s || Risk score: %lf\n", insuranceNumber, riskMen);

        fclose(patients);

        system("pause");
    }

    return 0;
}
// Compiler version: gcc.exe (MinGW.org GCC-6.3.0-1) 6.3.0
// Comp
