//
//

#include "PaymentToDocument.hpp"


namespace cns {
    namespace sales {

PaymentsDocuments::PaymentsDocuments(int64_t doc_id, int64_t doc_total, int64_t amount_paid, int64_t number_cheque, int64_t account, int64_t transfer_number, int32_t days, const std::string& doc_type, const std::string& payment_type, const std::string& bank, const std::string& expiry)
:
_doc_id(doc_id),
_doc_total(doc_total),
_amount_paid(amount_paid),
_number_cheque(number_cheque),
_account(account),
_transfer_number(transfer_number),
_days(days),
_doc_type(doc_type),
_payment_type(payment_type),
_bank(bank),
_expiry(expiry)
{ }


int64_t PaymentsDocuments::remainder_paid (std::vector<PaymentsDocuments> document)
{
    int64_t remainder_paid = 0;

    for (auto& data : document)
    {
        remainder_paid += data._amount_paid;
    }

    return remainder_paid;
}


PaymentToDocument::PaymentToDocument(int64_t doc_id, int64_t doc_total, int64_t pay_amount, int64_t number_cheque, int64_t transfer_number, int32_t cheque_days, const std::string& doc_type, const std::string& pay_type, const std::string& name_bank, const std::string& cheque_expiry, const std::string& cheque_rejected)
:
_doc_id(doc_id),
_doc_total(doc_total),
_pay_amount(pay_amount),
_number_cheque(number_cheque),
_transfer_number(transfer_number),
_cheque_days(cheque_days),
_doc_type(doc_type),
_pay_type(pay_type),
_name_bank(name_bank),
_cheque_expiry(cheque_expiry),
_cheque_rejected(cheque_rejected)
{ }


std::vector<PaymentToDocument> PaymentToDocument::selectDocumentPaid (std::shared_ptr<Connection> conn, int64_t doc_id)
{
    std::vector<PaymentToDocument> documentPaid;

    Query query {select_documents_paid};
    query["doc_id"] << doc_id;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        const std::string& sql_pay_type = get<std::string>(row["pay_type"]);

        std::string pay_type = "";
        std::string rejected = "";

        bool sql_rejected = get<bool>(row["cheque_rejected"], false);

        if (sql_pay_type == Payment::PaymentType_sqlCash())
        {
            pay_type = Payment::PaymentType_nameCash();
            rejected = "--";
        }

        if (sql_pay_type == Payment::PaymentType_sqlCheque())
        {
            pay_type = Payment::PaymentType_nameCheque();

            if (sql_rejected == true) { rejected = "Rechazado";    }
            else                      { rejected = "No Rechazado"; }
        }

        if (sql_pay_type == Payment::PaymentType_sqlCard())
        {
            pay_type = Payment::PaymentType_nameCard();
            rejected = " -- ";
        }

        documentPaid.emplace_back(
            get<int64_t>(row["doc_id"],          0),
            get<int64_t>(row["doc_total"],       0),
            get<int64_t>(row["pay_amount"],      0),
            get<int64_t>(row["number_cheque"],   0),
            get<int64_t>(row["transfer_number"], 0),
            get<int32_t>(row["cheque_days"],     0),
            get<std::string>(row["doc_type"],    " -- "),
            pay_type,
            get<std::string>(row["name_bank"],     " -- "),
            get<std::string>(row["cheque_expiry"], " -- "),
            rejected
        );
    }

    return documentPaid;
}


int64_t PaymentToDocument::amount_remaining (int64_t total, int64_t amount_paid)
{
    return total - amount_paid;
}


int64_t PaymentToDocument::total_amount (std::vector<PaymentToDocument> PaidDocuments)
{
    int64_t amount = 0;

    for (auto& data : PaidDocuments)
    {
        amount += data._pay_amount;
    }

    return amount;
}

    } // end sales
} // end cns