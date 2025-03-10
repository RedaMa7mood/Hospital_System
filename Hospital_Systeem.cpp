#include <iostream>
#include <fstream>
#include <sstream> 
#include<Windows.h>
#include<vector>
#include<ctime>
#include <iomanip>
using namespace std;
struct Date {

	int day;
	int month;
	int year;
};

class User
{
protected:
	string Name;
	int ID;
	int Age;
	string role;
	string Password;

public:
	User() : ID(0), Age(0), role(""), Password("") {}
	void SetName(string n) { Name = n; }
	void SetId(int id) { ID = id; }
	void SetPassword(string pass) {Password=pass; }
	void SetAge(int a) { Age = a; }
	int GetId() { return ID; }
	string GetName() { return Name; }
	int GetAge() { return Age; }
	virtual	void  DisplayInfo() = 0;


	};

class Patient : public User
{ 
private:
	string medical_history;
	string gender;
	vector<Date>date;

public:
	Patient() : medical_history(""), gender("") {
		role = "patient"; // Default role for patients
	}

	void Setmedical(string m) { medical_history = m; }
	void SetGender(string g) { gender = g; }
	string GetMedical() { return medical_history; }
	string GetGender() { return gender; }
	string GetPassward() { return Password; }

	void SetDate(Date d)
	{
		cout << "At [ " << d.day << " / " << d.month << " / " << d.year << "] ";
		date.push_back(d);
	}
	void DisplayDate()
	{
		for (auto& d : date)
		{
			cout << d.day << " / " << d.month << " / " << d.year << "\n";
		}
		
	}
	Date GetDate() {
		if (!date.empty()) {
			// Assuming you want the first date from the list
			return date[0];
		}
		else {
			// Return a default date if the list is empty
			return Date();
		}
	}

	void  DisplayInfo() override 
	{
		

		cout <<"\t\t\t\t " << this->ID << "   " << this->Name << "     " << this->Age << "        " << this->Password << "      " << this->gender << "       " << this->medical_history << endl;
			
	}
	
};
class Doctor :public User
{
private:
	string Specilization;
	vector<Patient>assignedpatients;
	int Salary;

public:
	Doctor() :Specilization(""), Salary(0) {
		role = "Doctor";
	}

	void SetId(int id) { ID = id; }
	void SetName(string name) { Name = name; }
	void SetSalary(int s) { Salary = s; }
	void SetPassword(string pass) { Password = pass; }
	void SetAge(int age) { Age = age; }
	void SetSpecilization(string s) { Specilization = s; }
	 string GetPassward() { return Password; }
	 int GetSalary() { return Salary; }
	 string GetSpecilization() { return Specilization; }

	
	void assign_patient(Patient p)
	{
		assignedpatients.push_back(p);
		cout << "Patient " << p.GetName() << " assigned to Doctor " << this->Name << "  ";
	}
	void DisplayInfo() override
	{
		
			cout << "\t\t" << left
				<< setw(10) << this->ID
				<< setw(20) << this->Name
				<< setw(10) << this->Age
				<< setw(15) << this->Password
				<< setw(20) << this->Specilization
				<< setw(10) << this->Salary
				<< endl;
		


	}
	void DisplayAssignedPatients()
	{
		if (this->assignedpatients.empty())
		{
			cout << "\t\t\t\t\tThere is no patients assigned to Doctor " << this->Name<<endl;
			return;
		}

		cout << "\t\t\tDoctor " << this->Name << " Patients : \n";

		for (auto& p : assignedpatients)
		{
			cout << "at "; p.DisplayDate();
			cout << "\t\t\t\t " << p.GetId() << "  " << p.GetName() << "    " << p.GetAge() << "    " << p.GetMedical() << "     " << p.GetGender() << endl;
		}
	}



};

class Hospital
{
private:
	vector<Date>date;
	int nextpatient;
	int nextdoctor;
	vector<Patient>patients;
	vector<Doctor>Doctors;
public:
	Hospital() :nextpatient(0),nextdoctor(0) {
		loadPatientsFromFile("patient_data.txt");
		loadDoctorsFromFile("doctor_data.txt");
	};
	~Hospital()
	{

		saveDoctorsToFile("doctor_data.txt");
		savePatientsToFile("patient_data.txt");
	}
	
