/* 
Name: Renato Recio 
ACC ID : r1154565
Program Status: Complete
Program Function: Payroll Report 3.0
				  Uses two input files to process
				  Payroll Information for up to 100 Employees
				
*/



////////////////////////////////////////////////////////////////////
//Includes                                                         
///////////////////////////////////////////////////////////////////	
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;



////////////////////////////////////////////////////////////////////
//Payroll Structure, stores the final payroll information for each
//of the employees                                                         
///////////////////////////////////////////////////////////////////	
struct Payroll{
	int id_num;
	string name;
	double gross_pay;
	double tax;
	double insurance;
	double net_pay;
	double total_gross_pay;
	double total_net_pay;
	bool invalid;
};


////////////////////////////////////////////////////////////////////
//Employee class: sets/gets information for an Employee Object                                                  
///////////////////////////////////////////////////////////////////	
class Employee 
{
  private:
    int id;             // employee ID
    char name[21];        // employee name
    double hourlyPay;   // pay per hour
    int numDeps;        // number of dependents
    int type;           // employee type
	
    
  public:
    Employee( int initId=0, char initName[] = 0, double initHourlyPay=0.0, 
              int initNumDeps=0, int initType=0 );// Constructor

    bool set(int newId, char newName[], double newHourlyPay,
             int newNumDeps, int newType);
	int get_id(){ return id;}
	char* get_name(){ return name;}
	double get_hourlyPay(){ return hourlyPay;}
	int get_numDeps(){return numDeps;}
	int get_type(){ return type;}
    
};

Employee::Employee( int initId, char initName[], 
                    double initHourlyPay,
                    int initNumDeps, int initType )
{
  bool status = set( initId, initName, initHourlyPay, 
                     initNumDeps, initType );
  int i;
  if ( !status )
  {
    id = 0;
    for (i = 0; i <= 20; i++) name[i] = '\0';
    hourlyPay = 0.0;
    numDeps = 0;
    type = 0;    
  }
}

bool Employee::set( int newId, char newName[], double newHourlyPay,
                                 int newNumDeps, int newType )
{
  bool status = false;
  int i;
  if ( newId > 0 && newHourlyPay > 0 && newNumDeps >= 0 && 
       newType >= 0 && newType <= 1 )
  {
    status = true;
    id = newId;
    for (i= 0; i < 20;i++)name[i] = newName[i];
    hourlyPay = newHourlyPay;
    numDeps = newNumDeps;
    type = newType;
  }
  return status;
}


////////////////////////////////////////////////////////////////////
//Function Prototypes                                                   
///////////////////////////////////////////////////////////////////	
string get_file_name(string type);
int store_employee_info(Employee all[], double hours[][2], ifstream &fin_master, ifstream &fin_trans);
int calculate_payroll_info(Employee emp[], double hours[][2], Payroll Payroll_Report[], int total);
void print_payroll_report(Payroll Payroll_Report[], ofstream &fout);



////////////////////////////////////////////////////////////////////
//Main Driver                                                   
///////////////////////////////////////////////////////////////////	
int main(int argc, char *argv[]){
	
	int total_payroll, i, j;
	string master, transaction;
	ifstream fin_master; //Master input file
	ifstream fin_trans; //Transaction input file
	ofstream fout; //Output file

	master = get_file_name("Master"); 

	transaction = get_file_name("Timecard");

	fin_master.open(master);
	fin_trans.open(transaction);
	
	Employee all[100]; //All Employee objects for each of the employees
	double hours[100][2]; //Stores hours in a 1-1 associativity to the all array
	for (i = 0 ; i < 100; i++){
		for (j = 0; j < 2; j++){
			hours[i][j] = -1;
		}
	}
	
	total_payroll = store_employee_info(all, hours, fin_master, fin_trans); 
	
	Payroll *Payroll_Report = new Payroll[100]; //Final payroll report values
	for (i = 0; i < total_payroll; i++){
		Payroll_Report[i].invalid = true;
		
		
	}
	calculate_payroll_info(all, hours, Payroll_Report, total_payroll);
	
	fout.open("Payroll_Report.txt"); //Output file Payroll_Report
	print_payroll_report(Payroll_Report, fout);
	
	//Close files
	fin_master.close();
	fin_trans.close();
	fout.close();
	
	return 1;
}




////////////////////////////////////////////////////////////////////
//Print the Payroll Report                                                      
///////////////////////////////////////////////////////////////////	
void print_payroll_report(Payroll Payroll_Report[], ofstream &fout){
	int i;
	
	    fout << "Payroll Report\n\n";
	
		fout << setw(4) << left << "ID  " << setw(27) << left << "Name";
		fout << setw(9) << right << "Gross Pay" << setw(1) << " " << setw(8) << right;
		fout << "Tax" << setw(1) << " " << setw(10) << "Insurance" << setw(10)<< "Net Pay";
	
	for (i = 0; i < 100; i ++){
			
		if (Payroll_Report[i].invalid == false && Payroll_Report[i].id_num != 0){
			fout << "\n" << setw(4) << left << fixed << setprecision(2)<< Payroll_Report[i].id_num << setw(27) << left << Payroll_Report[i].name;
			fout << setw(9) << right << fixed << setprecision(2)<< Payroll_Report[i].gross_pay << setw(1) << " " << setw(8) << right;
			fout << setprecision(2)<< Payroll_Report[i].tax << setw(1) << " " << setw(8) << right ;
			fout << setprecision(2)<< setw(10) << Payroll_Report[i].insurance;
			fout << setprecision(2)<< setw(10) << Payroll_Report[i].net_pay;
			}
		}
		
		fout << "\n\nTotal Gross Pay $ " << fixed << setprecision(2)<< Payroll_Report[0].total_gross_pay;
		fout << "\nTotal Net Pay   $ " << fixed << setprecision(2)<< Payroll_Report[0].total_net_pay;
	
	
}
	
	

