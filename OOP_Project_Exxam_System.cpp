#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Base class for questions
class Question {
public:
    virtual void display() = 0; // Pure virtual function to display the question
};

// MCQ question class
class MCQ : public Question {
private:
    string prompt;
    vector<string> choices;
    int correctChoiceIndex;
public:
    MCQ(const string& p, const vector<string>& c, int correctIndex) : prompt(p), choices(c), correctChoiceIndex(correctIndex) {}
	MCQ(const string& p, const vector<string>& c) : prompt(p), choices(c) {}
    // Method to display the MCQ question
    void display() override {
        cout << "Question: " << prompt << endl;
        for (size_t i = 0; i < choices.size(); ++i) {
            cout << i + 1 << ". " << choices[i] << endl;
        }
    }

    // Method to get the prompt of the MCQ question
    string getPrompt() const { return prompt; }

    // Method to check if a choice index is correct
    bool isCorrectChoice(int index) const {
        return index == correctChoiceIndex;
    }
};

// True or False question class
class TrueFalse : public Question {
	private:
    string prompt;
    bool correctAnswer;
public:
    TrueFalse(const string& p, bool correct) : prompt(p), correctAnswer(correct) {}
    TrueFalse(const string& p) : prompt(p) {}

    // Method to display the True or False question
    void display() override {
        cout << "Question: " << prompt << " (True/False)" << endl;
    }

    // Method to get the prompt of the True or False question
    string getPrompt() const { return prompt; }

    // Method to check if the provided answer is correct
    bool isCorrect(bool answer) const {
        return answer == correctAnswer;
    }
};

    // Attributes and methods specific to True or False questions
// Short answer question class
class ShortAnswer : public Question {
    // Attributes and methods specific to Short Answer questions
    private:
    string prompt;
    string correctAnswer;
public:
    ShortAnswer(const string& p, const string& correct) : prompt(p), correctAnswer(correct) {}
	ShortAnswer(const string& p) : prompt(p) {}
    // Method to display the Short Answer question
    void display() override {
        cout << "Question: " << prompt << endl;
    }

    // Method to get the prompt of the Short Answer question
    string getPrompt() const { return prompt; }

    // Method to check if the provided answer is correct
    bool isCorrect(const string& answer) const {
        return answer == correctAnswer;
    }
};

// Long answer question class
class LongAnswer : public Question {
    // Attributes and methods specific to Long Answer questions
    private:
    string prompt;
    string correctAnswer;
public:
    LongAnswer(const string& p, const string& correct) : prompt(p), correctAnswer(correct) {}
    LongAnswer(const string& p) : prompt(p) {}

    // Method to display the Long Answer question
    void display() override {
        cout << "Question: " << prompt << endl;
    }

    // Method to get the prompt of the Long Answer question
    string getPrompt() const { return prompt; }

    // Method to check if the provided answer is correct
    bool isCorrect(const string& answer) const {
        return answer == correctAnswer;
    }
};

// Base class for users
class User {
protected:
    string name;
public:
    virtual void enterInfo() = 0; // Pure virtual function to enter user info
    virtual void displayInfo() = 0; // Pure virtual function to display user info
};

// Teacher class
class Teacher : public User {
    // Attributes and methods specific to Teacher
    private:
    string department;
public:
    // Constructor
    Teacher(const string& n, const string& dep) : User(n), department(dep) {}

    // Method to enter teacher information
    
    void enterInfo() override {
    cin.ignore(); // Clear input buffer
    cout << "Enter teacher's name: ";
    getline(cin, name);
    cout << "Enter department: ";
    cin >> department;
    cin.ignore(); // To ignore the newline character left in the input buffer
	}

    // Method to display teacher information
    void displayInfo() override {
        cout << "Teacher Information:" << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
    }
    
	void writeToFile(ofstream& out) const {
	    if (!out) {
	        cerr << "Error: Unable to write to file" << endl;
	        return;
	    }
	    out << name << ',' << department << '\n';
    }
    
