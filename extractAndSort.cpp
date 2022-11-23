#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

int main()
{
    // Flux opening in W/R mode
    ofstream outputRaw("post/rawPositions.txt");
    ofstream outputFiltered("post/filteredPositions.txt");
    ifstream dataFlux("U_data/positions");  

    // Headers in the raw positions file
    outputRaw << "X-coord Y-coord Z-coord";   

    // Parameters for string retrieving 
    smatch m;
    regex e ("[+-]?([0-9]*[.])?[0-9]+");

    // 2D-vectors initialization
    vector<vector<double>> data;
    vector<vector<double>> filteredData;

    // Raw and filtered counters for vector indexing
    int rawCounter = 0; 
    int filteredCounter = 0;

    // If incoming flux is detected
    if(dataFlux)
    { 
        cout << "Program has detected data \nData will be extracted..." << endl;

        string line;       
        int coordCounter = 0;

        // While lines remain in the file
        while(getline(dataFlux, line)) 
        {
            if (line.find("(") == 0){
                string str = line;
                coordCounter = 0;
                
                // If line starts with an open parenthesis, append a vector to data 2D-vector   
                data.push_back(vector<double>());

                while (regex_search(str, m, e) && coordCounter < 3) {
                    // While numeric entries are found and n_coordinates doesn't exceed 3 (X, Y, Z)
                    outputRaw << std::stod(m[0]) << " ";
                    data[rawCounter].push_back(std::stod(m[0]));

                    // Move to next string part and increment n_coordinates
                    str = m.suffix();
                    coordCounter++;             
                }
                outputRaw << endl;
                rawCounter++;             
            }
        }
        // Blank line was added at the beginning of the vector, remove it
        data.erase(data.begin());

        cout << endl << "Program has retrieved " << rawCounter - 1 << " data points" << endl;
        cout << "Data size: " << data.size() << "x" << data[1].size() << endl;
        cout << "Data preview (row #1): " << data[0][0] << " " << data[0][1] << " " << data[0][2] << endl;        

        // Filtering function
        char choice; 

        while(choice != 'N' && choice != 'Y'){
            cout << endl << "Do you want to proceed with spatial filtering? [Y/N] ";
            cin >> choice;
        }

        switch(choice)
        {
            case 'Y':
                cout << "Program will start filtering your data based on your selected settings..." << endl;
                for(int row = 0; row < data.size(); row++){
                    if(data[row][0] < 0.0005 && data[row][0] > 0.00045){                
                        filteredData.push_back(vector<double>());                        
                        for(int col = 0; col < 3; col++){                    
                            filteredData[filteredCounter].push_back(data[row][col]);
                        }                
                        outputFiltered << filteredData[filteredCounter][0] << " " << filteredData[filteredCounter][1] << " " << filteredData[filteredCounter][2] << endl;
                        filteredCounter++;            
                    }
                }
                cout << "Program has successfully filtered " << filteredCounter << " data points.";
                break;

            case 'N':
                cout << "Spatial filtering aborted. Program will terminate.";
        } 

    }                
    
    else{cout << "ERROR: Unable to open read-mode." << endl;}

    return 0;
}
