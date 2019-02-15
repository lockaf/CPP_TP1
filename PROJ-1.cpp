//
//  PROJ-1.cpp
//  
//
//  Created by Dumont Maxime on 05/02/2019.
//

#include "PROJ-1.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;




bool is_date(int day, int month, int year) {
    bool ret=false;
    if(day < 32 && day>0){
        if(month <13 && month>0){
            if(year>0 && year<2019)
                ret = true;
            else
                ret=false;
        }
        else
            ret=false;
    }
    else
        ret=false;
    return ret;
}

bool parse_date(std::string date_name, int& day, int& month, int& year){
    bool valid = true;

    int slash_1 = date_name.find('/',0);
    int slash_2 = date_name.find('/',slash_1+1);

    std::string day_str = date_name.substr(0,2);
    std::string month_str = date_name.substr(slash_1+1,2);
    std::string year_str = date_name.substr(slash_2+1,4);


    day = stoi(day_str);
    month = stoi(month_str);
    year = stoi(year_str);

    valid = is_date(day, month, year);

    if (slash_1==-1 or slash_2==-1){
        valid = false;
    }

    return valid;
}

int read_story(std::string filename, std::string name, std::string dob){
    ifstream fichier(filename.c_str());  //déclaration du flux et ouverture du fichier
    if(fichier)  // si l'ouverture a réussi
    {
	string texte;
	string ligne;
	while(getline(fichier, ligne)){
		texte+=ligne+"\n";
	}
	fichier.close();  // on referme le fichier
	size_t pos_dob;size_t pos_name;
	while(pos_dob !=string::npos || pos_name != string::npos){
		if(pos_dob !=string::npos && pos_name != string::npos){
			pos_dob = texte.find("$(dob)");
			texte.replace(pos_dob,sizeof("$(dob)")-1,dob);
			pos_name = texte.find("$(name)");
			texte.replace(pos_name,sizeof("$(name)")-1,name);
		}
		if(pos_dob ==string::npos && pos_name != string::npos){
			pos_name = texte.find("$(name)");
			texte.replace(pos_name,sizeof("$(name)")-1,name);
		}
		if(pos_dob !=string::npos && pos_name == string::npos){
			pos_dob = texte.find("$(dob)");
			texte.replace(pos_dob,sizeof("$(dob)"),name);
		}
	pos_dob = texte.find("$(dob)");pos_name = texte.find("$(name)");	
	}

	cout<<texte<<std::endl;   
	return 0;
    }
    else{  // sinon
        std::cerr << "Error 3 : Story "+ filename +" not found" << std::endl;
	return 3;
    }
}

/////////////////////////////////////////////////////////Fonction principale
int main(int argc, char *argv[]) {
      if(argc<4){
        std::cerr << "Error 1 : Running out of arguments" << std::endl;
        return 1;
	}
	int day; int month; int year;bool valid;int ret;
	valid=parse_date(argv[3],day,month,year);
	if(valid){
		ret=read_story(argv[1],argv[2],argv[3]);
	}
	else{
		std::string dob = argv[3];
		std::cerr << "Error 2 : Date "+ dob + " not valid" << std::endl;
		ret=2;
	}
	return ret;

}
