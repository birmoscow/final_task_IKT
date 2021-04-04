#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Subject{
	private:
		string subject,
			   subjShort;
		int subId;
	public:
		Subject(string subject_, int subId_) : subject(subject_), subId(subId_), subjShort()
		{
			subjShort = subject_.substr(0, 3);
		}
		
		string getSub(){
			return(subject);
		}
		
		int getSubId(){
			return(subId);
		}
		
		string getSubjShort(){
			return(subjShort);
		}
};

class Student{
	private:
		vector<vector<int> > markVal;		// id val
		string firstName,
			   secondName,
			   parrentName,
			   grade,
			   fio;
		int	studentId;
	public:
		Student(int studentId_,
			    string secondName_, 
				string firstName_, 
				string parrentName_, 
				string grade_) 
				  	: markVal(),		//????
				 	  firstName(firstName_),
				  	  secondName(secondName_),
				  	  parrentName(parrentName_),
				  	  grade(grade_),
				  	  studentId(studentId_)
		{
			fio = "";
			fio = fio + secondName;
			if(firstName.size() !=0 && parrentName.size() !=0)
				fio = fio + ' ' + firstName[0] + '.' + parrentName[0] + '.';
		}
		
		string getFirstName(){
			return(firstName);
		}
		
		string getSecondName(){
			return(secondName);
		}
		
		string getParrentName(){
			return(parrentName);
		}
		
		string getGrade(){
			return(grade);
		}
		
		string getFio(){
			return(fio);		
		}
		
		int getStudentId(){
			return(studentId);
		}
		
		void initMarks(int subId_, int mark_){
			vector<int> bufferV_;
			bufferV_.push_back(subId_);
			bufferV_.push_back(mark_);
			markVal.push_back(bufferV_);
		}
		
		int markOfSub(int subId){
		
			int pointIdSub = -1;
			
			for(int i = 0; i < markVal.size(); i++){
				if(markVal[i][0] != subId)	
					continue;
				else{
					pointIdSub = i;
					break;
				}
			}
			
			if(pointIdSub == -1)
				return 0;
			
			return	markVal[pointIdSub][1];	
		}
		
		void setMarkOfSub(int subId, int changeMark){		
			for(int i = 0; i < markVal.size(); i++){
				if(markVal[i][0] != subId)	
					continue;
				else{
					markVal[i][1] = changeMark;
					return;
				}
			}
			
			cout << "\n\n>> Error"
				 << "\n>> cannot find subj";	
		}
		
		void deliteMark(int subId){
		
			int findMark;
			vector<int> buffV_;
			
		
			for(int i = 0; i < markVal.size(); i++){
				if(markVal[i][0] != subId)	
					continue;
				else{
					findMark = i;
					markVal.erase(markVal.begin() + i);
					break;
				}
			}
		}
		
		void addMark(int subId, int addMark_){
			vector<int> buffAdd;
			buffAdd.push_back(subId);
			buffAdd.push_back(addMark_);
			markVal.push_back(buffAdd);
		}		
};

//	functions

bool stopRec(string stopRec_);
bool tryCinInt(bool checkStrToInt);
bool checkSymStr(string __c);
bool checkStrToInt(string checkStrToInt_);
int findStudId(vector<Student> Stud, int id__);
int findSubId(vector<Subject> Sub, int id__);
void clearMarks(vector<Student> &Stud);
void clearSub(vector<Student> &Stud, vector<Subject> &Sub);
void clearStud(vector<Student> &Stud, vector<Subject> &Sub);
void delMark(vector<Student> &Stud, vector<Subject> &Sub);
void recInFileMarks(vector<Student> &Stud, vector<Subject> Sub);
void recInFileStudent(vector<Student> Stud);
void recInFileSubject(vector<Subject> Sub);
void delStud(vector<Student> &Stud, vector<Subject> &Sub);
void delSub(vector<Student> &Stud, vector<Subject> &Sub);



void initSub(vector<Subject> &Sub){
	string buffStr,
		   buffSubId,
		   buffSub;
	int countLine = 0,
		valRecord = 0,
		subIdInt;
	 
	ifstream FileSub ("subject.txt");
	 
	if(!FileSub){
		cout << "\n>> Error"
		 	 << "\n>> cannot open 'subject.txt'"
		 	 << "\n>> enter any key";
		 	 _getch();
		return;
  	}
  	
	while(getline(FileSub, buffStr)){
		buffSubId = "";
		buffSub = "";
		countLine = 0;
		valRecord = 0;
		
		for(int i = 0; i < buffStr.size(); i++){
		
			if(buffStr[i] != ' '){
				if(!valRecord){
					valRecord = 1;
				}
			}
			else{
				if(valRecord){
					countLine++;
					valRecord = 0;
				}			
			}
					
			if(countLine == 0 && valRecord == 1)
				buffSubId = buffSubId + buffStr[i];
			
			if(countLine == 1 && valRecord == 1)
				buffSub = buffSub + buffStr[i];		
		}
		
		subIdInt = atoi(buffSubId.c_str());
		
		if(subIdInt)
			Sub.push_back(Subject(buffSub, subIdInt));
	}
	
	FileSub.close();
}

////////////////////////////////////////////

