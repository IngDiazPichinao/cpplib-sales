//
//
//

#pragma once

#include <string>

namespace cns {
namespace sales {

static const std::string select_customers_q{
    R"(
        SELECT cust.rut          AS rut,
               ent.razon_social  AS name,
               ent.giro          AS activity,
               reg.name          AS region,
               addr.comune       AS comune,
               addr.city         AS city,
               addr.address      AS address
          FROM sales.customers   AS cust
     LEFT JOIN common.entities AS ent
            ON cust.rut = ent.rut
     LEFT JOIN common.entity_addresses AS addr
            ON ent.rut = addr.entity
     LEFT JOIN meta.geo_regions AS reg
            ON addr.region = reg.iso
    ;)"};


static const std::string select_CustomerInformation_q{
    R"(
        SELECT ent.razon_social AS name,
               ent.giro         AS activity,
               addr.address     AS address,
               addr.city        AS city,
               addr.comune      AS comune
          FROM sales.customers AS cust
     LEFT JOIN common.entities AS ent
            ON cust.rut = ent.rut
     LEFT JOIN common.entity_addresses AS addr
            ON cust.rut = addr.entity
         WHERE cust.rut = :cust_rut
    ;)"};


static const std::string select_products_q{
    R"(
        SELECT product.id         AS id,
               product.ordinal    AS ordinal,
               product.descriptor AS descriptor,
               prices.price       AS price
          FROM sales.products AS product
     LEFT JOIN sales.prices   AS prices
            ON product.id = prices.idProduct
         WHERE product.type = :type
           AND prices.company = :company
           AND prices.branch  = :branch
    ;)"};


static const std::string select_last_transactions_q{
    R"(
        SELECT id
          FROM common.transactions
      ORDER BY opened  DESC
         LIMIT 1
    ;)"};


static const std::string select_salesman_q{
    R"(
        SELECT ent.rut          AS rut,
               ent.razon_social AS name
          FROM common.entities AS ent
     LEFT JOIN sales.salesmen AS salesmen
            ON salesmen.rut = ent.rut
    ;)"};


static const std::string select_filter_by_salesman_q{
    R"(
        SELECT ent.razon_social AS name
          FROM common.entities AS ent
     LEFT JOIN sales.salesmen AS sal
            ON sal.rut = ent.rut
         WHERE sal.rut = :sal_rut
    ;)"};


static const std::string select_filter_debts_by_customer_q{
    R"(
        SELECT doc_created,
               doc_company,
               doc_branch,
               doc_id,
               doc_type,
               doc_customer,
               trade_name,
               customer_address,
               city,
               salesman,
               pay_amount,
               doc_total,
               remaining
          FROM sales.view_list_debts
         WHERE doc_customer = :customer
           AND remaining > 0
    ;)"};


static const std::string select_company_q{
    R"(
        SELECT rut
          FROM meta.companies
         WHERE rut = :company
    ;)"};


static const std::string select_branch_q{
    R"(
        SELECT branch
          FROM meta.company_branches
         WHERE company = :company
           AND branch  = :branch
    )"};


static const std::string check_salesman_q{
    R"(
        SELECT rut
          FROM sales.salesmen
         WHERE rut = :salesman
    ;)"};

static const std::string check_company_name_q{
    R"(
        SELECT identifier
          FROM meta.companies
         WHERE rut        = :company_rut
           AND identifier = :company_identifier
    ;)"};

static const std::string check_company_address_q{
    R"(
        SELECT address
          FROM meta.company_branches
         WHERE company = :company_rut
           AND branch  = :company_branch
           AND address = :company_address
    ;)"};


static const std::string select_filter_debts_by_salesman_q{
    R"(
        SELECT doc_created,
               doc_company,
               doc_branch,
               doc_id,
               doc_type,
               doc_customer,
               trade_name,
               customer_address,
               city,
               salesman,
               pay_amount,
               doc_total,
               remaining
          FROM sales.view_list_debts
         WHERE salesman = :salesman
           AND remaining > 0
    ;)"};


static const std::string select_Info_Customer_q{
    R"(
        SELECT cust.rut           AS customer_rut,
               ent.razon_social   AS customer_trade_name,
               add.address        AS customer_address,
               add.comune         AS customer_commune,
               add.city           AS customer_city,
               ent.fono           AS customer_fono,
               ent.movil          AS customer_movil,
               ent.email          AS customer_email,
               ent.giro           AS customer_commercial_business,
               cust.credit        AS customer_credit_used,
               cust.credit_backed AS customer_credit_backed
          FROM sales.customers AS cust
     LEFT JOIN common.entities AS ent
            ON ent.rut = cust.rut
     LEFT JOIN common.entity_addresses AS add
            ON add.entity = cust.rut
           AND add.entity = ent.rut
         WHERE cust.rut = :rut
    ;)"};


static const std::string select_docs_unaccounted{
    R"(
        SELECT doc_created,
               doc_company,
               doc_branch,
               doc_id,
               doc_type,
               doc_customer,
               trade_name,
               customer_address,
               city,
               salesman,
               pay_amount,
               doc_total,
               remaining
          FROM sales.view_list_debts
         WHERE doc_customer =:customer
           AND doc_created =:date
    ;)"};


static const std::string select_filter_branch_by_rut_q{
    R"(
        SELECT branch AS nameBranches
          FROM meta.company_branches
         WHERE company = :company
    ;)"};


static const std::string select_docs_unaccounted_q{
    R"(
        SELECT DATE(created),
               doc_id,
               doc_type,
               pay_type,
               doc_total,
               unacconunted
          FROM sales.view_unaccounted
         WHERE pay_rutcompany = :company
           AND DATE(created) BETWEEN :dateinit AND :datefinish
    ;)"};


static const std::string select_bank_q{
    R"(
        SELECT iban,
               number,
               name
          FROM meta.banks
    ;)"};


static const std::string select_UnpaidDocuments_q{
    R"(
        SELECT *
          FROM (
                SELECT docs.doc_type           AS doc_type,
                       docs.doc_branch         AS doc_branch,
                       docs.doc_company        AS doc_company,
                       docs.doc_customer       AS doc_customer,
                       docs.doc_id             AS doc_id,
                       DATE(docs.doc_created)  AS doc_created,
                       docs.doc_total          AS doc_total,
                       (
                        SELECT
                               SUM(amount_paid)
                          FROM sales.view_documents_unpaid
                         WHERE doc_id      = docs.doc_id
                           AND doc_company = docs.doc_company
                       ) AS amount_paid,
                       (
                        SELECT
                               total
                          FROM sales.documents
                         WHERE doc_id = docs.doc_id
                           AND doc_company = docs.doc_company
                       ) -
                       (
                        SELECT
                               SUM(amount)
                          FROM sales.payments_to_documents
                         WHERE doc_id = docs.doc_id
                           AND doc_company = docs.doc_company
                       )
                       AS amount_remainder
                  FROM sales.view_documents_unpaid AS docs
              GROUP BY docs.doc_type, docs.doc_branch,  docs.doc_company, docs.doc_customer,
                       docs.doc_id,   docs.doc_created, docs.doc_total,   docs.amount_paid,
                       docs.amount_remainder
            ) AS subq
        WHERE subq.doc_customer = :customer
          AND subq.doc_branch   = :branch
          AND subq.doc_company  = :company
          AND subq.amount_paid < subq.doc_total
    ;)"};


static const std::string select_documents_paid(
    R"(
        SELECT docs_paid.doc_type                 AS doc_type,
               docs_paid.doc_id                   AS doc_id,
               docs_paid.pay_type                 AS pay_type,
               docs_paid.doc_total                AS doc_total,
               docs_paid.pay_amount               AS pay_amount,
               docs_paid.meta_bank                AS name_bank,
               docs_paid.pay_cheque_number_cheque AS number_cheque,
               docs_paid.pay_card_transfer_number AS transfer_number,
               DATE(docs_paid.pay_cheque_expiry)  AS cheque_expiry,
               docs_paid.pay_cheque_days          AS cheque_days,
               docs_paid.ch_rejected              AS cheque_rejected
          FROM sales.view_documents_paid AS docs_paid
         WHERE docs_paid.doc_id = :doc_id
    ;)");


static const std::string select_doc_dataCustomer_q{
    R"(
        SELECT doc.doc_type       AS doc_type,
               doc.doc_id         AS doc_id,
               DATE(doc.created)  AS doc_created,
               doc.customer       AS doc_customer,
               doc.customer_addr  AS doc_customer_addr,
               ent.razon_social   AS ent_trade_name,
               ent.giro           AS ent_commercial_business,
               add.comune         AS add_comune,
               add.city           AS add_city,
               doc.discount       AS doc_discount,
               doc.discounted     AS doc_discounted,
               doc.net            AS doc_net,
               doc.tax_vat_rate   AS doc_tax_vat_rate,
               doc.tax_vat        AS doc_tax_vat,
               doc.total          AS doc_total
          FROM sales.documents AS doc
     LEFT JOIN common.entities AS ent
            ON doc.customer = ent.rut
    LEFT JOIN common.entity_addresses AS add
            ON doc.customer = add.entity
           AND ent.rut      = add.entity
         WHERE doc.doc_id   = :doc_id
           AND doc.doc_type = :doc_type
           AND doc.company  = :doc_company
    )"};

static const std::string select_doc_items_q{
    R"(
        SELECT pro.descriptor               AS descriptor,
               itm.price                    AS price,
               itm.quantity                 AS quantity,
               itm.discount                 AS discount,
               itm.discounted               AS discounted,
               (itm.total + itm.discounted) AS total_with_dcto,
               itm.total                    AS total
          FROM sales.document_items AS itm
     LEFT JOIN sales.documents AS doc
            ON doc.doc_id   = itm.doc_id
           AND doc.doc_type = itm.doc_type
           AND doc.company  = itm.company
     LEFT JOIN sales.products AS pro
            ON itm.product  = pro.id
         WHERE itm.doc_id   = :doc_id
           AND itm.doc_type = :doc_type
           AND itm.company  = :company
    )"};

static const std::string select_payments_to_document_q{
    R"(
        SELECT pay.id              AS pay_id,
               pay.type            AS pay_type,
               pay.cash            AS pay_cash,
               pay.amount          AS pay_amount,
               bank.name           AS name_bank,
               ch.number           AS ch_number,
               ch.days             AS ch_days,
               DATE(ch.expiry)     AS ch_date_expiry,
               crd.transfer_number AS crd_transfer_number
          FROM sales.payments_to_documents AS ptd
     LEFT JOIN sales.payments AS pay
            ON ptd.pay_id       = pay.id
           AND ptd.pay_company  = pay.company
           AND ptd.pay_customer = pay.customer
     LEFT JOIN sales.payments_cheque AS ch
            ON ptd.pay_id       = ch.id
           AND ptd.pay_company  = ch.company
           AND ptd.pay_customer = ch.customer
     LEFT JOIN sales.payments_card AS crd
            ON ptd.pay_id       = crd.id
           AND ptd.pay_company  = crd.company
           AND ptd.pay_customer = crd.customer
     LEFT JOIN meta.banks AS bank
            ON ch.bank = bank.iban
         WHERE ptd.doc_id      = :doc_id
           AND ptd.doc_type    = :doc_type
           AND ptd.doc_company = :company
    )"};


static const std::string select_last_payment_q{
    R"(
        SELECT MAX(id) AS id
          FROM sales.payments
         WHERE company = :company
    ;)"};


static const std::string select_pay_id_paymentsdocuments_q{
    R"(
        SELECT
               pay_id
          FROM sales.payments_to_documents
         WHERE doc_id = :doc_id
    ;)"};


static const std::string select_idProduct_q{
    R"(
        SELECT id
          FROM sales.products
         WHERE descriptor = :descriptor
    ;)"};
}
}