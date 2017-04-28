#include <base/output.h>
#include <base/component.h>
#include <util/string.h>
#include <Filialie.h>
using namespace Genode; 
		
		
class Fahrrad {

public:
	
	enum einsatzgebiet {Wald, Stunts, Stadt};
	enum schaltung {Nabenschaltung, Kettenschaltung, Singlespeed};
			
private:
		
	unsigned _Gaenge;		 
	bool _Gepaecktraeger;
	char const* _Besitzer;
	unsigned _Zeit;
	einsatzgebiet Einsatzgebiet;
	schaltung Schaltung;
	bool _Verfuegbar;
	char const* _Name_Bike;
	char const* _Stunden; 
	Filiale*_filiale;
        

public:

	bool  Ausleihe(char const* besitzer, unsigned zeit){

			if (_Verfuegbar==false){	
			
		
			
 			return false;
			}
			if (_Verfuegbar==true){
			_Besitzer = besitzer;
			_Zeit = zeit;
 			_Verfuegbar = false;
			
                        return true; 
			}
}

         

        void zurueckgegeben()
{
        _Verfuegbar = true; 
        _Besitzer = " ICH ";
        
	log ("Fahrrad ist wieder im Geschaeft");                
}


	void gib_filiale_aus (){


 	log (*_filiale);      


}

Fahrrad (Filiale* filiale, char const* name_bike, unsigned gaenge, bool gepaecktraeger,einsatzgebiet eeinsatzgebiet, schaltung sschaltung)

{

	_filiale=filiale;
	_Gaenge=gaenge;
	_Gepaecktraeger=gepaecktraeger;
	_Besitzer="";
        _Zeit=0;
	Einsatzgebiet=eeinsatzgebiet;
	Schaltung=sschaltung;
	_Verfuegbar=true;
        _Name_Bike=name_bike;
        filiale->fahrrad_herstellung();


}


				

			void print(Output &output) const
			{Genode::print(output, "Fahrrad: ",  _Name_Bike, "Verfuegbarkeit: ", _Verfuegbar ? "ist verfuegbar" : "ist nicht verfuegbar", _Besitzer, " ", _Zeit == 0 ?String<16>(" "):String<16>(_Zeit) , _Zeit == 0 ? " ":" Stunden " , " ", (unsigned)Einsatzgebiet, _Gaenge, " ", (unsigned)Schaltung , " ", _Gepaecktraeger);
			
		}
			
			
};




void Component::construct(Genode::Env &env){

  



	Filiale filiale[2] {

		{ "Dresden", "Richard", "Berliner Straße", 541451 },
		{ "Leipzig","Gunther", "Bahnhogstrasse", 9 }
	};

        Fahrrad fahrraeder [4] {            
	
		{&filiale[0], "Mountainbike", 27, false, Fahrrad::Wald, Fahrrad::Kettenschaltung},
        	{&filiale[1], "Diamant", 8, true, Fahrrad::Stadt, Fahrrad::Nabenschaltung},
        	{&filiale[0], "BMX" , 1, false, Fahrrad::Stunts, Fahrrad::Singlespeed},
		{&filiale[1], "Trekking", 30, true, Fahrrad::Stadt, Fahrrad::Kettenschaltung}  
          
      		};
	
	for (unsigned i=0; i<sizeof(fahrraeder)/sizeof(fahrraeder[0]);i++) {
	

		log (fahrraeder [i]);

	};
	
		fahrraeder[0].Ausleihe (" Guenther Wallraff ", 98);
 		fahrraeder[1].Ausleihe (" Max ", 733);

 		if (fahrraeder[1].Ausleihe (" Martin1378", 733)){ log ("Martin hat den Weg zum Tresen geschafft und das Fahrrad auszuleihen :) !"); }
		else {log ("Martin muss weiter in Muttis auto fahren"); }

		fahrraeder[1].zurueckgegeben();

 		if (fahrraeder[1].Ausleihe (" Martin1378", 733)){ log ("Martin hat den Weg zum Tresen geschafft und das Fahrrad auszuleihen :) !"); }
		else {log ("Martin muss weiter in Muttis auto fahren"); }		

		fahrraeder[0].Ausleihe (" Lisa ", 98);

		fahrraeder[0].gib_filiale_aus();
		fahrraeder[1].gib_filiale_aus();
		fahrraeder[2].gib_filiale_aus();
	        fahrraeder[3].gib_filiale_aus();
        
        
               
 

	
	for (unsigned i=0; i<sizeof(fahrraeder)/sizeof(fahrraeder[0]);i++) {
	

		log (fahrraeder [i]);


	}
};
	