void initStudentName(vector<Student> &Stud){
	string buffStr,
	   	   buffFirstName,
	 	   buffSecondName,
	 	   buffParrentName,
	 	   buffGrade,
	 	   buffStudentId;
	int countLine = 0,
		valRecord = 0,
		StudentIdInt;
	 
	ifstream FileStudent ("student.txt");
	 
	if(!FileStudent){
		cout << "\n>> Error"
		 	 << "\n>> cannot open 'student.txt'"
		 	 << "\n>> enter any key";
		 	 _getch();
		return;
  	}
  	
	while(getline(FileStudent, buffStr)){
		buffSecondName = "";
		buffParrentName = "";
		buffGrade = "";
		buffStudentId = "";
		buffFirstName = "";
		countLine = 0;
		valRecord = 0;
		
		for(int i = 0; i < buffStr.size(); i++){
		
			if(buffStr[i] != ' '){
				if(!valRecord){
					valRecord = 1;
				}
			}
			else{
				if(valRecord){
					countLine++;
					valRecord = 0;
				}			
			}
					
			if(countLine == 0 && valRecord == 1)
				buffStudentId = buffStudentId + buffStr[i];
			
			if(countLine == 1 && valRecord == 1)
				buffSecondName = buffSecondName + buffStr[i];
			
			if(countLine == 2 && valRecord == 1)
				buffFirstName = buffFirstName + buffStr[i];	
				
			if(countLine == 3 && valRecord == 1)
				buffParrentName = buffParrentName + buffStr[i];
				
			if(countLine == 4 && valRecord == 1)
				buffGrade = buffGrade + buffStr[i];
			
		}
		
		StudentIdInt = atoi(buffStudentId.c_str());
		
		
		if(buffSecondName.size() != 0)
			Stud.push_back(Student(StudentIdInt, buffSecondName, buffFirstName, buffParrentName, buffGrade));
		
	}
	
	FileStudent.close();

}

////////////////////////////////////////////

void initStudentMark(vector<Student> &Stud){
	string buffStr;
	int subId,
		studentId,
		markNotId,
		countLine = 0,
		count = 0;
		
	ifstream FileMarks ("marks.txt");
	
	if(!FileMarks){
		cout << "\n>> Error"
		   	 << "\n>> cannot open 'marks.txt'"
		   	 << "\n>> enter any key";
		_getch();
		return;
	}
	
	while(getline(FileMarks, buffStr)){
		countLine = 0;
		studentId = 0;
		for(int i = 0; i < buffStr.size(); i++ ){
			if(countLine == 0 && buffStr[i] != ' '){
				studentId = studentId * 10 + buffStr[i] - 48;
				continue;
			}
			else{
				if(countLine == 0 && buffStr[i] == ' '){
					countLine++;
					continue;
				}
			}
			if(countLine == 1 && buffStr[i] != ' '){
				subId = buffStr[i] - 48;
				countLine++;
				continue;
			}
			if(countLine == 2 && buffStr[i] != ' '){
				markNotId = buffStr[i] - 48;
				countLine++;
				continue;
			}
		}
	    
	   		for(int i = 0; i < Stud.size(); i++){
	   				if(Stud[i].getStudentId() == studentId){
	   	 				Stud[i].initMarks(subId, markNotId);
						break;	
	   	 			}
	   	 	}
	}
	
	FileMarks.close();
}

// cout bd files

void checkFiles(){
	string bufferCheck;

	ifstream FileMarks ("marks.txt");
	ifstream FileStudent ("student.txt");
	ifstream FileSub ("subject.txt");
	
	cout << endl << ">> students:\n\n";
	
	while(getline(FileStudent , bufferCheck)){
		cout << bufferCheck << endl;
	}
	
	cout << endl << ">> subj:\n\n";
	
	while(getline(FileSub , bufferCheck)){
		cout << bufferCheck << endl;
	}
	
	cout << endl << ">> marks:\n\n";
	
	while(getline(FileMarks , bufferCheck)){
		cout << bufferCheck << endl;
	}
	
	FileMarks.close();
	FileStudent.close();
	FileSub.close(); 
	
}

// make table without sorting

void makeTable(vector<Student> Stud, vector<Subject> Sub){
	
	int sizeOfSpaces = 20;
	string buffSubjShort,
		   buffFio;
	
	ofstream FileTable ("output.txt");
	
	if(!FileTable) cout << endl
				 		<< ">> Error\n>> cannot open output.txt\n\n";
	
	cout << "\n\n\n";
	
	for(int j = 0; j < sizeOfSpaces; j++){
		cout << " ";
		FileTable << " ";
	}
	
	for(int j = 0; j < Sub.size(); j++){
		cout << setw(3) << Sub[j].getSubjShort();
		FileTable << setw(3) << Sub[j].getSubjShort();
		cout << "   "; 			//3
		FileTable << "   "; 
	}
	
	cout << endl;
	FileTable << endl;
	
	for(int j = 0; j < Stud.size(); j++){
	
		FileTable << Stud[j].getFio();
		cout << Stud[j].getFio();
		
		for(int k = 0; k < sizeOfSpaces + 2 - Stud[j].getFio().size(); k++){
			cout << " ";
			FileTable << " ";
		}
		
		for(int countSub = 0; countSub < Sub.size(); countSub++){
			cout << Stud[j].markOfSub(countSub+1) 
				 << "     ";	//5
			FileTable << Stud[j].markOfSub(countSub+1) 
				 << "     ";	//5
		}
		
		FileTable << endl;
		cout << endl;
	}
	
	FileTable.close();
}

// no comments			last fix 01.05.20

