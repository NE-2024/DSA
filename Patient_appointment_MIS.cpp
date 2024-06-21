#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class PatientsLL {
public:
    int patient_id;
    string name;
    string dob;
    string gender;
    PatientsLL* next;

    PatientsLL() : patient_id(0), name(""), dob(""), gender(""), next(nullptr) {}
    PatientsLL(int patient_id, string name, string dob, string gender) : patient_id(patient_id), name(name), dob(dob), gender(gender), next(nullptr) {}

    int getPatientId() const { return patient_id; }
    string getPatientName() const { return name; }
    string getPatientDob() const { return dob; }
    string getPatientGender() const { return gender; }
};

class DoctorsLL {
public:
    int doctor_id;
    string name;
    string specialization;
    DoctorsLL* next;

    DoctorsLL(int doctor_id, string name, string specialization) :
        doctor_id(doctor_id), name(name),
        specialization(specialization), next(nullptr) {}

    int getDoctorId() const { return doctor_id; }
    string getDoctorName() const { return name; }
    string getDoctorSpecialization() const { return specialization; }
};

class Appointments {
public:
    int appointment_id;
    PatientsLL* patient_id;
    DoctorsLL* doctor_id;
    string appointment_date;
    Appointments* next;

    Appointments(int appointment_id, int patient_id, int doctor_id, string appointment_date) :
        appointment_id(appointment_id), appointment_date(appointment_date),
        patient_id(nullptr), doctor_id(nullptr), next(nullptr) {}

    int getAppointmentId() const { return appointment_id; }
    string getAppointmentDate() const { return appointment_date; }
    int getPatientId() const { return patient_id->getPatientId(); }
    int getDoctorId() const { return doctor_id->getDoctorId(); }

    void setPatientId(PatientsLL* patient_id) { this->patient_id = patient_id; }
    void setDoctorId(DoctorsLL* doctor_id) { this->doctor_id = doctor_id; }
};

class PatientsList {
public:
    PatientsLL* head;

    PatientsList() : head(nullptr) {}

    bool validatePatientInput(int patient_id, const string& name, const string& dob, const string& gender) {
        if (patient_id <= 0) {
            cerr << "Invalid patient ID. Please enter a positive integer." << endl;
            return false;
        }
        if (name.empty() || !regex_match(name, regex("^[A-Za-z ]+$"))) {
            cerr << "Invalid name. Please enter a valid name without numbers or special characters." << endl;
            return false;
        }
        if (dob.empty() || !regex_match(dob, regex("^\\d{4}/\\d{2}/\\d{2}$"))) {
            cerr << "Invalid date of birth. Please enter the date in the format yyyy/mm/dd." << endl;
            return false;
        }
        if (gender.empty() || (gender != "Male" && gender != "Female")) {
            cerr << "Invalid gender. Please enter either 'Male' or 'Female'." << endl;
            return false;
        }
        return true;
    }
// adding patient
    void addPatient(PatientsLL* patient) {
        if (head == nullptr) {
            head = patient;
        } else {
            PatientsLL* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = patient;
        }
    }
// saving patient to file
    static void savePatientToFile(PatientsLL* patient) {
        ofstream outfile;
        outfile.open("patients.txt", ios::app);
        if (!outfile) {
            cerr << "Error in opening the file" << endl;
            return;
        }
        outfile << patient->getPatientId() << "," << patient->getPatientName() << "," << patient->getPatientDob() << "," << patient->getPatientGender() << endl;
        outfile.close();
        cout << "Patient data saved to the file." << endl;
    }
// loading patients from the file
    void loadPatientsFromFile() {
        ifstream infile;
        infile.open("patients.txt");
        if (!infile) {
            cout << "Error in opening the file." << endl;
            return;
        }
        string line;
        while (getline(infile, line)) {
            istringstream ss(line);
            string id, name, dob, gender;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, dob, ',');
            getline(ss, gender, ',');
            auto* patient = new PatientsLL(stoi(id), name, dob, gender);
            addPatient(patient);
        }
    }
// display patients
    void displayPatients() {
        PatientsLL* temp = head;
        while (temp != nullptr) {
            cout << "Patient ID: " << temp->getPatientId() << ", Name: " << temp->getPatientName() << ", DOB: " << temp->getPatientDob() << ", Gender: " << temp->getPatientGender() << endl;
            temp = temp->next;
        }
    }
};

class DoctorsList {
public:
    DoctorsLL* head;

    DoctorsList() : head(nullptr) {}

