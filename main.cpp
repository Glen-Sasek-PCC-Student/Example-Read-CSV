#include <iostream>
#include <fstream>

using namespace std;

const int MAXCHAR = 51;
const int ROW_COUNT = 15;
const int IGNORE_FIRST_ROWS = 100;
const int MAX_IGNORE_CHARS = 1000;
const char DATAFILE[] = "salaries.csv";

void openFile(ifstream &fin, const char name[]);

void readData(ifstream &fin, 
              int work_year[], 
              int salary_in_usd[], 
              int remote_ratio[], 
              char job_title[][MAXCHAR]);

void printData(int work_year[], 
               int salary_in_usd[], 
               int remote_ratio[], 
               char job_title[][MAXCHAR]);

int main() {

    int work_year[ROW_COUNT]= {0};
    int salary_in_usd[ROW_COUNT] = {0};
    int remote_ratio[ROW_COUNT] = {0};
    char job_title[ROW_COUNT][MAXCHAR] = {0};

    // work_year,experience_level,employment_type,job_title,salary,salary_currency,salary_in_usd,employee_residence,remote_ratio,company_location,company_size
    // 
    // 2023,SE,FT,Principal Data Scientist,80000,EUR,85847,ES,100,ES,L

    ifstream fin;
    openFile(fin, DATAFILE);

    for(int i = 0; i < IGNORE_FIRST_ROWS; i++) {
        fin.ignore(MAX_IGNORE_CHARS, '\n');
    }       

    readData(fin, work_year, salary_in_usd, remote_ratio, job_title);
    
    printData(work_year, salary_in_usd, remote_ratio, job_title);

    // Close file if still open
    if(fin) {
        fin.close();
    }
    return 0;
}

void openFile(ifstream &fin, const char name[]) {
    fin.open(name);
    if(fin) {
        cout << "Opened: " << name << endl;
    } else {
        cout << "Fail opening: " << name << endl;
    }
}

void readData(ifstream &fin, 
              int work_year[], 
              int salary_in_usd[], 
              int remote_ratio[], 
              char job_title[][MAXCHAR]) {  
    char comma; // to read and discard commas
    for(int row = 0; row < ROW_COUNT; row++) {
        fin >> work_year[row] >> comma;
        
        // skip experience_level,employment_type
        fin.ignore(MAX_IGNORE_CHARS, ',');
        fin.ignore(MAX_IGNORE_CHARS, ',');

        fin.getline(job_title[row], MAXCHAR, ',');

        // skip salary,salary_currency
        fin.ignore(MAX_IGNORE_CHARS, ',');
        fin.ignore(MAX_IGNORE_CHARS, ',');

        fin >> salary_in_usd[row] >> comma;

        // skip employee_residence
        fin.ignore(MAX_IGNORE_CHARS, ',');

        fin >> remote_ratio[row] >> comma;

        // skip company_location,company_size
        fin.ignore(MAX_IGNORE_CHARS, '\n');         
    }
}

void printData(int work_year[], 
               int salary_in_usd[], 
               int remote_ratio[], 
               char job_title[][MAXCHAR]) {  
    cout << "Data from file:" << endl;
    for(int row = 0; row < ROW_COUNT; row++) {
        cout << work_year[row] << ", "
             << job_title[row] << ", "
             << salary_in_usd[row] << ", "
             << remote_ratio[row] << endl;
    }
}   