void getAverageMark(vector<Student> Stud, vector<Subject> Sub){

	string buffSubIn;
	int	   buffSubId = -1,
		   summ = 0,
		   countVal = 0;
	float rez;
	
	cout << endl << "\n\n>> Enter the subject id"
		 << endl << ">> then press enter\n\n";
		 
	for(int i = 0; i < Sub.size(); i++){
	
		cout << endl << ">> "
			 << Sub[i].getSubId() << " "
			 << Sub[i].getSub();
		
	}
	
	cout << "\n\n\n>> ";
		
	cin >> buffSubIn;
	
	//fixed 01.05.20
	/*	
	for(int i = 0; i < Sub.size(); i++){		
			
		if(Sub[i].getSub() == buffSubIn){
			buffSubId = Sub[i].getSubId();
			break;
		}
		
	}
	
	if(buffSubId == -1) {
		cout << endl << ">> Error input"
			 << endl << ">> Press any key";
		_getch();
		return;
	}
	*/
	
	if(!tryCinInt(checkStrToInt(buffSubIn))){
		return;
	}
	
	buffSubId = atoi(buffSubIn.c_str());
	
	if(findSubId(Sub, buffSubId) == -1) {
		cout << endl << ">> Error"
			 << endl << ">> The subject does not exist"
			 << endl << ">> Press any key";
		_getch();	 
		return;
	}
	
	for(int i = 0; i < Stud.size(); i++){
		if(Stud[i].markOfSub(buffSubId)){
			summ += Stud[i].markOfSub(buffSubId);
			countVal++;
		}
	}
	
	if(countVal == 0) {
		cout << endl << ">> No marks"
			 << endl << ">> Press any key";
		_getch();
		return;
	}
	
	rez = summ/float(countVal);
	
	cout << endl << ">> Average mark for "
		 << Sub[findSubId(Sub, buffSubId)].getSub() << " equal "
		 << fixed << setprecision(3) << rez
		 << endl << endl
		 << ">> Press any key to exit the menu";
		 
	_getch();
}	

// function creates sortVector, change old/buff vec

void sortStudSN(vector<Student> Stud, vector<Student> &sortStr){
	
	if(!Stud.size()) return;
	
	Student Buff(1, "", "", "","");
	sortStr = Stud;

	for(int i = 0; i < Stud.size() - 1; i++){
		for(int k = 0; k < Stud.size() - 1; k++){
			if(sortStr[k].getSecondName() > sortStr[k+1].getSecondName()){
				Buff = sortStr[k];
				sortStr[k] = sortStr[k+1];
				sortStr[k+1] = Buff;
			}			
		}
	}
}

// func of menu -- sort

void getSortFile(vector<Student> &Stud, vector<Subject> &Sub){

	vector<Student> sortStud;	
	sortStudSN(Stud, sortStud);
	makeTable(sortStud, Sub);
}

// returns sort vector of grades/forms

void readGradesAndSort(vector<Student> Stud, vector<string> &buffGrade__){
	
	buffGrade__.clear();
	string buffGr,
		   buffFormNum_1,
		   buffFormNum_2;
	int flag__ = 1,
		num_1,
		num_2,
		flag_ = 1;
	
	//init
	
	for(int i = 0; i < Stud.size(); i++){
		flag__ = 1;
		buffGr = Stud[i].getGrade();
		
		if(!buffGr.size()) continue;
		
		for(int j = 0; j < buffGrade__.size(); j++){
			if(buffGrade__[j] == buffGr)
				flag__ = 0;
		}
		
		if(!flag__) continue;
		
		buffGrade__.push_back(buffGr);
	}

	//sort
	
	for(int i = 0; i < buffGrade__.size(); i++){
		for(int j = 0; j < buffGrade__.size() - 1; j++){

			buffFormNum_1 = "";
			buffFormNum_2 = "";	

			for(int q = 0; q > -1; q++){
				buffFormNum_1 += buffGrade__[j][q];
				if(!checkStrToInt(buffFormNum_1)){
					buffFormNum_1 = buffFormNum_1.substr(0, buffFormNum_1.size()-1);
					break;
				}
			}
				
			if(checkStrToInt(buffFormNum_1))
				num_1 = atoi(buffFormNum_1.c_str());
			else continue;
			
			for(int q = 0; q > -1; q++){
				buffFormNum_2 += buffGrade__[j+1][q];
				if(!checkStrToInt(buffFormNum_2)){
					buffFormNum_2 = buffFormNum_2.substr(0, buffFormNum_2.size()-1);
					break;
				}
			}

			if(checkStrToInt(buffFormNum_1))
				num_2 = atoi(buffFormNum_2.c_str());
			else continue;
				
			if(num_2 > num_1){
				buffGr = buffGrade__[j];
				buffGrade__[j] = buffGrade__[j+1];
				buffGrade__[j+1] = buffGr;
			}
		}
	}
	
	
	for(int i = 0; i < buffGrade__.size(); i++){
		for(int j = 0; j < buffGrade__.size() - 1; j++){
		
			flag_ = 1;		
		
			if(!checkStrToInt(buffGrade__[j].substr(0,1))) continue;
			
			buffFormNum_1 = buffGrade__[j];
			buffFormNum_2 = buffGrade__[j + 1];

			//check same form/grade

			for(int q = 0; q < buffFormNum_1.size(); q++){
				if(checkStrToInt(buffFormNum_1.substr(q, 1)) && buffFormNum_1[0] != 0) {}
				else{
					buffFormNum_1 = buffFormNum_1.substr(0, q);
					break;
				}
			}
			
			for(int q = 0; q < buffFormNum_2.size(); q++){
				if(checkStrToInt(buffFormNum_2.substr(q, 1)) && buffFormNum_2[0] != 0) {}
				else{
					buffFormNum_2 = buffFormNum_2.substr(0, q);
					break;
				}
			}
			
			if(buffFormNum_1 != buffFormNum_2){
				flag_ = 0;
			}
				
				if(!flag_) continue;
			
			buffFormNum_1 = buffGrade__[j];
			buffFormNum_2 = buffGrade__[j + 1];
			
			//find word
			
			while(true){
				if(checkStrToInt(buffFormNum_1.substr(0, 1)) && buffFormNum_1[0] != 0)
					buffFormNum_1 = buffFormNum_1.substr(1, buffFormNum_1.size() - 1);
				else break;

			}

			while(true){
				if(checkStrToInt(buffFormNum_2.substr(0, 1))  && buffFormNum_2[0] != 0)
					buffFormNum_2 = buffFormNum_2.substr(1, buffFormNum_2.size() - 1);
				else break;
			}
			
			//cout << endl << buffFormNum_1 << " " << buffFormNum_2 << endl;
			
			if(buffFormNum_1 > buffFormNum_2){
				buffGr = buffGrade__[j];
				buffGrade__[j] = buffGrade__[j+1];
				buffGrade__[j+1] = buffGr;
			}
		}
	}
}

