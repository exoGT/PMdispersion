#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

int main()
{
    ofstream outputRaw("post/rawPositions.txt");
    ifstream dataFlux("U_data/positions");  

    outputRaw << "X-coord Y-coord Z-coord";   

    smatch m;
    regex e ("[+-]?([0-9]*[.])?[0-9]+");

    vector<vector<double>> data;

    if(dataFlux)
    { 
        cout << "Program has detected data \nData will be extracted..." << endl;
        string line;       

        int counter = 0; //for testing purposes only
        int coordCounter = 0;

        while(getline(dataFlux, line)) // set
        {
            if (line.find("(") == 0){
                string str = line;
                coordCounter = 0;  
                data.push_back(vector<double>());

                while (regex_search(str, m, e) && coordCounter < 3) {
                    outputRaw << std::stod(m[0]) << " ";
                    data[counter].push_back(std::stod(m[0]));
                    str = m.suffix();
                    coordCounter++;             
                }   

                outputRaw << endl;
                counter++;             
            }
        }

        data.erase(data.begin());

        cout << endl << "Program has retrieved " << counter << " data points" << endl;
        cout << "Data size: " << data.size() << "x" << data[1].size() << endl;
        cout << endl << "Data preview (row #1): " << data[0][0] << " " << data[0][1] << " " << data[0][2];
    }
    else 
        cout << "ERROR: Unable to open read-mode." << endl;
    
    return 0;
}
