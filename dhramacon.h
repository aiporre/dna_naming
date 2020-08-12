//
// Created by Ariel on 11.08.2020.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <dirent.h>
#define HEIGHT 14
#define WIDTH  24

#ifndef DNA_NAMING_DHRAMACON_H
    #define DNA_NAMING_DHRAMACON_H
#endif //DNA_NAMING_DHRAMACON_H



using namespace std;
typedef vector< vector<string> > csvVector;

string encodedFileName(std::string const & filename);

float s2f(string const & floatstring);

void averageSubTables(csvVector &input, csvVector &output);

void averageSubTables(csvVector &input, csvVector &output);

void readCSV(istream &input, csvVector &output, char const & delim);

int processFile(string const & dirname, string const & filename);

string encodedFileName(std::string const & filename);

inline bool ends_with(std::string const & value, std::string const & ending);

int processFolder(string const & dirname);

void decodePosition(string const & filename, string & dnaCode, string & concentration);

int** getTable();

void printTable(int** const & table);

float s2f(string const & floatstring){
    std::string::size_type sz;     // alias of size_t
    float conv =  std::stof (floatstring,&sz);
    return conv;
}
void averageSubTables(csvVector &input, csvVector &output){
    string a;
    float meanIntensityGPF = 0, meanIntensityCy3=0, dapiArea=0;

    int zRowCounter = 0; // zero row counter
    int nzRowCounter = 0; // non zero row counter
    string filename;
    bool skipFirst = true;
    vector<string> header;
    header.push_back("% Input File Name");
    header.push_back("% MeanInt GPF");
    header.push_back("% MeanInt Cy3");
    header.push_back("% DAPI Area");
    header.push_back("% concentration");
    header.push_back("% DNA code");
    output.push_back(header);
    for(csvVector::iterator i = input.begin(); i != input.end(); ++i)
    {
        if (skipFirst){
            skipFirst = false;
            continue;
        }
        if (i->size()>0){
            float valueIntesityGPF = s2f(i->at(2));
            float valueIntensityCy3 = s2f(i->at(3));
            float valueDapiArea = s2f(i->at(4));
            if (isnan(valueIntesityGPF) or isnan(valueIntensityCy3) or  isnan(valueDapiArea))
                continue;
            meanIntensityGPF += valueIntesityGPF;
            meanIntensityCy3 += valueIntensityCy3;
            dapiArea += valueDapiArea;
            filename  = i->at(0);
            nzRowCounter++;
        } else {
            if (zRowCounter>1){ // finds two or more consequetive row to close sub-table accumulation
                // append averaged values to row
                vector<string> csvColumn;
                csvColumn.push_back(filename);
                csvColumn.push_back( to_string(meanIntensityGPF/nzRowCounter));
                csvColumn.push_back(to_string(meanIntensityCy3/nzRowCounter));
                csvColumn.push_back(to_string(dapiArea/nzRowCounter));
                string concentration;
                string dnaCode;
                decodePosition(filename, concentration, dnaCode);
                csvColumn.push_back(concentration);
                csvColumn.push_back(dnaCode);
                // append new row to table
                output.push_back(csvColumn);
                // reset row counters and accumulatior
                zRowCounter = 0;
                nzRowCounter = 0;
                meanIntensityGPF = 0, meanIntensityCy3=0, dapiArea=0;
            } else{
                zRowCounter ++;
            }
        }
    }
}

void readCSV(istream &input, csvVector &output, char const & delim)
{
    string csvLine;
    // read every line from the stream
    while( getline(input, csvLine) )
    {
        istringstream csvStream(csvLine);
        vector<string> csvColumn;
        string csvElement;
        // read every element from the line that is seperated by commas
        // and put it into the vector or strings
        while( getline(csvStream, csvElement, delim) )
        {
            csvColumn.push_back(csvElement);
        }
        output.push_back(csvColumn);
    }
}

