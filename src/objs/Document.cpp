//
//
//

#include "Document.hpp"


namespace cns {
namespace sales {

DataDocument::DataDocument(int64_t            doc_id,
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
                           const std::string& uuid)
    : _doc_id(doc_id)
    , _amount_dcto(amount_dcto)
    , _net(net)
    , _tax_vat(tax_vat)
    , _total(total)
    , _company(company)
    , _customer(customer)
    , _salesman(salesman)
    , _tax_vat_rate(tax_vat_rate)
    , _discount(discount)
    , _branch(branch)
    , _doc_type(doc_type)
    , _doc_created(doc_created)
    , _customer_addr(customer_addr)
    , _trade_name(trade_name)
    , _commercial_business(commercial_business)
    , _commune(commune)
    , _city(city)
    , _sii_xml(sii_xml)
    , _sii_uploaded(sii_uploaded)
    , _uuid(uuid)
{
}


Document::Document(int64_t            doc_id,
                   int64_t            doc_total,
                   int64_t            amount_paid,
                   int64_t            amount_remainder,
                   int64_t            new_amount_paying,
                   int64_t            total_documentUnpaid,
                   const std::string& doc_type,
                   const std::string& doc_created)
    : doc_id(doc_id)
    , doc_total(doc_total)
    , amount_paid(amount_paid)
    , amount_remainder(amount_remainder)
    , new_amount_paying(new_amount_paying)
    , total_documentUnpaid(total_documentUnpaid)
    , doc_type(doc_type)
    , doc_created(doc_created)
{
}


std::vector<Document> Document::selectUnpaidDocuments(std::shared_ptr<Connection> conn,
                                                      int32_t                     customer,
                                                      int32_t                     company,
                                                      const std::string&          branch)
{
    std::vector<Document> document;

    Query query{select_UnpaidDocuments_q};

    query["customer"] << customer;
    query["branch"] << branch;
    query["company"] << company;

    int64_t total_documentUnpaid = 0;
    int64_t doc_id               = 0;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        if (doc_id == 0)
        {
            doc_id = get<int64_t>(row["doc_id"]);

            document.emplace_back(get<int64_t>(row["doc_id"], 0),
                                  get<int64_t>(row["doc_total"], 0),
                                  get<int64_t>(row["amount_paid"], 0),
                                  get<int64_t>(row["amount_remainder"], 0),
                                  get<int64_t>(row["amount_paid"], 0),
                                  total_documentUnpaid += get<int64_t>(row["amount_remainder"], 0),
                                  get<std::string>(row["doc_type"], ""),
                                  get<std::string>(row["doc_created"], ""));
        }

        if (doc_id != get<int64_t>(row["doc_id"]))
        {
            doc_id = get<int64_t>(row["doc_id"]);

            document.emplace_back(get<int64_t>(row["doc_id"], 0),
                                  get<int64_t>(row["doc_total"], 0),
                                  get<int64_t>(row["amount_paid"], 0),
                                  get<int64_t>(row["amount_remainder"], 0),
                                  get<int64_t>(row["amount_paid"], 0),
                                  total_documentUnpaid += get<int64_t>(row["amount_remainder"], 0),
                                  get<std::string>(row["doc_type"], ""),
                                  get<std::string>(row["doc_created"], ""));
        }
    }

    return document;
}


std::vector<DataDocument> Document::read_head(std::shared_ptr<Connection> conn,
                                              int64_t                     doc_id,
                                              const std::string&          doc_type,
                                              int32_t                     company)
{
    std::vector<DataDocument> data;

    Query query{select_doc_dataCustomer_q};
    query["doc_id"] << doc_id;
    query["doc_type"] << doc_type;
    query["doc_company"] << company;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        data.emplace_back(get<int64_t>(row["doc_id"], 0),
                          get<int64_t>(row["doc_discounted"], 0),
                          get<int64_t>(row["doc_net"], 0),
                          get<int64_t>(row["doc_tax_vat"], 0),
                          get<int64_t>(row["doc_total"], 0),
                          0,
                          get<int64_t>(row["doc_customer"], 0),
                          0,
                          get<int16_t>(row["doc_tax_vat_rate"], 0),
                          get<int16_t>(row["doc_discount"], 0),
                          "",
                          get<std::string>(row["doc_type"], ""),
                          get<std::string>(row["doc_created"], ""),
                          get<std::string>(row["doc_customer_addr"], ""),
                          get<std::string>(row["ent_trade_name"], ""),
                          get<std::string>(row["ent_commercial_business"], ""),
                          get<std::string>(row["add_comune"], ""),
                          get<std::string>(row["add_city"], ""),
                          "",
                          "",
                          "");
    }

