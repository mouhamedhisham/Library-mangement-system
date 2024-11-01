#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int month;
    int year;
} date;

typedef struct
{
    char uname[50];
    char pword[50];
} creds;

typedef struct
{
    char ISBN[20];
    char title[50];
    char aName[50];
    int quantity;
    float price;
    date dop;
} book;

// Edited flag
int edited = 0;

// Global variable for number of books
int nob = 0;

// Global array for books inside the file
book b[200];


//Prompt a Login screen
void login()
{
    //Declaring array of users
    creds u[10];

    //Declaring iteration variable
    int i = 0;

    //Getting the username and passsword from user
    char uname[30];
    char pword[30];
    printf("\nEnter username:");
    gets(uname);
    printf("Enter password:");
    gets(pword);


    //Handling the creds file
    FILE *cfptr;
    cfptr = fopen("credentials.txt","r");
    if(cfptr == NULL)
    {
        printf("Error in the code!");
        exit(1);
    }

    //Getting creds from file to compare to it
    while(!feof(cfptr))
    {
        fscanf(cfptr,"%s",u[i].uname);
        fscanf(cfptr,"%s",u[i].pword);
        i++;
    }

    //Checking the data
    for(int l = 0; l<i; l++)
    {
        if(strcmp(uname,u[l].uname) == 0 && strcmp(pword,u[l].pword)== 0)
        {
            printf("login successful :\)\n");
            fclose(cfptr);
            system("cls");
            load();
            menu();
        }
    }
    printf("Failed to login wrong username or password\n");
    fclose(cfptr);
    init_menu();
}


//Return number of lines in the file
void NOL()
{
    char line[200][200];

    //Handling file
    FILE *fptr;
    fptr = fopen("books.txt", "r");
    if(fptr == NULL)
    {
        printf("Error in the code!");
        exit(1);
    }

    //Getting data from file
    while(!feof(fptr))
    {
        fgets(line[nob], 200, fptr);
        nob++;
    }

    fclose(fptr);
}


//Print available books from the file
void load()
{
    // Call NOL() to get how many books in file
    NOL();

    //Setting iteration variables
    int l;

    //Handling file
    FILE *fptr;
    fptr = fopen("books.txt", "r");
    if(fptr == NULL)
    {
        printf("Error in the code!");
        exit(1);
    }

    for( l =0; l<nob; l++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^,],%d,%f,%d-%d\n", &b[l].ISBN, &b[l].title, &b[l].aName, &b[l].quantity, &b[l].price, &b[l].dop.month, &b[l].dop.year);
    }

}


// Check if year is in the right format
int isvalid_year(char year[])
{
    int i ;
    for(i=0; i<strlen(year); i++)
    {
        if(!(year[i]>='0'&&year[i]<='9'))
            return 0;
    }
    int x =atoi(year);
    if(x>=1&&x<=2022)
        return(1);
    else return 0;
}


// Check if the ISBN is in the right format
int isvalid_ISBN(char ISBN [25])
{
    int i ;
    for(i=0; i<strlen(ISBN); i++)
    {
        if(!(ISBN[i]>='0'&&ISBN[i]<='9'))

            return 0;
    }

    if(strlen(ISBN)==13)
        return(1);
    else return 0;
}


// Check if month is in the right format
int isvalid_Month(char month[])
{
    int i ;
    for(i=0; i<strlen(month); i++)
    {
        if(!(month[i]>='0'&&month[i]<='9'))
            return 0;
    }
    int x =atoi(month);
    if(x>=1&&x<=12)
        return(1);
    else return 0;
}


// Convert month from number to letters
char* month(int m)
{

    // Return the month in letters
    switch(m)
    {
    case 1:
        return "January";
    case 2:
        return "February";
    case 3:
        return "March";
    case 4:
        return "April";
    case 5:
        return "May";
    case 6:
        return "June";
    case 7:
        return "July";
    case 8:
        return "August";
    case 9:
        return "september";
    case 10:
        return "October";
    case 11:
        return "November";
    case 12:
        return "December";
    default:
        return "Wrong Date format";
    }
}


