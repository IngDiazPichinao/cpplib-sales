//
//
//

#pragma once

#include <cns/pgsql/Connection.hpp>

#include "../sql/queries.hpp"
#include "Payment.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cns {
namespace sales {


class Closure
{
public:
    const int64_t _docID;
    const int32_t _company;

    const std::string _branch;
    const std::string _docType;

    const bool value;

    Closure(int64_t docID, int32_t company, const std::string& branch, const std::string& docType, bool value);
    ~Closure() = default;
};


class Accounting
{
public:
    const int64_t _docID;
    const int64_t _docTotal;

    const std::string _created;
    const std::string _docType;
    const std::string _payType;

    const bool _unAccounted;

    Accounting(
        int64_t            docID,
        int64_t            docTotal,
        const std::string& created,
        const std::string& docType,
        const std::string& payType,
        bool               unAccounted);
    ~Accounting() = default;

    static std::vector<Accounting> Unaccounted(
        std::shared_ptr<Connection> conn, int32_t rut, const std::string& from, const std::string& expiry);

    static void UpdateAccounting(std::shared_ptr<Connection> conn, std::vector<Closure> closure);
};

}  // end Sale
}  // end cns