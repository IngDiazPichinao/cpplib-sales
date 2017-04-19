//
//
//
#pragma once

#include <map>


namespace cns {
namespace sales {


enum class ProductType
{
    Unknown,  // error default

    Timber,
    Flour
};


enum class HeadModels
{
    RUT,
    Name,
    Activity,
    Address,
    City,
    Region,
    Code,
    Description,
    Price,
    Stock,
    Quantity,
    Discount,
    ValUnDcto,
    AmountDcto,
    ValWithDcto,
    Delete,
    PaymentType,
    Amount,
    Cheque,
    Account,
    Transfer,
    Bank,
    DateExpiry,
    Days,
    PaymentDocument,
    Document,
    AmountTotal,
    Payment,
    StatusCheque,
    Date,
    Remaining,
    Company,
    Branch,
    Customer,
    TradeName,
    SalesMan,
    Accounting
};

enum class PaymentType : int16_t
{
    Unknown = 0,

    Cash   = 1,
    Cheque = 2,
    Card   = 3
};


enum class DocumentType : int16_t
{
    Unknown = 0,  // error default

    Factura                           = 30,   // FV,
    FacturaElectronica                = 33,   // FVE,
    FacturaExenta                     = 34,   // FEE,
    Boleta                            = 35,   // BV,
    BoletaElectronica                 = 39,   // BVE,
    FacturaCompraElectronica          = 46,   // FCE,
    GuiaDespacho                      = 50,   // GD,
    GuiaDespachoElectronica           = 52,   // GDE,
    NotaDebito                        = 55,   // ND,
    NotaDebitoElectronica             = 56,   // NDE,
    NotaCredito                       = 60,   // NC,
    NotaCreditoElectronica            = 61,   // NVE,
    NotaDebitoExportacionElectronica  = 111,  // NDEE, export
    NotaCreditoExportacionElectronica = 112   // NCEE export
};


enum class UnitType
{
    Unknown,  // error default

    Units,  // == quantity
    Kilogram,
    Inches  // this one is crooked, not quite sure of it either at this point (check git-blame on
            // this line to see when this was)
};


enum class TaxType
{
    IVA,  // VAT

    // Forwards
    IHA,  // Flours

    // Retentions
    IRT,  // Full retention
    ITR   // Wheats

    /* ... */
};


enum class TaxForesign  // foresign of the taxation, relative to document total
{
    Plus,  // gets added on top of total (you Cash, in the tax right away) [customer hands over the
           // tax to you together with totals payment]
    Minus  // gets subtracted from total (you dont pay out tax to the provider) [provider
           // relinquishes tax to you deducting it from totals]
};

struct DocTypeName
{
    std::string name;
    std::string accr;
};


// clang-format off
// Translation Maps - std::string
static const std::map<ProductType, std::string> product_type_str
{
    {ProductType::Unknown, "Unknown"},
    {ProductType::Timber,  "Timber"},
    {ProductType::Flour,   "Flour"}
};

//
static const std::map<ProductType, std::string> product_type_sql
{
    {ProductType::Unknown, "NULL"},
    {ProductType::Timber,  "timbers"},
    {ProductType::Flour,   "flours"}
};


static std::map<HeadModels, std::string> translate_models
{
    {HeadModels::RUT,             "RUT"              },
    {HeadModels::Name,            "Nombre"           },
    {HeadModels::Activity,        "Rol"              },
    {HeadModels::Address,         "Direccion"        },
    {HeadModels::City,            "Ciudad"           },
    {HeadModels::Region,          "Region"           },
    {HeadModels::Code,            "Codigo"           },
    {HeadModels::Description,     "Descripcion"      },
    {HeadModels::Price,           "Precio"           },
    {HeadModels::Stock,           "Stock"            },
    {HeadModels::Quantity,        "Cantidad"         },
    {HeadModels::Discount,        "Dscto [%]"        },
    {HeadModels::ValUnDcto,       "Valor S/Dcto [$]" },
    {HeadModels::AmountDcto,      "Monto Dcto"       },
    {HeadModels::ValWithDcto,     "Valor C/Dcto [$]" },
    {HeadModels::Delete,          "A. Producto"      },
    {HeadModels::PaymentType,     "Tipo Pago"        },
    {HeadModels::Amount,          "Monto"            },
    {HeadModels::Cheque,          "N° Cheque"        },
    {HeadModels::Account,         "Cuenta"           },
    {HeadModels::Transfer,        "N°. Transferencia"},
    {HeadModels::Bank,            "Banco"            },
    {HeadModels::DateExpiry,      "Ven."             },
    {HeadModels::Days,            "Dias"             },
    {HeadModels::PaymentDocument, "Tipo Doc"         },
    {HeadModels::Document,        "N° Documento"     },
    {HeadModels::AmountTotal,     "Total"            },
    {HeadModels::Payment,         "Abono"            },
    {HeadModels::StatusCheque,    "Cq. Estado"       },
    {HeadModels::Date,            "Fecha"            },
    {HeadModels::Remaining,       "Saldo"            },
    {HeadModels::Company,         "Rut/Compañia"     },
    {HeadModels::Branch,          "Sucursal"         },
    {HeadModels::Customer,        "Cliente"          },
    {HeadModels::TradeName,       "R. Social"        },
    {HeadModels::SalesMan,        "Vendedor"         },
    {HeadModels::Accounting,      "Contabilizado"    }

};


static std::map<DocumentType, DocTypeName> TranslateDocumentType
{
    {DocumentType::Factura,                           {"(FV)   Factura",                              "FV"  }},
    {DocumentType::FacturaElectronica,                {"(FVE)  Factura Electronica",                  "FVE" }},
    {DocumentType::FacturaExenta,                     {"(FE)   Factura Exenta",                       "FE"  }},
    {DocumentType::Boleta,                            {"(BV)   Boleta",                               "BV"  }},
    {DocumentType::BoletaElectronica,                 {"(BVE)  Boleta Electronica",                   "BVE" }},
    {DocumentType::FacturaCompraElectronica,          {"(FCE)  Factura Compra Electronica",           "FCE" }},
    {DocumentType::GuiaDespacho,                      {"(GD)   Guia Despacho",                        "GD"  }},
    {DocumentType::GuiaDespachoElectronica,           {"(GDE)  Guia Despacho Electronica",            "GDE" }},
    {DocumentType::NotaDebito,                        {"(ND)   Nota Debito",                          "ND"  }},
    {DocumentType::NotaDebitoElectronica,             {"(NDE)  Nota Debito Electronica",              "NDE" }},
    {DocumentType::NotaCredito,                       {"(NC)   Nota Credito",                         "NC"  }},
    {DocumentType::NotaCreditoElectronica,            {"(NCE)  Nota Credito Electronica",             "NCE" }},
    {DocumentType::NotaDebitoExportacionElectronica,  {"(NDEE) Nota Debito Exportacion Electronica",  "NDEE"}},
    {DocumentType::NotaCreditoExportacionElectronica, {"(NCEE) Nota Credito Exportacion Electronica", "NCEE"}}
};


static std::map<PaymentType, std::string> TranslatePaymentType
{
    {PaymentType::Cash,   "Efectivo "},
    {PaymentType::Cheque, "Cheque   "},
    {PaymentType::Card,   "Credito  "}
};

// clang-format on

}  // sales
}  // cns
