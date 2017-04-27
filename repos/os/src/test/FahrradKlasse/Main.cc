#include <base/output.h>
#include <base/component.h>
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
public:

Fahrrad (char const* name_bike, unsigned gaenge, bool verfuegbar, bool gepaecktraeger,einsatzgebiet eeinsatzgebiet, schaltung sschaltung, char const* besitzer, unsigned zeit)
{
	
	_Gaenge=gaenge;
	_Gepaecktraeger=gepaecktraeger;
	_Besitzer=besitzer;
        _Zeit=zeit;
	Einsatzgebiet=eeinsatzgebiet;
	Schaltung=sschaltung;
	_Verfuegbar=verfuegbar;
        _Name_Bike=name_bike;
}


				

			void print(Output &output) const
			{Genode::print(output, "Fahrrad: ", _Name_Bike, "Verfügbarkeit: ", _Verfuegbar ? "ist verfügbar" : "ist nicht verfügbar", _Besitzer, " ", _Zeit, " ", (unsigned)Einsatzgebiet, _Gaenge, " ", (unsigned)Schaltung , " ", _Gepaecktraeger);
			
		}
			
			
};




void Component::construct(Genode::Env &env){

        Fahrrad fahrraeder [4] {            
	
		{"Mountainbike", 27, false, false, Fahrrad::Wald, Fahrrad::Kettenschaltung, "Martin Stein", 54},
        	{"Diamant", 8, true, true, Fahrrad::Stadt, Fahrrad::Nabenschaltung, "", 0 },
        	{"BMX" , 1, false, false, Fahrrad::Stunts, Fahrrad::Singlespeed, "Steve Vai", 234 },
		{"Trekking", 30, true, true, Fahrrad::Stadt, Fahrrad::Kettenschaltung, "", 0},  
          
      		};
	
	for (unsigned i=0; i<sizeof(fahrraeder)/sizeof(fahrraeder[0]);i++) {
	log (fahrraeder [i]);
	
	}

}