// Search for a specific ISBN and print its data
// Used linear search algorithm
void SEARCH()
{
    // Change edited flag
    edited = 1;

    // Initialize variables
    char S_ISBN[20];
    int flag = 0;
    int l;

    // Check if the ISBN is valid
    do
    {
        printf("\nEnter the book ISBN: ");
        gets(S_ISBN);
        if(!isvalid_ISBN(S_ISBN))
            printf("Wrong ISBN format");

    }
    while(!isvalid_ISBN(S_ISBN));

    // Check if the ISBN exist
    for(l =0; l<nob; l++)
    {
        if(!strcmp(S_ISBN,b[l].ISBN))
        {
            flag = 1;
            break;
        }
    }

    // If ISBN exist print its data if not print not found
    if(flag)
    {
        printf("ISBN: %s\n", b[l].ISBN);
        printf("Title: %s\n", b[l].title);
        printf("Author: %s\n", b[l].aName);
        printf("Quantity: %d\n", b[l].quantity);
        printf("Price: %.2f $\n", b[l].price);
        printf("Published: %s %d\n", month(b[l].dop.month), b[l].dop.year);
        printf("press Enter to continue");
        getchar();
        system("cls");
        return;
    }
    else
    {
        printf("Specified ISBN is not found\n\n");
        printf("press Enter to continue");
        getchar();
        system("cls");
        return;
    }
}


// Search for a certain keyword
// used linear search algorithm
void ADVANCED_SEARCH()
{
    int i;
    int flag=0;

    // Declare a variable to hold the user search key
    char keyword[100];

    // Take th search key from the user
    printf("enter the keyword :");
    gets(keyword);

    printf("Search results:\n\n");

    for (i=0; i<nob; i++)
    {
        if(strstr(b[i].title,keyword)!=NULL)
        {
            flag=1;

            if(flag)
            {
                printf("ISBN: %s\n", b[i].ISBN);
                printf("Title: %s\n", b[i].title);
                printf("Author: %s\n", b[i].aName);
                printf("Quantity: %d\n", b[i].quantity);
                printf("Price: %.2f $\n", b[i].price);
                printf("Published: %s %d\n\n", month(b[i].dop.month), b[i].dop.year);
            }

        }
    }
    if(!flag)
    {
        printf("No results found");
        printf("press Enter to continue");
        getchar();
        system("cls");
        return;
    }
    else
    {
        printf("press Enter to continue");
        getchar();
        system("cls");
    }

}


// Check if the ISBN added already exist
int Exist_ISBN(char ISBN[25])
{
    for(int i = 0; i < nob; i++)
    {
        if(strcmp(ISBN,b[i].ISBN) == 0)
        {
            return 1;
        }
    }
    return 0;
}


// add a new book to the array of books
//return the updated number of books in the array
void ADD()
{
    // Change edited flag
    edited = 1;

    // Declare variables to hold values untill checked
    char month[10], year[10], ISBN[25], title[50], aName[50], quantity[10], price[50];
    int quantity_Num;
    float price_Num;

    // Check if the entered ISBN is valid and if it is already exist if not add it to the array
    do
    {

        printf("\nEnter the ISBN of the new book: ");
        gets(ISBN);

        // If it is in wrong format prompt the user to enter it again
        if(!isvalid_ISBN(ISBN))
        {
            printf("Wrong ISBN format");
            continue;
        }

        // If it already exist prompt the user to enter another one
        if(Exist_ISBN(ISBN))
            printf("This ISBN already exist");

    }
    while(!isvalid_ISBN(ISBN) || Exist_ISBN(ISBN));

    // Copy ISBN value to the array
    strcpy(b[nob].ISBN, ISBN);


    // Hold the title value to check
    do
    {
        printf("Enter the title of the new book: ");
        gets(title);

        if(title[0] == '\0')
            printf("Title cannot be empty\n");

    }
    while(title[0] == '\0');

    // Copy title value to the array
    strcpy(b[nob].title, title);


    // Hold the author name value to check
    do
    {
        printf("Enter the author name of the new book: ");
        gets(aName);

        if(aName[0] == '\0')
            printf("Author name cannot be empty\n");

    }
    while(aName[0] == '\0');

    // Copy author name value to the array
    strcpy(b[nob].aName, aName);


    // Hold the quantity as an string to check
    do
    {
        printf("Enter the quantity of the new book: ");
        gets(quantity);

        // Change quantity to integer to check if right format
        quantity_Num = atoi(quantity);

        if(quantity_Num == 0)
            printf("Wrong quantity format\n");

    }
    while(quantity_Num == 0);

    // Copy quantity value to array
    b[nob].quantity = quantity_Num;

    // Hold the price as an string to check
    do
    {
        printf("Enter the price of the new book: ");
        gets(price);

        price_Num = atof(price);

        if(price_Num == 0)
            printf("Wrong price format\n");

    }
    while(price_Num == 0);

    b[nob].price = price_Num;


    // Check if month is in the right format and add it to the variable
    do
    {
        printf("Enter month of publish: ");
        gets(month);
        if(!isvalid_Month(month))
            printf("Wrong month format\n");

    }
    while(!isvalid_Month(month));

    // Check if year is in the right format and add it to the variable
    do
    {
        printf("Enter year of publish: ");
        gets(year);
        if(!isvalid_year(year))
            printf("Wrong year format\n");

    }
    while(!isvalid_year(year));

    // Add the values of the variables to the array
    b[nob].dop.month=atoi(month);
    b[nob].dop.year=atoi(year);

    // Increment the number of books variable by 1
    nob++;

}


