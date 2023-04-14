1)

 create procedure showMessage is
  2  begin
  3  dbms_output.put_line('Good Day to You');
  4  end;
  5  /
Procedure created.


EXECUTE showMessage

Output
------

Good Day to You

================================================================================


2)

CREATE OR REPLACE PROCEDURE showList (deptName Instructor.dept_name%type) IS
CURSOR curseInst (deptName Instructor.dept_name%type) IS
SELECT name FROM Instructor WHERE dept_name = deptName;
CURSOR curseCourses (deptName Instructor.dept_name%type) IS
SELECT course_id FROM Course WHERE dept_name = deptName;
BEGIN
    dbms_output.put_line('...........................');
    dbms_output.put_line('-- DEPARTMENTs INSTRUCTORS --');
    FOR row IN curseInst (deptName)
    LOOP
        dbms_output.put_line('Instructor name: ' || row.name);
    END LOOP;
    dbms_output.put_line('...........................');
    dbms_output.put_line('-- COURSES --');
    FOR row IN curseCourses (deptName) LOOP
        dbms_output.put_line(' ' || row.course_id);
    END LOOP;
END;
/


 BEGIN
    showList('Physics');
    END;
    /

Output
-------

...........................
-- DEPARTMENTs INSTRUCTORS --
Instructor name: Einstein
Instructor name: Gold
...........................
-- COURSES --
PHY-101

PL/SQL procedure successfully completed.

================================================================================


3)

CREATE OR REPLACE PROCEDURE course_popular IS
CURSOR point_to_course IS
WITH studentenroll as (select course_id,count(distinct ID) as student_count from takes group by course_id),
studenmod as (select course_id,student_count,dept_name from studentenroll natural join course),
deptmax as (select max(student_count) as stud_enrolled ,dept_name from course natural join studenmod group by dept_name)
select stud_enrolled ,course_id,dept_name from studenmod natural join deptmax where student_count=stud_enrolled;
BEGIN
    FOR row IN point_to_course LOOP
        dbms_output.put_line('Department name : '||row.dept_name);
        dbms_output.put_line(' Course ID : ' || row.course_id);
        dbms_output.put_line('Number of student enrolled : '||row.stud_enrolled);
        dbms_output.put_line('-------------');
        dbms_output.new_line;
    END LOOP;
END;
/


DECLARE
begin
    dbms_output.put_line('----- Highest Enrolled Courses of all Departments ------');
    dbms_output.new_line;
    course_popular;
end;
/

Output
------

----- Highest Enrolled Courses of all Departments ------
Department name : Comp. Sci.
Course ID : CS-101
Number of student enrolled : 6
-------------
Department name : Biology
Course ID : BIO-301
Number of student enrolled : 1
-------------
Department name : Biology
Course ID : BIO-101
Number of student enrolled : 1
-------------
Department name : History
Course ID : HIS-351
Number of student enrolled : 1
-------------
Department name : Elec. Eng.
Course ID : EE-181
Number of student enrolled : 1
-------------
Department name : Finance
Course ID : FIN-201
Number of student enrolled : 1
-------------
Department name : Music
Course ID : MU-199
Number of student enrolled : 1
-------------
Department name : Physics
Course ID : PHY-101
Number of student enrolled : 1
-------------

PL/SQL procedure successfully completed.


================================================================================

4)

CREATE OR REPLACE PROCEDURE showList (deptName student.dept_name%type) IS
CURSOR curseInst (deptName student.dept_name%type) IS
SELECT name FROM student WHERE dept_name = deptName;
CURSOR curseCourses (deptName student.dept_name%type) IS
SELECT course_id FROM Course WHERE dept_name = deptName;
BEGIN
    dbms_output.put_line('...........................');
    dbms_output.put_line('-- DEPARTMENTs STUDENT--');
    FOR row IN curseInst (deptName)
    LOOP
        dbms_output.put_line('Student name: ' || row.name);
    END LOOP;
    dbms_output.put_line('...........................');
    dbms_output.put_line('-- COURSES --');
    FOR row IN curseCourses (deptName) LOOP
        dbms_output.put_line(' ' || row.course_id);
    END LOOP;
END;
/


 BEGIN
    showList('Biology');
    END;
    /

Output
------
...........................
-- DEPARTMENTs STUDENT--
Student name: Tanaka
...........................
-- COURSES --
BIO-101
BIO-301
BIO-399


5)

CREATE OR REPLACE FUNCTION square (x number)
RETURN number AS
sqrt number;
begin
    sqrt := x * x;
    RETURN sqrt;
end;
/

DECLARE
begin
    dbms_output.put_line('Square of 3 is: ' || square(3));
end;
/

Output
------

Square of 3 is: 9

================================================================================


6)

create or replace function department_highest (dName Department.dept_name%type)
RETURN Instructor.salary%type AS
max_paid Instructor.salary%type;

begin
    select max(salary) into max_paid
    from Instructor group by Instructor.dept_name having Instructor.dept_name in (select dept_name 
                                                                                  from Instructor 
                                                                                  where dept_name = dName);
    return max_paid;
end;
/


DECLARE
    maximum Instructor.salary%type;
    cursor c1 is select distinct dept_name from department;
begin
    for dname in c1 loop
        maximum := department_highest(dname.dept_name);
        dbms_output.put_line('Highest paid salary in '||dname.dept_name||' is : ' || maximum);
    end loop;
end;
/

Output
------

Highest paid salary in Biology is : 72000
Highest paid salary in Comp. Sci. is : 92000
Highest paid salary in Elec. Eng. is : 80000
Highest paid salary in Finance is : 90000
Highest paid salary in History is : 62000
Highest paid salary in Music is : 40000
Highest paid salary in Physics is : 95000
