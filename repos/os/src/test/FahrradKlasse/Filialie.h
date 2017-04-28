using namespace Genode;




class Filiale {

private:

	char const* _Strasse;
	unsigned _Hausnummer;
 	char const* _Ort;
       
	


public:

int x = 0; 
 
	char const* Feliale;


Filiale (char const* ort, char const* feliale, char const* strasse, unsigned hausnummer){
	
	_Ort=ort;
	 Feliale=feliale;
	_Strasse=strasse;
	_Hausnummer=hausnummer;
	
	}

 void fahrrad_herstellung() {
 
 x++;

}



void print(Output &output) const{Genode::print(output, _Ort," ", Feliale,  "   ",    _Strasse, "  ",  _Hausnummer, " ",  x);}





};
