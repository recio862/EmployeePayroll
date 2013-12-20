EmployeePayroll
===============

Designed to handle a complete payroll for various types of employees
===============

Program input

The program input consists of two files - a master file and a transaction file. 
Note: the input should be entered during runtime

===============


Master file

The master file has one line of input per employee containing:

    employee ID number
    name of up to 20 characters
    pay rate per hour
    number of dependents
    type of employee (0 for union, 1 for management)
    gender of employee (M or F)

See the document attached named "master10.txt" for an example of this file

==================

Transaction file (weekly timesheet information)

The transaction file has one line for each employee who worked containing:

    employee id number (an integer greater than 0)
    number of hours worked for the week (a floating-point value of 0.0 or greater)

This file may have any number of transactions and may be in any order.

==================

Calculations

    Gross Pay - Union members are paid 1.5 times their normal pay rate for any hours worked over 40. Management employees are paid their normal pay rate for all hours worked (they are not paid extra for hours over 40).
    Tax - All employees pay a flat 15% income tax.
    Insurance - The company pays for insurance for the employee. Employees are required to buy insurance for their dependents at a price of $20 per dependent.
    Net Pay is Gross Pay minus Tax minus Insurance. 


=================
Payroll Processing

The payroll report will be printed in a tabular (row and column) format with each column clearly labeled. 
The name of the output file is Payroll_Report.txt, and its contents for each employee will include: 

    employee ID number
    name
    tax
    insurance
    gross pay
    net pay 
    
