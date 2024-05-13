

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, results = 0;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > 0)
        {
            results = 1;
            displayPatientData(&patient[i], fmt);
        }
    }
    putchar('\n');

    if (!results)
    {
        printf("*** No records found ***\n\n");
    }
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Search Options\n"
               "==========================\n"
               "1) By patient number\n"
               "2) By phone number\n"
               "..........................\n"
               "0) Previous menu\n"
               "..........................\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (selection);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int availRecordIndex;
    availRecordIndex = findPatientIndexByPatientNum(0, patient, max);
    
    if (availRecordIndex == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[availRecordIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[availRecordIndex]);
        printf("*** New patient record added ***\n\n");
    }
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNum, patientIndex;

    printf("Enter the patient number: ");
    patientNum = inputPatientNumber(patient, max, 1);
    putchar('\n');
    if (patientNum > 0)
    {   
        patientIndex = findPatientIndexByPatientNum(patientNum, patient, max);
        menuPatientEdit(&patient[patientIndex]);
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNum, patientIndex;
    struct Patient emptyPatient = { 0 };

    printf("Enter the patient number: ");
    patientNum = inputPatientNumber(patient, max, 1);
    putchar('\n');

    if (patientNum > 0)
    {
        patientIndex = findPatientIndexByPatientNum(patientNum, patient, max);
        displayPatientData(&patient[patientIndex], FMT_FORM);
        putchar('\n');

        printf("Are you sure you want to remove this patient record? (y/n): ");
        if (inputCharOption("yn") == 'y')
        {
            patient[patientIndex] = emptyPatient;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i, patientIndex;

    displayScheduleTableHeader(&data->appointments->date, 1);

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber > 0)
        {
            patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber, 
                           data->patients, data->maxPatient);
            displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 1);
        }
    }
    putchar('\n');
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data)
{
    struct Date tempDate = { 0 };
    int dateIndex = 0;

    inputDate(&tempDate);
    putchar('\n');

    dateIndex = findApptIndexByInputDateTime(data->appointments, data->maxAppointments, 
                                             &tempDate, NULL);                                   
    if (dateIndex < 0)
    {
        printf("ERROR: No appointment scheduled on entered date!\n\n");
    }
    else
    {
        displayScheduleTableHeader(&tempDate, 0);
        searchAppointmentsByDate(data, &tempDate);
        putchar('\n');
    }
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment appoints[], int maxAppts, const struct Patient patients[], 
                    int maxPatients)
{
    struct Date tempDate = { 0 };
    struct Time tempTime = { 0 };
    int patientNum, availAppointIndex = -1;
    int appointIndex, i, available = 0 ;

    // check if appointment record is full
    for (i = 0; i < maxAppts && !available; i++)
    {
        if (appoints[i].patientNumber == 0)
        {
            availAppointIndex = i;
            available = 1;
        }
    }
    
    if (!available)
    {
        printf("ERROR: No appointment available!\n\n");
    }
    else
    {
        printf("Patient Number: ");
        patientNum = inputPatientNumber(patients, maxPatients, 0);
        
        if (patientNum > 0)
        {
            // prompt for date and time input and check for appointment availability
            do {
                inputDate(&tempDate);
                inputTime(&tempTime);
                putchar('\n');

                appointIndex = findApptIndexByInputDateTime(appoints, maxAppts, &tempDate, &tempTime);
                if (appointIndex >= 0)
                {
                    printf("ERROR: Appointment timeslot is not available!\n\n");
                }
            } while (appointIndex >= 0);

            appoints[availAppointIndex].date = tempDate;
            appoints[availAppointIndex].time = tempTime;
            appoints[availAppointIndex].patientNumber = patientNum;

            printf("*** Appointment scheduled! ***\n");
            sortAppointmentsByDate(appoints, maxAppts);
        }
        putchar('\n');
    }
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appoints[], int maxAppts, const struct Patient patients[], 
                       int maxPatients)
{
    struct Appointment emptyAppt = { 0 };
    struct Date date = { 0 };
    int patientNum, appointIndex, patientIndex;
    int i, appointFound = 0;
    char selection;

    printf("Patient Number: ");
    patientNum = inputPatientNumber(patients, maxPatients, 0);

    if (patientNum > 0)
    {
        inputDate(&date);
        putchar('\n');

        for (i = 0; i < maxAppts && !appointFound; i++)
        {
            if (compareDate(&appoints[i].date, &date) == 0 
                && appoints[i].patientNumber == patientNum)
            {
                appointIndex = i;
                appointFound = 1;
            }   
        }
        if (appointFound)
        {
            patientIndex = findPatientIndexByPatientNum(patientNum, patients, maxPatients);
            displayPatientData(&patients[patientIndex], FMT_FORM);
            
            printf("Are you sure you want to remove this appointment (y,n): ");
            selection = inputCharOption("yn");
            putchar('\n');

            if (selection == 'y')
            {
                appoints[appointIndex] = emptyAppt;
                printf("Appointment record has been removed!\n");
                sortAppointmentsByDate(appoints, maxAppts);
            }

        }
        else
        {
            printf("ERROR: Appointment record not found!\n");

        }
    }
    putchar('\n');
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNum, patientIndex;
    printf("Search by patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    patientIndex = findPatientIndexByPatientNum(patientNum, patient, max);
    if (patientIndex >= 0)
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
        putchar('\n');
    }
    else
    {
        printf("*** No records found ***\n\n");
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char inputPhoneNum[PHONE_LEN + 1] = { '\0' };
    int i, match = 0;

    printf("Search by phone number: ");
    inputPhoneNumber(inputPhoneNum);
    putchar('\n');

    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp (inputPhoneNum, patient[i].phone.number) == 0)
        {   
            match = 1;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }
    putchar('\n');

    if (!match)
    {
        printf("*** No records found ***\n\n");
    }
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, nextPatientNum, maxPatientNum = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > maxPatientNum)
        {
            maxPatientNum = patient[i].patientNumber;
        }
    }
    nextPatientNum = maxPatientNum + 1;

    return (nextPatientNum);
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i, found = 0, patientIndex = 0;
    for (i = 0; i < max && !found; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            found = 1;
            patientIndex = i;
        }
    }

    if (!found)
    {
        patientIndex = -1;
    }

    return patientIndex;
}


