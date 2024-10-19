#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<string.h>
#include<conio.h>
#include<cstdlib>
#include<cstdio>
#include<sstream>

using namespace std;


char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "AK1656ak612004";

int qstate;
MYSQL mysql,* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class database_connection
{	
	public :
		static void toconnect()
		{
			if(!(conn = mysql_init(0)))
				 {
				 	cout << "ERROR:MySQL object could not be created" << endl;
				 }
			 else
		 		{
		 			if(!mysql_real_connect(conn,HOST,USER,PASS,"oopproj2",3306,NULL,0))
			 		{
			 		cout << "ERROR:DataBase doesn't exist" << endl;
			 		cout << mysql_error(conn) << endl;
					}
					else
					{
						cout << "database connected to mysql :) "<< endl;	
					}
				}	
		}	
};

void checkError()
{
	if(mysql_ping(conn))
	{
		cout<<"error:impossible to connect"<<endl;
		cout<<mysql_error(conn)<<endl;
	}
}

class signUp{
	public :
    char name[50], userName[50], emailID[30],password[50];
    int AorC;
   int mobileNo;
    char getSignUpData(){
        cout << "Hii there!! " << endl;

        cout << "Enter your name : \n";
        cin >> name ;
    
        try{
            cout << "Enter your mobile number : \n";
            cin >> mobileNo; 
            
            if(mobileNo < 1000000000 || mobileNo > 9999999999)
            throw mobileNo;

            cout << "Enter a username : \n";
            cin >> userName;
               
            cout << "Enter the password (Remember this password) : \n";
            cin >> password;
            
            cout << "Enter your Email ID : \n";
            cin >> emailID;

            cout << "1->Are u a customer/ 2->Want to be a organiser: \n";
            cin >>  AorC;

            string sentence_aux ;
            char* consult;
			char* sentence;
			int nQueryState = 0;
			
            switch(AorC)
            {
            	
            	case 2:
            		
					sentence_aux="INSERT INTO organiser(org_Name,org_Ph_No,org_EmailId,No_of_events,Range_of_cost,Location,Experience_in_this_sector,USERNAME,PASSWORD) VALUES('%s','%d','%s','%d','%d','%s','%d','%s','%s')";
            		sentence=new char[sentence_aux.length()+1];
					strcpy(sentence,sentence_aux.c_str());
					
					consult=new char[strlen(sentence)+strlen(name)+sizeof(long long int)+strlen(userName)+strlen(password)+strlen(emailID)];
					sprintf(consult,sentence,name,mobileNo,userName,password,emailID);
					
					cout << "Data added successfully"<< endl;

					checkError();
					
					if(mysql_query(conn,consult)){
						cout<<"error:"<<mysql_error(conn)<<endl;
						rewind(stdin);
						getchar();
					}
					else{
						cout<<"Signed Up as Organiser"<<endl;
					}
					
					break;

            		
	            case 1:
					sentence_aux="INSERT INTO customer(NAME,Ph_No,User_Name,Password,EmailId) VALUES('%s','%llu','%s','%s','%s')";
            		sentence=new char[sentence_aux.length()+1];
					strcpy(sentence,sentence_aux.c_str());
					
					
					consult=new char[strlen(sentence)+strlen(name)+sizeof(long long int)+strlen(userName)+strlen(password)+strlen(emailID)];
					sprintf(consult,sentence,name,mobileNo,userName,password,emailID);           		

					if(mysql_query(conn,consult)){
						cout<<"error:"<<mysql_error(conn)<<endl;
						rewind(stdin);
						getchar();
					}
					else{
						cout<<"Signed Up as a CUSTOMER"<<endl;
					} 
	            	break;
	            	
	            default:
	            		cout << "Give an appropriate 1/2 input" << endl;
			}
        }

        catch(long long int num)
        {
            cout << "The mobile number that you have entered " << num << " is invalid. Kindly check it again. \n";
        }
        
      //  return AorC;
    }
    
};

class checkCCredentials
{
    public:
    string userCheck;
    string passCheck;
    int checkData1()
    {
        cout << "Hii welcome again !! " << endl;
        cout << "Enter your username : \n";
        cin >> userCheck;

        cout << "Enter the password :\n";
        cin >> passCheck;
        
        string sentence_aux1 = "SELECT password FROM customer WHERE userName = '" +userCheck + "' AND password= '" +passCheck + "'";
        
	    const char* qn = sentence_aux1.c_str();
	    qstate = mysql_query(conn, qn);	

	   // cout << qstate << "\n";
	  
		if(!qstate)
		{	
			res = mysql_store_result(conn);	
			  int c; 			
	        while(row = mysql_fetch_row(res))
	        {
	        	cout << "The password you entered " << row[0] << "does match ." << endl;
				return 1;	        	
	    	}
	    		
		  }
		                                 
		if(qstate)
		{
			cout << "Query Execution Problem : " << mysql_errno(conn) << endl;
		}
		
		return 0;
	}
};


