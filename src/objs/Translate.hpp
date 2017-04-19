//
//
//

#pragma once

#include <cns/except.hpp>
#include <cns/pgsql/Connection.hpp>

#include "defs.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cns {
namespace sales {


class Translate
{
public:
    Translate();
    ~Translate();

    static const std::string head_rut(void);
    static const std::string head_name(void);
    static const std::string head_activity(void);
    static const std::string head_address(void);
    static const std::string head_city(void);
    static const std::string head_region(void);
    static const std::string head_code(void);
    static const std::string head_description(void);
    static const std::string head_price(void);
    static const std::string head_stock(void);
    static const std::string head_quantity(void);
    static const std::string head_discount(void);
    static const std::string head_valundcto(void);
    static const std::string head_amountdcto(void);
    static const std::string head_valwithdcto(void);
    static const std::string head_delete(void);
    static const std::string head_paymenttype(void);
    static const std::string head_amount(void);
    static const std::string head_cheque(void);
    static const std::string head_account(void);
    static const std::string head_transfer(void);
    static const std::string head_bank(void);
    static const std::string head_expiry(void);
    static const std::string head_days(void);
    static const std::string head_paymentdocument(void);
    static const std::string head_document(void);
    static const std::string head_amounttotal(void);
    static const std::string head_payment(void);
    static const std::string head_statuccheque(void);
    static const std::string head_date(void);
    static const std::string head_remaining(void);
    static const std::string head_company(void);
    static const std::string head_branch(void);
    static const std::string head_customer(void);
    static const std::string head_tradename(void);
    static const std::string head_salesman(void);
    static const std::string head_accounting(void);
};
}
}