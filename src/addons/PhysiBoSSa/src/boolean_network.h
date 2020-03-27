#ifndef __CELL_CYCLE_NETWORK_H
#define __CELL_CYCLE_NETWORK_H

#include "maboss_network.h"

/**
 * \class BooleanNetwork
 * \brief Boolean network handeler
 * 
 * Possible inputs and outputs depends on the structures of the network, try to put different possibilities.
 *
 *	\date 05/30/2017
 *	\author Gaelle Letort, Institut Curie
 */

class BooleanNetwork
{
	private:
		/** \brief MaBoss Network doing the job */
		MaBoSSNetwork maboss;
		
		/** \brief Vector of nodes state current value (0 or 1) */
		std::vector<bool> nodes;

		/** \brief time left before to update it again */
		double time_to_update;
	
		/** \brief choose a random update time, to asynchronize it between all cells 
		 *
		 * Set the next time at which to update the current cell's network. The time in between two udpates is chosen randomly in order to not update all cells together. */
		inline void set_time_to_update(){this->time_to_update = (1 + 0.5*UniformRandom11()) * this->maboss.get_update_time_step();}

	public:
		/** \brief Initialize a maboos network */
		void initialize_boolean_network(std::string bnd_file, std::string cfg_file, double time_step);

		/** \brief Reset nodes and time to update */
		void restart_nodes();

		/** \brief Update MaboSS network states */
		void run_maboss();
		
		/** \brief Get nodes */
		inline std::vector<bool>* get_nodes() {return &this->nodes;}
		
		/** \brief Get time to update*/
		inline double get_time_to_update() {return this->time_to_update;}
		
		/** \brief Get index of a node by name*/
		inline int get_node_index( std::string name ) {return this->maboss.get_maboss_node_index(name);}
		
		/** \brief Print name and values from the network */
		inline void print_nodes() {this->maboss.print_nodes(&this->nodes);}
};

#endif