class checkOCredentials
{
    public:
    string checkUser;
    string checkPass;
    int checkData2()
    {
        cout << "Hii welcome again !! " << endl;
        cout << "Enter your username : \n";
        cin >> checkUser;

        cout << "Enter the password :\n";
        cin >> checkPass;
        
        string sentence_aux1 = "SELECT organiserPassword FROM organiser WHERE organiserUserName = '" +checkUser + "' AND organiserPassword= '" +checkPass + "'";
        
	    const char* qn = sentence_aux1.c_str();
	    qstate = mysql_query(conn, qn);	

	   // cout << qstate << "\n";
		if(!qstate)
		{	
			res = mysql_store_result(conn);	
			    			
	        while(row = mysql_fetch_row(res))
	        {
	        	cout << "The password you entered " << row[0] << "does match ." << endl;
				return 1;	        	
	    	}
	    	
		}                                 
		if(qstate)
		{
			cout << "Query Execution Problem : " << mysql_errno(conn) << endl;
		}
		
		return 0;
	}
};



int main(){

    //
    system("COLOR 0A");
        int i ; 
	    cout << "\t \t \t 1-> Property Managament System " << endl 
	  	<< "\t \t \t 2->Event Managament System " ;
	  	cout<<"\n \t \t enter ur choice: ";
	  	cin >> i ;
	  	
	  	if(i ==2 ){
	getch();
	system("cls");
	system("COLOR 0E");
	
	cout<<"\n \n \n \n \n \n \n \n "<< endl;
	cout << "\t \t \t Welcome to Event  Managament \t \t \t" ;
	
	
	cout<<"\n \n \n \n \n \n \n \n \n \n \n \n	 \n \n \n \n  " <<endl; 
	cout<<"Enter any key to continue................................"<<endl;
	
	
	
     getch();
	system("cls");
		system("COLOR 0A");
        int choice;
        cout<<"*********\n\n\n";
        cout<<"                      Welcome to login page                               \n\n";
        cout<<"***        MENU        *****\n\n";
        cout<<"1.SIGN UP"<<endl;
        cout<<"2.SIGN IN (ALREADY EXISTED ACCOUNT)"<<endl;
        cout<<"3.PASSWORD"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"\nEnter your choice :";
        cin>>choice;
        cout<<endl;
        char exitentry;

	bool signUpFlag = true;
	int signUpChoice;
	
	database_connection::toconnect();   // static void can be called without using object ..
		  
	
	while(signUpFlag)
	{
		
		
	  switch(choice)
        {
                case 1:
                        signUp obj;
		                obj.getSignUpData();
		                break;
                case 2: 
                        int chi;
                        cout<<"Organiser->1/customer->2"<<endl;
                        cin>>chi;
                        if(chi==1){
						
                	    checkOCredentials obj1;
                        obj1.checkData2();
                        }
                        else{
                        checkCCredentials obj2;
                        obj2.checkData1();	
						}
                        break;
               
               
               
                        system("cls");
                        cout<<"You've made a mistake in registering  , give it a try again\n"<<endl; 
                        
        
   
    }
	
	    cout <<"Want to sign in again ? " << endl;
		cout << "1.YES \n2.NO\n" ;
		cin >> signUpChoice;
		
		switch(signUpChoice)
		{
			case 2:
				signUpFlag = false;	
		}
	}

}
  
  if(i == 1 ){
	
	getch();
	system("cls");
	
	system("COLOR 0E");
	
	cout<<"\n \n \n \n \n \n \n \n "<< endl;
	cout << "\t \t \t Welcome to property Managament \t \t \t" ;
	
	
	cout<<"\n \n \n \n \n \n \n \n \n \n \n \n	 \n \n \n \n  " <<endl; 
	
	cout<<"Enter any key to continue................................"<<endl;
	
	getch();
	system("cls");
		system("COLOR 0A");
        int choice;
        cout<<"*********\n\n\n";
        cout<<"                      Welcome to login page                               \n\n";
        cout<<"***        MENU        *****\n\n";
//        cout<<"1.SIGN UP"<<endl;
//        cout<<"2.SIGN IN (ALREADY EXISTED ACCOUNT)"<<endl;
//        cout<<"3.PASSWORD"<<endl;
//        cout<<"4.Exit"<<endl;
//        cout<<"\nEnter your choice :";
//        cin>>choice;
//        cout<<endl;
//        char exitentry;
//
//	bool signUpFlag = true;
//	int signUpChoice;
//	
//	database_connection::toconnect();   // static void can be called without using object ..
//		  
//	
//	while(signUpFlag)
//	{
//		
//		
//	  switch(choice)
//        {
//                case 1:
//                        signUp obj;
//		                obj.getSignUpData();
//		                break;
//                case 2:
//                	    checkCCredentials obj1;
//                        obj1.checkData1();
//                        break;
//               
//               
//               
//                        system("cls");
//                        cout<<"You've made a mistake in registering  , give it a try again\n"<<endl; 
//                        
//        
//   
//    }
//	
//	    cout <<"Want to sign in again ? " << endl;
//		cout << "1.YES \n2.NO\n" ;
//		cin >> signUpChoice;
//		
//		switch(signUpChoice)
//		{
//			case 2:
//				signUpFlag = false;	
//		}
//	}
//
//}
}
}