	void Displayassignedpatient()
	{
		
		for (auto& d : Doctors)
		{
			
			d.DisplayAssignedPatients();
		}
	}

	void viewAppointment(int patientId)
	{
		Patient* patient = searchPatient(patientId);
		if (patient != nullptr)
		{
			Date appointment = patient->GetDate();
			cout << "\t\t\t\t   ............Appointment Details............\n";
			cout << "\t\t\t\tPatient: " << patient->GetName() << endl;
			cout << "\t\t\t\tAppointment Date: " << appointment.day << "/"
				<< appointment.month << "/" << appointment.year << endl;
		}
		else
		{
			cout << "\t\t\t\tPatient not found!\n";
		}
	}

	void addpatient()
	{
		Patient p;
		p.SetId(nextpatient++);
		string n, pass, g, m;
		int a;
		cout << "\t\t\tEnter Name of patient : ";
		cin >> n;
		p.SetName(n);
		cout << "\t\t\tEnter age of patient : ";
		cin >> a;
		p.SetAge(a);
		cout << "\t\t\tEnter password : ";
		cin >> pass;
		p.SetPassword(pass);
		cout << "\t\t\tEnter your Gender : ";
		cin >> g;
		p.SetGender(g);
		cout << "\t\t\tEnter Medical History : ";
		cin >> m;
		p.Setmedical(m);
		patients.push_back(p);
		cout << "\t\t\Patient Added Successfully.........\n";

	}

	Patient* searchPatient(int id)
	{
		for (auto& p : patients)
		{
			if (id == p.GetId())
			{
				return &p;

			}
		}
		return nullptr;
	}


	void DisplayAllPatient()
	{
		cout << "\t\t\t\t   ................Display Patients................\n\n";
		cout << "\t\t\t\tID |  Name  | Age   |  Password  |   Gender  |  Medical History\n";
		cout << "\t\t\t  ----------------------------------------------------------------------\n";
		for (auto &patient : patients)
		{
			patient.DisplayInfo();
		}
	}

	void DeletePatient()
	{
		int id;
		cout << "\t\t\tEnter Id Of Patient You Want Delete :";
		cin >> id;
		for (auto it = patients.begin();it != patients.end();it++)
		{
			if (it->GetId() == id)
			{
				patients.erase(it);
				cout << "\t\t\t\t\tPatient with ID " << id << " has been deleted." << endl;
				--nextpatient;
				return;
			}

		}
		cout << "\t\t\t\t\tPatient with ID " << id << " not found." << endl;
	}

	void Editpatient()
	{

		int id, age;
		string name;
		string pass;

		cout << "\t\t\tEnter ID Of Patient You Want : ";
		cin >> id;
		Patient* p = searchPatient(id);
		if (p != nullptr)
		{
			cout << "\t\t\tEnter new name: "; cin >> name;
			cout << "\t\t\tEnter new password: "; cin >> pass;
			cout << "\t\t\tEnter new age: "; cin >> age;
			p->SetName(name);
			p->SetAge(age);
			p->SetPassword(pass);
		}
		else
		{
			cout << "\t\t\t\t\tThis Patient not exist!\n";
		}
	}

	 void generateDummyData(int n) {
		for (int i = 1;i <= n;i++)
		{
			Patient p;
			Doctor d;
			
			string names[] = { "Reda", "Ali", "Mohamed", "Eman", "Mariam", "Omar", "Aya", "Amr" };
		
			string medicalHistories[] = { "No allergies", "Asthma", "Diabetes", "Hypertension", "No medical issues" };
		
			string genders[] = { "Male", "Female" };
			
			string spec[] = { "heart","air and nose", "boons" };
			
			string name = names[rand() % 8];  
			int age = rand() % 50 + 20; 
			int salary = rand() % 5000 + 1000;
			string password = "pass" + to_string(rand() % 10000);  
			string gender = genders[rand() % 2]; 
			string medicalHistory = medicalHistories[rand() % 5]; 
			string specilization = spec[rand() % 3];

			p.SetId(nextpatient++);
			p.SetName(name);
			p.SetAge(age);
			p.SetPassword(password);
			p.SetGender(gender);
			p.Setmedical(medicalHistory);

			patients.push_back(p);

			d.SetId(nextdoctor++);
			d.SetName(name);
			d.SetAge(age);
			d.SetPassword(password);
			d.SetSpecilization(specilization);
			d.SetSalary(salary);

			Doctors.push_back(d);
		}
	}