    static vector<Teacher> readFromFile(const string& filename) {
        vector<Teacher> teachers;
        ifstream in(filename);
        if (!in) {
            cerr << "Error opening " << filename << endl;
            return teachers;
        }
        string line;
        while (getline(in, line)) {
            if (!line.empty()) {
                size_t pos = 0;
                string token;
                vector<string> tokens;

                while ((pos = line.find(',')) != string::npos) {
                    tokens.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                tokens.push_back(line); // Add the last token after the last comma

                if (tokens.size() == 3) {
                    string nme = tokens[0];
                    string dep = tokens[1]);
                    teachers.push_back(Teacher(nme, dep));
                }
            }
        }
        in.close();
        return teachers;
    }
};

// Student class
class Student : public User {
    // Attributes and methods specific to Student
    private:
    int studentID;
public:
    // Constructor
    Student(const string& n, int id) : User(n), studentID(id) {}

    // Method to enter student information
    void enterInfo() override {
        cout << "Enter Student Information:" << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Student ID: ";
        cin >> studentID;
    }

    // Method to display student information
    void displayInfo() override {
        cout << "Student Information:" << endl;
        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
    }
};

// Paper class to store questions
class Paper {
    // Attributes and methods to manage questions in a paper
    private:
    vector<MCQ*> mcq; // Vector to store pointers to questions
    vector<TrueFalse*> tf;
    vector<ShortAnswer*> sq;
    vector<LongAnswer*> lq;
public:
    // Method to add a question to the paper
    void addMCQ(MCQ* mcqs) {
        mcq.push_back(mcqs);
    }
    
    void addTrueFalse(TrueFalse* tfs) {
    tf.push_back(tfs);
    }
    
    void addShortAnswer(ShortAnswer* sqs) {
    sq.push_back(sqs);
    }
    
    void addLongAnswer(LongAnswer* lqs) {
    lq.push_back(lqs);
    }

    // Method to display all questions in the paper
    void displayMCQ() {
        cout << "MCQ's :" << endl;
        for (MCQ* mul : mcq) {
            mul->display();
            cout << endl;
        }
    }
    
    void displayTrueFalse() {
        cout << "True False :" << endl;
        for (TrueFalse* yesNo : tf) {
            yesNo->display();
            cout << endl;
        }
    }
    
    void displayShortAnswers() {
        cout << "ShortQuestions :" << endl;
        for (ShortAnswer* sas : sq) {
            sas->display();
            cout << endl;
        }
    }
    
    void displayQuestions() {
        cout << "Long Questions :" << endl;
        for (LongAnswer* las : lq) {
            las->display();
            cout << endl;
        }
    }
    
    

    // Destructor to release memory
//    ~Paper() {
//        for (Question* q : questions) {
//            delete q;
//        }
//    }
};

// Function prototypes
void displayMenuTeacher();
void displayMenuStudent();

