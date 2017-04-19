//
//
//
#include "PaymentCheque.hpp"


namespace cns {
    namespace sales {

PaymentCheque::PaymentCheque(int64_t id, int64_t amount, int64_t doc_id, int64_t number, int32_t company, int32_t customer, int32_t days, const std::string& type, const std::string& doc_type, const std::string& bank, const std::string& expiry, const std::string& uuid, bool cash)
: Payment(amount, doc_id, company, customer, type, doc_type, uuid, cash),
_id(id),
_number(number),
_days(days),
_bank(bank),
_expiry(expiry)
{ }

int64_t PaymentCheque::id     (void) const { return this->_id;     }
int64_t PaymentCheque::number (void) const { return this->_number; }

int32_t PaymentCheque::days   (void) const { return this->_days; }

std::string PaymentCheque::bank   (void) const { return this->_bank;   }
std::string PaymentCheque::expiry (void) const { return this->_expiry; }
//bool PaymentCheque::rejected (void) const { return this->_rejected; }


void PaymentCheque::insertCheque (std::shared_ptr<Connection> conn, std::vector<PaymentCheque> PaymentCheque)
{
    Query query {insert_payments_cheque_q};

    for (auto& data : PaymentCheque)
    {
        query["pay_company"]     << data._company,
        query["pay_customer"]    << data._customer;
        query["pay_type"]        << data._type;
        query["pay_cash"]        << data._cash;
        query["pay_amount"]      << data._amount;
        query["pay_uuid"]        << data._uuid;
        query["pc_company"]      << data._company;
        query["pch_company"]     << data._company;
        query["pch_customer"]    << data._customer;
        query["pch_bank"]        << data._bank;
        query["pch_number"]      << data._number;
        query["pch_days"]        << data._days;
        query["pch_expiry"]      << data._expiry;
        query["pd_company"]      << data._company;
        query["ptd_company"]     << data._company;
        query["ptd_customer"]    << data._customer;
        query["ptd_doc_company"] << data._company;
        query["ptd_doc_id"]      << data._doc_id;
        query["ptd_doc_type"]    << data._doc_type;
        query["ptd_amount"]      << data._amount;
        query["ptd_uuid"]        << data._uuid;

        std::shared_ptr<Result> result = conn->execute(query);
        result->fetchall();
    }
}

    }
}
