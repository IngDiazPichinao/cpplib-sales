//
//
//
#pragma once

#include <cns/currency.hpp>
#include <cns/pgsql/Connection.hpp>

#include <memory>
#include <string>
#include <vector>

#include "defs.hpp"
#include "Payment.hpp"
#include "../sql/queries.hpp"


namespace cns {
    namespace sales {


class PaymentsDocuments
{
public:

    int64_t _doc_id;
    int64_t _doc_total;
    int64_t _amount_paid;
    int64_t _number_cheque;
    int64_t _account;
    int64_t _transfer_number;

    int32_t _days;

    std::string _doc_type;
    std::string _payment_type;
    std::string _bank;
    std::string _expiry;

    PaymentsDocuments(int64_t doc_id, int64_t doc_total, int64_t amount_paid, int64_t number_cheque, int64_t account, int64_t transfer_number, int32_t days, const std::string& doc_type, const std::string& payment_type, const std::string& bank, const std::string& expiry);
   ~PaymentsDocuments() = default;

   static int64_t remainder_paid (std::vector<PaymentsDocuments> document);

};


class PaymentToDocument
{
public:
    const int64_t _doc_id;
    const int64_t _doc_total;
    const int64_t _pay_amount;
    const int64_t _number_cheque;
    const int64_t _transfer_number;

    const int32_t _cheque_days;

    const std::string _doc_type;
    const std::string _pay_type;
    const std::string _name_bank;
    const std::string _cheque_expiry;
    const std::string _cheque_rejected;

     PaymentToDocument(int64_t doc_id, int64_t doc_total, int64_t pay_amount, int64_t number_cheque, int64_t transfer_number, int32_t cheque_days, const std::string& doc_type, const std::string& pay_type, const std::string& name_bank, const std::string& cheque_expiry, const std::string& cheque_rejected);
    ~PaymentToDocument() = default;

    static std::vector<PaymentToDocument> selectDocumentPaid (std::shared_ptr<Connection> conn, int64_t doc_id);

    static int64_t amount_remaining (int64_t total, int64_t amount_paid);

    static int64_t total_amount (std::vector<PaymentToDocument> PaidDocuments);
};

    } // end  sale
} // end cns
