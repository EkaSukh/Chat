
#include "dataBase.h"

//(g++ -I/usr/include/mysql/ -o main sql.cpp -lmysqlclient)
int main()
{
    MYSQL mysql;
    MYSQL_RES* res;
    MYSQL_ROW row; 

    mysql_init(&mysql);

    if (&mysql == NULL)
    {
        std::cout <<"Error:can't create MySQL-descriptor" << std::endl;        
    }

    if(!mysql_real_connect(&mysql, "localhost", "root", "root", "testdb", 0, NULL, 0))
    {
        std::cout << "Error:can't connect to database" << mysql_error(&mysql) << std::endl;
    }
    else
    {
        std::cout << "Success!" << std::endl;
    }

    mysql_set_character_set(&mysql, "utf8");
    std::cout << "connection characters: " << mysql_character_set_name(&mysql) << std::endl;

    //mysql_query(&mysql, "select * from test");
    mysql_query(&mysql, "create table table_formCpp(id int auto_increment primary key, name varchar(255))");
    mysql_query(&mysql, "insert into table_formCpp(id, name) values(default, 'Daria')");
    mysql_query(&mysql, "insert into table_formCpp(id, name) values(default, 'Lyda')");
    mysql_query(&mysql, "insert into table_formCpp(id, name) values(default, 'Nastya')");

    mysql_query(&mysql, "select * from table_formCpp");


    if(res = mysql_store_result(&mysql))
    {
        while(row = mysql_fetch_row(res))
        {
            for(int i= 0;i < mysql_num_fields(res);i++)
            {
                std::cout << row[i] << " ";
            }

            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "Error MySQL number: " << mysql_error(&mysql);
    }

    mysql_close(&mysql);

    system("Pause");
    return 0;
}