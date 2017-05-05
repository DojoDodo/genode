/*
 * \brief  Bump-in-the-wire component to dump NIC traffic info to the log
 * \author Martin Stein
 * \date   2017-03-08
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode */
#include <base/component.h>
#include <base/heap.h>
#include <base/attached_rom_dataspace.h>
#include <timer_session/connection.h>
#include <os/timeout.h>

/* local includes */
#include <component.h>
#include <uplink.h>

using namespace Net;
using namespace Genode;

using Microseconds = Genode::Timer::Microseconds;

class Main
{
	private:

		Genode::Attached_rom_dataspace _config;
		Timer::Connection              _timer_connection;
		Genode::Timer                  _timer;
		unsigned                       _curr_time { 0 };
		Genode::Heap                   _heap;
		Uplink                         _uplink;
		Net::Root                      _root;
                unsigned                       _uplink_traffic;
		float 			       _difference;
                unsigned   		       _last;
	public:

	
	

		void _handle_time_difference (Microseconds now) {

                        unsigned x=_uplink.traffic_counter ();

			if ( _uplink.remote().is_set()) {				
			    x=x+_uplink.remote().deref().traffic_counter ()  
				;}
			_difference=x-_last;
			_last=x;
			

			log (": ", _uplink.traffic_counter(), " packages sended", "  package size: ", _uplink.traffic_size()/1000, " kb", "   traffic/s: ", _difference);
		 	 	 		
				

						
			
			}

		Genode::Periodic_timeout<Main> _time_difference { _timer, *this, &Main::_handle_time_difference, Microseconds (1000000)}; 



	Main(Env &env);
};


Main::Main(Env &env)
:
	_config(env, "config"), _timer_connection(env),
	_timer(_timer_connection, env.ep()), _heap(&env.ram(), &env.rm()),
	_uplink(env, _config.xml(), _timer, _curr_time, _heap),
	_root(env.ep(), _heap, _uplink, env.ram(), _config.xml(), _timer,
	      _curr_time, env.rm())
{
	env.parent().announce(env.ep().manage(_root));
}


void Component::construct(Env &env)
{
	/* XXX execute constructors of global statics */
	env.exec_static_constructors();

	static Main main(env);
}
