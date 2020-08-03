#ifndef SECTORS_PROXY_RESOURCES_H
#define SECTORS_PROXY_RESOURCES_H

// The resource types defined in this file are proxy types used to serialize
// the SectorMap internal data structures into resource files and to expose
// these objects out into scripts when requested.
//
// The real storage of these is embedded inside SectorMap, populated from these
// proxy resource types when a caller writes to the SectorMap setters.

#include "sector_map.h"
#include <core/resource.h>

class SectorWall : public Resource {
	GDCLASS(SectorWall, Resource);

public:
	typedef SectorMap::MaterialConfig::Flags MaterialFlags;
};

class SectorFloor : public Resource {
	GDCLASS(SectorFloor, Resource);

public:
	typedef SectorMap::MaterialConfig::Flags MaterialFlags;
};

class Sector : public Resource {
	GDCLASS(Sector, Resource);

public:
	Array walls;
};

class SectorMapData : public Resource {
	GDCLASS(SectorMapData, Resource);

public:
	PoolVector2Array vertices;
	Array sectors;
};

#endif