    bool validateDoctorInput(int doctor_id, const string& name, const string& specialization) {
        if (doctor_id <= 0) {
            cerr << "Invalid doctor ID. Please enter a positive integer." << endl;
            return false;
        }
        if (name.empty() || !regex_match(name, regex("^[A-Za-z ]+$"))) {
            cerr << "Invalid name. Please enter a valid name without numbers or special characters." << endl;
            return false;
        }
        if (specialization.empty() || !regex_match(specialization, regex("^[A-Za-z ]+$"))) {
            cerr << "Invalid specialization. Please enter a valid specialization without numbers or special characters." << endl;
            return false;
        }
        return true;
    }
// Creating a doctor
    void addDoctor(DoctorsLL* doctor) {
        if (head == nullptr) {
            head = doctor;
        } else {
            DoctorsLL* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = doctor;
        }
    }
// Saving the doctor to the file
    static void saveDoctorToFile(DoctorsLL* doctor) {
        ofstream outfile;
        outfile.open("doctors.txt", ios::app);
        if (!outfile) {
            cerr << "Error in opening the file" << endl;
            return;
        }
        outfile << doctor->getDoctorId() << "," << doctor->getDoctorName() << "," << doctor->getDoctorSpecialization() << endl;
        outfile.close();
        cout << "Doctor data saved to the file." << endl;
    }
// read the doctor from the file
    void readDoctorDataFromFile() {
        ifstream infile;
        infile.open("doctors.txt");
        if (!infile) {
            cout << "Error in opening the file." << endl;
            return;
        }
        string line;
        while (getline(infile, line)) {
            istringstream ss(line);
            string id, name, specialization;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, specialization, ',');
            auto* doctor = new DoctorsLL(stoi(id), name, specialization);
            addDoctor(doctor);
        }
    }
// displaying doctors
    void displayDoctors() const {
        DoctorsLL* temp = head;
        while (temp != nullptr) {
            cout << "Doctor ID: " << temp->getDoctorId() << ", Name: " << temp->getDoctorName() << ", Specialization: " << temp->getDoctorSpecialization() << endl;
            temp = temp->next;
        }
        cout << "---------------------" << endl;
    }
};

class AppointmentsList {
public:
    Appointments* head;

    AppointmentsList() : head(nullptr) {}

    bool validateAppointmentInput(int appointment_id, int patient_id, int doctor_id, const string& appointment_date) {
        if (appointment_id <= 0) {
            cerr << "Invalid appointment ID. Please enter a positive integer." << endl;
            return false;
        }
        if (appointment_date.empty() || !regex_match(appointment_date, regex("^\\d{4}/\\d{2}/\\d{2}$"))) {
            cerr << "Invalid date. Please enter the date in the format yyyy/mm/dd." << endl;
            return false;
        }
        return true;
    }
// Check whether the patient and doctor exists
    bool checkPatientAndDoctorExistence(int patient_id, int doctor_id, PatientsList& patientsList, DoctorsList& doctorsList) {
        PatientsLL* tempPatient = patientsList.head;
        bool patientExists = false;
        while (tempPatient != nullptr) {
            if (tempPatient->getPatientId() == patient_id) {
                patientExists = true;
                break;
            }
            tempPatient = tempPatient->next;
        }
        if (!patientExists) {
            cerr << "Patient with ID " << patient_id << " does not exist." << endl;
            return false;
        }

        DoctorsLL* tempDoctor = doctorsList.head;
        bool doctorExists = false;
        while (tempDoctor != nullptr) {
            if (tempDoctor->getDoctorId() == doctor_id) {
                doctorExists = true;
                break;
            }
            tempDoctor = tempDoctor->next;
        }
        if (!doctorExists) {
            cerr << "Doctor with ID " << doctor_id << " does not exist." << endl;
            return false;
        }
        return true;
    }
// Create an appointment
    void addAppointment(Appointments* appointment) {
        if (head == nullptr) {
            head = appointment;
            return;
        }
        Appointments* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = appointment;
    }
// save appointment from the file
    void saveAppointmentToFile(Appointments* appointment) {
        ofstream outfile;
        outfile.open("appointments.txt", ios::app);
        if (!outfile) {
            cerr << "Error in opening the file" << endl;
            return;
        }

        outfile << appointment->getAppointmentId() << "," << appointment->getPatientId() << "," << appointment->getDoctorId() << "," << appointment->getAppointmentDate() << endl;
        outfile.close();
        cout << "Appointment saved successfully" << endl;
    }
// Create appointment
    void addAppointment(int appointment_id, int patient_id, int doctor_id, const string& appointment_date, PatientsList& patientsList, DoctorsList& doctorsList) {
        if (!validateAppointmentInput(appointment_id, patient_id, doctor_id, appointment_date)) {
            cerr << "Invalid input. Appointment not created." << endl;
            return;
        }

        if (!checkPatientAndDoctorExistence(patient_id, doctor_id, patientsList, doctorsList)) {
            cerr << "Appointment not created. Patient or doctor does not exist." << endl;
            return;
        }

        auto* appointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
        addAppointment(appointment);
        saveAppointmentToFile(appointment);
    }
// Read appointments from the file
    void readAppointmentDataFromFile() {
        ifstream infile;
        infile.open("appointments.txt");
        if (!infile) {
            cerr << "Error in opening the file" << endl;
            return;
        }
        string line;
        while (getline(infile, line)) {
            istringstream ss(line);
            string id, patient_id, doctor_id, date;
            getline(ss, id, ',');
            getline(ss, patient_id, ',');
            getline(ss, doctor_id, ',');
            getline(ss, date, ',');
            auto* appointment = new Appointments(stoi(id), stoi(patient_id), stoi(doctor_id), date);
            addAppointment(appointment);
        }
    }

