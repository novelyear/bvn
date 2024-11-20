#include "MapFactory.h"
#include "MR.h"

std::unique_ptr<Map> MapFactory::createMap(MapType type)
{
    switch (type) {
    case MapType::MR:
        return std::make_unique<MR>();  // ����Ĭ�Ϲ��캯��
    default:
        throw std::invalid_argument("Unknown character type");
    }
}
