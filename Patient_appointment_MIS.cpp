//
// Created by User on 20/06/2024.
//
//
// Created by User on 20/06/2024.
//
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class PatientsLL {
public:
    int patient_id;
    string name;
    string dob;
    string gender;
    PatientsLL* next;

    PatientsLL() : patient_id(0), name(""),dob(""),gender(""), next(nullptr) {}
    PatientsLL(int patient_id, string name, string dob, string gender) : patient_id(patient_id), name(name),dob(dob),gender(gender), next(nullptr) {}

    int getPatientId() const { return patient_id; }
    string getPatientName() const { return name; }
    string getPatientDob() const { return dob; }
    string getPatientGender() const { return gender; }
};

class DoctorsLL{
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
        PatientsLL * patient_id;
        DoctorsLL * doctor_id;
        string appointment_date;
        Appointments * next;

        Appointments(int appointment_id, int patient_id, int doctor_id, string appointment_date):
                appointment_id(appointment_id),appointment_date(appointment_date),
               patient_id(nullptr),doctor_id(nullptr), next(nullptr){}


        int getAppointmentId() const { return appointment_id; }
        string getAppointmentDate() const { return appointment_date; }
        int getPatientId() const { return patient_id->getPatientId(); }
        int getDoctorId() const { return doctor_id->getDoctorId(); }

        void setPatientId(PatientsLL * patient_id) { this->patient_id = patient_id; }
        void setDoctorId(DoctorsLL * doctor_id) { this->doctor_id = doctor_id; }
            
        };
        

class PatientsList {
public:
    PatientsLL* head;

    PatientsList() : head(nullptr) {}
// validate patient input data type
    bool validatePatientInput(int& patient_id, string& name, string& dob, string& gender) {
        if (patient_id <= 0) {
            cout << "Invalid patient ID. Please enter a positive integer." << endl;
            return false;
        }
        if (name.empty() || dob.empty() || gender.empty()) {
            cout << "Invalid, No field can be empty. Please enter required data" << endl;
            return false;
        }
    }

// add patient
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
    // save created patient to the file
    void savePatientToFile(PatientsLL* patient) {
        ofstream outfile;
        outfile.open("patients.txt", ios::app);
        outfile << patient->getPatientId() << "," << patient->getPatientName() << "," << patient->getPatientDob() << endl;
        outfile.close();
    }
    // load patients and display them from the file where saved
    void loadPatientsFromFile() {
        ifstream infile;
        infile.open("patients.txt");
        if (!infile) {
            cout << "Error in opening the file" << endl;
            return;
        }
        int patient_id;
        string name;
        string dob;
        string gender;
        while (infile >> patient_id >> name >> dob >> gender) {
            PatientsLL* patient = new PatientsLL(patient_id, name, dob, gender);
            addPatient(patient);
        }
        infile.close();
    }
    // display patients
    void displayPatients() {

        PatientsLL* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << "Patient" << "ID:" << temp->getPatientId() << "," << "Name:" << temp->getPatientName() << "," << "Age:" << temp->getPatientDob() << endl;
            temp = temp->next;
            i++;

        }
        cout << "---------------------" << endl;
}
};
class DoctorsList {
public:
    DoctorsLL* head;

    DoctorsList() : head(nullptr) {}
    // validate doctor input data type
    bool validateDoctorInput(int& doctor_id, string& name, string& specialization) {
        if (doctor_id <= 0) {
            cout << "Invalid doctor ID. Please enter a positive integer." << endl;
            return false;
        }
        if (name.empty() || specialization.empty()) {
            cout << "Invalid, No field can be empty. Please enter required data" << endl;
            return false;
        }
    }
// add doctor
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
    // save created doctor to the file
    void saveDoctorToFile(DoctorsLL* doctor) {
        ofstream outfile;
        outfile.open("doctors.txt", ios::app);
        if (!outfile) {
            cout << "Error in opening the file" << endl;
            return;
        }
        outfile << doctor->getDoctorId() << "," << doctor->getDoctorName() << "," << doctor->getDoctorSpecialization() << endl;
        outfile.close();
    }
    // read doctor data from the file
    void readDoctorDataFromFile() {
        ifstream infile;
        infile.open("doctors.txt");
        if (!infile) {
            cout << "Error in opening the file" << endl;
            return;
        }
        int doctor_id;
        string name, specialization;
        while (infile >> doctor_id >> name >> specialization) {
            DoctorsLL* doctor = new DoctorsLL(doctor_id, name, specialization);
            addDoctor(doctor);
        }
        infile.close();
    }
   
