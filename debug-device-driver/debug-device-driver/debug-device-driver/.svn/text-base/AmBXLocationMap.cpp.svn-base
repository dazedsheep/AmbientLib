#include "stdafx.h"
#include "AmBXLocationMap.h"

AmBXLocationMap::AmBXLocationMap()
{	
	// initialize locations and heights for easier checking
	Locations[0] = amBX_N;
	Locations[1] = amBX_NW;
	Locations[2] = amBX_NE;
	Locations[3] = amBX_W;
	Locations[4] = amBX_E;
	Locations[5] = amBX_S;
	Locations[6] = amBX_SE;
	Locations[7] = amBX_SW;
	Locations[8] = amBX_C;
	/*Heights[0] = amBX_BOTTOM;
	Heights[1] = amBX_MIDDLE;
	Heights[2] = amBX_TOP;
	Heights[3] = amBX_EVERYHEIGHT;*/
	
	north.push_back(amBX_N);

	nnenw.push_back(amBX_N);
	nnenw.push_back(amBX_NE);
	nnenw.push_back(amBX_NW);
	
	nsc.push_back(amBX_N);
	nsc.push_back(amBX_S);
	nsc.push_back(amBX_C);	

	northwest.push_back(amBX_NW);
	
	nwwsw.push_back(amBX_NW);
	nwwsw.push_back(amBX_W);
	nwwsw.push_back(amBX_SW);
	
	northeast.push_back(amBX_NE);
	
	neese.push_back(amBX_NE);
	neese.push_back(amBX_E);
	neese.push_back(amBX_SE);
	
	west.push_back(amBX_W);
	
	east.push_back(amBX_E);
	
	south.push_back(amBX_S);
	
	ssesw.push_back(amBX_S);
	ssesw.push_back(amBX_SE);
	ssesw.push_back(amBX_SW);
	
	southeast.push_back(amBX_SE);
	
	southwest.push_back(amBX_SW);	
	
	center.push_back(amBX_C);

	all.push_back(amBX_N);
	all.push_back(amBX_NE);
	all.push_back(amBX_NW);
	all.push_back(amBX_E);
	all.push_back(amBX_W);
	all.push_back(amBX_S);
	all.push_back(amBX_SE);
	all.push_back(amBX_SW);
	all.push_back(amBX_C);
	

	// fill mapping with necessary locations
	// N = Center + Back
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_BACK, north));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_TOP + Classification::LOC_Z_BACK, north));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_BACK, north));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK, north));

	// N,NE,NW = Everywhere + Back
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_BACK, nnenw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_TOP + Classification::LOC_Z_BACK, nnenw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_BACK, nnenw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK, nnenw));

	// N,S,C = Center + Everywhere
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_BOTTOM + Classification::LOC_EVERYWHERE, nsc));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_TOP + Classification::LOC_EVERYWHERE, nsc));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_MIDDLE + Classification::LOC_EVERYWHERE, nsc));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE, nsc));

	// NW = Centerleft + Back
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_BACK, northwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_TOP + Classification::LOC_Z_BACK, northwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_BACK, northwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK, northwest));

	// NW = Left + Back
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_BACK, northwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_TOP + Classification::LOC_Z_BACK, northwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_BACK, northwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK, northwest));

	// NW,W,SW = Left + Everywhere
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_EVERYWHERE, nwwsw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_TOP + Classification::LOC_EVERYWHERE, nwwsw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_EVERYWHERE, nwwsw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE, nwwsw));

	// NW,W,SW = Centerleft + Everywhere
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_EVERYWHERE, nwwsw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_TOP + Classification::LOC_EVERYWHERE, nwwsw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_EVERYWHERE, nwwsw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE, nwwsw));

	// NE = Centerright + Back
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_BACK, northeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_TOP + Classification::LOC_Z_BACK, northeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_BACK, northeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK, northeast));

	// NE = Right + Back
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_BACK, northeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_TOP + Classification::LOC_Z_BACK, northeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_BACK, northeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_BACK, northeast));

	// NE,E,SE = Right + Everywhere
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_EVERYWHERE, neese));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_TOP + Classification::LOC_EVERYWHERE, neese));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_EVERYWHERE, neese));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE, neese));

	// NE,SE,E = Centerright + Everywhere
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_EVERYWHERE, neese));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_TOP + Classification::LOC_EVERYWHERE, neese));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_EVERYWHERE, neese));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE, neese));

	// W = Left + Midway
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_MIDWAY, west));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_TOP + Classification::LOC_Z_MIDWAY, west));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_MIDWAY, west));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY, west));

	// W,E,C = Everywhere + Midway
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_MIDWAY, amBX_W));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_TOP + Classification::LOC_Z_MIDWAY, amBX_W));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_MIDWAY, amBX_W));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY, amBX_W));

	// W = Centerleft + Midway
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_MIDWAY, west));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_TOP + Classification::LOC_Z_MIDWAY, west));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_MIDWAY, west));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY, west));

	// E = Right + Midway
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_MIDWAY, east));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_TOP + Classification::LOC_Z_MIDWAY, east));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_MIDWAY, east));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY, east));

	// E = Centerright + Midway
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_MIDWAY, east));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_TOP + Classification::LOC_Z_MIDWAY, east));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_MIDWAY, east));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY, east));

	// S = Center + Front
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_FRONT, south));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_TOP + Classification::LOC_Z_FRONT, south));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_FRONT, south));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT, south));

	// S,SE,SW = Everywhere + Front
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_FRONT, ssesw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_TOP + Classification::LOC_Z_FRONT, ssesw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_FRONT, ssesw));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT, ssesw));

	// SE = Centerright + Front
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_FRONT, southeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_TOP + Classification::LOC_Z_FRONT, southeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_FRONT, southeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERRIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT, southeast));

	// SE = Right + Front
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_FRONT, southeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_TOP + Classification::LOC_Z_FRONT, southeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_FRONT, southeast));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_RIGHT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT, southeast));

	// SW = Centerleft + Front
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_FRONT, southwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_TOP + Classification::LOC_Z_FRONT, southwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_FRONT, southwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTERLEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT, southwest));

	// SW = Left + Front
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_FRONT, southwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_TOP + Classification::LOC_Z_FRONT, southwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_FRONT, southwest));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_LEFT + Classification::LOC_EVERYWHERE + Classification::LOC_Z_FRONT, southwest));

	// C = Center + Midway
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_BOTTOM + Classification::LOC_Z_MIDWAY, center));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_TOP + Classification::LOC_Z_MIDWAY, center));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_Y_MIDDLE + Classification::LOC_Z_MIDWAY, center));
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_X_CENTER + Classification::LOC_EVERYWHERE + Classification::LOC_Z_MIDWAY, center));

	// ALL = Everywhere + Everywhere
	m_amBXLocMap.insert(std::make_pair(Classification::LOCATIONURIBASE + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE + Classification::LOC_EVERYWHERE, all));
}

int* AmBXLocationMap::getEnumLocations()
{
	return Locations;
}

int AmBXLocationMap::getEnumLocationsLength()
{
	return sizeof(Locations)/sizeof(Locations[0]);
}

std::map<std::string,std::vector<amBX_loc>> AmBXLocationMap::getamBXLocMap()
{
	return m_amBXLocMap;
}

std::vector<amBX_loc> AmBXLocationMap::getAmBXLocations(std::string location) 
{
	std::map<std::string, std::vector<amBX_loc>>::iterator iter = m_amBXLocMap.find(location);
	if(iter == m_amBXLocMap.end())
		return std::vector<amBX_loc>();
	else
		return iter->second;
}