	 //Doc op

	 void addDoctor()
	 {
		 Doctor d;
		 d.SetId(nextdoctor++);
		 string name, pass,spec;
		 int salary, age;
		 cout << "\t\t\tEnter Doctor Name :"; cin >> name;
		 d.SetName(name);
		 cout << "\t\t\tEnter Doctor Specilization :"; cin >> spec;
		 d.SetSpecilization(spec);
		 cout << "\t\t\tEnter Doctor Age :"; cin >> age;
		 d.SetAge(age);
		 cout << "\t\t\tEnter Doctor Password :"; cin >> pass;
		 d.SetPassword(pass);
		 cout << "\t\t\tEnter Doctor Salary :"; cin >> salary;
		 d.SetSalary(salary);
		 cout << "\t\t\tDocter Added Successfully.........\n";
		 Doctors.push_back(d);

	 }

	 Doctor* searchDoctor(int id)
	 {
		 for (auto &D : Doctors)
		 {
			 if (D.GetId() == id)
			 {
				 return &D;
				 
			 }
		 }
		 return nullptr;
	 }

	 void DisplayAllDoctor()
	 {
		 cout << "\n\t\t\t  ..................Display Doctors..................\n\n";
		 cout <<"\t\t" << left << setw(10) << "ID"
			 << setw(20) << "| Name"
			 << setw(10) << "| Age"
			 << setw(15) << "| Password"
			 << setw(20) << "| Specializing"
			 << setw(10) << "| Salary" << endl;
		 cout << "  \t\t -------------------------------------------------------------------------------\n";
		 for (auto& D : Doctors)
		 {
			 D.DisplayInfo();
		 }
	 }

	 void Editdoctor()
	 {
		 int id,age,sal;
		 string name, pass;
		 cout << "\t\t\tEnter ID Of Doc You Want : ";
		 cin >> id;
		 Doctor *D = searchDoctor(id);
		 if (D != nullptr)
		 {
			 cout << "\t\t\tEnter New Name : "; cin >> name;
			 cout << "\t\t\tEnter new Age : "; cin >> age;
			 cout << "\t\t\tEnter new Salary : "; cin >> sal;
			 cout << "\t\t\tEnter new Password : "; cin >> pass;
			 D->SetAge(age);
			 D->SetName(name);
			 D->SetPassword(pass);
			 D->SetSalary(sal);
			 cout << "\t\t\t\t\tYour Changing Done Successifully .....\n";
			 return;
		 }
		 cout << "\t\t\t\t\tThis Doctor Not Exist !\n";
		 
	 }

	 void Deletedoctor()
	 {
		 int id;
		 cout << "\t\t\tEnter Doc ID : "; cin >> id;
		 for (auto it = Doctors.begin();it != Doctors.end();it++)
		 {
			 if (it->GetId() == id)
			 {
				 Doctors.erase(it);
				 --nextdoctor;
				 cout << "\t\t\t\t\tDoctor with ID " << id << " has been deleted." << endl;
				 return;
			 }
		 }
		 cout << "\t\t\t\t\tDoctor with ID " << id << " not found." << endl;

	 }
	   
