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


class Branch
{
public:
    Branch();

    ~Branch() = default;

    static std::vector<std::string> queryBranchNameByRut(std::shared_ptr<Connection> conn, int32_t rut);

    static int32_t company(std::shared_ptr<Connection> conn, int32_t company);

    static std::string branch(std::shared_ptr<Connection> conn, int32_t company, const std::string& branch);

    static std::string name(std::shared_ptr<Connection> conn, int32_t company, const std::string& identifier);

    static std::string address(
        std::shared_ptr<Connection> conn, int32_t company, const std::string& branch, const std::string& address);
};

}  // end Sale
}  // end cns