    // display doctors
    void displayDoctors() {

        DoctorsLL* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << "Doctor" << "ID:" << temp->getDoctorId() << "," << "Name:" << temp->getDoctorName() << "," << "Specialization:" << temp->getDoctorSpecialization() << endl;
            temp = temp->next;
            i++;

        }
        cout << "---------------------" << endl;
    };
};

class AppointmentsList {
public:
    Appointments* head;

    AppointmentsList() : head(nullptr) {}
    // validate appointment input data type
    bool validateAppointmentInput(int& appointment_id, int& patient_id, int& doctor_id, string& appointment_date) {
        if (appointment_id <= 0) {
            cout << "Invalid appointment ID. Please enter a positive integer." << endl;
            return false;
        }
        if (appointment_date.empty()) {
            cout << "Invalid, No field can be empty. Please enter required data" << endl;
            return false;
        }
    }
// add appointment
    void addAppointment(Appointments* appointment) {
        if (head == nullptr) {
            head = appointment;
        } else {
            Appointments* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = appointment;
        }
    }
  // save created appointment to the file 
    void saveAppointmentToFile(Appointments* appointment) {
        ofstream outfile;
        outfile.open("appointments.txt", ios::app);
        if (!outfile) {
            cout << "Error in opening the file" << endl;
            return;
        }

        outfile << appointment->getAppointmentId() << "," << appointment->getPatientId() << "," << appointment->getDoctorId() << "," << appointment->getAppointmentDate() << "," << appointment->getAppointmentDate() << endl;
        outfile.close();
    }
    // read appointment data from the file
    void readAppointmentDataFromFile() {
        ifstream infile;
        infile.open("appointments.txt");
        if (!infile) {
            cout << "Error in opening the file" << endl;
            return;
        }
        int appointment_id, patient_id, doctor_id;
        string appointment_date;
        while (infile >> appointment_id >> patient_id >> doctor_id >> appointment_date) {
            Appointments* appointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
            addAppointment(appointment);
        }
        infile.close();
    }
    // display appointments
    void displayAppointments() {

        Appointments* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << "Appointment" << "ID:" << temp->getAppointmentId() << "," << "Date:" << temp->getAppointmentDate() << endl;
            temp = temp->next;
            i++;

        }
        cout << "---------------------" << endl;
    }
};
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
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                // create patient
                int patient_id;
                string name;
                string dob;
                string gender;
                cout << "PATIENT REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID:" << endl;
                cin >> patient_id;
                cout << "NAME:" << endl;
                cin >> name;
                cout << "DOB:" << endl;
                cin >> dob;
                cout << "GENDER:" << endl;
                cin >> gender;
                cin.ignore();
                if (patientsList.validatePatientInput( patient_id, name, dob, gender)) {
                    PatientsLL* patient = new PatientsLL(patient_id, name, dob, gender);
                    patientsList.addPatient(patient);
                }
                break;
            };
            case 2: {
                // create doctor
                int doctor_id;
                string specialization;
                string name;
                cout << "DOCTOR REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID:" << endl;
                cin >> doctor_id;
                cout << "NAME:" << endl;
                getline(cin, name);
                cout << "SPECIALIZATION:" << endl;
                getline(cin, specialization);
                cin.ignore();
                if (doctorsList.validateDoctorInput(doctor_id, name, specialization)) {
                    DoctorsLL* doctor = new DoctorsLL(doctor_id, name, specialization);
                    doctorsList.addDoctor(doctor);
                }
                break;
            };
            case 3: {
                // create appointment
                int appointment_id;
                int patient_id;
                int doctor_id;
                string appointment_date;
                cout << "APPOINTMENT REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID:" << endl;
                cin >> appointment_id;
                cout << "PATIENT ID:" << endl;
                cin >> patient_id;
                cout << "DOCTOR ID:" << endl;
                cin >> doctor_id;
                cout << "DATE:" << endl;
                cin.ignore(); 
                getline(cin, appointment_date);
                if (appointmentsList.validateAppointmentInput(appointment_id, patient_id, doctor_id,appointment_date)) {
                    Appointments* appointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
                    appointmentsList.addAppointment(appointment);
                }
                break;
            };
            case 4: {
              // display patients
                patientsList.displayPatients();
                break;
            };
            case 5: {
                // display doctors
                doctorsList.displayDoctors();
                break;
            };
            case 6: {
                // display appointments
                appointmentsList.displayAppointments();
                break;
            };
            case 7: {
                cout << "Exiting the program..." << endl;
                exit(0);
                break;
            };
            default:{
                cout << "Invalid choice" << endl;
            };
        }
    }
    return 0;
}