	 void addApointment()
	 {
		 int id,idd,day,month,year;
		 cout << "\t\t\tEnter your id: ";
		 cin >> id;
		 Patient* p = searchPatient(id);
		 if (p != nullptr)
		 {
			 cout << "\t\t\t\t\tWelcome " << p->GetName() << "To Our Hospital......\n\n";
			 cout << "\t\t\tAvailable Doctors : \n";
			 DisplayAllDoctor();
			 cout << "\t\t\tplease select id of doctor you want: ";
			 cin >> idd;
			 Doctor* D = searchDoctor(idd);
			 if (D != nullptr)
			 {
				 Date d;
				 cout << "\t\t\tEnter Date..........\n\n";
				 cout << "\t\t\tDay: ";cin >> day;
				 d.day = day;
				 cout << "\t\t\tMonth: ";cin >> month;
				 d.month = month;
				 cout << "\t\t\tYear: ";cin >> year;
				 d.year = year;
				 D->assign_patient(*p);
				 p->SetDate(d);
				

			 }
			 else {
				 cout << "\t\t\t\t\tDoctor with ID " << idd << " not found." << endl;

			 }
		 }
		 else
		 {
			 cout << "Patient with ID " << id << " not found." << endl;

		 }
	 }

	 void savePatientsToFile(const string& filename) {
		 fstream file(filename, ios::trunc|ios::out); // Overwrites instead of appending
		 if (!file) {
			 cout << "Error opening file!" << endl;
			 return;
		 }

		 file << nextpatient << "\n"; // Save last used ID

		 for (auto& p : patients) {
			 file << p.GetId() << " " << p.GetName() << " " << p.GetAge() << " "
				 << p.GetGender() << " " << p.GetMedical() << " " << p.GetPassward() << "\n";
		 }

		 file.close();
		 cout << "Patients data saved successfully.\n";
	 }


	 void saveDoctorsToFile(const string& filename) {
		 fstream file(filename,ios::trunc | ios::out);
		 if (!file) {
			 cout << "Error opening file!" << endl;
			 return;
		 }

		 file << nextdoctor << "\n"; // حفظ آخر ID مستخدم

		 for ( auto& d : Doctors) {
			 file << d.GetId() << " " << d.GetName() << " " << d.GetAge() << " "
				 << d.GetSpecilization() << " " << d.GetSalary() << " " << d.GetPassward()<<endl;
		 }
		 file.close();
		 cout << "Doctors data saved successfully.\n";
	 }

	 void loadPatientsFromFile(const string& filename) {
		 ifstream file(filename);
		 if (!file) {
			 cout << "Error opening file!" << endl;
			 return;
		 }

		 patients.clear();

		 file >> nextpatient; // استرجاع آخر ID للمرضى
		 file.ignore(); // لتجاوز سطر الـ ID الأول

		 string line;
		 while (getline(file, line)) {
			 stringstream ss(line);
			 string name, gender, medical, pass;
			 int id, age;
			 char comma;

			 ss >> id >> name>> age >> gender >> medical>> pass;

			 Patient p;
			 p.SetId(id);
			 p.SetName(name);
			 p.SetAge(age);
			 p.SetGender(gender);
			 p.Setmedical(medical);
			 p.SetPassword(pass);
			 patients.push_back(p);
		 }
		 file.close();
		 cout << "Patients data loaded successfully.\n";
	 }

	 void loadDoctorsFromFile(const string& filename) {
		 fstream file(filename,ios::in);
		 if (!file) {
			 fstream file(filename, ios::out);

			 cout << "Error opening file!" << endl;
			 return;
		 }

		 Doctors.clear();

		 file >> nextdoctor; // استرجاع آخر ID للأطباء
		 file.ignore(); // لتجاوز سطر الـ ID الأول

		 string line;
		 while (getline(file, line)) {
			 stringstream ss(line);
			 string name, spec, pass;
			 int id, age, salary;
			 char comma;

			 ss >> id  >> name >> age >> spec >> salary >> pass;

			 Doctor d;
			 d.SetId(id);
			 d.SetName(name);
			 d.SetAge(age);
			 d.SetSpecilization(spec);
			 d.SetSalary(salary);
			 d.SetPassword(pass);
			 Doctors.push_back(d);
		 }
		 file.close();
		 cout << "Doctors data loaded successfully.\n";
	 }

