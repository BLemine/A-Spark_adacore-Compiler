with Ada.Text_IO; use Ada.Text_IO;
WITH Ada.Integer_Text_IO ;
USE Ada.Integer_Text_IO ;
procedure  Main is
   Count : Integer:=10;
begin
   --nm:=Count;
   while Count>0 loop
      Put_Line("Hello Ada ppl");
      Count:=Count-1;

   end loop;
   Put(Count);
end Main;