    void displayAppointments() {
        Appointments* temp = head;
        while (temp != nullptr) {
            cout << "Appointment ID: " << temp->getAppointmentId() << ", Date: " << temp->getAppointmentDate() << endl;
            temp = temp->next;
        }
        cout << "---------------------" << endl;
    }
};
// The menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Register a patient" << endl;
    cout << "2. Register a doctor" << endl;
    cout << "3. Register an appointment" << endl;
    cout << "4. Display Patients" << endl;
    cout << "5. Display Doctors" << endl;
    cout << "6. Display Appointments" << endl;
    cout << "7. Exit the program" << endl;
    cout << "----------------------------" << endl;
}

int main() {
    PatientsList patientsList;
    DoctorsList doctorsList;
    AppointmentsList appointmentsList;
    int choice;

    displayMenu();
    while (true) {
        cout << "Enter your choice: " << endl;
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter an integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                int patient_id;
                string name, dob, gender;

                cout << "PATIENT REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID: ";
                while (!(cin >> patient_id)) {
                    cout << "Invalid input. Please enter a positive integer for ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                cout << "NAME: ";
                getline(cin, name);
                cout << "DOB: ";
                getline(cin, dob);
                cout << "GENDER: ";
                getline(cin, gender);

                if (patientsList.validatePatientInput(patient_id, name, dob, gender)) {
                    PatientsLL* patient = new PatientsLL(patient_id, name, dob, gender);
                    patientsList.addPatient(patient);
                    PatientsList::savePatientToFile(patient);
                    cout << "Patient registered successfully" << endl;
                }

                break;
            }
            case 2: {
                int doctor_id;
                string name, specialization;

                cout << "DOCTOR REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID: ";
                while (!(cin >> doctor_id)) {
                    cout << "Invalid input. Please enter a positive integer for ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                cout << "NAME: ";
                getline(cin, name);
                cout << "SPECIALIZATION: ";
                getline(cin, specialization);

                if (doctorsList.validateDoctorInput(doctor_id, name, specialization)) {
                    DoctorsLL* doctor = new DoctorsLL(doctor_id, name, specialization);
                    doctorsList.addDoctor(doctor);
                    DoctorsList::saveDoctorToFile(doctor);
                    cout << "Doctor registered successfully" << endl;
                }

                break;
            }
            case 3: {
                int appointment_id, patient_id, doctor_id;
                string appointment_date;

                cout << "APPOINTMENT REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID: ";
                while (!(cin >> appointment_id)) {
                    cout << "Invalid input. Please enter a positive integer for ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "PATIENT ID: ";
                while (!(cin >> patient_id)) {
                    cout << "Invalid input. Please enter a positive integer for Patient ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cout << "DOCTOR ID: ";
                while (!(cin >> doctor_id)) {
                    cout << "Invalid input. Please enter a positive integer for Doctor ID: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                cin.ignore();
                cout << "DATE (yyyy/mm/dd): ";
                getline(cin, appointment_date);

                if (appointmentsList.validateAppointmentInput(appointment_id, patient_id, doctor_id, appointment_date) &&
                    appointmentsList.checkPatientAndDoctorExistence(patient_id, doctor_id, patientsList, doctorsList)) {
                    appointmentsList.addAppointment(appointment_id, patient_id, doctor_id, appointment_date, patientsList, doctorsList);
                    cout << "Appointment registered successfully" << endl;
                }

                break;
            }
            case 4: {
                patientsList.displayPatients();
                break;
            }
            case 5: {
                doctorsList.displayDoctors();
                break;
            }
            case 6: {
                appointmentsList.displayAppointments();
                break;
            }
            case 7: {
                cout << "Exiting the program..." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice" << endl;
            }
        }
        displayMenu();
    }
    return 0;
}
