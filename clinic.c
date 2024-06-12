/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3

/////////////////////////////////////////////////////////////////////////*/

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

    do
    {
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

    do
    {
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
    do
    {
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
            putchar('\n');
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;
    do 
    {
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
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
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
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int recordFound = 0;
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber)
        {
            recordFound = 1;
            displayPatientData(&patient[i], fmt);
        }
    }
    if (!recordFound)
    {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int choice;
    int continueSearch = 1;
    while (continueSearch)
    {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        choice = inputIntRange(0, 2);
        switch (choice)
        {
        case 0:
            putchar('\n');
            continueSearch = 0;
            break;
        case 1:
            searchPatientByPatientNumber(patient, max);
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            break;
        }
    }
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int room = -1;
    int i;

    for (i = 0; i < max; i++)
    {
        if (room == -1 && patient[i].patientNumber == 0)
        {
            room = i;
        }
    }

    if (room != -1)
    {
        patient[room].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[room]);
        printf("\n*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int index;
    int patientNum;
    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index < 0)
    {
        printf("ERROR: Patient record not found!");
    }
    else
    {
        putchar('\n');
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int index = 0, patientNum = 0;
    char quitOption = {0};
    struct Patient remove = { 0 };

    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    if (index < 0)
    {
        putchar('\n');
        printf("ERROR: Patient record not found!\n\n");  
    }
    else
    {
        putchar('\n');
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        
        printf("Are you sure you want to remove this patient record? (y/n): ");
        quitOption = inputCharOption("yn");
        if (quitOption == 'y')
        {
            patient[index] = remove;
            printf("Patient record has been removed!\n\n");
        }
        else if (quitOption == 'n')
        {
            printf("Operation aborted.\n\n");
        }
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:

void displayAppointments(struct ClinicData* data, struct Date* filterDate, int filterByDate)
{
    int i, j;
    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            if (data->appointments[i].patients == data->patients[j].patientNumber)
            {
                if (!filterByDate || (data->appointments[i].date.year == filterDate->year &&
                    data->appointments[i].date.month == filterDate->month &&
                    data->appointments[i].date.day == filterDate->day))
                {
                    displayScheduleData(&data->patients[j], &data->appointments[i], filterByDate ? 0 : FMT_FORM);
                }
            }
        }
    }
}

void bubbleSort(struct Appointment appoints[], int max)
{
    int i, j;
    int tempTime;
    struct Appointment temp = { 0 };
    int timeInMinutes[10000] = { 0 };

    for (i = 0; i < max; i++)
    {
        timeInMinutes[i] = (appoints[i].date.year * 12 * 30 * 24 * 60) +
            (appoints[i].date.month * 30 * 24 * 60) +
            (appoints[i].date.day * 24 * 60) +
            (appoints[i].time.hour * 60) +
            appoints[i].time.min;
    }

    for (i = 0; i < max - 1; i++)
    {
        for (j = 0; j < max - i - 1; j++)
        {
            if (timeInMinutes[j] > timeInMinutes[j + 1])
            {

                temp = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = temp;
                tempTime = timeInMinutes[j];
                timeInMinutes[j] = timeInMinutes[j + 1];
                timeInMinutes[j + 1] = tempTime;
            }
        }
    }
}

void viewAllAppointments(struct ClinicData* data)
{

    bubbleSort(data->appointments, data->maxPatient);
    displayScheduleTableHeader(NULL, FMT_TABLE);
    displayAppointments(data, NULL, 0);
    putchar('\n');
}


// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int maxDay = 0;
    int isLeapYear;

    struct Date date = { 0 };
    int monthDay[] = { 31 , 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    printf("Year        : ");
    date.year = inputIntPositive();

    printf("Month (%d-%d): ",JAN, DEC);
    date.month = inputIntRange(1, 12);

    maxDay = monthDay[date.month - 1];

    isLeapYear = date.year % 4 == 0 && date.year % 100 != 0;

    if (monthDay[1] && isLeapYear)
    {
        maxDay = monthDay[1] + 1;
    }

    printf("Day (%d-%d)  : ", MIN_DAY, maxDay);
    date.day = inputIntRange(1, maxDay);
    putchar('\n');
    bubbleSort(data->appointments, data->maxPatient);
    displayScheduleTableHeader(&date, 0);
    displayAppointments(data, &date, 1);
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appoint, int maxApp, struct Patient* pat, int maxPat)
{
    int patientNumber, year, month, day, hour, min, isLeapYear, totalMinutes;
    int appointmentClash, invalidTimeSlot, timeSlotFound = 0, appointmentAdded = 0;
    int i;
    int maxDay;
    int monthDay[] = {31 , 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    while (!timeSlotFound) 
    {
        appointmentClash = 0;
        invalidTimeSlot = 0;

        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (%d-%d): ", JAN, DEC);
        month = inputIntRange(JAN, DEC);

        maxDay = monthDay[month - 1];
  
        isLeapYear = year % 4 == 0 && year % 100 != 0;

        if (monthDay[1] && isLeapYear)
        {
            maxDay = monthDay[1] + 1;
        }

        printf("Day (%d-%d)  : ", MIN_DAY, maxDay);
        day = inputIntRange(MIN_DAY, maxDay);

        do
        {              
            printf("Hour (%d-%2d)  : ", FIRST_HOUR, LAST_HOUR);
            hour = inputIntRange(FIRST_HOUR, LAST_HOUR);
            printf("Minute (%d-%d): ", START_MIN, END_MIN);
            min = inputIntRange(START_MIN, END_MIN);

            totalMinutes = hour * 60 + min;

            if (hour < START_HOUR || (hour > END_HOUR || (hour == END_HOUR && min > 0)) ||
                totalMinutes % INTERVAL != 0)
            {
                printf("ERROR: Time must be between %02d:00 and %02d:00 in %d minute intervals.\n\n", 
                        START_HOUR, END_HOUR, INTERVAL);
                invalidTimeSlot = 1;
            }
            else
            {
                invalidTimeSlot = 0;
            }
        } while (invalidTimeSlot);

        if (!invalidTimeSlot)
        {
            for (i = 0; i < maxApp; i++)
            {
                if (appoint[i].patients != 0)
                {
                    if (appoint[i].patients != 0 &&
                        appoint[i].date.year == year &&
                        appoint[i].date.month == month &&
                        appoint[i].date.day == day &&
                        appoint[i].time.hour == hour &&
                        appoint[i].time.min == min)
                    {
                        printf("\nERROR: Appointment timeslot is not available!\n\n");
                        appointmentClash = 1;
                    }
                }
            }
        }

        if (!appointmentClash && !invalidTimeSlot)
        {
            timeSlotFound = 1; 
        }
        else
        {        
            timeSlotFound = 0;
            appointmentClash = 0;
            invalidTimeSlot = 0;
        }
    }

    if (timeSlotFound) 
    {
        for (i = 0; i < maxApp && !appointmentAdded; i++) 
        {
            if (appoint[i].patients == 0) 
            {
                appoint[i].patients = patientNumber;
                appoint[i].date.year = year;
                appoint[i].date.month = month;
                appoint[i].date.day = day;
                appoint[i].time.hour = hour;
                appoint[i].time.min = min;
                appointmentAdded = 1; 
            }
        }
    }

    if (appointmentAdded) 
    {
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("\n*** Unable to schedule appointment. ***\n\n");
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appoint, int maxApp, struct Patient* pat, int maxPat)
{
    int input;
    int index;
    int answer;
    int i;
    int number;
    int year, month, day = 0;
    int isLeapYear, maxDay;
    struct Appointment patients = { 0 };
    int monthDay[] = { 31 , 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    printf("Patient Number: ");
    input = inputIntPositive();
    index = findPatientIndexByPatientNum(input, pat, maxPat);
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        printf("Year        : ");
        year = inputIntPositive();
        printf("Month (%d-%d): ", JAN, DEC);
        month = inputIntRange(JAN, DEC);

        maxDay = monthDay[month - 1];
        isLeapYear = year % 4 == 0 && year % 100 != 0;
        if (monthDay[1] && isLeapYear)
        {
            maxDay = monthDay[1] + 1;
        }
 
        printf("Day (%d-%d)  : ", MIN_DAY, maxDay);
        day = inputIntRange(MIN_DAY, maxDay);
            
        putchar('\n');
        printf("Name  : %s\n", pat[index].name);
        printf("Number: %05d\n", pat[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(pat[index].phone.number);
        printf(" (%s)\n", pat[index].phone.description);
        number = pat[index].patientNumber;
        printf("Are you sure you want to remove this appointment (y,n): ");
        answer = inputCharOption("yn");

        if (answer == 'y')
        {
            for (i = 0; i < maxApp; i++)
            {
                if (appoint[i].patients == number &&
                    appoint[i].date.year == year &&
                    appoint[i].date.month == month &&
                    appoint[i].date.day == day)
                {
                    appoint[i] = patients;
                }
            }
            printf("\nAppointment record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patient_num, index;

    printf("\nSearch by patient number: ");
    patient_num = inputIntPositive();
    putchar('\n');

    index = findPatientIndexByPatientNum(patient_num, patient, max);

    if (index >= 0)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, recordFound = 0;
    char tempPhoneNum[PHONE_LEN + 1] = { 0 };

    printf("\nSearch by phone number: ");
    validatePhoneNumber(tempPhoneNum, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(tempPhoneNum, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            recordFound = 1;
        }
    }
    if (!recordFound)
    {
        printf("\n*** No records found ***\n\n");
    }
    putchar('\n');
    suspend();
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, highest = 0;
    int nextNum = 0;
    for (i = 0; i < max; i++)
    {
        if (highest < patient[i].patientNumber)
        {
            highest = patient[i].patientNumber;
            nextNum = highest + 1;
        }
    }
    return nextNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i, indexFound = -1;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            indexFound = i;
        }
    }
    return  indexFound;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{

    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n"
        "Name  : ", patient->patientNumber);

    if (patient->name[0] == '\0')
    {
        inputCString(patient->name, 1, NAME_LEN);
        putchar('\n');
        inputPhoneData(&patient->phone);
    }
}


// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone)
{
    int choice;
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    choice = inputIntRange(1, 4);
    switch (choice)
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
        break;
    }
    if (choice != 4)
    {
        putchar('\n');
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        validatePhoneNumber(phone->number, PHONE_LEN);
    }
}

void validatePhoneNumber(char* str, int phoneLen)
{
    int length, valid;
    char getInput[PHONE_LEN + 1] = { 0 };
    char fmt[PHONE_LEN + 1] = { '\0' };
    do
    {
        valid = 1;
        sprintf(fmt, "%%%d[^\n]", phoneLen + 1);
        scanf(fmt, getInput);

        clearInputBuffer();

        length = strlen(getInput);

        while (str != '\0' && isdigit(str[length]))
        {
            length++;
        }

        if (length != phoneLen)
        {
            valid = 0;
            printf("Invalid %d-digit number! Number: ", phoneLen);
        }
    } while (!valid);

    strcpy(str, getInput);
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
 
    FILE* fp = NULL;
    int i;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        for (i = 0; i < max; i++) 
        {
            fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]\n", &patients[i].patientNumber, 
                patients[i].name, patients[i].phone.description, patients[i].phone.number);
        }
        fclose(fp);
    }
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max) 
{
  
    int i, count = 0;
    FILE* fp = NULL;

    fp = fopen(datafile, "r");

    if (fp != NULL) 
    {
        for (i = 0; i < max; i++)
        {
            fscanf(fp, "%d,%d,%d,%d,%d,%d\n",
                &appoints[i].patients, &appoints[i].date.year, &appoints[i].date.month,
                &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);

            if (appoints[i].patients != 0)
            {
                count++;
            }
        }
        fclose(fp);
    }
    return count;
}