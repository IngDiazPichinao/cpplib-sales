//
//
//
#include "PaymentCard.hpp"


namespace cns {
    namespace sales {


PaymentCard::PaymentCard(int64_t id, int64_t amount, int64_t doc_id, int64_t transfer_number, int32_t company, int32_t customer, const std::string& type, const std::string& doc_type, const std::string& uuid, bool cash)

: Payment(amount, doc_id, company, customer, type, doc_type, uuid, cash),
_id(id),
_transfer_number(transfer_number)
{ }

int64_t PaymentCard::id              (void) const { return this->_id;              }
int64_t PaymentCard::transfer_number (void) const { return this->_transfer_number; }


void PaymentCard::insertCard (std::shared_ptr<Connection> conn, std::vector<PaymentCard> PaymentsCard)
{
    Query query {insert_payments_card_q};

    for (auto& data : PaymentsCard)
    {
        query["pay_company"]         << data._company;
        query["pay_customer"]        << data._customer;
        query["pay_type"]            << data._type;
        query["pay_cash"]            << data._cash;
        query["pay_amount"]          << data._amount;
        query["pay_uuid"]            << data._uuid;
        query["pc_company"]          << data._company;
        query["pcc_company"]         << data._company;
        query["pcc_customer"]        << data._customer;
        query["pcc_transfer_number"] << data._transfer_number;
        query["pd_company"]          << data._company;
        query["ptd_company"]         << data._company;
        query["ptd_customer"]        << data._customer;
        query["ptd_doc_company"]     << data._company;
        query["ptd_doc_id"]          << data._doc_id;
        query["ptd_doc_type"]        << data._doc_type;
        query["ptd_amount"]          << data._amount;
        query["ptd_uuid"]            << data._uuid;

        std::shared_ptr<Result> result = conn->execute(query);
        result->fetchall();
    }
}

    }
}