////////////////////////////////////////////////////////////////////
//Calculate Payroll Info using Employee Objects                                                  
///////////////////////////////////////////////////////////////////	
int calculate_payroll_info(Employee emp[], double hours[][2], Payroll Payroll_Report[], int max_entries){
	int type, i, j, id, numDeps, total;
	char *name;
	double hourlyPay, hour, gross_pay, tax, insurance, net_pay, total_net, total_gross;
	total_gross = 0;
	total_net = 0;
	total = 0;
	for (i = 0 ; i < max_entries; i++){
		id = emp[i].get_id();
		if (id < 0)
			continue;
		for (j = 0; j < 100; j++){
			if (id == hours[j][0] && Payroll_Report[i].invalid == true){
				total++;
				name = emp[i].get_name();
				hourlyPay = emp[i].get_hourlyPay();
				numDeps = emp[i].get_numDeps();
				type = emp[i].get_type();
				hour = hours[j][i];
					if (type == 0){
			
						if (hour > 40){
							gross_pay = hourlyPay * 40;
							gross_pay += ((hour - 40) * (1.5 * hourlyPay));
						}
						else 
							gross_pay = hourlyPay * hour;
						}
						else 
						gross_pay = (hour * hourlyPay);
		
					tax = 0.15 * gross_pay;
					if (numDeps > 0){
						insurance = 20*numDeps;
				
					}
					net_pay = (gross_pay - tax - insurance);
		
					Payroll_Report[i].invalid = false;
			
					total_gross += gross_pay;
					total_net += net_pay;
			
					//Store all Payroll Values for each employee
					Payroll_Report[i].id_num = id;
					Payroll_Report[i].name = name;
					Payroll_Report[i].gross_pay = gross_pay;
					Payroll_Report[i].tax = tax;
					Payroll_Report[i].insurance = insurance;
					Payroll_Report[i].net_pay = net_pay;
				    break;
				    } 
				} //end for
			} //end for
			
			
			
		   
		    	Payroll_Report[0].total_gross_pay = total_gross;
				Payroll_Report[0].total_net_pay = total_net;
				
				
				return total;
		
		}
	
	
	
		


////////////////////////////////////////////////////////////////////
//Store employee information in each employee object of all[]                                       
///////////////////////////////////////////////////////////////////	
int store_employee_info(Employee all[], double hours[][2], ifstream &fin_master, ifstream &fin_trans){
	int i, j, newId, newNumDeps, newType, max_master_entries, tempId;
	double newHourlyPay, hoursWorked, hoursID;
	char gender;
	Employee temp;
	bool valid_employee;
	char names[21];

	char deposit[1];
	char *namepointer;
	string getName;
	string newName;
	max_master_entries = 0;
	i = 0;
	
	while (!fin_master.eof()){
		valid_employee = false;
		fin_master >> newId;
		
		
		fin_master.read(deposit, 1);
		fin_master.read(names, 20);
		names[20] = '\0';
				
		fin_master >> newHourlyPay;
		fin_master >> newNumDeps;
		fin_master >> newType;	
		valid_employee = temp.set(newId, names, newHourlyPay, newNumDeps, newType);
		
		if (valid_employee && newId != tempId){
			cout << "\n" << newId << " " << names << " " << newHourlyPay << " " << newNumDeps << " " << newType;
			all[i].set(newId, names, newHourlyPay, newNumDeps, newType);
		    max_master_entries++;	
			i++;
		} fin_master >> gender;
		tempId = newId;
	
	}
	
	
	i = 0;
	while (!fin_trans.eof()){
		fin_trans >> hoursID; 
		fin_trans >> hoursWorked;
		if (hoursWorked >= 0 && hoursID > 0){
		hours[i][1] = hoursWorked;
		hours[i][0] = hoursID;
		i++;
		}
	}
	
	
	return max_master_entries;
	
}


////////////////////////////////////////////////////////////////////
//Get the file name from user based on the type                                                    
///////////////////////////////////////////////////////////////////	
string get_file_name(string type){
	string file_name;
	bool done = false;
	bool invalid_file_name = false;
	int i;
	cout << "Please enter the file name for the " << type << " file, including .txt: ";
	getline(cin, file_name);
	while (!done){
	
		while (file_name.length() <= 4 || invalid_file_name){
			cout << "\nInvalid file, must include .txt and file name greater than 0 characters";
			getline(cin, file_name);
		
		}	
		invalid_file_name = true;
	for (i = 0; i < file_name.length(); i++){
		if (file_name.at(i) == '.')
			done = true;
		}
		
		
		} //end while

		return file_name;
	}
	 		
	
	
	
	
