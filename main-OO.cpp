//
// Program: C++ Conexion to Mysql for School courses management system.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include <mysql/jdbc.h> 

#include <conio.h>

using namespace std;

// reads in a password without echoing it to the screen
string myget_passwd()
{
	string passwd;
	char ch;
	for (;;)
	{
		ch = 0;
		while (ch == 0)   // Ugh. Microsoft not following standards on getch, so need to keep reading until a new char is typed. 
			ch = _getch();           // get char WITHIOUT echo! (should really be getch(), but MS is not following standrads again.)
		if (ch == 13 || ch == 10) // if done ...
			break;           //  stop reading chars!
		cout << '*';  // dump * to screen
		passwd += ch;   // addd char to password
	}
	cin.sync(); // flush anything else in the buffer (remaining newline)
	cout << endl;  // simulate the enter that the user pressed


	// read until end of line ... so future getlines work. 
	string dummy;
	getline(cin, dummy);

	return passwd;
}

int main()
{

	// strings for mysql hostname, userid, ...
	string db_host;
	string db_port;
	string db_user;
	string db_password;
	string db_name;

	// set up the client (this machine) to use mysql
	cout << "initializing client DB subsystem ..."; cout.flush();
	//mysql_init(&mysql);
	sql::Driver * driver = sql::mysql::get_driver_instance();
	cout << "Done!" << endl;

	// get user credentials and mysql server info
	cout << "Enter MySQL database hostname (or IP adress):";
	getline(cin, db_host); // cin >> db_host;
	
	//get the dtabase por numbr and add it to the host name
	cout << "Enter MySQL database port number (press enter for default):";
	getline(cin, db_port);
	if (db_port.length() > 0)
		db_host += ":" + db_port;
	
	//get user username
	cout << "Enter MySQL database username:";
	cin >> db_user;

	//get user password
	cout << "Enter MySQL database password:";
	db_password = myget_passwd();

	//get database name
	cout << "Enter MySQL database name:";
	getline(cin, db_name);
	

	char prompt;// controller of the switch

	do// ask continiuly for a promp until it is equal to q
	{
		try
		{
			/*make sure the tables we will
		    query to exist before sending a query*/


			/*************************************************************************/
			//make the conecction to the database
			sql::Connection* conn = driver->connect(db_host, db_user, db_password);
			conn->setSchema(db_name);

			// code to create the table we need. 
			string creator = "CREATE TABLE IF NOT EXISTS Students(lname VARCHAR(50), fname VARCHAR(50), phoneNum VARCHAR(50), PRIMARY KEY(lname, fname));";

			//prepare the query
			sql::PreparedStatement* pstmt;
			sql::Statement* stmt = conn->createStatement();

			//execute the query
			stmt->execute(creator);

			//close the conecction with the server
			conn->close();

			/*************************************************************************/
			//make the conecction to the database
			conn = driver->connect(db_host, db_user, db_password);
			conn->setSchema(db_name);

			// code to create the table we need 
			creator = "CREATE TABLE IF NOT EXISTS Courses(prefix VARCHAR(50), number INT, name VARCHAR(50), credits INT, PRIMARY KEY(prefix, number));";
			//prepare the query 
			stmt = conn->createStatement();
			//execute the query
			stmt->execute(creator);
			//close the conecction with the server
			conn->close();

			/*************************************************************************/
			//make the conecction to the database
			conn = driver->connect(db_host, db_user, db_password);
			conn->setSchema(db_name);

			// code to create the table we need 
			creator = "CREATE TABLE IF NOT EXISTS Grades(type VARCHAR(50), value DOUBLE, PRIMARY KEY(type));";
			//prepare the query
			stmt = conn->createStatement();
			//execute the query
			stmt->execute(creator);
			//close the conecction with the server
			conn->close();

			/*************************************************************************/
			//make the conecction to the database
			conn = driver->connect(db_host, db_user, db_password);
			conn->setSchema(db_name);

			// code to create the table we need  
			creator = "CREATE TABLE IF NOT EXISTS Semesters(code VARCHAR(50), year INT, description VARCHAR(50), PRIMARY KEY(code));";
			//prepare the query
			stmt = conn->createStatement();
			//execute the query
			stmt->execute(creator);
			//close the conecction with the server
			conn->close();

			/*************************************************************************/
			//make the conecction to the database
			conn = driver->connect(db_host, db_user, db_password);
			conn->setSchema(db_name);

			// code to create the table we need 
			creator = "CREATE TABLE IF NOT EXISTS CoursesTaken(lname VARCHAR(50), fname VARCHAR(50), prefix VARCHAR(50), number INT, type VARCHAR(50), code VARCHAR(50), PRIMARY KEY(lname, fname, prefix, number, type, code));";
			//prepare the query
			stmt = conn->createStatement();
			//execute the query
			stmt->execute(creator);
			//close the conecction with the server
			conn->close();
			/**************************************************************************/

			cout << ">>> ";
			cin >> prompt;//ask the user	

			switch (prompt)
			{
				char prompt2; //second input
				//if the first input is a 
			case 'a':
				cin >> prompt2;//read second input
				if (prompt2 == 'c') //if second inout is c we will read a new course and add it to the file of possibles courses
				{
					string cname; //course name
					int cnumber; // number
					string ctitle; //title
					int ccredits; //credits

					//read all the inputs
					cin >> cname;
					cin >> cnumber;
					cin >> ctitle;
					cin >> ccredits;

					//connect to the databse
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);

					//prepare the query
					pstmt =
						conn->prepareStatement("INSERT INTO Courses VALUES(?, ?, ?, ?);");
					pstmt->setString(1, cname);
					pstmt->setInt(2, cnumber);
					pstmt->setString(3, ctitle);
					pstmt->setInt(4, ccredits);

					//execute and close connection
					pstmt->execute();
					conn->close();

				}

				else if (prompt2 == 'g') //if second input is g we will read a new grade and add it to the file of possibles grades

				{
					//attributes of a new grade
					string ctype;
					double cgrade;

					//read those attributes from inout
					cin >> ctype;
					cin >> cgrade;

					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare the query
					pstmt =
						conn->prepareStatement("INSERT INTO Grades VALUES(?, ?);");
					pstmt->setString(1, ctype);
					pstmt->setDouble(2, cgrade);
					//execute query and close connection
					pstmt->execute();
					conn->close();


				}

				else if (prompt2 == 'm')//if second inout is m we will read a new semester and add it to the file of possibles semester

				{
					string scode;
					int year;
					string description;
					//read the attributes from inout
					cin >> scode;
					cin >> year;
					cin >> description;
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare the query
					pstmt =
						conn->prepareStatement("INSERT INTO Semesters VALUES(?, ?, ?);");
					pstmt->setString(1, scode);
					pstmt->setInt(2, year);
					pstmt->setString(3, description);
					//execute and close
					pstmt->execute();
					conn->close();


				}

				else if (prompt2 == 's')//if second inout is s we will read a new student and add it to the file of possibles students

				{
					//attributes of an student
					string lName; // last name
					string fName; // first name
					string pNumber; // phone number	

					//read in the attributes
					cin >> lName;
					cin >> fName;
					cin >> pNumber;
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare
					pstmt =
						conn->prepareStatement("INSERT INTO Students VALUES(?, ?, ?);");
					pstmt->setString(1, lName);
					pstmt->setString(2, fName);
					pstmt->setString(3, pNumber);
					//execute and close
					pstmt->execute();
					conn->close();


				}

				else if (prompt2 == 't') //if second input is t we will read a new course and add it to the file of course taken by a student

				{

					//attributes of a taken course
					string lName; //last name of the student
					string fName; // first name of the student
					string cprefix; //course prefix
					int cNumber; // course number
					string cgrade; // course grade
					string semester; // course semester

					//read in the values
					cin >> lName;
					cin >> fName;
					cin >> cprefix;
					cin >> cNumber;
					cin >> cgrade;
					cin >> semester;
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare
					pstmt =
						conn->prepareStatement("INSERT INTO CoursesTaken VALUES(?, ?, ?, ?, ?, ?);");
					pstmt->setString(1, lName);
					pstmt->setString(2, fName);
					pstmt->setString(3, cprefix);
					pstmt->setInt(4, cNumber);
					pstmt->setString(5, cgrade);
					pstmt->setString(6, semester);
					//execute and close
					pstmt->execute();
					conn->close();


				}
				break;

				//if the first input is an l, it means we want to print
			case 'l':
				cin >> prompt2;
				if (prompt2 == 'c') //if second input is a c we want to print all the courses

				{
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare 
					pstmt =
						conn->prepareStatement("Select * FROM Courses;");
					//store the result and execute
					sql::ResultSet* res = pstmt->executeQuery();
					//print the result
					while (res->next())
					{
						cout << res->getString("prefix") << "  " << res->getInt("number") << "  " << res->getString("name") << "  " << res->getInt("credits") << endl;
					}

					conn->close();
				}

				else if (prompt2 == 'g') //if the second input is a g, print all the grade possibilities

				{
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare
					pstmt =
						conn->prepareStatement("Select * FROM Grades;");
					//store the result and execute
					sql::ResultSet* res = pstmt->executeQuery();
					//print the result
					while (res->next())
					{
						cout << res->getString("type") << "  " << res->getDouble("value") << endl;
					}

					conn->close();


				}

				else if (prompt2 == 'm') // if second input is an m will print all the semesters

				{
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare
					pstmt =
						conn->prepareStatement("Select * FROM Semesters;");
					//execute and store the result
					sql::ResultSet* res = pstmt->executeQuery();

					//print the result
					while (res->next())
					{
						cout << res->getString("code") << "  " << res->getInt("year") << "  " << res->getString("description") << endl;
					}
					//close connection
					conn->close();


				}

				else if (prompt2 == 's') //if the second input is an s will print all the students

				{
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare
					pstmt =
						conn->prepareStatement("Select * FROM Students;");
					//execute and store
					sql::ResultSet* res = pstmt->executeQuery();
					
					//print the result
					while (res->next())
					{
						cout << res->getString("lname") << "  " << res->getString("fname") << "  " << res->getString("phoneNum") << endl;
					}
					//close connection
					conn->close();




				}

				else if (prompt2 == 't') //print all the courses taken 

				{
					//connect
					conn = driver->connect(db_host, db_user, db_password);
					conn->setSchema(db_name);
					//prepare
					pstmt =
						conn->prepareStatement("Select * FROM CoursesTaken, Courses WHERE Courses.prefix = CoursesTaken.prefix AND Courses.number = CoursesTaken.number ;");
					//execute and store the result
					sql::ResultSet* res = pstmt->executeQuery();
					//print the result
					while (res->next())
					{
						cout << res->getString("lname") << "  " << res->getString("fname") << "  " << res->getString("prefix") << "  " << res->getString("name") << "  " << res->getInt("number") << "  " << res->getString("type") << "  " << res->getString("code") << endl;
					}
					//close connection
					conn->close();
				}
				break;

			//if the first input is an t followed by the full name of an student we will shows his transcripts
			case 't': 
			{
				string lName; // last name
				string fName; // first name

				//read in the attributes
				cin >> lName;
				cin >> fName;
				//connect
				conn = driver->connect(db_host, db_user, db_password);
				conn->setSchema(db_name);
				//prepare the query to get the courses taken by the student
				pstmt =
					conn->prepareStatement("SELECT * FROM CoursesTaken, Courses, Grades, Semesters WHERE Courses.prefix = CoursesTaken.prefix AND Courses.number = CoursesTaken.number AND lname = ? AND fname = ? AND CoursesTaken.type = Grades.type AND CoursesTaken.code = Semesters.code ORDER BY Semesters.year, Semesters.description DESC ;");
				pstmt->setString(1, lName);
				pstmt->setString(2, fName);
				//execute and store the result
				sql::ResultSet* res = pstmt->executeQuery();

				//variable to store the semester year and description
				string semester = "";
				int year = 0;
				//variable to store the total credits and the credits times the grade value
				int totalcredits = 0;
				double credithours = 0;

				//print the result
				while (res->next())
				{
					//If the semester is different from the previous
					if (semester != res->getString("description") || year != res->getInt("year"))
					{
						//print the semester
						semester = res->getString("description");
						year = res->getInt("year");
						cout << "=========== " << "Semester: " << semester << " " << year << " ============" << endl;
					}
					//store the credits of each course and the grade value
					totalcredits += res->getInt("credits");
					credithours += res->getInt("credits") * res->getDouble("value");
					//print all the courseTaken attributes
					cout << res->getString("prefix") << res->getInt("number") << "  " << res->getString("name") << "  (" << res->getInt("credits") << ")  " << res->getString("type") << endl;
				}

				//print the credits and the gpa
				cout << "STUDENT HOURS COMPLETED: " << totalcredits << endl;
				double gpa;
				if (credithours > 0)
				{
					gpa = credithours / totalcredits;
				}
				else
					gpa = 0;

				cout << "STUDENT GPA: " << gpa << endl;

				conn->close();

			}
				break;

			//if the first input is an d followed by the full name of an student delete all the records
			case 'd':
			{
				string lName; // last name
				string fName; // first name

				//read in the attributes
				cin >> lName;
				cin >> fName;

				//connect
				conn = driver->connect(db_host, db_user, db_password);
				conn->setSchema(db_name);
				//prepare the query
				pstmt =
					conn->prepareStatement("DELETE FROM Students WHERE lname = ? AND fname = ?;");
				pstmt->setString(1, lName);
				pstmt->setString(2, fName);
				//execute and close
				pstmt->execute();
				conn->close();
				//connect again
				conn = driver->connect(db_host, db_user, db_password);
				conn->setSchema(db_name);
				//prepare the query to delete
				pstmt =
					conn->prepareStatement("DELETE FROM CoursesTaken WHERE lname = ? AND fname = ?;");
				pstmt->setString(1, lName);
				pstmt->setString(2, fName);
				//execute and close
				pstmt->execute();
				conn->close();
				//we succesfully deleted at this point
				cout << "Done Deleting" << endl; cout.flush();
				

			}
				break;

			case 'q'://quit
				break;

			default://other values that is not one of the above

				cout << "Invalid Character" << endl;

			}
		}
		catch (sql::SQLException sqle)
		{
			cout << "Exception in SQL: " << sqle.what() << endl;
		}

	} while (prompt != 'q');

	return 0;
}