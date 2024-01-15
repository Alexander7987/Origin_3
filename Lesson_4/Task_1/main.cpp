#include <iostream>
#include <pqxx/pqxx>
#include <Windows.h>

class MyBase
{
public:
    pqxx::connection c{
        "host='localhost' "
        "port='5432' "
        "dbname='test' "
        "user='postgres' "
        "password='7SQL798' " };  

    void addTable()
    {
        pqxx::work transaction_2{ c };
        transaction_2.exec("CREATE TABLE IF NOT EXISTS ClientInfo (id serial PRIMARY KEY, email text UNIQUE, name text, lastname text)");
        transaction_2.exec("CREATE TABLE IF NOT EXISTS ClientTelephone (id integer references ClientInfo(id), telephone text UNIQUE, constraint ppk UNIQUE (id, telephone))");
        transaction_2.commit();
    }
    
    void addClient()
    {
        pqxx::work transaction_2{ c };
        std::string email;
        std::string name;
        std::string lastname;
        std::cout << "Enter email: ";
        std::cin >> email;
        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "Enter lastname: ";
        std::cin >> lastname;
        std::cout << std::endl;
        transaction_2.exec("INSERT INTO ClientInfo(email, name, lastname) "
            "VALUES ('"+transaction_2.esc(email) + "', '" + transaction_2.esc(name) + "', '" + transaction_2.esc(lastname) + "')");
        transaction_2.commit();
    }
    
    void addTelephone()
    {
        pqxx::work transaction_2{ c };
        std::string id;
        std::string telephone;
        std::cout << "Enter existing Client's id: ";
        std::cin >> id;
        std::cout << "Enter telephone: ";
        std::cin >> telephone;
        std::cout << std::endl;
        transaction_2.exec("INSERT INTO ClientTelephone(id, telephone) "
            "VALUES ('" + transaction_2.esc(id) + "', '" + transaction_2.esc(telephone) + "')");
        transaction_2.commit();
    }
    
    void changeClientInfo()
    {
        pqxx::work transaction_2{ c };
        std::string id;
        std::string email;
        std::string name;
        std::string lastname;
        std::cout << "Enter id Client, you want change his data: ";
        std::cin >> id;
        std::cout << "Enter new email: ";
        std::cin >> email;
        std::cout << "Enter new name: ";
        std::cin >> name;
        std::cout << "Enter new lastname: ";
        std::cin >> lastname;
        std::cout << std::endl;
        transaction_2.exec("UPDATE ClientInfo "
            "SET email = '"+ transaction_2.esc(email) + "', name = '" + transaction_2.esc(name) + "', lastname = '" + transaction_2.esc(lastname) + "' "
            "WHERE id = '" + transaction_2.esc(id) + "'");
        transaction_2.commit();
    } 

    void deleteTelephone()
    {
        pqxx::work transaction_2{ c };
        std::string telephone;
        std::cout << "Enter telephone Client, you want delete: ";
        std::cin >> telephone;
        std::cout << std::endl;
        transaction_2.exec("DELETE FROM ClientTelephone "
            "WHERE telephone = '" + transaction_2.esc(telephone) + "'");
        transaction_2.commit();
    }

    void deleteClient()
    {
        pqxx::work transaction_2{ c };
        std::string id;
        std::string telephone;
        std::cout << "Enter id, you want delete: ";
        std::cin >> id;
        std::cout << std::endl;
        transaction_2.exec("DELETE FROM ClientTelephone "
            "WHERE id = '" + transaction_2.esc(id) + "'");
        transaction_2.exec("DELETE FROM ClientInfo "
            "WHERE id = '" + transaction_2.esc(id) + "'");

        transaction_2.commit();
    }

    void selectClient()
    {
        pqxx::work transaction_1{ c };
        int a;
        std::string id;
        std::string email;
        std::string name;
        std::string lastname;
        std::string telephone;
        std::string answer;
        std::cout << "What do you know about Client? Choose: " << std::endl;
        std::cout << "1.id" << std::endl;
        std::cout << "2.email" << std::endl;
        std::cout << "3.name" << std::endl;
        std::cout << "4.lastname" << std::endl;
        std::cout << "5.telephone" << std::endl;
        std::cin >> a;
        switch (a)
        {
        case 1:
        {
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cout << "Answer: " << std::endl;
            for (auto [email, name, lastname] : transaction_1.query<std::string, std::string, std::string>("SELECT email, name, lastname FROM ClientInfo WHERE id = '" + transaction_1.esc(id) + "'" 
                "LIMIT 1"))
            {
                std::cout << email << " " << name << " " << lastname;
            }
        }
        case 2:
        {
            std::cout << "Enter email: ";
            std::cin >> email;
            std::cout << "Answer: " << std::endl;
            for (auto [email, name, lastname] : transaction_1.query<std::string, std::string, std::string>("SELECT email, name, lastname FROM ClientInfo WHERE email = '" + transaction_1.esc(email) + "'"
                "LIMIT 1"))
            {
                std::cout << email << " " << name << " " << lastname;
            }
        }
        case 3:
        {
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Answer: " << std::endl;
            for (auto [email, name, lastname] : transaction_1.query<std::string, std::string, std::string>("SELECT email, name, lastname FROM ClientInfo WHERE name = '" + transaction_1.esc(name) + "'"
                "LIMIT 1"))
            {
                std::cout << email << " " << name << " " << lastname;
            }
        }
        case 4:
        {
            std::cout << "Enter lastname: ";
            std::cin >> lastname;
            std::cout << "Answer: " << std::endl;
            for (auto [email, name, lastname] : transaction_1.query<std::string, std::string, std::string>("SELECT email, name, lastname FROM ClientInfo WHERE lastname = '" + transaction_1.esc(lastname) + "'"
                "LIMIT 1"))
            {
                std::cout << email << " " << name << " " << lastname;
            }
        }
        case 5:
        {
            std::string temp;
            std::cout << "Enter telephone: ";
            std::cin >> telephone;
            temp = transaction_1.query_value<std::string>("SELECT id FROM ClientTelephone WHERE telephone = '" + transaction_1.esc(telephone) + "'");
            std::cout << "Answer: " << std::endl;
            for (auto [email, name, lastname] : transaction_1.query<std::string, std::string, std::string>("SELECT email, name, lastname FROM ClientInfo WHERE id = '" + transaction_1.esc(temp) + "'"
                "LIMIT 1"))
            {
                std::cout << email << " " << name << " " << lastname;
            }
        }
        }
    }

};


int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    try
    {
        MyBase Base_1;

       // Base_1.addTable();

        //Base_1.addClient();

        //Base_1.addTelephone();

        //Base_1.changeClientInfo();

        //Base_1.deleteTelephone();

        //Base_1.deleteClient();

        Base_1.selectClient();

    }
    catch (const std::exception& e)
    {
        std::cout << "Error. Exception happened: " << e.what() << std::endl;
    }



    return 0;
}