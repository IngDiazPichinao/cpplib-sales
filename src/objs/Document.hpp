//
//
//

#pragma once

#include <cns/except.hpp>
#include <cns/pgsql/Connection.hpp>

#include "../sql/queries.hpp"
#include "Payment.hpp"
#include "Product.hpp"

#include "PaymentToDocument.hpp"
#include "defs.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cns {
namespace sales {


class DataDocument
{
public:
    const int64_t _doc_id;
    const int64_t _amount_dcto;
    const int64_t _net;
    const int64_t _tax_vat;
    const int64_t _total;

    const int32_t _company;
    const int32_t _customer;
    const int32_t _salesman;

    const int16_t _tax_vat_rate;
    const int16_t _discount;

    const std::string _branch;
    const std::string _doc_type;
    const std::string _doc_created;
    const std::string _customer_addr;
    const std::string _trade_name;
    const std::string _commercial_business;
    const std::string _commune;
    const std::string _city;
    const std::string _sii_xml;
    const std::string _sii_uploaded;
    const std::string _uuid;

    DataDocument(int64_t            doc_id,
                 int64_t            amount_dcto,
                 int64_t            net,
                 int64_t            tax_vat,
                 int64_t            total,
                 int32_t            company,
                 int32_t            customer,
                 int32_t            salesman,
                 int16_t            tax_vat_rate,
                 int16_t            discount,
                 const std::string& branch,
                 const std::string& doc_type,
                 const std::string& doc_created,
                 const std::string& customer_addr,
                 const std::string& trade_name,
                 const std::string& commercial_business,
                 const std::string& commune,
                 const std::string& city,
                 const std::string& sii_xml,
                 const std::string& sii_uploaded,
                 const std::string& uuid);
    ~DataDocument() = default;
};


class Document
{
public:
    int64_t doc_id;
    int64_t doc_total;
    int64_t amount_paid;
    int64_t amount_remainder;
    int64_t new_amount_paying;
    int64_t total_documentUnpaid;

    std::string doc_type;
    std::string doc_created;

    Document(int64_t            doc_id,
             int64_t            doc_total,
             int64_t            amount_paid,
             int64_t            amount_remainder,
             int64_t            new_amount_paying,
             int64_t            total_documentUnpaid,
             const std::string& doc_type,
             const std::string& doc_created);
    ~Document() = default;

    static std::vector<Document> selectUnpaidDocuments(std::shared_ptr<Connection> conn,
                                                       int32_t                     customer,
                                                       int32_t                     company,
                                                       const std::string&          branch);

    static std::vector<DataDocument> read_head(std::shared_ptr<Connection> conn,
                                               int64_t                     doc_id,
                                               const std::string&          doc_type,
                                               int32_t                     company);

    static std::vector<LoadingProducts> read_items(std::shared_ptr<Connection> conn,
                                                   int64_t                     doc_id,
                                                   const std::string&          doc_type,
                                                   int32_t                     company);

    static std::vector<PaymentsData> read_payments(std::shared_ptr<Connection> conn,
                                                   int64_t                     doc_id,
                                                   const std::string&          doc_type,
                                                   int32_t                     company);

    static int64_t subTotal_Items(std::vector<LoadingProducts> items);
    //
    static int32_t document_codeFV(void);
    static int32_t document_codeFVE(void);
    static int32_t document_codeFE(void);
    static int32_t document_codeBV(void);
    static int32_t document_codeBVE(void);
    static int32_t document_codeFCE(void);
    static int32_t document_codeGD(void);
    static int32_t document_codeGDE(void);
    static int32_t document_codeND(void);
    static int32_t document_codeNDE(void);
    static int32_t document_codeNC(void);
    static int32_t document_codeNCE(void);
    static int32_t document_codeNDEE(void);
    static int32_t document_codeNCEE(void);

    static int32_t document_type(int32_t type);

    static const std::string document_nameFV(void);
    static const std::string document_nameFVE(void);
    static const std::string document_nameFE(void);
    static const std::string document_nameBV(void);
    static const std::string document_nameBVE(void);
    static const std::string document_nameFCE(void);
    static const std::string document_nameGD(void);
    static const std::string document_nameGDE(void);
    static const std::string document_nameND(void);
    static const std::string document_nameNDE(void);
    static const std::string document_nameNC(void);
    static const std::string document_nameNCE(void);
    static const std::string document_nameNDEE(void);
    static const std::string document_nameNCEE(void);

    static const std::string document_acronym(int32_t type);


    static void insert(std::shared_ptr<Connection> conn, std::vector<DataDocument> data);
};

}  // end sales
}  // end cns