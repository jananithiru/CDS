//cds_createdatastore.h
/*
This function expects the database name without any extension.
For example the database file name is employee
1) The schema file that needs to be created manually before calling this
   function will be of name employee.sch which has the details as mentioned
   in the specification document. For example


   emp_no:4:int
   emp_name:30:string
   age:4:int

2) The function reads the .sch file (by appending .sch to the databasename) line by line
   and parses it using strtok (the function that is to be defined by you). Here the following
   files are created
   a) primary index file as databasename_primaryindexcolname.ndx which persists an empty stack.
      ex: employee_emp_no.ndx
   b) secondary index file as databasename_secondaryindexcolname.ndx which is an empty file.
      There should not be a freelist. ex: employee_emp_name.ndx
   c) Empty .dat files for each column name as databasename_columnname.dat
      ex: (i)   employee_emp_no.dat
          (ii)  employee_emp_name.dat
          (iii) employee_age.dat
   d) If everything was successful then return 0 else return 1.
      But take care that if it was a failure then all created files (except .sch) should be
      deleted. This means that either the function was fully successful or failed completly
      reverting the changes it did.
*/

int cds_createDataStore(char *database);