// make table of sort grades

void getTableGrades(vector<Student> Stud ,vector<Subject> Sub){
	
	vector<string> buffGrade;
	int mark_1 = 0,
		mark_2 = 0,
		mark_3 = 0,
		mark_4 = 0,
		mark_5 = 0,
		buffInt_mark,
		spaceSize = 6;
	
	readGradesAndSort(Stud, buffGrade);
	
	ofstream makeTable ("output.txt");
	
	
	makeTable << "      " /* 6 spaces */ << "(1) (2) (3) (4) (5)";
	cout << endl
		 << endl
		 << endl
		 << "      " /* 6 spaces */ << "(1) (2) (3) (4) (5)";
	
	for(int i = 0; i < buffGrade.size(); i++){
		makeTable << endl << buffGrade[i]; 
		cout << endl << buffGrade[i];
			
		for(int k = 0; k < 6 - buffGrade[i].size(); k++){
			cout << " ";
			makeTable << " ";
		}
	
		buffInt_mark = 1;
		mark_1 = 0;
		mark_2 = 0;
		mark_3 = 0;
		mark_4 = 0;
		mark_5 = 0;
		
		for(int k = 0; k < Stud.size(); k++){
		
			if(Stud[k].getGrade() == buffGrade[i]){
			
				for(int q = 1; q < Sub.size() + 1; q++){
				//	cout << "ya tut";
					buffInt_mark = Stud[k].markOfSub(q);
					if(buffInt_mark == 1)	mark_1++;
					if(buffInt_mark == 2)	mark_2++;
					if(buffInt_mark == 3)	mark_3++;
					if(buffInt_mark == 4)	mark_4++;
					if(buffInt_mark == 5)	mark_5++;
				}
			}
		}
		
		cout << setw(2) << mark_1
			 << "  "
			 << setw(2) << mark_2
			 << "  "
			 << setw(2) << mark_3
			 << "  "
			 << setw(2) << mark_4
			 << "  "
			 << setw(2) << mark_5;
		
		makeTable << setw(2) << mark_1
				  << "  "
				  << setw(2) << mark_2
				  << "  "
				  << setw(2) << mark_3
				  << "  "
				  << setw(2) << mark_4
				  << "  "
				  << setw(2) << mark_5;		
	}
	
	makeTable.close();
	
	cout << endl;
}

// new stud

