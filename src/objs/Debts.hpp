//
//
//

#pragma once

#include <cns/pgsql/Column.hpp>
#include <cns/pgsql/Connection.hpp>

#include "../sql/queries.hpp"

#include <ctime>
#include <memory>
#include <string>
#include <vector>

namespace cns {
namespace sales {


class Debts
{
public:
    const int64_t _doc_id;
    const int64_t _amount_paid;
    const int64_t _doc_total;
    const int64_t _remaining;

    const int32_t _company;
    const int32_t _customer;
    const int32_t _salesman;

    const std::string _created;
    const std::string _branch;
    const std::string _doc_type;
    const std::string _trade_name;
    const std::string _address;

    Debts(int64_t            doc_id,
          int64_t            amount_paid,
          int64_t            doc_total,
          int64_t            remaining,
          int32_t            company,
          int32_t            customer,
          int32_t            salesman,
          const std::string& created,
          const std::string& branch,
          const std::string& doc_type,
          const std::string& trade_name,
          const std::string& address);
    ~Debts() = default;

    static std::vector<Debts> queryFilterDebtsByCustomer(std::shared_ptr<Connection> conn,
                                                         int32_t                     rut);
    static std::vector<Debts> queryFilterDebtsBySalesMan(std::shared_ptr<Connection> conn,
                                                         int32_t                     rut);
    static std::vector<Debts> queryFilterDebtsByCustomerDate(std::shared_ptr<Connection> conn,
                                                             int32_t                     rut,
                                                             std::string                 date);
};
}  // sale
}  // cns