// Sort appointments by date (ascending)
void sortAppointmentsByDate(struct Appointment* appoints, int max)
{
    struct Appointment tempAppt = { 0 };
    int i, j, doSwap = 0;
    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (compareDate(&appoints[j].date, &appoints[j + 1].date) > 0)
            {
                doSwap = 1;
            }
            else if (compareDate(&appoints[j].date, &appoints[j + 1].date) == 0  && 
                     compareTime(&appoints[j].time, &appoints[j + 1].time) > 0)
            {
                doSwap = 1;
            }
            else
            {
                doSwap = 0;
            }

            if (doSwap)
            {
                tempAppt = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = tempAppt;
            }
        }
    }
}

// Return the number of days in the given month
int numberOfDaysInMonth(int month, int isLeapYear)
{
    int numDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((isLeapYear == 1) & (month == 2))
    {
        numDays[1] = 29;
    }
    else
    {
        numDays[1] = 28;
    }

    return numDays[month - 1];
}

// Return the index of appointment with matching date and/or time (returns -1 if not found)
int findApptIndexByInputDateTime(const struct Appointment* appoints, int maxAppts, 
                                 const struct Date* date, const struct Time* time)
{
    int i, found = 0, idx = 0;
    if (time == NULL)
    {
        for (i = 0; i <  maxAppts && !found; i++)
        {
            if (compareDate(&appoints[i].date, date) == 0)
            {
                found = 1;
                idx = i;
            }
        }
        
        if (!found)
        {
            idx = -1;
        }

    }
    else
    {
        for (i = 0; i < maxAppts && !found; i++)
        {
            if (compareDate(&appoints[i].date, date) == 0 && 
                compareTime(&appoints[i].time, time) == 0)
            {
                found = 1;
                idx = i;
            }
        }
        
        if (!found)
        {
            idx = -1;
        }
    }

    return idx;
}

// Search and display appointments based on user input date
void searchAppointmentsByDate(const struct ClinicData* data, const struct Date* date)
{
    int i, patientIndex;
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (compareDate(&data->appointments[i].date, date) == 0)
        {
            patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber, 
                           data->patients, data->maxPatient);
            displayScheduleData(&data->patients[patientIndex], &data->appointments[i], 0);
        }
    }
}


// Compare two date values (returns: 1 if dt1 is > dt2, -1 if dt1 < dt2, 0 if the same)
int compareDate(const struct Date* dt1, const struct Date* dt2)
{
    int result = 0;
    int date1 = dt1->year * 10000 + dt1->month * 100 + dt1->day;
    int date2 = dt2->year * 10000 + dt2->month * 100 + dt2->day;

    if (date1 < date2)
    {
        result = -1;
    }
    else if (date1 > date2)
    {
        result = 1;
    }

    return result;
}
                    
// Compare two time values (returns: 1 if t1 is > t2, -1 if t1 < t2, 0 if the same)
int compareTime(const struct Time* t1, const struct Time* t2)
{
    int result = 0;
    int time1 = t1->hour * 60 + t1->min;
    int time2 = t2->hour * 60 + t2->min;

    if (time1 < time2)
    {
        result = -1;
    }
    else if (time1 > time2)
    {
        result = 1;
    }

    return result;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int selection;// valid, i;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    selection = inputIntRange(1, 4);
    putchar('\n');
    switch(selection)
    {
        case 1:
            strcpy(phone->description, "CELL");
            break;
        case 2:
            strcpy(phone->description, "HOME");
            break;
        case 3:
            strcpy(phone->description, "WORK");
            break;
        case 4:
            strcpy(phone->description, "TBD");
            phone->number[0] = '\0';
            break;
    }

    if (selection < 4)
    {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputPhoneNumber(phone->number);
        putchar('\n');
    }
}

