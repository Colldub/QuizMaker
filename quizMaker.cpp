#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int getLength(char* str){
    int i = 0;
    int count = 0;
    while(str[i] != '\0'){
        i++;
        count++;
    }
    return count;
}

int findLoc(char* str,char token){
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == token){
            return i;
        }

    }
    cout << "couldn't find match" << endl;
    return 0;
}

int score(char ** givenAnswers, char** realAnswers, int numQues){
    int score = 0;

    for(int i = 0; i < numQues; i++){
        if(strcmp(givenAnswers[i], realAnswers[i]) == 0){
            score ++;
        }
    }
    return score;
}

char* substring(const char* str, size_t start, size_t end) {
    // Check for invalid positions
    size_t strLength = strlen(str);
    if (start >= strLength || start > end) {
        return nullptr; // Invalid start position or start is greater than end
    }

    // Adjust end if it exceeds the length of the string
    if (end >= strLength) {
        end = strLength - 1;
    }

    // Calculate the length of the substring
    size_t length = end - start + 1;

    // Allocate memory for the substring (+1 for null terminator)
    char* substr = new char[length + 1];

    // Copy the substring
    strncpy(substr, str + start, length);

    // Null-terminate the new string
    substr[length] = '\0';

    return substr;
}

int GiveQuiz(char** questions, int numQues, char** realAnswers){

    //char * givenAnswers = new char[numQues]
    char** givenAnswers = (char**)malloc(numQues * sizeof(char*));
    if(givenAnswers == NULL) {
        fprintf(stderr, "Memory allocation for pointers failed\n");
        return 1;
    }

    // Allocate memory for each string that is attached to the pointers
    for(int i = 0; i < numQues; i++){
        givenAnswers[i] = (char*)malloc(50 * sizeof(char)); // 50 is a temp variable for tests change later

        if(givenAnswers[i] == NULL){ fprintf(stderr, "Memory allocation for string failed at index %d\n", i);
            for (int j = 0; j < i; j++){
                free(givenAnswers[j]);
            }
            free(givenAnswers);
            return 1;
        }
    }


    for(int i = 0; i < numQues; i ++){
        // Print question
        cout << questions[i] << ":" << endl;

        // Recive answer
        cin >> givenAnswers[i];
    }
    int amountCorrect = score(givenAnswers, realAnswers, numQues); 
    cout << "You scored " << amountCorrect << "/" << numQues << endl; 
    
    // Free array
    for(int i = 0; i < numQues; i ++){
        free(givenAnswers[i]);
    }
    free(givenAnswers);

    return 1;
}



int main(int argc, char* argv[]){
    // Args exptectd: file for questions and amount of questions to take
    /*
    if (argc != 2){
        cerr << "Usage: " << argv[0] << endl;
        return 1;
    }
    */
    // temp vars 
    //
    int numQuestions = 10;
    string FILENAME = "questionSet_1.txt";
    char* templine = new char[100];
    int dashPos;
    int stringLen;
    int timesRun = 10;
    //
    ///////

//cout << "opening file" << endl;

    // File reading
    ifstream inputFile(FILENAME);

    // Check that file is open properly
    if (!inputFile){ printf("%s", "Unable to open file");}

    // Create array for questions
    char* questions[numQuestions];
    char* answers[numQuestions];

//cout << "entering while" << endl;

    // Read file line by line
    //while(timesRun != 0){
    for(int i = 0; i < timesRun; i ++){
        inputFile.getline(templine, 100); // 100 as max len right now just so it will run
//cout << "getting line" << endl; 
        // Split line to question and answer
        stringLen = getLength(templine);
        dashPos = findLoc(templine, '-');
//cout << "my funcs" << endl; 
    // Turning my char*'s into strings to make it easier would like to finish with making my own functions

        //string tempstring(templine);
//cout << "setting stuff" << endl;  
        questions[i] = substring(templine, 0, dashPos - 2);
        answers[i] = substring(templine, dashPos + 2, stringLen);
    }

    
    for(int i = 0; i < 10; i ++){
        printf("question: %s, answer: %s\n", questions[i], answers[i]);
    }
    cout <<"Test times run = " <<timesRun<<endl; 

    if(GiveQuiz(questions, timesRun, answers) == 1){
        fprintf(stderr, "Give quiz failed");
    }

    delete[] templine;
    inputFile.close();
    return 0;
}