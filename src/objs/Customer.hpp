//
// Customer Object in a Sale
//
#pragma once

#include <cns/pgsql/Connection.hpp>

#include "../sql/queries.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cns {
namespace sales {

class Customer
{
public:
    const int64_t _credit_used;
    const int64_t _credit_backed;

    const int32_t _rut;  // ID

    const std::string _trade_name;
    const std::string _region;
    const std::string _address;
    const std::string _comune;
    const std::string _city;
    const std::string _fono;
    const std::string _movil;
    const std::string _email;
    const std::string _commercial_business;


    Customer(int64_t            credit_used,
             int64_t            credit_backed,
             int32_t            rut,
             const std::string& trade_name,
             const std::string& region,
             const std::string& address,
             const std::string& comune,
             const std::string& city,
             const std::string& fono,
             const std::string& movil,
             const std::string& email,
             const std::string& commercial_business);
    ~Customer() = default;

    static std::vector<Customer> querySelectCustomers(std::shared_ptr<Connection> conn);
    static std::vector<Customer> readCustomerInformation(std::shared_ptr<Connection> conn,
                                                         int32_t                     rut);
    static std::vector<Customer> dataCustomer(std::shared_ptr<Connection> conn, int32_t rut);


    cns::money querySelectCredit(std::shared_ptr<Connection> conn);  // available credit on good
                                                                     // trust
    cns::money querySelectCreditBacked(std::shared_ptr<Connection> conn);  // available credit
                                                                           // backed with a document
};


}  // sale
}  // cns
