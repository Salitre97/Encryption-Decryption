#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool encrypt = false;
bool decrypt = false;

int Max_Upper = int('Z');
int Min_Upper = int('A');
int max_lower = int('z');
int min_lower = int('a');
int char_total = 26;


int encryptFile(string inputFile, string outputFile, int key);
int decryptFile(string inputFile, string outputFile, int key);


int main(int argc, char* argv[]){
    int key;   
    bool input = false;
    bool output = false;
    bool keyExists = false;
    string inputFile;
    string outputFile;
    string text;
    ifstream iFile;
    ofstream oFile;
    
    for(int i = 0; i < argc; i++){
        if(argv[i][0] == '-'){
            if(argv[i][1] == 'e'){
                encrypt = true;
                cout << "encrypt" << endl;
            }
            else if(argv[i][1] == 'd'){
                decrypt = true;
                cout << "decrypt" << endl;
            }
             if(argv[i][1] == 'k'){
                 int j = i;
                 while(!isdigit(argv[i][j])){
                     j++;
                 }
               key = stoi(argv[j]);
                if(key > 26){
                    key = key % 26;
                }
                keyExists = true;
                cout << "Key: " << key << endl;
            }
            else if(argv[i][1] == 'i'){
                inputFile = argv[i+1];
                input = true;
                cout << inputFile << endl;
            }
            else if(argv[i][1] == 'o'){
                outputFile = argv[i+1];
                output = true;
                cout << outputFile << endl;
            }
            
        }
    }
    if(!keyExists || !output || !input){
        cout << "Missing command parameters" << endl;
        return 0;
    }
    if(encrypt){
            encryptFile(inputFile, outputFile, key);
    }
    if(decrypt){
        decryptFile(inputFile, outputFile, key);
    }
    

    return 0;
}

int encryptFile(string inputFile, string outputFile, int key){
    ifstream iFile;
    iFile.open(inputFile);
    
    if(!iFile.is_open()){
        cout << "Error: " << inputFile << " not open." << endl;
        return 1;
    }
    
    ofstream oFile;
    oFile.open(outputFile);
    
    if(!oFile.is_open()){
        cout << "Error: " << outputFile << " not open." << endl;
        return 1;
    }
    
    string text;
    while(getline(iFile, text)){
        for(int i = 0; i < text.length(); i++){
            if(isalpha(text[i])){
                if(isupper(text[i]) && (int(text[i]) + key) > Max_Upper){
                    text[i] = char(((int(text[i]) + key - Min_Upper) % char_total) + Min_Upper);
                } else if (islower(text[i]) && int(text[i]) + key > max_lower){
                    text[i] = char(((int(text[i]) + key - min_lower) % char_total) + min_lower);
                } else{
                    text[i] = char(int(text[i]) + key); 
                }
            }
        }
    }
    oFile << text << endl;
    
    iFile.close();
    oFile.close();
}

int decryptFile(string inputFile, string outputFile, int key){
    ifstream iFile;
    iFile.open(inputFile);
    
    if(!iFile.is_open()){
        cout << "Error: " << inputFile << "not open." << endl;
        return 1;
    }
    
    ofstream oFile;
    oFile.open(outputFile);
    
    if(!oFile.is_open()){
        cout << "Error: " << outputFile << "not open." << endl;
        return 1;
    }
    
    string text;
    while(getline(iFile, text)){
        for(int i = 0; i < text.length(); i++){
            if(isalpha(text[i])){
                if(isupper(text[i]) && (int(text[i]) - key) < Min_Upper){
                    text[i] = char(((int(text[i]) - key + Min_Upper) % char_total) + Min_Upper);
                } else if (islower(text[i]) && int(text[i]) - key < min_lower){
                    text[i] = char(((int(text[i]) - key + min_lower) % char_total) + min_lower);
                } else{
                    text[i] = char(int(text[i]) - key);
                }
            
            }
        }
    }
    cout << text;
    oFile << text << endl;
    
    iFile.close();
    oFile.close();
}