void recStud(vector<Student> &Stud){
	
	int idNew_;
	if(!Stud.size())	idNew_ = 1;
	else  idNew_ = Stud[Stud.size() - 1].getStudentId() + 1;
	string buffFirstName,
		   buffSecondName,
		   buffParrentName,
		   buffGrade;
	
	ofstream FileStudent ("student.txt", ios_base::app);
	
	if(!FileStudent){
		cout << endl << ">> Error to open stud" << endl;
		return;
	}
	
	cout << endl << ">> Enter second name >> ";
	cin >> buffSecondName;
	
	if(stopRec(buffSecondName)){
		cout << endl << ">> Stop rec"
			 << endl << ">> Press any key";
		FileStudent.close();
		_getch();
		return;
	}
	
	if(checkSymStr(buffSecondName)){
		cout << endl << ">> Error input"
			 << endl << ">> Enter only words"
			 << endl << ">> Press any key";
		_getch();
		FileStudent.close();
		return;
	}
	
	cout << endl << ">> Enter first name >> ";
	cin >> buffFirstName;
	
	if(stopRec(buffFirstName)){
		cout << endl << ">> Stop rec"
			 << endl << ">> Press any key";
		FileStudent.close();
		_getch();
		return;
	}
	
	if(checkSymStr(buffFirstName)){
		cout << endl << ">> Error input"
			 << endl << ">> Enter only words"
			 << endl << ">> Press any key";
		_getch();
		FileStudent.close();
		return;
	}
	
	cout << endl << ">> Enter parrent name >> ";
	cin >> buffParrentName;
	
	if(stopRec(buffParrentName)){
		cout << endl << ">> Stop rec"
			 << endl << ">> Press any key";
		FileStudent.close();
		_getch();
		return;
	}
	
	if(checkSymStr(buffParrentName)){
		cout << endl << ">> Error input"
			 << endl << ">> Enter only words"
			 << endl << ">> Press any key";
		_getch();
		FileStudent.close();
		return;
	}
	
	cout << endl << ">> Enter grade >> ";
	cin >> buffGrade;
	
	if(stopRec(buffGrade)){
		cout << endl << ">> Stop rec"
			 << endl << ">> Press any key";
		FileStudent.close();
		_getch();
		return;
	}
	
	if(buffGrade.size() == 2) {
		if(buffGrade[0] < 48 ||
			 buffGrade[0] > 58 ||
			 	 buffGrade[1] < 65 ||
				  	buffGrade[1] > 70 ){
					   	 
		cout << endl << ">> Invalid format"
			 << endl << ">> The input must be such that the form/grade and letter are written together"
			 << endl << ">> The form/grade < 99 and one big letter  [A, F]"
			 << endl << ">> Like '10F'  '1A'   etc."
			 << endl << ">> Press any key";
		
		_getch();
		FileStudent.close();
		
		return;
		}	
		
	} else if(buffGrade.size() == 3) {
		if(buffGrade[0] < 48 ||
			 buffGrade[0] > 58 ||
			 	buffGrade[1] < 48 ||
					 buffGrade[1] > 58 ||
			 			 buffGrade[2] < 65 ||
				  			 buffGrade[2] > 70){
					   	 
		cout << endl << ">> Invalid format"
			 << endl << ">> The input must be such that the form/grade and letter are written together"
			 << endl << ">> The form/grade < 99 and one big letter [A, F]"
			 << endl << ">> Like '10F'  '1A'   etc."
			 << endl << ">> Press any key";
		
		_getch();
		FileStudent.close();
		
		return;
		}
		
	} else {
		cout << endl << ">> Invalid format"
			 << endl << ">> The input must be such that the form/grade and letter are written together"
			 << endl << ">> The form/grade < 99 and one big letter [A, F]"
			 << endl << ">> Like '10F'  '1A'   etc."
			 << endl << ">> Press any key";
		
		_getch();
		FileStudent.close();
		
		return;
		
	}
	
	Stud.push_back(Student(idNew_, buffSecondName, buffFirstName, buffParrentName, buffGrade));
	FileStudent << "\n" << idNew_ << " "
				<< buffSecondName << " "
				<< buffFirstName << " "
				<< buffParrentName << " "
				<< buffGrade;
	
	FileStudent.close();
}

// new sub

void recSub(vector<Subject> &Sub){
	
	int idNew_;
	if(!Sub.size())	idNew_ = 1;
	else  idNew_ = Sub[Sub.size() - 1].getSubId() + 1;
	string buffGrade;
	
	ofstream FileSub ("subject.txt", ios_base::app);
	
	if(!FileSub){
		cout << endl << ">> Error to open subj" << endl;
		return;
	}
	
	cout << endl << ">> Enter subject >> ";
	
	cin >> buffGrade;
	
	if(stopRec(buffGrade)){
		cout << endl << ">> Stop rec"
			 << endl << ">> Press any key";
		FileSub.close();
		_getch();
		return;
	}
	
	if(checkSymStr(buffGrade)){
		cout << endl << ">> Error input"
			 << endl << ">> Enter only words"
			 << endl << ">> Press any key";
		_getch();
		FileSub.close();
		return;
	}
	
	for(int i = 0; i < Sub.size(); i++) {
		if(Sub[i].getSub() == buffGrade){
			cout << endl << endl
				 << endl << ">> The subject exists"
				 << endl << ">> Press any key";
			FileSub.close();
			_getch();
			return;
		}
	}
	
	Sub.push_back(Subject( buffGrade, idNew_));
	FileSub << "\n" << idNew_ << " "
			<< buffGrade;
	
	FileSub.close();
}

// recMark or question of overwriting