    return data;
}

std::vector<LoadingProducts> Document::read_items(std::shared_ptr<Connection> conn,
                                                  int64_t                     doc_id,
                                                  const std::string&          doc_type,
                                                  int32_t                     company)
{
    std::vector<LoadingProducts> items;

    Query query{select_doc_items_q};

    query["doc_id"] << doc_id;
    query["doc_type"] << doc_type;
    query["company"] << company;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        items.emplace_back(get<int64_t>(row["quantity"], 0),
                           get<int64_t>(row["price"], 0),
                           get<int64_t>(row["discounted"], 0),
                           get<int64_t>(row["total"], 0),
                           get<int64_t>(row["total_with_dcto"], 0),
                           0,
                           get<int16_t>(row["discount"], 0),
                           get<std::string>(row["descriptor"], ""));
    }

    return items;
}


std::vector<PaymentsData> Document::read_payments(std::shared_ptr<Connection> conn,
                                                  int64_t                     doc_id,
                                                  const std::string&          doc_type,
                                                  int32_t                     company)
{
    std::vector<PaymentsData> payments;

    Query query{select_payments_to_document_q};
    query["doc_id"] << doc_id;
    query["doc_type"] << doc_type;
    query["company"] << company;

    std::shared_ptr<Result> result = conn->execute(query);
    std::vector<Row>        rows   = result->fetchall();

    for (const Row& row : rows)
    {
        const std::string& sql_type = get<std::string>(row["pay_type"]);

        std::string PaymentType = "";

        if (sql_type == Payment::PaymentType_sqlCash())
            PaymentType = Payment::PaymentType_nameCash();

        if (sql_type == Payment::PaymentType_sqlCheque())
            PaymentType = Payment::PaymentType_nameCheque();

        if (sql_type == Payment::PaymentType_sqlCard())
            PaymentType = Payment::PaymentType_nameCard();

        payments.emplace_back(get<int64_t>(row["pay_amount"], 0),
                              get<int64_t>(row["ch_number"], 0),
                              0,
                              get<int64_t>(row["crd_transfer_number"], 0),
                              get<int32_t>(row["ch_days"], 0),
                              PaymentType,
                              get<std::string>(row["name_bank"], ""),
                              get<std::string>(row["ch_date_expiry"], ""));
    }

    return payments;
}


int64_t Document::subTotal_Items(std::vector<LoadingProducts> items)
{
    int64_t subTotal = 0;

    for (auto& data : items)
    {
        subTotal += data.total_with_dcto;
    }

    return subTotal;
}


int32_t Document::document_codeFV(void)
{
    return static_cast<int32_t>(sales::DocumentType::Factura);
}

int32_t Document::document_codeFVE(void)
{
    return static_cast<int32_t>(sales::DocumentType::FacturaElectronica);
}

int32_t Document::document_codeFE(void)
{
    return static_cast<int32_t>(sales::DocumentType::FacturaExenta);
}

int32_t Document::document_codeBV(void)
{
    return static_cast<int32_t>(sales::DocumentType::Boleta);
}

int32_t Document::document_codeBVE(void)
{
    return static_cast<int32_t>(sales::DocumentType::BoletaElectronica);
}

int32_t Document::document_codeFCE(void)
{
    return static_cast<int32_t>(sales::DocumentType::FacturaCompraElectronica);
}

