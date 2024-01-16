#include <iostream>
#include <string>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <Windows.h>


class Book;
class Stock;
class Sale;
class Shop;

class Publisher
{
public:
    std::string name = "";
    Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;


    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
    }
};


class Shop
{
public:
    std::string name = "";
    Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stock;


    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, name, "name");
        Wt::Dbo::hasMany(a, stock, Wt::Dbo::ManyToOne, "shop");
    }
};



class Book
{
public:
    std::string title = "";
    Wt::Dbo::ptr<Publisher> publisher;


    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, title, "title");
        Wt::Dbo::belongsTo(a, publisher, "publisher");
    }
};


class Stock
{
public:
    int count;
    Wt::Dbo::ptr<Shop> shop;
    Wt::Dbo::ptr<Book> book;
    Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;


    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::belongsTo(a, shop, "shop");
        Wt::Dbo::belongsTo(a, book, "book");
        Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
    }
};


class Sale
{
public:
    int price;
    int count;
    std::string date_sale = "";
    Wt::Dbo::ptr<Stock> stock;


    template<typename Action>
    void persist(Action& a)
    {
        Wt::Dbo::field(a, price, "ptice");
        Wt::Dbo::field(a, count, "count");
        Wt::Dbo::field(a, date_sale, "date_sale");
        Wt::Dbo::belongsTo(a, stock, "stock");
    }
};



int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    try
    {
        std::string connectionString =
            "host=localhost "
            "port=5432 "
            "dbname=test "
            "user=postgres "
            "password=7SQL798";

        auto conn = std::make_unique<Wt::Dbo::backend::Postgres>(connectionString);

        Wt::Dbo::Session session;
        session.setConnection(std::move(conn));
        session.mapClass<Book>("book");
        session.mapClass<Publisher>("publisher");
        session.mapClass<Shop>("shop");
        session.mapClass<Stock>("stock");
        session.mapClass<Sale>("sale");

        try
        {
            session.createTables();
        }
        catch (const Wt::Dbo::Exception& e)
        {
            std::cout << "Tables already exist" << std::endl;
        }     

        //////////////////////         ДОБАВЛЕНИЕ ЗАПИСЕЙ В ТАБЛИЦЫ       ///////////////////////////////// 
        Wt::Dbo::Transaction transaction{ session };

        std::unique_ptr<Publisher> publisher{ new Publisher() };
        publisher->name = "Joe";
        session.add(std::move(publisher));
        //Wt::Dbo::ptr<Publisher> publisherPtr = session.add(std::move(publisher));
        //std::cout << "Name = " << publisherPtr->name;


        std::unique_ptr<Book> book{ new Book() };
        book->title = "Joe's Life";
        session.add(std::move(book));
        Wt::Dbo::ptr<Book> bookPtr = session.add(std::move(book));
        std::cout << "Title = " << bookPtr->title;


        std::unique_ptr<Shop> shop{ new Shop() };
        shop->name = "The best shop";
        session.add(std::move(shop));
        //Wt::Dbo::ptr<Shop> shopPtr = session.add(std::move(shop));
        //std::cout << "Name = " << shopPtr->name;


        std::unique_ptr<Stock> stock{ new Stock() };
        stock->count = 12;
        session.add(std::move(stock));
        //Wt::Dbo::ptr<Stock> stockPtr = session.add(std::move(stock));
        //std::cout << "Count = " << stockPtr->count;


        std::unique_ptr<Sale> sale{ new Sale() };
        sale->price = 455;
        sale->count = 13;
        sale->date_sale = "2024-10-17";
        session.add(std::move(sale));
        //Wt::Dbo::ptr<Sale> salePtr = session.add(std::move(sale));
        //std::cout << "price = " << salePtr->price;

        transaction.commit();
        ///////////////////////////////////////////////////////


        //////////// ПОЛУЧЕНИЕ ДАННЫХ ////////////////////////
        Wt::Dbo::Transaction transactionn{ session };
        Wt::Dbo::collection<Wt::Dbo::ptr<Publisher>> publ = session.find<Publisher>();
        for (auto itr = publ.begin(); itr != publ.end(); itr++)
        {
            std::cout << (*itr)->name << std::endl;
        }


        //////////////////////////////////////////////////////


    }
    catch (const Wt::Dbo::Exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}




/*

using ResultType = std::tuple<Wt::Dbo::ptr<Stock>, Wt::Dbo::ptr<Book>>;

ResultType query = session.query<ResultType>("select stock, book from stock").join<Book>("book", "book.id = stock.book_id").limit(1);

std::cout << std::get<0>(query)->shop->name << " " << std::get<1>(query)->title << std::endl;
}
else
{
std::cout << "NOT FOUND" << std::endl;
}
*/