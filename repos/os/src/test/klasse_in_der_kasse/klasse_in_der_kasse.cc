#include <base/log.h>
#include <base/component.h>
#include <base/output.h>

using namespace Genode;

class Spiel {
public:
	enum genre {Shooter,Simulation,Strategie,Jump_and_run,Twinstick};
private:
	char const*Name;
	bool Coop; 
	unsigned Spieleranzahl;
	int Bewertung;
	genre Genre;
public: 
	Spiel(char const* name, Genre kenre, bool coop, unsigned spieleranzahl, int bewertung){
		Name=name;
		Coop=coop;
		Spieleranzahl=spieleranzahl;
		Bewertung=bewertung;
		Genre=kenre;
	 }
	
	void print(Output &output) const 
	{ 
		Genode::print(output, "Spiel:  ",
				Name, "  ", (int)kenre, "\n", Coop, "\n", Spieleranzahl, "\n", Bewertung);
	}

};





void Component::construct(Genode::Env &env){
	Spiel Battlefield ("Battlefield",Spiel::Shooter,false,64,4);
	Spiel Mario ("Mario",Spiel::Jump_and_run,true,2,3);
    Spiel Guenthersimulator ("Guenthersimulator",Spiel::Simulation,false,1,-10);
    Spiel Enterthegungion ("Enterthegungion",Spiel::Twinstick,true,2,10);
log (Battlefield);
log (Mario); 
log (Enterthegungion);
log (Guenthersimulator);

bool Suche = true; 
	
if (){
	
}
}

}