void recMark(vector<Student> &Stud, vector<Subject> Sub){
	
	int studId__,
		subId__,
		mark__;
		
	string buffStopRec;	
	
	ofstream FileMarks ("marks.txt", ios_base::app);
	
	if(!FileMarks){
		cout << endl << ">> Error to open marks" << endl;
		return;
	}
	
	makeTable(Stud, Sub);
	cout << endl << endl;
	
	cout << endl << ">> Enter student ID"
		 << endl << ">> And press enter";
	
	for(int i = 0; i < Stud.size(); i++){
		cout << endl << ">>  "<< Stud[i].getStudentId()
			 << " " << Stud[i].getSecondName()
			 << " " << Stud[i].getFirstName()
			 << " " << Stud[i].getParrentName()
			 << " " << Stud[i].getGrade();
	}
	
	cout << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)){
		cout << endl << ">> stop rec"
			 << endl << ">> press any key";
		FileMarks.close();
		_getch();
		return;
	}	
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		FileMarks.close();
		return;
	}
	
	studId__ = atoi(buffStopRec.c_str());
	
	if(findStudId(Stud, studId__) == -1) {
		cout << endl << ">> Error"
			 << endl << ">> The student does not exist"
			 << endl << ">> Press any key";
		FileMarks.close();
		_getch();	 
		return;
	}
		
	cout << endl << endl << ">> Enter subject ID"
		 << endl << ">> And press enter";
	
	for(int i = 0; i < Sub.size(); i++){
		cout << endl << ">>  "<< i + 1
			 << " " << Sub[i].getSub();
	}

	cout << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)){
		cout << endl << endl <<">> stop rec"
			 << endl << ">> press any key";
		FileMarks.close();
		_getch();
		return;
	}
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		FileMarks.close();
		_getch();
		return;
	}
	
	subId__ = atoi(buffStopRec.c_str());
	
	if(findSubId(Sub, subId__) == -1) {
		cout << endl << ">> Error"
			 << endl << ">> The subject does not exist"
			 << endl << ">> Press any key";
		FileMarks.close();
		_getch();	 
		return;
	}
	
	cout << endl << endl << ">> Enter mark"
		 << endl << ">> And press enter"
		 << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)){
		cout << endl << ">> stop rec"
			 << endl << ">> press any key";
		FileMarks.close();
		_getch();
		return;
	}
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		FileMarks.close();
		return;
	} 
	
	mark__ = atoi(buffStopRec.c_str());
	
	if(mark__ < 1 || mark__ > 5) {
	
		cout << endl << endl
			 << endl << ">> Error"
			 << endl << ">> Mark can be 1 2 3 4 5"
			 << endl << ">> Press any key";
			 
		FileMarks.close();
		_getch();
		return;
	}
	
	if(findStudId(Stud, studId__) !=-1)
		if(Stud[findStudId(Stud, studId__)].markOfSub(subId__)){
		
			char YN_;
			
			cout << endl << ">> mark exists, overwrite?"
				 << endl << ">> [Y/N]";
			
				while(true){				//fixed	30.04.20
					YN_ = _getch();
				
					if(YN_ == 'n' || YN_ == 'N'){
						FileMarks.close();
						return;
					}
					
					else if(YN_ == 'y' || YN_ == 'Y'){
					
						FileMarks.close();
						system("cls");
										
						Stud[findStudId(Stud, studId__)].deliteMark(subId__);
						
						// new
						Stud[findStudId(Stud, studId__)].addMark(subId__, mark__);
						//
						recInFileMarks(Stud, Sub);
						Stud.clear();
						
						initStudentName(Stud);
						initStudentMark(Stud);
						//	recMark(Stud, Sub); --> old version						
						//	replacing the mark without calling the menu
						return;
					}
				}
			
		}
	
	if(findStudId(Stud, studId__) != -1){
		
		Stud[findStudId(Stud, studId__)].addMark(subId__, mark__);
		
		FileMarks << "\n"
				  << studId__ << " "
				  << subId__ << " "
				  << mark__;
	}
	
	FileMarks.close();
}

// function of recs

void inputNewRec(vector<Student> &Stud, vector<Subject> &Sub){
	
	char input_;
	int flag__ = 1;
	
	while(flag__){
	
	system("cls");
	
	cout << ">> choose file to rec"
		 << endl << ">> 1. student"
		 << endl << ">> 2. subject"
		 << endl << ">> 3. marks"
		 << endl << ">> 0. Exit to menu"
		 << endl << ">> enter 'Q' to stop writing"
		 << endl << endl;
		 
	input_ = _getch();
			
		switch(input_){
			case '1':
				recStud(Stud);
				break;
			case '2':
				recSub(Sub);
				break;
			case '3':
				recMark(Stud, Sub);
				break;
			case '0':
				flag__ = 0;
				break;
			default:
				cout << endl << endl
					 << endl << ">> Error Input"
					 << endl << ">> Press any key";
				_getch();
				break;
		}
	}	
}

// menu of delRec

void deleteRec(vector<Student> &Stud, vector <Subject> &Sub){
	
	char chooseDel;
	int flag = 1;
	

	while(flag){
		
		system("cls");
				
		cout << "\t\t\tChoose object to del"
		 	 << endl << ">> 1. Student"
		 	 << endl << ">> 2. Subject"
			 << endl << ">> 3. Mark"
			 << endl << ">> 6. Delete all students"
			 << endl << ">> 7. Delete all subjects"
			 << endl << ">> 8. Delete all marks"
			 << endl << ">> 0. Exit to menu"
			 << endl << ">> press 'Q' to stop del";
		 
		
		chooseDel = _getch();
		
		switch(chooseDel){
			case '1':
				delStud(Stud, Sub);
				break;
			case '2':
				delSub(Stud, Sub);
				break;
			case '3':
				delMark(Stud, Sub);
				break;
			case '6':
				clearStud(Stud, Sub);
				cout << endl << ">> Press any key";
				_getch();
				break;
			case '7':
				clearSub(Stud, Sub);
				cout << endl << ">> Press any key";
				_getch();
				break;
			case '8':
				clearMarks(Stud);
				cout << endl << ">> Press any key";
				_getch();
				break;
			case '0':
				flag = 0;
				break;
			default:
				cout << endl << endl
					 << endl << ">> Error input"
					 << endl << ">> Press any key";
					 _getch();
				break;
		}
	}
}

// del all subj

void clearSub(vector<Student> &Stud, vector<Subject> &Sub){
	ofstream clearSub ("subject.txt");
	ofstream clearMarks ("marks.txt");
	
	clearSub << " ";
	clearMarks << " ";
	Stud.clear();
	Sub.clear();
	initSub(Sub);
	initStudentName(Stud);
	initStudentMark(Stud);
	
	clearMarks.close();
	clearSub.close();
}

//del all marks

void clearMarks(vector<Student> &Stud){
	ofstream clearMarks ("marks.txt");
	
	clearMarks << " ";
	Stud.clear();
	initStudentName(Stud);
	initStudentMark(Stud);
	
	clearMarks.close();
}

// del all students

