#include "register_types.h"

#include "sector_map.h"
#include "sectors_proxy_resources.h"
#include <core/class_db.h>

void register_sectors_types() {
	ClassDB::register_class<SectorMap>();
	ClassDB::register_class<SectorMapData>();
	ClassDB::register_class<Sector>();
	ClassDB::register_class<SectorWall>();
	ClassDB::register_class<SectorFloor>();
}

void unregister_sectors_types() {
}
