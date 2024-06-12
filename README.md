# VetClinicSys
This is the  final project of my IPC144 course which was completed in winter 2023. This project is a veterinary clinic management system that allows users to manage patient information and appointments. The system supports functionalities such as viewing, adding, and removing patient records, as well as managing appointment schedules.

## Project Structure
The project is divided into several modules:
1. **Core Module**: Contains utility functions for user input and interface handling.
2. **Clinic Module**: Manages clinic-specific data structures and functionalities, including patient and appointment management.

### Core Module
- **User Interface Functions**: Clear input buffer and suspend screen for better user interaction.
- **User Input Functions**: Functions to handle integer input, integer ranges, character options, and formatted string input.
- **Utility Functions**: Display formatted phone numbers.

### Clinic Module
- **Data Structures**: Definitions for `Patient`, `Phone`, `Time`, `Date`, and `Appointment` structures.
- **Display Functions**: Functions to display patient and appointment data in formatted tables.
- **Menu Functions**: Functions to display and handle main, patient management, and appointment management menus.
- **File Functions**: Functions to import patient and appointment data from text files.
- **Appointment Management**: Functions to view, add, and remove appointments.
