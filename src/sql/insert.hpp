// n
//
//
#include <string>

#pragma once

namespace cns {
namespace sales {


static const std::string insert_items_q{
    R"(
        INSERT INTO sales.document_items
            (company, doc_id, doc_type, product, quantity, price, discount, discounted, total)
        VALUES
            (:company, :doc_id, :doc_type, :product, :quantity, :price, :discount, :amount_dcto, :total)
    ;)"};


static const std::string insert_document_q{
    R"(
        INSERT INTO sales.documents
            (
                company,      branch,     doc_id, doc_type,     customer, customer_addr, salesman,
                discount,     discounted, net,    tax_vat_rate, tax_vat,  total,         sii_xml,
                sii_uploaded, transact
            )
        VALUES
            (
                :company,      :branch,      :doc_id, :doc_type, :customer, :addr,  :salesman,
                :discount,     :amount_dcto, :net,    :dcto,     :tax_vat,  :total, :sii_xml,
                :sii_uploaded, :uuid
            )
    ;)"


};


static const std::string insert_payment_q(
    R"(
        INSERT INTO sales.payments
            (company,  customer,  type,  cash,  amount, transact)
        VALUES
            (:pay_company, :pay_customer, :pay_type, :pay_cash, :pay_amount, :pay_uuid)
    ;)"

    R"(
        INSERT INTO sales.payments_to_documents
            (pay_id, pay_company, pay_customer, doc_company, doc_id, doc_type, amount, transact)
        VALUES
            ((
                SELECT MAX(id) AS ID
                  FROM sales.payments
                  WHERE company = :company
             ), :pd_pay_company, :pd_pay_customer, :pd_doc_company, :pd_doc_id, :pd_doc_type, :pd_amount, :pd_uuid
            )
    ;)");


static const std::string insert_payments_cheque_q(
    R"(
        INSERT INTO sales.payments
            (company, customer, type, cash, amount, transact)
        VALUES
            (:pay_company, :pay_customer, :pay_type, :pay_cash, :pay_amount, :pay_uuid)
    ;)"

    R"(
        INSERT INTO sales.payments_cheque
            (id, company, customer, bank, number, days, expiry)
        VALUES
            ((
                SELECT MAX(id) AS ID
                  FROM sales.payments
                 WHERE company = :pc_company
            ), :pch_company, :pch_customer, :pch_bank, :pch_number, :pch_days, :pch_expiry)
    ;)"

    R"(
        INSERT INTO sales.payments_to_documents
            (pay_id, pay_company, pay_customer, doc_company, doc_id, doc_type, amount, transact)
        VALUES
            ((
                SELECT MAX(id) AS ID
                  FROM sales.payments
                 WHERE company = :pd_company
            ), :ptd_company, :ptd_customer, :ptd_doc_company, :ptd_doc_id, :ptd_doc_type, :ptd_amount, :ptd_uuid)
    ;)");


static const std::string insert_payments_card_q(
    R"(
        INSERT INTO sales.payments
            (company, customer, type, cash, amount, transact)
        VALUES
            (:pay_company, :pay_customer, :pay_type, :pay_cash, :pay_amount, :pay_uuid)
    ;)"


    R"(
        INSERT INTO sales.payments_card
            (id, company, customer, transfer_number)
        VALUES
            ((
                SELECT MAX(id) AS ID
                  FROM sales.payments
                 WHERE company = :pc_company
            ), :pcc_company, :pcc_customer, :pcc_transfer_number)
    ;)"

    R"(
        INSERT INTO sales.payments_to_documents
            (pay_id, pay_company, pay_customer, doc_company, doc_id, doc_type, amount, transact)
        VALUES
            ((
                SELECT MAX(id) AS ID
                  FROM sales.payments
                 WHERE company = :pd_company
            ), :ptd_company, :ptd_customer, :ptd_doc_company, :ptd_doc_id, :ptd_doc_type, :ptd_amount, :ptd_uuid)
    ;)");


static const std::string insert_transactions_q(
    R"(
        INSERT INTO common.transactions
            (closed)
        values
            (:closed)
    ;)");
}
}