int main() {
//for oop
	MCQ m1("Which OOP principle emphasizes reusability and building relationships between classes? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m2("What does OOP stand for? ", {"A) Object-Oriented Programming", "B) Object-Oriented Protocol", "C) Object-Oriented Processing", "D)  Object-Oriented Procedure"});
	MCQ m3("In OOP, which concept allows a class to have multiple methods with the same name but different parameters? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m4("Which OOP concept allows a class to inherit properties and behavior from another class? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m5("Which OOP principle focuses on bundling data and methods that work on the data into a single unit? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	
	TrueFalse tf1("In C++, a class can have multiple constructors with different parameter lists.");
	TrueFalse tf2("Inheritance in C++ allows a class to inherit properties and behaviors from multiple base classes simultaneously.  ");
	TrueFalse tf3("Private members of a base class are accessible in the derived class in C++. ");
	TrueFalse tf4("Polymorphism in C++ allows a function to have different forms based on the number or type of parameters. ");
	TrueFalse tf5("Encapsulation in C++ is the mechanism of wrapping data (variables) and functions (methods) into a single unit. ");
	
	ShortAnswer sa1("What is encapsulation in C++? ");
	ShortAnswer sa2("Explain the concept of inheritance in C++. ");
	ShortAnswer sa3("How do you achieve polymorphism in C++? ");
	ShortAnswer sa4("What is a constructor, and why is it used in C++? ");
	ShortAnswer sa5("How does C++ support the concept of abstraction? ");
	
	LongAnswer la1("make a program ");
	LongAnswer la2("Explain in details ");
	LongAnswer la3("Define the tearms ");
	LongAnswer la4("Construct a class diagram ");
	LongAnswer la5("what is ");					
//for linear
	MCQ m1L("What is the definition of a vector space? ", {"A) A set of vectors that cannot be added or multiplied.", "B)  A set of vectors closed under addition and scalar multiplication", "C) A set of vectors with only one dimension", "D) A set of vectors with infinite dimensions"});
	MCQ m2L("What is the span of a set of vectors? ", {"A) The number of vectors in the set.", "B)  The space formed by all possible linear combinations of the vectors in the set.", "C) The determinant of the vectors in the set.", "D)  The length of the vectors in the set"});
	MCQ m3L("What is a linear transformation? ", {"A) A transformation that preserves distances between vectors.", "B)  A transformation that only affects one dimension of a vector", "C) A transformation that maps vectors to scalars", "D) A transformation that preserves vector addition and scalar multiplication."});
	MCQ m4L("What does it mean for a set of vectors to be linearly independent? ", {"A) The vectors in the set are all multiples of each other.", "B) The span of the vectors in the set is equal to the number of vectors.", "C) The only solution to the equation c1v1 + c2v2 + ......+ cnvn = 0 is c1 = c2 = ...... = cn = 0", "D) The vectors in the set are all orthogonal to each other."});
	MCQ m5L("What is the determinant of a square matrix used for? ", {"A) It determines the number of rows and columns in the matrix.", "B)  It measures the size of the matrix.", "C) It determines whether the matrix is invertible.", "D) It calculates the eigenvalues of the matrix"});
	
	TrueFalse tf1L(" ");
	TrueFalse tf2L(" ");
	TrueFalse tf3L(" ");
	TrueFalse tf4L(" ");
	TrueFalse tf5L(" ");
	
	ShortAnswer sa1L(" ");
	ShortAnswer sa2L(" ");
	ShortAnswer sa3L(" ");
	ShortAnswer sa4L(" ");
	ShortAnswer sa5L(" ");
	
	LongAnswer la1L(" ");
	LongAnswer la2L(" ");
	LongAnswer la3L(" ");
	LongAnswer la4L(" ");
	LongAnswer la5L(" ");					

//for financial

	MCQ m1F("Which OOP principle emphasizes reusability and building relationships between classes? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m2F("What does OOP stand for? ", {"A) Object-Oriented Programming", "B) Object-Oriented Protocol", "C) Object-Oriented Processing", "D)  Object-Oriented Procedure"});
	MCQ m3F("In OOP, which concept allows a class to have multiple methods with the same name but different parameters? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m4F("Which OOP concept allows a class to inherit properties and behavior from another class? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m5F("Which OOP principle focuses on bundling data and methods that work on the data into a single unit? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	
	TrueFalse tf1F(" ");
	TrueFalse tf2F(" ");
	TrueFalse tf3F(" ");
	TrueFalse tf4F(" ");
	TrueFalse tf5F(" ");
	
	ShortAnswer sa1F(" ");
	ShortAnswer sa2F(" ");
	ShortAnswer sa3F(" ");
	ShortAnswer sa4F(" ");
	ShortAnswer sa5F(" ");
	
	LongAnswer la1F(" ");
	LongAnswer la2F(" ");
	LongAnswer la3F(" ");
	LongAnswer la4F(" ");
	LongAnswer la5F(" ");					
				

//for for calculus

	MCQ m1C("Which OOP principle emphasizes reusability and building relationships between classes? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m2C("What does OOP stand for? ", {"A) Object-Oriented Programming", "B) Object-Oriented Protocol", "C) Object-Oriented Processing", "D)  Object-Oriented Procedure"});
	MCQ m3C("In OOP, which concept allows a class to have multiple methods with the same name but different parameters? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m4C("Which OOP concept allows a class to inherit properties and behavior from another class? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m5C("Which OOP principle focuses on bundling data and methods that work on the data into a single unit? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	
	TrueFalse tf1C(" ");
	TrueFalse tf2C(" ");
	TrueFalse tf3C(" ");
	TrueFalse tf4C(" ");
	TrueFalse tf5C(" ");
	
	ShortAnswer sa1C(" ");
	ShortAnswer sa2C(" ");
	ShortAnswer sa3C(" ");
	ShortAnswer sa4C(" ");
	ShortAnswer sa5C(" ");
	
	LongAnswer la1C(" ");
	LongAnswer la2C(" ");
	LongAnswer la3C(" ");
	LongAnswer la4C(" ");
	LongAnswer la5C(" ");					
			

//for software

	MCQ m1S("Which OOP principle emphasizes reusability and building relationships between classes? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m2S("What does OOP stand for? ", {"A) Object-Oriented Programming", "B) Object-Oriented Protocol", "C) Object-Oriented Processing", "D)  Object-Oriented Procedure"});
	MCQ m3S("In OOP, which concept allows a class to have multiple methods with the same name but different parameters? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m4S("Which OOP concept allows a class to inherit properties and behavior from another class? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	MCQ m5S("Which OOP principle focuses on bundling data and methods that work on the data into a single unit? ", {"A) Encapsulation", "B) Inheritance", "C) Polymorphism", "D) Abstraction"});
	
	TrueFalse tf1S(" ");
	TrueFalse tf2S(" ");
	TrueFalse tf3S(" ");
	TrueFalse tf4S(" ");
	TrueFalse tf5S(" ");
	
	ShortAnswer sa1S(" ");
	ShortAnswer sa2S(" ");
	ShortAnswer sa3S(" ");
	ShortAnswer sa4S(" ");
	ShortAnswer sa5S(" ");
	
	LongAnswer la1S(" ");
	LongAnswer la2S(" ");
	LongAnswer la3S(" ");
	LongAnswer la4S(" ");
	LongAnswer la5S(" ");					

    // Main program logic
    int choice;
    cout << "Welcome to the Exam Management System!" << endl;
    cout << "Are you a Teacher or a Student?" << endl;
    cout << "1. Teacher\n2. Student" << endl;
    cin >> choice;
    if (choice == 1) {
        displayMenuTeacher(); // Display teacher menu
    } else if (choice == 2) {
        displayMenuStudent(); // Display student menu
    } else {
        cout << "Invalid choice. Exiting program." << endl;
        return 1; // Exiting with error status
    }
    return 0; // Exiting with success status
}