void clearStud(vector<Student> &Stud, vector<Subject> &Sub){
	ofstream clearStudent ("student.txt");
	ofstream clearMarks ("marks.txt");
	
	clearStudent << " ";
	clearMarks << " ";
	
	Stud.clear();
	initStudentName(Stud);
	initStudentMark(Stud);
	
	clearMarks.close();
	clearStudent.close();
}

//menu of delMark

void delMark(vector<Student> &Stud, vector<Subject> &Sub){
	
	int _StudId,
		_SubId,
		_flag = 1;
		
	string buffStopRec;	
		
	makeTable(Stud, Sub);
	cout << endl << endl;	
		
	cout << endl << ">> Enter student ID"
		 << endl << ">> And press enter";
	
	for(int i = 0; i < Stud.size(); i++){
		cout << endl << ">>  "<< Stud[i].getStudentId()
			 << " " << Stud[i].getSecondName()
			 << " " << Stud[i].getFirstName()
			 << " " << Stud[i].getParrentName()
			 << " " << Stud[i].getGrade();
	}
	
	cout << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)) {
		cout << endl << ">> stop rec"
			 << endl << ">> press any key";
		_getch();
		return;
	}	
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		return;
	}
	
	_StudId = atoi(buffStopRec.c_str());
		 
	if(findStudId(Stud, _StudId) == -1) {
		cout << endl << ">> Error"
			 << endl << ">> The student does not exist"
			 << endl << ">> Press any key";
		_getch();	 
		return;
	}	 
		 
	cout << endl << endl << ">> Enter subject ID"
		 << endl << ">> And press enter";
	
	for(int i = 0; i < Sub.size(); i++){
		cout << endl << ">>  "<< i + 1
			 << " " << Sub[i].getSub();
	}
	
	cout << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)){
		cout << endl << ">> stop rec"
			 << endl << ">> press any key";
		_getch();
		return;
	}	
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		return;
	}
	
	_SubId = atoi(buffStopRec.c_str());
	
	if(findSubId(Sub, _SubId) == -1) {
		cout << endl << ">> Error"
			 << endl << ">> The subject does not exist"
			 << endl << ">> Press any key";
		_getch();	 
		return;
	}
	
	
		if(findStudId(Stud, _StudId) != -1){	/* check if stud exist*/

			if(Stud[findStudId(Stud, _StudId)].markOfSub(_SubId) != 0){		//check is mark exist
			
				Stud[findStudId(Stud, _StudId)].deliteMark(_SubId);
				recInFileMarks(Stud, Sub);
				Stud.clear();
				initStudentName(Stud);
				initStudentMark(Stud);
				return;
			}
		}
}

// deleteStudent

void delStud(vector<Student> &Stud, vector<Subject> &Sub){
	int _StudId,
		_flag = 1;
		
	string buffStopRec;	
		
	cout << endl << endl
		 << endl << ">> Enter student ID"
		 << endl << ">> And press enter";
	
	for(int i = 0; i < Stud.size(); i++){
		cout << endl << ">>  "<< Stud[i].getStudentId()
			 << " " << Stud[i].getSecondName()
			 << " " << Stud[i].getFirstName()
			 << " " << Stud[i].getParrentName()
			 << " " << Stud[i].getGrade();
	}
	
	cout << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)){
		cout << endl << ">> stop rec"
			 << endl << ">> press any key";
		_getch();
		return;
	}	
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		return;
	}
	
	_StudId = atoi(buffStopRec.c_str());
	
	if(findStudId(Stud, _StudId) == -1) {
		cout << endl << ">> Error"
			 << endl << ">> The student does not exist"
			 << endl << ">> Press any key";
		_getch();	 
		return;
	}
	
	for(int i = 0; i < Sub.size(); i++){
		Stud[findStudId(Stud, _StudId)].deliteMark(Sub[i].getSubId());
	}
	
	recInFileMarks(Stud, Sub);
	Stud.erase(Stud.begin() + findStudId(Stud, _StudId));
	recInFileStudent(Stud);
/*	
	Stud.clear();
	initStudentName(Stud);
	initStudentMark(Stud);
	
	Stud.erase(Stud.begin() + findStudId(Stud, _StudId));
	recInFileStudent(Stud);
	
	Stud.clear();
	initStudentName(Stud);
	initStudentMark(Stud);
*/	
	cout << endl << ">> Press any key";
	_getch();
}

// del Subject

void delSub(vector<Student> &Stud, vector<Subject> &Sub){

	int _SubId,
		_flag = 1;
	string buffStopRec;


	cout << endl << endl 
		 << endl << ">> Enter subject ID"
		 << endl << ">> And press enter";
	
	for(int i = 0; i < Sub.size(); i++){
		cout << endl << ">>  "<< Sub[i].getSubId()
			 << " " << Sub[i].getSub();
	}
	
	cout << endl << ">> ";
	
	cin >> buffStopRec;
	
	if(stopRec(buffStopRec)){
		cout << endl << ">> Stop rec"
			 << endl << ">> Press any key";
		_getch();
		return;
	}	
	
	if(!tryCinInt(checkStrToInt(buffStopRec))){
		return;
	}
	
	_SubId = atoi(buffStopRec.c_str());
	
	if(findSubId(Sub, _SubId) == -1){
		cout << endl << ">> Error"
			 << endl << ">> The subject does not exist"
			 << endl << ">> Press any key";
		_getch();
		return;
	}
	
	for(int i = 0; i < Stud.size(); i++){
		Stud[i].deliteMark(_SubId);
	}
	
	recInFileMarks(Stud, Sub);
	Stud.clear();
	initStudentName(Stud);
	initStudentMark(Stud);
	
	Sub.erase(Sub.begin()  + findSubId(Sub, _SubId));	
	recInFileSubject(Sub);
	Sub.clear();	
	initSub(Sub); 
	
	cout << endl << ">> Press any key";
}

