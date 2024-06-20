
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


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

    // load patients and display them from the file where saved
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
            cout << "Patient" << " ID:" << temp->getPatientId() << ", " << "Name: " << temp->getPatientName() << ", " << "DOB: " << temp->getPatientDob() << ", " << "Gender: " << temp->getPatientGender() << endl;
            temp = temp->next;
        }
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
    static void saveDoctorToFile(DoctorsLL* doctor) {
        ofstream outfile;
        outfile.open("doctors.txt", ios::app);
        if (!outfile) {
            cout << "Error in opening the file" << endl;
            return;
        }
        outfile << doctor->getDoctorId() << "," << doctor->getDoctorName() << "," << doctor->getDoctorSpecialization() << endl;
        outfile.close();
        cout << "Doctor data saved to the file" << endl;
    }
    // read doctor data from the file
    void readDoctorDataFromFile() {
        ifstream infile;
        infile.open("doctors.txt");
        if (!infile) {
            cout << "Error in opening the file" << endl;
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
   
    // display doctors
    void displayDoctors() const {

        DoctorsLL* temp = head;
        while (temp != nullptr) {
            cout << "Doctor" << "ID:" << temp->getDoctorId() << "," << "Name:" << temp->getDoctorName() << "," << "Specialization:" << temp->getDoctorSpecialization() << endl;
            temp = temp->next;

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
// check existence of patient and doctor
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
            cout << "Patient with ID " << patient_id << " does not exist." << endl;
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
            cout << "Doctor with ID " << doctor_id << " does not exist." << endl;
            return false;
        }
        return true;
    }
// if patient and doctor exist add appointment
    void addAppointment(int appointment_id, int patient_id, int doctor_id, string appointment_date, PatientsList& patientsList, DoctorsList& doctorsList) {
        if (!checkPatientAndDoctorExistence(patient_id, doctor_id, patientsList, doctorsList)) {
            return;
        }
        auto* appointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
        addAppointment(appointment);
        saveAppointmentToFile(appointment);
    }
    // add appointment to the list
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
        cout << "Appointment saved successfully" << endl;
    }
    // read appointment data from the file
    void readAppointmentDataFromFile() {
        ifstream infile;
        infile.open("appointments.txt");
        if (!infile) {
            cout << "Error in opening the file" << endl;
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
    // display appointments
    void displayAppointments() {

        Appointments* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << "Appointment" << "ID:" << temp->getAppointmentId() << "," << "Date:" << temp->getAppointmentDate() << endl;
            temp = temp->next;
        

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
                cout << "ID: ";
                cin >> patient_id;
                cout << "NAME: ";
                cin >> name;
                cout << "DOB: ";
                cin >> dob;
                cout << "GENDER: ";
                cin >> gender;
                cin.ignore();

                    PatientsLL* patient = new PatientsLL(patient_id, name, dob, gender);
                    patientsList.addPatient(patient);
                    cout << "Patient registered successfully" << endl;

                break;
            };
            case 2: {
                // create doctor
                int doctor_id;
                string specialization;
                string name;
                cout << "DOCTOR REGISTRATION" << endl;
                cout << "------------------------" << endl;
                cout << "ID: ";
                cin >> doctor_id;
                cout << "NAME: ";
                cin >> name ;
                cout << "SPECIALIZATION: ";
                cin >> specialization;
                cin.ignore();
                    DoctorsLL* doctor = new DoctorsLL(doctor_id, name, specialization);
                    doctorsList.addDoctor(doctor);

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
                cout << "PATIENT ID: " ;
                cin >> patient_id;
                cout << "DOCTOR ID: " ;
                cin >> doctor_id;
                cout << "DATE: " ;
                cin.ignore(); 
                cin >> appointment_date;
                    Appointments* appointment = new Appointments(appointment_id, patient_id, doctor_id, appointment_date);
                    appointmentsList.addAppointment(appointment);

                break;
            };
            case 4: {
              // display patients
                patientsList.displayPatients();
                displayMenu();
                break;
            };
            case 5: {
                // display doctors
                doctorsList.displayDoctors();
                displayMenu();
                break;
            };
            case 6: {
                // display appointments
                appointmentsList.displayAppointments();
                displayMenu();
                break;
            };
            case 7: {
                cout << "Exiting the program..." << endl;
                exit(0);
                break;
            };
            default:{
                cout << "Invalid choice" << endl;
                displayMenu();
                break;
            
            };
        }
    }
    return 0;
}