void displayMenuTeacher() {
    // Display menu options for Teacher
    cout << "Teacher Menu:" << endl;
    cout << "1. Enter Teacher Information" << endl;
    cout << "2. Display Teacher Information" << endl;
    cout << "3. Display Questions" << endl;
    cout << "4. Make Paper" << endl;
    cout << "5. Check Paper" << endl;
    cout << "6. Back to Menu" << endl;

    int choice;
    cout<<"Enter what you want to do ?(1-6) ";
    cin >> choice;
    
    switch (choice){
    	case 1: {//enter teacher info
    		t.inputTeacherInfo();
            ofstream out("teacher.txt", ios::app);
            if (out) {
                t.writeToFile(out);
            } else {
                cerr << "Error opening teacher.txt for writing" << endl;
            }
            out.close();
			break;
		}
		
		case 2: {//display teacher info
	        vector<Teacher> teachers = Teacher::readFromFile("teacher.txt");
            for (const auto& teacher : teachers) {
                teacher.displayTeacher();
            }
			break;
		}
		
		case 3: {//display questions
			int sub;
			cout<<"Which exam paper you want to display :" <<endl ;
			cout<<"1- OOP " <<endl;
			cout<<"2- Linear Algebra " <<endl;
			cout<<"3- Financial Accounting " <<endl;
			cout<<"4- Calculus " <<endl;
			cout<<"5- Software Engineering Concepts " <<endl;
			cin>>sub;
		
			switch(sub){
				case 1:{//display oop
					m1.display();
					m2.display();
					m3.display();
					m4.display();
					m5.display();
					
					tf1.display();
					tf2.display();
					tf3.display();
					tf4.display();
					tf5.display();
					
					sa1.display();
					sa2.display();
					sa3.display();
					sa4.display();
					sa5.display();
					
					la1.display();
					la2.display();
					la3.display();
					la4.display();
					la5.display();
					
					break;
				}
				case 2:{//display linear
					m1L.display();
					m2L.display();
					m3L.display();
					m4L.display();
					m5L.display();
					
					tf1L.display();
					tf2L.display();
					tf3L.display();
					tf4L.display();
					tf5L.display();
					
					sa1L.display();
					sa2L.display();
					sa3L.display();
					sa4L.display();
					sa5L.display();
					
					la1L.display();
					la2L.display();
					la3L.display();
					la4L.display();
					la5L.display();
					break;
				}
				
				case 3:{//display financial
					m1F.display();
					m2F.display();
					m3F.display();
					m4F.display();
					m5F.display();
					
					tf1F.display();
					tf2F.display();
					tf3F.display();
					tf4F.display();
					tf5F.display();
					
					sa1F.display();
					sa2F.display();
					sa3F.display();
					sa4F.display();
					sa5F.display();
					
					la1F.display();
					la2F.display();
					la3F.display();
					la4F.display();
					la5F.display();
					break;
				}
				
				case 4:{//display calculus
					m1C.display();
					m2C.display();
					m3C.display();
					m4C.display();
					m5C.display();
					
					tf1C.display();
					tf2C.display();
					tf3C.display();
					tf4C.display();
					tf5C.display();
					
					sa1C.display();
					sa2C.display();
					sa3C.display();
					sa4C.display();
					sa5C.display();
					
					la1C.display();
					la2C.display();
					la3C.display();
					la4C.display();
					la5C.display();
					break;
				}
				
				case 5:{//display software
					m1S.display();
					m2S.display();
					m3S.display();
					m4S.display();
					m5S.display();
					
					tf1S.display();
					tf2S.display();
					tf3S.display();
					tf4S.display();
					tf5S.display();
					
					sa1S.display();
					sa2S.display();
					sa3S.display();
					sa4S.display();
					sa5S.display();
					
					la1S.display();
					la2S.display();
					la3S.display();
					la4S.display();
					la5S.display();
					break;
				}
			}//switch terminate
		}//case terminate
		case 4: {//make paper
			cout<<"Which subject paper you want to make? " endl;
			cout<<"1- OOP " <<endl;
			cout<<"2- Linear Algebra " <<endl;
			cout<<"3- Financial Accounting " <<endl;
			cout<<"4- Calculus " <<endl;
			cout<<"5- Software Engineering Concepts " <<endl;
			cin>>sub;
			switch(sub){
				case 1:{//make oop
					while(true){
					
						cout<<"Multiple Choice Questions "<<endl;
						m1.display();
						m2.display();
						m3.display();
						m4.display();
						m5.display();
						
						string x;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>x;
						
						Paper p;
						if(x=="1"){
							p.addMCQ(m1);
						}
						
						else if(x=="2"){
							p.addMCQ(m2);
						}
						
						else if(x=="3"){
							p.addMCQ(m3);
						}
						else if(x=="4"){
							p.addMCQ(m4);
						}
						else if(x=="5"){
							p.addMCQ(m5);
						}
						else if(x=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
						
						cout<<"True False Questions "<<endl;
						tf1.display();
						tf2.display();
						tf3.display();
						tf4.display();
						tf5.display();
						
						string y;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>y;
						
						Paper p;
						if(y=="1"){
							p.addTrueFalse(tf1);
						}
						
						else if(y=="2"){
							p.addTrueFalse(tf2);
						}
						
						else if(y=="3"){
							p.addTrueFalse(tf3);
						}
						else if(y=="4"){
							p.addTrueFalse(tf4);
						}
						else if(y=="5"){
							p.addTrueFalse(tf5);
						}
						else if(y=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
					
						cout<<"Short Questions "<<endl;
						sa1.display();
						sa2.display();
						sa3.display();
						sa4.display();
						sa5.display();
						
						string z;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>z;
						
						Paper p;
						if(z=="1"){
							p.addShortAnswer(sa1);
						}
						
						else if(z=="2"){
							p.addShortAnswer(sa2);
						}
						
						else if(z=="3"){
							p.addShortAnswer(sa3);
						}
						else if(z=="4"){
							p.addShortAnswer(sa4);
						}
						else if(z=="5"){
							p.addShortAnswer(sa5);
						}
						else if(z=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					while(true){
					
						cout<<"Long Questions "<<endl;
						la1.display();
						la2.display();
						la3.display();
						la4.display();
						la5.display();
						
						string a;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>a;
						
						Paper p;
						if(a=="1"){
							p.addLongAnswer(la1);
						}
						
						else if(a=="2"){
							p.addLongAnswer(la2);
						}
						
						else if(a=="3"){
							p.addLongAnswer(la3);
						}
						else if(a=="4"){
							p.addLongAnswer(la4);
						}
						else if(a=="5"){
							p.addLongAnswer(la5)
						}
						else if(a=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
				}
					
				case 2:{//make linear
					while(true){
					
						cout<<"Multiple Choice Questions "<<endl;
						m1L.display();
						m2L.display();
						m3L.display();
						m4L.display();
						m5L.display();
						
						string x;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>x;
						
						Paper p;
						if(x=="1"){
							p.addMCQ(m1L);
						}
						
						else if(x=="2"){
							p.addMCQ(m2L);
						}
						
						else if(x=="3"){
							p.addMCQ(m3L);
						}
						else if(x=="4"){
							p.addMCQ(m4L);
						}
						else if(x=="5"){
							p.addMCQ(m5L);
						}
						else if(x=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
						
						cout<<"True False Questions "<<endl;
						tf1L.display();
						tf2L.display();
						tf3L.display();
						tf4L.display();
						tf5L.display();
						
						string y;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>y;
						
						Paper p;
						if(y=="1"){
							p.addTrueFalse(tf1L);
						}
						
						else if(y=="2"){
							p.addTrueFalse(tf2L);
						}
						
						else if(y=="3"){
							p.addTrueFalse(tf3L);
						}
						else if(y=="4"){
							p.addTrueFalse(tf4L);
						}
						else if(y=="5"){
							p.addTrueFalse(tf5L);
						}
						else if(y=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
					
						cout<<"Short Questions "<<endl;
						sa1L.display();
						sa2L.display();
						sa3L.display();
						sa4L.display();
						sa5L.display();
						
						string z;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>z;
						
						Paper p;
						if(z=="1"){
							p.addShortAnswer(sa1L);
						}
						
						else if(z=="2"){
							p.addShortAnswer(sa2L);
						}
						
						else if(z=="3"){
							p.addShortAnswer(sa3L);
						}
						else if(z=="4"){
							p.addShortAnswer(sa4L);
						}
						else if(z=="5"){
							p.addShortAnswer(sa5L);
						}
						else if(z=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					while(true){
					
						cout<<"Long Questions "<<endl;
						la1L.display();
						la2L.display();
						la3L.display();
						la4L.display();
						la5L.display();
						
						string a;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>a;
						
						Paper p;
						if(a=="1"){
							p.addLongAnswer(la1L);
						}
						
						else if(a=="2"){
							p.addLongAnswer(la2L);
						}
						
						else if(a=="3"){
							p.addLongAnswer(la3L);
						}
						else if(a=="4"){
							p.addLongAnswer(la4L);
						}
						else if(a=="5"){
							p.addLongAnswer(la5L)
						}
						else if(a=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					break;
				}
				
				case 3:{//make financial
					while(true){
					
						cout<<"Multiple Choice Questions "<<endl;
						m1F.display();
						m2F.display();
						m3F.display();
						m4F.display();
						m5F.display();
						
						string x;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>x;
						
						Paper p;
						if(x=="1"){
							p.addMCQ(m1F);
						}
						
						else if(x=="2"){
							p.addMCQ(m2F);
						}
						
						else if(x=="3"){
							p.addMCQ(m3F);
						}
						else if(x=="4"){
							p.addMCQ(m4F);
						}
						else if(x=="5"){
							p.addMCQ(m5F);
						}
						else if(x=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
						
						cout<<"True False Questions "<<endl;
						tf1F.display();
						tf2F.display();
						tf3F.display();
						tf4F.display();
						tf5F.display();
						
						string y;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>y;
						
						Paper p;
						if(y=="1"){
							p.addTrueFalse(tf1F);
						}
						
						else if(y=="2"){
							p.addTrueFalse(tf2F);
						}
						
						else if(y=="3"){
							p.addTrueFalse(tf3F);
						}
						else if(y=="4"){
							p.addTrueFalse(tf4F);
						}
						else if(y=="5"){
							p.addTrueFalse(tf5F);
						}
						else if(y=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
					
						cout<<"Short Questions "<<endl;
						sa1F.display();
						sa2F.display();
						sa3F.display();
						sa4F.display();
						sa5F.display();
						
						string z;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>z;
						
						Paper p;
						if(z=="1"){
							p.addShortAnswer(sa1F);
						}
						
						else if(z=="2"){
							p.addShortAnswer(sa2F);
						}
						
						else if(z=="3"){
							p.addShortAnswer(sa3F);
						}
						else if(z=="4"){
							p.addShortAnswer(sa4F);
						}
						else if(z=="5"){
							p.addShortAnswer(sa5F);
						}
						else if(z=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					while(true){
					
						cout<<"Long Questions "<<endl;
						la1F.display();
						la2F.display();
						la3F.display();
						la4F.display();
						la5F.display();
						
						string a;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>a;
						
						Paper p;
						if(a=="1"){
							p.addLongAnswer(la1F);
						}
						
						else if(a=="2"){
							p.addLongAnswer(la2F);
						}
						
						else if(a=="3"){
							p.addLongAnswer(la3F);
						}
						else if(a=="4"){
							p.addLongAnswer(la4F);
						}
						else if(a=="5"){
							p.addLongAnswer(la5F);
						}
						else if(a=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					break;
				}
					
				case 4:{//make calculus
					while(true){
					
						cout<<"Multiple Choice Questions "<<endl;
						m1C.display();
						m2C.display();
						m3C.display();
						m4C.display();
						m5C.display();
						
						string x;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>x;
						
						Paper p;
						if(x=="1"){
							p.addMCQ(m1C);
						}
						
						else if(x=="2"){
							p.addMCQ(m2C);
						}
						
						else if(x=="3"){
							p.addMCQ(m3C);
						}
						else if(x=="4"){
							p.addMCQ(m4C);
						}
						else if(x=="5"){
							p.addMCQ(m5C);
						}
						else if(x=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
						
						cout<<"True False Questions "<<endl;
						tf1C.display();
						tf2C.display();
						tf3C.display();
						tf4C.display();
						tf5C.display();
						
						string y;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>y;
						
						Paper p;
						if(y=="1"){
							p.addTrueFalse(tf1C);
						}
						
						else if(y=="2"){
							p.addTrueFalse(tf2C);
						}
						
						else if(y=="3"){
							p.addTrueFalse(tf3C);
						}
						else if(y=="4"){
							p.addTrueFalse(tf4C);
						}
						else if(y=="5"){
							p.addTrueFalse(tf5C);
						}
						else if(y=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
					
						cout<<"Short Questions "<<endl;
						sa1C.display();
						sa2C.display();
						sa3C.display();
						sa4C.display();
						sa5C.display();
						
						string z;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>z;
						
						Paper p;
						if(z=="1"){
							p.addShortAnswer(sa1C);
						}
						
						else if(z=="2"){
							p.addShortAnswer(sa2C);
						}
						
						else if(z=="3"){
							p.addShortAnswer(sa3C);
						}
						else if(z=="4"){
							p.addShortAnswer(sa4C);
						}
						else if(z=="5"){
							p.addShortAnswer(sa5C);
						}
						else if(z=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					while(true){
					
						cout<<"Long Questions "<<endl;
						la1C.display();
						la2C.display();
						la3C.display();
						la4C.display();
						la5C.display();
						
						string a;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>a;
						
						Paper p;
						if(a=="1"){
							p.addLongAnswer(la1C);
						}
						
						else if(a=="2"){
							p.addLongAnswer(la2C);
						}
						
						else if(a=="3"){
							p.addLongAnswer(la3C);
						}
						else if(a=="4"){
							p.addLongAnswer(la4C);
						}
						else if(a=="5"){
							p.addLongAnswer(la5C)
						}
						else if(a=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					break;
				}
				 case 5:{//make software
					while(true){
					
						cout<<"Multiple Choice Questions "<<endl;
						m1S.display();
						m2S.display();
						m3S.display();
						m4S.display();
						m5S.display();
						
						string x;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>x;
						
						Paper p;
						if(x=="1"){
							p.addMCQ(m1S);
						}
						
						else if(x=="2"){
							p.addMCQ(m2S);
						}
						
						else if(x=="3"){
							p.addMCQ(m3S);
						}
						else if(x=="4"){
							p.addMCQ(m4S);
						}
						else if(x=="5"){
							p.addMCQ(m5S);
						}
						else if(x=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
						
						cout<<"True False Questions "<<endl;
						tf1S.display();
						tf2S.display();
						tf3S.display();
						tf4S.display();
						tf5S.display();
						
						string y;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>y;
						
						Paper p;
						if(y=="1"){
							p.addTrueFalse(tf1S);
						}
						
						else if(y=="2"){
							p.addTrueFalse(tf2S);
						}
						
						else if(y=="3"){
							p.addTrueFalse(tf3S);
						}
						else if(y=="4"){
							p.addTrueFalse(tf4S);
						}
						else if(y=="5"){
							p.addTrueFalse(tf5S);
						}
						else if(y=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					while(true){
					
						cout<<"Short Questions "<<endl;
						sa1S.display();
						sa2S.display();
						sa3S.display();
						sa4S.display();
						sa5S.display();
						
						string z;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>z;
						
						Paper p;
						if(z=="1"){
							p.addShortAnswer(sa1S);
						}
						
						else if(z=="2"){
							p.addShortAnswer(sa2S);
						}
						
						else if(z=="3"){
							p.addShortAnswer(sa3S);
						}
						else if(z=="4"){
							p.addShortAnswer(sa4S);
						}
						else if(z=="5"){
							p.addShortAnswer(sa5S);
						}
						else if(z=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}
					
					while(true){
					
						cout<<"Long Questions "<<endl;
						la1S.display();
						la2S.display();
						la3S.display();
						la4S.display();
						la5S.display();
						
						string a;
						cout<<"Which mcq you want to make part of paper or done to exit"<<endl
						cin>>a;
						
						Paper p;
						if(a=="1"){
							p.addLongAnswer(la1S);
						}
						
						else if(a=="2"){
							p.addLongAnswer(la2S);
						}
						
						else if(a=="3"){
							p.addLongAnswer(la3S);
						}
						else if(a=="4"){
							p.addLongAnswer(la4S);
						}
						else if(a=="5"){
							p.addLongAnswer(la5S)
						}
						else if(a=="done"){
							break;
						}
						else{
							cout<<"Choose between 1-5 " <<endl;
						}
					}				 	
					break;
				}
									
			}//switch terminate
		}//case 4 terminate
		
		case 5:{//check paper
		
		
			break;
		}			
						
					
}
	}
    // Implement the functionality for each option


void displayMenuStudent() {
    // Display menu options for Student
    cout << "Student Menu:" << endl;
    cout << "1. Input Information" << endl;
    cout << "2. Display Information" << endl;
    cout << "3. Take Exam" << endl;
    cout << "4. Display Scores with Student Name" << endl;
    cout << "5. Back to Menu" << endl;

    int choice;
    cin >> choice;
    // Implement the functionality for each option
}