#ifndef AMBXLOCATIONMAP_H
#define AMBXLOCATIONMAP_H

#include <map>
#include <vector>

#include "Classification.h"

typedef enum {
 	amBX_EVERYWHERE = 9, /**< amBX Location considered to be all Locations */
 	amBX_N = 1,          /**< amBX Location North */
 	amBX_NE = 2,         /**< amBX Location North-East */
 	amBX_E = 5,          /**< amBX Location East */
 	amBX_SE = 8,         /**< amBX Location South-East */
 	amBX_S = 7,         /**< amBX Location South */
 	amBX_SW = 6,        /**< amBX Location South-West */
 	amBX_W = 3,         /**< amBX Location West */
 	amBX_NW = 0,       /**< amBX Location North-West */
 	amBX_C = 4         /**< amBX Location Center */
}amBX_loc;

class AmBXLocationMap
{
public:
	AmBXLocationMap();
	std::vector<amBX_loc> getAmBXLocations(std::string location);
	int* getEnumLocations();
	int getEnumLocationsLength();
	std::map<std::string, std::vector<amBX_loc>> getamBXLocMap();
private:
	std::map<std::string, std::vector<amBX_loc>> m_amBXLocMap;
	std::vector<amBX_loc> north;
	std::vector<amBX_loc> nnenw;
	std::vector<amBX_loc> nsc;
	std::vector<amBX_loc> northwest;
	std::vector<amBX_loc> nwwsw;
	std::vector<amBX_loc> northeast;
	std::vector<amBX_loc> neese;
	std::vector<amBX_loc> west;
	std::vector<amBX_loc> east;
	std::vector<amBX_loc> south;
	std::vector<amBX_loc> ssesw;
	std::vector<amBX_loc> southeast;
	std::vector<amBX_loc> southwest;
	std::vector<amBX_loc> center;
	std::vector<amBX_loc> all;

	int Locations[9];
	//int Heights[4]; // NOTE: currently ignoring heights and using everytime EVERYWHERE
};

#endif