// reRecord marks in file

void recInFileMarks(vector<Student> &Stud, vector<Subject> Sub){

	ofstream markFile ("marks.txt");

	for(int i = 0; i < Stud.size(); i++){
		for(int j = 0; j < Sub.size(); j++){
			if(Stud[i].markOfSub(j + 1) != 0){
				markFile << "\n"
						 << Stud[i].getStudentId() << " "
						 << j + 1 << " "
						 << Stud[i].markOfSub(j + 1);
				}
		}
	}
	
	markFile.close();
	
	cout << endl
		 << endl;
}

// record students in file 

void recInFileStudent(vector<Student> Stud){

	ofstream fileStud ("student.txt");
	
	for(int k = 0; k < Stud.size(); k++){
		fileStud << "\n" << Stud[k].getStudentId()
			     << " " << Stud[k].getSecondName()
			     << " " << Stud[k].getFirstName()
			     << " " << Stud[k].getParrentName()
			     << " " << Stud[k].getGrade();
	}
	
	fileStud.close();
	
	cout << endl
		 << endl;
}

//record subjects in file

void recInFileSubject(vector<Subject> Sub){

	ofstream fileSub ("subject.txt");
	
	for(int k = 0; k < Sub.size(); k++){
		fileSub << "\n" << Sub[k].getSubId()
			     << " " << Sub[k].getSub();
	}
	
	fileSub.close();
	
	cout << endl
		 << endl;
}

// check smth for exit

bool stopRec(string stopRec_){
	if((stopRec_[0] == 'q' ||
		  stopRec_[0] == 'Q') && stopRec_.size() == 1)
		return true;
	else
		return false;
}

// check str if it can be conv

bool checkStrToInt(string checkStrToInt_){
	for(int q = 0; q < checkStrToInt_.size(); q++){
		if(checkStrToInt_[q] == '0' || 
		  	 checkStrToInt_[q] == '1' ||
		  		 checkStrToInt_[q] == '2' ||
		  			 checkStrToInt_[q] == '3' ||
		  				 checkStrToInt_[q] == '4' ||
		 					  checkStrToInt_[q] == '5'	||
								   checkStrToInt_[q] == '6' ||
		  								checkStrToInt_[q] == '7' ||
										   checkStrToInt_[q] == '8' ||
											   checkStrToInt_[q] == '9'){}
		else
			return false;
	}
	return true;
}

//	find num of stud for Id

int findStudId(vector<Student> Stud, int id__){
	for(int i = 0; i < Stud.size(); i++){
		if(Stud[i].getStudentId() == id__)
			return i;
	}
	return -1;
}

// find num of sub for id

int findSubId(vector<Subject> Sub, int id__){
	for(int i = 0; i < Sub.size(); i++){
		if(Sub[i].getSubId() == id__)
			return i;
	}
	return -1;
}


//break smth if string cant be conv to int with cout of error

bool tryCinInt(bool checkStrToInt){
	if(!checkStrToInt){
		cout << endl << endl
			 << ">> enter numbers, not words"
			 << endl << ">> press any key";
			 _getch();
		return false;
	}
	else
		return true;
}

// check nums/sym in str

bool checkSymStr(string __c) {

	for(int i = 0; i < __c.size(); i++) {
		if(__c[i] < 65 || (__c[i] > 90 && __c[i] < 97) || __c[i] > 122)
			return true;	
	}
	
	return false;
}

///////////////////////////////////////////////////////

int main(){

	setlocale(LC_ALL, "Russian");
	char inputCase;
	int prg = 1;

	vector <Subject> Sub;
	vector <Student> Stud;

	initSub(Sub);
	initStudentName(Stud);
	initStudentMark(Stud);

	while(prg){
	
		system("cls");
		cout << "\t\t\tWaiting for input"
			 << endl << ">> 1. Viewing the contents of files"
			 << endl << ">> 2. Output a report in a table in output.txt"
			 << endl << ">> 3. getAverageMark"
			 << endl << ">> 4. Sort table of forms/grades/marks in output.txt"
			 << endl << ">> 5. getSortFile in output.txt"
			 << endl << ">> 6. Add new record"
			 << endl << ">> 7. Delete records"
			 << endl << ">> 0. Exit";

		inputCase = _getch();
	
		switch(inputCase){
			case '1':
				cout << "\n\n\n>> Viewing the contents of files\n\n";
				checkFiles();
				cout << "\n\n\n>> Press any key to exit the menu";
					 _getch();
				break;
			case '2':
				makeTable(Stud, Sub);
				cout << endl << ">> Press any key to exit the menu";
					 _getch();
				break;
			case '3':
				getAverageMark(Stud, Sub);
				break;
			case '4':
				getTableGrades(Stud, Sub);
				cout << endl << ">> Press any key to exit the menu";
					 _getch();
				break;
			case '5':
				getSortFile(Stud, Sub);
				cout << endl << ">> Press any key to exit the menu";
				_getch();
				break;
			case '6':
				inputNewRec(Stud, Sub);
				break;
			case '7':
				deleteRec(Stud,Sub);
				break;
			case '0':
				prg = 0;
				break;
			default:
				cout << "\n\n\n>> Input error"
					 << "\n>> Press any key to exit the menu";
					 _getch();
				break;
		}
	}
}