	 bool login_patient()
	 {
		 string pass;
		 int username;
		 bool loggedin = false;
		 cout << "\t\t\t\t\tPatient Login\n\n";
		 cout << "\t\t\t=========================================================\n\n";
		 cout << "\t\tEnter Username : ";
		 cin >> username;
		 cout << "\t\tEnter Passward : ";
		 cin >> pass;
		 for (auto& p : patients)
		 {
			 if (p.GetId() == username)
			 {
				 if (p.GetPassward() == pass)
				 {
					 loggedin = true;
					 break;
				 }
				
			 }
			 
		 }
		 return loggedin;
	 } 
	 
	 bool login_doctor()
	 {
		 int username;
		 string pass;
		 cout << "\t\t\t\t\tDoctor Login\n\n";
		 cout << "\t\t\t======================================================\n\n";
		 cout << "\t\tEnter Username : ";
		 cin >> username;
		 cout << "\t\tEnter Passward : ";
		 cin >> pass;
		 bool loggedin = false;
		 for (auto& d : Doctors)
		 {
			 if (d.GetId() == username)
			 {
				 if (d.GetPassward() == pass)
				 {
					 cout << "\t\tWelcome Dr " << d.GetName() << "To Our Hospital\n";
					 loggedin = true;
					 break;
				}
				 
			 }
		 }
		 return loggedin;

	 }
	 void Administrator()
	 {
		 bool exit = false;
		 while (!exit)
		 {
			 Sleep(750);
			 system("cls");

			 cout << "\t\t\t\t\t ___________________________\n";
			 cout << "\t\t\t\t\t|                           |\n";
			 cout << "\t\t\t\t\t|   A D M I N S T R T O R   |\n";
			 cout << "\t\t\t\t\t|___________________________|\n";
			 cout << "\t\t\t__________________________________________________________________\n\n";
			 cout << "\t\t[1]ADD Patient \t [2]Edit Patient \t[3]Removing Patient \t[4]Display Patients\n\n ";
			 cout << "\t\t[5]ADD Doctor \t [6]Edit Doctor \t[7]Removing Doctor \t[8]Display Doctors \n\n";
			 cout << "\t\t\t\t      \t\t[9]Exit \n\n";
			 int choice;
			 cout << "\tEnter Operation You Want: ";
			 cin >> choice;
			 switch (choice)
			 {
			 case 1:
				 cout << "\t\t\t\t   ................ADD Patient................\n\n";
				 addpatient();
				 break;
			 case 2:
				 cout << "\t\t\t\t   ................Edit Patient................\n\n";
				 Editpatient();
				 break;
			 case 3:
				 cout << "\t\t\t\t   ................Removeing Patient................\n\n";
				 DeletePatient();
				 break;
			 case 4:
				
				 DisplayAllPatient();
				 cin.ignore();
				 cin.get();
				 break;
			 case 5:
				 cout << "\t\t\t\t   ................ADD Doctor................\n\n";
				 addDoctor();

				 break;
			 case 6:
				 cout << "\t\t\t\t   ................Edit Doctor................\n\n";
				 Editdoctor();

				 break;
			 case 7:
				 cout << "\t\t\t\t   ................Removeing Doctor................\n\n";
				 Deletedoctor();

				 break;

			 case 8:
				 DisplayAllDoctor();
				 cin.ignore();
				 cin.get();

				 break;
			 case 9:
				 exit = true;
				 break;
			 default:
				 cout << "Invalid Operation!\n";
			 }
		 }
	 }



