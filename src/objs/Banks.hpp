//
//
//

#pragma once

#include <cns/pgsql/Connection.hpp>

#include "../sql/queries.hpp"

#include <memory>
#include <string>
#include <vector>


namespace cns {
namespace sales {


class Banks
{
public:
    const std::string iban;
    const std::string name;

    const int32_t number;

    Banks(const std::string& iban, const std::string& name, int32_t number);
    ~Banks() = default;

    static std::vector<Banks> querySelectBanks(std::shared_ptr<Connection> conn);
};

}  // end sales
}  // end cns