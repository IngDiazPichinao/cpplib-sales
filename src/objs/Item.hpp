//
// Item Object in a Sale
//
#pragma once

#include <cns/except.hpp>
#include <cns/currency.hpp>
#include <cns/pgsql/Connection.hpp>

#include "Product.hpp"
#include "../sql/queries.hpp"

#include <vector>
#include <utility>
#include <memory>
#include <cmath>
#include <iomanip>

namespace cns {
    namespace sales {


class Item
{
public:
     Item(const Product& product);
    ~Item() = default;

    static int64_t total_items      (int64_t value, int32_t quantity);
    static int64_t amountLessDcto   (int64_t value, float dcto);
    static int64_t discounted       (int64_t total, int64_t amountLessDcto);
    static int16_t percentaje       (float   value);
    static float_t parse_percentaje (int16_t value);

    void setQuantity (int32_t quantity);
    void setDiscount (int8_t  discount);  // % (0 <= discount <= 100)

    int64_t getId (void) const;

    int32_t getOrdinal (void) const;
    int32_t getStock   (void) const;

    double getPrice (void) const;

    std::string        getDescriptor (void) const;
    std::vector<tax_t> getTaxes      (void) const;

    cns::money getDiscount (void);  // $
    cns::money getNet      (void);  // $
    cns::money getVat      (void);  // $



    //&std::vector<tax_t> taxes (void);  // std::vector<tax_t<"IHA", 19%, 16800$>, ...>

    static void insert (std::shared_ptr<Connection> conn, int32_t company, int64_t doc_id, const std::string& doc_type, std::vector<LoadingProducts> items);

    //void commit (std::shared_ptr<Connection> conn);

private:
    const Product& prod;

    int32_t Quantity = 0;  // u
    int8_t  discount = 0;  // %

};


    }  // sale
}  // cns
