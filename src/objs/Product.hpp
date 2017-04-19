//
//
//
#pragma once

#include "../sql/queries.hpp"
#include "defs.hpp"


#include <cns/currency.hpp>
#include <cns/except.hpp>
#include <cns/pgsql/Connection.hpp>
#include <cns/pgsql/Query.hpp>

#include <memory>
#include <string>
#include <vector>

namespace cns {
namespace sales {


struct tax_t
{
    const std::string code;
    const int8_t      rate;  // %

    int64_t amount = 0;
};


class Product
{
public:
    const int64_t id;

    const int32_t ordinal;
    const int32_t stock;

    const double price;

    const std::string descriptor;

    Product(int64_t id, int32_t ordinal, int32_t stock, double price, const std::string& descriptor);
    ~Product() = default;

    static int64_t idProduct(std::shared_ptr<Connection> conn, const std::string& product);

    static std::vector<Product> querySelectProducts(std::shared_ptr<Connection> conn,
                                                    ProductType                 type,
                                                    int32_t                     company,
                                                    const std::string&          branch);
};


class LoadingProducts
{
public:
    int64_t quantity;
    int64_t price;
    int64_t amount_dcto;
    int64_t total_with_dcto;
    int64_t total_without_dcto;
    int64_t product;

    int16_t discount;

    std::string descriptor;

    LoadingProducts(int64_t            quantity,
                    int64_t            price,
                    int64_t            amount_dcto,
                    int64_t            total_with_dcto,
                    int64_t            total_without_dcto,
                    int64_t            product,
                    int16_t            discount,
                    const std::string& descriptor);
    ~LoadingProducts() = default;
};


}  // sale
}  // cns
