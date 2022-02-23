#include <iostream>
#include <fstream>

using namespace std;

void coordinatesToAscii(const string& figure, bool** array, int maxSize);
void writeAsciiToFile(fstream& file, bool** array, int maxSize);

void coordinatesToASCIIFile(const string& fileName, int maxSize) {
    fstream file;
    file.open(fileName, ios::in);

    fstream fileOutput;
    string fileOutputName = fileName.substr(0, fileName.find_first_of('.'))+"_ASCII.txt";
    fileOutput.open(fileOutputName, ios::out);

    string figure;
    bool** arrayASCII = new bool* [maxSize];
    for(int i = 0; i < maxSize; i++)
        arrayASCII[i] = new bool [maxSize];

    while(getline(file, figure)) {
        cout << "figure: " << figure << endl;
        coordinatesToAscii(figure, arrayASCII, maxSize);
        writeAsciiToFile(fileOutput, arrayASCII, maxSize);
    }

    for(int i = 0; i < maxSize; i++) {
        delete [] arrayASCII[i];
    }
    delete [] arrayASCII;

}

void writeAsciiToFile(fstream& file, bool** array, int maxSize) {
    for(int i = 0; i < maxSize; i++) {
        for(int j = 0; j < maxSize; j++) {
            if(!array[i][j]) file << ".";
            else file << "#";
        }
        file << "\n";
    }
    file << "\n";
    file << "==========================\n";
}

void coordinatesToAscii(const string& figure, bool** array, int maxSize) {
    // clearing array
    for(int i = 0; i < maxSize; i++) {
        for(int j = 0; j < maxSize; j++) {
            array[i][j] = false;
        }
    }


    // iterating over pairs and marking true on the array
    for(int i = 0; i < figure.size(); i++) {
        i++; // to skip (
        int beginIndex = i;
        while(figure.at(i) != ',') {
            i++;
        }
        // figure.at(i) == ','

        int row = stoi(figure.substr(beginIndex, i-beginIndex));
        cout << "row: " << row << endl;

        beginIndex = ++i;
        while(figure.at(i) != ')') {
            i++;
        }
        int column = stoi(figure.substr(beginIndex, i-beginIndex));
        cout << "column: " << column << endl << endl;

        array[row][column] = true;
        i++; // moving on "space"
        // i++ for "(" automatically in for loop)
    }
}

/// from ASCII to coordinates
void asciiToCoordinatesFile(const string& fileName) {
    fstream file;
    file.open(fileName, ios::in);

    fstream fileOutput;
    string fileOutputName = fileName.substr(0, fileName.find_first_of('.'))+"_Coordinates.txt";
    fileOutput.open(fileOutputName, ios::out);

    string line;
    int row = 0;
    bool firstAppearance = true;
    bool newLineBeginning = false;
    while(getline(file, line)) {
        cout << line << endl;
        if(line.length() > 0) {
            if (line.at(0) == '#' || line.at(0) == '.' || line.at(0) == ' ') {
                for (int i = 0; i < line.length(); i++) {
                    if (line.at(i) == '#') {
                        if(newLineBeginning) {
                            fileOutput << endl;
                            newLineBeginning = false;
                        }
                        if (!firstAppearance) {
                            fileOutput << " (" << row << "," << i << ")";
                        } else {
                            fileOutput << "(" << row << "," << i << ")";
                            firstAppearance = false;
                        }
                    }
                }
                row++;
            }
        } else {
            newLineBeginning = true;
            row = 0;
            firstAppearance = true;
        }
    }
}



int main(int argc, char *argv[]) {
    // mode == toASCII
    // mode == toNumbers

    if(argc == 1) {
        cout << "Please provide mode parameter. Type -help for help." << endl;
        exit(3);
    }

    string mode = argv[1];

    if(mode == "toASCII") {
        string fileName = argv[2];
        int maxSize = stoi(argv[3]);
        coordinatesToASCIIFile(fileName, maxSize);
    } else if (mode == "toNumbers") {
        string fileName = argv[2];
        asciiToCoordinatesFile(fileName);
    } else {
        cout << "Incorrect mode." << endl;
        cout << "Run examples: "<< endl;
        cout << "inputConverter {toASCII, toNumbers} [fileName] (max coordinate - only in toASCII mode)" << endl;
        cout << "./inputConverter.exe toASCII file.txt 10" << endl;
        cout << "./inputConverter.exe toNumbers file.txt" << endl;
    }

    return 0;
}