// Get user input for appointment date 
void inputDate(struct Date* date)
{
    int inputYear, inputMonth, inputDay;
    int maxDaysInMonth;
    int isLeapYear = 0, valid;

    printf("Year        : ");
    do {
        valid = 1;
        inputYear = inputIntPositive();
        if (inputYear < CURRENT_YEAR)
        {
            valid = 0;
            printf("ERROR: Appointments must be in the future!\n");
        }
    } while (!valid);

    if (inputYear % 100 == 0)
    {
        if (inputYear % 400 == 0)
        {
            isLeapYear = 1;
        }
    }
    else if (inputYear % 4 == 0)
    {
        isLeapYear = 1;
    }

    printf("Month (%d-%d): ", 1, 12);
    inputMonth = inputIntRange(1, 12);
    maxDaysInMonth = numberOfDaysInMonth(inputMonth, isLeapYear);

    printf("Day (1-%d)  : ", maxDaysInMonth);
    inputDay = inputIntRange(1, maxDaysInMonth);

    date->year = inputYear;
    date->month = inputMonth;
    date->day = inputDay;
}

// Get user input for appointment time
void inputTime(struct Time* time)
{
    int inputHour, inputMin;
    int valid;

    do {
        valid = 1;
        printf("Hour (0-23)  : ");
        inputHour = inputIntRange(0, 23);
        if (inputHour < OPEN_TIME || inputHour > CLOSE_TIME)
        {
            valid = 0;
        }

        printf("Minute (0-59): ");
        inputMin = inputIntRange(0, 59);
        if (inputMin % INTERVAL != 0 || (inputMin == INTERVAL && inputHour == CLOSE_TIME))
        {
            valid = 0;
        }

        if (!valid)
        {
            printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n\n", 
                    OPEN_TIME, CLOSE_TIME, INTERVAL);
        }
    } while (!valid);

    time->hour = inputHour;
    time->min = inputMin;
}

// Get user input for a valid phone number
void inputPhoneNumber(char* cStr)
{
    char inputCStr[MAX_STR_LEN + 1] = { '\0' };
    char fmt [20 + 1] = { '\0' };
    int inputCStrLen, valid, i;

    sprintf(fmt, "%%%d[^\n]", MAX_STR_LEN);

    do {
        valid = 1;
        scanf(fmt, inputCStr);
        clearInputBuffer();

        inputCStrLen = strlen(inputCStr);

        if (inputCStrLen != PHONE_LEN)
        {
            valid = 0;
        }
        else
        {
            for (i = 0; i < PHONE_LEN; i++)
            {
                if (isdigit(inputCStr[i]) == 0)
                {
                    valid = 0;
                }
            }
        }
        if (!valid)
        {
            printf("Invalid 10-digit number! Number: ");
        }
    } while (!valid);

    strcpy(cStr, inputCStr);
}

// Validate and return the user-input patient number or -1 if invalid
int inputPatientNumber(const struct Patient* patients, int maxPatients, int addNewLine)
{
    int patientNum;
    
    patientNum = inputIntPositive();
    if (findPatientIndexByPatientNum(patientNum, patients, maxPatients) < 0)
    {
        // valid = 0;
        if (addNewLine)
        {
            putchar('\n');
        }
        patientNum = -1;
        printf("ERROR: Patient record not found!\n");
    }

    return patientNum;
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0, recordsRead = 0;
    char fmt[20 + 1] = {'\0'};
    FILE *fp = NULL;

    sprintf(fmt, "%%d|%%%d[^|]|%%[^|]|", NAME_LEN);

    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (i < max && 
                fscanf(fp, fmt, 
                       &patients[i].patientNumber, 
                       patients[i].name, 
                       patients[i].phone.description) == 3)
        {
            if (strcmp(patients[i].phone.description, "TBD") != 0)
            {
                fscanf(fp, "%10[^\n]\n", patients[i].phone.number);
            }
            recordsRead++;
            i++;
        }
        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: unable to open patient data file for reading!\n");
    }

    return recordsRead;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0, recordsRead = 0;
    FILE* fp = NULL;

    fp = fopen(datafile, "r");
    if (fp != NULL)
    {
        while (i < max && (fscanf(fp, "%d,%d,%d,%d,%d,%d\n",
                                 &appoints[i].patientNumber,
                                 &appoints[i].date.year,
                                 &appoints[i].date.month,
                                 &appoints[i].date.day,
                                 &appoints[i].time.hour,
                                 &appoints[i].time.min)) == 6)
        {
            i++;
            recordsRead++;
        }
        fclose(fp);
        fp = NULL;
        sortAppointmentsByDate(appoints, max);
    }
    else
    {
        printf("ERROR: unable to open appointment data file for reading!\n");
    }

    return recordsRead;
}
