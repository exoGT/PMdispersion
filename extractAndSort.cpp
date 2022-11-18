#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

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
        
        float offset = 0.02; // relative to X,Y or Z = 0
        float depth = 0.001; // thickness of the clip
        int normal = 1; // 1 = X, 2 = Y, 3 =Z 

        int counter = 0; //for testing purposes only
        int limit = 400000;
        int coordCounter = 0;

        while(getline(dataFlux, line) && counter < limit) // set
        {
            if (line.find("(") == 0){
                string str = line;
                coordCounter = 0;
                
                while (regex_search(str, m, e)) {                   
                    if (coordCounter < 3) {
                        switch (normal)
                        {
                            case 1: // if clip normal to X
                                if (coordCounter == 1 && std::stof(m[0]) >= offset - depth && std::stof(m[0]) <= offset + depth ){
                                    output << m[0] << " ";
                                    break;
                                }
                                else if(coordCounter != 1 || std::stof(m[0]) < offset - depth || std::stof(m[0]) > offset + depth){
                                    break;
                                }
                            case 2: // if clip normal to Y
                                if (coordCounter == 2 && std::stof(m[0]) >= offset - depth && std::stof(m[0]) <= offset + depth ){
                                    output << m[0] << " ";
                                    break;
                                }
                                else if(coordCounter != 2 || std::stof(m[0]) < offset - depth || std::stof(m[0]) > offset + depth){
                                    break;
                                }
                            case 3: // if clip normal to Z
                                if (coordCounter == 3 && std::stof(m[0]) >= offset - depth && std::stof(m[0]) <= offset + depth ){
                                    output << m[0] << " ";
                                    break;
                                }
                                else if(coordCounter != 3 || std::stof(m[0]) < offset - depth || std::stof(m[0]) > offset + depth){
                                    break;
                                }
                        }
                        //cout << std::stof(m[0]) << " ";
                        //output << m[0] << " ";
                    }
                    str = m.suffix();
                    coordCounter++;             
                }
                std::cout << std::endl;
                output << endl;
            }
            counter++;
        }
        
    }
    else 
        cout << "ERROR: Unable to open read-mode." << endl;
    
    return 0;
}
