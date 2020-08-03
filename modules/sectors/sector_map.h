#ifndef SECTOR_MAP_H
#define SECTOR_MAP_H

#include <core/map.h>
#include <core/math/vector2.h>
#include <core/reference.h>
#include <core/resource.h>
#include <core/vector.h>
#include <scene/resources/material.h>

class SectorMap : public Resource {
	GDCLASS(SectorMap, Resource);

public:
	struct MaterialConfig {
		enum Flags {
			SWAP_XY = 1,
			X_FLIP = 2,
			Y_FLIP = 4,
			ALIGN_ALT = 8, // for floor/ceiling, align to first wall instead of origin/axes. For walls, align to bottom instead of top.
		};

		Ref<Material> resource;
		Flags flags;
		Vector2 panning;
		Vector2 scale;
		uint32_t collision_layers;
		uint32_t collision_mask;
	};

private:
	// We (ab?)use Vector2i to compactly store a pair of vertices where the
	// first element (x) is the left side and the second element (y) is the
	// right side.
	typedef Vector2i VertexPair;

	struct Wall {
		enum Flags {
			CLOSE_LOOP = 1,
			HAS_PORTAL = 2,
		};

		size_t left_vertex_idx;
		Flags flags;
		size_t portal_sector_idx; // must have a wall with the same two vertices in the opposite order

		MaterialConfig ceiling_step_material;
		MaterialConfig main_material;
		MaterialConfig floor_step_material;
	};

	struct Floor {
		real_t start_height;
		real_t slope;

		MaterialConfig material;
	};

	struct Sector {
		Vector<Wall> walls;
		Floor floor;
		Floor ceiling;

		// Computes a single polygon that covers the area delimited by
		// the walls, flattening any inner hole loops into the inner loop
		// using additional bridge edges.
		PoolVector2Array floor_polygon();

		// Computes the floor heights for each of the vertices used by walls of
		// the sector based on the floor's slope. It's a waste of time to
		// call this if the floor's slope is zero, but it'll still succeed.
		Map<size_t, real_t> sloped_floor_vertex_heights();

		// Computes the ceiling for each of the vertices used by walls of
		// the sector based on the ceiling's slope. It's a waste of time to
		// call this if the ceiling's slope is zero, but it'll still succeed.
		Map<size_t, real_t> sloped_ceiling_vertex_heights();
	};

	Vector<Vector2> vertices;
	Vector<Sector> sectors;

protected:
	static void
	_bind_methods();

public:
	SectorMap();
};

#endif