	 void Doctor_admin()
	 {
		
		 int choice;
		 bool exit = false;
		 while (!exit)
		 {
			 Sleep(750);
			 system("cls");
			 cout << "\t\t\t\t\t ___________________________\n";
			 cout << "\t\t\t\t\t|                           |\n";
			 cout << "\t\t\t\t\t|        D O C T O R        |\n";
			 cout << "\t\t\t\t\t|___________________________|\n";
			 cout << "\t\t\t__________________________________________________________________\n\n";
			 cout << "\t\t[1]View assigned patients\n";
			 cout << "\t\t[2]Edit Account\n";
			 cout << "\t\t[3]Delete Account\n";
			 cout << "\t\t[4]Exit\n\n";
			 cout << "\t\tSelect Operation You Want: ";
			 cin >> choice;
			 switch (choice)
			 {
			 case 1:
				 Displayassignedpatient();
				 cin.ignore();
				 cin.get();

				 break;
			 case 2:
				 cout << "\t\t\t\t   ................Edit Account................\n\n";
				 Editdoctor();
					 break;
			 case 3:
				 cout << "\t\t\t\t   ................Delete Account................\n\n";
				 Deletedoctor();
				 exit = true;
				 break;
			 case 4:
				 exit = true;
				 break;
			 default:
				 break;
			 }


		 }
	 }
	 void Patient_admin()
	 {
		
		 int choice;
		 bool exit=false;
		 while (!exit)
		 {
			 Sleep(750);
			 system("cls");
		
			 cout << "\t\t\t\t\t ___________________________\n";
			 cout << "\t\t\t\t\t|                           |\n";
			 cout << "\t\t\t\t\t|        P A T I E N T      |\n";
			 cout << "\t\t\t\t\t|___________________________|\n";
			 cout << "\t\t\t__________________________________________________________________\n\n";
			 cout << "\t\t[1]Make Appointment\n";
			 cout << "\t\t[2]View Appointment\n";
			 cout << "\t\t[3]Delete Account  \n";
			 cout << "\t\t[4]Edit Account  \n";
			 cout << "\t\t[5]Exit\n\n";
			 cout << "\t\tSelect Operation You Want: ";
			 cin >> choice;
			 switch (choice)
			 {
			 case 1:
				 cout << "\t\t\t\t   ................Make Appointment................\n\n";
				 addApointment();
				 break;
			 case 2:
				 cout << "Enter Your Id : ";
				 int id; cin >> id;
				 viewAppointment(id);

				 cin.ignore();
				 cin.get();

				 break;
			 case 3:
				 cout << "\t\t\t\t   ................Delete Account................\n\n";
				 DeletePatient();
				 exit = true;
				 break;
			 case 4:
				 cout << "\t\t\t\t   ................Edit Account................\n\n";
				 Editpatient();
				 break;
			 case 5:
				 exit = true;
				 break;
			 default:
				 cout << "Invalid Operation.....!\n";
				 break;
			 }
		 }
		 
		


		

		


	 }

	 void menu()
	 {
		 bool exit = false;
			while (!exit)
			{
				Sleep(750);
				system("cls");
				int role, id;
				string username, pass;
				cout << "\t\t\t\t\t ___________________________\n";
				cout << "\t\t\t\t\t|                           |\n";
				cout << "\t\t\t\t\t|  Welcome To Our Hospital  |\n";
				cout << "\t\t\t\t\t|___________________________|\n";
				cout << "\t\t\t____________________________________________________________\n\n";
				cout << "\t\t\t\t\t[1] Adminstrator\n";
				cout << "\t\t\t\t\t[2] Doctor\n";
				cout << "\t\t\t\t\t[3] Patient\n";
				cout << "\t\t\t\t\t[4] Exit\n";

				cout << "\t\t\t\tSelect Your Role :";
				cin >> role;
				switch (role)
				{
				case 1:
					cout << "\n\t\t\t\t\tAdminstrator\n";
					cout << "\t\t\t===============================================\n\n";
					cout << "\t\tEnter Username : ";
					cin >> username;
					cout << "\t\tEnter Passward : ";
					cin >> pass;
					if (username == "reda@gmail.com")
					{
						if (pass == "123456")
						{
							cout << "\t\t\t\t\tWelcome Reda To Your System.......\n";
							Administrator();
						}
						else
						{
							cout << "\t\tWronge Password Try Again!\n";

						}
					}
					else
					{
						cout << "\t\tWronge Username Try Again!\n";
					}
					break;

				case 2:

					if (!login_doctor())
					{
						cout << "Wrong Username or Password!\n";
					}
					else
					{
						Doctor_admin();
					}
					break;

				case 3:
					if (!login_patient())
					{
						cout << "Wrong Username or Password!\n";

					}
					else
					{
						Patient_admin();
					}
					break;

				case 4:
					exit = true;
					break;

				default:
					cout << "Invalid Operation try again.......\n";

				}



			}
	 }
};






int main()
{
	srand(time(0));
	

	Hospital h;
	h.menu();
	
	

}