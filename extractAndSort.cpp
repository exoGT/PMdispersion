#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

bool isValid(double value, int coord, float off, float dep, int norm){
    if (coord == norm){
        if (value >= off - dep && value <= off + dep){
            return true;
        }
        else {return false;}
    }
    else {return true;} 
}

string writeOutput(bool valid, string input){
    // if (valid == true) {
    //     return input + "\n";
    // }
    // else {return "";}
    return input;
}

int main()
{
    ofstream output("post/positions.txt");
    ifstream dataFlux("U_data/positions");
    
    output << "x-coord y-coord z-coord";

    smatch m;
    regex e ("[+-]?([0-9]*[.])?[0-9]+");

    if(dataFlux)
    { 
        string line;
        string tempLine;
        
        float offset = 0.026; // relative to X,Y or Z = 0
        float depth = 0.00001; // thickness of the clip
        int normal = 1; // 1 = X, 2 = Y, 3 =Z 

        int counter = 0; //for testing purposes only
        int limit = 1000;
        int coordCounter = 0;

        bool state;

        while(getline(dataFlux, line) && counter < limit) // set
        {
            if (line.find("(") == 0){
                // Enter that loop if line starts with an open parenthesis
                string str = line;

                tempLine == "";
                state = true;
                coordCounter = 0;
                
                while (regex_search(str, m, e) && coordCounter < 3) {                   
                    state = isValid(std::stod(m[0]), coordCounter, offset, depth, normal); 
                                      
                    if (state) {  
                        cout << "here"; 
                        tempLine += m[0];
                        tempLine += " ";                  
                    }
                    else {break;}

                    str = m.suffix();
                    coordCounter++;             
                }
                cout << writeOutput(state, tempLine) << endl;
            }
            counter++;
        }
        
    }
    else 
        cout << "ERROR: Unable to open read-mode." << endl;
    
    return 0;
}