int32_t Document::document_codeGD(void)
{
    return static_cast<int32_t>(sales::DocumentType::GuiaDespacho);
}

int32_t Document::document_codeGDE(void)
{
    return static_cast<int32_t>(sales::DocumentType::GuiaDespachoElectronica);
}

int32_t Document::document_codeND(void)
{
    return static_cast<int32_t>(sales::DocumentType::NotaDebito);
}

int32_t Document::document_codeNDE(void)
{
    return static_cast<int32_t>(sales::DocumentType::NotaDebitoElectronica);
}

int32_t Document::document_codeNC(void)
{
    return static_cast<int32_t>(sales::DocumentType::NotaCredito);
}

int32_t Document::document_codeNCE(void)
{
    return static_cast<int32_t>(sales::DocumentType::NotaCreditoElectronica);
}

int32_t Document::document_codeNDEE(void)
{
    return static_cast<int32_t>(sales::DocumentType::NotaDebitoExportacionElectronica);
}

int32_t Document::document_codeNCEE(void)
{
    return static_cast<int32_t>(sales::DocumentType::NotaCreditoExportacionElectronica);
}

int32_t Document::document_type(int32_t type)
{
    switch (type)
    {
        case 30:
            return static_cast<int32_t>(sales::DocumentType::Factura);
            break;

        case 33:
            return static_cast<int32_t>(sales::DocumentType::FacturaElectronica);
            break;

        case 34:
            return static_cast<int32_t>(sales::DocumentType::FacturaExenta);
            break;

        case 35:
            return static_cast<int32_t>(sales::DocumentType::Boleta);
            break;

        case 39:
            return static_cast<int32_t>(sales::DocumentType::BoletaElectronica);
            break;

        case 46:
            return static_cast<int32_t>(sales::DocumentType::FacturaCompraElectronica);
            break;

        case 50:
            return static_cast<int32_t>(sales::DocumentType::GuiaDespacho);
            break;

        case 52:
            return static_cast<int32_t>(sales::DocumentType::GuiaDespachoElectronica);
            break;

        case 55:
            return static_cast<int32_t>(sales::DocumentType::NotaDebito);
            break;

        case 56:
            return static_cast<int32_t>(sales::DocumentType::NotaDebitoElectronica);
            break;

        case 60:
            return static_cast<int32_t>(sales::DocumentType::NotaCredito);
            break;

        case 61:
            return static_cast<int32_t>(sales::DocumentType::NotaCreditoElectronica);
            break;

        case 111:
            return static_cast<int32_t>(sales::DocumentType::NotaDebitoExportacionElectronica);
            break;

        case 112:
            return static_cast<int32_t>(sales::DocumentType::NotaCreditoExportacionElectronica);
            break;

        default:
            throw cns::Exception("Unsupported type: <" + std::to_string(static_cast<int8_t>(type))
                                 + ">");
            break;
    }
}


const std::string Document::document_nameFV(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::Factura];
    return doc.name;
}

const std::string Document::document_nameFVE(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::FacturaElectronica];
    return doc.name;
}

const std::string Document::document_nameFE(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::FacturaExenta];
    return doc.name;
}

const std::string Document::document_nameBV(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::Boleta];
    return doc.name;
}

const std::string Document::document_nameBVE(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::BoletaElectronica];
    return doc.name;
}

const std::string Document::document_nameFCE(void)
{
    sales::DocTypeName doc
        = sales::TranslateDocumentType[sales::DocumentType::FacturaCompraElectronica];
    return doc.name;
}

const std::string Document::document_nameGD(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::GuiaDespacho];
    return doc.name;
}

const std::string Document::document_nameGDE(void)
{
    sales::DocTypeName doc
        = sales::TranslateDocumentType[sales::DocumentType::GuiaDespachoElectronica];
    return doc.name;
}

const std::string Document::document_nameND(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::NotaDebito];
    return doc.name;
}

const std::string Document::document_nameNDE(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::NotaDebitoElectronica];
    return doc.name;
}