int processFile(string const & dirname, string const & filename){
    // get table of concetration/gene/slot for filename column conversion
    // int** table = getTable();
    // printTable(table);

    ofstream myfile; // Output file
    string a;
    fstream file( dirname + "/" + filename, ios::in); // Input file
    myfile.open (dirname + "/" + encodedFileName(filename)); // create file
    if(!file.is_open())
    {
        cout << "File not found!\n";
        return 1;
    }
    // typedef to save typing for the following object

    csvVector csvData;
    csvVector csvAvgData;

    readCSV(file, csvData, '\t');
    averageSubTables(csvData, csvAvgData);


    // print out read data to prove reading worked
    float progress = 0.0;
    int barWidth = 70;
    float processed_lines = 0.0;
    int total_lines = csvAvgData.size();
    for(csvVector::iterator i = csvAvgData.begin(); i != csvAvgData.end(); ++i)
    {
        std::cout << "[";
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "=";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << filename << " (" <<int(progress * 100.0) << "%) \r";
        std::cout.flush();

        for(vector<string>::iterator j = i->begin(); j != i->end(); ++j)
        {
            a=*j;
            myfile <<a<<",";
        }
        myfile <<"\n";
        processed_lines +=1.0;
        progress = processed_lines/((float) total_lines);
    }
    myfile.close();
    return 0;
}


string encodedFileName(std::string const & filename) {
    std::string token = filename.substr(0, filename.find("."));
    return token + "-proc.csv";
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int processFolder(string const & dirname){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(dirname.c_str())) != nullptr) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != nullptr) {
            string filename = ent->d_name;
            if(ends_with(filename, ".csv") and not ends_with(filename, "-proc.csv")){
                cout << "processing file: " << filename << "... " << endl;
                processFile(dirname, filename);
            }
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        cout << "Directory not found!\n";
        return 1;
    }
    return 0;
}


void decodePosition(string const & filename, string & dnaCode, string & concentration) {
    try{
        string code = filename.substr(filename.find("_")+1, filename.find("--") - filename.find("_")-1);
        int abscissa = static_cast<unsigned char>( code[0] );
        abscissa -=65;
        string aaa = code.substr(1, code.size() - 1);
        int ordinate = std::stoi(aaa)-1;
        int** layout = getTable();
        int codeLayout = layout[abscissa][ordinate]; //layout[abscissa][ordinate];
        int bbb = codeLayout / 100;
        dnaCode = std::to_string(bbb);
        int ccc = codeLayout % 100;
        concentration = std::to_string(ccc);

    } catch (const std::exception &exc) {
        // catch anything thrown within try block that derives from std::exception
        concentration = "NAN";
        dnaCode = "NAN";
        std::cerr << "Exception occured during generation of code from filename OCCURRED : "<<  exc.what() << endl;
    } catch(...){
        concentration = "NAN";
        dnaCode = "NAN";
        std::cerr << "exception during generation of code from filename " << endl;
    }
}


int** getTable() {
    int** dharmaconTable = 0;

    dharmaconTable = new int*[HEIGHT];

    int cellCount = 1;
    int densities[3] = {3000, 1000, 300}, *d;
    d = densities;

    // init table with zeros
    for (int h = 0; h < HEIGHT; h++){
        dharmaconTable[h] = new int[WIDTH];
        for(int w = 0; w < WIDTH; w++)
            dharmaconTable[h][w] = 0;
    }

    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
            if (cellCount < 23) {
                if (h > 1 and h % 2 == 0) {
                    if (w > 1 and w % 2 == 0) {
                        dharmaconTable[h][w] = cellCount + *d;
                        dharmaconTable[h + 1][w] = cellCount + *d;
                        dharmaconTable[h][w + 1] = cellCount + *d;
                        cellCount++;
                    }
                }
            } else {
                cellCount = 1;
                d++;
            }
        }
    }

    return dharmaconTable;
}


void printTable(int** const & table){
    for (int i=0; i<HEIGHT; i++){
        for (int j=0; j<WIDTH; j++)
            std::cout << table[i][j] << "\t";
        std::cout <<";\n";
    }

}
