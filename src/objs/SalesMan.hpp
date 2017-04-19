//
//
//
#pragma once

#include <cns/pgsql/Connection.hpp>

#include <memory>
#include <string>
#include <vector>

#include "../sql/queries.hpp"


namespace cns {
namespace sales {


class SalesMan
{
public:
    const int32_t     rut;
    const std::string name;

    SalesMan(int32_t rut, const std::string& name);
    ~SalesMan() = default;

    static std::vector<SalesMan> querySelectSalesMan(std::shared_ptr<Connection> conn);

    static std::string queryGetNameSalesman(std::shared_ptr<Connection> conn, int32_t rut);

    static int32_t check_salesman(std::shared_ptr<Connection> conn, int32_t rut);
};
}
}