// Delete the given ISBN
// Decrease the index by 1
void DELETE()
{
    // Change edited flag
    edited = 1;

    // Declare flag to know if book is found
    int flag = 0;

    // declare a temp to store the book
    book temp;
    char ISBN_D[20];

    // Check if the ISBN is valid
    do
    {
        printf("\nEnter the book ISBN: ");
        gets(ISBN_D);
        if(!isvalid_ISBN(ISBN_D))
            printf("Wrong ISBN format");

    }
    while(!isvalid_ISBN(ISBN_D));

    //Check for ISBN to delete
    for(int j = 0; j<nob; j++)
    {
        if(strcmp(ISBN_D,b[j].ISBN) == 0)
        {
            temp = b[j];
            b[j] = b[nob-1];
            b[nob-1] = temp;
            nob--;
            flag = 1;
        }
    }

    if(flag)
    {
        return;
    }
    else
    {
        printf("Book does not exist\n");
    }
}


// Print a warning message and quit application
void QUIT()
{
    // if the file was not edited Quit without asking
    if(!edited)
    {
        printf("\nThank You \:\)");
        printf("\nGood Bye \:\)");
        exit(0);
    }


    // Variable to hold whatever the user going to enter
    char x[25];

    printf("All changes will be deleted...are u sure you want to EXIT\n");
    printf("1-Yes\n");
    printf("2-No\n");

    // Take input from user
    printf("Enter your choice: ");
    scanf("%s",x);

    // Change the user input into integer
    int choice;
    choice=atoi(x);


    while(1)
    {
        switch(choice)
        {
        case 1 :
            printf("\nThank You \:\)");
            printf("\nGood Bye \:\)");
            exit(0);
            break;

        case 2 :
            SAVE();
            break;

        default :
            printf(" Wrong number reEnter the number : \n ");
        }

        QUIT();
    }

}


// Used bubble sort to sort data by date from newest to oldest
void SortByDate()
{
    // Declare iteration variables
    int l,i,j;

    // Variable to hold changeable books
    book temp;

    // Main bubble sort algorithm
    for(i = 0; i < nob - 1; i++)
    {
        for(l = 0; l < nob - i - 1 ; l++)
        {
            if(b[l+1].dop.year > b[l].dop.year)
            {
                temp = b[l];
                b[l] = b[l+1];
                b[l+1] = temp;
            }
            else if(b[l+1].dop.year == b[l].dop.year)
            {
                if(b[l+1].dop.month >= b[l].dop.month)
                {
                    temp = b[l];
                    b[l] = b[l+1];
                    b[l+1] = temp;
                }
            }
        }
    }

    // Print the the date sorted
    for(j = 0; j < nob; j++)
    {
        printf("\nISBN: %s\n", b[j].ISBN);
        printf("Title: %s\n", b[j].title);
        printf("Author: %s\n", b[j].aName);
        printf("Quantity: %d\n", b[j].quantity);
        printf("Price: %.2f $\n", b[j].price);
        printf("Published: %s %d\n\n", month(b[j].dop.month), b[j].dop.year);
    }

}