const std::string Document::document_nameNC(void)
{
    sales::DocTypeName doc = sales::TranslateDocumentType[sales::DocumentType::NotaCredito];
    return doc.name;
}

const std::string Document::document_nameNCE(void)
{
    sales::DocTypeName doc
        = sales::TranslateDocumentType[sales::DocumentType::NotaCreditoElectronica];
    return doc.name;
}

const std::string Document::document_nameNDEE(void)
{
    sales::DocTypeName doc
        = sales::TranslateDocumentType[sales::DocumentType::NotaDebitoExportacionElectronica];
    return doc.name;
}

const std::string Document::document_nameNCEE(void)
{
    sales::DocTypeName doc
        = sales::TranslateDocumentType[sales::DocumentType::NotaCreditoExportacionElectronica];
    return doc.name;
}

const std::string Document::document_acronym(int32_t type)
{
    sales::DocTypeName document;

    switch (type)
    {
        case 30:
            document = sales::TranslateDocumentType[sales::DocumentType::Factura];
            return document.accr;
            break;

        case 33:
            document = sales::TranslateDocumentType[sales::DocumentType::FacturaElectronica];
            return document.accr;
            break;

        case 34:
            document = sales::TranslateDocumentType[sales::DocumentType::FacturaExenta];
            return document.accr;
            break;

        case 35:
            document = sales::TranslateDocumentType[sales::DocumentType::Boleta];
            return document.accr;
            break;

        case 39:
            document = sales::TranslateDocumentType[sales::DocumentType::BoletaElectronica];
            return document.accr;
            break;

        case 46:
            document = sales::TranslateDocumentType[sales::DocumentType::FacturaCompraElectronica];
            return document.accr;
            break;

        case 50:
            document = sales::TranslateDocumentType[sales::DocumentType::GuiaDespacho];
            return document.accr;
            break;

        case 52:
            document = sales::TranslateDocumentType[sales::DocumentType::GuiaDespachoElectronica];
            return document.accr;
            break;

        case 55:
            document = sales::TranslateDocumentType[sales::DocumentType::NotaDebito];
            return document.accr;
            break;

        case 56:
            document = sales::TranslateDocumentType[sales::DocumentType::NotaDebitoElectronica];
            return document.accr;
            break;

        case 60:
            document = sales::TranslateDocumentType[sales::DocumentType::NotaCredito];
            return document.accr;
            break;

        case 61:
            document = sales::TranslateDocumentType[sales::DocumentType::NotaCreditoElectronica];
            return document.accr;
            break;

        case 111:
            document
                = sales::TranslateDocumentType[sales::DocumentType::NotaDebitoExportacionElectronica];
            return document.accr;
            break;

        case 112:
            document
                = sales::TranslateDocumentType[sales::DocumentType::NotaCreditoExportacionElectronica];
            return document.accr;
            break;

        default:
            throw cns::Exception("Unsupported type: <" + std::to_string(static_cast<int8_t>(type))
                                 + ">");
            break;
    }
}


void Document::insert(std::shared_ptr<Connection> conn, std::vector<DataDocument> data)
{
    Query query{insert_document_q};

    for (auto& insert : data)
    {
        query["company"] << insert._company;
        query["branch"] << insert._branch;
        query["doc_id"] << insert._doc_id;
        query["doc_type"] << insert._doc_type;
        query["customer"] << insert._customer;
        query["addr"] << insert._customer_addr;
        query["salesman"] << insert._salesman;
        query["discount"] << insert._discount;
        query["amount_dcto"] << insert._amount_dcto;
        query["net"] << insert._net;
        query["dcto"] << insert._tax_vat_rate;
        query["tax_vat"] << insert._tax_vat;
        query["total"] << insert._total;
        query["sii_xml"] << insert._sii_xml;
        query["sii_uploaded"] << insert._sii_uploaded;
        query["uuid"] << insert._uuid;

        std::shared_ptr<Result> result = conn->execute(query);
        result->fetchall();
    }
}


}  // end sales
}  // end cns
