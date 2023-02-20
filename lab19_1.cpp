#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string text;
    char format[]= "%[^:]: %d %d %d";
    char name[100];
    int s1,s2,s3;


    while(getline(source,text)){
        sscanf(text.c_str(),format,name,&s1,&s2,&s3);
        names.push_back(name);
        scores.push_back(s1+s2+s3);
        grades.push_back(score2grade(s1+s2+s3));
    }
    
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    string text;

    getline(cin,text);
    
    int start=0;
    int pos = text.find_first_of(" ");

    command = text.substr(start,pos);

    
    key = text.substr(pos+1);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";

    for (unsigned int i=0;i<names.size();i++){
        if (toUpperStr(names[i])==key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            break;
        }else if(!(names[i]==key) && i==names.size()-1){
            cout << "Cannot found.\n";        
        }
    }

    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    
    for (unsigned int i=0;i<grades.size();i++){
        if (grades[i] == key[0]) cout << names[i] << " (" << scores[i] << ")\n";   
    }

    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
