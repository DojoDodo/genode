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
#include <polygon_gfx/shaded_polygon_painter.h>
#include <polygon_gfx/interpolate_rgb565.h>
#include <os/pixel_alpha8.h>
#include <nano3d/scene.h>
#include <nano3d/sincos_frac16.h>
#include <gems/color_hsv.h>



using namespace Net;
using namespace Genode;

using Microseconds = Genode::Timer::Microseconds;


class Graph : public Nano3d::Scene<Pixel_rgb565>
{
	private:

		enum { HISTORY_LEN = 32 };

		Nitpicker::Area const    _size;
		unsigned                 _data[HISTORY_LEN];
		unsigned                 _oldest_data_idx { 0 };
		Polygon::Shaded_painter  _shaded_painter;

	public:

		Graph(Env              &env,
		      Heap             &heap,
		      unsigned          update_rate_ms,
		      Nitpicker::Point  pos,
		      Nitpicker::Area   size)
		:
			Nano3d::Scene<Pixel_rgb565>(env, update_rate_ms, pos, size),
			_size(size), _shaded_painter(heap, _size.h())
		{
			for (unsigned i = 1; i < HISTORY_LEN; i++) {
				_data[i] = 0; }
		}

		void new_data(unsigned v)
		{
			_data[_oldest_data_idx] = v;
			_oldest_data_idx = (_oldest_data_idx + 1) % HISTORY_LEN;
		}

		void render(Genode::Surface<Pixel_rgb565> &pixel,
		            Genode::Surface<Pixel_alpha8> &alpha) override
		{
error("HAllo");
			Color const top_color    = Color(10, 10, 10, 20);
			Color const bottom_color = Color(10, 10, 10, 100);
			Color const graph_color  = Color(0, 0, 0, 100);

			unsigned const w = pixel.size().w();
			unsigned const h = pixel.size().h();

			/* paint background square */
			typedef Polygon::Shaded_painter::Point Point;
			Point points[4];
			points[0] = Point(0,     0,     top_color);
			points[1] = Point(w - 1, 0,     top_color);
			points[2] = Point(w - 1, h - 1, bottom_color);
			points[3] = Point(0,     h - 1, bottom_color);
			_shaded_painter.paint(pixel, alpha, points, sizeof(points)/sizeof(points[0]));

			/* calculate graph scaling parameters */
			unsigned h_limit = 1;
			for (unsigned i = 1; i < HISTORY_LEN; i++) {
				if (_data[i] > h_limit) {
					h_limit = _data[i]; }
			}
			float const w_step  = ((float)w - 1) / (HISTORY_LEN - 1);
			float const h_step  = ((float)h - 1) / h_limit;

			/* paint graph as consecutive rectangles */
			unsigned x1;
			unsigned x2 = 0;
			unsigned y1;
			unsigned y2;
			for (unsigned i = 0; i < HISTORY_LEN - 1; i++) {
				unsigned di1 = (i + _oldest_data_idx) % HISTORY_LEN;
				unsigned di2 = di1 < HISTORY_LEN - 1 ? di1 + 1 : 0;
				x1 = x2;
				x2 = (float)w_step * (i + 1);
				y1 = (float)h_step * _data[di1];
				y2 = (float)h_step * _data[di2];
				points[0] = Point(x1, (h - 1) - y1, graph_color);
				points[1] = Point(x2, (h - 1) - y2, graph_color);
				points[2] = Point(x2, (h - 1),      graph_color);
				points[3] = Point(x1, (h - 1),      graph_color);
				_shaded_painter.paint(pixel, alpha, points, sizeof(points)/sizeof(points[0]));
			}
		}
};



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
		float			       _traffic_per_second;
		unsigned 		       _last2; 			       
                Nitpicker::Area                _size {400,600}; 
		Nitpicker::Point               _pos {0,0};	
  		unsigned		       _update_rate_ms {1000} ;
		Graph 			       _graph;

		

	public:

	
			void _handle_time_difference (Microseconds now) {
error("time_diff");
                        unsigned x=_uplink.traffic_counter ();
			unsigned y=_uplink.traffic_size ();
			
	
			if ( _uplink.remote().is_set()) {				
			    x=x+_uplink.remote().deref().traffic_counter ();  

		            y=y+_uplink.remote().deref().traffic_size ();
			  
				
		            _graph.new_data (_traffic_per_second/1000);     
	
			    
				
				}

			_difference=x-_last;
			_last=x;
			_traffic_per_second=y-_last2;
			_last2=y;
			
			

			log (_difference, "  packages sended/", _traffic_per_second/1000, " Kb/s");
		 	 	 		
				

						
			
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
	      _curr_time, env.rm()),
	_graph (env, _heap, _update_rate_ms, _pos, _size) 

{
	env.parent().announce(env.ep().manage(_root));
}


void Component::construct(Env &env)
{
	/* XXX execute constructors of global statics */
	env.exec_static_constructors();

	static Main main(env);
}



