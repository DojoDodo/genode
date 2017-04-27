#include <base/log.h>
#include <base/component.h>
using namespace Genode;
 
void Component::construct(Genode::Env &env)
{   
	char const*y;
	for (unsigned i=1; i<=50; i++){
    
		for (unsigned t=1; t<=50; t++){
			if (t<26){
		    y="klein Zahl";
			}
			if (t>25){
		    y="große Zahl";
			}
			
			log ("Runde ",i,y," ",t);
    	}
    
	}
}
				