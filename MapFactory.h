#pragma once
#include "Map.h"
#include <bits/stdc++.h>
class MapFactory {
public:
	static std::unique_ptr<Map> createMap(MapType type);
};