// Used bubble sort to sort data by title from A to Z
void SortByTiTle ()
{
    // Declare iteration variables
    int i,k,j;

    // Variable to hold changeable books
    book temp;

    // Main bubble sort algorithm
    for(i=0; i< nob -1; i++)
    {
        for(k=0; k< nob - i -1; k++)
        {
            if((strcmp(b[k].title,b[k+1].title))== 1)
            {
                temp = b[k];
                b[k] = b[k+1];
                b[k+1] = temp;
            }
        }
    }

    // Print the the date sorted
    for(j = 0; j < nob; j++)
    {
        printf("\nISBN: %s\n", b[j].ISBN);
        printf("Title: %s\n", b[j].title);
        printf("Author: %s\n", b[j].aName);
        printf("Quantity: %d\n", b[j].quantity);
        printf("Price: %.2f $\n", b[j].price);
        printf("Published: %s %d\n\n", month(b[j].dop.month), b[j].dop.year);
    }

}


// Used bubble sort to sort data by price from lowest to highest
void SortByPrice()
{
    // Declare iteration variable
    int i,k,j;

    // Variable to hold changeable books
    book temp;

    // Main bubble sort algorithm
    for(i=0; i < nob - 1; i++)
    {
        for(k=0; k < nob -i -1; k++)
        {
            if(b[k].price>b[k+1].price)
            {
                temp = b[k];
                b[k] = b[k+1];
                b[k+1] = temp;
            }
        }
    }

    // Print the the date sorted
    for(j = 0; j < nob; j++)
    {
        printf("\nISBN: %s\n", b[j].ISBN);
        printf("Title: %s\n", b[j].title);
        printf("Author: %s\n", b[j].aName);
        printf("Quantity: %d\n", b[j].quantity);
        printf("Price: %.2f $\n", b[j].price);
        printf("Published: %s %d\n\n", month(b[j].dop.month), b[j].dop.year);
    }

}


// print the array of books sorted according to the user choice
void PrintSorted()
{
    //Declare variable to hold whatever user enter
    char x[50];

    // Declare variable for user choice
    int choice ;


    do
    {
        printf("\n1-sort by title \n");
        printf("2-sort by price \n");
        printf("3-sort by date \n");

        printf("How do you want to sort: ");
        scanf("%s",x);

        choice = atoi(x);

    }
    while(choice != 1 && choice != 2 && choice != 3);

    switch(choice)
    {
    case 1 :
        SortByTiTle ();
        break;

    case 2 :
        SortByPrice() ;
        break;

    case 3 :
        SortByDate();
        break;

    default :
        printf(" wrong number reEnter the number : \n ");
    }

}


// Initial menu two options (login or quit)
void init_menu()
{

    // Array to hold whatever the user enter
    char x[20];

    // Options
    printf("\n\n");
    printf("1- Login\n");
    printf("2- Quit\n");

    // Takes input from user
    printf("Enter your choice: ");
    gets(x);

    // Change input into integer
    int choice;
    choice=atoi(x);

    // True while loop
    while(1)
    {
        switch(choice)
        {
        case 1 :
            login(); // Call the login function
            break;

        case 2 :
            QUIT(); // Call the quit function
            break;

        default :
            printf("Wrong entry reEnter the number: ");
            gets(x);
            choice=atoi(x);
        }
    }

}


// Save the data inside the array to the file
void SAVE()
{
    // Change edited flag
    edited = 0;

    // Declare iteration variable
    int i;

    // Handling the file
    FILE *fptr=fopen("books.txt", "w");
    if(fptr == NULL)
    {
        printf("Error in the code!");
        exit(1);
    }

    //Write data to the file
    for(i=0; i<nob; i++)
    {
        if(i == nob -1)
            fprintf(fptr,"%s,%s,%s,%d,%.2f,%d-%d",b[i].ISBN,b[i].title,b[i].aName,b[i].quantity,b[i].price,b[i].dop.month,b[i].dop.year);
        else
            fprintf(fptr,"%s,%s,%s,%d,%.2f,%d-%d\n",b[i].ISBN,b[i].title,b[i].aName,b[i].quantity,b[i].price,b[i].dop.month,b[i].dop.year);
    }
    fclose(fptr);

    system("cls");
    printf("Saved Successfully");

}


// Modify data inside the array
void MODIFY()
{
    // String to hold ISBN from user
    char ISBN_M[20];

    // Flag to check if ISBN exist
    int found = 0;

    // Take ISBN from user
    printf("Enter ISBN: ");
    scanf("%s",ISBN_M);

    // Change edited flag
    edited = 1;

    // Declare variables to hold values untill checked
    char month[10], year[10], title[50], aName[50], quantity[10], price[50];
    int quantity_Num;
    float price_Num;


    for(int j = 0; j<nob; j++)
    {
        if (strcmp(ISBN_M,b[j].ISBN)==0)
        {
            printf("Enter new data: \n");

            getchar();
            // Hold the title value to check
            do
            {
                printf("Enter the title: ");
                gets(title);

                if(title[0] == '\0')
                    printf("Title cannot be empty\n");
            }
            while(title[0] == '\0');

            // Copy title value to the array
            strcpy(b[j].title, title);


            // Hold the author name value to check
            do
            {
                printf("Enter the name of the author: ");
                gets(aName);

                if(aName[0] == '\0')
                    printf("Author name cannot be empty\n");
            }
            while(aName[0] == '\0');

            // Copy author name value to the array
            strcpy(b[j].aName, aName);


            // Hold the quantity as an string to check
            do
            {
                printf("Enter the quantity of the book: ");
                gets(quantity);

                // Change quantity to integer to check if right format
                quantity_Num = atoi(quantity);

                if(quantity_Num == 0)
                    printf("Wrong quantity format\n");
            }
            while(quantity_Num == 0);

            // Copy quantity value to array
            b[j].quantity = quantity_Num;

            // Hold the price as an string to check
            do
            {
                printf("Enter the price of the book: ");
                gets(price);

                price_Num = atof(price);

                if(price_Num == 0)
                    printf("Wrong price format\n");
            }
            while(price_Num == 0);

            b[j].price = price_Num;


            // Check if month is in the right format and add it to the variable
            do
            {
                printf("Enter month of publish: ");
                gets(month);
                if(!isvalid_Month(month))
                    printf("Wrong month format\n");

            }
            while(!isvalid_Month(month));

            // Check if year is in the right format and add it to the variable
            do
            {
                printf("Enter year of publish: ");
                gets(year);
                if(!isvalid_year(year))
                    printf("Wrong year format\n");

            }
            while(!isvalid_year(year));

            // Add the values of the variables to the array
            b[j].dop.month=atoi(month);
            b[j].dop.year=atoi(year);

            found = 1;
            break;
        }
    }
    if(found)
        return;
    else
        printf("Book not found");
}


// print the main menu of the application
// Call each other function according to the user request
void menu ()
{
    // Declaring user request variable
    int choice;

    // Variable to hold what ever the user enter
    char x[25] ;

    // Application main menu
    printf("\n\t\t\t\t\t MAIN MENU \n");
    printf("1- ADD\n");
    printf("2- DELETE\n");
    printf("3- MODIFY\n");
    printf("4- SEARCH\n");
    printf("5- ADVANCED SEARCH \n");
    printf("6- PRINT\n");
    printf("7- SAVE\n");
    printf("8- QUIT\n");

    // Take Input from user
    printf("Enter what do you want to do: ");
    gets(x);

    // Change input to integer
    choice=atoi(x);

    while(1)
    {
        switch(choice)
        {
        case 1 :
            ADD();
            system("cls");
            printf("Added successfully");
            menu();
            break;

        case 2 :
            DELETE();
            system("cls");
            printf("Deleted successfully");
            menu();
            break;

        case 3 :
            MODIFY();
            system("cls");
            printf("Modified successfully");
            menu();
            break;

        case 4 :
            SEARCH();
            menu();
            break;

        case 5 :
            ADVANCED_SEARCH();
            menu();
            break;

        case 6 :
            PrintSorted();
            getchar();
            getchar();
            system("cls");
            menu();
            break;

        case 7 :
            SAVE();
            menu();
            break;

        case 8 :
            QUIT();
            break;

        default :
            printf("Wrong entry reEnter the number: ");
            gets(x);
            choice=atoi(x);
        }
    }
}



void main ()
{
     // Title of application
    printf("\t\t\t\t\t Library Management System \n");
    printf("\t\t\t\t\t ------------------------- \n");

    // Welcome message
    printf("\nWelcome back \:\)");

    init_menu();
}
